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
            OpenSHC::Map::ClimbData* _climb;
            _counter = 0;
            _climb = &this->climbData[climbDataID];
            _canBeUsed = _climb->canBeUsed;
            _climb->numberOfUnitsUsing = 0;
            if (_canBeUsed != 0) {
                _ptrUnitID = &this->climbData[climbDataID].unitID1;
                do {
                    _unitID = *_ptrUnitID;
                    if (_unitID != 0) {
                        int _uid = (&this->climbData[climbDataID].unitUID1)[_counter];
                        _ptrUnitUID = &this->climbData[climbDataID].unitUID1 + _counter;
                        if (DAT_UnitsState::instance.units[_unitID].logicalState != OpenSHC::Map::Units::ULS_NORMAL) {
                            *_ptrUnitID = 0;
                            *_ptrUnitUID = 0;
                        } else if (DAT_UnitsState::instance.units[_unitID].uid != _uid) {
                            *_ptrUnitID = 0;
                            *_ptrUnitUID = 0;
                        } else if (DAT_UnitsState::instance.units[_unitID].climbDataID != climbDataID) {
                            *_ptrUnitID = 0;
                            *_ptrUnitUID = 0;
                        } else {
                            _climb->numberOfUnitsUsing = _climb->numberOfUnitsUsing + 1;
                        }
                    }
                    _ptrUnitID = _ptrUnitID + 1;
                    _counter = _counter + 1;
                } while (_counter < 50);
            }
            return;
        }

    }
}
}
