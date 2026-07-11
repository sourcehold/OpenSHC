# Enable Local Function Development

Configure `cmake/openshc-sources.txt.local` with selected `.cpp` implementations.

## Input

Request a list of functions.

Accepted formats:

- Function: `wipeAICMemory`
- Class/function: `AICState::wipeAICMemory`
- Path: `src/OpenSHC/AI/AICState/wipeAICMemory.cpp`
- Address: `0x004C6D30`

Mixed formats are allowed.

---

## Resolve Inputs

Resolve each input using **Find Function Implementation**.

Rules:

- Deduplicate resolved paths while preserving input order.
- If any input fails to resolve, abort.
- Do not modify files on failure.
- Report the failing input and reason.

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
