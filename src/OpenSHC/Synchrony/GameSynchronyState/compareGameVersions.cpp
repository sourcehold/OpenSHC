#include "../../Synchrony.func.hpp"

#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/Text/UserTextHandler.func.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_UserTextHandlerState.hpp"
#include "OpenSHC/Globals/MSVC_SecurityCookie.hpp"

namespace OpenSHC {
namespace Synchrony {

    using Commands::GameCommandType;
    using DE::SHCDE::eTextSections;
    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x0048BD40
    void GameSynchronyState::compareGameVersions()
    {
        char cVar1;
        char* pcVar5;
        int* piVar6;
        int iVar7;
        char* pcVar8;
        int iVar9;
        int _gameVersion;
        int local_8c[9];
        char local_68[100];
        uint local_4;
        BOOLEnum BVar4 = this->flag_0x7aad8;
        local_4 = MSVC_SecurityCookie::instance ^ (uint)local_8c;
        iVar7 = 4294967295;
        _gameVersion = 0x7fffffff;
        this->flag_0x7aad8 = TRUE;
        iVar9 = 1;
        piVar6 = this->DAT_MultiplayerGameVersions;
        do {
            piVar6 = piVar6 + 1;
            if (piVar6[-0x1e8fa] != -1) {
                if (!piVar6[9]) {
                    this->flag_0x7aad8 = TRUE;
                    break;
                }
                if (iVar7 == -1) {
                    iVar7 = *piVar6;
                } else if (iVar7 != *piVar6) {
                    this->flag_0x7aad8 = FALSE;
                }
                if (*piVar6 < _gameVersion) {
                    _gameVersion = *piVar6;
                }
            }
            iVar9 = iVar9 + 1;
        } while (iVar9 < 9);
        if (!this->flag_0x7aad8) {
            if ((BVar4) && (_gameVersion < this->DAT_MultiplayerGameVersions[this->currentPlayerSlotID])) {
                /*
                  added by script: "Someone has an old version, please get him or her to   upgrade"
                 */
                pcVar5 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_MP_VERSION_CONTROL, 2);
                pcVar8 = this->receivedChatMessage;
                do {
                    cVar1 = *pcVar5;
                    *pcVar8 = cVar1;
                    pcVar5 = pcVar5 + 1;
                    pcVar8 = pcVar8 + 1;
                } while (cVar1 != '\0');
                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::addChatMessageToDisplayList, this)(
                    this->DAT_GameCommandParam0, 0);
                piVar6 = this->DAT_ChatMessageReceiverArray;
                iVar7 = 0;
                do {
                    int iVar2 = *piVar6;
                    *piVar6 = 0;
                    int iVar3 = this->currentPlayerFullIDArray[iVar9];
                    local_8c[iVar7] = iVar2;
                    if ((iVar3 != -1)
                        && (piVar6[-0x239f5] < this->DAT_MultiplayerGameVersions[this->currentPlayerSlotID])) {
                        *piVar6 = 1;
                    }
                    iVar7 = iVar7 + 1;
                    piVar6 = piVar6 + 1;
                } while (iVar7 < 9);
                this->DAT_ChatTauntOrMessage = 0;
                pcVar8 = MACRO_CALL_MEMBER(Text::UserTextHandler_Func::getCurrentText, DAT_UserTextHandlerState::ptr)();
                pcVar5 = local_68;
                do {
                    cVar1 = *pcVar8;
                    *pcVar5 = cVar1;
                    pcVar8 = pcVar8 + 1;
                    pcVar5 = pcVar5 + 1;
                } while (cVar1 != '\0');
                /*
                  added by script: "You have an old version, please upgrade to the latest   version"
                 */
                pcVar5 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_MP_VERSION_CONTROL, 1);
                MACRO_CALL_MEMBER(
                    Text::UserTextHandler_Func::setTextEntryAndUpdateCursor, DAT_UserTextHandlerState::ptr)(4, pcVar5);
                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, this)(Commands::GCT_TAUNT_OR_CHAT);
                MACRO_CALL_MEMBER(Text::UserTextHandler_Func::setTextEntryAndUpdateCursor,
                    DAT_UserTextHandlerState::ptr)(4, local_68);
                this->DAT_ChatMessageReceiverArray[0] = local_8c[0];
                this->DAT_ChatMessageReceiverArray[1] = local_8c[1];
                this->DAT_ChatMessageReceiverArray[2] = local_8c[2];
                this->DAT_ChatMessageReceiverArray[3] = local_8c[3];
                this->DAT_ChatMessageReceiverArray[4] = local_8c[4];
                this->DAT_ChatMessageReceiverArray[5] = local_8c[5];
                this->DAT_ChatMessageReceiverArray[6] = local_8c[6];
                this->DAT_ChatMessageReceiverArray[7] = local_8c[7];
                this->DAT_ChatMessageReceiverArray[8] = local_8c[8];
            }
            if (this->DAT_PlayerSlotArraySomeValue[this->currentPlayerSlotID] != 0) {
                this->DAT_PlayerSlotArraySomeValue[this->currentPlayerSlotID] = 0;
                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, this)(
                    Commands::GCT_HOST_ANNOUNCE_TEAMS_AND_POSITIONS);
            }
        };
    }

}
}
