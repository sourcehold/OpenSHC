#include "../ScenarioDescription.func.hpp"

#include "OpenSHC/Audio/MSS/SoundSystem.func.hpp"
#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Input/MouseState.func.hpp"
#include "OpenSHC/Map/MapPropertiesState.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Synchrony.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Text/TextEditorState.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/MenuTextInputState.func.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/UI/Enums/BuildingsAndStatusMenuTabType.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Map/MapType2.hpp"
#include "OpenSHC/Globals/DAT_00eb0b24.hpp"
#include "OpenSHC/Globals/DAT_00ed2794.hpp"
#include "OpenSHC/Globals/DAT_00ed2798.hpp"
#include "OpenSHC/Globals/DAT_00ed27bc.hpp"
#include "OpenSHC/Globals/DAT_BlendingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MapMissionType.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_SoundSystemState.hpp"
#include "OpenSHC/Globals/DAT_TextEditorState.hpp"
#include "OpenSHC/Globals/INT_00ed27c4.hpp"
#include "OpenSHC/Globals/MSVC_SecurityCookie.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::Commands::GameCommandType;
        using OpenSHC::Game::GameMode2;
        using OpenSHC::UI::Enums::BuildingsAndStatusMenuTabType;
        using OpenSHC::UI::Enums::MenuModalType;
        using OpenSHC::UI::Enums::MenuViewType;

        /*
          WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
         */
        /*
          WARNING: Enum "DPERRInt": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004D8570
        void ScenarioDescription::MenuItemActionHandler_ScenarioDescription_Main(int param_1, ...)
        {
            int iVar1;
            char local_68[100];
            uint local_4;
            local_4 = MSVC_SecurityCookie::instance ^ (uint)local_68;
            if (DAT_MenuTextInputState::instance.currentModalDialog == OpenSHC::UI::Enums::MMT_NO_MENU) {
                switch (param_1) {
                case 6:
                    if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_CAMPAIGN_MISSION)
                        || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_ECONOMIC_CAMPAIGN_SH1)) {
                        DAT_00ed2798::instance = 0;
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::closeHelpDialogAndReturnToMenu,
                            DAT_TextEditorState::ptr)();
                        ;
                    }
                    break;
                case 8:
                    if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_CAMPAIGN_MISSION)
                        || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_ECONOMIC_CAMPAIGN_SH1)) {
                        DAT_00ed2798::instance = 2;
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::closeHelpDialogAndReturnToMenu,
                            DAT_TextEditorState::ptr)();
                        ;
                    }
                    break;
                case 9:
                    if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_CAMPAIGN_MISSION)
                        || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_ECONOMIC_CAMPAIGN_SH1)) {
                        DAT_00ed2798::instance = 3;
                        MACRO_CALL(OpenSHC::OS_Func::_sprintf)(
                            local_68, "mission%d.hlp", DAT_GameCore::instance.missionNumber1to20);
                        iVar1 = MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::findOrAddHelpSectionName,
                            DAT_TextEditorState::ptr)(local_68);
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::openScenarioHelpDialog,
                            DAT_TextEditorState::ptr)(iVar1);
                        ;
                    }
                    break;
                case 10:
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::closeHelpDialogAndReturnToMenu,
                        DAT_TextEditorState::ptr)();
                    if (DAT_GameCore::instance.field22_0x64 == 1) {
                        MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                            OpenSHC::UI::Enums::MVT_BUILD_MENU, 0);
                        ;
                    }
                    if (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_BUILDERUnk) {
                        if (DAT_GameCore::instance.missionNumber1to20 < 1) {
                            DAT_GameCore::instance.missionNumber1to20 = 1;
                        }
                        DAT_GameCore::instance.section1066 = 1;
                        DAT_GameCore::instance.landscapingmenuMenuTabToSwitchTo = 0xe7;
                        MACRO_CALL_MEMBER(OpenSHC::Map::MapPropertiesState_Func::loadMissionMapAndSetLord,
                            DAT_MapPropertiesState::ptr)(DAT_GameCore::instance.missionNumber1to20);
                        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                            DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_ASK_FOR_SLOT_ASSIGNMENT);
                        MACRO_CALL(OpenSHC::Synchrony_Func::SetAIPlayerNickNames)();
                        if (0xf < DAT_GameCore::instance.missionNumber1to20) {
                            MACRO_CALL_MEMBER(
                                OpenSHC::Synchrony::GameSynchronyState_Func::initializeFinalResultsForActivePlayers,
                                DAT_GameSynchronyState::ptr)();
                        }
                    }
                    DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.tabType = OpenSHC::UI::Enums::BASMTT_HUNTERSHUT;
                    MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                        OpenSHC::UI::Enums::MVT_BUILD_MENU, 0);
                    MACRO_CALL_MEMBER(
                        OpenSHC::UI::MenuTextInputState_Func::clearModalDialog2to6, DAT_MenuTextInputState::ptr)();
                    DAT_00ed2794::instance = 0;
                    MACRO_CALL_MEMBER(OpenSHC::Audio::MSS::SoundSystem_Func::endSpeechStreamsAndResetLoopFlags,
                        DAT_SoundSystemState::ptr)();
                    MACRO_CALL_MEMBER(OpenSHC::Input::MouseState_Func::resetMouseState2, DAT_MouseState::ptr)();
                    ;
                    return;
                case 0xc:
                case 0xd:
                    if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_BUILDERUnk) {
                        switch (DAT_MapPropertiesState::instance.SEC_U3_MapType2_1) {
                        case OpenSHC::Map::MT_SIEGE:
                            DAT_MapMissionType::instance = 2;
                            break;
                        case OpenSHC::Map::MT_INVASION:
                            DAT_MapMissionType::instance = 3;
                            break;
                        case OpenSHC::Map::MT_ECONOMIC:
                            DAT_MapMissionType::instance = 1;
                            break;
                        case OpenSHC::Map::MT_JUST_BUILD:
                            DAT_MapMissionType::instance = 0;
                        }
                        if (DAT_GameCore::instance.field22_0x64 == 0) {
                            DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[0]
                                = DAT_BlendingDefinedData::instance.DefaultPlayerSlotUnitColor[0];
                            DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[1]
                                = DAT_BlendingDefinedData::instance.DefaultPlayerSlotUnitColor[1];
                            DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[2]
                                = DAT_BlendingDefinedData::instance.DefaultPlayerSlotUnitColor[2];
                            DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[3]
                                = DAT_BlendingDefinedData::instance.DefaultPlayerSlotUnitColor[3];
                            DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[4]
                                = DAT_BlendingDefinedData::instance.DefaultPlayerSlotUnitColor[4];
                            DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[5]
                                = DAT_BlendingDefinedData::instance.DefaultPlayerSlotUnitColor[5];
                            DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[6]
                                = DAT_BlendingDefinedData::instance.DefaultPlayerSlotUnitColor[6];
                            DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[7]
                                = DAT_BlendingDefinedData::instance.DefaultPlayerSlotUnitColor[7];
                            DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[8]
                                = DAT_BlendingDefinedData::instance.DefaultPlayerSlotUnitColor[8];
                            MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                                OpenSHC::UI::Enums::MVT_SINGLEPLAYER_MAP_CHOICE, 0);
                            ;
                        }
                        DAT_MenuTextInputState::instance.DAT_MenuOptionsActionParameter = 0xfffffff9;
                        MACRO_CALL_MEMBER(OpenSHC::UI::MenuTextInputState_Func::activateModalDialogAndClearText,
                            DAT_MenuTextInputState::ptr)(OpenSHC::UI::Enums::MMT_YES_NO_DIALOG);
                        ;
                    }
                case 0xb:
                    if (DAT_00ed27bc::instance == 1) {
                        DAT_00ed27bc::instance = 0;
                        ;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::closeHelpDialogAndReturnToMenu,
                        DAT_TextEditorState::ptr)();
                    MACRO_CALL_MEMBER(OpenSHC::Audio::MSS::SoundSystem_Func::endSpeechStreamsAndResetLoopFlags,
                        DAT_SoundSystemState::ptr)();
                    if (DAT_GameCore::instance.field22_0x64 == 0) {
                        if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_CAMPAIGN_MISSION) {
                            MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                                OpenSHC::UI::Enums::MVT_HISTORIC_MISSION_SELECT, 0);
                            ;
                        }
                        MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                            OpenSHC::UI::Enums::MVT_UNUSED_ECONOMIC_MISSION_SELECTUnk, 0);
                        ;
                    }
                    DAT_MenuTextInputState::instance.DAT_MenuOptionsActionParameter = 1000;
                    MACRO_CALL_MEMBER(OpenSHC::UI::MenuTextInputState_Func::activateModalDialogAndClearText,
                        DAT_MenuTextInputState::ptr)(OpenSHC::UI::Enums::MMT_YES_NO_DIALOG);
                    ;
                    return;
                case -4:
                    DAT_00eb0b24::instance = DAT_00eb0b24::instance + 1;
                    if (INT_00ed27c4::instance <= DAT_00eb0b24::instance) {
                        DAT_00eb0b24::instance = 0;
                    }
                    break;
                case -3:
                    DAT_MenuTextInputState::instance.DAT_MenuOptionsActionParameter = 0x2c;
                    MACRO_CALL_MEMBER(OpenSHC::UI::MenuTextInputState_Func::activateModalDialogAndClearText,
                        DAT_MenuTextInputState::ptr)(OpenSHC::UI::Enums::MMT_YES_NO_DIALOG);
                    ;
                    return;
                case -2:
                    DAT_00ed27bc::instance = 1;
                    ;
                    return;
                case -1:
                    if ((DAT_00ed2798::instance == 0)
                        && (((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_CAMPAIGN_MISSION
                                 || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_ECONOMIC_CAMPAIGN_SH1))
                            && (DAT_GameCore::instance.field22_0x64 == 0)))) {
                        DAT_GameState::instance.mapAndTime.difficulty
                            = DAT_GameState::instance.mapAndTime.difficulty + 1;
                        if (3 < DAT_GameState::instance.mapAndTime.difficulty) {
                            DAT_GameState::instance.mapAndTime.difficulty = 0;
                        }
                        if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_CAMPAIGN_MISSION) {
                            DAT_GameCore::instance.missionDifficulty = DAT_GameState::instance.mapAndTime.difficulty;
                            MACRO_CALL(OpenSHC::UI::Helpers_Func::ResetEventStatusUnk)();
                            ;
                        }
                        DAT_GameCore::instance.missionDifficulty2 = DAT_GameState::instance.mapAndTime.difficulty;
                        MACRO_CALL(OpenSHC::UI::Helpers_Func::ResetEventStatusUnk)();
                        ;
                    }
                }
            };
        }

    }
}
}
