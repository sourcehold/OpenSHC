#include "../DirectionAlgorithmState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        // FUNCTION: STRONGHOLDCRUSADER 0x004092C0
        int DirectionAlgorithmState::computeHealthPercentage(int health, int maxHealth)
        {
            if (maxHealth == 0) {
                return 100;
            }
            return (health * 100) / maxHealth;
        }

    }
}
}
