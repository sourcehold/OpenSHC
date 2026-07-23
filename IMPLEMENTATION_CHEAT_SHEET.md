# Implementation Cheat Sheet

This file is meant to contain general behaviors, patterns and oddities of the compiler that are found during the reimplementation process.  
It should be used as a reference for the reimplementation process by providing possible options on how the code can be changed to produce different assembly while keeping the logic flow.  
Update whenever new information is discovered!

Note, that Ghidra and reccmp use slightly different disassembly styles, so there might be different opcodes generated. Example: JZ (Jump if Zero) and JE (Jump if Equal) mean the same and are the same instruction. So do not get confused.

## Boundaries

Certain instructions work as boundaries between different code segments, preventing reordering of instructions and aiding in identifying the possible structure. 

### Functions

The main boundary. Regular functions use one of the Visual C++ call conventions:

| Convention   | Arg order    | Register args | Cleanup          | Volatile registers | Non-volatile registers |
| ------------ | ------------ | ------------- | ---------------- | ------------------ | ---------------------- |
| `__cdecl`    | Right → Left | None          | Caller           | EAX, ECX, EDX      | EBX, ESI, EDI, EBP     |
| `__stdcall`  | Right → Left | None          | Callee           | EAX, ECX, EDX      | EBX, ESI, EDI, EBP     |
| `__fastcall` | Right → Left | ECX, EDX      | Callee           | EAX, ECX, EDX      | EBX, ESI, EDI, EBP     |
| `__thiscall` | Right → Left | ECX = `this`  | Callee (usually) | EAX, ECX, EDX      | EBX, ESI, EDI, EBP     |

| Type                | Register                |
| ------------------- | ----------------------- |
| 8/16/32-bit integer | EAX                     |
| 64-bit integer      | EDX:EAX                 |
| Pointer             | EAX                     |
| Float (`float`)     | x87 ST(0)               |
| Double              | x87 ST(0)               |
| Large struct/class  | Hidden pointer argument |

Instructions usually are not moved to the other side of a call.
Variables/Globals accessed through pointers have to be considered changed due to aliasing. The compiler can not prove they
are the same, so they would need to be pulled into a register again.

If a volatile register is **NOT** used as return register but still used after the call without it being rewritten,
it is a clean indication of a known function body. The source of the other function was likely in the same file,
allowing the compiler to optimize the register usage.

### Conditionals

Instructions can only be pulled:
- before a condition block if every block has the same instruction at the start.
- after a condition block if every block that does not return has the same instruction at the end.

This also applies when putting instructions inside the condition branches.

### Variable Usage

Naturally, the logic flow needs to be kept, so the update of a variable can not move before or after another usage of the same variable.

## Structure

### Bitwise Operations

Decompiler code that contains complex bitwise instructions that can not be explained by flag operations might hint
at the usage of a structure that the compiler optimized.
If not contained in the examples here yet, AI is usually good at identifying them.

The most prominent example are modulo operations so far:
```cpp
if ((int)SEC_RNG.currentNumber1 % 3 == 0) {
    DAT_SoundEffectsHelperData1.field6_0x34 = 1;
}
else {
    DAT_SoundEffectsHelperData1.field6_0x34 = (-(uint)((int)SEC_RNG.currentNumber1 % 3 != 1) & 0xfffffffe) + 2;
}
```
is roughly:
```cpp
int const randomNumber = SEC_RNG::instance.currentNumber1 % 3;
if (randomNumber == 0)
    DAT_SoundEffectsHelperData1::instance.field6_0x34 = 1;
else if (randomNumber == 1)
    DAT_SoundEffectsHelperData1::instance.field6_0x34 = 2;
else
    DAT_SoundEffectsHelperData1::instance.field6_0x34 = 0;
```

Or another modulo:
```cpp
uVar1 = (int)SEC_RNG.currentNumber1 & 0x80000003;
if ((int)uVar1 < 0) {
    uVar1 = (uVar1 - 1 | 0xfffffffc) + 1;
}
```
being
```cpp
SEC_RNG::ptr->currentNumber1 % 4
```

### Variables

- Ghidra declares all variables at the start of a function. Please try to declare them when needed. Helps the readability.
- The assembly may contain multiple assigns of the same value to the same variable within the same boundary. This might be optimization suggesting there was only one assign.
- The decompiler may suggest multiple assigns of the same value to the same variable within the same boundary. If this is not present in the assembly, it might be an artifact.
- Sometimes, the decompiler may suggest a temporary variable while the compiler requires the direct usage of the variable for the byte-match.
  - This may even include cases that can get pretty long in our style, like a variable access providing the index for an array.
- If a variable is stored in a temporary, before it is directly being incremented or decremented by one, suggests a post-increment/decrement, even more if the temporary is then used after.

### Conditionals

- Ghidra's decompiler sometimes uses a number off by one for the condition compared to the assembly. Use the assembly as reference in this case.
- Ghidra's decompiler sometimes inverts the condition in an if-else case and therefore also the blocks. In most cases, the condition and the block order are like the assembly suggests. Only in some cases the order is actually inverted compared to the source:
  - Certain pressure might cause this. This can only be detected through tests.
  - Early returns.
- A condition block wrapping the entire remaining code of the function or loop can often be inverted to an early return or break, increasing readability.
- If a condition suddenly uses a normally signed variable as unsigned value (e.g. `ja` compared to signed `jg`) and most times also contains a subtraction, it suggests a range condition optimization. The actual value was moved to 0 to allow expressing this via a single check:
  - Decomp code example: `DAT_GameCore.missionNumber1to20 - 1U < 0x14`
  - Original (likely): `1 <= DAT_GameCore.missionNumber1to20 && DAT_GameCore.missionNumber1to20 <= 20`
- A switch with fewer then 4 cases is often simplified and uses subtractions in assembly to compare the value:
  ```
  MOV          EAX,[DAT_SoundEffectsHelperData1.SEC_Section1079.  volumeLevel]
  SUB          EAX,EBX
  JZ           LAB_0047c029
  SUB          EAX,EBX
  JZ           LAB_0047bfef
  SUB          EAX,0x3
  JNZ          LAB_0047c386
  ```
  Once 4 are reached, the switch is probably converted to a table lookup.  
  This structure shows up as if-else chain in the decompiler, so do not be confused and check the assembly if the conditions are repeated checks of the same value. 

### Loops

Loops are very often presented in the decompiler as a pointer being incremented or decremented. The pointer is often created by getting the address to an array before the loop. There is also often a condition variable present that is incremented or decremented with the direction not necessarily matching the direction of the pointer increment.

Example:
```cpp
int _soundIndex = 1;
if (1 < DAT_SoundSystemState.loadedSoundsCountAndIndex_0x316c) {
    int* piVar1 = DAT_SoundSystemState.soundFileCurrSampleNum_0x28c;
    do {
        piVar1 = piVar1 + 1;
        if ((-1 < *piVar1) && (piVar1[0xbda] != 0)) {
            DAT_SoundSystemState.samplePaused_0x31f4[*piVar1] = 0;
            AIL_resume_sample(DAT_SoundSystemState.sample[*piVar1]);
        }
        _soundIndex = _soundIndex + 1;
    } while (_soundIndex < DAT_SoundSystemState.loadedSoundsCountAndIndex_0x316c);
}
```

This can and should be simplified to a default for-block with array index access:
```cpp
for (int soundIndex = 1; soundIndex < this->loadedSoundsCountAndIndex_0x316c; ++soundIndex) {
    if (this->soundFileCurrSampleNum_0x28c[soundIndex] < 0 || !this->samplePaused_0x31f4[soundIndex]) {
        continue;
    }
    this->samplePaused_0x31f4[this->soundFileCurrSampleNum_0x28c[soundIndex]] = false;
    AIL_resume_sample(this->sample[this->soundFileCurrSampleNum_0x28c[soundIndex]]);
}
```

This covers most cases like this.

An exception is when the update parts of the pointer and index are not the last instructions before the loop condition.
This indicates manual handling like in a while loop.

If you see a repeating logic structure, that, for example, increments by a value in its logic every repeat,
you might have found an unrolled loop. Therefore, try to reproduce the logic in loop form and see how the compiler behaves.

### GOTO

A function may contain multiple GOTOs.
These might be very large condition blocks the decompiler did not wrap.
Often, however, these indicate that the compiler optimized certain branches by reusing the assembly code.

These are very hard to get right, since it is sometimes unclear which parts need to be unified and which code needs to be doubled at different positions.
Despite this, still try to remove the GOTOs.
They might be worth trying in very tricky cases, but they were usually seen as code smell even back then and were unlikely to be present in the code.
