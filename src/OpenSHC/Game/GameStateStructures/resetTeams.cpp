#include "../GameStateStructures.func.hpp"

#include "OpenSHC/Game/GameMode2.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"

namespace OpenSHC {
namespace Game {

    // FUNCTION: STRONGHOLDCRUSADER 0x00459640
    void GameStateStructures::resetTeams()
    {
        for (int playerID = 0; playerID < 9; ++playerID) {
            this->mapAndTime.playerTeams[playerID] = playerID;
        }
        if (DAT_GameCore::instance.gameMode_2 != GM_SKIRMISH_AND_MULTIPLAYER
            && DAT_GameCore::instance.gameMode_2 != GM_EDITOR) {
            for (int playerID = 5; playerID > 1; playerID--) {
                this->mapAndTime.playerTeams[playerID] = 9;
            }
        }
    }

}
}
