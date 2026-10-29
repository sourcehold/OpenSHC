#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/LandscapeState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {

    // updatePathLinkagesInAllEightDirections gets (short)yPosition and the tree tile (0x4F208B..0x4F20A3).
    // FUNCTION: STRONGHOLDCRUSADER 0x004F2070
    void LandscapeState::removeTree(int treeID)
    {
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::clearTreeFootprintFlags, DAT_TileMapState::ptr)(treeID);
        MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updatePathLinkagesInAllEightDirections,
            DAT_PathFindingState::ptr)((short)this->trees[treeID].yPosition, this->trees[treeID].tile);
        DAT_PathFindingState::instance.toggleUpdateSeparateAreaTileMap = 1;
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::applyTreeBrushToLogicalLayer, DAT_TileMapState::ptr)(
            treeID, 1);
        MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
            0x9c, 0, &this->trees[treeID]);
    }

}
}
