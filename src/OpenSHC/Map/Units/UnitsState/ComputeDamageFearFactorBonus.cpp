#include "../UnitsState.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x005311F0
        int UnitsState::computeDamageFearFactorBonus(int damage, int playerID)
        {
            return ((DAT_GameState::instance.playerDataArray[playerID].fearFactorLevel + 20) * damage * 5) / 100;
        }

    }
}
}
