#include "OpenSHC/Map/TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"

namespace OpenSHC {
namespace Map {

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004F6F90
    void TileMapState::setMapSize(int size)
    {
        int index = 0;
        while (size <= DAT_TerrainDefinedData::instance.MapSizes[index]) {
            index++;
        }

        if (DAT_TerrainDefinedData::instance.MapSizes[index] == -1) {
            this->mapSize = DAT_TerrainDefinedData::instance.MapSizes[0];
            return;
        }
        this->mapSize = DAT_TerrainDefinedData::instance.MapSizes[index];
    }

}
}
