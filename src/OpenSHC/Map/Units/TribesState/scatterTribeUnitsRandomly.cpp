#include "../../../Map.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"

#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using Map::Units::UnitLogicState;
        using Map::Units::States::UnitState;

        // FUNCTION: STRONGHOLDCRUSADER 0x00523920
        int TribesState::scatterTribeUnitsRandomly(int param_1)
        {
            short sVar1;
            int iVar2;
            int iVar3;
            int iVar4;
            int unitSelectionIndex;
            int index;
            if (!param_1) {
                return 0;
            }
            sVar1 = this->tribes[param_1].selectionTargetUnitID;
            unitSelectionIndex = 0;
            index = 100;
            MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::findSuitableSpawnLocationUnk,
                DAT_PathFindingState::ptr)((int)DAT_UnitsState::instance.units[sVar1].x,
                (int)(DAT_UnitsState::instance.units[sVar1].y), -1, -1, 5000, 0);
            iVar2 = MACRO_CALL_MEMBER(
                Map::Navigation::PathFindingState_Func::getComputationalTileIndex, DAT_PathFindingState::ptr)();
            iVar4 = (int)this->tribes[param_1].size;
            if (iVar4 * 0x10 + 200 <= iVar2) {
                if (0 < iVar4) {
                    do {
                        iVar2 = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::getUnitIDForIndexInTribe, this)(
                            param_1, unitSelectionIndex);
                        unitSelectionIndex = unitSelectionIndex + 1;
                        if ((DAT_UnitsState::instance.units[iVar2].logicalState == Map::Units::ULS_NORMAL)
                            && (DAT_UnitsState::instance.units[iVar2].dying == 0)) {
                            index = index + 1 + (DAT_UnitsState::instance.units[iVar2].fixedRng & 0xf);
                            iVar3 = MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::getTileInSearchQueue,
                                DAT_PathFindingState::ptr)(index);
                            iVar4 = DAT_ViewportRenderState::instance
                                        .translationMatrix[DAT_ViewportRenderState::instance
                                                .tileTranslationMatrix_YComponent[iVar3]]
                                        .addXgetTile;
                            DAT_UnitsState::instance.units[iVar2].targetY
                                = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[iVar3];
                            DAT_UnitsState::instance.units[iVar2].targetX = (short)iVar3 - (short)iVar4;
                            DAT_UnitsState::instance.units[iVar2].state.generic = ((UnitStateShort)0xd1);
                        }
                    } while (unitSelectionIndex < this->tribes[param_1].size);
                }
                return 1;
            }
            return 0;
        }

    }
}
}
