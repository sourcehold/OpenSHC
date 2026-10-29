#include "../DirectionAlgorithmState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        /* each case is a hand-written `rol` on the parameter (rol byte ptr [esp+4], n in the original) */
        // FUNCTION: STRONGHOLDCRUSADER 0x0046CE30
        byte DirectionAlgorithmState::rotateByteLeft(byte value, int bits)
        {
            switch (bits) {
            case 1:
                __asm rol value, 1
                break;
            case 2:
                __asm rol value, 2
                break;
            case 3:
                __asm rol value, 3
                break;
            case 4:
                __asm rol value, 4
                break;
            case 5:
                __asm rol value, 5
                break;
            case 6:
                __asm rol value, 6
                break;
            case 7:
                __asm rol value, 7
                break;
            }
            return value;
        }

    }
}
}
