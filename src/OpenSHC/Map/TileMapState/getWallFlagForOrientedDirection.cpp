#include "../TileMapState.func.hpp"

#include "OpenSHC/Map/Enums/CardinalDirection.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_WALL_OR_GATEHOUSE;

    // FUNCTION: STRONGHOLDCRUSADER 0x004F89C0
    BOOLEnum TileMapState::getWallFlagForOrientedDirection(int tileUnk, int y, int twoOrFour)
    {
        int direction = OpenSHC::Map::Enums::CD_NORTH;
        if (twoOrFour == OpenSHC::Map::Enums::CD_EAST) {
            if (this->mapOrientation == OpenSHC::Map::Enums::MO_NORTH) {
                direction = OpenSHC::Map::Enums::CD_EAST;
            } else if (this->mapOrientation == OpenSHC::Map::Enums::MO_EAST) {
                direction = OpenSHC::Map::Enums::CD_SOUTH;
            } else if (this->mapOrientation == OpenSHC::Map::Enums::MO_SOUTH) {
                direction = OpenSHC::Map::Enums::CD_WEST;
            } else if (this->mapOrientation == OpenSHC::Map::Enums::MO_WEST) {
                direction = OpenSHC::Map::Enums::CD_NORTH;
            }
        } else if (twoOrFour == OpenSHC::Map::Enums::CD_SOUTH) {
            if (this->mapOrientation == OpenSHC::Map::Enums::MO_NORTH) {
                direction = OpenSHC::Map::Enums::CD_SOUTH;
            } else if (this->mapOrientation == OpenSHC::Map::Enums::MO_EAST) {
                direction = OpenSHC::Map::Enums::CD_WEST;
            } else if (this->mapOrientation == OpenSHC::Map::Enums::MO_SOUTH) {
                direction = OpenSHC::Map::Enums::CD_NORTH;
            } else if (this->mapOrientation == OpenSHC::Map::Enums::MO_WEST) {
                direction = OpenSHC::Map::Enums::CD_EAST;
            }
        } else {
            return FALSE;
        }
        if ((this->LogicLayer[this->directionTranslationMatrix[y][direction] + tileUnk] & L_WALL_OR_GATEHOUSE) != 0) {
            return TRUE;
        }
        return FALSE;
    }

}
}
