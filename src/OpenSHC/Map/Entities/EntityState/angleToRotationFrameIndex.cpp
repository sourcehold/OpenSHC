#include "../EntityState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        // FUNCTION: STRONGHOLDCRUSADER 0x00402BD0
        undefined4 EntityState::angleToRotationFrameIndex(int param_1)
        {
            if (param_1 <= 5) {
                if (param_1 <= -50) {
                    return 0;
                }
                if (param_1 <= -35) {
                    return 1;
                }
                if (param_1 <= -17) {
                    return 2;
                }
                if (param_1 <= -5) {
                    return 3;
                }
            } else {
                if (param_1 <= 20) {
                    return 5;
                }
                if (param_1 <= 35) {
                    return 6;
                }
                if (param_1 <= 50) {
                    return 7;
                }
                if (param_1 <= 90) {
                    return 8;
                }
            }
            return 4;
        }

    } // namespace Entities
} // namespace Map
} // namespace OpenSHC
