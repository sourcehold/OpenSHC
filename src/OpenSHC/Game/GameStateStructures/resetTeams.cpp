#include "../GameStateStructures.func.hpp"

#include "OpenSHC/Game/GameMode2.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"

namespace OpenSHC {
namespace Game {

    using OpenSHC::Game::GameMode2;

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00459640
    void GameStateStructures::resetTeams()
    {
        for (int playerID = 0; playerID < 9; playerID++) {
            this->mapAndTime.playerTeams[playerID] = playerID;
        }
        if ((DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_SKIRMISH_AND_MULTIPLAYER)
            && (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_EDITOR)) {
            for (int playerID = 5; playerID > 1; playerID--) {
                this->mapAndTime.playerTeams[playerID] = 9;
            }
        }
    }
}
}
