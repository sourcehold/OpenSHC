#include "../../../Map.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using Map::Units::UnitLogicState;
        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00524CA0
        undefined4 TribesState::isTribePathToDestinationClear(
            int param_1, uint param_2, uint param_3, uint param_4, uint param_5)
        {
            int iVar2;
            int iVar3;
            int local_4 = 0;
            if (param_2 < 400 && param_3 < 400 && *(char*)(param_3 * 400 + (int)DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400 + param_2) != '\0' && param_4 < 400
                && param_5 < 400 && *(char*)(param_5 * 400 + (int)DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400 + param_4) != '\0'
                && (iVar2 = DAT_ViewportRenderState::instance.translationMatrix[param_5].addXgetTile + param_4,
                    DAT_TileMapState::instance.PathConnectionLayer
                            [DAT_ViewportRenderState::instance.translationMatrix[param_3].addXgetTile + param_2]
                        == DAT_TileMapState::instance.PathConnectionLayer[iVar2])) {
                this->ALG_ResultTileIndex = 0;
                uint uVar1 = DAT_TileMapState::instance.LogicLayer[iVar2];
                MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::findLinkageBasedPathOrWalkRadius,
                    DAT_PathFindingState::ptr)(param_4, param_5, -1, -1, 500, FALSE);
                while (true) {
                    do {
                        if (this->tribes[param_1].size <= local_4) {
                            return (undefined4)(1);
                        }
                        iVar2 = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::getUnitIDForIndexInTribe, this)(
                            param_1, local_4);
                        local_4 = local_4 + 1;
                    } while ((DAT_UnitsState::instance.units[iVar2].logicalState != Map::Units::ULS_NORMAL)
                        || (DAT_UnitsState::instance.units[iVar2].dying != 0));
                    iVar3 = MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::findClosestTileToStartingTile,
                        DAT_PathFindingState::ptr)(2 - (uint)((uVar1 & 0x100)));
                    this->ALG_ResultTileIndex = this->ALG_ResultTileIndex + 1;
                    if (499 < this->ALG_ResultTileIndex)
                        break;
                    iVar3 = (int)(short)DAT_TileMapState::instance.UnitLayer[iVar3];
                    if (iVar3 && iVar2 != iVar3 && DAT_UnitsState::instance.units[iVar3].tribeID != param_1
                        && DAT_UnitsState::instance.units[iVar3].tunnelerFinishedDigging != 2) {
                        return (undefined4)(0);
                    }
                }
            }
            return (undefined4)(0);
        }

    }
}
}
