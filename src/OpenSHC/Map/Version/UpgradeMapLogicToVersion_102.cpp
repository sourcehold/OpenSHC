#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Version.func.hpp"
#include "OpenSHC/Map/MapConstants.hpp"

#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x00501490
    void Version::UpgradeMapLogicToVersion_102()
    {
        // Older maps stored the logic layer as 16-bit values: widen them in place
        ushort oldLogicLayer[OpenSHC::Map::MC_MAP_TILES_COUNT];
        MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::copyData, DAT_LowLevelMemory::ptr)(
            sizeof(oldLogicLayer), DAT_TileMapState::instance.LogicLayer, oldLogicLayer);
        for (int tile = 0; tile < OpenSHC::Map::MC_MAP_TILES_COUNT; ++tile) {
            DAT_TileMapState::instance.LogicLayer[tile] = oldLogicLayer[tile];
        }
    }

}
}
