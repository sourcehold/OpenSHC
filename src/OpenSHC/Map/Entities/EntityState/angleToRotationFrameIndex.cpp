#include "../EntityState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        // FUNCTION: STRONGHOLDCRUSADER 0x00402BD0
        undefined4 EntityState::angleToRotationFrameIndex(int angleDegrees)
        {
            if (angleDegrees <= 5) {
                if (angleDegrees <= -50) {
                    return 0;
                }
                if (angleDegrees <= -35) {
                    return 1;
                }
                if (angleDegrees <= -17) {
                    return 2;
                }
                if (angleDegrees <= -5) {
                    return 3;
                }
            }
            else {
                if (angleDegrees <= 20) {
                    return 5;
                }
                if (angleDegrees <= 35) {
                    return 6;
                }
                if (angleDegrees <= 50) {
                    return 7;
                }
                if (angleDegrees <= 90) {
                    return 8;
                }
            }
            return 4;
        }

    }
}
}
