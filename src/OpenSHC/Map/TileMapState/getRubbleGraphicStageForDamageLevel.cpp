#include "../TileMapState.func.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::Enums::CD_NORTHEAST;
    using OpenSHC::Map::Enums::CD_NORTHWEST;
    using OpenSHC::Map::Enums::CD_SOUTHEAST;
    using OpenSHC::Map::Enums::CD_SOUTHWEST;
    using OpenSHC::Map::Enums::MO_EAST;
    using OpenSHC::Map::Enums::MO_NORTH;
    using OpenSHC::Map::Enums::MO_SOUTH;
    using OpenSHC::Map::Enums::MO_WEST;

    // FUNCTION: STRONGHOLDCRUSADER 0x004FA460
    int TileMapState::getRubbleGraphicStageForDamageLevel(int rotation)
    {
        int result = 0;
        int orientation = this->mapOrientation;
        if (orientation == MO_NORTH) {
            if (rotation == 80) {
                result = 1;
            } else if (rotation == 81) {
                result = 0;
            } else if (rotation == CD_NORTHEAST) {
                result = 2;
            } else if (rotation == CD_NORTHWEST) {
                result = 5;
            } else if (rotation == CD_SOUTHEAST) {
                result = 3;
            } else if (rotation == CD_SOUTHWEST) {
                result = 4;
            }
        } else if (orientation == MO_SOUTH) {
            if (rotation == 80) {
                result = 1;
            } else if (rotation == 81) {
                result = 0;
            } else if (rotation == CD_NORTHEAST) {
                result = 4;
            } else if (rotation == CD_NORTHWEST) {
                result = 3;
            } else if (rotation == CD_SOUTHEAST) {
                result = 5;
            } else if (rotation == CD_SOUTHWEST) {
                result = 2;
            }
        } else if (orientation == MO_EAST) {
            if (rotation == 80) {
                result = 0;
            } else if (rotation == 81) {
                result = 1;
            } else if (rotation == CD_NORTHEAST) {
                result = 5;
            } else if (rotation == CD_NORTHWEST) {
                result = 4;
            } else if (rotation == CD_SOUTHEAST) {
                result = 2;
            } else if (rotation == CD_SOUTHWEST) {
                result = 3;
            }
        } else if (orientation == MO_WEST) {
            if (rotation == 80) {
                result = 0;
            } else if (rotation == 81) {
                result = 1;
            } else if (rotation == CD_NORTHEAST) {
                result = 3;
            } else if (rotation == CD_NORTHWEST) {
                result = 2;
            } else if (rotation == CD_SOUTHEAST) {
                result = 4;
            } else if (rotation == CD_SOUTHWEST) {
                result = 5;
            }
        }
        return result;
    }

}
}
