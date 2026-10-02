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
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

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

        using OpenSHC::Commands::GameCommandType;
        using OpenSHC::UI::ChooseNetworkServiceProvider::ChooseNetworkServiceProviderButtonActions;
        using OpenSHC::UI::Enums::BuildingsAndStatusMenuTabType;
        using OpenSHC::UI::Enums::MenuModalType;
        using OpenSHC::UI::Enums::MenuViewType;
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
            if (param_1 < ((ChooseNetworkServiceProviderButtonActions)0x80000000)) {
                if (param_1 == OpenSHC::UI::ChooseNetworkServiceProvider::CNSPBA_EXIT) {
                LAB_00490d4f:
                    MACRO_CALL_MEMBER(
                        OpenSHC::Synchrony::GameSynchronyState_Func::disconnectDPlay, DAT_GameSynchronyState::ptr)();
                    DAT_GameSynchronyState::instance.kickedAtTime = 0;
                    MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                        DAT_MenuModalComposition1::ptr)(OpenSHC::UI::Enums::MMT_NONE, FALSE);
                    MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                        OpenSHC::UI::Enums::MVT_MAIN_MENU, 0);
                    MACRO_CALL_MEMBER(OpenSHC::Input::MouseState_Func::resetMouseState2, DAT_MouseState::ptr)();
                }
                if (param_1 == OpenSHC::UI::ChooseNetworkServiceProvider::CNSPBA_HOST_GAME) {
                    DAT_GameSynchronyState::instance.isHost = TRUE;
                    DAT_GameSynchronyState::instance.kickedAtTime = 0;
                    iVar4 = MACRO_CALL_MEMBER(
                        OpenSHC::Synchrony::GameSynchronyState_Func::initializeDirectPlayAndCreateOrJoinSession,
                        DAT_GameSynchronyState::ptr)(FALSE);
                    if (-1 < iVar4) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                            DAT_MenuModalComposition1::ptr)(OpenSHC::UI::Enums::MMT_NONE, FALSE);
                        DAT_GameSynchronyState::instance.field225_0x106ee4 = 1;
                        DAT_GameCore::instance.menuTabToSwitchTo.tabType = ((BuildingsAndStatusMenuTabType)0);
                        MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                            OpenSHC::UI::Enums::MVT_LOBBY_MENU, 0);
                        MACRO_CALL(OpenSHC::Synchrony_Func::InitSkirmishLobbyData)();
                        Menu_LobbyMenu::instance.thousand = 0;
                        MACRO_CALL(OpenSHC::OS_Func::_memset)(
                            DAT_GameSynchronyState::instance.DAT_PlayerNames, 0, 0x8ca);
                        pcVar3 = MACRO_CALL_MEMBER(
                            OpenSHC::Text::UserTextHandler_Func::getTextArrayPointer, DAT_UserTextHandlerState::ptr)(0);
                        pacVar7 = DAT_GameSynchronyState::instance.DAT_PlayerNames + 1;
                        do {
                            cVar1 = *pcVar3;
                            (*pacVar7)[0] = cVar1;
                            pcVar3 = pcVar3 + 1;
                            pacVar7 = (char (*)[250])(*pacVar7 + 1);
                        } while (cVar1 != '\0');
                        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::waitForMultiplayerHost,
                            DAT_GameSynchronyState::ptr)();
                        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                            DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_ASK_FOR_SLOT_ASSIGNMENT);
                    }
                    MACRO_CALL_MEMBER(OpenSHC::Input::MouseState_Func::resetMouseState2, DAT_MouseState::ptr)();
                }
                if (param_1 == OpenSHC::UI::ChooseNetworkServiceProvider::CNSPBA_JOIN_GAME) {
                    DAT_GameSynchronyState::instance.isHost = FALSE;
                    DAT_GameSynchronyState::instance.kickedAtTime = 0;
                    if (DAT_GameCore::instance.activeMenuTab.tabType
                        == OpenSHC::UI::Enums::BASMTT_GRANARY_OR_MPMENU_TCPIP) {
                        pcVar2 = MACRO_CALL_MEMBER(
                            OpenSHC::Text::UserTextHandler_Func::getTextArrayPointer, DAT_UserTextHandlerState::ptr)(5);
                        pcVar3 = pcVar2 + 1;
                        do {
                            cVar1 = *pcVar2;
                            pcVar2 = pcVar2 + 1;
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
                                pacVar6 = pacVar6 + 1;
                            } while ((int)pacVar6 < 0x1a274f4);
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
                                        pcVar3 = pcVar3 + 1;
                                        pacVar6 = (char (*)[20])(*pacVar6 + 1);
                                    } while (cVar1 != '\0');
                                    goto LAB_00490c30;
                                }
                                pacVar6 = pacVar6 + 1;
                                iVar4 = iVar4 + 1;
                            } while ((int)pacVar6 < 0x1a274f4);
                            DAT_GameSynchronyState::instance.ipRelatedArray[0][0]
                                = DAT_GameSynchronyState::instance.ipRelatedArray[1][0];
                            DAT_GameSynchronyState::instance.ipRelatedArray[0][1]
                                = DAT_GameSynchronyState::instance.ipRelatedArray[1][1];
                            DAT_GameSynchronyState::instance.ipRelatedArray[0][2]
                                = DAT_GameSynchronyState::instance.ipRelatedArray[1][2];
                            DAT_GameSynchronyState::instance.ipRelatedArray[0][3]
                                = DAT_GameSynchronyState::instance.ipRelatedArray[1][3];
                            DAT_GameSynchronyState::instance.ipRelatedArray[0][4]
                                = DAT_GameSynchronyState::instance.ipRelatedArray[1][4];
                            DAT_GameSynchronyState::instance.ipRelatedArray[0][5]
                                = DAT_GameSynchronyState::instance.ipRelatedArray[1][5];
                            DAT_GameSynchronyState::instance.ipRelatedArray[0][6]
                                = DAT_GameSynchronyState::instance.ipRelatedArray[1][6];
                            DAT_GameSynchronyState::instance.ipRelatedArray[0][7]
                                = DAT_GameSynchronyState::instance.ipRelatedArray[1][7];
                            DAT_GameSynchronyState::instance.ipRelatedArray[0][8]
                                = DAT_GameSynchronyState::instance.ipRelatedArray[1][8];
                            DAT_GameSynchronyState::instance.ipRelatedArray[0][9]
                                = DAT_GameSynchronyState::instance.ipRelatedArray[1][9];
                            DAT_GameSynchronyState::instance.ipRelatedArray[0][10]
                                = DAT_GameSynchronyState::instance.ipRelatedArray[1][10];
                            DAT_GameSynchronyState::instance.ipRelatedArray[0][0xb]
                                = DAT_GameSynchronyState::instance.ipRelatedArray[1][0xb];
                            DAT_GameSynchronyState::instance.ipRelatedArray[0][0xc]
                                = DAT_GameSynchronyState::instance.ipRelatedArray[1][0xc];
                            DAT_GameSynchronyState::instance.ipRelatedArray[0][0xd]
                                = DAT_GameSynchronyState::instance.ipRelatedArray[1][0xd];
                            DAT_GameSynchronyState::instance.ipRelatedArray[0][0xe]
                                = DAT_GameSynchronyState::instance.ipRelatedArray[1][0xe];
                            DAT_GameSynchronyState::instance.ipRelatedArray[0][0xf]
                                = DAT_GameSynchronyState::instance.ipRelatedArray[1][0xf];
                            DAT_GameSynchronyState::instance.ipRelatedArray[0][0x10]
                                = DAT_GameSynchronyState::instance.ipRelatedArray[1][0x10];
                            DAT_GameSynchronyState::instance.ipRelatedArray[0][0x11]
                                = DAT_GameSynchronyState::instance.ipRelatedArray[1][0x11];
                            DAT_GameSynchronyState::instance.ipRelatedArray[0][0x12]
                                = DAT_GameSynchronyState::instance.ipRelatedArray[1][0x12];
                            DAT_GameSynchronyState::instance.ipRelatedArray[0][0x13]
                                = DAT_GameSynchronyState::instance.ipRelatedArray[1][0x13];
                            DAT_GameSynchronyState::instance.ipRelatedArray[1][0]
                                = DAT_GameSynchronyState::instance.ipRelatedArray[2][0];
                            DAT_GameSynchronyState::instance.ipRelatedArray[1][1]
                                = DAT_GameSynchronyState::instance.ipRelatedArray[2][1];
                            DAT_GameSynchronyState::instance.ipRelatedArray[1][2]
                                = DAT_GameSynchronyState::instance.ipRelatedArray[2][2];
                            DAT_GameSynchronyState::instance.ipRelatedArray[1][3]
                                = DAT_GameSynchronyState::instance.ipRelatedArray[2][3];
                            DAT_GameSynchronyState::instance.ipRelatedArray[1][4]
                                = DAT_GameSynchronyState::instance.ipRelatedArray[2][4];
                            DAT_GameSynchronyState::instance.ipRelatedArray[1][5]
                                = DAT_GameSynchronyState::instance.ipRelatedArray[2][5];
                            DAT_GameSynchronyState::instance.ipRelatedArray[1][6]
                                = DAT_GameSynchronyState::instance.ipRelatedArray[2][6];
                            DAT_GameSynchronyState::instance.ipRelatedArray[1][7]
                                = DAT_GameSynchronyState::instance.ipRelatedArray[2][7];
                            DAT_GameSynchronyState::instance.ipRelatedArray[1][8]
                                = DAT_GameSynchronyState::instance.ipRelatedArray[2][8];
                            DAT_GameSynchronyState::instance.ipRelatedArray[1][9]
                                = DAT_GameSynchronyState::instance.ipRelatedArray[2][9];
                            DAT_GameSynchronyState::instance.ipRelatedArray[1][10]
                                = DAT_GameSynchronyState::instance.ipRelatedArray[2][10];
                            DAT_GameSynchronyState::instance.ipRelatedArray[1][0xb]
                                = DAT_GameSynchronyState::instance.ipRelatedArray[2][0xb];
                            DAT_GameSynchronyState::instance.ipRelatedArray[1][0xc]
                                = DAT_GameSynchronyState::instance.ipRelatedArray[2][0xc];
                            DAT_GameSynchronyState::instance.ipRelatedArray[1][0xd]
                                = DAT_GameSynchronyState::instance.ipRelatedArray[2][0xd];
                            DAT_GameSynchronyState::instance.ipRelatedArray[1][0xe]
                                = DAT_GameSynchronyState::instance.ipRelatedArray[2][0xe];
                            DAT_GameSynchronyState::instance.ipRelatedArray[1][0xf]
                                = DAT_GameSynchronyState::instance.ipRelatedArray[2][0xf];
                            DAT_GameSynchronyState::instance.ipRelatedArray[1][0x10]
                                = DAT_GameSynchronyState::instance.ipRelatedArray[2][0x10];
                            DAT_GameSynchronyState::instance.ipRelatedArray[1][0x11]
                                = DAT_GameSynchronyState::instance.ipRelatedArray[2][0x11];
                            DAT_GameSynchronyState::instance.ipRelatedArray[1][0x12]
                                = DAT_GameSynchronyState::instance.ipRelatedArray[2][0x12];
                            DAT_GameSynchronyState::instance.ipRelatedArray[1][0x13]
                                = DAT_GameSynchronyState::instance.ipRelatedArray[2][0x13];
                            DAT_GameSynchronyState::instance.ipRelatedArray[2][0]
                                = DAT_GameSynchronyState::instance.ipRelatedArray[3][0];
                            DAT_GameSynchronyState::instance.ipRelatedArray[2][1]
                                = DAT_GameSynchronyState::instance.ipRelatedArray[3][1];
                            DAT_GameSynchronyState::instance.ipRelatedArray[2][2]
                                = DAT_GameSynchronyState::instance.ipRelatedArray[3][2];
                            DAT_GameSynchronyState::instance.ipRelatedArray[2][3]
                                = DAT_GameSynchronyState::instance.ipRelatedArray[3][3];
                            DAT_GameSynchronyState::instance.ipRelatedArray[2][4]
                                = DAT_GameSynchronyState::instance.ipRelatedArray[3][4];
                            DAT_GameSynchronyState::instance.ipRelatedArray[2][5]
                                = DAT_GameSynchronyState::instance.ipRelatedArray[3][5];
                            DAT_GameSynchronyState::instance.ipRelatedArray[2][6]
                                = DAT_GameSynchronyState::instance.ipRelatedArray[3][6];
                            DAT_GameSynchronyState::instance.ipRelatedArray[2][7]
                                = DAT_GameSynchronyState::instance.ipRelatedArray[3][7];
                            DAT_GameSynchronyState::instance.ipRelatedArray[2][8]
                                = DAT_GameSynchronyState::instance.ipRelatedArray[3][8];
                            DAT_GameSynchronyState::instance.ipRelatedArray[2][9]
                                = DAT_GameSynchronyState::instance.ipRelatedArray[3][9];
                            DAT_GameSynchronyState::instance.ipRelatedArray[2][10]
                                = DAT_GameSynchronyState::instance.ipRelatedArray[3][10];
                            DAT_GameSynchronyState::instance.ipRelatedArray[2][0xb]
                                = DAT_GameSynchronyState::instance.ipRelatedArray[3][0xb];
                            DAT_GameSynchronyState::instance.ipRelatedArray[2][0xc]
                                = DAT_GameSynchronyState::instance.ipRelatedArray[3][0xc];
                            DAT_GameSynchronyState::instance.ipRelatedArray[2][0xd]
                                = DAT_GameSynchronyState::instance.ipRelatedArray[3][0xd];
                            DAT_GameSynchronyState::instance.ipRelatedArray[2][0xe]
                                = DAT_GameSynchronyState::instance.ipRelatedArray[3][0xe];
                            DAT_GameSynchronyState::instance.ipRelatedArray[2][0xf]
                                = DAT_GameSynchronyState::instance.ipRelatedArray[3][0xf];
                            DAT_GameSynchronyState::instance.ipRelatedArray[2][0x10]
                                = DAT_GameSynchronyState::instance.ipRelatedArray[3][0x10];
                            DAT_GameSynchronyState::instance.ipRelatedArray[2][0x11]
                                = DAT_GameSynchronyState::instance.ipRelatedArray[3][0x11];
                            DAT_GameSynchronyState::instance.ipRelatedArray[2][0x12]
                                = DAT_GameSynchronyState::instance.ipRelatedArray[3][0x12];
                            DAT_GameSynchronyState::instance.ipRelatedArray[2][0x13]
                                = DAT_GameSynchronyState::instance.ipRelatedArray[3][0x13];
                            DAT_GameSynchronyState::instance.ipRelatedArray[3][0] = '\0';
                            DAT_GameSynchronyState::instance.ipRelatedArray[3][1] = '\0';
                            DAT_GameSynchronyState::instance.ipRelatedArray[3][2] = '\0';
                            DAT_GameSynchronyState::instance.ipRelatedArray[3][3] = '\0';
                            DAT_GameSynchronyState::instance.ipRelatedArray[3][4] = '\0';
                            DAT_GameSynchronyState::instance.ipRelatedArray[3][5] = '\0';
                            DAT_GameSynchronyState::instance.ipRelatedArray[3][6] = '\0';
                            DAT_GameSynchronyState::instance.ipRelatedArray[3][7] = '\0';
                            DAT_GameSynchronyState::instance.ipRelatedArray[3][8] = '\0';
                            DAT_GameSynchronyState::instance.ipRelatedArray[3][9] = '\0';
                            DAT_GameSynchronyState::instance.ipRelatedArray[3][10] = '\0';
                            DAT_GameSynchronyState::instance.ipRelatedArray[3][0xb] = '\0';
                            DAT_GameSynchronyState::instance.ipRelatedArray[3][0xc] = '\0';
                            DAT_GameSynchronyState::instance.ipRelatedArray[3][0xd] = '\0';
                            DAT_GameSynchronyState::instance.ipRelatedArray[3][0xe] = '\0';
                            DAT_GameSynchronyState::instance.ipRelatedArray[3][0xf] = '\0';
                            DAT_GameSynchronyState::instance.ipRelatedArray[3][0x10] = '\0';
                            DAT_GameSynchronyState::instance.ipRelatedArray[3][0x11] = '\0';
                            DAT_GameSynchronyState::instance.ipRelatedArray[3][0x12] = '\0';
                            DAT_GameSynchronyState::instance.ipRelatedArray[3][0x13] = '\0';
                            pcVar3 = MACRO_CALL_MEMBER(OpenSHC::Text::UserTextHandler_Func::getTextArrayPointer,
                                DAT_UserTextHandlerState::ptr)(5);
                            pacVar6 = DAT_GameSynchronyState::instance.ipRelatedArray + 3;
                            do {
                                cVar1 = *pcVar3;
                                (*pacVar6)[0] = cVar1;
                                pcVar3 = pcVar3 + 1;
                                pacVar6 = (char (*)[20])(*pacVar6 + 1);
                            } while (cVar1 != '\0');
                        }
                    }
                LAB_00490c30:
                    iVar4 = MACRO_CALL_MEMBER(
                        OpenSHC::Synchrony::GameSynchronyState_Func::initializeDirectPlayAndCreateOrJoinSession,
                        DAT_GameSynchronyState::ptr)(FALSE);
                    if (-1 < iVar4) {
                        DAT_GameSynchronyState::instance.unkEnumerationRelatedBool = false;
                        DAT_GameSynchronyState::instance.scrollBarIndex = -1;
                        DAT_GameSynchronyState::instance.scrollBarItemOffset = 0;
                        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::restartDPlaySessionEnumeration,
                            DAT_GameSynchronyState::ptr)(FALSE);
                        MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                            DAT_MenuModalComposition1::ptr)(OpenSHC::UI::Enums::MMT_FINDING_NETWORK_SESSIONS, FALSE);
                    }
                    MACRO_CALL_MEMBER(OpenSHC::Input::MouseState_Func::resetMouseState2, DAT_MouseState::ptr)();
                }
            } else if (param_1 == ((ChooseNetworkServiceProviderButtonActions)0xffffffff)) {
                if (0 < DAT_GameSynchronyState::instance.scrollBarItemOffset) {
                    DAT_GameSynchronyState::instance.scrollBarItemOffset
                        = DAT_GameSynchronyState::instance.scrollBarItemOffset + -1;
                }
            } else if ((int)param_1 < -9) {
                if (param_1 == ((ChooseNetworkServiceProviderButtonActions)0xfffffff6)) {
                    if (DAT_GameSynchronyState::instance.field32_0x510 != 0) {
                        DAT_WindowAndDirectDraw::instance.postWindowCloseMessage = 1;
                        DAT_GameSynchronyState::instance.openOnClose = TRUE;
                    }
                } else {
                    if (param_1 == ((ChooseNetworkServiceProviderButtonActions)0xffffd8f0))
                        goto LAB_00490d4f;
                    if (param_1 == ((ChooseNetworkServiceProviderButtonActions)0xfffffc18)) {
                        MACRO_CALL_MEMBER(OpenSHC::Text::UserTextHandler_Func::setTextEntryAndUpdateCursor,
                            DAT_UserTextHandlerState::ptr)(
                            5, (char*)(DAT_GameSynchronyState::instance.ipArrayIndex * 0x14 + 0x1a274a4));
                        DAT_GameSynchronyState::instance.ipArrayIndex
                            = DAT_GameSynchronyState::instance.ipArrayIndex + 1;
                        if (3 < DAT_GameSynchronyState::instance.ipArrayIndex) {
                            DAT_GameSynchronyState::instance.ipArrayIndex = 0;
                        }
                    }
                }
            } else if ((param_1 == ((ChooseNetworkServiceProviderButtonActions)0xfffffffe))
                && (DAT_GameSynchronyState::instance.scrollBarItemOffset
                    < DAT_GameSynchronyState::instance.scrollBarItemCount + -4)) {
                DAT_GameSynchronyState::instance.scrollBarItemOffset
                    = DAT_GameSynchronyState::instance.scrollBarItemOffset + 1;
            }
        }

    }
}
}
