#include "../../Synchrony.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"

namespace OpenSHC {
namespace Synchrony {

    using Commands::GameCommandType;
    using Game::GameMode;
    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x00490480
    void GameSynchronyState::checkMultiplayerLaggingPlayers()
    {
        int* piVar3;
        ConnectionLagInfo* piVar6;
        ConnectionLagInfo* pDVar7;
        int _playerID;
        bool _anyIsZero;
        this->currentGameModeCopy_SEC_Section1106 = this->currentGameMode;
        if ((this->currentGameMode == Game::GM_SOLITARY)
            || (this->currentGameMode == Game::GM_SKIRMISH_SINGLE_PLAYER)) {
            this->commandDelay = 0;
        }
        if (this->shouldSendAnnouncementUnk) {
            MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, this)(
                (Commands::GameCommandType)Commands::M_MAPPER_HEALER);
            this->shouldSendAnnouncementUnk = 0;
        }
        if ((!this->syncStatus) && (!this->saveRelated)) {
            BOOLEnum BVar1 = MACRO_CALL_MEMBER(Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)();
            if (BVar1) {
                int iVar2 = 0;
                piVar6 = &this->connectionLagInfoArray[1];
                piVar3 = this->currentPlayerFullIDArray + 1;
                _anyIsZero = true;
                do {
                    /*
                      this code does three at a time
                     */
                    if (piVar3[-1] != -1 && iVar2 != this->currentPlayerSlotID && piVar6[-1].checkFor0 == 0) {
                        _anyIsZero = false;
                    }
                    if (*piVar3 != -1 && iVar2 + 1 != this->currentPlayerSlotID && !piVar6->checkFor0) {
                        _anyIsZero = false;
                    }
                    if (piVar3[1] != -1 && iVar2 + 2 != this->currentPlayerSlotID && piVar6[1].checkFor0 == 0) {
                        _anyIsZero = false;
                    }
                    iVar2 = iVar2 + 3;
                    piVar3 = piVar3 + 3;
                    piVar6 = piVar6 + 3;
                } while (iVar2 < 9);
                if (_anyIsZero) {
                    DWORD _now = timeGetTime();
                    _playerID = 0;
                    pDVar7 = &this->connectionLagInfoArray[0];
                    piVar3 = this->currentPlayerFullIDArray;
                    do {
                        if (*piVar3 != -1 && _playerID != this->currentPlayerSlotID && pDVar7->time) {
                            if (15000 < (int)(_now - pDVar7->time) && this->isHost && !this->laggingPlayerIDUnk) {
                                this->laggingPlayerIDUnk = _playerID;
                                this->DAT_GameCommandParam0 = _playerID;
                                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, this)(
                                    (Commands::GameCommandType)(Commands::GCT_SEND_RESYNC_TILEMAPDATA2
                                        | Commands::GCT_CHANGE_TAXES));
                            }
                            if (60000 < (int)(_now - pDVar7->time)) {
                                this->kickDueToLagStatusUnk = 62;
                                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::removePlayerFromLobby, this)(
                                    _playerID);
                            }
                        }
                        _playerID = _playerID + 1;
                        piVar3 = piVar3 + 1;
                        pDVar7 = pDVar7 + 9;
                    } while (_playerID < 9);
                }
            }
            DWORD _now2 = timeGetTime();
            if (1800 < (int)(_now2 - this->otherTime1)) {
                this->otherTime1 = _now2;
                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::sendSyncPacket126, this)();
            }
            if (180 <= (int)(_now2 - this->now2)
                && (this->now2 = _now2,
                    MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::sendSomeMultiplayerSyncMessageWithType, this)(
                        0),
                    0 < this->syncRelatedCountdown)) {
                this->syncRelatedCountdown = this->syncRelatedCountdown + -1;
            }
        }
        this->connectionLagInfoArray[0].time = 0;
        this->connectionLagInfoArray[1].time = 0;
        this->connectionLagInfoArray[2].time = 0;
        this->connectionLagInfoArray[3].time = 0;
        this->connectionLagInfoArray[4].time = 0;
        this->connectionLagInfoArray[5].time = 0;
        this->connectionLagInfoArray[6].time = 0;
        this->connectionLagInfoArray[7].time = 0;
        this->connectionLagInfoArray[8].time = 0;
    }

}
}
