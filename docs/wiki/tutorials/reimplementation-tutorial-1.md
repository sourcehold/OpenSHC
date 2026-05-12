# Tutorials
## Reimplementation Tutorial 1

For this tutorial, I chose to reimplement the function: `OpenSHC::AI::AICState::setFoodBuyPlan`, which is a member function of class `AICState`. This function doesn't contain any calls to other functions, and I understand the Ghidra decompilation for this function, which makes reimplementation simpler.

### Step 1: the groundwork

Every file in OpenSHC has a deterministic location. The reimplementation for function `OpenSHC::AI::AICState::setFoodBuyPlan` should be placed in `OpenSHC/AI/AICState/setFoodBuyPlan.cpp`. Everything in OpenSHC is also namespaced.

Therefore, we create file: `OpenSHC/AI/AICState/setFoodBuyPlan.cpp` with the following contents
```cpp=
#include "OpenSHC/AI/AICState.hpp"

namespace OpenSHC {
namespace AI {
    void AICState::setFoodBuyPlan(int playerID) { };
}
}

```

Now, for `reccmp` to be able to associate this definition with the one in the original binary, we insert an annotation containing the address of this function in the original binary. You can find this address in `OpenSHC/AI/AICState.func.hpp`, which contains this:

```cpp=
        MACRO_FUNCTION_RESOLVER(
            void (AICState::*)(int), false, Address::SHC_3BB0A8C1_0x004CB060, &AICState::setFoodBuyPlan)
        setFoodBuyPlan;
```

(If you use an IDE like VSCode it is easiest to just search for `AICState::setFoodBuyPlan`)

Let's insert the annotation:

```cpp=
#include "OpenSHC/AI/AICState.hpp"

namespace OpenSHC {
namespace AI {
    // FUNCTION: STRONGHOLDCRUSADER 0x004CB060
    void AICState::setFoodBuyPlan(int playerID) { };
}
}

```

Now, for the compiler to include this .cpp file in the compilation, we add it to `cmake/openshc-sources.txt.local` (use the .local file for local development):

`cmake/openshc-sources.txt.local`:
```txt=
src/OpenSHC/AI/AICState/setFoodBuyPlan.cpp
```

Now we are ready to compile:
```bash
build.bat RelWithDebInfo OpenSHC.dll
```

Hopefully the compiler output ends with:
```raw
[ 88%] Building CXX object CMakeFiles/OpenSHC.dll.dir/src/OpenSHC/AI/AICState/setFoodBuyPlan.cpp.obj
setFoodBuyPlan.cpp
[100%] Linking CXX shared library DLL\OpenSHC.dll
[100%] Built target OpenSHC.dll
Build completed successfully for preset "RelWithDebInfo" target "OpenSHC.dll".
```


### Step 2: getting an initial reimplementation

Given succesful compilation, we can now use `reccmp` to inspect any differences with the original.  Note that we specify which function to give verbose output for (an assembly diff) by address:
```bash
reccmp/dll/run reccmp-reccmp --target STRONGHOLDCRUSADER --verbose 0x004CB060
```

Output:
```diff=

---
+++
@@ -,0 +0x1002e4d0,1 @@
           : +ret 4     (setFoodBuyPlan.cpp:6)


OpenSHC::AI::AICState::setFoodBuyPlan is only 0.00% similar to the original, diff above
```

Note that `reccmp` processes our function until it finds the last `return` statement (`ret` in assembly). Since our reimplementation begins with `ret`, we don't get useful output. We need to find the assembly through other means.

I use Ghidra, which given the current state of the database gives:

```cpp=
void __thiscall OpenSHC::AI::AICState::setFoodBuyPlan(AICState *this, int playerID)

{
  int iVar1;
  int iVar2;
  
  iVar1 = DAT_GameState.playerDataArray[playerID].aiType;
  if (iVar1 != 0) {
    iVar2 = (iVar1 + -1) * 0x2a4;
    iVar1 = *(int *)((int)&DAT_AICState + iVar2 + 0x84);
    if ((-1 < iVar1) && (DAT_GameState.playerDataArray[playerID].currentResources[0xd] < iVar1)) {
      DAT_GameState.playerDataArray[playerID].resourcesToAcquireArray[0xd] =
           *(int *)((int)&DAT_AICState + iVar2 + 0x98);
    }
    iVar1 = *(int *)((int)&DAT_AICState + iVar2 + 0x88);
    if ((0 < iVar1) && (DAT_GameState.playerDataArray[playerID].currentResources[0xb] < iVar1)) {
      DAT_GameState.playerDataArray[playerID].resourcesToAcquireArray[0xb] =
           *(int *)((int)&DAT_AICState + iVar2 + 0x98);
    }
    iVar1 = *(int *)((int)&DAT_AICState + iVar2 + 0x8c);
    if ((0 < iVar1) && (DAT_GameState.playerDataArray[playerID].currentResources[10] < iVar1)) {
      DAT_GameState.playerDataArray[playerID].resourcesToAcquireArray[10] =
           *(int *)((int)&DAT_AICState + iVar2 + 0x98);
    }
    iVar1 = *(int *)((int)&DAT_AICState + iVar2 + 0x90);
    if ((0 < iVar1) && (DAT_GameState.playerDataArray[playerID].currentResources[9] < iVar1)) {
      DAT_GameState.playerDataArray[playerID].resourcesToAcquireArray[9] =
           *(int *)((int)&DAT_AICState + iVar2 + 0x98);
    }
    iVar1 = *(int *)((int)&DAT_AICState + iVar2 + 0x94);
    if ((0 < iVar1) && (DAT_GameState.playerDataArray[playerID].currentResources[3] < iVar1)) {
      DAT_GameState.playerDataArray[playerID].resourcesToAcquireArray[3] =
           *(int *)((int)&DAT_AICState + iVar2 + 0x98);
    }
  }
  return;
}
```

We could try to compile this directly, which would be a good starting point. Because I will use AI later on, I want to give the AI as much context as I can. Therefore, let's clean up the raw output from Ghidra by renaming the local variables.

### Step 3: understanding and tidying the basic reimplementation

```cpp=
void __thiscall OpenSHC::AI::AICState::setFoodBuyPlan(AICState *this, int playerID)

{
  int _offset;
  int _aiType;
  int _preferredStock;
  
  _aiType = DAT_GameState.playerDataArray[playerID].aiType;
  if (_aiType != 0) {
    _offset = (_aiType + -1) * 0x2a4;
    _preferredStock = *(int *)((int)&DAT_AICState + _offset + 0x84);
    if ((-1 < _preferredStock) &&
       (DAT_GameState.playerDataArray[playerID].currentResources[0xd] < _preferredStock)) {
      DAT_GameState.playerDataArray[playerID].resourcesToAcquireArray[0xd] =
           *(int *)((int)&DAT_AICState + _offset + 0x98);
    }
    _preferredStock = *(int *)((int)&DAT_AICState + _offset + 0x88);
    if ((0 < _preferredStock) &&
       (DAT_GameState.playerDataArray[playerID].currentResources[0xb] < _preferredStock)) {
      DAT_GameState.playerDataArray[playerID].resourcesToAcquireArray[0xb] =
           *(int *)((int)&DAT_AICState + _offset + 0x98);
    }
    _preferredStock = *(int *)((int)&DAT_AICState + _offset + 0x8c);
    if ((0 < _preferredStock) &&
       (DAT_GameState.playerDataArray[playerID].currentResources[10] < _preferredStock)) {
      DAT_GameState.playerDataArray[playerID].resourcesToAcquireArray[10] =
           *(int *)((int)&DAT_AICState + _offset + 0x98);
    }
    _preferredStock = *(int *)((int)&DAT_AICState + _offset + 0x90);
    if ((0 < _preferredStock) &&
       (DAT_GameState.playerDataArray[playerID].currentResources[9] < _preferredStock)) {
      DAT_GameState.playerDataArray[playerID].resourcesToAcquireArray[9] =
           *(int *)((int)&DAT_AICState + _offset + 0x98);
    }
    _preferredStock = *(int *)((int)&DAT_AICState + _offset + 0x94);
    if ((0 < _preferredStock) &&
       (DAT_GameState.playerDataArray[playerID].currentResources[3] < _preferredStock)) {
      DAT_GameState.playerDataArray[playerID].resourcesToAcquireArray[3] =
           *(int *)((int)&DAT_AICState + _offset + 0x98);
    }
  }
  return;
}
```

Line 10-15 look quite ugly, they use binary offsets instead of accessing fields. Probably the compiler optimized memory access. Luckily, Ghidra is of help here by giving hints about which memory is accessed, but let's do some calculation the manual way for sake of explanation.

#### Finding fields

Assuming `_aiType` is 1, which is a valid ai type (the Rat), then `_offset` is 0. Then `_preferredStock` simplifies to `&DAT_AICState + 0x84` which gives us the field `DAT_AICState.minimumApples`. This last step can be figured out like so:
1. Look for `DAT_AICState` in the project. Or visit `src/OpenSHC/Globals` and find `DAT_AICState.hpp`:
```cpp=
#pragma once

#include "OpenSHC/AI/AICState.hpp"
namespace OpenSHC {

using OpenSHC::AI::AICState;

MACRO_STRUCT_RESOLVER(AICState, false, Address::SHC_3BB0A8C1_0x023FC8E8) DAT_AICState;
} // namespace OpenSHC
```
We see that `DAT_AICState` is of type `AICState`, which is defined in `OpenSHC/AI/AICState.hpp` as can we be seen from the `#include` statement (in this case this is actually the same class for which we are reimplementing a member function).

2. Looking at the struct part of the class declaration, we can see some helpful annotations to trace offset `+ 0x84`.
```cpp=
// SIZE: 0x00006D90
class AICState {
public:
    AICSpecification DAT_AICArray[20]; // 0x00000000 length: 13520
    undefined4 aiBorderTilesIndex; // 0x000034D0 length: 4
    TileDistancePair aiBorderTiles[1000]; // 0x000034D4 length: 8000
    byte unused01[512]; // 0x00005414 length: 512
    short tribeIDArray[1000]; // 0x00005614 length: 2000
    int tribeUIDArray[1000]; // 0x00005DE4 length: 4000
    undefined4 DAT_SomeTime; // 0x00006D84 length: 4
    byte unused02[8]; // 0x00006D88 length: 8
```
Note that `+ 0x84` is smaller than the first field's offset which is  `DAT_AICArray[20]` with offsets `0`. We have to look into `AICSpecification` in which we find `minimumApples` at offset `0x84`.

```cpp=
// SIZE: 0x000002A4
typedef struct AICSpecification {

    dword flagType; // 0x00000000 length: 4
    dword unknown001; // 0x00000004 length: 4
    dword unknown002; // 0x00000008 length: 4
    ... // ommitted for tutorial brevity
    dword minimumApples; // 0x00000084 length: 4
    dword minimumCheese; // 0x00000088 length: 4
    dword minimumBread; // 0x0000008C length: 4
    dword minimumWheat; // 0x00000090 length: 4
    dword minimumHop; // 0x00000094 length: 4
    dword tradeAmountFood; // 0x00000098 length: 4
```

So the code in the function is accessing minimum apples.

3. Let's rewrite our reimplementation (line 2 below, note `_offset` becomes useless):
```cpp=
_offset = (_aiType + -1) * 0x2a4;
_preferredStock = *(int*)((int)&DAT_AICState.DAT_AICArray[_aiType - 1].minimumApples);
if ((-1 < _preferredStock)
    && (DAT_GameState.playerDataArray[playerID].currentResources[0xd] < _preferredStock)) {
    DAT_GameState.playerDataArray[playerID].resourcesToAcquireArray[0xd]
        = *(int*)((int)&DAT_AICState + _offset + 0x98);
}
```


#### Substituting enum values
At line 4 we see the usage of `0xd`, which we can guess is the resource type for apples. Let's check in `src/OpenSHC/Game/Resources/ResourceType.hpp` to see if apples is associated with integer 0xd. Yes, see line 15:
```cpp=
typedef enum ResourceType {

    RT_LOGS = 1, // 0x00000001
    RT_WOOD = 2, // 0x00000002
    RT_HOPS = 3, // 0x00000003
    RT_STONE = 4, // 0x00000004
    RT_PARTIALSTONE = 5, // 0x00000005
    RT_IRON = 6, // 0x00000006
    RT_PITCH = 7, // 0x00000007
    RT_PARTIALPITCH = 8, // 0x00000008
    RT_WHEAT = 9, // 0x00000009
    RT_BREAD = 10, // 0x0000000A
    RT_CHEESE = 11, // 0x0000000B
    RT_MEAT = 12, // 0x0000000C
    RT_APPLE = 13, // 0x0000000D
```

Furthermore, we can trace offset `+0x98 in line 6` to `tradeAmountFood`. Cleaning up our reimplementation (include ResourceType.hpp!):

```cpp=
#include "OpenSHC/AI/AICState.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"

namespace OpenSHC {
namespace AI {

    using OpenSHC::Game::Resources::ResourceType;

    // FUNCTION: STRONGHOLDCRUSADER 0x004CB060
    void AICState::setFoodBuyPlan(int playerID)
    {
        int _offset;
        int _aiType;
        int _preferredStock;

        _aiType = DAT_GameState.playerDataArray[playerID].aiType;
        if (_aiType != 0) {
            _offset = (_aiType + -1) * 0x2a4;
            _preferredStock = *(int*)((int)&DAT_AICState.DAT_AICArray[_aiType - 1].minimumApples);
            if ((-1 < _preferredStock)
                && (DAT_GameState.playerDataArray[playerID].currentResources[RT_APPLE] < _preferredStock)) {
                DAT_GameState.playerDataArray[playerID].resourcesToAcquireArray[RT_APPLE]
                    = *(int*)((int)&DAT_AICState.DAT_AICArray[_aiType - 1].tradeAmountFood);
            }
```

### Step 4: Correct references to global variables

Before we recompile, we need to change how globals are referred to. OpenSHC refers to the global memory in the exe, so we use pointer access for structs `->` instead of `.`. Also, we need to explicitly mention we want the pointer with `::ptr`:
```cpp=
#include "OpenSHC/AI/AICState.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"

namespace OpenSHC {
namespace AI {

    using OpenSHC::Game::Resources::ResourceType;

    // FUNCTION: STRONGHOLDCRUSADER 0x004CB060
    void AICState::setFoodBuyPlan(int playerID)
    {
        int _offset;
        int _aiType;
        int _preferredStock;

        _aiType = DAT_GameState::ptr->playerDataArray[playerID].aiType;
        if (_aiType != 0) {
            _offset = (_aiType + -1) * 0x2a4;
            _preferredStock = DAT_AICState::ptr->DAT_AICArray[_aiType - 1].minimumApples;
            if ((-1 < _preferredStock)
                && (DAT_GameState::ptr->playerDataArray[playerID].currentResources[RT_APPLE] < _preferredStock)) {
                DAT_GameState::ptr->playerDataArray[playerID].resourcesToAcquireArray[RT_APPLE]
                    = DAT_AICState::ptr->DAT_AICArray[_aiType - 1].tradeAmountFood;
            }
```

Also note we use DAT_GameState, so make sure to include that too:
```cpp=
#include "OpenSHC/Globals/DAT_GameState.hpp"
```

### Step 5: compiling the reimplementation and comparing it to the original

Patching everything up, we get something that looks like good code and that actually compiles with `.\build.bat RelWithDebInfo OpenSHC.dll`: 
```cpp=
#include "OpenSHC/AI/AICState.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"
#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace AI {

    using OpenSHC::Game::Resources::ResourceType;

    // FUNCTION: STRONGHOLDCRUSADER 0x004CB060
    void AICState::setFoodBuyPlan(int playerID)
    {
        // int _offset;
        int _aiType;
        int _preferredStock;

        _aiType = DAT_GameState::ptr->playerDataArray[playerID].aiType;
        if (_aiType != 0) {
            // _offset = (_aiType + -1) * 0x2a4;
            _preferredStock = DAT_AICState::ptr->DAT_AICArray[_aiType - 1].minimumApples;
            if ((-1 < _preferredStock)
                && (DAT_GameState::ptr->playerDataArray[playerID].currentResources[ResourceType::RT_APPLE]
                    < _preferredStock)) {
                DAT_GameState::ptr->playerDataArray[playerID].resourcesToAcquireArray[ResourceType::RT_APPLE]
                    = DAT_AICState::ptr->DAT_AICArray[_aiType - 1].tradeAmountFood;
            }
            _preferredStock = DAT_AICState::ptr->DAT_AICArray[_aiType - 1].minimumCheese;
            if ((0 < _preferredStock)
                && (DAT_GameState::ptr->playerDataArray[playerID].currentResources[ResourceType::RT_CHEESE]
                    < _preferredStock)) {
                DAT_GameState::ptr->playerDataArray[playerID].resourcesToAcquireArray[ResourceType::RT_CHEESE]
                    = DAT_AICState::ptr->DAT_AICArray[_aiType - 1].tradeAmountFood;
            }
            _preferredStock = DAT_AICState::ptr->DAT_AICArray[_aiType - 1].minimumBread;
            if ((0 < _preferredStock)
                && (DAT_GameState::ptr->playerDataArray[playerID].currentResources[ResourceType::RT_BREAD]
                    < _preferredStock)) {
                DAT_GameState::ptr->playerDataArray[playerID].resourcesToAcquireArray[ResourceType::RT_BREAD]
                    = DAT_AICState::ptr->DAT_AICArray[_aiType - 1].tradeAmountFood;
            }
            _preferredStock = DAT_AICState::ptr->DAT_AICArray[_aiType - 1].minimumWheat;
            if ((0 < _preferredStock)
                && (DAT_GameState::ptr->playerDataArray[playerID].currentResources[ResourceType::RT_WHEAT]
                    < _preferredStock)) {
                DAT_GameState::ptr->playerDataArray[playerID].resourcesToAcquireArray[ResourceType::RT_WHEAT]
                    = DAT_AICState::ptr->DAT_AICArray[_aiType - 1].tradeAmountFood;
            }
            _preferredStock = DAT_AICState::ptr->DAT_AICArray[_aiType - 1].minimumHop;
            if ((0 < _preferredStock)
                && (DAT_GameState::ptr->playerDataArray[playerID].currentResources[ResourceType::RT_HOPS]
                    < _preferredStock)) {
                DAT_GameState::ptr->playerDataArray[playerID].resourcesToAcquireArray[ResourceType::RT_HOPS]
                    = DAT_AICState::ptr->DAT_AICArray[_aiType - 1].tradeAmountFood;
            }
        }
        return;
    };
}
}

```


Here is our first `reccmp`:

```bash
reccmp/dll/run reccmp-reccmp --target STRONGHOLDCRUSADER --verbose 0x004CB060
```

Output:
```diff=

---
+++
@@ -0x4cb060,42 +0x1002e4d0,42 @@
0x4cb060 : -mov edx, dword ptr [esp + 4]
0x4cb064 : -imul edx, edx, 0x39f4
0x4cb06a : -mov eax, dword ptr [edx + 0x115e0f8]
           : +mov ecx, dword ptr [esp + 4]      (setFoodBuyPlan.cpp:18)
           : +imul ecx, ecx, 0x39f4
           : +mov eax, dword ptr [ecx + 0x115e0f8]
0x4cb070 : test eax, eax        (setFoodBuyPlan.cpp:19)
0x4cb072 : -je 0xa1
0x4cb078 : -add eax, -1
           : +je 0x9d
0x4cb07b : imul eax, eax, 0x2a4         (setFoodBuyPlan.cpp:21)
0x4cb081 : -add eax, ecx
0x4cb083 : -mov ecx, dword ptr [eax + 0x84]
0x4cb089 : -test ecx, ecx
0x4cb08b : -jl 0x14
0x4cb08d : -cmp dword ptr [edx + 0x115c2fc], ecx
           : +mov edx, dword ptr [eax + 0x23fc6c8]
           : +cmp edx, -1       (setFoodBuyPlan.cpp:24)
           : +jle 0x14
           : +cmp dword ptr [ecx + 0x115c2fc], edx
0x4cb093 : jge 0xc
0x4cb095 : -mov ecx, dword ptr [eax + 0x98]
0x4cb09b : -mov dword ptr [edx + 0x115e89c], ecx
0x4cb0a1 : -mov ecx, dword ptr [eax + 0x88]
0x4cb0a7 : -test ecx, ecx
           : +mov edx, dword ptr [eax + 0x23fc6dc]      (setFoodBuyPlan.cpp:26)
           : +mov dword ptr [ecx + 0x115e89c], edx
           : +mov edx, dword ptr [eax + 0x23fc6cc]      (setFoodBuyPlan.cpp:28)
           : +test edx, edx     (setFoodBuyPlan.cpp:31)
0x4cb0a9 : jle 0x14
0x4cb0ab : -cmp dword ptr [edx + 0x115c2f4], ecx
           : +cmp dword ptr [ecx + 0x115c2f4], edx
0x4cb0b1 : jge 0xc
0x4cb0b3 : -mov ecx, dword ptr [eax + 0x98]
0x4cb0b9 : -mov dword ptr [edx + 0x115e894], ecx
0x4cb0bf : -mov ecx, dword ptr [eax + 0x8c]
0x4cb0c5 : -test ecx, ecx
           : +mov edx, dword ptr [eax + 0x23fc6dc]      (setFoodBuyPlan.cpp:33)
           : +mov dword ptr [ecx + 0x115e894], edx
           : +mov edx, dword ptr [eax + 0x23fc6d0]      (setFoodBuyPlan.cpp:35)
           : +test edx, edx     (setFoodBuyPlan.cpp:38)
0x4cb0c7 : jle 0x14
0x4cb0c9 : -cmp dword ptr [edx + 0x115c2f0], ecx
           : +cmp dword ptr [ecx + 0x115c2f0], edx
0x4cb0cf : jge 0xc
0x4cb0d1 : -mov ecx, dword ptr [eax + 0x98]
0x4cb0d7 : -mov dword ptr [edx + 0x115e890], ecx
0x4cb0dd : -mov ecx, dword ptr [eax + 0x90]
0x4cb0e3 : -test ecx, ecx
           : +mov edx, dword ptr [eax + 0x23fc6dc]      (setFoodBuyPlan.cpp:40)
           : +mov dword ptr [ecx + 0x115e890], edx
           : +mov edx, dword ptr [eax + 0x23fc6d4]      (setFoodBuyPlan.cpp:42)
           : +test edx, edx     (setFoodBuyPlan.cpp:45)
0x4cb0e5 : jle 0x14
0x4cb0e7 : -cmp dword ptr [edx + 0x115c2ec], ecx
           : +cmp dword ptr [ecx + 0x115c2ec], edx
0x4cb0ed : jge 0xc
0x4cb0ef : -mov ecx, dword ptr [eax + 0x98]
0x4cb0f5 : -mov dword ptr [edx + 0x115e88c], ecx
0x4cb0fb : -mov ecx, dword ptr [eax + 0x94]
0x4cb101 : -test ecx, ecx
           : +mov edx, dword ptr [eax + 0x23fc6dc]      (setFoodBuyPlan.cpp:47)
           : +mov dword ptr [ecx + 0x115e88c], edx
           : +mov edx, dword ptr [eax + 0x23fc6d8]      (setFoodBuyPlan.cpp:49)
           : +test edx, edx     (setFoodBuyPlan.cpp:52)
0x4cb103 : jle 0x14
0x4cb105 : -cmp dword ptr [edx + 0x115c2d4], ecx
           : +cmp dword ptr [ecx + 0x115c2d4], edx
0x4cb10b : jge 0xc
0x4cb10d : -mov eax, dword ptr [eax + 0x98]
           : +mov eax, dword ptr [eax + 0x23fc6dc]      (setFoodBuyPlan.cpp:54)
           : +mov dword ptr [ecx + 0x115e874], eax
           : +ret 4     (setFoodBuyPlan.cpp:58)


OpenSHC::AI::AICState::setFoodBuyPlan is only 26.19% similar to the original, diff above
```

Oof, only 26%! Now this is a great moment to start using AI to get better results.

### Step 6: improving the reimplementation

Let's try manual improvements first:
Line 13 suggests `_aiType - 1` is cached in a register. Let's do that and insert that line after the `if (_aiType != 0)` check.
```cpp=
int _aiType0 = _aiType - 1;
```

Great, 27% and we fixed this line specifically.

#### Global access versus `this` pointer
Note however dat we used `DAT_AICState` even though we could have used `this` as we are implementing a member function for `AICState` class.

That change to our code (`DAT_AICState::ptr->` to `this->`) actually made the match worse: 22%! but it is much more likely the developers used `this` from a programmer's mindset point of view.

#### Checking for functional reimplementation versus exact reimplementation

Also note that the difference is in registry usage not really in terms of functionality, e.g. our code uses edx instead of eax and the other way around. Perhaps we can try reordering statements such that the right variable goes in the right register.

### Step 7: Use AI to improve the quality

At this point, I used Claude with the MCP tools provided in the OpenSHC repo to iteratively improve (see [this]() tutorial on how to set that up).

AI prompt:
> Using the available MCP tools, improve function `OpenSHC::AI::AICState::setFoodBuyPlan`

After two iterations, it found a 100% matching solution and it documented our source code by itself:

```cpp=
#include "OpenSHC/AI/AICState.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"
#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace AI {

    using OpenSHC::Game::Resources::ResourceType;

    // FUNCTION: STRONGHOLDCRUSADER 0x004CB060
    void AICState::setFoodBuyPlan(int playerID)
    {
        int aiType;
        int aiConfigIndex;
        int minimumStock;

        aiType = DAT_GameState::ptr->playerDataArray[playerID].aiType;

        // Early return if not an AI player (human player has aiType == 0)
        if (aiType == 0) {
            return;
        }

        // Get AI configuration index (convert 1-based to 0-based index)
        aiConfigIndex = aiType - 1;

        // Check each food type and queue purchase if current stock is below minimum

        // Apples: special handling with >= 0 check (allows -1 to disable)
        minimumStock = this->DAT_AICArray[aiConfigIndex].minimumApples;
        if (minimumStock >= 0
            && DAT_GameState::ptr->playerDataArray[playerID].currentResources[ResourceType::RT_APPLE] < minimumStock) {
            DAT_GameState::ptr->playerDataArray[playerID].resourcesToAcquireArray[ResourceType::RT_APPLE]
                = this->DAT_AICArray[aiConfigIndex].tradeAmountFood;
        }

        // Cheese: standard check with > 0
        minimumStock = this->DAT_AICArray[aiConfigIndex].minimumCheese;
        if (minimumStock > 0
            && DAT_GameState::ptr->playerDataArray[playerID].currentResources[ResourceType::RT_CHEESE] < minimumStock) {
            DAT_GameState::ptr->playerDataArray[playerID].resourcesToAcquireArray[ResourceType::RT_CHEESE]
                = this->DAT_AICArray[aiConfigIndex].tradeAmountFood;
        }

        // Bread: standard check with > 0
        minimumStock = this->DAT_AICArray[aiConfigIndex].minimumBread;
        if (minimumStock > 0
            && DAT_GameState::ptr->playerDataArray[playerID].currentResources[ResourceType::RT_BREAD] < minimumStock) {
            DAT_GameState::ptr->playerDataArray[playerID].resourcesToAcquireArray[ResourceType::RT_BREAD]
                = this->DAT_AICArray[aiConfigIndex].tradeAmountFood;
        }

        // Wheat: standard check with > 0
        minimumStock = this->DAT_AICArray[aiConfigIndex].minimumWheat;
        if (minimumStock > 0
            && DAT_GameState::ptr->playerDataArray[playerID].currentResources[ResourceType::RT_WHEAT] < minimumStock) {
            DAT_GameState::ptr->playerDataArray[playerID].resourcesToAcquireArray[ResourceType::RT_WHEAT]
                = this->DAT_AICArray[aiConfigIndex].tradeAmountFood;
        }

        // Hops: standard check with > 0
        minimumStock = this->DAT_AICArray[aiConfigIndex].minimumHop;
        if (minimumStock > 0
            && DAT_GameState::ptr->playerDataArray[playerID].currentResources[ResourceType::RT_HOPS] < minimumStock) {
            DAT_GameState::ptr->playerDataArray[playerID].resourcesToAcquireArray[ResourceType::RT_HOPS]
                = this->DAT_AICArray[aiConfigIndex].tradeAmountFood;
        }
    }
}
}

```

```bash
OpenSHC> reccmp/dll/run reccmp-reccmp --target STRONGHOLDCRUSADER --verbose 0x004CB060

...

0x4cb060: OpenSHC::AI::AICState::setFoodBuyPlan 100% match.

✨ OK! ✨
```

#### Improving code style
While the code is 100% matching, it can be improved in terms of style. Let's apply some code style changes that don't affect matching (always check!).

```cpp=
#include "OpenSHC/AI/AICState.hpp"
#include "OpenSHC/AI/AITypeA.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"
#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace AI {

    using OpenSHC::AI::AITypeA;
    using OpenSHC::Game::Resources::ResourceType;

    // FUNCTION: STRONGHOLDCRUSADER 0x004CB060
    void AICState::setFoodBuyPlan(int playerID)
    {

        int aiType = DAT_GameState::ptr->playerDataArray[playerID].aiType;

        // Early return if not an AI player (human player has aiType == 0)
        if (aiType == AITypeA::AITA_NULL) {
            return;
        }

        // Get AI configuration index (convert 1-based to 0-based index)
        int aiConfigIndex = aiType - 1;

        // Check each food type and queue purchase if current stock is below minimum

        // Apples: special handling with >= 0 check (allows -1 to disable)
        int minimumApples = this->DAT_AICArray[aiConfigIndex].minimumApples;
        int* currentResources = DAT_GameState::ptr->playerDataArray[playerID].currentResources;
        if (minimumApples >= 0 && currentResources[ResourceType::RT_APPLE] < minimumApples) {
            DAT_GameState::ptr->playerDataArray[playerID].resourcesToAcquireArray[ResourceType::RT_APPLE]
                = this->DAT_AICArray[aiConfigIndex].tradeAmountFood;
        }

        // Cheese: standard check with > 0
        int minimumCheese = this->DAT_AICArray[aiConfigIndex].minimumCheese;
        if (minimumCheese > 0 && currentResources[ResourceType::RT_CHEESE] < minimumCheese) {
            DAT_GameState::ptr->playerDataArray[playerID].resourcesToAcquireArray[ResourceType::RT_CHEESE]
                = this->DAT_AICArray[aiConfigIndex].tradeAmountFood;
        }

        // Bread: standard check with > 0
        int minimumBread = this->DAT_AICArray[aiConfigIndex].minimumBread;
        if (minimumBread > 0 && currentResources[ResourceType::RT_BREAD] < minimumBread) {
            DAT_GameState::ptr->playerDataArray[playerID].resourcesToAcquireArray[ResourceType::RT_BREAD]
                = this->DAT_AICArray[aiConfigIndex].tradeAmountFood;
        }

        // Wheat: standard check with > 0
        int minimumWheat = this->DAT_AICArray[aiConfigIndex].minimumWheat;
        if (minimumWheat > 0 && currentResources[ResourceType::RT_WHEAT] < minimumWheat) {
            DAT_GameState::ptr->playerDataArray[playerID].resourcesToAcquireArray[ResourceType::RT_WHEAT]
                = this->DAT_AICArray[aiConfigIndex].tradeAmountFood;
        }

        // Hops: standard check with > 0
        int minimumHop = this->DAT_AICArray[aiConfigIndex].minimumHop;
        if (minimumHop > 0 && currentResources[ResourceType::RT_HOPS] < minimumHop) {
            DAT_GameState::ptr->playerDataArray[playerID].resourcesToAcquireArray[ResourceType::RT_HOPS]
                = this->DAT_AICArray[aiConfigIndex].tradeAmountFood;
        }
    }
}
}

```

### Step 8: Documentation and bug hunting
Note that this 100% reimplementation also revealed a bug or quirk (or feature?): minimumApples permits 0 as a valid value for minimum stock, which doesn't make sense as can be seen one line later as `currentResources` being smaller than 0 doesn't make any sense (unless the AI cheats with negative stock values?).

It is best practice to note down such oddities in code comments.

### Step 9: Preparing a Pull Request
For every reimplemented function, the associated function resolver should have its reimplementation state set to `true`. So, in file `OpenSHC/AI/AICState.func.hpp` we change line 2 below from `, false,` to `true, `. This detours all calls to `setFoodBuyPlan` through our DLL instead of through the original binary. Furthermore, functions calling `setFoodBuyPlan` have their percentages improved as the call points to a reimplementation.

```cpp=
MACRO_FUNCTION_RESOLVER(
    void (AICState::*)(int), false, Address::SHC_3BB0A8C1_0x004CB060, &AICState::setFoodBuyPlan)
setFoodBuyPlan;
```

Furthermore, in the file `status/addresses-SHC-3BB0A8C1.txt`, we set entry `SHC_3BB0A8C1_0x004CB060`  to `100%` and change `Pending` into `Completed`. If we didn't achieve 100% in Step 7, we note here what prevented full reimplementation. For example, if the reimplementation appears to be functionally identical but optimizations that are only applied to exe files hinder 100%, write: `Functional reimplementation: compiler optimization prevented identical reimplementation`.

### Step 10: open the Pull Request
The Pull Request should contain the changes to the .cpp file, the .func.hpp file. The body of your Pull Request should contain the status of the reimplementation and the output of `reccmp` if not 100%.


### Conclusion
Happy reimplementing!