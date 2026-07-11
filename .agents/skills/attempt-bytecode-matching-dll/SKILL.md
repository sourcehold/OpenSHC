# Attempt Bytecode Matching DLL

Iteratively improve bytecode matching between a reimplementation and the original binary using the workflow:

**Locate → Setup → Build → Compare → Analyze → Modify → Repeat**

At each iteration, perform the next phase only if the previous one succeeded.

## Workflow

### Locate
- Use the **find-function-implementation** skill to locate the target `.cpp` file.

### Setup
- Ask whether to enable source compilation for the located function.
- Mention that it is assumed the function is already active if declined.
- If yes, invoke **enable-local-function-dev** for the located function.

### Build
Run:

```powershell
.\build --wrap-quiet RelWithDebInfo OpenSHC.dll > $null 2>&1
```

If the build fails:
- Stop the workflow.
- Offer to rerun with verbose output:

```powershell
.\build RelWithDebInfo OpenSHC.dll
```

### Compare
Extract the hexadecimal address from the function comment:

```cpp
// FUNCTION: STRONGHOLDCRUSADER 0x...
```

Run:

```powershell
reccmp/dll/run --wrap-quiet reccmp-reccmp --target STRONGHOLDCRUSADER --verbose <address> 2>$null
```

If the comparison fails or produces no output:
- Stop the workflow.
- Offer to rerun with stderr enabled for diagnosis, noting that the output may be large.

### Analyze
Compare **structure**, not exact bytes.

Treat the following as expected differences:
- proxied function calls
- global resolver addresses

Instead, compare:
- control flow
- call placement
- global access patterns
- local variable ordering
- stack usage
- casts and type conversions

### Modify
Attempt structural improvements without changing program behavior.

Typical changes include:
- reordering local variables
- reordering statements
- introducing or removing temporary variables
- moving casts
- expanding or simplifying expressions
- restructuring control flow

### Repeat
Return to the **Build** phase.

After each iteration:
- report whether the match improved
- explain likely causes of remaining mismatches
- ask whether another iteration should be attempted

If 3–4 consecutive iterations show no improvement, recommend stopping.

### Optional: Enable Struct Implementations
If many diffs appear to be caused by global resolver usage, offer to enable struct implementations.
Note that this will only remove diffs caused by `<offset>` <-> `<StructResolver::Instance>` mismatches if the structure fits.
It will **not** improve structural differences.

If accepted:
1. Find every included `OpenSHC/Globals/...` header used by the function.
2. In each included header, locate its `MACRO_STRUCT_RESOLVER(...)` definition.
3. Change the second macro argument from `false` to `true`.
4. Return to the **Build** phase.
5. Report whether the match improved.

## Principles

- Preserve program behavior at all times.
- Prefer structural changes over logic changes.
- Function calls will always and global accesses will often appear as differences because they are proxied or resolved; compare only their structural placement.
- The user decides whether to continue after every iteration.
