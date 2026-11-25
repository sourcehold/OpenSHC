#include "../PathFindingState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"

#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        // FUNCTION: STRONGHOLDCRUSADER 0x00496E40
        void PathFindingState::clearPathFindingTileMaps()
        {
            MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                sizeof(DAT_TileMapState::instance.PathConnectionLayer), 0,
                DAT_TileMapState::instance.PathConnectionLayer);
            MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                sizeof(DAT_TileMapState::instance.PathLinkageLayer), 0, DAT_TileMapState::instance.PathLinkageLayer);
            MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                sizeof(DAT_TileMapState::instance.CertainPathLayer), 0, DAT_TileMapState::instance.CertainPathLayer);
            MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                sizeof(DAT_TileMapState::instance.WalkLayer), 0, DAT_TileMapState::instance.WalkLayer);
        }

    }
}
}
