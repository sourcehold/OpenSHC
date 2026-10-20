#include "../GameSynchronyState.func.hpp"

#include "OpenSHC/Game/GameMode.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

#include "string.h"

namespace OpenSHC {
namespace Synchrony {

    using Game::GameMode;

    // FUNCTION: STRONGHOLDCRUSADER 0x0047E8F0
    int GameSynchronyState::checkPlayerSetValid()
    {
        int _teamMemberCounts[9];
        int _someCounter = 0;
        int _validPlayerCount = 0;
        memset(_teamMemberCounts, 0, sizeof(_teamMemberCounts));
        for (int _somePlayerID = 1; _somePlayerID < 9; ++_somePlayerID) {
            if (this->currentPlayerFullIDArray[_somePlayerID] != -1) {
                ++_someCounter;
            }
            // no human player and no AI in this slot
            if ((this->currentPlayerFullIDArray[_somePlayerID] == -1) && (this->currentAIArray[_somePlayerID] == 0)) {
                continue;
            }
            _teamMemberCounts[DAT_GameState::instance.mapAndTime.playerTeams[_somePlayerID]]
                = _teamMemberCounts[DAT_GameState::instance.mapAndTime.playerTeams[_somePlayerID]] + 1;
            if (DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SKIRMISH_SINGLE_PLAYER) {
                ++_someCounter;
            }
        }
        if (_someCounter < 2) {
            return 0;
        }
        for (int _somePlayerID = 1; _somePlayerID < 9; ++_somePlayerID) {
            if (_teamMemberCounts[_somePlayerID] != 0) {
                ++_validPlayerCount;
                if (2 < _teamMemberCounts[_somePlayerID]) {
                    return 0;
                }
            }
        }
        return _validPlayerCount;
    }

}
}
