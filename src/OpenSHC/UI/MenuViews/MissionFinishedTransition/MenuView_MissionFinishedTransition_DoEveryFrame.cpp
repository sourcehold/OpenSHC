#include "../MissionFinishedTransition.func.hpp"

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
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
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
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_SoundSystemState.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"
#include "OpenSHC/Globals/DWORD_00ed27b4.hpp"
#include "OpenSHC/Globals/SEC_SkirmishLobbySetupStructure.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuViews {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x004DC500
        void MissionFinishedTransition::MenuView_MissionFinishedTransition_DoEveryFrame()
        {
            if (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_SKIRMISH_AND_MULTIPLAYER) {
                if (DAT_BinkControlState::instance.binkObjPtrArray[0] == NULL) {
                    DAT_MouseState::instance.draggingStopped = TRUE;
                }
            } else {
                if (DAT_GameSynchronyState::instance.currentGameMode
                    == OpenSHC::Game::GM_SKIRMISH_END_OF_GAME_SINGLE_PLAYER) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::drawGfxOnFlaggedSurface,
                        DAT_TextureRenderCoreObject::ptr)(0,
                        (DAT_WindowAndDirectDraw::instance.resolutionX
                            - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].width)
                            / 2,
                        (DAT_WindowAndDirectDraw::instance.resolutionY
                            - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height)
                            / 2);
                }
                MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderGreatestLordScreen)();
            }
            // a flag, not a goto: the timed-out path skips the return below
            BOOLEnum waitedLongEnough = FALSE;
            if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_CAMPAIGN_MISSION
                && DAT_GameSynchronyState::instance.currentGameMode
                    != OpenSHC::Game::GM_SKIRMISH_END_OF_GAME_SINGLE_PLAYER
                && DAT_BinkControlState::instance.unknown02_zero[0] != 0) {
                if (DWORD_00ed27b4::instance == 0) {
                    DWORD_00ed27b4::instance = timeGetTime();
                } else if (timeGetTime() - DWORD_00ed27b4::instance > 5000) {
                    waitedLongEnough = TRUE;
                }
            }
            if (!waitedLongEnough
                && (!DAT_MouseState::instance.draggingStopped
                    || DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SKIRMISH_AND_MULTIPLAYER)
                && !BOOLEnum_00ed279c::instance) {
                return;
            }
            // endSpeechStreamsAndResetLoopFlags, written out inline
            DAT_SoundSystemState::instance.streamFlagsUnkAndLoopCount_0x34[OpenSHC::Audio::MSS::enums::SND_STR_SPEECH_2]
                = 0;
            DAT_SoundSystemState::instance.streamFlagsUnkAndLoopCount_0x34[OpenSHC::Audio::MSS::enums::SND_STR_SPEECH_1]
                = 0;
            MACRO_CALL_MEMBER(OpenSHC::Audio::MSS::SoundSystem_Func::endSoundStream, DAT_SoundSystemState::ptr)(
                OpenSHC::Audio::MSS::enums::SND_STR_SPEECH_1);
            MACRO_CALL_MEMBER(OpenSHC::Audio::MSS::SoundSystem_Func::endSoundStream, DAT_SoundSystemState::ptr)(
                OpenSHC::Audio::MSS::enums::SND_STR_SPEECH_2);
            MACRO_CALL_MEMBER(
                OpenSHC::Rendering::Bink::BinkControlClass_Func::stopAllBinkPlayback, DAT_BinkControlState::ptr)();
            if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SKIRMISH_AND_MULTIPLAYER) {
                if (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER) {
                    if (!DAT_GameCore::instance.isSkirmishTrail) {
                        if (!DAT_GameCore::instance.skipStoreSKMasters) {
                            MACRO_CALL(OpenSHC::Game::Skirmish_Func::StoreGameIntoSKMasters)(0);
                        }
                        MACRO_CALL(
                            OpenSHC::UI::MenuItems::SelectCrusade_Func::MenuItemActionHandler_SelectCrusade_Main)(2);
                        MACRO_CALL_MEMBER(
                            OpenSHC::Game::Skirmish::SkirmishLobbySetupStructure_Func::restoreSkirmishLobbySetup,
                            SEC_SkirmishLobbySetupStructure::ptr)();
                    }
                    // compared with TRUE, as the original does
                    if (DAT_GameCore::instance.isSkirmishTrail == TRUE) {
                        if (!DAT_GameCore::instance.skipStoreSKMasters) {
                            if (DAT_GameCore::instance.currentTrailType == OpenSHC::Game::TT_EXTREME) {
                                MACRO_CALL(OpenSHC::Game::Skirmish_Func::StoreGameIntoSKMasters)(
                                    DAT_GameCore::instance.extremeTrailProgress + 81);
                            } else if (DAT_GameCore::instance.currentTrailType == OpenSHC::Game::TT_WARCHEST) {
                                MACRO_CALL(OpenSHC::Game::Skirmish_Func::StoreGameIntoSKMasters)(
                                    DAT_GameCore::instance.warchestTrailProgress + 51);
                            } else {
                                MACRO_CALL(OpenSHC::Game::Skirmish_Func::StoreGameIntoSKMasters)(
                                    DAT_GameCore::instance.skirmishTrailProgress + 1);
                            }
                        }
                        int progressBefore = DAT_GameCore::instance.skirmishTrailProgress;
                        if (DAT_GameCore::instance.currentTrailType == OpenSHC::Game::TT_EXTREME) {
                            progressBefore = DAT_GameCore::instance.extremeTrailProgress;
                        } else if (DAT_GameCore::instance.currentTrailType == OpenSHC::Game::TT_WARCHEST) {
                            progressBefore = DAT_GameCore::instance.warchestTrailProgress;
                        }
                        if (DAT_GameState::instance.mapAndTime
                                .playerIsAlive[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            != 0) {
                            int const months = DAT_GameState::instance.mapAndTime.month
                                + DAT_GameState::instance.mapAndTime.year * 12;
                            if (DAT_GameCore::instance.currentTrailType == OpenSHC::Game::TT_EXTREME) {
                                if (months - DAT_GameCore::instance.extremeTrailStartDateMonths
                                        < DAT_GameCore::instance.extremeTrailMonthsTakenOrChicken[DAT_GameCore::instance
                                                .extremeTrailProgress]
                                    || DAT_GameCore::instance.extremeTrailMonthsTakenOrChicken[DAT_GameCore::instance
                                               .extremeTrailProgress]
                                        < 0) {
                                    DAT_GameCore::instance
                                        .extremeTrailMonthsTakenOrChicken[DAT_GameCore::instance.extremeTrailProgress]
                                        = months - DAT_GameCore::instance.extremeTrailStartDateMonths;
                                    MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::setStartDateUnk, DAT_GameCore::ptr)(
                                        3);
                                }
                            } else if (DAT_GameCore::instance.currentTrailType == OpenSHC::Game::TT_WARCHEST) {
                                if (months - DAT_GameCore::instance.warchestTrailStartDateMonths
                                        < DAT_GameCore::instance.warchestTrailMonthsTakenOrChicken
                                            [DAT_GameCore::instance.warchestTrailProgress]
                                    || DAT_GameCore::instance.warchestTrailMonthsTakenOrChicken[DAT_GameCore::instance
                                               .warchestTrailProgress]
                                        < 0) {
                                    DAT_GameCore::instance
                                        .warchestTrailMonthsTakenOrChicken[DAT_GameCore::instance.warchestTrailProgress]
                                        = months - DAT_GameCore::instance.warchestTrailStartDateMonths;
                                    MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::setStartDateUnk, DAT_GameCore::ptr)(
                                        2);
                                }
                            } else {
                                if (months - DAT_GameCore::instance.skirmishTrailStartDateMonths
                                        < DAT_GameCore::instance.skirmishTrailMonthsTakenOrChicken
                                            [DAT_GameCore::instance.skirmishTrailProgress]
                                    || DAT_GameCore::instance.skirmishTrailMonthsTakenOrChicken[DAT_GameCore::instance
                                               .skirmishTrailProgress]
                                        < 0) {
                                    DAT_GameCore::instance
                                        .skirmishTrailMonthsTakenOrChicken[DAT_GameCore::instance.skirmishTrailProgress]
                                        = months - DAT_GameCore::instance.skirmishTrailStartDateMonths;
                                    MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::setStartDateUnk, DAT_GameCore::ptr)(
                                        1);
                                }
                            }
                        }
                        // each trail's step nested like this, as the original lays out the three trails
                        if (DAT_GameCore::instance.currentTrailType == OpenSHC::Game::TT_EXTREME) {
                            if (DAT_GameState::instance.mapAndTime
                                        .playerIsAlive[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                    != 0
                                && DAT_GameCore::instance.extremeTrailProgress
                                    >= DAT_GameCore::instance.furthestExtremeTrailMission) {
                                DAT_GameCore::instance.furthestExtremeTrailMission
                                    = DAT_GameCore::instance.extremeTrailProgress + 1;
                                if (DAT_GameCore::instance.extremeTrailProgress < 19) {
                                    ++DAT_GameCore::instance.extremeTrailProgress;
                                }
                            } else if (DAT_GameState::instance.mapAndTime
                                           .playerIsAlive[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                    != 0
                                && DAT_GameCore::instance.extremeTrailProgress < 19) {
                                ++DAT_GameCore::instance.extremeTrailProgress;
                            }
                            if (DAT_GameState::instance.mapAndTime
                                        .playerIsAlive[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                    != 0
                                && DAT_GameCore::instance.extremeTrailProgress == 19
                                && progressBefore == DAT_GameCore::instance.extremeTrailProgress) {
                                MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                                    OpenSHC::UI::Enums::MVT_CRUSADE_ENDSCREEN, 0);
                            } else {
                                MACRO_CALL(OpenSHC::UI::MenuItems::SelectCrusade_Func::
                                        MenuItemActionHandler_SelectCrusade_Main)(4);
                            }
                        } else if (DAT_GameCore::instance.currentTrailType == OpenSHC::Game::TT_WARCHEST) {
                            if (DAT_GameState::instance.mapAndTime
                                        .playerIsAlive[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                    != 0
                                && DAT_GameCore::instance.warchestTrailProgress
                                    >= DAT_GameCore::instance.furthestWarchestTrailMission) {
                                DAT_GameCore::instance.furthestWarchestTrailMission
                                    = DAT_GameCore::instance.warchestTrailProgress + 1;
                                if (DAT_GameCore::instance.warchestTrailProgress < 29) {
                                    ++DAT_GameCore::instance.warchestTrailProgress;
                                }
                            } else if (DAT_GameState::instance.mapAndTime
                                           .playerIsAlive[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                    != 0
                                && DAT_GameCore::instance.warchestTrailProgress < 29) {
                                ++DAT_GameCore::instance.warchestTrailProgress;
                            }
                            if (DAT_GameState::instance.mapAndTime
                                        .playerIsAlive[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                    != 0
                                && DAT_GameCore::instance.warchestTrailProgress == 29
                                && progressBefore == DAT_GameCore::instance.warchestTrailProgress) {
                                MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                                    OpenSHC::UI::Enums::MVT_CRUSADE_ENDSCREEN, 0);
                            } else {
                                MACRO_CALL(OpenSHC::UI::MenuItems::SelectCrusade_Func::
                                        MenuItemActionHandler_SelectCrusade_Main)(3);
                            }
                        } else {
                            if (DAT_GameState::instance.mapAndTime
                                        .playerIsAlive[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                    != 0
                                && DAT_GameCore::instance.skirmishTrailProgress
                                    >= DAT_GameCore::instance.furthestSkirmishTrailMission) {
                                DAT_GameCore::instance.furthestSkirmishTrailMission
                                    = DAT_GameCore::instance.skirmishTrailProgress + 1;
                                if (DAT_GameCore::instance.skirmishTrailProgress < 49) {
                                    ++DAT_GameCore::instance.skirmishTrailProgress;
                                }
                            } else if (DAT_GameState::instance.mapAndTime
                                           .playerIsAlive[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                    != 0
                                && DAT_GameCore::instance.skirmishTrailProgress < 49) {
                                ++DAT_GameCore::instance.skirmishTrailProgress;
                            }
                            if (DAT_GameState::instance.mapAndTime
                                        .playerIsAlive[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                    != 0
                                && DAT_GameCore::instance.skirmishTrailProgress == 49
                                && progressBefore == DAT_GameCore::instance.skirmishTrailProgress) {
                                MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                                    OpenSHC::UI::Enums::MVT_CRUSADE_ENDSCREEN, 0);
                            } else {
                                MACRO_CALL(OpenSHC::UI::MenuItems::SelectCrusade_Func::
                                        MenuItemActionHandler_SelectCrusade_Main)(1);
                            }
                        }
                    }
                } else if (DAT_GameSynchronyState::instance.currentGameMode
                    == OpenSHC::Game::GM_SKIRMISH_END_OF_GAME_SINGLE_PLAYER) {
                    DAT_GameSynchronyState::instance.currentGameMode = OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER;
                    MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                        OpenSHC::UI::Enums::MVT_RANKING_GAMES, 0);
                } else {
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
                DAT_GameCore::instance.gameSuspended = 0;
                if (DAT_GameCore::instance.missionNumber1to20 > DAT_GameCore::instance.historicCampaignNumber * 5) {
                    MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                        OpenSHC::UI::Enums::MVT_HISTORIC_CAMPAIGN_OUTRO, 0);
                } else {
                    MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                        OpenSHC::UI::Enums::MVT_HISTORIC_MISSION_PICTURE, 0);
                }
            } else if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_ECONOMIC_CAMPAIGN_SH1) {
                DAT_GameCore::instance.gameSuspended = 0;
                if (DAT_GameCore::instance.missionNumber1to20 > 37) {
                    MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                        OpenSHC::UI::Enums::MVT_MAIN_MENU, 0);
                } else {
                    MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                        OpenSHC::UI::Enums::MVT_SCENARIO_DESCRIPTION, 0);
                }
            } else if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_BUILDERUnk) {
                // a switch on the map type, as the original dispatches it
                switch (DAT_MapPropertiesState::instance.SEC_U3_MapType2_1) {
                case OpenSHC::Map::MT_ECONOMIC:
                    MACRO_CALL(OpenSHC::UI::MenuItems::MainMenu_Func::MenuItemActionHandler_MainMenu_Main)(3);
                    break;
                default:
                    MACRO_CALL(
                        OpenSHC::UI::MenuItems::CustomScenarios_Func::MenuItemActionHandler_CustomScenarios_Main)(4);
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
