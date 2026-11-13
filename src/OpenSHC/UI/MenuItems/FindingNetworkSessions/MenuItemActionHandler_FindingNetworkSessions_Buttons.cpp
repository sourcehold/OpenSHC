#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Input/MouseState.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Synchrony.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/UI/MenuItems/FindingNetworkSessions.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/DirectPlay/EnumSessionsFlagsEnum.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DPLAY_CurrentSessionGUID.hpp"
#include "OpenSHC/Globals/GUID_APP.hpp"
#include "OpenSHC/Globals/Menu_LobbyMenu.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace FindingNetworkSessions {

            // FUNCTION: STRONGHOLDCRUSADER 0x00490D90
            void __cdecl MenuItemActionHandler_FindingNetworkSessions_Buttons(
                FindingNetworkSessions_ButtonParameters param_1, ...)
            {
                switch ((int)param_1) {
                case -2:
                    if (DAT_GameSynchronyState::instance.scrollBarItemOffset
                        < DAT_GameSynchronyState::instance.DPLAY_SessionsCount - 10) {
                        DAT_GameSynchronyState::instance.scrollBarItemOffset += 1;
                    }
                    break;
                case -1:
                    if (DAT_GameSynchronyState::instance.scrollBarItemOffset > 0) {
                        DAT_GameSynchronyState::instance.scrollBarItemOffset -= 1;
                    }
                    break;
                case -10000:
                case 3: {
                    DPSESSIONDESC2 description;
                    MACRO_CALL(OpenSHC::OS_Func::_memset)(&description, 0, sizeof(description));
                    description.dwSize = sizeof(description);
                    description.guidApplication = GUID_APP::instance;
                    if (DAT_GameSynchronyState::instance.DPLAYX_4A != NULL) {
                        DAT_GameSynchronyState::instance.DPLAYX_4A->EnumSessions(&description, 0,
                            MACRO_CALL(OpenSHC::Synchrony_Func::EnumSessionsCallback_addSession_async), NULL,
                            OpenSHC::DirectPlay::ESFE_ASYNC_ENUMERATION_STOP);
                    }
                    MACRO_CALL_MEMBER(
                        OpenSHC::Synchrony::GameSynchronyState_Func::disconnectDPlay, DAT_GameSynchronyState::ptr)();
                    MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::initializeMultiplayerLobby,
                        DAT_GameSynchronyState::ptr)();
                    MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                        DAT_MenuModalComposition1::ptr)(OpenSHC::UI::Enums::MMT_CHOOSE_NETWORK_SERVICE_PROVIDER, FALSE);
                    break;
                }
                case OpenSHC::UI::Multiplayer::FNSBP_JOIN:
                    if (DAT_GameSynchronyState::instance.scrollBarIndex == -1) {
                        break;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::fetchSessionGUID,
                        DAT_GameSynchronyState::ptr)(&DPLAY_CurrentSessionGUID::instance);
                    if (MACRO_CALL_MEMBER(
                            OpenSHC::Synchrony::GameSynchronyState_Func::initializeDirectPlayAndCreateOrJoinSession,
                            DAT_GameSynchronyState::ptr)(TRUE)
                        >= 0) {
                        DPSESSIONDESC2 description;
                        MACRO_CALL(OpenSHC::OS_Func::_memset)(&description, 0, sizeof(description));
                        description.dwSize = sizeof(description);
                        description.guidApplication = GUID_APP::instance;
                        DAT_GameSynchronyState::instance.DPLAYX_4A->EnumSessions(&description, 0,
                            MACRO_CALL(OpenSHC::Synchrony_Func::EnumSessionsCallback_addSession_async), NULL,
                            OpenSHC::DirectPlay::ESFE_ASYNC_ENUMERATION_STOP);
                        MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                            DAT_MenuModalComposition1::ptr)(OpenSHC::UI::Enums::MMT_NONE, FALSE);
                        DAT_GameSynchronyState::instance.field_0x106ee4 = 1;
                        DAT_GameCore::instance.menuTabToSwitchTo.tabType = 0;
                        MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                            OpenSHC::UI::Enums::MVT_LOBBY_MENU, 0);
                        MACRO_CALL(OpenSHC::Synchrony_Func::InitSkirmishLobbyData)();
                        Menu_LobbyMenu::instance.thousand = 0;
                        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::waitForMultiplayerHost,
                            DAT_GameSynchronyState::ptr)();
                        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                            DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_ASK_FOR_SLOT_ASSIGNMENT);
                        MACRO_CALL_MEMBER(OpenSHC::Input::MouseState_Func::resetMouseState2, DAT_MouseState::ptr)();
                    } else {
                        DPSESSIONDESC2 description;
                        MACRO_CALL(OpenSHC::OS_Func::_memset)(&description, 0, sizeof(description));
                        description.dwSize = sizeof(description);
                        description.guidApplication = GUID_APP::instance;
                        if (DAT_GameSynchronyState::instance.DPLAYX_4A != NULL) {
                            DAT_GameSynchronyState::instance.DPLAYX_4A->EnumSessions(&description, 0,
                                MACRO_CALL(OpenSHC::Synchrony_Func::EnumSessionsCallback_addSession_async), NULL,
                                OpenSHC::DirectPlay::ESFE_ASYNC_ENUMERATION_STOP);
                        }
                        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::disconnectDPlay,
                            DAT_GameSynchronyState::ptr)();
                        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::initializeMultiplayerLobby,
                            DAT_GameSynchronyState::ptr)();
                        MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                            DAT_MenuModalComposition1::ptr)(
                            OpenSHC::UI::Enums::MMT_CHOOSE_NETWORK_SERVICE_PROVIDER, FALSE);
                        MACRO_CALL_MEMBER(OpenSHC::Input::MouseState_Func::resetMouseState2, DAT_MouseState::ptr)();
                    }
                    break;
                }
            }

        }
    }
}
}
