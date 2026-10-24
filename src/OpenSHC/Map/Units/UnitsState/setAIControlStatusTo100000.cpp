#include "../UnitsState.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00537EE0
        void UnitsState::setAIControlStatusTo100000()
        {
            for (int i = 1; i < 9; i++) {
                if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[i] == -1) {
                    DAT_GameState::instance.playerDataArray[i].aiControlStatusRelated = 100000;
                }
            }
        }

    }
}
}
