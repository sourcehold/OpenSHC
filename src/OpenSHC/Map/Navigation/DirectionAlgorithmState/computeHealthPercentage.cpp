#include "../DirectionAlgorithmState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        // FUNCTION: STRONGHOLDCRUSADER 0x004092C0
        int DirectionAlgorithmState::computeHealthPercentage(int param_1, int param_2)
        {
            if (param_2 == 0) {
                return 100;
            }
            return (param_1 * 100) / param_2;
        }

    }
}
}
