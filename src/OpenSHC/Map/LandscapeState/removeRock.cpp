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

    // FUNCTION: STRONGHOLDCRUSADER 0x004F2220
    void LandscapeState::removeRock(int param_1)
    {
        MACRO_CALL_MEMBER(Map::TileMapState_Func::clearRockFootprintFlags, DAT_TileMapState::ptr)(param_1);
        MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::updatePathLinkagesInAllEightDirections,
            DAT_PathFindingState::ptr)((int)(short)this->rocks[param_1].y, (int)((int)(this->rocks[param_1].tile)));
        DAT_PathFindingState::instance.toggleUpdateSeparateAreaTileMap = 1;
        MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
            0x20, '\0', (void*)((int)(this->rocks + param_1)));
    }

}
}
