#include "../TribesState.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"

#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // The coordinates are tested unsigned (ja 0x18F); ALG_ResultTileIndex counts the tiles taken and is
        // compared signed (jge 0x1F4 at 0x524DCF); UnitLayer is read signed (movsx, 0x524DD5). The tribe size is
        // re-read every iteration (0x524D80). All failure exits share the return block at 0x524CD7 except the
        // occupied-tileUnk exit (0x524E00).
        // FUNCTION: STRONGHOLDCRUSADER 0x00524CA0
        undefined4 TribesState::isTribePathToDestinationClear(
            int tribeID, uint fromX, uint fromY, uint destX, uint destY)
        {
            int unitSelectionIndex = 0;
            if (fromX > 399 || fromY > 399
                || DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[fromY * 400 + fromX] == 0) {
                return 0;
            }
            if (destX > 399 || destY > 399
                || DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[destY * 400 + destX] == 0) {
                return 0;
            }
            int const destTile = DAT_ViewportRenderState::instance.translationMatrix[destY].addXgetTile + destX;
            if (DAT_TileMapState::instance
                    .PathConnectionLayer[DAT_ViewportRenderState::instance.translationMatrix[fromY].addXgetTile + fromX]
                != DAT_TileMapState::instance.PathConnectionLayer[destTile]) {
                return 0;
            }
            this->ALG_ResultTileIndex = 0;
            int const closestTileMode = (DAT_TileMapState::instance.LogicLayer[destTile] & 0x100) != 0 ? 1 : 2;
            MACRO_CALL_MEMBER(Navigation::PathFindingState_Func::findLinkageBasedPathOrWalkRadius,
                DAT_PathFindingState::ptr)(destX, destY, -1, -1, 500, FALSE);
            for (;;) {
                if (unitSelectionIndex >= this->tribes[tribeID].size) {
                    return 1;
                }
                int const unitID = MACRO_CALL_MEMBER(
                    OpenSHC::Map::Units::TribesState_Func::getUnitIDForIndexInTribe, this)(tribeID, unitSelectionIndex);
                ++unitSelectionIndex;
                if (DAT_UnitsState::instance.units[unitID].logicalState != ULS_NORMAL
                    || DAT_UnitsState::instance.units[unitID].dying != 0) {
                    continue;
                }
                int const tileUnk = MACRO_CALL_MEMBER(Navigation::PathFindingState_Func::findClosestTileToStartingTile,
                    DAT_PathFindingState::ptr)(closestTileMode);
                ++this->ALG_ResultTileIndex;
                if ((int)this->ALG_ResultTileIndex >= 500) {
                    return 0;
                }
                int const occupantUnitID = (short)DAT_TileMapState::instance.UnitLayer[tileUnk];
                if (occupantUnitID != 0 && unitID != occupantUnitID
                    && DAT_UnitsState::instance.units[occupantUnitID].tribeID != tribeID
                    && DAT_UnitsState::instance.units[occupantUnitID].tunnelerFinishedDigging != 2) {
                    return 0;
                }
            }
        }
    }
}
}
