#include "../TileMapState.func.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004F89C0
    uint TileMapState::getWallFlagForOrientedDirection(int tileUnk, int y, int twoOrFour)
    {
        int direction = 0;
        if (twoOrFour == 2) {
            if (this->mapOrientation == 0) {
                direction = 2;
            } else if (this->mapOrientation == 2) {
                direction = 4;
            } else if (this->mapOrientation == 4) {
                direction = 6;
            } else if (this->mapOrientation == 6) {
                direction = 0;
            }
        } else if (twoOrFour == 4) {
            if (this->mapOrientation == 0) {
                direction = 4;
            } else if (this->mapOrientation == 2) {
                direction = 6;
            } else if (this->mapOrientation == 4) {
                direction = 0;
            } else if (this->mapOrientation == 6) {
                direction = 2;
            }
        } else {
            return 0;
        }
        return (uint)this->LogicLayer[this->directionTranslationMatrix[y][direction] + tileUnk] >> 8 & 1;
    }

}
}
