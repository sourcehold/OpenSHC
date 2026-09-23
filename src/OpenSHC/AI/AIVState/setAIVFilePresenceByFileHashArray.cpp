#include "../AIVState.func.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace AI {

    // an AIV is only usable in multiplayer if all players have the same file
    // FUNCTION: STRONGHOLDCRUSADER 0x004ECDB0
    void AIVState::setAIVFilePresenceByFileHashArray(int unused)
    {
        if (DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SKIRMISH_SINGLE_PLAYER) {
            for (int aiIndex = 0; aiIndex < 16; ++aiIndex) {
                for (int castleID = 0; castleID < 8; ++castleID) {
                    this->aivFilePresent[aiIndex][castleID] = 1;
                }
            }
            return;
        }
        for (int aiIndex = 0; aiIndex < 16; ++aiIndex) {
            for (int castleID = 0; castleID < 8; ++castleID) {
                int hash = -1;
                this->aivFilePresent[aiIndex][castleID] = 1;
                for (int player = 1; player < 9; ++player) {
                    if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[player] == -1) {
                        continue;
                    }
                    // the received hashes use the same layout as aivFileHash
                    if (hash == -1) {
                        hash = ((int*)this->receivedAIVFileHash[player])[aiIndex * 8 + castleID];
                        if (hash == -1) {
                            this->aivFilePresent[aiIndex][castleID] = 0;
                            break;
                        }
                    } else if (hash != ((int*)this->receivedAIVFileHash[player])[aiIndex * 8 + castleID]) {
                        this->aivFilePresent[aiIndex][castleID] = 0;
                        break;
                    }
                }
                if (hash == -1) {
                    this->aivFilePresent[aiIndex][castleID] = 0;
                }
            }
        }
    }

}
}
