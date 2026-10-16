#include "../../Synchrony.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/MSVC_SecurityCookie.hpp"

namespace OpenSHC {
namespace Synchrony {

    using DE::SHCDE::eTextSections;
    using Game::GameMode;
    using UI::Enums::MenuModalType;
    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x00490690
    void GameSynchronyState::receiveAllTransmittedCommands()
    {
        char cVar1;
        uint _playerID;
        int* piVar2;
        char* pcVar3;
        BOOLEnum BVar4;
        uint _sentByPlayerID;
        int iVar5;
        char* pcVar6;
        char acStack_68[100];
        uint local_4;
        local_4 = MSVC_SecurityCookie::instance ^ (uint)acStack_68;
        this->lastCommandReceiveTime = timeGetTime();
        /*
          this is the main packet reading loop in multiplayer
         */
        if (this->currentGameMode != Game::GM_SOLITARY) {
            while (true) {
                if ((this->currentGameMode == Game::GM_SKIRMISH_SINGLE_PLAYER)
                    || (this->DPLAYX_4A == (IDirectPlay4A*)0x0))
                    goto LAB_00490905;
                this->DPLAY_ReceiveDataSize = 61000;
                /*
                  Receive(lpidFrom, lpidTo, dwFlags, lpData, lpdwDataSize)   DPRECEIVE_ALL = 1
                 */
                this->DPLAYX_SendAndReceiveREsult = this->DPLAYX_4A->Receive((LPDPID)&this->DPLAYX_ReceivedPlayerID, (LPDPID)&this->DPLAY_ToID, DPRECEIVE_ALL, &this->DPLAY_ReceiveData, (DWORD*)&this->DPLAY_ReceiveDataSize);
                if ((this->DPLAYX_SendAndReceiveREsult == -0x7ffffff6)
                    || (this->DPLAYX_SendAndReceiveREsult == -0x7788ff42))
                    goto LAB_00490905;
                if (this->DPLAYX_SendAndReceiveREsult)
                    break;
                if (!this->DPLAYX_ReceivedPlayerID) {
                    /*
                      received system message
                     */
                    if ((*(uint*)&this->DPLAY_ReceiveData) != 3) {
                        if ((*(uint*)&this->DPLAY_ReceiveData) == 5) {
                            this->kickDueToLagStatusUnk = 0x3d;
                            _playerID = MACRO_CALL_MEMBER(
                                Synchrony::GameSynchronyState_Func::translateMultiplayerIDsIntoPlayerIDs,
                                this)((*(uint*)((char*)&this->DPLAY_ReceiveData + 8)));
                            MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::removePlayerFromLobby, this)(
                                _playerID);
                        } else if ((*(uint*)&this->DPLAY_ReceiveData) != 49) {
                            if ((*(uint*)&this->DPLAY_ReceiveData) == 257) {
                                this->isHost = TRUE;
                                this->DAT_HashCountdown = 2;
                                this->timeSkirmishGameStart = timeGetTime();
                                piVar2 = this->DAT_PlayerMatchTimes;
                                iVar5 = 9;
                                do {
                                    piVar2[-9] = 0;
                                    *piVar2 = 0;
                                    piVar2 = piVar2 + 1;
                                    iVar5 = iVar5 + -1;
                                } while (iVar5);
                                /*
                                  added by script: "You are now Host"
                                 */
                                pcVar3 = MACRO_CALL_MEMBER(
                                    Text::TextManager_Func::getTextStringInGroupAtOffset,
                                    DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_MULTIPLAYER_CONNECTION, 0x3c);
                                pcVar6 = this->receivedChatMessage;
                                do {
                                    cVar1 = *pcVar3;
                                    *pcVar6 = cVar1;
                                    pcVar3 = pcVar3 + 1;
                                    pcVar6 = pcVar6 + 1;
                                } while (cVar1 != '\0');
                                MACRO_CALL_MEMBER(
                                    Synchrony::GameSynchronyState_Func::addChatMessageToDisplayList, this)(
                                    this->currentPlayerSlotID, 0);
                                BVar4 = MACRO_CALL_MEMBER(
                                    Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)();
                                if (!BVar4) {
                                    if (DAT_MenuModalComposition1::instance.activeModalDialogID
                                        == UI::Enums::MMT_ROUNDTABLE) {
                                        DAT_MenuModalComposition1::instance.activeModalDialogID
                                            = UI::Enums::MMT_NONE;
                                    }
                                    MACRO_CALL_MEMBER(
                                        Synchrony::GameSynchronyState_Func::reorderTeamsAndPositions, this)();
                                }
                            } else {
                                MACRO_CALL(OS_Func::_sprintf)(
                                    acStack_68, "DP SYS Message: %x", (*(uint*)&this->DPLAY_ReceiveData));
                            }
                        }
                    }
                } else if (this->DPLAYX_ReceivedPlayerID != this->DPLAYX_PlayerHandle) {
                    if (this->DPLAY_ReceiveData.packet.commandProtocol == 125) {
                        /*
                          new meaning!
                         */
                        *(uint*)&this->DPLAY_ReceiveData = (*(uint*)&this->DPLAY_ReceiveData >> 8)
                            | ((uint)(uchar)this->DPLAY_ReceiveData.packet.payload[0] << 24);
                        MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::decompressTooLongPacketData,
                            this)(this->DPLAY_ReceiveData.packet.payload + 1,
                            (byte*)((int)(this->DPLAY_ReceiveData.packet.payload)));
                    }
                    this->receivedCommandMapTimeInTicks = 0;
                    MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::moveLowerThreeBytesIntoParam2,
                        DAT_LowLevelMemory::ptr)((void*)((int)&this->DPLAY_ReceiveData + 1),
                        (void*)((int)(&this->receivedCommandMapTimeInTicks)));
                    if (126 <= (char)this->DPLAY_ReceiveData.packet.commandProtocol) {
                        MACRO_CALL_MEMBER(
                            Synchrony::GameSynchronyState_Func::computeAndSetLatencyInformation, this)();
                    } else if ((char)this->DPLAY_ReceiveData.packet.commandProtocol < 2) {
                        MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::processSyncPacket, this)(
                            (int)(char)this->DPLAY_ReceiveData.packet.commandProtocol);
                    } else {
                        this->packetsReceived = this->packetsReceived + 1;
                        MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::scheduleReceivedCommand,
                            this)((Commands::GameCommandType)this->DPLAY_ReceiveData.packet.commandProtocol,
                            this->DPLAYX_ReceivedPlayerID, this->receivedCommandMapTimeInTicks,
                            (void*)((int)&this->DPLAY_ReceiveData + 4));
                    }
                }
                if (this->currentGameMode == Game::GM_SOLITARY) {
                    ;
                }
            }
            MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::handleUnexpectedDPlayXResult, this)();
        }
    LAB_00490905:;
    }

}
}
