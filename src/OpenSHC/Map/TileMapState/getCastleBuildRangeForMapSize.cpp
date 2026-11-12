#include "../TileMapState.func.hpp"

#include "OpenSHC/Map/MapConstants.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004FBC30
    undefined4 TileMapState::getCastleBuildRangeForMapSize()
    {
        switch (this->mapSize) {
        case MC_MAP_SIZE_160:
            return 45;
        case MC_MAP_SIZE_200:
            return 50;
        case MC_MAP_SIZE_300:
            return 60;
        case MC_MAP_SIZE_400:
            return 70;
        }
        return 70;
    }

}
}
