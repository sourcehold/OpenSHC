#include "../GameStateStructures.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Game {

    // FUNCTION: STRONGHOLDCRUSADER 0x004597D0
    BOOLEnum GameStateStructures::areActivePlayersMostlySameTeam()
    {
        int soloCount = 0;
        int soloTeam = -1;
        for (int playerID = 1; playerID < 9; ++playerID) {
            if ((DAT_GameSynchronyState::instance.currentAIArray[playerID] != 0
                    || DAT_GameSynchronyState::instance.currentPlayerFullIDArray[playerID] != -1)
                && DAT_GameState::instance.playerDataArray[playerID].lordKilledByPlayerID == 0) {
                if (soloTeam == -1) {
                    soloTeam = this->mapAndTime.playerTeams[playerID];
                    ++soloCount;
                } else if (this->mapAndTime.playerTeams[playerID] != soloTeam) {
                    ++soloCount;
                }
            }
        }
        return soloCount <= 1;
    }

}
}
