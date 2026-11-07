#include "../TileMapState.func.hpp"

#include "OpenSHC/Map/MapConstants.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004FBC30
    undefined4 TileMapState::getCastleBuildRangeForMapSize()
    {
        switch (this->mapSize) {
        case 160:
            return 45;
        case 200:
            return 50;
        case 300:
            return 60;
        case MC_MAP_XY_LIMIT:
            return 70;
        }
        return 70;
    }

}
}
