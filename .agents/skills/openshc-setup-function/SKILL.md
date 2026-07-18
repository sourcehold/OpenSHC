# Setup Function for Reimplementation

Creates a new C++ implementation file for an existing Stronghold Crusader function.

## Input

Accepted formats:

- Function: `wipeAICMemory`
- Class/function: `AICState::wipeAICMemory`
- Address: `0x004C6D30`

If validation fails, abort without creating or modifying files and report the failure reason.

---

## Workflow

Powershell script call: `tools/reimplementation-helper/Setup-Function-Implementation.ps1 -Partial -Query <input>`

- If a function name was requested and the resulting name is different, mention the partial match.
- Use the returned path to the implementation file for the completion report.

---

## Completion Report

Output:

```text
Created:
<file path>

Function:
<function name>

Address:
<hex address>
```
