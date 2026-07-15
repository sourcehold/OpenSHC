# Setup Function for Reimplementation

Creates a new C++ implementation file for an existing Stronghold Crusader function.

## Input

Ask for:

```text
File: <path relative to src/>
Function: <function name>
```

If validation fails, abort without creating or modifying files. Report source `.func.hpp` path, function name, and failure reason.

---

## Workflow

### 1. Validate `.func.hpp`

Locate `src/<File>`.

Find `MACRO_FUNCTION_RESOLVER(..., &Class::Function) Function;`.

The function identifier after the macro must match the requested function.

---

### 2. Extract Address

Extract only the hexadecimal value from `Address::SHC_xxxxxxxx_0xXXXXXXXX`.

Example:

`Address::SHC_3BB0A8C1_0x004C6D30` → `0x004C6D30`

Never use the symbolic identifier.

---

### 3. Resolve Paths

From `src/<path>/<Class>.func.hpp`, derive:

- Implementation folder: `src/<path>/<Class>/`
- Declaration file: `src/<path>/<Class>.hpp`

Create the implementation folder if missing. Abort if creation fails.

---

### 4. Check Implementation

Target: `src/<path>/<Class>/<Function>.cpp`.

If it exists, abort. Never overwrite.

---

### 5. Validate Declaration

Search `<Class>.hpp` for the class-qualified function declaration.

Use the exact header declaration as the implementation signature.

Abort if:
- Header is missing
- Declaration is missing
- Namespace extraction fails

---

### 6. Generate File

Create `src/<path>/<Class>/<Function>.cpp`.

Content:

```cpp
#include "../<Class>.func.hpp"

<namespace blocks>

// FUNCTION: STRONGHOLDCRUSADER <address>
<function signature> {
}
```

Rules:
- Preserve namespace order and nesting
- Copy only normal `namespace` declarations
- Ignore `using` declarations and namespace aliases
- Do not modify existing files

Example:
```
#include "../AICState.func.hpp"

namespace OpenSHC {
namespace AI {

   // FUNCTION: STRONGHOLDCRUSADER 0x004C6D30
   void AICState::wipeAICMemory() {
   }

}
}
```

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
