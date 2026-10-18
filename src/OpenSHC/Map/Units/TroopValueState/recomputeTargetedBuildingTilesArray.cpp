#include "../../../Map.func.hpp"
#include "../TroopValueState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using Map::Units::UnitLogicState;
        using Map::Units::UnitType;

        // FUNCTION: STRONGHOLDCRUSADER 0x005198C0
        void TroopValueState::recomputeTargetedBuildingTilesArray(int playerID)
        {
            Unit* _pUnit;
            int _arraySize;
            int _unitID;
            DAT_TroopValueState::instance.attackInfo.targetedBuildingTilesArraySize = 0;
            MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                sizeof(DAT_TroopValueState::instance.attackInfo.targetedBuildingTilesArray), '\0',
                (void*)((int)(DAT_TroopValueState::instance.attackInfo.targetedBuildingTilesArray)));
            uint const _maxUnitCount = DAT_UnitsState::instance.maxUnitCount;
            _unitID = 1;
            if (1 < DAT_UnitsState::instance.maxUnitCount) {
                _pUnit = &DAT_UnitsState::instance.units[1];
                _arraySize = DAT_TroopValueState::instance.attackInfo.targetedBuildingTilesArraySize;
                do {
                    if (_pUnit->logicalState == Map::Units::ULS_NORMAL && _pUnit->isSelectable_OR_matchTime
                        && _pUnit->owner == playerID && _pUnit->targetedBuildingTile
                        && _pUnit->unitType != Map::Units::UT_A_SLAVE) {
                        DAT_TroopValueState::instance.attackInfo.targetedBuildingTilesArray[_arraySize]
                            = _pUnit->targetedBuildingTile;
                        /*
                          Units.targetBuildingTile
                         */
                        _arraySize = DAT_TroopValueState::instance.attackInfo.targetedBuildingTilesArraySize + 1;
                        DAT_TroopValueState::instance.attackInfo.targetedBuildingTilesArraySize = _arraySize;
                        if (4000 <= _arraySize) {
                            break;
                        }
                    }
                    _unitID = _unitID + 1;
                    _pUnit = _pUnit + 1;
                } while (_unitID < (int)_maxUnitCount);
            }
        }

    }
}
}
