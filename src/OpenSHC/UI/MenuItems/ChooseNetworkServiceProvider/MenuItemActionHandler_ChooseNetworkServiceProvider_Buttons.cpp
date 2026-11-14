// disable deprecation warnings for strcpy
#pragma warning(disable : 4996)

#include "../ChooseNetworkServiceProvider.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Input/MouseState.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Synchrony.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Text/UserTextHandler.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/UI/ChooseNetworkServiceProvider/ChooseNetworkServiceProviderButtonActions.hpp"
#include "OpenSHC/UI/Enums/BuildingsAndStatusMenuTabType.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_UserTextHandlerState.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"
#include "OpenSHC/Globals/Menu_LobbyMenu.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x004909E0
        void ChooseNetworkServiceProvider::MenuItemActionHandler_ChooseNetworkServiceProvider_Buttons(
            ChooseNetworkServiceProviderButtonActions action, ...)
        {
            // the cases in the original's block order
            switch (action) {
            case OpenSHC::UI::ChooseNetworkServiceProvider::CNSPBA_NEXT_IP_ADDRESSUnk:
                MACRO_CALL_MEMBER(
                    OpenSHC::Text::UserTextHandler_Func::setTextEntryAndUpdateCursor, DAT_UserTextHandlerState::ptr)(
                    5, DAT_GameSynchronyState::instance.ipRelatedArray[DAT_GameSynchronyState::instance.ipArrayIndex]);
                ++DAT_GameSynchronyState::instance.ipArrayIndex;
                if (DAT_GameSynchronyState::instance.ipArrayIndex
                    >= countof(DAT_GameSynchronyState::instance.ipRelatedArray)) {
                    DAT_GameSynchronyState::instance.ipArrayIndex = 0;
                }
                return;
            case OpenSHC::UI::ChooseNetworkServiceProvider::CNSPBA_GAMESPY_ARCADEUnk:
                if (DAT_GameSynchronyState::instance.gameSpyArcadeAvailable != 0) {
                    DAT_WindowAndDirectDraw::instance.postWindowCloseMessage = 1;
                    DAT_GameSynchronyState::instance.openOnClose = TRUE;
                }
                return;
            case OpenSHC::UI::ChooseNetworkServiceProvider::CNSPBA_SCROLL_DOWNUnk:
                if (DAT_GameSynchronyState::instance.scrollBarItemOffset
                    < DAT_GameSynchronyState::instance.scrollBarItemCount - 4) {
                    ++DAT_GameSynchronyState::instance.scrollBarItemOffset;
                }
                return;
            case OpenSHC::UI::ChooseNetworkServiceProvider::CNSPBA_SCROLL_UPUnk:
                if (DAT_GameSynchronyState::instance.scrollBarItemOffset > 0) {
                    --DAT_GameSynchronyState::instance.scrollBarItemOffset;
                }
                return;
            case OpenSHC::UI::ChooseNetworkServiceProvider::CNSPBA_JOIN_GAME:
                DAT_GameSynchronyState::instance.isHost = FALSE;
                DAT_GameSynchronyState::instance.kickedAtTime = 0;
                // remember a new address: in the first empty slot, or at the end after dropping the oldest
                if (DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_GRANARY_OR_MPMENU_TCPIP
                    && strlen(MACRO_CALL_MEMBER(
                           OpenSHC::Text::UserTextHandler_Func::getTextArrayPointer, DAT_UserTextHandlerState::ptr)(5))
                        != 0) {
                    OpenSHC::WindowsHelper::Enums::BOOLEnum known = FALSE;
                    for (int entry = 0; entry < countof(DAT_GameSynchronyState::instance.ipRelatedArray); ++entry) {
                        if (MACRO_CALL(OpenSHC::OS_Func::__stricmp)(
                                MACRO_CALL_MEMBER(OpenSHC::Text::UserTextHandler_Func::getTextArrayPointer,
                                    DAT_UserTextHandlerState::ptr)(5),
                                DAT_GameSynchronyState::instance.ipRelatedArray[entry])
                            == 0) {
                            known = TRUE;
                            break;
                        }
                    }
                    if (!known) {
                        OpenSHC::WindowsHelper::Enums::BOOLEnum stored = FALSE;
                        for (int slot = 0; slot < countof(DAT_GameSynchronyState::instance.ipRelatedArray); ++slot) {
                            if (strlen(DAT_GameSynchronyState::instance.ipRelatedArray[slot]) == 0) {
                                strcpy(DAT_GameSynchronyState::instance.ipRelatedArray[slot],
                                    MACRO_CALL_MEMBER(OpenSHC::Text::UserTextHandler_Func::getTextArrayPointer,
                                        DAT_UserTextHandlerState::ptr)(5));
                                stored = TRUE;
                                break;
                            }
                        }
                        if (!stored) {
                            // memcpy and memset compile to the original's dword moves
                            for (int row = 0; row < countof(DAT_GameSynchronyState::instance.ipRelatedArray) - 1;
                                ++row) {
                                memcpy(DAT_GameSynchronyState::instance.ipRelatedArray[row],
                                    DAT_GameSynchronyState::instance.ipRelatedArray[row + 1],
                                    sizeof(DAT_GameSynchronyState::instance.ipRelatedArray[row]));
                            }
                            memset(DAT_GameSynchronyState::instance
                                       .ipRelatedArray[countof(DAT_GameSynchronyState::instance.ipRelatedArray) - 1],
                                0,
                                sizeof(DAT_GameSynchronyState::instance
                                        .ipRelatedArray[countof(DAT_GameSynchronyState::instance.ipRelatedArray) - 1]));
                            strcpy(DAT_GameSynchronyState::instance
                                       .ipRelatedArray[countof(DAT_GameSynchronyState::instance.ipRelatedArray) - 1],
                                MACRO_CALL_MEMBER(OpenSHC::Text::UserTextHandler_Func::getTextArrayPointer,
                                    DAT_UserTextHandlerState::ptr)(5));
                        }
                    }
                }
                if (MACRO_CALL_MEMBER(
                        OpenSHC::Synchrony::GameSynchronyState_Func::initializeDirectPlayAndCreateOrJoinSession,
                        DAT_GameSynchronyState::ptr)(FALSE)
                    >= 0) {
                    DAT_GameSynchronyState::instance.unkEnumerationRelatedBool = false;
                    DAT_GameSynchronyState::instance.scrollBarIndex = -1;
                    DAT_GameSynchronyState::instance.scrollBarItemOffset = 0;
                    MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::restartDPlaySessionEnumeration,
                        DAT_GameSynchronyState::ptr)(FALSE);
                    MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                        DAT_MenuModalComposition1::ptr)(OpenSHC::UI::Enums::MMT_FINDING_NETWORK_SESSIONS, FALSE);
                }
                MACRO_CALL_MEMBER(OpenSHC::Input::MouseState_Func::resetMouseState2, DAT_MouseState::ptr)();
                return;
            case OpenSHC::UI::ChooseNetworkServiceProvider::CNSPBA_HOST_GAME:
                DAT_GameSynchronyState::instance.isHost = TRUE;
                DAT_GameSynchronyState::instance.kickedAtTime = 0;
                if (MACRO_CALL_MEMBER(
                        OpenSHC::Synchrony::GameSynchronyState_Func::initializeDirectPlayAndCreateOrJoinSession,
                        DAT_GameSynchronyState::ptr)(FALSE)
                    >= 0) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                        DAT_MenuModalComposition1::ptr)(OpenSHC::UI::Enums::MMT_NONE, FALSE);
                    DAT_GameSynchronyState::instance.field_0x106ee4 = 1;
                    DAT_GameCore::instance.menuTabToSwitchTo.tabType = OpenSHC::UI::Enums::BASMTT_NONE;
                    MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                        OpenSHC::UI::Enums::MVT_LOBBY_MENU, 0);
                    MACRO_CALL(OpenSHC::Synchrony_Func::InitSkirmishLobbyData)();
                    Menu_LobbyMenu::instance.thousand = 0;
                    MACRO_CALL(OpenSHC::OS_Func::_memset)(DAT_GameSynchronyState::instance.DAT_PlayerNames, 0,
                        sizeof(DAT_GameSynchronyState::instance.DAT_PlayerNames));
                    strcpy(DAT_GameSynchronyState::instance.DAT_PlayerNames[1],
                        MACRO_CALL_MEMBER(OpenSHC::Text::UserTextHandler_Func::getTextArrayPointer,
                            DAT_UserTextHandlerState::ptr)(0));
                    MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::waitForMultiplayerHost,
                        DAT_GameSynchronyState::ptr)();
                    MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                        DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_ASK_FOR_SLOT_ASSIGNMENT);
                }
                MACRO_CALL_MEMBER(OpenSHC::Input::MouseState_Func::resetMouseState2, DAT_MouseState::ptr)();
                return;
            case OpenSHC::UI::ChooseNetworkServiceProvider::CNSPBA_EXIT:
            case OpenSHC::UI::ChooseNetworkServiceProvider::CNSPBA_EXIT_ALTUnk:
                MACRO_CALL_MEMBER(
                    OpenSHC::Synchrony::GameSynchronyState_Func::disconnectDPlay, DAT_GameSynchronyState::ptr)();
                DAT_GameSynchronyState::instance.kickedAtTime = 0;
                MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                    DAT_MenuModalComposition1::ptr)(OpenSHC::UI::Enums::MMT_NONE, FALSE);
                MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    OpenSHC::UI::Enums::MVT_MAIN_MENU, 0);
                MACRO_CALL_MEMBER(OpenSHC::Input::MouseState_Func::resetMouseState2, DAT_MouseState::ptr)();
                return;
            }
        }

    }
}
}
