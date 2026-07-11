# Enable Local Function Development

Configures `cmake/openshc-sources.txt.local` with selected `.cpp` implementations.

## Input

Request a list of functions.

Accepted formats:

- Function: `wipeAICMemory`
- Class/function: `AICState::wipeAICMemory`
- Path: `src/OpenSHC/AI/AICState/wipeAICMemory.cpp`
- Address: `0x004C6D30`

Mixed formats are allowed.

On failure, abort without modifying files and report the input and reason.

---

## Resolve Inputs

Deduplicate inputs while preserving order.

### Function identifiers

Resolve to `.cpp` implementation files under `src/`.

Function only:

Search for matching implementation filenames.

If zero or multiple matches are found, abort and report matches.

Class/function:

Restrict the search to the matching class folder.

Example:

`AICState::wipeAICMemory`

→

`src/**/AICState/wipeAICMemory.cpp`

If zero or multiple matches are found, abort and report matches.

### Paths

Verify the `.cpp` file exists.

### Addresses

Require an available CLI or optimized text-search tool.

Use this tool to search all `.cpp` files under `src/` for:

`FUNCTION: STRONGHOLDCRUSADER <hex-address>`

The AI must not perform address searches by reading files individually.

If no suitable search tool exists, abort.

If zero or multiple matches are found, abort and report matches.

---

## Update Configuration

Manage:

`cmake/openshc-sources.txt.local`

Create it if missing.

Rewrite the file contents with the resolved paths. Do not append.

Rules:
- Paths are relative to project root
- Use `/` separators
- Preserve order
- End with newline

Never modify:

`cmake/openshc-sources.txt`

---

## Completion

Output:

```text
Configured <count> files for local development

Files:
<path>
<path>
...
```
