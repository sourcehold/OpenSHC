#include "../GameStateStructures.func.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Game {

    // FUNCTION: STRONGHOLDCRUSADER 0x00459700
    int GameStateStructures::findAITeamMate(int playerID)
    {
        for (int teamMateID = 0; teamMateID < 9; ++teamMateID) {
            if (teamMateID != playerID && DAT_GameSynchronyState::instance.currentAIArray[teamMateID] != 0
                && this->mapAndTime.playerTeams[playerID] == this->mapAndTime.playerTeams[teamMateID]) {
                return teamMateID;
            }
        }
        return 0;
    }

}
}
