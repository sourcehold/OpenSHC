#include "../Game.func.hpp"

namespace OpenSHC {
namespace Game {

    // FUNCTION: STRONGHOLDCRUSADER 0x0044AAB0
    int __cdecl RelativeValueForGenie(int larger, int smaller)
    {
        if (larger < 1) {
            larger = 1;
        }
        if (smaller < 1) {
            smaller = 1;
        }
        if (larger > smaller) {
            int iVar1 = (larger * 100) / smaller;
            if (iVar1 < 150) {
                return 0;
            }
            if (iVar1 < 170) {
                return 1;
            }
            if (iVar1 < 190) {
                return 2;
            }
            if (iVar1 < 210) {
                return 3;
            }
            if (iVar1 < 230) {
                return 4;
            }
            if (iVar1 < 250) {
                return 5;
            }
            if (iVar1 < 270) {
                return 6;
            }
            return 7;
        } else {
            int iVar1 = (smaller * 100) / larger;
            if (iVar1 < 150) {
                return 0;
            }
            if (iVar1 < 190) {
                return -1;
            }
            if (iVar1 < 240) {
                return -2;
            }
            return -3;
        }
    }

}
}
