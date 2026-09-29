
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
        int tile = this->DAT_SomeTile;
        int y = this->DAT_SomeY;
        if (MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::isWallConnectionHeightValid, this)(
                this->DAT_SomeTile, this->DAT_SomeY, 2)
            != FALSE) {
            if (this->mapOrientation == 0) {
                if ((x & 0xf) != 0xf) {
                    return 17 - (x & 0xf);
                }
                return 2;
            }
            if (this->mapOrientation == 4) {
                if ((x & 0xf) != 0) {
                    return (x & 0xf) + 2;
                }
                return 2;
            }
            if (this->mapOrientation == 2) {
                if ((x & 0xf) == 0) {
                    return 1;
                }
                return (x & 0xf) + 0x11;
            }
            if (this->mapOrientation != 6) {
                return 0;
            }
            if ((x & 0xf) == 0xf) {
                return 1;
            }
            return 32 - (x & 0xf);
        }

        if (MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::isWallConnectionHeightValid, this)(tile, y, 0)
            != FALSE) {
            if (this->mapOrientation == 0) {
                if ((y & 0xf) != 0xf) {
                    return 32 - (y & 0xf);
                }
                return 1;
            }
            if (this->mapOrientation == 4) {
                if ((y & 0xf) != 0) {
                    return (y & 0xf) + 0x11;
                }
                return 1;
            }
            if (this->mapOrientation == 6) {
                if ((y & 0xf) == 0) {
                    return 2;
                }
                return (y & 0xf) + 2;
            }
            if (this->mapOrientation != 2) {
                return 0;
            }
            if ((y & 0xf) == 0xf) {
                return 2;
            }
            return 0x11 - (y & 0xf);
        }

        if (MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getWallFlagForOrientedDirection, this)(tile, y, 2)
            != 0) {
            return 48;
        }
        /* 0x3f when the other direction carries a wall too, 0x21 when it does not */
        return (-(uint)(MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getWallFlagForOrientedDirection, this)(
                            tile, y, 4)
                    != 0)
                   & 0x1e)
            + 0x21;
    }

}
}
