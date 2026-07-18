# Find Function Implementation

Resolve a single function reference to exactly one `.cpp` implementation file.

## Input

Accepted formats:

- Function: `wipeAICMemory`
- Class/function: `AICState::wipeAICMemory`
- Address: `0x004C6D30`

---

## Resolution

Powershell script call: `tools/reimplementation-helper/Get-Function-Data.ps1 -Partial -Query <input>`

- If a function name was requested and the resulting name is different, mention the partial match.
- Use the implementation file and the exists parameter.
- Report failure if implementation file does not exist.

---

## Failure

On failure:

- Do not modify files.
- Stop processing.
- Report:
  - Input.
  - Reason.

---

## Output

Success: `<resolved cpp path>`

Example: `src/OpenSHC/AI/AICState/wipeAICMemory.cpp`
