#include "../General.func.hpp"

#include "OpenSHC/Game/Skirmish.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Synchrony/Commands.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/Text/UserTextHandler.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_ButtonBackgroundBlendStrength.hpp"
#include "OpenSHC/Globals/DAT_ButtonW.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition2.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_UserTextHandlerState.hpp"
#include "OpenSHC/Globals/INT_00b960cc.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using Commands::GameCommandType;
        using DE::SHCDE::eTextSections;
        using Game::GameMode;
        using Text::TextAlignment;
        using UI::Enums::MenuModalType;
        using WindowsHelper::Enums::BOOLEnum;

        /*
          Why are these advanced play options part of the lobby menu, an extra play options menu modal and   a reduced
          version of it only containing the tempo and the auto safe frequency called connection   options? Maybe this
          function actually handlse the expected options and something in the lobby   menu itself? But why the reduced
          "connection options"?   --TheRedDaemon   gynt: some of them are from Extreme! Like enabling disabling Extreme
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00429A40
        void General::MenuItemActionHandler_General_AdvancedGameOptions(int param_1, ...)
        {
            char* pcVar1;
            char* pcVar2;
            bool bVar3;
            eTextSections eVar4;
            int iVar5;
            if (!DAT_GameSynchronyState::instance.isHost) {
                return;
            }
            if (DAT_MenuModalComposition1::instance.activeModalDialogID == UI::Enums::MMT_SEND_MAP_TO) {
                return;
            }
            if (DAT_MenuModalComposition1::instance.activeModalDialogID == UI::Enums::MMT_RECEIVE_MAP_FROM) {
                return;
            }
            if (DAT_MenuModalComposition1::instance.activeModalDialogID == UI::Enums::MMT_SKIRMISH_PLAY_OPTIONS
                && param_1 != -1000 && param_1 != -10 && param_1 != -0xb && param_1 != -0xc && param_1 != -0xd
                && param_1 != -0xe && param_1 != 99 && param_1 != 100 && param_1 != 0x53 && param_1 != 0x6d
                && param_1 != 0x52 && param_1 != 0x5e) {
                return;
            }
            if (DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SKIRMISH_SINGLE_PLAYER) {
                if (param_1 == 0x5d) {
                    return;
                }
                if (param_1 == 0x1f) {
                    return;
                }
            }
            if (DAT_MenuModalComposition1::instance.activeModalDialogID == UI::Enums::MMT_ROUNDTABLE) {
                return;
            }
            if (DAT_MenuModalComposition1::instance.activeModalDialogID == UI::Enums::MMT_BASIC_AI_LORD_SELECT) {
                return;
            }
            if (DAT_MenuModalComposition1::instance.activeModalDialogID == UI::Enums::MMT_EXTENDED_AI_LORD_SELECT) {
                return;
            }
            if (param_1 == 0xe) {
                if ((DAT_MenuModalComposition2::instance.activeModalDialogID != UI::Enums::MMT_NONE)
                    && (INT_00b960cc::instance == 1)) {
                    DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[0] = 1;
                    DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[1] = 1;
                    DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[2] = 1;
                    DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[3] = 1;
                    DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[4] = 1;
                    DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[5] = 1;
                    DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[6] = 1;
                    DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[7] = 1;
                    DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[8] = 1;
                    return;
                }
                INT_00b960cc::instance = 1;
                MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::setSliderParameters, DAT_MenuModalComposition2::ptr)(0,
                    10000, DAT_GameSynchronyState::instance.skirmishStartGold,
                    (undefined*)((int)(&DAT_GameSynchronyState::instance.skirmishStartGold)),
                    (void*)MACRO_CALL(Synchrony::Commands_Func::QueueChangeGameIntensityOrBalance));
                MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::setExtraActiveModalDialog,
                    DAT_MenuModalComposition2::ptr)(UI::Enums::MMT_OVERLAY_SLIDER,
                    (int)((int)(DAT_ButtonX::instance + 0x48)), (int)((int)(DAT_ButtonY::instance + 4)));
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[0] = 1;
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[1] = 1;
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[2] = 1;
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[3] = 1;
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[4] = 1;
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[5] = 1;
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[6] = 1;
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[7] = 1;
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[8] = 1;
                return;
            }
            if (param_1 == 0xf) {
                MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::setSliderParameters, DAT_MenuModalComposition2::ptr)(0,
                    100, DAT_GameSynchronyState::instance.skirmishDefaultPopularity,
                    (undefined*)((int)(&DAT_GameSynchronyState::instance.skirmishDefaultPopularity)),
                    (void*)MACRO_CALL(Synchrony::Commands_Func::QueueChangeGameIntensityOrBalance));
                MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::setExtraActiveModalDialog,
                    DAT_MenuModalComposition2::ptr)(UI::Enums::MMT_OVERLAY_SLIDER,
                    (int)((int)(DAT_ButtonX::instance + 0x17)), (int)((int)(DAT_ButtonY::instance + 0x23)));
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[0] = 1;
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[1] = 1;
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[2] = 1;
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[3] = 1;
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[4] = 1;
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[5] = 1;
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[6] = 1;
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[7] = 1;
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[8] = 1;
                return;
            }
            if (param_1 == 0x52) {
                if ((DAT_MenuModalComposition2::instance.activeModalDialogID != UI::Enums::MMT_NONE)
                    && (INT_00b960cc::instance == 2)) {
                    DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[0] = 1;
                    DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[1] = 1;
                    DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[2] = 1;
                    DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[3] = 1;
                    DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[4] = 1;
                    DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[5] = 1;
                    DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[6] = 1;
                    DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[7] = 1;
                    DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[8] = 1;
                    return;
                }
                INT_00b960cc::instance = 2;
                MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::setSliderParameters, DAT_MenuModalComposition2::ptr)(
                    0x14, 0x5a, DAT_GameSynchronyState::instance.skirmishGameSpeedLevel,
                    (undefined*)((int)(&DAT_GameSynchronyState::instance.skirmishGameSpeedLevel)),
                    (void*)MACRO_CALL(UI::Helpers_Func::CallbackSetMultiplayerSpeedLevel));
                MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::setExtraActiveModalDialog,
                    DAT_MenuModalComposition2::ptr)(UI::Enums::MMT_OVERLAY_SLIDER,
                    (int)((int)(DAT_ButtonX::instance + 0x48)), (int)((int)(DAT_ButtonY::instance + 4)));
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[0] = 1;
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[1] = 1;
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[2] = 1;
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[3] = 1;
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[4] = 1;
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[5] = 1;
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[6] = 1;
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[7] = 1;
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[8] = 1;
                return;
            }
            if (param_1 == 0x1f) {
                DAT_GameSynchronyState::instance.skirmishTechLevel
                    = DAT_GameSynchronyState::instance.skirmishTechLevel + 2;
                if (5 < DAT_GameSynchronyState::instance.skirmishTechLevel) {
                    DAT_GameSynchronyState::instance.skirmishTechLevel = 0;
                }
                MACRO_CALL(Game::Skirmish_Func::SetupSkirmishBalanceAndOrIntensity)();
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[0] = 1;
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[1] = 1;
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[2] = 1;
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[3] = 1;
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[4] = 1;
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[5] = 1;
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[6] = 1;
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[7] = 1;
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[8] = 1;
                return;
            }
            if (param_1 == 0x24) {
                MACRO_CALL_MEMBER(
                    UI::MenuModalComposition_Func::setModalSliderParameters, DAT_MenuModalComposition1::ptr)(0x4f, 0x33,
                    2, (dword)((int)(DAT_GameSynchronyState::instance.skirmishWinCondition)),
                    (undefined*)((int)(&DAT_GameSynchronyState::instance.skirmishWinCondition)),
                    (undefined*)MACRO_CALL(Synchrony::Commands_Func::QueueChangeGameIntensityOrBalance));
                MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::setExtraActiveModalDialog,
                    DAT_MenuModalComposition1::ptr)(UI::Enums::MMT_UNUSED_WIN_CONDITION,
                    (int)((int)(DAT_ButtonX::instance + 5)), (int)((int)(DAT_ButtonY::instance + 0x23)));
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[0] = 1;
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[1] = 1;
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[2] = 1;
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[3] = 1;
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[4] = 1;
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[5] = 1;
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[6] = 1;
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[7] = 1;
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[8] = 1;
                return;
            }
            if (param_1 == 0x53) {
                DAT_GameSynchronyState::instance.skirmishTroopsCostGold
                    = DAT_GameSynchronyState::instance.skirmishTroopsCostGold ^ 1;
                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                    Commands::GCT_CHANGE_GAME_INTENSITY_OR_BALANCE);
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[0] = 1;
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[1] = 1;
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[2] = 1;
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[3] = 1;
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[4] = 1;
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[5] = 1;
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[6] = 1;
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[7] = 1;
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[8] = 1;
                return;
            }
            if (param_1 == 0x6d) {
                DAT_GameState::instance.mapAndTime.skirmishFogOfWar
                    = DAT_GameState::instance.mapAndTime.skirmishFogOfWar + 1;
                if (DAT_GameState::instance.mapAndTime.skirmishFogOfWar == 3) {
                    DAT_GameState::instance.mapAndTime.skirmishFogOfWar = 0;
                }
                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                    Commands::GCT_CHANGE_GAME_INTENSITY_OR_BALANCE);
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[0] = 1;
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[1] = 1;
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[2] = 1;
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[3] = 1;
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[4] = 1;
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[5] = 1;
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[6] = 1;
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[7] = 1;
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[8] = 1;
                return;
            }
            if (param_1 == 0x5d) {
                MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog, DAT_MenuModalComposition1::ptr)(
                    UI::Enums::MMT_SKIRMISH_CONNECTION_OPTIONS, FALSE);
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[0] = 1;
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[1] = 1;
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[2] = 1;
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[3] = 1;
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[4] = 1;
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[5] = 1;
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[6] = 1;
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[7] = 1;
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[8] = 1;
                return;
            }
            if (param_1 == 0x67) {
                MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog, DAT_MenuModalComposition1::ptr)(
                    UI::Enums::MMT_SKIRMISH_PLAY_OPTIONS, FALSE);
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[0] = 1;
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[1] = 1;
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[2] = 1;
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[3] = 1;
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[4] = 1;
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[5] = 1;
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[6] = 1;
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[7] = 1;
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[8] = 1;
                return;
            }
            if (param_1 == 0x5e) {
                if (!DAT_GameSynchronyState::instance.skirmishAutoSaveEveryMinutes) {
                    DAT_GameSynchronyState::instance.skirmishAutoSaveEveryMinutes = 5;
                } else if (DAT_GameSynchronyState::instance.skirmishAutoSaveEveryMinutes == 5) {
                    DAT_GameSynchronyState::instance.skirmishAutoSaveEveryMinutes = 10;
                } else if (DAT_GameSynchronyState::instance.skirmishAutoSaveEveryMinutes == 10) {
                    DAT_GameSynchronyState::instance.skirmishAutoSaveEveryMinutes = 0x14;
                } else if (DAT_GameSynchronyState::instance.skirmishAutoSaveEveryMinutes == 0x14) {
                    DAT_GameSynchronyState::instance.skirmishAutoSaveEveryMinutes = 0;
                }
                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                    Commands::GCT_CHANGE_GAME_INTENSITY_OR_BALANCE);
                if (!DAT_GameSynchronyState::instance.skirmishAutoSaveEveryMinutes) {
                    /*
                      added by script: "Off"
                     */
                    pcVar1 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, 0x5f);
                    /*
                      added by script: "Auto save game"
                     */
                    pcVar2 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, 0x5e);
                    MACRO_CALL(OS_Func::_sprintf)(
                        DAT_GameSynchronyState::instance.receivedChatMessage, "%s :%s", pcVar2, pcVar1);
                }
                if (DAT_GameSynchronyState::instance.skirmishAutoSaveEveryMinutes == 5) {
                    /*
                      added by script: "5 minutes"
                     */
                    pcVar1 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, 0x60);
                    /*
                      added by script: "Auto save game"
                     */
                    pcVar2 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, 0x5e);
                    MACRO_CALL(OS_Func::_sprintf)(
                        DAT_GameSynchronyState::instance.receivedChatMessage, "%s :%s", pcVar2, pcVar1);
                }
                if (DAT_GameSynchronyState::instance.skirmishAutoSaveEveryMinutes == 10) {
                    /*
                      added by script: "10 minutes"
                     */
                    pcVar1 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, 0x61);
                    /*
                      added by script: "Auto save game"
                     */
                    pcVar2 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, 0x5e);
                    MACRO_CALL(OS_Func::_sprintf)(
                        DAT_GameSynchronyState::instance.receivedChatMessage, "%s :%s", pcVar2, pcVar1);
                }
                if (DAT_GameSynchronyState::instance.skirmishAutoSaveEveryMinutes == 20) {
                    /*
                      added by script: "20 minutes"
                     */
                    pcVar1 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, 0x62);
                    iVar5 = 0x5e;
                    eVar4 = DE::SHCDE::TEXT_XPLAY_WAITING_ROOM;
                LAB_0042a392:
                    /*
                      added by script: "Auto save game"
                     */
                    pcVar2 = MACRO_CALL_MEMBER(
                        Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(eVar4, iVar5);
                    MACRO_CALL(OS_Func::_sprintf)(
                        DAT_GameSynchronyState::instance.receivedChatMessage, "%s :%s", pcVar2, pcVar1);
                }
            LAB_0042a3af:
                MACRO_CALL_MEMBER(Text::UserTextHandler_Func::copyIntoTextArray, DAT_UserTextHandlerState::ptr)(
                    DAT_GameSynchronyState::instance.receivedChatMessage);
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
                    .DAT_ChatMessageReceiverArray[DAT_GameSynchronyState::instance.currentPlayerSlotID] = 0;
                DAT_GameSynchronyState::instance.DAT_ChatTauntOrMessage = 10000;
                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                    Commands::GCT_TAUNT_OR_CHAT);
                goto LAB_0042a41d;
            }
            if (param_1 == 99) {
                DAT_GameSynchronyState::instance.skirmishStrongWalls
                    = DAT_GameSynchronyState::instance.skirmishStrongWalls ^ 1;
                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                    Commands::GCT_CHANGE_GAME_INTENSITY_OR_BALANCE);
                if (!DAT_GameSynchronyState::instance.skirmishStrongWalls) {
                    iVar5 = 0x5f;
                    eVar4 = DE::SHCDE::TEXT_XPLAY_WAITING_ROOM;
                } else {
                    iVar5 = 0xd;
                    eVar4 = DE::SHCDE::TEXT_GAME_OPTIONS;
                }
                /*
                  added by script: "Off"
                 */
                pcVar1 = MACRO_CALL_MEMBER(
                    Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(eVar4, iVar5);
                iVar5 = 99;
                eVar4 = DE::SHCDE::TEXT_XPLAY_WAITING_ROOM;
            LAB_00429e4b:
                /*
                  added by script: "Strong Walls"
                 */
                pcVar2 = MACRO_CALL_MEMBER(
                    Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(eVar4, iVar5);
                MACRO_CALL(OS_Func::_sprintf)(
                    DAT_GameSynchronyState::instance.receivedChatMessage, "%s :%s", pcVar2, pcVar1);
                MACRO_CALL_MEMBER(Text::UserTextHandler_Func::copyIntoTextArray, DAT_UserTextHandlerState::ptr)(
                    DAT_GameSynchronyState::instance.receivedChatMessage);
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
                    .DAT_ChatMessageReceiverArray[DAT_GameSynchronyState::instance.currentPlayerSlotID] = 0;
                DAT_GameSynchronyState::instance.DAT_ChatTauntOrMessage = 10000;
                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                    Commands::GCT_TAUNT_OR_CHAT);
            } else {
                if (param_1 == 100) {
                    DAT_GameSynchronyState::instance.skirmishAlliances
                        = DAT_GameSynchronyState::instance.skirmishAlliances ^ 1;
                    MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                        Commands::GCT_CHANGE_GAME_INTENSITY_OR_BALANCE);
                    DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[0] = 1;
                    DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[1] = 1;
                    DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[2] = 1;
                    DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[3] = 1;
                    DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[4] = 1;
                    DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[5] = 1;
                    DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[6] = 1;
                    DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[7] = 1;
                    DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[8] = 1;
                    return;
                }
                if (param_1 == -1000) {
                    MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog,
                        DAT_MenuModalComposition1::ptr)(UI::Enums::MMT_NONE, FALSE);
                    DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[0] = 1;
                    DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[1] = 1;
                    DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[2] = 1;
                    DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[3] = 1;
                    DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[4] = 1;
                    DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[5] = 1;
                    DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[6] = 1;
                    DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[7] = 1;
                    DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[8] = 1;
                    return;
                }
                if (param_1 == -1) {
                    MACRO_CALL_MEMBER(
                        UI::MenuModalComposition_Func::setSliderParameters, DAT_MenuModalComposition2::ptr)(2000,
                        150000, (int)((int)(DAT_GameSynchronyState::instance.skirmishPoints)),
                        (undefined*)((int)(&DAT_GameSynchronyState::instance.skirmishPoints)),
                        (void*)MACRO_CALL(Synchrony::Commands_Func::QueueChangeGameIntensityOrBalance));
                    DAT_MenuModalComposition2::instance.textGroup = 0x4f;
                    DAT_MenuModalComposition2::instance.textIndex = 0x58;
                    /*
                      cr.tex: Points
                     */
                    MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::setExtraActiveModalDialog,
                        DAT_MenuModalComposition2::ptr)(UI::Enums::MMT_OVERLAY_SLIDER,
                        (int)((int)(DAT_ButtonX::instance + -0x17)), (int)((int)(DAT_ButtonY::instance + 0x3f)));
                    DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[0] = 1;
                    DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[1] = 1;
                    DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[2] = 1;
                    DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[3] = 1;
                    DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[4] = 1;
                    DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[5] = 1;
                    DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[6] = 1;
                    DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[7] = 1;
                    DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[8] = 1;
                    return;
                }
                if (param_1 == -10) {
                    DAT_GameSynchronyState::instance.skirmishNoCowThrowing
                        = DAT_GameSynchronyState::instance.skirmishNoCowThrowing ^ 1;
                    MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                        Commands::GCT_CHANGE_GAME_INTENSITY_OR_BALANCE);
                    if (!DAT_GameSynchronyState::instance.skirmishNoCowThrowing) {
                        iVar5 = 0x5f;
                        eVar4 = DE::SHCDE::TEXT_XPLAY_WAITING_ROOM;
                    } else {
                        iVar5 = 0xd;
                        eVar4 = DE::SHCDE::TEXT_GAME_OPTIONS;
                    }
                    /*
                      added by script: "Off" / "On"
                     */
                    pcVar1 = MACRO_CALL_MEMBER(
                        Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(eVar4, iVar5);
                    iVar5 = 5;
                } else {
                    if (param_1 == -0xb) {
                        DAT_GameSynchronyState::instance.skirmishNoDogs
                            = DAT_GameSynchronyState::instance.skirmishNoDogs ^ 1;
                        MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand,
                            DAT_GameSynchronyState::ptr)(Commands::GCT_CHANGE_GAME_INTENSITY_OR_BALANCE);
                        if (!DAT_GameSynchronyState::instance.skirmishNoDogs) {
                            /*
                              added by script: "Off"
                             */
                            pcVar1 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                                DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, 0x5f);
                        } else {
                            /*
                              added by script: "On"
                             */
                            pcVar1 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                                DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_GAME_OPTIONS, 0xd);
                        }
                        iVar5 = 6;
                        eVar4 = DE::SHCDE::TEXT_SKIRMISH_MISC;
                        goto LAB_0042a392;
                    }
                    if (param_1 == -0xd) {
                        DAT_GameSynchronyState::instance.skirmishExtremeMode
                            = DAT_GameSynchronyState::instance.skirmishExtremeMode ^ 1;
                        MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand,
                            DAT_GameSynchronyState::ptr)(Commands::GCT_CHANGE_GAME_INTENSITY_OR_BALANCE);
                        if (!DAT_GameSynchronyState::instance.skirmishExtremeMode) {
                            /*
                              added by script: "Off"
                             */
                            pcVar1 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                                DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, 0x5f);
                            iVar5 = 0xd;
                            eVar4 = DE::SHCDE::TEXT_SKIRMISH_MISC;
                        } else {
                            /*
                              added by script: "On"
                             */
                            pcVar1 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                                DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_GAME_OPTIONS, 0xd);
                            iVar5 = 0xd;
                            eVar4 = DE::SHCDE::TEXT_SKIRMISH_MISC;
                        }
                        goto LAB_00429e4b;
                    }
                    if (param_1 != -0xe) {
                        if (param_1 != -0xc) {
                            DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[0] = 1;
                            DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[1] = 1;
                            DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[2] = 1;
                            DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[3] = 1;
                            DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[4] = 1;
                            DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[5] = 1;
                            DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[6] = 1;
                            DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[7] = 1;
                            DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[8] = 1;
                            return;
                        }
                        DAT_GameSynchronyState::instance.skirmishNoRushSetting
                            = DAT_GameSynchronyState::instance.skirmishNoRushSetting + 1;
                        if (5 < (int)DAT_GameSynchronyState::instance.skirmishNoRushSetting) {
                            DAT_GameSynchronyState::instance.skirmishNoRushSetting = 0;
                        }
                        MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand,
                            DAT_GameSynchronyState::ptr)(Commands::GCT_CHANGE_GAME_INTENSITY_OR_BALANCE);
                        if (!DAT_GameSynchronyState::instance.skirmishNoRushSetting) {
                            iVar5 = (DAT_ButtonBackgroundBlendStrength::instance + -0x20) * 0x20;
                            MACRO_CALL_MEMBER(Text::TextManager_Func::renderInGameText2, DAT_TextManagerObject::ptr)(
                                DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, 0x5f,
                                (int)((int)(DAT_ButtonW::instance + -0x14 + DAT_ButtonX::instance)),
                                (int)((int)(DAT_ButtonY::instance + 7)), Text::TTA_RIGHT, 0xb8e6f5, 0, 0x12, FALSE,
                                (iVar5 / 32) + 0x20);
                        }
                        if (DAT_GameSynchronyState::instance.skirmishNoRushSetting == 1) {
                            iVar5 = (DAT_ButtonBackgroundBlendStrength::instance + -0x20) * 0x20;
                            MACRO_CALL_MEMBER(Text::TextManager_Func::renderInGameText2, DAT_TextManagerObject::ptr)(
                                DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, 0x60,
                                (int)((int)(DAT_ButtonW::instance + -0x14 + DAT_ButtonX::instance)),
                                (int)((int)(DAT_ButtonY::instance + 7)), Text::TTA_RIGHT, 0xb8e6f5, 0, 0x12, FALSE,
                                (iVar5 / 32) + 0x20);
                        }
                        if (DAT_GameSynchronyState::instance.skirmishNoRushSetting == 2) {
                            iVar5 = (DAT_ButtonBackgroundBlendStrength::instance + -0x20) * 0x20;
                            MACRO_CALL_MEMBER(Text::TextManager_Func::renderInGameText2, DAT_TextManagerObject::ptr)(
                                DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, 0x61,
                                (int)((int)(DAT_ButtonW::instance + -0x14 + DAT_ButtonX::instance)),
                                (int)((int)(DAT_ButtonY::instance + 7)), Text::TTA_RIGHT, 0xb8e6f5, 0, 0x12, FALSE,
                                (iVar5 / 32) + 0x20);
                        }
                        if (DAT_GameSynchronyState::instance.skirmishNoRushSetting == 3) {
                            iVar5 = (DAT_ButtonBackgroundBlendStrength::instance + -0x20) * 0x20;
                            MACRO_CALL_MEMBER(Text::TextManager_Func::renderInGameText2, DAT_TextManagerObject::ptr)(
                                DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, 0x62,
                                (int)((int)(DAT_ButtonW::instance + -0x14 + DAT_ButtonX::instance)),
                                (int)((int)(DAT_ButtonY::instance + 7)), Text::TTA_RIGHT, 0xb8e6f5, 0, 0x12, FALSE,
                                (iVar5 / 32) + 0x20);
                        }
                        if (DAT_GameSynchronyState::instance.skirmishNoRushSetting == 4) {
                            iVar5 = (DAT_ButtonBackgroundBlendStrength::instance + -0x20) * 0x20;
                            /*
                              30 minutes
                             */
                            MACRO_CALL_MEMBER(Text::TextManager_Func::renderInGameText2, DAT_TextManagerObject::ptr)(
                                DE::SHCDE::TEXT_SKIRMISH_MISC, 8,
                                (int)((int)(DAT_ButtonW::instance + -0x14 + DAT_ButtonX::instance)),
                                (int)((int)(DAT_ButtonY::instance + 7)), Text::TTA_RIGHT, 0xb8e6f5, 0, 0x12, FALSE,
                                (iVar5 / 32) + 0x20);
                        }
                        bVar3 = false;
                        if (DAT_GameSynchronyState::instance.skirmishNoRushSetting == 5) {
                            iVar5 = (DAT_ButtonBackgroundBlendStrength::instance + -0x20) * 0x20;
                            MACRO_CALL_MEMBER(Text::TextManager_Func::renderInGameText2, DAT_TextManagerObject::ptr)(
                                DE::SHCDE::TEXT_SKIRMISH_MISC, 9,
                                (int)((int)(DAT_ButtonW::instance + -0x14 + DAT_ButtonX::instance)),
                                (int)((int)(DAT_ButtonY::instance + 7)), Text::TTA_RIGHT, 0xb8e6f5, 0, 0x12, FALSE,
                                (iVar5 / 32) + 0x20);
                            bVar3 = DAT_GameSynchronyState::instance.skirmishNoRushSetting == 5;
                        }
                        if (DAT_GameSynchronyState::instance.skirmishNoRushSetting < 5 || bVar3) {
                            switch (DAT_GameSynchronyState::instance.skirmishNoRushSetting) {
                            case 0:
                                pcVar1 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                                    DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, 0x5f);
                                break;
                            case 1:
                                pcVar1 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                                    DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, 0x60);
                                break;
                            case 2:
                                pcVar1 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                                    DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, 0x61);
                                break;
                            case 3:
                                pcVar1 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                                    DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, 0x62);
                                break;
                            case 4:
                                pcVar1 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                                    DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_SKIRMISH_MISC, 8);
                                break;
                            case 5:
                                pcVar1 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                                    DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_SKIRMISH_MISC, 9);
                                break;
                            }
                            pcVar2 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                                DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_SKIRMISH_MISC, 7);
                            MACRO_CALL(OS_Func::_sprintf)(
                                DAT_GameSynchronyState::instance.receivedChatMessage, "%s :%s", pcVar2, pcVar1);
                            goto LAB_0042a3af;
                        }
                        goto LAB_0042a3af;
                    }
                    DAT_GameSynchronyState::instance.skirmishExtremeMode2
                        = DAT_GameSynchronyState::instance.skirmishExtremeMode2 ^ 1;
                    MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                        Commands::GCT_CHANGE_GAME_INTENSITY_OR_BALANCE);
                    if (!DAT_GameSynchronyState::instance.skirmishExtremeMode) {
                        /*
                          added by script: "Off"
                         */
                        pcVar1 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, 0x5f);
                        iVar5 = 0xe;
                    } else {
                        /*
                          added by script: "On"
                         */
                        pcVar1 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_GAME_OPTIONS, 0xd);
                        iVar5 = 0xe;
                    }
                }
                /*
                  added by script: "Extreme Powers around Lord"
                 */
                pcVar2 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_SKIRMISH_MISC, iVar5);
                MACRO_CALL(OS_Func::_sprintf)(
                    DAT_GameSynchronyState::instance.receivedChatMessage, "%s :%s", pcVar2, pcVar1);
                MACRO_CALL_MEMBER(Text::UserTextHandler_Func::copyIntoTextArray, DAT_UserTextHandlerState::ptr)(
                    DAT_GameSynchronyState::instance.receivedChatMessage);
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
                    .DAT_ChatMessageReceiverArray[DAT_GameSynchronyState::instance.currentPlayerSlotID] = 0;
                DAT_GameSynchronyState::instance.DAT_ChatTauntOrMessage = 10000;
                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                    Commands::GCT_TAUNT_OR_CHAT);
            }
        LAB_0042a41d:
            MACRO_CALL_MEMBER(Text::UserTextHandler_Func::clearEntry, DAT_UserTextHandlerState::ptr)(
                DAT_UserTextHandlerState::instance.textArrayIndex);
            DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[8] = 1;
            DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[7] = 1;
            DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[6] = 1;
            DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[5] = 1;
            DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[4] = 1;
            DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[3] = 1;
            DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[2] = 1;
            DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[1] = 1;
            DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[0] = 1;
            return;
        }

    }
}
}
