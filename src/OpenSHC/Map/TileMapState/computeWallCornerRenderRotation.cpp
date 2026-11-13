#include "../TileMapState.func.hpp"

#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004FC650
    int TileMapState::computeWallCornerRenderRotation(uint x)
    {
        int tileUnk = this->DAT_SomeTile;
        int y = this->DAT_SomeY;
        int result = 0;
        if (MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::isWallConnectionHeightValid, this)(tileUnk, y, 2)) {
            if (this->mapOrientation == OpenSHC::Map::Enums::MO_NORTH) {
                if ((x & 0xf) == 0xf) {
                    result = 2;
                } else {
                    result = 17 - (x & 0xf);
                }
            } else if (this->mapOrientation == OpenSHC::Map::Enums::MO_SOUTH) {
                if ((x & 0xf) == 0) {
                    result = 2;
                } else {
                    result = (x & 0xf) + 2;
                }
            } else if (this->mapOrientation == OpenSHC::Map::Enums::MO_EAST) {
                if ((x & 0xf) == 0) {
                    result = 1;
                } else {
                    result = (x & 0xf) + 17;
                }
            } else if (this->mapOrientation == OpenSHC::Map::Enums::MO_WEST) {
                if ((x & 0xf) == 0xf) {
                    result = 1;
                } else {
                    result = 32 - (x & 0xf);
                }
            }
        } else if (MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::isWallConnectionHeightValid, this)(
                       tileUnk, y, 0)) {
            if (this->mapOrientation == OpenSHC::Map::Enums::MO_NORTH) {
                if ((y & 0xf) == 0xf) {
                    result = 1;
                } else {
                    result = 32 - (y & 0xf);
                }
            } else if (this->mapOrientation == OpenSHC::Map::Enums::MO_SOUTH) {
                if ((y & 0xf) == 0) {
                    result = 1;
                } else {
                    result = (y & 0xf) + 17;
                }
            } else if (this->mapOrientation == OpenSHC::Map::Enums::MO_WEST) {
                if ((y & 0xf) == 0) {
                    result = 2;
                } else {
                    result = (y & 0xf) + 2;
                }
            } else if (this->mapOrientation == OpenSHC::Map::Enums::MO_EAST) {
                if ((y & 0xf) == 0xf) {
                    result = 2;
                } else {
                    result = 17 - (y & 0xf);
                }
            }
        } else if (MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getWallFlagForOrientedDirection, this)(
                       tileUnk, y, 2)) {
            result = 48;
        } else if (MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getWallFlagForOrientedDirection, this)(
                       tileUnk, y, 4)) {
            result = 63;
        } else {
            result = 33;
        }
        return result;
    }
}
}
