#include "../../Synchrony.func.hpp"
#include "../GameSynchronyState.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x0047EA40
    int GameSynchronyState::countPlayersInSameTeam(int playerID)
    {
        int _count = 0;
        int _team = DAT_GameState::instance.mapAndTime.playerTeams[playerID];
        for (int _player = 1; _player < 9; ++_player) {
            if ((this->currentPlayerFullIDArray[_player] != -1)
                && (DAT_GameState::instance.mapAndTime.playerTeams[_player] == _team)) {
                ++_count;
            }
        }
        return _count;
    }

}
}
