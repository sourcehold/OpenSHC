#include "../TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004F6F90
    void TileMapState::setMapSize(int size)
    {
        int index = 0;
        for (; size <= DAT_TerrainDefinedData::instance.MapSizes[index]; index++) {}

        if (DAT_TerrainDefinedData::instance.MapSizes[index] == -1) {
            this->mapSize = DAT_TerrainDefinedData::instance.MapSizes[0];
            return;
        }
        this->mapSize = DAT_TerrainDefinedData::instance.MapSizes[index];
    }

}
}
