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
            int _counter = 0;
            int _canBeUsed = this->climbData[climbDataID].canBeUsed;
            this->climbData[climbDataID].numberOfUnitsUsing = 0;
            if (_canBeUsed != 0) {
                do {
                    int* _ptrUnitID = &this->climbData[climbDataID].unitID1 + _counter;
                    int _unitID = *_ptrUnitID;
                    if (_unitID != 0) {
                        int* _ptrUnitUID = &this->climbData[climbDataID].unitUID1 + _counter;
                        int _unitUID = *_ptrUnitUID;
                        if (DAT_UnitsState::instance.units[_unitID].logicalState != OpenSHC::Map::Units::ULS_NORMAL) {
                            *_ptrUnitID = 0;
                            *_ptrUnitUID = 0;
                        } else if (DAT_UnitsState::instance.units[_unitID].uid != _unitUID) {
                            *_ptrUnitID = 0;
                            *_ptrUnitUID = 0;
                        } else if (DAT_UnitsState::instance.units[_unitID].climbDataID != climbDataID) {
                            *_ptrUnitID = 0;
                            *_ptrUnitUID = 0;
                        } else {
                            this->climbData[climbDataID].numberOfUnitsUsing
                                = this->climbData[climbDataID].numberOfUnitsUsing + 1;
                        }
                    }
                    _counter = _counter + 1;
                } while (_counter < 50);
            }
        }

    }
}
}
