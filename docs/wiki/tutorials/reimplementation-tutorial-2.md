# Tutorials

## Reimplementation Tutorial 2
This tutorial assumes you have followed tutorial 1.

### Step 1: rough reimplementation
In this tutorial, we reimplement `OpenSHC::AI::AIVState::setupAIVMetadata`. I have taken a decompilation from Ghidra and polished it with what we learned from Tutorial 1.

```cpp=
#include "OpenSHC/AI/AIVState.hpp"
#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace AI {
    
    // FUNCTION: STRONGHOLDCRUSADER 0x004ECEF0
    int AIVState::setupAIVMetadata(int playerID)

    {
        AIV* pAVar1;
        int _buildIntervalUnk;
        int _aivID;
        int _aiType;

        _aivID = 1;
        pAVar1 = this->SEC_AIVS;
        do {
            pAVar1 = pAVar1 + 1;
            if (pAVar1->playerID == 0) {
                this->SEC_AIVS[_aivID].playerID = playerID;
                _aiType = DAT_GameState::ptr->playerDataArray[playerID].aiType;
                this->SEC_AIVS[_aivID].currentStepGoal = 0;
                this->SEC_AIVS[_aivID].aivPoorCounter = 0;
                this->SEC_AIVS[_aivID].aivSubType = 0;
                this->SEC_AIVS[_aivID].aiType = _aiType;
                _buildIntervalUnk = AICState::getAIBuildInterval(DAT_AICState::ptr, playerID);
                this->SEC_AIVS[_aivID].aivPoorLimit_OR_AIC_buildInterval = _buildIntervalUnk;
                this->aivCount = this->aivCount + 1;
                return _aivID;
            }
            _aivID = _aivID + 1;
        } while (_aivID < 9);
        return 0;
    }

}
}

```

Note that line 26 contains a method call in Ghidra style (pseudo C++). This style is not compatible with MSVC. Furthermore, it doesn't take into account the OpenSHC approach of either calling the original function (if it hasn't been fully reimplemented yet), or calling the reimplemented function (if it has been fully reimplemented). 

#### Using the FunctionResolver to invoke member calls
We should change line 25 into:
```cpp
_buildIntervalUnk = MACRO_CALL_MEMBER(AICState_Func::getAIBuildInterval, DAT_AICState::ptr)(playerID);
```

### Step 2: comparing the reimplementation
We run the following to get a diff report:
```bash
reccmp/dll/run reccmp-reccmp --target STRONGHOLDCRUSADER --verbose 0x004ECEF0
```

```raw=

---
+++
@@ -0x4ecef0,38 +0x10030420,40 @@
0x4ecef0 : push ebx     (setupAIVMetadata.cpp:12)
0x4ecef1 : mov ebx, ecx
0x4ecef3 : push edi
0x4ecef4 : mov edi, 1   (setupAIVMetadata.cpp:18)
0x4ecef9 : -lea eax, [ebx + 0x6d9c]
0x4eceff : -xor ecx, ecx
0x4ecf01 : -cmp dword ptr [eax], ecx
0x4ecf03 : -je 0x14
           : +lea eax, [ebx + 4]        (setupAIVMetadata.cpp:19)
           : +xor edx, edx
           : +mov edi, edi
           : +add eax, 0x6d98   (setupAIVMetadata.cpp:21)
           : +cmp dword ptr [eax], edx  (setupAIVMetadata.cpp:22)
           : +je 0xf
0x4ecf05 : add edi, 1   (setupAIVMetadata.cpp:34)
0x4ecf08 : -add eax, 0x6d98
0x4ecf0d : cmp edi, 9   (setupAIVMetadata.cpp:35)
0x4ecf10 : jl -0x11
0x4ecf12 : pop edi
0x4ecf13 : xor eax, eax         (setupAIVMetadata.cpp:36)
0x4ecf15 : pop ebx
0x4ecf16 : ret 4        (setupAIVMetadata.cpp:37)
0x4ecf19 : mov eax, edi         (setupAIVMetadata.cpp:23)
0x4ecf1b : imul eax, eax, 0x6d98
0x4ecf21 : push esi
0x4ecf22 : lea esi, [eax + ebx]
0x4ecf25 : mov eax, dword ptr [esp + 0x10]
0x4ecf29 : -mov edx, eax
0x4ecf2b : -imul edx, edx, 0x39f4
           : +mov ecx, eax      (setupAIVMetadata.cpp:24)
           : +imul ecx, ecx, 0x39f4
0x4ecf31 : mov dword ptr [esi + 4], eax
0x4ecf34 : -mov edx, dword ptr [edx + 0x115e0f8]
0x4ecf3a : -mov dword ptr [esi + 0x18], ecx
0x4ecf3d : -mov dword ptr [esi + 0x1c], ecx
0x4ecf40 : -mov dword ptr [esi + 0x14], ecx
           : +mov ecx, dword ptr [ecx + 0x115e0f8]
           : +mov dword ptr [esi + 8], ecx      (setupAIVMetadata.cpp:28)
0x4ecf43 : push eax     (setupAIVMetadata.cpp:29)
0x4ecf44 : mov ecx, 0x23fc8e8
0x4ecf49 : -mov dword ptr [esi + 8], edx
0x4ecf4c : -call <OFFSET1>
           : +mov dword ptr [esi + 0x18], edx
           : +mov dword ptr [esi + 0x1c], edx
           : +mov dword ptr [esi + 0x14], edx
           : +call FunctionResolver::Resolver<int (__thiscall OpenSHC::AI::AICState::*)(int),0,5026080,&OpenSHC::AI::AICState::getAIBuildInterval,0>::GameFunction<int (__thiscall OpenSHC::AI::AICState::*)(int)>::CallHelper<int,void>::call (FUNCTION)
0x4ecf51 : mov dword ptr [esi + 0x20], eax      (setupAIVMetadata.cpp:30)
0x4ecf54 : add dword ptr [ebx + 0xb6c68], 1     (setupAIVMetadata.cpp:31)
0x4ecf5b : pop esi
0x4ecf5c : mov eax, edi         (setupAIVMetadata.cpp:32)
0x4ecf5e : pop edi
0x4ecf5f : pop ebx
           : +ret 4     (setupAIVMetadata.cpp:37)


OpenSHC::AI::AIVState::setupAIVMetadata is only 64.10% similar to the original, diff above
[OK] Virtual environment deactivated.
[SUCCESS] Command completed successfully.
```

We achieved 64%!

### Step 3: Dealing with non-reimplemented calls
Note line 50 which instead of calling an OFFSET, it calls `FunctionResolver::Resolver<int (__thiscall OpenSHC::AI::AICState::*)(int),0,5026080,&OpenSHC::AI::AICState::getAIBuildInterval,0>::GameFunction<int (__thiscall OpenSHC::AI::AICState::*)(int)>::CallHelper<int,void>::call (FUNCTION)`.

This happens when the called function hasn't been implemented yet. One solution is to temporarily stub a reimplementation for this function and set its reimplementation state to `true`. The other solution is to reimplement that function first.

For every reimplemented function to be called, the associated function resolver should have its reimplementation state set to `true`. So, for example, for function `AICState::setFoodBuyPlan` (see Tutorial 1) in file `OpenSHC/AI/AICState.func.hpp` we change line 2 below from `, false,` to `true, `. This detours all calls to `setFoodBuyPlan` through our DLL instead of through the original binary. **Furthermore, functions calling `setFoodBuyPlan` have their percentages improved as the call points to the reimplementation.**

```cpp=
MACRO_FUNCTION_RESOLVER(
    void (AICState::*)(int), false, Address::SHC_3BB0A8C1_0x004CB060, &AICState::setFoodBuyPlan)
setFoodBuyPlan;
```

### Step 4: reimplementing called functions
Let's see whether we can reimplement that function while we are at it:

```cpp=
int AICState::getAIBuildInterval(int playerID)
{
  int _aiType;
  
  _aiType = DAT_GameState.playerDataArray[playerID].aiType;
  if (_aiType == 0) {
    return _aiType; // is the same as return 0;
  }
                    /* fixme: this accesses AIC.buildInterval !? */
  return *(int *)((int)DAT_EntityState.seagullArray + _aiType * 0x2a4 + 0x24e8);
}
```

Note that because `_aiType` is non-zero, the compiler optimized the access into the array by shifting the base, essentially mapping the [1-16] range unto a [0-15] array.

We can verify this by adding `0x2a4` to the offset of seagulArray + `0x24e8`. We get the AIC `buildInterval` field of the zero entry.

Note that the raw assembly for that instruction says something entirely different, what we see in the decompilation is an artifact produced by Ghidra.


Luckily, this optimization is quite straightforward and always occurs, as this fix for the optimization achieves 100% accuracy with the original bytecode:

```cpp=
#include "OpenSHC/AI/AICState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004cb120
    int AICState::getAIBuildInterval(int playerID)

    {
        int _aiType;

        _aiType = DAT_GameState::ptr->playerDataArray[playerID].aiType;
        if (_aiType == 0) {
            return _aiType;
        }

        return this->DAT_AICArray[(_aiType - 1)].buildInterval;
    }
}
}

```


Now let's set the reimplemented status inside `AICState.func.hpp` to `true`:
```cpp=
        MACRO_FUNCTION_RESOLVER(
            int (AICState::*)(int), true, Address::SHC_3BB0A8C1_0x004CB120, &AICState::getAIBuildInterval)
        getAIBuildInterval;
```

And rerun the comparison for `setupAIVMetadata`. Note that line 48 now corresponds with the correct function instead of a `FunctionResolver` statement.

```diff=
---
+++
@@ -0x4ecef0,38 +0x1002ef40,40 @@
0x4ecef0 : push ebx     (setupAIVMetadata.cpp:12)
0x4ecef1 : mov ebx, ecx
0x4ecef3 : push edi
0x4ecef4 : mov edi, 1   (setupAIVMetadata.cpp:18)
0x4ecef9 : -lea eax, [ebx + 0x6d9c]
0x4eceff : -xor ecx, ecx
0x4ecf01 : -cmp dword ptr [eax], ecx
0x4ecf03 : -je 0x14
           : +lea eax, [ebx + 4]        (setupAIVMetadata.cpp:19)
           : +xor edx, edx
           : +mov edi, edi
           : +add eax, 0x6d98   (setupAIVMetadata.cpp:21)
           : +cmp dword ptr [eax], edx  (setupAIVMetadata.cpp:22)
           : +je 0xf
0x4ecf05 : add edi, 1   (setupAIVMetadata.cpp:34)
0x4ecf08 : -add eax, 0x6d98
0x4ecf0d : cmp edi, 9   (setupAIVMetadata.cpp:35)
0x4ecf10 : jl -0x11
0x4ecf12 : pop edi
0x4ecf13 : xor eax, eax         (setupAIVMetadata.cpp:36)
0x4ecf15 : pop ebx
0x4ecf16 : ret 4        (setupAIVMetadata.cpp:37)
0x4ecf19 : mov eax, edi         (setupAIVMetadata.cpp:23)
0x4ecf1b : imul eax, eax, 0x6d98
0x4ecf21 : push esi
0x4ecf22 : lea esi, [eax + ebx]
0x4ecf25 : mov eax, dword ptr [esp + 0x10]
0x4ecf29 : -mov edx, eax
0x4ecf2b : -imul edx, edx, 0x39f4
           : +mov ecx, eax      (setupAIVMetadata.cpp:24)
           : +imul ecx, ecx, 0x39f4
0x4ecf31 : mov dword ptr [esi + 4], eax
0x4ecf34 : -mov edx, dword ptr [edx + 0x115e0f8]
0x4ecf3a : -mov dword ptr [esi + 0x18], ecx
0x4ecf3d : -mov dword ptr [esi + 0x1c], ecx
0x4ecf40 : -mov dword ptr [esi + 0x14], ecx
           : +mov ecx, dword ptr [ecx + 0x115e0f8]
           : +mov dword ptr [esi + 8], ecx      (setupAIVMetadata.cpp:28)
0x4ecf43 : push eax     (setupAIVMetadata.cpp:29)
0x4ecf44 : mov ecx, 0x23fc8e8
0x4ecf49 : -mov dword ptr [esi + 8], edx
           : +mov dword ptr [esi + 0x18], edx
           : +mov dword ptr [esi + 0x1c], edx
           : +mov dword ptr [esi + 0x14], edx
0x4ecf4c : call OpenSHC::AI::AICState::getAIBuildInterval (FUNCTION)
0x4ecf51 : mov dword ptr [esi + 0x20], eax      (setupAIVMetadata.cpp:30)
0x4ecf54 : add dword ptr [ebx + 0xb6c68], 1     (setupAIVMetadata.cpp:31)
0x4ecf5b : pop esi
0x4ecf5c : mov eax, edi         (setupAIVMetadata.cpp:32)
0x4ecf5e : pop edi
0x4ecf5f : pop ebx
           : +ret 4     (setupAIVMetadata.cpp:37)


OpenSHC::AI::AIVState::setupAIVMetadata is only 66.67% similar to the original, diff above
```


### Step 5: improving accuracy using AI

Using Claude AI, the following solution gives a special 100% match:

```cpp=
#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/AI/AIVState.hpp"
#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004ECEF0
    int AIVState::setupAIVMetadata(int playerID)
    {
        int aivID = 1;
        AIVSpec* pSlot = &this->SEC_AIVS[1];
        do {
            if (pSlot->playerID == 0) {
                this->SEC_AIVS[aivID].playerID = playerID;
                this->SEC_AIVS[aivID].aivPoorCounter = 0;

                int aiType = DAT_GameState::ptr->playerDataArray[playerID].aiType;
                this->SEC_AIVS[aivID].aiType = aiType;

                this->SEC_AIVS[aivID].aivSubType = 0;
                this->SEC_AIVS[aivID].currentStepGoal = 0;

                this->SEC_AIVS[aivID].aivPoorLimit_OR_AIC_buildInterval
                    = MACRO_CALL_MEMBER(AICState_Func::getAIBuildInterval, DAT_AICState::ptr)(playerID);

                this->aivCount = this->aivCount + 1;

                return aivID;
            }
            aivID = aivID + 1;
            pSlot = pSlot + 1;
        } while (aivID < 9);
        return 0;
    }

}
}

```

#### Effective matches
The reccmp output indicates a special form of 100% accuracy:
```raw

0x4ecef0: OpenSHC::AI::AIVState::setupAIVMetadata 100% effective match (differs, but only in ways that don't affect behavior).

✨ OK! ✨


```

#### Achieving a true 100% match
It turns out some code lines can be reordered to achieve a full 100% match. If you are a perfectionist, go ahead!

This is the right order:
```cpp=
this->SEC_AIVS[aivID].playerID = playerID;

int aiType = DAT_GameState::ptr->playerDataArray[playerID].aiType;
this->SEC_AIVS[aivID].aiType = aiType;

this->SEC_AIVS[aivID].currentStepGoal = 0;
this->SEC_AIVS[aivID].aivPoorCounter = 0;
this->SEC_AIVS[aivID].aivSubType = 0;

this->SEC_AIVS[aivID].aivPoorLimit_OR_AIC_buildInterval
    = MACRO_CALL_MEMBER(AICState_Func::getAIBuildInterval, DAT_AICState::ptr)(playerID);

this->aivCount = this->aivCount + 1;

```

### Step 6: Pull Request preparation
See Tutorial 1. Make sure to only submit the .cpp file and `status/` update for one function per PR or multiple functions that belong logically together (such as class methods of the same class).

### Note: reimplementation of library functions
Not all called functions can reimplemented, as some are windows library functions that were statically included into the binary. Note that not all library functions start with `_`.

#### Windows library functions
For example, line 20 calls the windows `_rand()` function:

```cpp=
#include "OpenSHC/Global.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Random/RNG.func.hpp"
#include "OpenSHC/Random/RNG.hpp"

namespace OpenSHC {
namespace Random {

    // FUNCTION: STRONGHOLDCRUSADER 0x0046a760
    void RNG::populateRNG1040()

    {

        MACRO_CALL(OpenSHC::Global_Func::SetRNGSeed)(this->seed);
        this->index2 = 0;
        this->index1 = 0;
        short* _pRandomNumber = &this->randomNumbers[0];
        int n = 20000;
        do {
            int random = MACRO_CALL(OpenSHC::OS_Func::_rand)();
            *_pRandomNumber = (short)random;
            _pRandomNumber += 1;
            n -= 1;
        } while (n != 0);

        this->currentNumber2 = this->randomNumbers[this->index2];
        this->index2 += 1;

        this->currentNumber1 = this->randomNumbers[this->index1];
        this->index1 += 1;

        return;
    }

}
}
```

#### Compiler-injected functions
For math operations that involve floating point numbers, functions are injected as well. See line 3 and line 6 below (`OpenSHC::IO::FilePackager::writeMapOrSaveFile`):
```cpp=
        if (local_8 != (RenderLoadAndSaveBar *)0x0) {
          _someBigNumbeKeeper =
               __allmul(_secSizeSumUnk,(int)_secSizeSumUnk >> 0x1f,1000,0);
          mapSectionAddressArray = (MapSectionAddress *)(_someBigNumbeKeeper >> 0x20);
          _someRelativeSizeValue =
               __alldiv
                         ((long)_someBigNumbeKeeper,(long)mapSectionAddressArray,_rawSize,
                          _rawSize >> 0x1f);
          (*local_8)((int)_someRelativeSizeValue);
        }
```

As this injection of functions cannot be replicated from source code, we ignore these in reimplementations and hope the compiler injects them again.

You won't see such functions listed in the `OpenSHC::OS` namespace.


### Note: ignoring Ghidra function sugar
Ghidra includes helper functions to explicate what is happening logically. One such example is the `ADJ()` function, which represents relative offsets from one field to another. Note how the ptr on line 12 is the input of `ADJ()` to get access to other fields.

Ghida functions like this are not reimplemented and can be removed/ignored.

```cpp=

int __thiscall
OpenSHC::Map::Units::UnitsState::getAliveLordForPlayer(UnitsState *this,int playerID)

{
  int _unit;
  Unit * 150 _ptrUnit;
  
  _unit = 1;
  if (1 < (int)DAT_UnitsState.maxUnitCount) {
                    /* Unit offset 150 */
    _ptrUnit = &DAT_UnitsState.units[1].owner;
    do {
      if ((((ADJ(_ptrUnit)->unitType == UT_LORD) && (ADJ(_ptrUnit)->owner == playerID)) &&
          (ADJ(_ptrUnit)->logicalState == ULS_NORMAL)) && (ADJ(_ptrUnit)->dying == 0)) {
        return _unit;
      }
      _unit = _unit + 1;
      _ptrUnit = _ptrUnit + 0x248;
    } while (_unit < (int)DAT_UnitsState.maxUnitCount);
  }
  return 0;
}

```
