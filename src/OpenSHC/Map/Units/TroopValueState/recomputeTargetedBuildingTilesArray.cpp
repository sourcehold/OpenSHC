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
            Unit* psVar2;
            int iVar2;
            int iVar3;
            DAT_TroopValueState::instance.attackInfo.targetedBuildingTilesArraySize = 0;
            MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                16000, '\0', (void*)((int)(DAT_TroopValueState::instance.attackInfo.targetedBuildingTilesArray)));
            uint uVar1 = DAT_UnitsState::instance.maxUnitCount;
            iVar3 = 1;
            if (1 < DAT_UnitsState::instance.maxUnitCount) {
                psVar2 = &DAT_UnitsState::instance.units[1];
                iVar2 = DAT_TroopValueState::instance.attackInfo.targetedBuildingTilesArraySize;
                do {
                    if (psVar2->logicalState == Map::Units::ULS_NORMAL && psVar2->isSelectable_OR_matchTime
                        && psVar2->owner == playerID && psVar2->targetedBuildingTile
                        && psVar2->unitType != Map::Units::UT_A_SLAVE) {
                        DAT_TroopValueState::instance.attackInfo.targetedBuildingTilesArray[iVar2]
                            = psVar2->targetedBuildingTile;
                        /*
                          Units.targetBuildingTile
                         */
                        iVar2 = DAT_TroopValueState::instance.attackInfo.targetedBuildingTilesArraySize + 1;
                        DAT_TroopValueState::instance.attackInfo.targetedBuildingTilesArraySize = iVar2;
                        if (4000 <= iVar2) {
                            break;
                        }
                    }
                    iVar3 = iVar3 + 1;
                    psVar2 = psVar2 + 1;
                } while (iVar3 < (int)uVar1);
            }
        }

    }
}
}
