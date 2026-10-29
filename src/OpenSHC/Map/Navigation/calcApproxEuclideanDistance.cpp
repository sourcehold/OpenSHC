#include "OpenSHC/Map/Navigation.func.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x0049B8C0
    int __cdecl Navigation::calcApproxEuclideanDistance(int x1, int x2, int y1, int y2)
    {
        int dx;
        if (x1 > x2) {
            dx = x1 - x2;
        } else {
            dx = x2 - x1;
        }
        int dy;
        if (y1 > y2) {
            dy = y1 - y2;
        } else {
            dy = y2 - y1;
        }

        if (dx < dy) {
            if (dy != 0) {
                return dx * 2 / 5 * dx / dy + dy;
            }
        } else {
            if (dx != 0) {
                return dy * 2 / 5 * dy / dx + dx;
            }
        }
        return 0;
    }

}
}
