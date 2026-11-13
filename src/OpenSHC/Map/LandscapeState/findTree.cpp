#include "../LandscapeState.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004F3B90
    int LandscapeState::findTree(int playerID, uint unitXPosition, uint unitYPosition)
    {
        bool const onMap = unitXPosition <= 399 && unitYPosition <= 399
            && DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[unitYPosition * 400 + unitXPosition] != 0;
        if (!onMap) {
            return 0;
        }
        int closestDistance = 10000;
        int closestTreeID = 0;
        int const unitArea
            = (short)DAT_TileMapState::instance
                  .PathConnectionLayer[DAT_ViewportRenderState::instance.translationMatrix[unitYPosition].addXgetTile
                      + unitXPosition];
        if (unitArea <= 0) {
            return 0;
        }
        for (int treeID = 1; treeID < this->maxTreeCount; ++treeID) {
            if (this->trees[treeID].stage >= 4) {
                continue;
            }
            if (this->trees[treeID].state != 2) {
                continue;
            }
            if (!MACRO_CALL_MEMBER(LandscapeState_Func::isTreeAdult, this)(treeID, this->trees[treeID].uid)) {
                continue;
            }
            int const treeHeight = DAT_TileMapState::instance.HeightLayer[this->trees[treeID].tile];
            int direction = 0;
            for (; direction < 8; ++direction) {
                int const tile
                    = DAT_TileMapState::instance.directionTranslationMatrix[this->trees[treeID].yPosition][direction]
                    + this->trees[treeID].tile;
                int height = DAT_TileMapState::instance.HeightLayer[tile];
                if (DAT_TileMapState::instance.BuildingLayer[tile] != 0) {
                    height += MACRO_CALL_MEMBER(Buildings::BuildingsState_Func::getBuildingHeightForBuildingID,
                        DAT_BuildingsState::ptr)(DAT_TileMapState::instance.BuildingLayer[tile]);
                }
                if (treeHeight > height + 16 || treeHeight < height - 16) {
                    continue;
                }
                if (MACRO_CALL_MEMBER(Navigation::PathFindingState_Func::calculateCanPlayerUnitsNavigateToAreaFromArea,
                        DAT_PathFindingState::ptr)(
                        playerID, unitArea, (short)DAT_TileMapState::instance.PathConnectionLayer[tile], 0)) {
                    break;
                }
            }
            if (direction >= 8) {
                continue;
            }
            MACRO_CALL_MEMBER(
                Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult, DAT_DirectionAlgorithmState::ptr)(
                unitXPosition, unitYPosition, this->trees[treeID].xPosition, this->trees[treeID].yPosition);
            if (DAT_DirectionAlgorithmState::instance.distanceHigh < closestDistance) {
                closestDistance = DAT_DirectionAlgorithmState::instance.distanceHigh;
                closestTreeID = treeID;
            }
        }
        return closestTreeID;
    }

}
}
