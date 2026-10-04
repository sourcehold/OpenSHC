#include "../DirectionAlgorithmState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        // FUNCTION: STRONGHOLDCRUSADER 0x0046CCD0
        int DirectionAlgorithmState::getMouseVectorLengthBasedOnDirection(
            int storedScreenSpaceX, int storedScreenSpaceY, int screenSpaceX, int screenSpaceY, int orientation)
        {
            if (orientation == 0) {
                if (storedScreenSpaceY > screenSpaceY) {
                    return storedScreenSpaceY - screenSpaceY;
                }
            } else if (orientation == 4) {
                if (screenSpaceY > storedScreenSpaceY) {
                    return screenSpaceY - storedScreenSpaceY;
                }
            } else if (orientation == 6) {
                if (storedScreenSpaceX > screenSpaceX) {
                    return storedScreenSpaceX - screenSpaceX;
                }
            } else if (orientation == 2) {
                if (screenSpaceX > storedScreenSpaceX) {
                    return screenSpaceX - storedScreenSpaceX;
                }
            }
            return 0;
        }

    }
}
}
