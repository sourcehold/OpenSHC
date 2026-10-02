#include "../GameSynchronyState.func.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Synchrony {
    // FUNCTION: STRONGHOLDCRUSADER 0x0048CB00
    void GameSynchronyState::checkGameSync()
    {
        int referenceHash = 0;
        int referenceTime = 0;
        if (DAT_HashCountdown == 0) {
            DAT_GameHalted = 0;
            for (int player = 1; player < 9; ++player) {
                if (currentPlayerFullIDArray[player] != -1 && unknownPlayerInfo_03[player] == 0) {
                    referenceHash = HASH_HashTotal[player];
                    referenceTime = DAT_PlayerMatchTimes[player];
                    break;
                }
            }

            if (DAT_GameSynchronyState::instance.isHost && flag_0xbec == 0) {
                // Wait until every participating peer has supplied a usable sample.
                for (int player = 1; player < 9; ++player) {
                    if (currentPlayerFullIDArray[player] != -1 && unknownPlayerInfo_03[player] == 0) {
                        if (HASH_HashTotal[player] == 0 || DAT_PlayerMatchTimes[player] < 10) {
                            return;
                        }
                    }
                }

                for (int player = 1; player < 9; ++player) {
                    if (currentPlayerFullIDArray[player] != -1 && unknownPlayerInfo_03[player] == 0) {
                        if (HASH_HashTotal[player] == 0) {
                            return;
                        }
                        // Different advertised ticks are not a comparable state pair.
                        if (DAT_PlayerMatchTimes[player] == referenceTime && HASH_HashTotal[player] != referenceHash) {
                            if (syncRelatedCountdown != 0) {
                                syncRelatedCountdown = 0;
                                commandDelay = 30;
                            }
                            MACRO_CALL_MEMBER(GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                                OpenSHC::Commands::GCT_GAME_DESYNCUnk);
                            flag_0xbec = 1;
                            for (int slot = 1; slot < 9; ++slot) {
                                receivedSyncStatusByPlayerUnk[slot] = 0;
                                syncStatus10Related[slot] = 0;
                            }
                            return;
                        }
                    }
                }
            }
        }
    }

}
}
