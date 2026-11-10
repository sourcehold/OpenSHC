#include "../GameLost.func.hpp"

#include "OpenSHC/Audio/MSS/SoundSystem.func.hpp"
#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Game/Skirmish.func.hpp"
#include "OpenSHC/Game/Skirmish/SkirmishLobbySetupStructure.func.hpp"
#include "OpenSHC/Rendering/Bink/BinkControlClass.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/UI/MenuItems/CustomScenarios.func.hpp"
#include "OpenSHC/UI/MenuItems/General.func.hpp"
#include "OpenSHC/UI/MenuItems/MainMenu.func.hpp"
#include "OpenSHC/UI/MenuItems/SelectCrusade.func.hpp"
#include "OpenSHC/UI/Rendering.func.hpp"
#include "OpenSHC/Audio/MSS/enums/SHC_SoundStream.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Game/TrailType.hpp"
#include "OpenSHC/Map/MapType2.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/BOOLEnum_00ed279c.hpp"
#include "OpenSHC/Globals/DAT_BinkControlState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_SoundSystemState.hpp"
#include "OpenSHC/Globals/DWORD_00ed27b4.hpp"
#include "OpenSHC/Globals/SEC_SkirmishLobbySetupStructure.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuViews {
        namespace GameLost {

            using OpenSHC::WindowsHelper::Enums::BOOLEnum;

            // FUNCTION: STRONGHOLDCRUSADER 0x004DC9E0
            void MenuView_GameLost_DoEveryFrame()
            {
                // the bink test first (the greatest-lord screen first: quick_diff 0.9221 -> 0.9026)
                if (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_SKIRMISH_AND_MULTIPLAYER) {
                    if (DAT_BinkControlState::instance.binkObjPtrArray[0] == NULL) {
                        DAT_MouseState::instance.draggingStopped = TRUE;
                    }
                } else {
                    MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderGreatestLordScreen)();
                }
                // in a campaign mission, leave 5 seconds after the first frame that gets here
                BOOLEnum timedOut = FALSE;
                if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_CAMPAIGN_MISSION
                    && DAT_GameSynchronyState::instance.currentGameMode
                        != OpenSHC::Game::GM_SKIRMISH_END_OF_GAME_SINGLE_PLAYER
                    && DAT_BinkControlState::instance.unknown02_zero[0] != 0) {
                    if (DWORD_00ed27b4::instance == 0) {
                        DWORD_00ed27b4::instance = timeGetTime();
                    } else if (timeGetTime() - DWORD_00ed27b4::instance > 5000) {
                        timedOut = TRUE;
                    }
                }
                if (!timedOut
                    && (!DAT_MouseState::instance.draggingStopped
                        || DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SKIRMISH_AND_MULTIPLAYER)
                    && !BOOLEnum_00ed279c::instance) {
                    return;
                }

                // SoundSystem::endSpeechStreamsAndResetLoopFlags (0x00424700), inlined
                DAT_SoundSystemState::instance
                    .streamFlagsUnkAndLoopCount_0x34[OpenSHC::Audio::MSS::enums::SND_STR_SPEECH_2] = 0;
                DAT_SoundSystemState::instance
                    .streamFlagsUnkAndLoopCount_0x34[OpenSHC::Audio::MSS::enums::SND_STR_SPEECH_1] = 0;
                MACRO_CALL_MEMBER(OpenSHC::Audio::MSS::SoundSystem_Func::endSoundStream, DAT_SoundSystemState::ptr)(
                    OpenSHC::Audio::MSS::enums::SND_STR_SPEECH_1);
                MACRO_CALL_MEMBER(OpenSHC::Audio::MSS::SoundSystem_Func::endSoundStream, DAT_SoundSystemState::ptr)(
                    OpenSHC::Audio::MSS::enums::SND_STR_SPEECH_2);
                MACRO_CALL_MEMBER(
                    OpenSHC::Rendering::Bink::BinkControlClass_Func::stopAllBinkPlayback, DAT_BinkControlState::ptr)();

                // one shared store at the end, as MSVC copies it into each arm (per arm: quick_diff 0.9221 -> 0.6937)
                if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SKIRMISH_AND_MULTIPLAYER) {
                    if (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER) {
                        // SKMasters slots: 0 custom skirmish, 1-50 skirmish trail, 51-80 warchest, 81-100 extreme
                        // SelectCrusade_Main: 1 skirmish trail, 2 custom skirmish, 3 warchest, 4 extreme
                        if (!DAT_GameCore::instance.isSkirmishTrail) {
                            if (!DAT_GameCore::instance.skipStoreSKMasters) {
                                MACRO_CALL(OpenSHC::Game::Skirmish_Func::StoreGameIntoSKMasters)(0);
                            }
                            MACRO_CALL(
                                OpenSHC::UI::MenuItems::SelectCrusade_Func::MenuItemActionHandler_SelectCrusade_Main)(
                                2);
                            MACRO_CALL_MEMBER(
                                OpenSHC::Game::Skirmish::SkirmishLobbySetupStructure_Func::restoreSkirmishLobbySetup,
                                SEC_SkirmishLobbySetupStructure::ptr)();
                        }
                        // compared with 1, as the original does
                        if (DAT_GameCore::instance.isSkirmishTrail == TRUE) {
                            if (DAT_GameCore::instance.currentTrailType == OpenSHC::Game::TT_EXTREME) {
                                if (!DAT_GameCore::instance.skipStoreSKMasters) {
                                    MACRO_CALL(OpenSHC::Game::Skirmish_Func::StoreGameIntoSKMasters)(
                                        DAT_GameCore::instance.extremeTrailProgress + 81);
                                }
                                MACRO_CALL(OpenSHC::UI::MenuItems::SelectCrusade_Func::
                                        MenuItemActionHandler_SelectCrusade_Main)(4);
                            } else if (DAT_GameCore::instance.currentTrailType == OpenSHC::Game::TT_WARCHEST) {
                                if (!DAT_GameCore::instance.skipStoreSKMasters) {
                                    MACRO_CALL(OpenSHC::Game::Skirmish_Func::StoreGameIntoSKMasters)(
                                        DAT_GameCore::instance.warchestTrailProgress + 51);
                                }
                                MACRO_CALL(OpenSHC::UI::MenuItems::SelectCrusade_Func::
                                        MenuItemActionHandler_SelectCrusade_Main)(3);
                            } else {
                                if (!DAT_GameCore::instance.skipStoreSKMasters) {
                                    MACRO_CALL(OpenSHC::Game::Skirmish_Func::StoreGameIntoSKMasters)(
                                        DAT_GameCore::instance.skirmishTrailProgress + 1);
                                }
                                MACRO_CALL(OpenSHC::UI::MenuItems::SelectCrusade_Func::
                                        MenuItemActionHandler_SelectCrusade_Main)(1);
                            }
                        }
                    } else if (DAT_GameSynchronyState::instance.currentGameMode
                        == OpenSHC::Game::GM_SKIRMISH_END_OF_GAME_SINGLE_PLAYER) {
                        DAT_GameSynchronyState::instance.currentGameMode = OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER;
                        MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                            OpenSHC::UI::Enums::MVT_RANKING_GAMES, 0);
                    } else {
                        // 7 is the "Quit Mission" action
                        DAT_MenuTextInputState::instance.DAT_MenuOptionsActionParameter = 7;
                        MACRO_CALL(OpenSHC::UI::MenuItems::General_Func::
                                MenuItemActionHandler_General_LaunchOrQuitMultiplayerGameUnk)(22);
                        if (DAT_GameSynchronyState::instance.isHost) {
                            MACRO_CALL_MEMBER(
                                OpenSHC::Game::Skirmish::SkirmishLobbySetupStructure_Func::restoreSkirmishLobbySetup,
                                SEC_SkirmishLobbySetupStructure::ptr)();
                            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                                DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_HOST_SHARE_LOBBY_STATE);
                        }
                    }
                } else if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_CAMPAIGN_MISSION) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::Game::GameCore_Func::switchToScenarioDescriptionMenuView, DAT_GameCore::ptr)();
                } else if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_ECONOMIC_CAMPAIGN_SH1) {
                    MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::exitToScenarioDescriptionMenu, DAT_GameCore::ptr)();
                } else if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_BUILDERUnk) {
                    // a switch, as the original's sub / je (if / else: quick_diff 0.9221 -> 0.9121)
                    switch (DAT_MapPropertiesState::instance.SEC_U3_MapType2_1) {
                    case OpenSHC::Map::MT_ECONOMIC:
                        MACRO_CALL(OpenSHC::UI::MenuItems::MainMenu_Func::MenuItemActionHandler_MainMenu_Main)(3);
                        break;
                    default:
                        MACRO_CALL(
                            OpenSHC::UI::MenuItems::CustomScenarios_Func::MenuItemActionHandler_CustomScenarios_Main)(
                            4);
                        break;
                    }
                } else {
                    MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                        OpenSHC::UI::Enums::MVT_MAIN_MENU, 0);
                }
                DAT_GameCore::instance.skipStoreSKMasters = 0;
            }

        }
    }
}
}
