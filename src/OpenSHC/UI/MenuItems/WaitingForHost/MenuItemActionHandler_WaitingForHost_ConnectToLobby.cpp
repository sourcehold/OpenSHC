#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Synchrony.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/UI/MenuItems/WaitingForHost.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/DirectPlay/EnumSessionsFlagsEnum.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"
#include "OpenSHC/wstring-literals.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DPLAY_CurrentSessionGUID.hpp"
#include "OpenSHC/Globals/GUID_APP.hpp"
#include "OpenSHC/Globals/Menu_LobbyMenu.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace WaitingForHost {

            // FUNCTION: STRONGHOLDCRUSADER 0x004914D0
            void __cdecl MenuItemActionHandler_WaitingForHost_ConnectToLobby()
            {
                DAT_GameSynchronyState::instance.scrollBarItemOffset = 0;
                if (DAT_GameSynchronyState::instance.multiplayerJoinStep == 0) {
                    if (MACRO_CALL_MEMBER(
                            OpenSHC::Synchrony::GameSynchronyState_Func::initializeDirectPlayAndCreateOrJoinSession,
                            DAT_GameSynchronyState::ptr)(FALSE)
                        >= 0) {
                        DAT_GameSynchronyState::instance.multiplayerJoinStep = 1;
                        DAT_GameSynchronyState::instance.unkEnumerationRelatedBool = false;
                        DAT_GameSynchronyState::instance.scrollBarIndex = -1;
                        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::restartDPlaySessionEnumeration,
                            DAT_GameSynchronyState::ptr)(FALSE);
                    }
                }
                if (DAT_GameSynchronyState::instance.multiplayerJoinStep != 1) {
                    return;
                }
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::restartDPlaySessionEnumeration,
                    DAT_GameSynchronyState::ptr)(TRUE);
                for (int i = 0; i < DAT_GameSynchronyState::instance.DPLAY_SessionsCount; ++i) {
                    // The wide string literal is the session name "Crusader"
                    if (MACRO_CALL(OpenSHC::OS_Func::__wcsicmp)(
                            u_Crusader_005a6f40, DAT_GameSynchronyState::instance.DPLAY_SessionNames[i])
                        != 0) {
                        continue;
                    }
                    DPLAY_CurrentSessionGUID::instance = *DAT_GameSynchronyState::instance.DPLAY_SessionGUIDs[i];
                    if (MACRO_CALL_MEMBER(
                            OpenSHC::Synchrony::GameSynchronyState_Func::initializeDirectPlayAndCreateOrJoinSession,
                            DAT_GameSynchronyState::ptr)(TRUE)
                        < 0) {
                        continue;
                    }
                    DPSESSIONDESC2 description;
                    MACRO_CALL(OpenSHC::OS_Func::_memset)(&description, 0, sizeof(description));
                    description.dwSize = sizeof(description);
                    description.guidApplication = GUID_APP::instance;
                    DAT_GameSynchronyState::instance.DPLAYX_4A->EnumSessions(&description, 0,
                        MACRO_CALL(OpenSHC::Synchrony_Func::EnumSessionsCallback_addSession_async), NULL,
                        OpenSHC::DirectPlay::ESFE_ASYNC_ENUMERATION_STOP);
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
                    DAT_GameSynchronyState::instance.multiplayerJoinStep = 2;
                    MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                        DAT_MenuModalComposition1::ptr)(OpenSHC::UI::Enums::MMT_NONE, FALSE);
                }
            }

        }
    }
}
}
