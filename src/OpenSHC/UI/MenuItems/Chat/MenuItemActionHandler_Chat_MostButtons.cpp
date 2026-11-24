#include "../Chat.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Text/UserTextHandler.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_UserTextHandlerState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace Chat {

            // FUNCTION: STRONGHOLDCRUSADER 0x0048F590
            void MenuItemActionHandler_Chat_MostButtons(int buttonID, ...)
            {
                // one counter for all the loops (a counter per loop swaps the text scan's address registers)
                int i;
                // the player buttons (-1 to -8) address the next message to that one player only
                // both arms end in the sender's store below (a return in this arm builds the 1 from the 0 register)
                if (buttonID < 0) {
                    for (i = 0; i < countof(DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray); ++i) {
                        DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[i] = FALSE;
                    }
                    // the conditional, not -buttonID or abs() (both lose the match: -buttonID folds into the address)
                    DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[buttonID < 0 ? -buttonID : buttonID]
                        = TRUE;
                } else {
                    switch (buttonID) {
                    case 31:
                        // everyone
                        for (i = 0; i < countof(DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray); ++i) {
                            DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[i] = TRUE;
                        }
                        break;
                    case 32:
                        // nobody but the sender (no button of the chat menu passes 32)
                        for (i = 0; i < countof(DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray); ++i) {
                            DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[i] = FALSE;
                        }
                        break;
                    case 35: {
                        // the own team (before 33 as in the original; in number order the match is lost)
                        int const team = DAT_GameState::instance.mapAndTime
                                             .playerTeams[DAT_GameSynchronyState::instance.currentPlayerSlotID];
                        for (i = 0; i < countof(DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray); ++i) {
                            DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[i] = FALSE;
                        }
                        // the players' slots, 1 to 8
                        for (i = 1; i < countof(DAT_GameState::instance.mapAndTime.playerTeams); ++i) {
                            if (DAT_GameState::instance.mapAndTime.playerTeams[i] == team) {
                                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[i] = TRUE;
                            }
                        }
                        break;
                    }
                    case 33: {
                        // send, unless the message is empty or only spaces
                        char* const text = MACRO_CALL_MEMBER(
                            OpenSHC::Text::UserTextHandler_Func::getCurrentText, DAT_UserTextHandlerState::ptr)();
                        int const length = strlen(text);
                        for (i = 0; i < length; ++i) {
                            if (text[i] != ' ') {
                                // 0: the typed text (the taunt buttons store the taunt's number, 1 to 20)
                                DAT_GameSynchronyState::instance.DAT_ChatTauntOrMessage = 0;
                                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                                    DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_TAUNT_OR_CHAT);
                                MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                                    DAT_MenuModalComposition1::ptr)(OpenSHC::UI::Enums::MMT_NONE, FALSE);
                                break;
                            }
                        }
                        break;
                    }
                    case 34:
                        // close the dialog without sending
                        MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                            DAT_MenuModalComposition1::ptr)(OpenSHC::UI::Enums::MMT_NONE, FALSE);
                        break;
                    case 69:
                        // the allies dialog
                        MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                            DAT_MenuModalComposition1::ptr)(OpenSHC::UI::Enums::MMT_ALLIES, FALSE);
                        if (DAT_GameCore::instance.genieVoiceActive) {
                            // "Genie_11.wav": "Your allies"
                            MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                                SFX_YourAllies);
                        }
                        break;
                    }
                }
                // the sender always gets the message too
                DAT_GameSynchronyState::instance
                    .DAT_ChatMessageReceiverArray[DAT_GameSynchronyState::instance.currentPlayerSlotID] = TRUE;
            }

        }
    }
}
}
