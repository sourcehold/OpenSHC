#include "OpenSHC/Map/TileMapState.func.hpp"

namespace OpenSHC {
namespace Map {

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
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
        case 400:
            return 70;
        }
        return 70;
    }

}
}
