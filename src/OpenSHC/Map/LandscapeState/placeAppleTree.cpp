#include "OpenSHC/Map/LandscapeState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_LandscapeState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004F3560
    void LandscapeState::placeAppleTree(int buildingID, undefined4 treeX, undefined4 treeY)
    {
        int const treeID = MACRO_CALL_MEMBER(LandscapeState_Func::createTree, DAT_LandscapeState::ptr)(
            treeX, treeY, Trees::TT_APPLEUnk, 1, 0, 0, 0);
        if (treeID == 0) {
            return;
        }
        DAT_LandscapeState::instance.trees[treeID].appleFarmID = (short)buildingID;
        DAT_LandscapeState::instance.trees[treeID].appleFarmUID
            = DAT_BuildingsState::instance.buildings[buildingID].uid;
        DAT_LandscapeState::instance.trees[treeID].stageTracker
            = DAT_LandscapeState::instance.trees[treeID].rng1 & 0x1f;
        DAT_TileMapState::instance.LogicLayer[DAT_LandscapeState::instance.trees[treeID].tile] |= 0x1000;
        DAT_TileMapState::instance.OrganismLayer[DAT_LandscapeState::instance.trees[treeID].tile] = (short)treeID;
        MACRO_CALL_MEMBER(TileMapState_Func::applyTreeBrushToLogicalLayer, DAT_TileMapState::ptr)(treeID, 0);
        MACRO_CALL_MEMBER(
            Navigation::PathFindingState_Func::updatePathLinkagesInAllEightDirections, DAT_PathFindingState::ptr)(
            DAT_LandscapeState::instance.trees[treeID].yPosition, DAT_LandscapeState::instance.trees[treeID].tile);
        DAT_PathFindingState::instance.toggleUpdateSeparateAreaTileMap = 1;
    }

}
}
