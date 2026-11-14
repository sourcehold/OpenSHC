#pragma warning(disable : 4996)

#include "../General.func.hpp"

#include "OpenSHC/Game/Skirmish.func.hpp"
#include "OpenSHC/Synchrony/Commands.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/Text/UserTextHandler.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"

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

#include <stdio.h>

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x00429a40
        void __cdecl General::MenuItemActionHandler_General_AdvancedGameOptions(int param_1, ...)
        {
            if (DAT_GameSynchronyState::instance.isHost == 0) {
                return;
            }
            int activeDialog = DAT_MenuModalComposition1::instance.activeModalDialogID;
            if (activeDialog == 42 || activeDialog == 43) {
                return;
            }
            if (activeDialog == 37 && param_1 != -1000 && param_1 != -10 && param_1 != -11 && param_1 != -12
                && param_1 != -13 && param_1 != -14 && param_1 != 99 && param_1 != 100 && param_1 != 83
                && param_1 != 109 && param_1 != 82 && param_1 != 94) {
                return;
            }
            if (DAT_GameSynchronyState::instance.currentGameMode == 99 && (param_1 == 93 || param_1 == 31)) {
                return;
            }
            if (activeDialog == 120 || activeDialog == 118 || activeDialog == 119) {
                return;
            }
            if (param_1 == 14) {
                if (DAT_MenuModalComposition2::instance.activeModalDialogID == -1 || INT_00b960cc::instance != 1) {
                    INT_00b960cc::instance = 1;
                    MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::setSliderParameters,
                        DAT_MenuModalComposition2::ptr)(0, 10000, DAT_GameSynchronyState::instance.skirmishStartGold,
                        (undefined*)&DAT_GameSynchronyState::instance.skirmishStartGold,
                        (Util::FunctionTypes::NoArgCallback*)MACRO_CALL(
                            Synchrony::Commands_Func::QueueChangeGameIntensityOrBalance));
                    MACRO_CALL_MEMBER(
                        UI::MenuModalComposition_Func::setExtraActiveModalDialog, DAT_MenuModalComposition2::ptr)(
                        (UI::Enums::MenuModalType)23, DAT_ButtonX::instance + 72, DAT_ButtonY::instance + 4);
                }
            } else if (param_1 == 15) {
                MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::setSliderParameters, DAT_MenuModalComposition2::ptr)(0,
                    100, DAT_GameSynchronyState::instance.skirmishDefaultPopularity,
                    (undefined*)&DAT_GameSynchronyState::instance.skirmishDefaultPopularity,
                    (Util::FunctionTypes::NoArgCallback*)MACRO_CALL(
                        Synchrony::Commands_Func::QueueChangeGameIntensityOrBalance));
                MACRO_CALL_MEMBER(
                    UI::MenuModalComposition_Func::setExtraActiveModalDialog, DAT_MenuModalComposition2::ptr)(
                    (UI::Enums::MenuModalType)23, DAT_ButtonX::instance + 23, DAT_ButtonY::instance + 35);
            } else if (param_1 == 82) {
                if (DAT_MenuModalComposition2::instance.activeModalDialogID == -1 || INT_00b960cc::instance != 2) {
                    INT_00b960cc::instance = 2;
                    MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::setSliderParameters,
                        DAT_MenuModalComposition2::ptr)(20, 90, DAT_GameSynchronyState::instance.skirmishGameSpeedLevel,
                        (undefined*)&DAT_GameSynchronyState::instance.skirmishGameSpeedLevel,
                        (Util::FunctionTypes::NoArgCallback*)MACRO_CALL(
                            UI::Helpers_Func::CallbackSetMultiplayerSpeedLevel));
                    MACRO_CALL_MEMBER(
                        UI::MenuModalComposition_Func::setExtraActiveModalDialog, DAT_MenuModalComposition2::ptr)(
                        (UI::Enums::MenuModalType)23, DAT_ButtonX::instance + 72, DAT_ButtonY::instance + 4);
                }
            } else if (param_1 == 31) {
                DAT_GameSynchronyState::instance.skirmishTechLevel += 2;
                if (DAT_GameSynchronyState::instance.skirmishTechLevel > 5) {
                    DAT_GameSynchronyState::instance.skirmishTechLevel = 0;
                }
                MACRO_CALL(Game::Skirmish_Func::SetupSkirmishBalanceAndOrIntensity)();
            } else if (param_1 == 36) {
                MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::setModalSliderParameters,
                    DAT_MenuModalComposition1::ptr)(79, 51, 2, DAT_GameSynchronyState::instance.skirmishWinCondition,
                    (int*)&DAT_GameSynchronyState::instance.skirmishWinCondition,
                    (Util::FunctionTypes::NoArgCallback*)MACRO_CALL(
                        Synchrony::Commands_Func::QueueChangeGameIntensityOrBalance));
                MACRO_CALL_MEMBER(
                    UI::MenuModalComposition_Func::setExtraActiveModalDialog, DAT_MenuModalComposition1::ptr)(
                    (UI::Enums::MenuModalType)24, DAT_ButtonX::instance + 5, DAT_ButtonY::instance + 35);
            } else if (param_1 == 83) {
                DAT_GameSynchronyState::instance.skirmishTroopsCostGold ^= 1;
                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                    (Commands::GameCommandType)52);
            } else if (param_1 == 109) {
                DAT_GameState::instance.mapAndTime.skirmishFogOfWar += 1;
                if (DAT_GameState::instance.mapAndTime.skirmishFogOfWar == 3) {
                    DAT_GameState::instance.mapAndTime.skirmishFogOfWar = 0;
                }
                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                    (Commands::GameCommandType)52);
            } else if (param_1 == 93) {
                MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog, DAT_MenuModalComposition1::ptr)(
                    (UI::Enums::MenuModalType)32, FALSE);
            } else if (param_1 == 103) {
                MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog, DAT_MenuModalComposition1::ptr)(
                    (UI::Enums::MenuModalType)37, FALSE);
            } else if (param_1 == 94) {
                if (DAT_GameSynchronyState::instance.skirmishAutoSaveEveryMinutes == 0) {
                    DAT_GameSynchronyState::instance.skirmishAutoSaveEveryMinutes = 5;
                } else if (DAT_GameSynchronyState::instance.skirmishAutoSaveEveryMinutes == 5) {
                    DAT_GameSynchronyState::instance.skirmishAutoSaveEveryMinutes = 10;
                } else if (DAT_GameSynchronyState::instance.skirmishAutoSaveEveryMinutes == 10) {
                    DAT_GameSynchronyState::instance.skirmishAutoSaveEveryMinutes = 20;
                } else if (DAT_GameSynchronyState::instance.skirmishAutoSaveEveryMinutes == 20) {
                    DAT_GameSynchronyState::instance.skirmishAutoSaveEveryMinutes = 0;
                }
                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                    (Commands::GameCommandType)52);
                if (DAT_GameSynchronyState::instance.skirmishAutoSaveEveryMinutes == 0) {
                    sprintf(DAT_GameSynchronyState::instance.receivedChatMessage, "%s :%s",
                        MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)79, 94),
                        MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)79, 95));
                }
                if (DAT_GameSynchronyState::instance.skirmishAutoSaveEveryMinutes == 5) {
                    sprintf(DAT_GameSynchronyState::instance.receivedChatMessage, "%s :%s",
                        MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)79, 94),
                        MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)79, 96));
                }
                if (DAT_GameSynchronyState::instance.skirmishAutoSaveEveryMinutes == 10) {
                    sprintf(DAT_GameSynchronyState::instance.receivedChatMessage, "%s :%s",
                        MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)79, 94),
                        MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)79, 97));
                }
                if (DAT_GameSynchronyState::instance.skirmishAutoSaveEveryMinutes == 20) {
                    sprintf(DAT_GameSynchronyState::instance.receivedChatMessage, "%s :%s",
                        MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)79, 94),
                        MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)79, 98));
                }
                MACRO_CALL_MEMBER(Text::UserTextHandler_Func::copyIntoTextArray, DAT_UserTextHandlerState::ptr)(
                    DAT_GameSynchronyState::instance.receivedChatMessage);
                for (int i = 0; i < 9; ++i) {
                    DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[i] = 1;
                }
                DAT_GameSynchronyState::instance
                    .DAT_ChatMessageReceiverArray[DAT_GameSynchronyState::instance.currentPlayerSlotID] = 0;
                DAT_GameSynchronyState::instance.DAT_ChatTauntOrMessage = 10000;
                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                    (Commands::GameCommandType)14);
                MACRO_CALL_MEMBER(Text::UserTextHandler_Func::clearEntry, DAT_UserTextHandlerState::ptr)(
                    DAT_UserTextHandlerState::instance.textArrayIndex);
            } else if (param_1 == 99) {
                DAT_GameSynchronyState::instance.skirmishStrongWalls ^= 1;
                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                    (Commands::GameCommandType)52);
                sprintf(DAT_GameSynchronyState::instance.receivedChatMessage, "%s :%s",
                    MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                        (DE::SHCDE::eTextSections)79, 99),
                    DAT_GameSynchronyState::instance.skirmishStrongWalls != 0
                        ? MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                              DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)74, 13)
                        : MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                              DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)79, 95));
                MACRO_CALL_MEMBER(Text::UserTextHandler_Func::copyIntoTextArray, DAT_UserTextHandlerState::ptr)(
                    DAT_GameSynchronyState::instance.receivedChatMessage);
                for (int i = 0; i < 9; ++i) {
                    DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[i] = 1;
                }
                DAT_GameSynchronyState::instance
                    .DAT_ChatMessageReceiverArray[DAT_GameSynchronyState::instance.currentPlayerSlotID] = 0;
                DAT_GameSynchronyState::instance.DAT_ChatTauntOrMessage = 10000;
                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                    (Commands::GameCommandType)14);
                MACRO_CALL_MEMBER(Text::UserTextHandler_Func::clearEntry, DAT_UserTextHandlerState::ptr)(
                    DAT_UserTextHandlerState::instance.textArrayIndex);
            } else if (param_1 == 100) {
                DAT_GameSynchronyState::instance.skirmishAlliances ^= 1;
                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                    (Commands::GameCommandType)52);
            } else if (param_1 == -1000) {
                MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog, DAT_MenuModalComposition1::ptr)(
                    (UI::Enums::MenuModalType)-1, FALSE);
            } else if (param_1 == -1) {
                MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::setSliderParameters, DAT_MenuModalComposition2::ptr)(
                    2000, 150000, DAT_GameSynchronyState::instance.skirmishPoints,
                    (undefined*)&DAT_GameSynchronyState::instance.skirmishPoints,
                    (Util::FunctionTypes::NoArgCallback*)MACRO_CALL(
                        Synchrony::Commands_Func::QueueChangeGameIntensityOrBalance));
                DAT_MenuModalComposition2::instance.textGroup = 79;
                DAT_MenuModalComposition2::instance.textIndex = 88;
                MACRO_CALL_MEMBER(
                    UI::MenuModalComposition_Func::setExtraActiveModalDialog, DAT_MenuModalComposition2::ptr)(
                    (UI::Enums::MenuModalType)23, DAT_ButtonX::instance - 23, DAT_ButtonY::instance + 63);
            } else if (param_1 == -10) {
                DAT_GameSynchronyState::instance.skirmishNoCowThrowing ^= 1;
                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                    (Commands::GameCommandType)52);
                sprintf(DAT_GameSynchronyState::instance.receivedChatMessage, "%s :%s",
                    MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                        (DE::SHCDE::eTextSections)252, 5),
                    DAT_GameSynchronyState::instance.skirmishNoCowThrowing != 0
                        ? MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                              DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)74, 13)
                        : MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                              DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)79, 95));
                MACRO_CALL_MEMBER(Text::UserTextHandler_Func::copyIntoTextArray, DAT_UserTextHandlerState::ptr)(
                    DAT_GameSynchronyState::instance.receivedChatMessage);
                for (int i = 0; i < 9; ++i) {
                    DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[i] = 1;
                }
                DAT_GameSynchronyState::instance
                    .DAT_ChatMessageReceiverArray[DAT_GameSynchronyState::instance.currentPlayerSlotID] = 0;
                DAT_GameSynchronyState::instance.DAT_ChatTauntOrMessage = 10000;
                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                    (Commands::GameCommandType)14);
                MACRO_CALL_MEMBER(Text::UserTextHandler_Func::clearEntry, DAT_UserTextHandlerState::ptr)(
                    DAT_UserTextHandlerState::instance.textArrayIndex);
            } else if (param_1 == -11) {
                DAT_GameSynchronyState::instance.skirmishNoDogs ^= 1;
                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                    (Commands::GameCommandType)52);
                if (DAT_GameSynchronyState::instance.skirmishNoDogs != 0) {
                    sprintf(DAT_GameSynchronyState::instance.receivedChatMessage, "%s :%s",
                        MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)252, 6),
                        MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)74, 13));
                } else {
                    sprintf(DAT_GameSynchronyState::instance.receivedChatMessage, "%s :%s",
                        MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)252, 6),
                        MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)79, 95));
                }
                MACRO_CALL_MEMBER(Text::UserTextHandler_Func::copyIntoTextArray, DAT_UserTextHandlerState::ptr)(
                    DAT_GameSynchronyState::instance.receivedChatMessage);
                for (int i = 0; i < 9; ++i) {
                    DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[i] = 1;
                }
                DAT_GameSynchronyState::instance
                    .DAT_ChatMessageReceiverArray[DAT_GameSynchronyState::instance.currentPlayerSlotID] = 0;
                DAT_GameSynchronyState::instance.DAT_ChatTauntOrMessage = 10000;
                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                    (Commands::GameCommandType)14);
                MACRO_CALL_MEMBER(Text::UserTextHandler_Func::clearEntry, DAT_UserTextHandlerState::ptr)(
                    DAT_UserTextHandlerState::instance.textArrayIndex);
            } else if (param_1 == -13) {
                DAT_GameSynchronyState::instance.skirmishExtremeMode ^= 1;
                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                    (Commands::GameCommandType)52);
                if (DAT_GameSynchronyState::instance.skirmishExtremeMode != 0) {
                    sprintf(DAT_GameSynchronyState::instance.receivedChatMessage, "%s :%s",
                        MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)252, 13),
                        MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)74, 13));
                } else {
                    sprintf(DAT_GameSynchronyState::instance.receivedChatMessage, "%s :%s",
                        MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)252, 13),
                        MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)79, 95));
                }
                MACRO_CALL_MEMBER(Text::UserTextHandler_Func::copyIntoTextArray, DAT_UserTextHandlerState::ptr)(
                    DAT_GameSynchronyState::instance.receivedChatMessage);
                for (int i = 0; i < 9; ++i) {
                    DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[i] = 1;
                }
                DAT_GameSynchronyState::instance
                    .DAT_ChatMessageReceiverArray[DAT_GameSynchronyState::instance.currentPlayerSlotID] = 0;
                DAT_GameSynchronyState::instance.DAT_ChatTauntOrMessage = 10000;
                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                    (Commands::GameCommandType)14);
                MACRO_CALL_MEMBER(Text::UserTextHandler_Func::clearEntry, DAT_UserTextHandlerState::ptr)(
                    DAT_UserTextHandlerState::instance.textArrayIndex);
            } else if (param_1 == -14) {
                DAT_GameSynchronyState::instance.skirmishExtremeMode2 ^= 1;
                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                    (Commands::GameCommandType)52);
                if (DAT_GameSynchronyState::instance.skirmishExtremeMode != 0) {
                    sprintf(DAT_GameSynchronyState::instance.receivedChatMessage, "%s :%s",
                        MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)252, 14),
                        MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)74, 13));
                } else {
                    sprintf(DAT_GameSynchronyState::instance.receivedChatMessage, "%s :%s",
                        MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)252, 14),
                        MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)79, 95));
                }
                MACRO_CALL_MEMBER(Text::UserTextHandler_Func::copyIntoTextArray, DAT_UserTextHandlerState::ptr)(
                    DAT_GameSynchronyState::instance.receivedChatMessage);
                for (int i = 0; i < 9; ++i) {
                    DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[i] = 1;
                }
                DAT_GameSynchronyState::instance
                    .DAT_ChatMessageReceiverArray[DAT_GameSynchronyState::instance.currentPlayerSlotID] = 0;
                DAT_GameSynchronyState::instance.DAT_ChatTauntOrMessage = 10000;
                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                    (Commands::GameCommandType)14);
                MACRO_CALL_MEMBER(Text::UserTextHandler_Func::clearEntry, DAT_UserTextHandlerState::ptr)(
                    DAT_UserTextHandlerState::instance.textArrayIndex);
            } else if (param_1 == -12) {
                DAT_GameSynchronyState::instance.skirmishNoRushSetting += 1;
                if ((int)DAT_GameSynchronyState::instance.skirmishNoRushSetting >= 6) {
                    DAT_GameSynchronyState::instance.skirmishNoRushSetting = 0;
                }
                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                    (Commands::GameCommandType)52);
                if (DAT_GameSynchronyState::instance.skirmishNoRushSetting == 0) {
                    MACRO_CALL_MEMBER(Text::TextManager_Func::renderInGameText2, DAT_TextManagerObject::ptr)(
                        (DE::SHCDE::eTextSections)79, 95, DAT_ButtonX::instance + DAT_ButtonW::instance - 20,
                        DAT_ButtonY::instance + 7, Text::TTA_RIGHT, 12117749, 0, 18, FALSE,
                        (((int)DAT_ButtonBackgroundBlendStrength::instance - 32) * 32) / 32 + 32);
                }
                if (DAT_GameSynchronyState::instance.skirmishNoRushSetting == 1) {
                    MACRO_CALL_MEMBER(Text::TextManager_Func::renderInGameText2, DAT_TextManagerObject::ptr)(
                        (DE::SHCDE::eTextSections)79, 96, DAT_ButtonX::instance + DAT_ButtonW::instance - 20,
                        DAT_ButtonY::instance + 7, Text::TTA_RIGHT, 12117749, 0, 18, FALSE,
                        (((int)DAT_ButtonBackgroundBlendStrength::instance - 32) * 32) / 32 + 32);
                }
                if (DAT_GameSynchronyState::instance.skirmishNoRushSetting == 2) {
                    MACRO_CALL_MEMBER(Text::TextManager_Func::renderInGameText2, DAT_TextManagerObject::ptr)(
                        (DE::SHCDE::eTextSections)79, 97, DAT_ButtonX::instance + DAT_ButtonW::instance - 20,
                        DAT_ButtonY::instance + 7, Text::TTA_RIGHT, 12117749, 0, 18, FALSE,
                        (((int)DAT_ButtonBackgroundBlendStrength::instance - 32) * 32) / 32 + 32);
                }
                if (DAT_GameSynchronyState::instance.skirmishNoRushSetting == 3) {
                    MACRO_CALL_MEMBER(Text::TextManager_Func::renderInGameText2, DAT_TextManagerObject::ptr)(
                        (DE::SHCDE::eTextSections)79, 98, DAT_ButtonX::instance + DAT_ButtonW::instance - 20,
                        DAT_ButtonY::instance + 7, Text::TTA_RIGHT, 12117749, 0, 18, FALSE,
                        (((int)DAT_ButtonBackgroundBlendStrength::instance - 32) * 32) / 32 + 32);
                }
                if (DAT_GameSynchronyState::instance.skirmishNoRushSetting == 4) {
                    MACRO_CALL_MEMBER(Text::TextManager_Func::renderInGameText2, DAT_TextManagerObject::ptr)(
                        (DE::SHCDE::eTextSections)252, 8, DAT_ButtonX::instance + DAT_ButtonW::instance - 20,
                        DAT_ButtonY::instance + 7, Text::TTA_RIGHT, 12117749, 0, 18, FALSE,
                        (((int)DAT_ButtonBackgroundBlendStrength::instance - 32) * 32) / 32 + 32);
                }
                if (DAT_GameSynchronyState::instance.skirmishNoRushSetting == 5) {
                    MACRO_CALL_MEMBER(Text::TextManager_Func::renderInGameText2, DAT_TextManagerObject::ptr)(
                        (DE::SHCDE::eTextSections)252, 9, DAT_ButtonX::instance + DAT_ButtonW::instance - 20,
                        DAT_ButtonY::instance + 7, Text::TTA_RIGHT, 12117749, 0, 18, FALSE,
                        (((int)DAT_ButtonBackgroundBlendStrength::instance - 32) * 32) / 32 + 32);
                }
                switch (DAT_GameSynchronyState::instance.skirmishNoRushSetting) {
                case 0: {
                    sprintf(DAT_GameSynchronyState::instance.receivedChatMessage, "%s :%s",
                        MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)252, 7),
                        MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)79, 95));
                    break;
                }
                case 1: {
                    sprintf(DAT_GameSynchronyState::instance.receivedChatMessage, "%s :%s",
                        MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)252, 7),
                        MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)79, 96));
                    break;
                }
                case 2: {
                    sprintf(DAT_GameSynchronyState::instance.receivedChatMessage, "%s :%s",
                        MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)252, 7),
                        MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)79, 97));
                    break;
                }
                case 3: {
                    sprintf(DAT_GameSynchronyState::instance.receivedChatMessage, "%s :%s",
                        MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)252, 7),
                        MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)79, 98));
                    break;
                }
                case 4: {
                    sprintf(DAT_GameSynchronyState::instance.receivedChatMessage, "%s :%s",
                        MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)252, 7),
                        MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)252, 8));
                    break;
                }
                case 5: {
                    sprintf(DAT_GameSynchronyState::instance.receivedChatMessage, "%s :%s",
                        MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)252, 7),
                        MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)252, 9));
                    break;
                }
                }
                MACRO_CALL_MEMBER(Text::UserTextHandler_Func::copyIntoTextArray, DAT_UserTextHandlerState::ptr)(
                    DAT_GameSynchronyState::instance.receivedChatMessage);
                for (int i = 0; i < 9; ++i) {
                    DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[i] = 1;
                }
                DAT_GameSynchronyState::instance
                    .DAT_ChatMessageReceiverArray[DAT_GameSynchronyState::instance.currentPlayerSlotID] = 0;
                DAT_GameSynchronyState::instance.DAT_ChatTauntOrMessage = 10000;
                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                    (Commands::GameCommandType)14);
                MACRO_CALL_MEMBER(Text::UserTextHandler_Func::clearEntry, DAT_UserTextHandlerState::ptr)(
                    DAT_UserTextHandlerState::instance.textArrayIndex);
            }
            for (int i = 0; i < 9; ++i) {
                DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[i] = 1;
            }
        }

    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
