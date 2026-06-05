## Tutorial 3: Dealing with Ghidra arrays, field pointers, and ADJ()

### Example 1
A lot of assembly that accesses structs is optimized by the compiler to use relative offsets. Usually one field of a struct is chosen as the reference point. For example, in this function, `owner` is chosen as the reference point as can be seen in line 11:


{lineno-start=1}
```cpp
int __thiscall
UnitsState::getAliveLordForPlayer(UnitsState *this,int playerID)

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

#### Fields and arrays
Furthermore, the line `_ptrUnit  = _ptrUnit + 0x248` is deceptive. Technically, it is incrementing `0x248`, but as `ptrUnit` is of type `int`, it is actually increment `4 * 0x248 = 0x490` (the struct size of `Unit`). 


#### Solution
Note how we changed the line referring to `owner` and instead refer to the unit instead. Then, when incrementing the pointer, we increment by `1` (1 `Unit`).
We remove `ADJ()`.


{lineno-start=1}
```cpp
#include "OpenSHC/Map/Units/UnitsState.hpp"

#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x005377f0
        int UnitsState::getAliveLordForPlayer(int playerID)

        {
            int _unit = 1;
            if (1 < (int)this->maxUnitCount) {
                /* Unit offset 150 */
                Unit* _ptrUnit = &this->units[1];
                do {
                    if ((((_ptrUnit->unitType == UT_LORD) && (_ptrUnit->owner == playerID))
                            && (_ptrUnit->logicalState == ULS_NORMAL))
                        && (_ptrUnit->dying == 0)) {
                        return _unit;
                    }
                    _unit = _unit + 1;
                    _ptrUnit = _ptrUnit + 1;
                } while (_unit < (int)this->maxUnitCount);
            }
            return 0;
        }

    }
}
}
```