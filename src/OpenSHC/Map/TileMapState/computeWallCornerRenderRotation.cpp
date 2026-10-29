
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004FC650
    int TileMapState::computeWallCornerRenderRotation(uint x)
    {
        int tileUnk = this->DAT_SomeTile;
        int y = this->DAT_SomeY;
        int result = 0;
        if (MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::isWallConnectionHeightValid, this)(tileUnk, y, 2)
            != FALSE) {
            if (this->mapOrientation == 0) {
                if ((x & 0xf) == 0xf) {
                    result = 2;
                } else {
                    result = 0x11 - (x & 0xf);
                }
            } else if (this->mapOrientation == 4) {
                if ((x & 0xf) == 0) {
                    result = 2;
                } else {
                    result = (x & 0xf) + 2;
                }
            } else if (this->mapOrientation == 2) {
                if ((x & 0xf) == 0) {
                    result = 1;
                } else {
                    result = (x & 0xf) + 0x11;
                }
            } else if (this->mapOrientation == 6) {
                if ((x & 0xf) == 0xf) {
                    result = 1;
                } else {
                    result = 0x20 - (x & 0xf);
                }
            }
        } else if (MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::isWallConnectionHeightValid, this)(tileUnk, y, 0)
            != FALSE) {
            if (this->mapOrientation == 0) {
                if ((y & 0xf) == 0xf) {
                    result = 1;
                } else {
                    result = 0x20 - (y & 0xf);
                }
            } else if (this->mapOrientation == 4) {
                if ((y & 0xf) == 0) {
                    result = 1;
                } else {
                    result = (y & 0xf) + 0x11;
                }
            } else if (this->mapOrientation == 6) {
                if ((y & 0xf) == 0) {
                    result = 2;
                } else {
                    result = (y & 0xf) + 2;
                }
            } else if (this->mapOrientation == 2) {
                if ((y & 0xf) == 0xf) {
                    result = 2;
                } else {
                    result = 0x11 - (y & 0xf);
                }
            }
        } else if (MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getWallFlagForOrientedDirection, this)(tileUnk, y, 2)
            != 0) {
            result = 48;
        } else {
            /* 0x3f when the other direction carries a wall too, 0x21 when it does not */
            result = (-(uint)(MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getWallFlagForOrientedDirection, this)(
                                  tileUnk, y, 4)
                          != 0)
                         & 0x1e)
                + 0x21;
        }
        return result;
    }
}
}
