#include "../PathFindingState.func.hpp"

#include "OpenSHC/Map/Units/UnitLogicState.hpp"

#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        using OpenSHC::Map::Units::UnitLogicState;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004A4BB0
        void PathFindingState::recountUnitsUsingClimbData(int climbDataID)
        {
            int* _ptrUnitID;
            int _counter;
            int _canBeUsed;
            int* _ptrUnitUID;
            int _unitID;
            _counter = 0;
            _canBeUsed = this->climbData[climbDataID].canBeUsed;
            this->climbData[climbDataID].numberOfUnitsUsing = 0;
            if (_canBeUsed != 0) {
                _ptrUnitID = &this->climbData[climbDataID].unitID1;
                do {
                    _unitID = *_ptrUnitID;
                    if (_unitID != 0) {
                        _ptrUnitUID = &this->climbData[climbDataID].unitUID1 + _counter;
                        if (DAT_UnitsState::instance.units[_unitID].logicalState == OpenSHC::Map::Units::ULS_NORMAL) {
                            if (DAT_UnitsState::instance.units[_unitID].uid
                                == (&this->climbData[climbDataID].unitUID1)[_counter]) {
                                if (DAT_UnitsState::instance.units[_unitID].climbDataID == climbDataID) {
                                    _ptrUnitUID = &this->climbData[climbDataID].numberOfUnitsUsing;
                                    *_ptrUnitUID = *_ptrUnitUID + 1;
                                } else {
                                    *_ptrUnitID = 0;
                                    *_ptrUnitUID = 0;
                                }
                            } else {
                                *_ptrUnitID = 0;
                                *_ptrUnitUID = 0;
                            }
                        } else {
                            *_ptrUnitID = 0;
                            *_ptrUnitUID = 0;
                        }
                    }
                    _counter = _counter + 1;
                    _ptrUnitID = _ptrUnitID + 1;
                } while (_counter < 50);
            }
            return;
        }

    }
}
}
