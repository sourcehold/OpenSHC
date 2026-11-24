#include "../../Map.func.hpp"
#include "../LandscapeState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004F2070
    void LandscapeState::removeTree(int treeID)
    {
        MACRO_CALL_MEMBER(Map::TileMapState_Func::clearTreeFootprintFlags, DAT_TileMapState::ptr)(treeID);
        MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::updatePathLinkagesInAllEightDirections,
            DAT_PathFindingState::ptr)(
            (int)(short)this->trees[treeID].yPosition, (int)((int)(this->trees[treeID].tile)));
        DAT_PathFindingState::instance.toggleUpdateSeparateAreaTileMap = 1;
        MACRO_CALL_MEMBER(Map::TileMapState_Func::applyTreeBrushToLogicalLayer, DAT_TileMapState::ptr)(
            treeID, 1);
        MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
            0x9c, '\0', (void*)((int)(this->trees + treeID)));
    }

}
}
