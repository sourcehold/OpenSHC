#include "../../Synchrony.func.hpp"
#include "../GameSynchronyState.func.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x00486A70
    int GameSynchronyState::getLordTypeForPlayer(int playerID)
    {
        if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[playerID] == -1) {
            switch (DAT_GameState::instance.playerDataArray[playerID].aiType) {
            case AI::AIT_RAT:
            case AI::AIT_SNAKE:
            case AI::AIT_PIG:
            case AI::AIT_WOLF:
            case AI::AIT_RICHARD:
            case AI::AIT_FREDERICK:
            case AI::AIT_PHILIPP:
            case AI::AIT_SHERIFF:
            case AI::AIT_MARSHAL:
            case AI::AIT_ABBOT:
                return 0;
            default:
                return 1;
            }
        }
        return DAT_GameCore::instance.selectedLordTypes[playerID];
    }

}
}
