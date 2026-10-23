#include "OpenSHC/Map/TileMapState.func.hpp"

namespace OpenSHC {
namespace Map {

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004FA460
    undefined4 TileMapState::getRubbleGraphicStageForDamageLevel(int rotation)
    {
        /* the result lives in eax from the start (xor eax, eax), every comparison goes through ecx */
        int result = 0;
        int orientation = this->mapOrientation;
        if (orientation == 0) {
            if (rotation == 0x50) {
                result = 1;
            } else if (rotation == 0x51) {
                result = 0;
            } else if (rotation == 1) {
                result = 2;
            } else if (rotation == 7) {
                result = 5;
            } else if (rotation == 3) {
                result = 3;
            } else if (rotation == 5) {
                result = 4;
            }
        } else if (orientation == 4) {
            if (rotation == 0x50) {
                result = 1;
            } else if (rotation == 0x51) {
                result = 0;
            } else if (rotation == 1) {
                result = 4;
            } else if (rotation == 7) {
                result = 3;
            } else if (rotation == 3) {
                result = 5;
            } else if (rotation == 5) {
                result = 2;
            }
        } else if (orientation == 2) {
            if (rotation == 0x50) {
                result = 0;
            } else if (rotation == 0x51) {
                result = 1;
            } else if (rotation == 1) {
                result = 5;
            } else if (rotation == 7) {
                result = 4;
            } else if (rotation == 3) {
                result = 2;
            } else if (rotation == 5) {
                result = 3;
            }
        } else if (orientation == 6) {
            if (rotation == 0x50) {
                result = 0;
            } else if (rotation == 0x51) {
                result = 1;
            } else if (rotation == 1) {
                result = 3;
            } else if (rotation == 7) {
                result = 2;
            } else if (rotation == 3) {
                result = 4;
            } else if (rotation == 5) {
                result = 5;
            }
        }
        return result;
    }

}
}
