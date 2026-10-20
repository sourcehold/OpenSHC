#include "../../../Map.func.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using Map::Units::UnitLogicState;
        using Map::Units::States::UnitState;

        // FUNCTION: STRONGHOLDCRUSADER 0x00524B30
        undefined4 TribesState::isTribeUnitBlockedByOtherUnit(int param_1)
        {
            int iVar2;
            int unitSelectionIndex = 0;
            int sVar1 = this->tribes[param_1].size;
            while (true) {
                do {
                    if (unitSelectionIndex >= sVar1) {
                        return (undefined4)(0);
                    }
                    iVar2 = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::getUnitIDForIndexInTribe, this)(
                        param_1, unitSelectionIndex);
                    unitSelectionIndex = unitSelectionIndex + 1;
                } while ((DAT_UnitsState::instance.units[iVar2].logicalState != Map::Units::ULS_NORMAL)
                    || (DAT_UnitsState::instance.units[iVar2].dying != 0));
                if (DAT_UnitsState::instance.units[iVar2].usingTeleport != 0) {
                    return (undefined4)(0);
                }
                if (DAT_UnitsState::instance.units[iVar2].field303_0x413 != 0) {
                    return (undefined4)(0);
                }
                if (DAT_UnitsState::instance.units[iVar2].tunnelerFinishedDigging == 2)
                    break;
                if (DAT_UnitsState::instance.units[iVar2].state.generic == Map::Units::States::US_MELEE_ATTACK) {
                    return (undefined4)(0);
                }
                if (DAT_UnitsState::instance.units[iVar2].laddermanIsInPosition != '\0') {
                    return (undefined4)(0);
                }
                int iVar3
                    = (int)(short)DAT_TileMapState::instance.UnitLayer[DAT_UnitsState::instance.units[iVar2].tile];
                if (iVar3 && iVar2 != iVar3 && DAT_UnitsState::instance.units[iVar3].tunnelerFinishedDigging != 2) {
                    return (undefined4)(1);
                }
            }
            return (undefined4)(0);
        }

    }
}
}
