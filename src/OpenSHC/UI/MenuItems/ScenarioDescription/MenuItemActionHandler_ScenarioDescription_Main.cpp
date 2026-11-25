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
#include "OpenSHC/Map/MapType2.hpp"
#include "OpenSHC/UI/Enums/BuildMenuTabType.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_00ed2794.hpp"
#include "OpenSHC/Globals/DAT_00ed2798.hpp"
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
#include "OpenSHC/Globals/INT_00eb0b24.hpp"
#include "OpenSHC/Globals/INT_00ed27bc.hpp"
#include "OpenSHC/Globals/INT_00ed27c4.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x004D8570
        void ScenarioDescription::MenuItemActionHandler_ScenarioDescription_Main(int button, ...)
        {
            if (DAT_MenuTextInputState::instance.currentModalDialog != OpenSHC::UI::Enums::MMT_NO_MENU) {
                return;
            }
            switch (button) {
            case 10:
                // start the mission
                MACRO_CALL_MEMBER(
                    OpenSHC::Text::TextEditorState_Func::closeHelpDialogAndReturnToMenu, DAT_TextEditorState::ptr)();
                if (DAT_GameCore::instance.gameSuspended == 1) {
                    MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                        OpenSHC::UI::Enums::MVT_BUILD_MENU, 0);
                    return;
                }
                if (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_BUILDERUnk) {
                    if (DAT_GameCore::instance.missionNumber1to20 <= 0) {
                        DAT_GameCore::instance.missionNumber1to20 = 1;
                    }
                    DAT_GameCore::instance.section1066 = 1;
                    DAT_GameCore::instance.landscapingmenuMenuTabToSwitchTo.buildMenuTab = 231;
                    MACRO_CALL_MEMBER(OpenSHC::Map::MapPropertiesState_Func::loadMissionMapAndSetLord,
                        DAT_MapPropertiesState::ptr)(DAT_GameCore::instance.missionNumber1to20);
                    MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                        DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_ASK_FOR_SLOT_ASSIGNMENT);
                    MACRO_CALL(OpenSHC::Synchrony_Func::SetAIPlayerNickNames)();
                    if (DAT_GameCore::instance.missionNumber1to20 >= 16) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::Synchrony::GameSynchronyState_Func::initializeFinalResultsForActivePlayers,
                            DAT_GameSynchronyState::ptr)();
                    }
                }
                DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.buildMenuTab = OpenSHC::UI::Enums::BMTT_CASTLE;
                MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    OpenSHC::UI::Enums::MVT_BUILD_MENU, 0);
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::MenuTextInputState_Func::clearModalDialog2to6, DAT_MenuTextInputState::ptr)();
                DAT_00ed2794::instance = 0;
                MACRO_CALL_MEMBER(OpenSHC::Audio::MSS::SoundSystem_Func::endSpeechStreamsAndResetLoopFlags,
                    DAT_SoundSystemState::ptr)();
                MACRO_CALL_MEMBER(OpenSHC::Input::MouseState_Func::resetMouseState2, DAT_MouseState::ptr)();
                return;
            case 12:
            case 13:
                // in the builder: back to the map choice, or ask first while a game is suspended
                if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_BUILDERUnk) {
                    // the map choice's mission type: 0 just build, 1 economic, 2 siege, 3 invasion
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
                        break;
                    }
                    if (!DAT_GameCore::instance.gameSuspended) {
                        for (int i = 0; i < countof(DAT_BlendingDefinedData::instance.PlayerSlotUnitColor); ++i) {
                            DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[i]
                                = DAT_BlendingDefinedData::instance.DefaultPlayerSlotUnitColor[i];
                        }
                        MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                            OpenSHC::UI::Enums::MVT_SINGLEPLAYER_MAP_CHOICE, 0);
                        return;
                    }
                    DAT_MenuTextInputState::instance.DAT_MenuOptionsActionParameter = -7;
                    MACRO_CALL_MEMBER(OpenSHC::UI::MenuTextInputState_Func::activateModalDialogAndClearText,
                        DAT_MenuTextInputState::ptr)(OpenSHC::UI::Enums::MMT_YES_NO_DIALOG);
                    return;
                }
                // otherwise as 11
            case 11:
                if (INT_00ed27bc::instance == 1) {
                    INT_00ed27bc::instance = 0;
                    return;
                }
                MACRO_CALL_MEMBER(
                    OpenSHC::Text::TextEditorState_Func::closeHelpDialogAndReturnToMenu, DAT_TextEditorState::ptr)();
                MACRO_CALL_MEMBER(OpenSHC::Audio::MSS::SoundSystem_Func::endSpeechStreamsAndResetLoopFlags,
                    DAT_SoundSystemState::ptr)();
                if (!DAT_GameCore::instance.gameSuspended) {
                    if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_CAMPAIGN_MISSION) {
                        MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                            OpenSHC::UI::Enums::MVT_HISTORIC_MISSION_SELECT, 0);
                        return;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                        OpenSHC::UI::Enums::MVT_UNUSED_ECONOMIC_MISSION_SELECTUnk, 0);
                    return;
                }
                DAT_MenuTextInputState::instance.DAT_MenuOptionsActionParameter = 1000;
                MACRO_CALL_MEMBER(OpenSHC::UI::MenuTextInputState_Func::activateModalDialogAndClearText,
                    DAT_MenuTextInputState::ptr)(OpenSHC::UI::Enums::MMT_YES_NO_DIALOG);
                return;
            case 6:
                if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_CAMPAIGN_MISSION
                    || DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_ECONOMIC_CAMPAIGN_SH1) {
                    DAT_00ed2798::instance = 0;
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::closeHelpDialogAndReturnToMenu,
                        DAT_TextEditorState::ptr)();
                }
                return;
            case 8:
                if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_CAMPAIGN_MISSION
                    || DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_ECONOMIC_CAMPAIGN_SH1) {
                    DAT_00ed2798::instance = 2;
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::closeHelpDialogAndReturnToMenu,
                        DAT_TextEditorState::ptr)();
                }
                return;
            case 9:
                // the mission's help page
                if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_CAMPAIGN_MISSION
                    || DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_ECONOMIC_CAMPAIGN_SH1) {
                    DAT_00ed2798::instance = 3;
                    char helpSectionName[100];
                    // "mission%d.hlp"
                    MACRO_CALL(OpenSHC::OS_Func::_sprintf)(
                        helpSectionName, s_mission_d_hlp_005aaf7c, DAT_GameCore::instance.missionNumber1to20);
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextEditorState_Func::openScenarioHelpDialog, DAT_TextEditorState::ptr)(
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::findOrAddHelpSectionName,
                            DAT_TextEditorState::ptr)(helpSectionName));
                }
                return;
            case -1:
                // "Difficulty": from 0 to 3 and round again
                if (DAT_00ed2798::instance == 0
                    && (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_CAMPAIGN_MISSION
                        || DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_ECONOMIC_CAMPAIGN_SH1)
                    && !DAT_GameCore::instance.gameSuspended) {
                    ++DAT_GameState::instance.mapAndTime.difficulty;
                    if (DAT_GameState::instance.mapAndTime.difficulty > 3) {
                        DAT_GameState::instance.mapAndTime.difficulty = 0;
                    }
                    if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_CAMPAIGN_MISSION) {
                        DAT_GameCore::instance.missionDifficulty = DAT_GameState::instance.mapAndTime.difficulty;
                        MACRO_CALL(OpenSHC::UI::Helpers_Func::ResetEventStatusUnk)();
                        return;
                    }
                    DAT_GameCore::instance.missionDifficulty2 = DAT_GameState::instance.mapAndTime.difficulty;
                    MACRO_CALL(OpenSHC::UI::Helpers_Func::ResetEventStatusUnk)();
                }
                return;
            case -2: // "View Briefing"
                INT_00ed27bc::instance = 1;
                return;
            case -3: // "Restart Mission", asked first
                DAT_MenuTextInputState::instance.DAT_MenuOptionsActionParameter = 44;
                MACRO_CALL_MEMBER(OpenSHC::UI::MenuTextInputState_Func::activateModalDialogAndClearText,
                    DAT_MenuTextInputState::ptr)(OpenSHC::UI::Enums::MMT_YES_NO_DIALOG);
                return;
            case -4: // "Next": the next description page
                ++INT_00eb0b24::instance;
                if (INT_00eb0b24::instance >= INT_00ed27c4::instance) {
                    INT_00eb0b24::instance = 0;
                }
                return;
            }
        }

    }
}
}
