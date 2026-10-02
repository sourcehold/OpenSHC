#include "../Chat.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Text/UserTextHandler.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_UserTextHandlerState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::Commands::GameCommandType;
        using OpenSHC::UI::Enums::MenuModalType;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
         */
        /*
          WARNING: Enum "DPERRInt": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x0048F590
        void Chat::MenuItemActionHandler_Chat_MostButtons(int param_1, ...)
        {
            char cVar1;
            char* pcVar2;
            char* pcVar3;
            int iVar4;
            if (param_1 < 0) {
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[0] = 0;
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[1] = 0;
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[2] = 0;
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[3] = 0;
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[4] = 0;
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[5] = 0;
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[6] = 0;
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[7] = 0;
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[8] = 0;
                *(undefined4*)((int)DAT_GameSynchronyState::ptr + param_1 * -4 + 0x109264) = 1;
                DAT_GameSynchronyState::instance
                    .DAT_ChatMessageReceiverArray[DAT_GameSynchronyState::instance.currentPlayerSlotID] = 1;
            }
            switch (param_1) {
            case 0x1f:
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[0] = 1;
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[1] = 1;
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[2] = 1;
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[3] = 1;
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[4] = 1;
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[5] = 1;
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[6] = 1;
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[7] = 1;
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[8] = 1;
                DAT_GameSynchronyState::instance
                    .DAT_ChatMessageReceiverArray[DAT_GameSynchronyState::instance.currentPlayerSlotID] = 1;
                return;
            case 0x20:
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[0] = 0;
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[1] = 0;
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[2] = 0;
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[3] = 0;
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[4] = 0;
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[5] = 0;
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[6] = 0;
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[7] = 0;
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[8] = 0;
                DAT_GameSynchronyState::instance
                    .DAT_ChatMessageReceiverArray[DAT_GameSynchronyState::instance.currentPlayerSlotID] = 1;
                return;
            case 0x21:
                pcVar2 = MACRO_CALL_MEMBER(
                    OpenSHC::Text::UserTextHandler_Func::getCurrentText, DAT_UserTextHandlerState::ptr)();
                pcVar3 = pcVar2;
                do {
                    cVar1 = *pcVar3;
                    pcVar3 = pcVar3 + 1;
                } while (cVar1 != '\0');
                iVar4 = 0;
                if (0 < (int)pcVar3 - (int)(pcVar2 + 1)) {
                    while (pcVar2[iVar4] == ' ') {
                        iVar4 = iVar4 + 1;
                        if ((int)pcVar3 - (int)(pcVar2 + 1) <= iVar4) {
                            DAT_GameSynchronyState::instance
                                .DAT_ChatMessageReceiverArray[DAT_GameSynchronyState::instance.currentPlayerSlotID] = 1;
                        }
                    }
                    DAT_GameSynchronyState::instance.DAT_ChatTauntOrMessage = 0;
                    MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                        DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_TAUNT_OR_CHAT);
                    goto switchD_0048f603_caseD_22;
                }
                break;
            case 0x22:
            switchD_0048f603_caseD_22:
                MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                    DAT_MenuModalComposition1::ptr)(OpenSHC::UI::Enums::MMT_NONE, FALSE);
                DAT_GameSynchronyState::instance
                    .DAT_ChatMessageReceiverArray[DAT_GameSynchronyState::instance.currentPlayerSlotID] = 1;
                return;
            case 0x23:
                iVar4 = DAT_GameState::instance.mapAndTime
                            .playerTeams[DAT_GameSynchronyState::instance.currentPlayerSlotID];
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[0] = 0;
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[8] = 0;
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[1]
                    = (int)(DAT_GameState::instance.mapAndTime.playerTeams[1] == iVar4);
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[2]
                    = (int)(DAT_GameState::instance.mapAndTime.playerTeams[2] == iVar4);
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[3]
                    = (int)(DAT_GameState::instance.mapAndTime.playerTeams[3] == iVar4);
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[4]
                    = (int)(DAT_GameState::instance.mapAndTime.playerTeams[4] == iVar4);
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[5]
                    = (int)(DAT_GameState::instance.mapAndTime.playerTeams[5] == iVar4);
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[6]
                    = (int)(DAT_GameState::instance.mapAndTime.playerTeams[6] == iVar4);
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[7]
                    = (int)(DAT_GameState::instance.mapAndTime.playerTeams[7] == iVar4);
                if (DAT_GameState::instance.mapAndTime.playerTeams[8] == iVar4) {
                    DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[8] = 1;
                    DAT_GameSynchronyState::instance
                        .DAT_ChatMessageReceiverArray[DAT_GameSynchronyState::instance.currentPlayerSlotID] = 1;
                }
                break;
            case 0x45:
                MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                    DAT_MenuModalComposition1::ptr)(OpenSHC::UI::Enums::MMT_ALLIES, FALSE);
                if (DAT_GameCore::instance.genieVoiceActive != FALSE) {
                    /*
                      "Your allies"
                     */
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                        "Genie_11.wav");
                }
            }
            DAT_GameSynchronyState::instance
                .DAT_ChatMessageReceiverArray[DAT_GameSynchronyState::instance.currentPlayerSlotID] = 1;
        }

    }
}
}
