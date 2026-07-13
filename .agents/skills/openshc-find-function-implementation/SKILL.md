# Find Function Implementation

Resolve a single function reference to exactly one `.cpp` implementation file.

## Input

Accepted formats:

- Function: `wipeAICMemory`
- Class/function: `AICState::wipeAICMemory`
- Path: `src/OpenSHC/AI/AICState/wipeAICMemory.cpp`
- Address: `0x004C6D30`

---

## Resolution

### Function

Search `src/**/*.cpp` for implementation filenames matching the function name.

### Class/function

Restrict the search to the class folder.

Example:

`AICState::wipeAICMemory` → `src/**/AICState/wipeAICMemory.cpp`

### Path

Verify that the `.cpp` file exists.

### Address

Requires an available CLI or optimized text-search tool.

Search all `.cpp` files under `src/` for:

`FUNCTION: STRONGHOLDCRUSADER <hex-address>`

Requirements:

- Use the search tool only.
- Do not inspect files individually.

### Match Rules

For function, class/function, and address resolution:

- One match → return path.
- Zero matches → fail.
- Multiple matches → fail and report matches.

---

## Failure

On failure:

- Do not modify files.
- Stop processing.
- Report:
  - Input.
  - Reason.
  - Matches (if applicable).

---

## Output

Success: `<resolved cpp path>`

Example: `src/OpenSHC/AI/AICState/wipeAICMemory.cpp`
