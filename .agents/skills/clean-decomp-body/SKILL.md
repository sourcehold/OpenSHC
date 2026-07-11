# Clean Decomp Body

Transforms decompiled C++ function implementations into the project's macro/global style while preserving the original logic.

## Workflow

### Input

Request the function implementation file using **Find Function Implementation**.

Transform the file directly. Do not create a separate replacement snippet unless requested.

### Abort Conditions

Do not transform if:
- The body is empty or contains no meaningful code.
- The code already matches cleaned style:
  - Uses `MACRO_CALL` / `MACRO_CALL_MEMBER`.
  - Uses `::instance` / `::ptr` for global access.
  - Uses `_Func` namespaces inside function macros.
  - Already uses correct namespaces and imports.

Report that no transformation is required.

---

## Rules

Preserve:
- Control flow.
- Local variables.
- Conditions.
- Returns.
- Statement order.
- Switch structure.
- Original logic.

Do not:
- Refactor.
- Simplify.
- Remove code.
- Reorder code.

Never invent:
- namespaces
- globals
- singleton names
- imports

If a required transformation cannot be resolved from the implementation or project context, ask for clarification instead of guessing.
Leave all code not covered by these transformation rules unchanged.

---

## Transformation Process

Apply transformations in this order:

### 1. Determine Context

Identify:
- Current class if member function.
- Existing imports.
- Function and class namespaces.
- Required function/global dependencies.

Use this information for all following transformations.

---

### 2. Function Calls

Replace direct calls:

`Namespace::Function(args)` → `MACRO_CALL(Namespace_Func::Function)(args)`

Replace member calls using global objects:

`Namespace::Class::Function(&Global, args)` or `Namespace::Class::Function(Global, args)` → `MACRO_CALL_MEMBER(Namespace::Class_Func::Function, Global::ptr)(args)`

Rules:
- Keep normal namespaces for classes and functions.
- Only add `_Func` inside macro function references.
- Use the resolved namespace to determine the required `.func.hpp` import.
- Apply transformations recursively, including nested function calls.

---

### 3. Member Field Access

Member field access might appear through a global in the code, since many are singletons.

Determine from the function signature whether the implementation is a member function: `<class>::<function>(<params>)`

If so, identify the singleton/global representing the current class. For example: `DAT_<class>`

Transform to `this` access:

`DAT_<class>.field` → `this->field`

If the required global cannot be identified, ask for clarification instead of guessing.

---

### 4. Global Access

Convert globals for field access:

`SEC_RNG.currentNumber1` → `SEC_RNG::instance.currentNumber1`

Only use pointer in cases of function calls or pointer assigns:

`&DAT_Global` → `DAT_Global::ptr`

Keep global namespaces.

---

### 5. Namespace Resolution

Ensure classes, functions, and types use their correct namespaces after transformation.

Rules:
- Macro function references use the `_Func` namespace: `SFX::SFXState_Func::PlaySpeechSFX`
- Types and globals keep their normal namespaces.

Use namespace information to identify required imports.

---

### 6. Imports

Add only required dependency imports.

Rules:
- The current file's relative `.func.hpp` import already exists. Do not add or modify it.
- Add `.func.hpp` imports for called functions/classes.
- Add global `.hpp` imports for accessed globals. Not for the transformed class global.
- Global imports always use `OpenSHC/Globals/<Name>.hpp`.
- All new imports must use the full project path.
- Do not add unused imports.
- Preserve existing include grouping.
- Do not duplicate existing imports.

Example:

```cpp
#include "OpenSHC/Audio/SFX/SFXState.func.hpp"

#include "OpenSHC/Globals/DAT_SFXState.hpp"
```

---

## File Structure

Keep the existing file structure.

Preserve:
- Existing namespace layout.
- Function address comments: `// FUNCTION: STRONGHOLDCRUSADER 0xXXXXXXXX`

---

## Output

Apply the transformation directly to the function implementation file.

The CLI response should only contain a short summary:
- Functions converted to `MACRO_CALL` / `MACRO_CALL_MEMBER`.
- Globals converted to `::instance`, `::ptr`, or `this`.
- Imports added.
- Namespace/type adjustments made.

Do not output the full transformed file unless explicitly requested.
