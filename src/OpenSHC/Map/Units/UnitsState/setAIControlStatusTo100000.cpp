#include "OpenSHC/Map/Units/UnitsState.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00537EE0
        void UnitsState::setAIControlStatusTo100000()
        {
            if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[1] == -1) {
                DAT_GameState::instance.playerDataArray[1].aiControlStatusRelated = 100000;
            }
            if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[2] == -1) {
                DAT_GameState::instance.playerDataArray[2].aiControlStatusRelated = 100000;
            }
            if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[3] == -1) {
                DAT_GameState::instance.playerDataArray[3].aiControlStatusRelated = 100000;
            }
            if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[4] == -1) {
                DAT_GameState::instance.playerDataArray[4].aiControlStatusRelated = 100000;
            }
            if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[5] == -1) {
                DAT_GameState::instance.playerDataArray[5].aiControlStatusRelated = 100000;
            }
            if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[6] == -1) {
                DAT_GameState::instance.playerDataArray[6].aiControlStatusRelated = 100000;
            }
            if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[7] == -1) {
                DAT_GameState::instance.playerDataArray[7].aiControlStatusRelated = 100000;
            }
            if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[8] == -1) {
                DAT_GameState::instance.playerDataArray[8].aiControlStatusRelated = 100000;
            }
        }

    }
}
}
