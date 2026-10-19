#include "../../Synchrony.func.hpp"

#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Synchrony {

    using Commands::GameCommandType;
    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x0048CB00
    void GameSynchronyState::checkGameSync()
    {
        int _currentHash = 0;
        int _currentMatchTime = 0;
        if (this->DAT_HashCountdown) {
            return;
        }
        this->DAT_GameHalted = 0;
        for (int _playerID = 1; _playerID < 9; ++_playerID) {
            if ((this->currentPlayerFullIDArray[_playerID] != -1) && (this->unknownPlayerInfo_03[_playerID] == 0)) {
                _currentHash = this->HASH_HashTotal[_playerID];
                _currentMatchTime = this->DAT_PlayerMatchTimes[_playerID];
                break;
            }
        }
        if (!DAT_GameSynchronyState::instance.isHost) {
            return;
        }
        if (this->flag_0xbec) {
            return;
        }
        for (int _playerID = 1; _playerID < 9; ++_playerID) {
            if ((this->currentPlayerFullIDArray[_playerID] != -1) && (this->unknownPlayerInfo_03[_playerID] == 0)) {
                if (this->HASH_HashTotal[_playerID] == 0) {
                    return;
                }
                if (this->DAT_PlayerMatchTimes[_playerID] < 10) {
                    return;
                }
            }
        }
        for (int _playerID = 1; _playerID < 9; ++_playerID) {
            if ((this->currentPlayerFullIDArray[_playerID] != -1) && (this->unknownPlayerInfo_03[_playerID] == 0)) {
                if (this->HASH_HashTotal[_playerID] == 0) {
                    return;
                }
                if ((this->DAT_PlayerMatchTimes[_playerID] == _currentMatchTime)
                    && (this->HASH_HashTotal[_playerID] != _currentHash)) {
                    // hash mismatch for the same game time
                    if (this->syncRelatedCountdown) {
                        this->syncRelatedCountdown = 0;
                        this->commandDelay = 30;
                    }
                    MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                        Commands::GCT_GAME_DESYNCUnk);
                    this->flag_0xbec = 1;
                    for (int _slot = 1; _slot < 9; ++_slot) {
                        this->receivedSyncStatusByPlayerUnk[_slot] = 0;
                        this->syncStatus10Related[_slot] = 0;
                    }
                    return;
                }
            }
        }
    }

}
}
