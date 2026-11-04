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

        using OpenSHC::UI::ChooseNetworkServiceProvider::ChooseNetworkServiceProviderButtonActions;

        // FUNCTION: STRONGHOLDCRUSADER 0x004909E0
        void ChooseNetworkServiceProvider::MenuItemActionHandler_ChooseNetworkServiceProvider_Buttons(
            ChooseNetworkServiceProviderButtonActions param_1, ...)
        {
            char cVar1;
            char* pcVar2;
            char* pcVar3;
            int iVar4;
            char (*pacVar5)[20];
            char (*pacVar6)[20];
            char (*pacVar7)[250];
            switch (param_1) {
            case OpenSHC::UI::ChooseNetworkServiceProvider::CNSPBA_NEXT_IP_ADDRESSUnk:
                MACRO_CALL_MEMBER(
                    OpenSHC::Text::UserTextHandler_Func::setTextEntryAndUpdateCursor, DAT_UserTextHandlerState::ptr)(
                    5, DAT_GameSynchronyState::instance.ipRelatedArray[DAT_GameSynchronyState::instance.ipArrayIndex]);
                iVar4 = DAT_GameSynchronyState::instance.ipArrayIndex + 1;
                DAT_GameSynchronyState::instance.ipArrayIndex = iVar4;
                if (4 <= iVar4) {
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
                if (0 < DAT_GameSynchronyState::instance.scrollBarItemOffset) {
                    --DAT_GameSynchronyState::instance.scrollBarItemOffset;
                }
                return;
            case OpenSHC::UI::ChooseNetworkServiceProvider::CNSPBA_JOIN_GAME:
                DAT_GameSynchronyState::instance.isHost = FALSE;
                DAT_GameSynchronyState::instance.kickedAtTime = 0;
                if (DAT_GameCore::instance.activeMenuTab.tabType
                    == OpenSHC::UI::Enums::BASMTT_GRANARY_OR_MPMENU_TCPIP) {
                    pcVar2 = MACRO_CALL_MEMBER(
                        OpenSHC::Text::UserTextHandler_Func::getTextArrayPointer, DAT_UserTextHandlerState::ptr)(5);
                    pcVar3 = pcVar2 + 1;
                    do {
                        cVar1 = *pcVar2;
                        ++pcVar2;
                    } while (cVar1 != '\0');
                    if (pcVar2 != pcVar3) {
                        pacVar6 = DAT_GameSynchronyState::instance.ipRelatedArray;
                        do {
                            pacVar5 = pacVar6;
                            pcVar3 = MACRO_CALL_MEMBER(OpenSHC::Text::UserTextHandler_Func::getTextArrayPointer,
                                DAT_UserTextHandlerState::ptr)(5);
                            iVar4 = MACRO_CALL(OpenSHC::OS_Func::__stricmp)(pcVar3, (char const*)((int)(*pacVar5)));
                            if (iVar4 == 0)
                                goto LAB_00490c30;
                            ++pacVar6;
                        } while ((int)pacVar6 < (int)&DAT_GameSynchronyState::instance + 1088908);
                        iVar4 = 0;
                        pacVar6 = DAT_GameSynchronyState::instance.ipRelatedArray;
                        do {
                            pacVar5 = pacVar6;
                            do {
                                pcVar3 = *pacVar5;
                                pacVar5 = (char (*)[20])(*pacVar5 + 1);
                            } while (*pcVar3 != '\0');
                            if (pacVar5 == (char (*)[20])(*pacVar6 + 1)) {
                                pcVar3 = MACRO_CALL_MEMBER(OpenSHC::Text::UserTextHandler_Func::getTextArrayPointer,
                                    DAT_UserTextHandlerState::ptr)(5);
                                pacVar6 = DAT_GameSynchronyState::instance.ipRelatedArray + iVar4;
                                do {
                                    cVar1 = *pcVar3;
                                    (*pacVar6)[0] = cVar1;
                                    ++pcVar3;
                                    pacVar6 = (char (*)[20])(*pacVar6 + 1);
                                } while (cVar1 != '\0');
                                goto LAB_00490c30;
                            }
                            ++pacVar6;
                            ++iVar4;
                        } while ((int)pacVar6 < (int)&DAT_GameSynchronyState::instance + 1088908);
                        // memcpy and memset compile to the original's dword moves
                        for (int row = 0; row < 3; ++row) {
                            memcpy(DAT_GameSynchronyState::instance.ipRelatedArray[row],
                                DAT_GameSynchronyState::instance.ipRelatedArray[row + 1],
                                sizeof(DAT_GameSynchronyState::instance.ipRelatedArray[row]));
                        }
                        memset(DAT_GameSynchronyState::instance.ipRelatedArray[3], 0,
                            sizeof(DAT_GameSynchronyState::instance.ipRelatedArray[3]));
                        pcVar3 = MACRO_CALL_MEMBER(
                            OpenSHC::Text::UserTextHandler_Func::getTextArrayPointer, DAT_UserTextHandlerState::ptr)(5);
                        pacVar6 = DAT_GameSynchronyState::instance.ipRelatedArray + 3;
                        do {
                            cVar1 = *pcVar3;
                            (*pacVar6)[0] = cVar1;
                            ++pcVar3;
                            pacVar6 = (char (*)[20])(*pacVar6 + 1);
                        } while (cVar1 != '\0');
                    }
                }
            LAB_00490c30:
                iVar4 = MACRO_CALL_MEMBER(
                    OpenSHC::Synchrony::GameSynchronyState_Func::initializeDirectPlayAndCreateOrJoinSession,
                    DAT_GameSynchronyState::ptr)(FALSE);
                if (0 <= iVar4) {
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
                iVar4 = MACRO_CALL_MEMBER(
                    OpenSHC::Synchrony::GameSynchronyState_Func::initializeDirectPlayAndCreateOrJoinSession,
                    DAT_GameSynchronyState::ptr)(FALSE);
                if (0 <= iVar4) {
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
                    pcVar3 = MACRO_CALL_MEMBER(
                        OpenSHC::Text::UserTextHandler_Func::getTextArrayPointer, DAT_UserTextHandlerState::ptr)(0);
                    pacVar7 = DAT_GameSynchronyState::instance.DAT_PlayerNames + 1;
                    do {
                        cVar1 = *pcVar3;
                        (*pacVar7)[0] = cVar1;
                        ++pcVar3;
                        pacVar7 = (char (*)[250])(*pacVar7 + 1);
                    } while (cVar1 != '\0');
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
