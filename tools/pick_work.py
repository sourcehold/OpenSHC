#!/usr/bin/env python3
"""Pick N functions with the worst match from status_rollup.tsv.

Preference is given to functions sharing a namespace (the ``A::B`` prefix
derived from expected_cpp), so a batch of picks tends to land in one class.

The rollup is fetched from the project's latest-sarif release by default;
pass --tsv with a local path (or another URL) to override it.

Every pick is reported with the URL of the place its best match lives, derived
from the rollup's best_source (``main`` or a remote-tracking branch such as
``owner-OpenSHC/reimpl/foo``) and the local git remotes. With --all-sources the
local fork branches are scanned as well, so each pick lists every branch that
has the function and the URL of the file on that branch.

Usage:
    python pick_worst.py [-n N] [--tsv PATH_OR_URL] [--namespace NS]
                         [--include-done] [--max-pct P] [--spread]
                         [--all-sources] [--format table|tsv|json|addresses|urls]
"""

import argparse
import csv
import io
import json
import os
import re
import subprocess
import sys
import urllib.error
import urllib.request
from collections import defaultdict

DEFAULT_TSV = ("https://github.com/sourcehold/OpenSHC/releases/download/"
               "latest-sarif/status_rollup.tsv")


def namespace_of(expected_cpp):
    """src/OpenSHC/Rendering/ViewportRenderState/foo.cpp -> Rendering::ViewportRenderState"""
    if not expected_cpp:
        return "<unknown>"
    parts = expected_cpp.replace("\\", "/").split("/")[:-1]
    # drop the leading src/ and the project root directory (OpenSHC)
    while parts and parts[0] in ("src", "source", "."):
        parts.pop(0)
    if parts and parts[0].startswith("OpenSHC"):
        parts.pop(0)
    return "::".join(parts) if parts else "<unknown>"


def function_of(expected_cpp):
    if not expected_cpp:
        return ""
    return os.path.splitext(os.path.basename(expected_cpp.replace("\\", "/")))[0]


def to_float(text, default=0.0):
    try:
        return float(str(text).strip().rstrip("%"))
    except (TypeError, ValueError):
        return default


def to_int(text, default=0):
    try:
        return int(str(text).strip())
    except (TypeError, ValueError):
        return default


def open_rollup(source, timeout=30):
    """Open a local path or an http(s) URL as a text handle."""
    if source.startswith(("http://", "https://")):
        request = urllib.request.Request(
            source, headers={"User-Agent": "pick_worst.py"})
        with urllib.request.urlopen(request, timeout=timeout) as response:
            text = response.read().decode("utf-8-sig", errors="replace")
        return io.StringIO(text, newline="")
    return open(source, newline="", encoding="utf-8-sig")


def load(source):
    with open_rollup(source) as handle:
        rows = []
        for raw in csv.DictReader(handle, delimiter="\t"):
            cpp = (raw.get("expected_cpp") or "").strip()
            rows.append({
                "shc_id": (raw.get("shc_id") or "").strip(),
                "address": (raw.get("address") or "").strip(),
                "done": (raw.get("done") or "").strip().lower() == "yes",
                "pct": to_float(raw.get("best_pct")),
                "status": (raw.get("best_status") or "").strip(),
                "source": (raw.get("best_source") or "").strip(),
                "refs": to_int(raw.get("refs_at_100")),
                "cpp": cpp,
                "namespace": namespace_of(cpp),
                "function": function_of(cpp),
                "url": "",
                "sources": [],
            })
        return rows


DEFAULT_REPO_URL = "https://github.com/sourcehold/OpenSHC"
#: one entry per line: SHC_<hash>_0x<addr> | <pct>% | <status text>
ENTRY = re.compile(r"^\s*(SHC_[0-9A-Fa-f]+_0x[0-9A-Fa-f]+)\s*\|\s*([0-9.]+)%\s*\|\s*(.*?)\s*$")
STATUS_GLOB = re.compile(r"^status/addresses-SHC-[0-9A-Fa-f]+\.txt$")


def git(args):
    """-> (returncode, stdout); never raises, so a missing repo degrades gracefully."""
    try:
        p = subprocess.run(["git"] + args, capture_output=True, text=True,
                           errors="replace")
    except OSError:
        return 1, ""
    return p.returncode, p.stdout


def web_base(url):
    """git remote url -> browsable https base, or '' if it is not a known host."""
    url = url.strip()
    if url.startswith("git@"):
        host, _, path = url[4:].partition(":")
        url = "https://{}/{}".format(host, path)
    elif url.startswith("ssh://git@"):
        url = "https://" + url[len("ssh://git@"):]
    if not url.startswith(("http://", "https://")):
        return ""
    return url[:-4].rstrip("/") if url.endswith(".git") else url.rstrip("/")


def remote_bases():
    """-> {remote name: browsable https base} for the local remotes."""
    rc, out = git(["remote", "-v"])
    bases = {}
    for line in out.splitlines():
        parts = line.split()
        if len(parts) >= 2 and parts[0] not in bases:
            base = web_base(parts[1])
            if base:
                bases[parts[0]] = base
    return bases


def source_url(source, cpp, bases):
    """'owner-OpenSHC/reimpl/foo' + a cpp path -> the URL of that file on GitHub.

    'main' (the rollup's name for HEAD) is the project's own repository,
    sourcehold/OpenSHC. Remote names never contain a slash, so the
    first component of a remote-tracking branch is the remote.
    """
    if not source or source == "main":
        # the rollup's 'main' is the project's own main, not whatever this
        # checkout's origin happens to be
        base, branch = DEFAULT_REPO_URL, "main"
    else:
        remote, _, branch = source.partition("/")
        if not branch:
            return ""
        base = bases.get(remote)
        if base is None:
            # not fetched locally: rebuild owner/name from the remote name, which
            # fetch_fork_branches made by replacing the slash with a dash
            owner, _, name = remote.partition("-")
            if not name:
                return ""
            base = "https://github.com/{}/{}".format(owner, name)
    if cpp:
        return "{}/blob/{}/{}".format(base, branch, cpp.replace("\\", "/"))
    return "{}/tree/{}".format(base, branch)


def reimpl_refs(filter_re):
    """-> ['HEAD'] + the remote-tracking branches whose name matches the filter."""
    rc, out = git(["branch", "-r", "--format=%(refname:short)"])
    refs = [b.strip() for b in out.splitlines()
            if b.strip() and "->" not in b and filter_re.search(b)]
    return ["HEAD"] + sorted(refs)


def ref_rows(ref, wanted):
    """-> {shc id: (pct, status)} for the wanted ids in one ref's status files."""
    rc, out = git(["ls-tree", "-r", "--name-only", ref, "--", "status"])
    rows = {}
    for path in out.splitlines():
        path = path.strip()
        if not STATUS_GLOB.match(path):
            continue
        rc, text = git(["show", "{}:{}".format(ref, path)])
        if rc != 0:
            continue
        for line in text.splitlines():
            m = ENTRY.match(line)
            if m and m.group(1) in wanted:
                rows[m.group(1)] = (float(m.group(2)), m.group(3).strip())
    return rows


def collect_sources(picks, pattern="", min_pct=None, progress=False,
                    keep_duplicates=False):
    """Fill each pick's 'sources' with every ref that reports the function.

    Branch contents are taken as truth exactly as status_rollup.py does: nothing
    is re-measured, only the per-address status files are read.

    Most of these branches are cut from one another, so the same file turns up
    verbatim on dozens of them. Sources are therefore grouped by the blob id of
    the cpp on that branch: one entry per distinct version of the function,
    carrying the other branches that hold the identical file in 'also_on'.
    """
    wanted = {r["shc_id"]: r for r in picks}
    bases = remote_bases()
    refs = reimpl_refs(re.compile(pattern))
    for i, ref in enumerate(refs, 1):
        if progress:
            print("scanning {}/{}: {}".format(i, len(refs), ref),
                  end="\r", file=sys.stderr)
        for sid, (pct, status) in ref_rows(ref, wanted).items():
            # every branch carries a status line for every address, so a branch
            # that has not touched the function reports 0% and has no file
            if pct <= (0.0 if min_pct is None else min_pct - 1e-9):
                continue
            row = wanted[sid]
            source = "main" if ref == "HEAD" else ref
            rc, blob = git(["rev-parse", "--verify", "--quiet",
                            "{}:{}".format(ref, row["cpp"])])
            row["sources"].append({
                "source": source,
                "pct": pct,
                "status": status,
                "url": source_url(source, row["cpp"], bases),
                "blob": blob.strip() if rc == 0 else "",
                "also_on": [],
            })
    if progress:
        print(" " * 60, end="\r", file=sys.stderr)
    for row in picks:
        row["sources"].sort(key=lambda s: (-s["pct"], s["source"]))
        if not keep_duplicates:
            row["sources"] = dedupe_sources(row["sources"])
    return picks


def dedupe_sources(sources):
    """Collapse sources whose cpp is byte-identical into one entry each."""
    out, by_blob = [], {}
    for src in sources:
        first = by_blob.get(src["blob"]) if src["blob"] else None
        if first is None:
            if src["blob"]:
                by_blob[src["blob"]] = src
            out.append(src)
        else:
            first["also_on"].append(src["source"])
    return out


#: namespaces that hold generated / runtime glue rather than game logic
SKIPPED_NAMESPACES = ("OS", "Global::Init")


def is_runtime(row):
    """CRT / runtime glue: underscore-prefixed names and the skipped namespaces."""
    ns = row["namespace"]
    return (row["function"].startswith("_")
            or any(ns == skip or ns.startswith(skip + "::")
                   for skip in SKIPPED_NAMESPACES))


def badness_key(row):
    """Worst first: lowest percentage, then most-referenced, then address."""
    return (row["pct"], -row["refs"], row["address"])


def select(rows, n, prefer_namespace=True, spread=False):
    candidates = sorted(rows, key=badness_key)
    if not candidates or n <= 0:
        return []
    if spread or not prefer_namespace:
        return candidates[:n]

    by_ns = defaultdict(list)
    for row in candidates:
        by_ns[row["namespace"]].append(row)

    def ns_rank(item):
        ns, members = item
        head = members[:n]
        # prefer namespaces that can fill the batch and whose members are worst
        return (-min(len(head), n), sum(r["pct"] for r in head) / len(head), ns)

    picks, seen = [], set()
    for ns, members in sorted(by_ns.items(), key=ns_rank):
        for row in members:
            if len(picks) >= n:
                break
            if row["shc_id"] not in seen:
                seen.add(row["shc_id"])
                picks.append(row)
        if len(picks) >= n:
            break
    # pad with the globally worst if the chosen namespaces ran dry
    for row in candidates:
        if len(picks) >= n:
            break
        if row["shc_id"] not in seen:
            seen.add(row["shc_id"])
            picks.append(row)
    return sorted(picks[:n], key=badness_key)


def render(picks, fmt):
    if fmt == "json":
        return json.dumps(picks, indent=2)
    if fmt == "addresses":
        return "\n".join(r["address"] for r in picks)
    if fmt == "urls":
        out = []
        for r in picks:
            for src in r["sources"] or [{"source": r["source"], "pct": r["pct"],
                                         "url": r["url"], "also_on": []}]:
                out.append("{}\t{:.1f}\t{}\t{}".format(
                    r["address"], src["pct"], src["source"], src["url"]))
        return "\n".join(out)
    if fmt == "tsv":
        cols = ["address", "pct", "namespace", "function", "refs", "status",
                "source", "url", "cpp"]
        out = ["\t".join(cols)]
        out += ["\t".join(str(r[c]) for c in cols) for r in picks]
        return "\n".join(out)

    lines, last_ns = [], None
    for r in picks:
        if r["namespace"] != last_ns:
            lines.append("")
            lines.append(r["namespace"])
            last_ns = r["namespace"]
        lines.append("  {:>6.1f}%  {}  refs={:<4} {}".format(
            r["pct"], r["address"], r["refs"], r["function"] or r["shc_id"]))
        if r["status"]:
            lines.append("           status: {}".format(r["status"]))
        if r["sources"]:
            for src in r["sources"]:
                lines.append("           {:>6.1f}%  {}".format(
                    src["pct"], src["url"] or src["source"]))
                if src["also_on"]:
                    lines.append("                    (identical on {} other "
                                 "branch(es))".format(len(src["also_on"])))
        elif r["url"]:
            lines.append("           {:>6.1f}%  {}".format(r["pct"], r["url"]))
    counts = defaultdict(int)
    for r in picks:
        counts[r["namespace"]] += 1
    lines.append("")
    lines.append("{} picked across {} namespace(s): {}".format(
        len(picks), len(counts),
        ", ".join("{} x{}".format(ns, c) for ns, c in
                  sorted(counts.items(), key=lambda kv: -kv[1]))))
    return "\n".join(lines).lstrip("\n")


def main(argv=None):
    ap = argparse.ArgumentParser(
        description=__doc__,
        formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("-n", "--count", type=int, default=5,
                    help="how many functions to pick (default 5)")
    ap.add_argument("--tsv", default=DEFAULT_TSV,
                    help="local path or URL of status_rollup.tsv "
                         "(default: the latest-sarif release asset)")
    ap.add_argument("--namespace", help="restrict to namespaces containing this text")
    ap.add_argument("--include-done", action="store_true",
                    help="also consider rows marked done=yes")
    ap.add_argument("--max-pct", type=float,
                    help="only consider rows at or below this match percentage")
    ap.add_argument("--include-runtime", action="store_true",
                    help="also consider CRT/runtime glue: names starting with '_' "
                         "and the ::OS and ::Global::Init namespaces (all skipped by default)")
    ap.add_argument("--min-pct", type=float,
                    help="only consider rows above this match percentage "
                         "(use --min-pct 0 to skip untouched Pending rows)")
    ap.add_argument("--min-refs", type=int, default=0,
                    help="only consider rows with at least this many refs_at_100")
    ap.add_argument("--spread", action="store_true",
                    help="ignore namespace grouping; take the globally worst N")
    ap.add_argument("--all-sources", action="store_true",
                    help="scan the local fork branches and list every branch "
                         "that has the function, with the URL of its file there "
                         "(slow: one pass over every remote-tracking branch)")
    ap.add_argument("--sources-filter", default="",
                    help="regex narrowing the remote-tracking branches to scan "
                         "with --all-sources (default: all of them)")
    ap.add_argument("--sources-min-pct", type=float,
                    help="with --all-sources, only list branches at or above "
                         "this match percentage (default: above 0%%, i.e. every "
                         "branch that has actually touched the function)")
    ap.add_argument("--keep-duplicate-sources", action="store_true",
                    help="with --all-sources, list every branch separately "
                         "instead of collapsing branches whose file is identical")
    ap.add_argument("--format", choices=["table", "tsv", "json", "addresses", "urls"],
                    default="table")
    ap.add_argument("--list-namespaces", action="store_true",
                    help="print a per-namespace badness summary instead of picks")
    args = ap.parse_args(argv)

    try:
        rows = load(args.tsv)
    except (OSError, urllib.error.URLError) as exc:
        print("cannot read {}: {}".format(args.tsv, exc), file=sys.stderr)
        return 2

    pool = rows
    if not args.include_done:
        pool = [r for r in pool if not r["done"]]
    if not args.include_runtime:
        pool = [r for r in pool if not is_runtime(r)]
    if args.max_pct is not None:
        pool = [r for r in pool if r["pct"] <= args.max_pct]
    if args.min_pct is not None:
        pool = [r for r in pool if r["pct"] > args.min_pct]
    if args.min_refs:
        pool = [r for r in pool if r["refs"] >= args.min_refs]
    if args.namespace:
        needle = args.namespace.lower()
        pool = [r for r in pool if needle in r["namespace"].lower()]

    if not pool:
        print("no candidates after filtering", file=sys.stderr)
        return 1

    if args.list_namespaces:
        by_ns = defaultdict(list)
        for r in pool:
            by_ns[r["namespace"]].append(r)
        summary = sorted(by_ns.items(),
                         key=lambda kv: (sum(x["pct"] for x in kv[1]) / len(kv[1]),
                                         -len(kv[1])))
        for ns, members in summary:
            print("{:>5} fns  avg {:>6.1f}%  min {:>6.1f}%  {}".format(
                len(members), sum(x["pct"] for x in members) / len(members),
                min(x["pct"] for x in members), ns))
        return 0

    picks = select(pool, args.count, spread=args.spread)

    bases = remote_bases()
    for row in picks:
        row["url"] = source_url(row["source"], row["cpp"], bases)
    if args.all_sources:
        collect_sources(picks, pattern=args.sources_filter,
                        min_pct=args.sources_min_pct,
                        progress=sys.stderr.isatty(),
                        keep_duplicates=args.keep_duplicate_sources)

    print(render(picks, args.format))
    return 0


if __name__ == "__main__":
    sys.exit(main())
