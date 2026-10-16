#include "../../../Map.func.hpp"
#include "../TroopValueState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using Map::Units::UnitLogicState;
        using Map::Units::UnitType;

        // FUNCTION: STRONGHOLDCRUSADER 0x005198C0
        void TroopValueState::recomputeTargetedBuildingTilesArray(int playerID)
        {
            uint uVar1;
            Unit* psVar2;
            int iVar2;
            int iVar3;
            this->attackInfo.targetedBuildingTilesArraySize = 0;
            MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                16000, '\0', (void*)((int)(this->attackInfo.targetedBuildingTilesArray)));
            uVar1 = DAT_UnitsState::instance.maxUnitCount;
            iVar3 = 1;
            if (1 < DAT_UnitsState::instance.maxUnitCount) {
                psVar2 = &DAT_UnitsState::instance.units[1];
                iVar2 = this->attackInfo.targetedBuildingTilesArraySize;
                do {
                    if ((((psVar2->logicalState == Map::Units::ULS_NORMAL) && (psVar2->isSelectable_OR_matchTime))
                            && (psVar2->owner == playerID))
                        && ((psVar2->targetedBuildingTile && (psVar2->unitType != Map::Units::UT_A_SLAVE)))) {
                        this->attackInfo.targetedBuildingTilesArray[iVar2] = psVar2->targetedBuildingTile;
                        /*
                          Units.targetBuildingTile
                         */
                        iVar2 = this->attackInfo.targetedBuildingTilesArraySize + 1;
                        this->attackInfo.targetedBuildingTilesArraySize = iVar2;
                        if (3999 < iVar2) {}
                    }
                    iVar3 = iVar3 + 1;
                    psVar2 = psVar2 + 0x248;
                } while (iVar3 < (int)uVar1);
            }
        }

    }
}
}
