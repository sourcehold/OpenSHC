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

        /*
          The two guards stay as `||` chains. Splitting them into six separate `if`s, which
          is what recovered trySpawnAdditionalWildlifeForTribe's inline return blocks,
          measures worse here (quick_diff 0.6635 -> 0.6296): the original merges every
          failure into one `return 0` at 0x524cd7 rather than shrink-wrapping them.
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00524CA0
        undefined4 TribesState::isTribePathToDestinationClear(
            int tribeID, uint fromX, uint fromY, uint toX, uint toY)
        {
            int _unitIndex = 0;
            if (399 < fromX || 399 < fromY
                || DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[fromY * 400 + fromX] == 0) {
                return (undefined4)(0);
            }
            if (399 < toX || 399 < toY
                || DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[toY * 400 + toX] == 0) {
                return (undefined4)(0);
            }
            int const _toTile = DAT_ViewportRenderState::instance.translationMatrix[toY].addXgetTile + toX;
            if (DAT_TileMapState::instance.PathConnectionLayer
                    [DAT_ViewportRenderState::instance.translationMatrix[fromY].addXgetTile + fromX]
                != DAT_TileMapState::instance.PathConnectionLayer[_toTile]) {
                return (undefined4)(0);
            }
            this->ALG_ResultTileIndex = 0;
            /*
              The original computes this once, before the search is seeded. The
              decompiler's `2 - (uVar1 & 0x100)` subtracts the mask itself, but the binary
              has `and 0x100; neg; sbb; add 2`, which is 2 minus a 0/1 flag.
             */
            int const _searchMode = (DAT_TileMapState::instance.LogicLayer[_toTile] & 0x100) != 0 ? 1 : 2;
            MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::findLinkageBasedPathOrWalkRadius,
                DAT_PathFindingState::ptr)(toX, toY, -1, -1, 500, FALSE);
            while (true) {
                int _unitID;
                do {
                    if (_unitIndex >= this->tribes[tribeID].size) {
                        return (undefined4)(1);
                    }
                    _unitID = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::getUnitIDForIndexInTribe, this)(
                        tribeID, _unitIndex);
                    _unitIndex = _unitIndex + 1;
                } while ((DAT_UnitsState::instance.units[_unitID].logicalState != Map::Units::ULS_NORMAL)
                    || (DAT_UnitsState::instance.units[_unitID].dying != 0));
                int _blockingUnitID = MACRO_CALL_MEMBER(
                    Map::Navigation::PathFindingState_Func::findClosestTileToStartingTile, DAT_PathFindingState::ptr)(
                    _searchMode);
                this->ALG_ResultTileIndex = this->ALG_ResultTileIndex + 1;
                if ((int)this->ALG_ResultTileIndex >= 500)
                    break;
                _blockingUnitID = (int)(short)DAT_TileMapState::instance.UnitLayer[_blockingUnitID];
                if (_blockingUnitID && _unitID != _blockingUnitID
                    && DAT_UnitsState::instance.units[_blockingUnitID].tribeID != tribeID
                    && DAT_UnitsState::instance.units[_blockingUnitID].tunnelerFinishedDigging != 2) {
                    return (undefined4)(0);
                }
            }
            return (undefined4)(0);
        }

    }
}
}
