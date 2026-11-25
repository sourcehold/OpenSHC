#include "../TroopValueState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map.func.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x005198C0
        void TroopValueState::recomputeTargetedBuildingTilesArray(int playerID)
        {
            DAT_TroopValueState::instance.attackInfo.targetedBuildingTilesArraySize = 0;
            MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                sizeof(DAT_TroopValueState::instance.attackInfo.targetedBuildingTilesArray), 0,
                DAT_TroopValueState::instance.attackInfo.targetedBuildingTilesArray);
            uint const maxUnitCount = DAT_UnitsState::instance.maxUnitCount;
            int unitID = 1;
            // the guard compares unsigned, the loop condition signed
            if (1 < DAT_UnitsState::instance.maxUnitCount) {
                int arraySize = DAT_TroopValueState::instance.attackInfo.targetedBuildingTilesArraySize;
                do {
                    if (DAT_UnitsState::instance.units[unitID].logicalState == Map::Units::ULS_NORMAL
                        && DAT_UnitsState::instance.units[unitID].isSelectable_OR_matchTime
                        && DAT_UnitsState::instance.units[unitID].owner == playerID
                        && DAT_UnitsState::instance.units[unitID].targetedBuildingTile
                        && DAT_UnitsState::instance.units[unitID].unitType != Map::Units::UT_A_SLAVE) {
                        DAT_TroopValueState::instance.attackInfo.targetedBuildingTilesArray[arraySize]
                            = DAT_UnitsState::instance.units[unitID].targetedBuildingTile;
                        arraySize = DAT_TroopValueState::instance.attackInfo.targetedBuildingTilesArraySize + 1;
                        DAT_TroopValueState::instance.attackInfo.targetedBuildingTilesArraySize = arraySize;
                        if (countof(DAT_TroopValueState::instance.attackInfo.targetedBuildingTilesArray) <= arraySize) {
                            break;
                        }
                    }
                    ++unitID;
                } while (unitID < (int)maxUnitCount);
            }
        }

    }
}
}
