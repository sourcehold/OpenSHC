#!/usr/bin/env python3
"""Pick N functions with the worst match from status_rollup.tsv.

Preference is given to functions sharing a namespace (the ``A::B`` prefix
derived from expected_cpp), so a batch of picks tends to land in one class.

The rollup is fetched from the project's latest-sarif release by default;
pass --tsv with a local path (or another URL) to override it.

Usage:
    python pick_worst.py [-n N] [--tsv PATH_OR_URL] [--namespace NS]
                         [--include-done] [--max-pct P] [--spread]
                         [--format table|tsv|json|addresses]
"""

import argparse
import csv
import io
import json
import os
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
            })
        return rows


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
    if fmt == "tsv":
        cols = ["address", "pct", "namespace", "function", "refs", "status", "cpp"]
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
    ap.add_argument("--format", choices=["table", "tsv", "json", "addresses"],
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

    print(render(select(pool, args.count, spread=args.spread), args.format))
    return 0


if __name__ == "__main__":
    sys.exit(main())
