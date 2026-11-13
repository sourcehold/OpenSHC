#include "../TileMapState.func.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004F89C0
    BOOLEnum TileMapState::getWallFlagForOrientedDirection(int tileUnk, int y, int twoOrFour)
    {
        int direction = 0;
        if (twoOrFour == 2) {
            if (this->mapOrientation == OpenSHC::Map::Enums::MO_NORTH) {
                direction = 2;
            } else if (this->mapOrientation == OpenSHC::Map::Enums::MO_EAST) {
                direction = 4;
            } else if (this->mapOrientation == OpenSHC::Map::Enums::MO_SOUTH) {
                direction = 6;
            } else if (this->mapOrientation == OpenSHC::Map::Enums::MO_WEST) {
                direction = 0;
            }
        } else if (twoOrFour == 4) {
            if (this->mapOrientation == OpenSHC::Map::Enums::MO_NORTH) {
                direction = 4;
            } else if (this->mapOrientation == OpenSHC::Map::Enums::MO_EAST) {
                direction = 6;
            } else if (this->mapOrientation == OpenSHC::Map::Enums::MO_SOUTH) {
                direction = 0;
            } else if (this->mapOrientation == OpenSHC::Map::Enums::MO_WEST) {
                direction = 2;
            }
        } else {
            return FALSE;
        }
        return (uint)this->LogicLayer[this->directionTranslationMatrix[y][direction] + tileUnk] >> 8 & TRUE;
    }

}
}
