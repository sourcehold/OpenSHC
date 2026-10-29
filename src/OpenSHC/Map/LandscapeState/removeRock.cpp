#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/LandscapeState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004F2220
    void LandscapeState::removeRock(int rockID)
    {
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::clearRockFootprintFlags, DAT_TileMapState::ptr)(rockID);
        MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updatePathLinkagesInAllEightDirections,
            DAT_PathFindingState::ptr)((short)this->rocks[rockID].y, this->rocks[rockID].tile);
        DAT_PathFindingState::instance.toggleUpdateSeparateAreaTileMap = 1;
        MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
            0x20, 0, &this->rocks[rockID]);
    }

}
}
