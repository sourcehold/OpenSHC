// disable deprecation warnings for strcpy and strcat
#pragma warning(disable : 4996)

#include "../General.func.hpp"

#include "OpenSHC/Audio/MSS/SoundSystem.func.hpp"
#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Game/Skirmish.func.hpp"
#include "OpenSHC/Game/Skirmish/SkirmishLobbySetupStructure.func.hpp"
#include "OpenSHC/IO/FilePackager.func.hpp"
#include "OpenSHC/IO/ResourceManager.func.hpp"
#include "OpenSHC/Input/MouseState.func.hpp"
#include "OpenSHC/Map.func.hpp"
#include "OpenSHC/Map/MapPropertiesState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/UI/Actions.func.hpp"
#include "OpenSHC/UI/MenuItems/CustomScenarios.func.hpp"
#include "OpenSHC/UI/MenuItems/HistoricCampaignSelect.func.hpp"
#include "OpenSHC/UI/MenuItems/MainMenu.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/UI/MenuTextInputState.func.hpp"
#include "OpenSHC/UI/Rendering.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/UI/Rendering/WindowAndDirectDraw.func.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/DE/SHCDE/eMusicIDs.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Game/GameModeInt.hpp"
#include "OpenSHC/Game/TrailType.hpp"
#include "OpenSHC/IO/FileResourceType.hpp"
#include "OpenSHC/Map/MapType2.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"
#include "OpenSHC/string-literals.hpp"
#include "OpenSHC/string-macros.hpp"

#include "OpenSHC/Globals/COL_BLACK.hpp"
#include "OpenSHC/Globals/DAT_BlendingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MapDefinedData.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition2.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition3.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_ResourceManager.hpp"
#include "OpenSHC/Globals/DAT_SoundEffectsHelperData1.hpp"
#include "OpenSHC/Globals/DAT_SoundSystemState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_VideoBikQueue.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"
#include "OpenSHC/Globals/FilePackagerObj.hpp"
#include "OpenSHC/Globals/SEC_SkirmishLobbySetupStructure.hpp"
#include "OpenSHC/Globals/UI_MissionModeIntent.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using UI::Enums::MenuViewType;

        // FUNCTION: STRONGHOLDCRUSADER 0x00494950
        void General::MenuItemActionHandler_General_LaunchOrQuitMultiplayerGameUnk(int param_1, ...)
        {
            OpenSHC::Game::GameModeInt GVar1;
            char* pcVar2;
            char* pcVar3;
            MenuViewType menuID;
            GVar1 = DAT_GameSynchronyState::instance.currentGameMode;
            if (param_1 != 22) {
                if (param_1 == 23) {
                    if (DAT_MenuTextInputState::instance.DAT_MenuOptionsActionParameter == 2000) {
                        DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = 1;
                        MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand,
                            DAT_GameSynchronyState::ptr)(Commands::GCT_START_OR_STOP_SEND_MAP_FILEUnk);
                    }
                    if (DAT_MenuTextInputState::instance.DAT_MenuOptionsActionParameter == 47) {
                        DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .playerDeathRelated = 0;
                        MACRO_CALL_MEMBER(
                            Map::MapPropertiesState_Func::activateScenarioTypeEvents, DAT_MapPropertiesState::ptr)();
                        MACRO_CALL_MEMBER(Map::MapPropertiesState_Func::createScenarioEventForNextMonth,
                            DAT_MapPropertiesState::ptr)();
                        DAT_GameCore::instance.section1095 = 2;
                    }
                    MACRO_CALL_MEMBER(UI::MenuTextInputState_Func::popModalDialog, DAT_MenuTextInputState::ptr)();
                    MACRO_CALL_MEMBER(Input::MouseState_Func::resetMouseState2, DAT_MouseState::ptr)();
                    return;
                }
                goto LAB_00495061;
            }
            if (DAT_MenuTextInputState::instance.DAT_MenuOptionsActionParameter < 44) {
                if (DAT_MenuTextInputState::instance.DAT_MenuOptionsActionParameter == 43) {
                    DAT_GameCore::instance.isTimeHalted2 = 0;
                    MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                        UI::Enums::MVT_CUSTOM_SCENARIOS, 0);
                    goto LAB_00494b4a;
                }
                switch (DAT_MenuTextInputState::instance.DAT_MenuOptionsActionParameter) {
                case 7:
                    break;
                case 9:
                    MACRO_CALL_MEMBER(
                        Synchrony::GameSynchronyState_Func::disconnectDPlay, DAT_GameSynchronyState::ptr)();
                    DAT_WindowAndDirectDraw::instance.postWindowCloseMessage = 1;
                    DAT_GameCore::instance.currentlyInGameUnk_0xa4 = FALSE;
                    MACRO_CALL_MEMBER(Input::MouseState_Func::resetMouseState2, DAT_MouseState::ptr)();
                    return;
                case 30:
                    if ((DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SOLITARY)
                        && (DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SKIRMISH_SINGLE_PLAYER)) {
                        DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = DAT_GameCore::instance.mapTimeInTicks;
                        DAT_GameSynchronyState::instance.DAT_GameCommandParam1
                            = MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::computeSomeHashOnUnitArray,
                                DAT_GameSynchronyState::ptr)();
                        DAT_GameSynchronyState::instance.DAT_GameCommandParam2 = 0;
                        MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand,
                            DAT_GameSynchronyState::ptr)(Commands::GCT_SAVE);
                        MACRO_CALL_MEMBER(
                            UI::MenuTextInputState_Func::clearAnyOtherModalDialogs, DAT_MenuTextInputState::ptr)();
                        MACRO_CALL_MEMBER(Input::MouseState_Func::resetMouseState2, DAT_MouseState::ptr)();
                        return;
                    }
                    DAT_MenuTextInputState::instance.DAT_MenuOptionsActionParameter = 32;
                    MACRO_CALL_MEMBER(UI::MenuTextInputState_Func::activateModalDialogAndClearText,
                        DAT_MenuTextInputState::ptr)(UI::Enums::MMT_PROGRESS_BAR_BOX);
                    MACRO_CALL_MEMBER(Input::MouseState_Func::resetMouseState2, DAT_MouseState::ptr)();
                    return;
                case -7:
                    for (int i = 0; i < countof(DAT_BlendingDefinedData::instance.PlayerSlotUnitColor); ++i) {
                        DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[i]
                            = DAT_BlendingDefinedData::instance.DefaultPlayerSlotUnitColor[i];
                    }
                    break;
                default:
                    goto switchD_00494a01_caseD_fffffffa;
                }
            } else {
                if (DAT_MenuTextInputState::instance.DAT_MenuOptionsActionParameter < 50) {
                    if (DAT_MenuTextInputState::instance.DAT_MenuOptionsActionParameter == 49) {
                        MACRO_CALL_MEMBER(
                            Map::MapPropertiesState_Func::spawnInvasionEventAttackWave, DAT_MapPropertiesState::ptr)();
                    } else {
                        if (DAT_MenuTextInputState::instance.DAT_MenuOptionsActionParameter == 44) {
                            // restart game
                            MACRO_CALL_MEMBER(Input::MouseState_Func::resetMouseState2, DAT_MouseState::ptr)();
                            DAT_VideoBikQueue::instance.storedMessages_0x924 = 0;
                            MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog,
                                DAT_MenuModalComposition1::ptr)(UI::Enums::MMT_NONE, FALSE);
                            MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog,
                                DAT_MenuModalComposition2::ptr)(UI::Enums::MMT_NONE, FALSE);
                            MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog,
                                DAT_MenuModalComposition3::ptr)(UI::Enums::MMT_NONE, FALSE);
                            MACRO_CALL_MEMBER(
                                Audio::MSS::SoundSystem_Func::stopAllActiveSounds, DAT_SoundSystemState::ptr)();
                            DAT_SoundEffectsHelperData1::instance.SEC_Section1079.musicState = 1;
                            MACRO_CALL_MEMBER(
                                Audio::MSS::SoundSystem_Func::setSomeSoundTime, DAT_SoundSystemState::ptr)();
                            MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::setupVolumeAndSoundID,
                                DAT_SoundSystemState::ptr)(DE::SHCDE::MUSIC_TUNE_NARR1);
                            MACRO_CALL_MEMBER(
                                UI::MenuTextInputState_Func::clearAnyOtherModalDialogs, DAT_MenuTextInputState::ptr)();
                            if (DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SKIRMISH_SINGLE_PLAYER) {
                                if (DAT_GameCore::instance.gameMode_2 != Game::GM_CAMPAIGN_MISSION) {
                                    if (DAT_GameCore::instance.isSkirmishTrail != TRUE) {
                                        MACRO_CALL_MEMBER(
                                            Game::Skirmish::SkirmishLobbySetupStructure_Func::restoreSkirmishLobbySetup,
                                            SEC_SkirmishLobbySetupStructure::ptr)();
                                        MACRO_CALL(UI::Actions_Func::LaunchSkirmishGame)(0);
                                        MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                                            UI::Enums::MVT_BUILD_MENU, 0);
                                        MACRO_CALL_MEMBER(
                                            Input::MouseState_Func::resetMouseState2, DAT_MouseState::ptr)();
                                        return;
                                    }
                                    if (DAT_GameCore::instance.currentTrailType == Game::TT_EXTREME) {
                                        if (DAT_GameCore::instance.extremeTrailProgress < 20) {
                                            MACRO_CALL(Game::Skirmish_Func::SetupSkirmishMode)(
                                                DAT_GameCore::instance.extremeTrailProgress);
                                            MACRO_CALL_MEMBER(
                                                Input::MouseState_Func::resetMouseState2, DAT_MouseState::ptr)();
                                            return;
                                        }
                                    } else if (DAT_GameCore::instance.currentTrailType == Game::TT_WARCHEST) {
                                        if (DAT_GameCore::instance.warchestTrailProgress < 30) {
                                            MACRO_CALL(Game::Skirmish_Func::SetupSkirmishMode)(
                                                DAT_GameCore::instance.warchestTrailProgress);
                                            MACRO_CALL_MEMBER(
                                                Input::MouseState_Func::resetMouseState2, DAT_MouseState::ptr)();
                                            return;
                                        }
                                    } else if (DAT_GameCore::instance.skirmishTrailProgress < 50) {
                                        MACRO_CALL(Game::Skirmish_Func::SetupSkirmishMode)(
                                            DAT_GameCore::instance.skirmishTrailProgress);
                                        MACRO_CALL_MEMBER(
                                            Input::MouseState_Func::resetMouseState2, DAT_MouseState::ptr)();
                                        return;
                                    }
                                    goto LAB_00495061;
                                }
                            } else {
                                if (DAT_GameCore::instance.gameMode_2 == Game::GM_BUILDERUnk) {
                                    DAT_GameCore::instance.currentMenuViewType
                                        = UI::Enums::MVT_UNKNOWN_49_DOES_NOTHINGUnk;
                                    MACRO_CALL(Map_Func::ResetSomeValuesFunctionUnk)();
                                    MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawColorBox,
                                        DAT_PencilRenderCore::ptr)(0, 0, DAT_WindowAndDirectDraw::instance.resolutionX,
                                        DAT_WindowAndDirectDraw::instance.resolutionY,
                                        (ushort)((int)(COL_BLACK::instance.shortValue)));
                                    MACRO_CALL(UI::Actions_Func::LaunchSinglePlayerGameUnk)(1);
                                    MACRO_CALL_MEMBER(Input::MouseState_Func::resetMouseState2, DAT_MouseState::ptr)();
                                    return;
                                }
                                if (DAT_GameCore::instance.gameMode_2 == Game::GM_CAMPAIGN_MISSION) {
                                    MACRO_CALL_MEMBER(Game::GameCore_Func::removeJesterAndLadyUnitsInCertainMissions,
                                        DAT_GameCore::ptr)();
                                }
                                if (DAT_GameCore::instance.gameMode_2 == Game::GM_ECONOMIC_CAMPAIGN_SH1) {
                                    MACRO_CALL_MEMBER(Game::GameCore_Func::removeLadyAndJester, DAT_GameCore::ptr)();
                                }
                            }
                            DAT_GameCore::instance.gameSuspended = 0;
                            MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                                UI::Enums::MVT_SCENARIO_DESCRIPTION, 0);
                            MACRO_CALL_MEMBER(Input::MouseState_Func::resetMouseState2, DAT_MouseState::ptr)();
                            return;
                        }
                        if (DAT_MenuTextInputState::instance.DAT_MenuOptionsActionParameter == 47) {
                            MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                                UI::Enums::MVT_MISSION_FINISHED_TRANSITION, 0);
                            MACRO_CALL_MEMBER(
                                UI::MenuTextInputState_Func::clearAnyOtherModalDialogs, DAT_MenuTextInputState::ptr)();
                            DAT_GameCore::instance.section1095 = 0;
                            MACRO_CALL_MEMBER(Input::MouseState_Func::resetMouseState2, DAT_MouseState::ptr)();
                            return;
                        }
                    }
                switchD_00494a01_caseD_fffffffa:
                    MACRO_CALL_MEMBER(UI::MenuTextInputState_Func::popModalDialog, DAT_MenuTextInputState::ptr)();
                    MACRO_CALL_MEMBER(Input::MouseState_Func::resetMouseState2, DAT_MouseState::ptr)();
                    return;
                }
                if (DAT_MenuTextInputState::instance.DAT_MenuOptionsActionParameter != 1000) {
                    if (DAT_MenuTextInputState::instance.DAT_MenuOptionsActionParameter == 2000) {
                        // ".map"
                        strcat(DAT_GameSynchronyState::instance.unknownMapName_01, S__MAP_005A2294);
                        MACRO_CALL_MEMBER(IO::ResourceManager_Func::resolveResourceFileName, DAT_ResourceManager::ptr)(
                            IO::FRT_MAPS, (char const*)((int)(DAT_GameSynchronyState::instance.unknownMapName_01)));
                        DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = 0;
                        MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand,
                            DAT_GameSynchronyState::ptr)(Commands::GCT_START_OR_STOP_SEND_MAP_FILEUnk);
                        MACRO_CALL_MEMBER(UI::MenuTextInputState_Func::popModalDialog, DAT_MenuTextInputState::ptr)();
                        MACRO_CALL_MEMBER(Input::MouseState_Func::resetMouseState2, DAT_MouseState::ptr)();
                        return;
                    }
                    goto switchD_00494a01_caseD_fffffffa;
                }
            }
            if (DAT_GameSynchronyState::instance.currentGameMode == Game::GM_MULTIPLAYER) {
                MACRO_CALL_MEMBER(
                    Synchrony::GameSynchronyState_Func::initMultiplayerLobbyState, DAT_GameSynchronyState::ptr)();
                return;
            }
            MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::disconnectDPlay, DAT_GameSynchronyState::ptr)();
            MACRO_CALL_MEMBER(Input::MouseState_Func::resetMouseState2, DAT_MouseState::ptr)();
            DAT_VideoBikQueue::instance.storedMessages_0x924 = 0;
            MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog, DAT_MenuModalComposition1::ptr)(
                UI::Enums::MMT_NONE, FALSE);
            MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog, DAT_MenuModalComposition2::ptr)(
                UI::Enums::MMT_NONE, FALSE);
            MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog, DAT_MenuModalComposition3::ptr)(
                UI::Enums::MMT_NONE, FALSE);
            MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::stopAllActiveSounds, DAT_SoundSystemState::ptr)();
            DAT_GameCore::instance.currentlyInGameUnk_0xa4 = FALSE;
            if (DAT_GameCore::instance.field_0x6c) {
                DAT_MenuTextInputState::instance.DAT_MenuOptionsActionParameter = 31;
                MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog, DAT_MenuModalComposition1::ptr)(
                    UI::Enums::MMT_PROGRESS_BAR_BOX, FALSE);
                MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::renderMenuModal, DAT_MenuModalComposition1::ptr)();
                DAT_WindowAndDirectDraw::instance.pendingBltMode = 1;
                MACRO_CALL_MEMBER(
                    UI::Rendering::WindowAndDirectDraw_Func::renderBltAndFlip, DAT_WindowAndDirectDraw::ptr)(0);
                MACRO_CALL_MEMBER(IO::ResourceManager_Func::resolveResourceFileName, DAT_ResourceManager::ptr)(
                    IO::FRT_MAPS, STR_AutoBackupMap);
                FilePackagerObj::instance.loadAndSaveBarFunc = MACRO_CALL(UI::Rendering_Func::RenderLoadAndSaveBar);
                MACRO_CALL_MEMBER(IO::FilePackager_Func::readMapOrSavFile, FilePackagerObj::ptr)(
                    DAT_MapDefinedData::instance.MapSectionAddressArray);
                MACRO_CALL_MEMBER(Map::TileMapState_Func::prepareMap, DAT_TileMapState::ptr)();
                MACRO_CALL_MEMBER(
                    UI::MenuTextInputState_Func::clearAnyOtherModalDialogs, DAT_MenuTextInputState::ptr)();
                MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    UI::Enums::MVT_MAP_EDITOR_PROPERTIES, 0);
                DAT_GameCore::instance.field_0x6c = 0;
                goto LAB_0049504b;
            }
            if (!UI_MissionModeIntent::instance) {
                if (DAT_MenuTextInputState::instance.DAT_MenuOptionsActionParameter != 7) {
                    menuID = UI::Enums::MVT_SINGLEPLAYER_MAP_CHOICE;
                    goto LAB_00495046;
                }
                if (GVar1 == Game::GM_SOLITARY) {
                    if (DAT_GameCore::instance.gameMode_2 != Game::GM_BUILDERUnk) {
                        menuID = UI::Enums::MVT_MAIN_MENU;
                        goto LAB_00495046;
                    }
                    if (DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 == Map::MT_INVASION) {
                        MACRO_CALL(UI::MenuItems::CustomScenarios_Func::MenuItemActionHandler_CustomScenarios_Main)(4);
                    } else {
                        MACRO_CALL(UI::MenuItems::MainMenu_Func::MenuItemActionHandler_MainMenu_Main)(3);
                    }
                } else if (GVar1 == Game::GM_SKIRMISH_SINGLE_PLAYER) {
                    if (DAT_GameCore::instance.gameMode_2 != Game::GM_CAMPAIGN_MISSION) {
                        if (!DAT_GameCore::instance.isSkirmishTrail) {
                            menuID = UI::Enums::MVT_UNKNOWN_61_RETURN_TO_SKIRMISH_MENUUnk;
                        } else {
                            DAT_GameCore::instance.gameSuspended = 0;
                            menuID = UI::Enums::MVT_CRUSADE_MAP;
                        }
                        goto LAB_00495046;
                    }
                    MACRO_CALL(
                        UI::MenuItems::HistoricCampaignSelect_Func::MenuItemActionHandler_HistoricCampaignSelect_Main)(
                        4);
                } else {
                    DAT_GameSynchronyState::instance.nextModalDialog = UI::Enums::MMT_CHOOSE_NETWORK_SERVICE_PROVIDER;
                    DAT_GameCore::instance.gameMode_2 = Game::GM_SKIRMISH_AND_MULTIPLAYER;
                    DAT_GameCore::instance.xbowProducible_logic = 1;
                    DAT_GameCore::instance.pikeProducible_logic = 1;
                    DAT_GameCore::instance.swordProducible_logic = 1;
                    DAT_GameCore::instance.bowProducible_logic = 1;
                    DAT_GameCore::instance.spearProducible_logic = 1;
                    DAT_GameCore::instance.maceProducible_logic = 1;
                    MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                        UI::Enums::MVT_MP_CONNECTION, 0);
                    for (int i = 0; i < countof(DAT_BlendingDefinedData::instance.PlayerSlotUnitColor); ++i) {
                        DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[i]
                            = DAT_BlendingDefinedData::instance.DefaultPlayerSlotUnitColor[i];
                    }
                }
            } else {
                if (DAT_GameCore::instance.gameMode_2 == Game::GM_CAMPAIGN_MISSION) {
                    menuID = UI::Enums::MVT_HISTORIC_MISSION_SELECT;
                } else {
                    menuID = UI::Enums::MVT_UNUSED_ECONOMIC_MISSION_SELECTUnk;
                }
            LAB_00495046:
                MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(menuID, 0);
            }
        LAB_0049504b:
            if (DAT_MenuTextInputState::instance.currentModalDialog != UI::Enums::MMT_NO_MENU) {
            LAB_00494b4a:
                MACRO_CALL_MEMBER(
                    UI::MenuTextInputState_Func::clearAnyOtherModalDialogs, DAT_MenuTextInputState::ptr)();
                MACRO_CALL_MEMBER(Input::MouseState_Func::resetMouseState2, DAT_MouseState::ptr)();
                return;
            }
            MACRO_CALL_MEMBER(UI::MenuTextInputState_Func::meth_0x4917c0, DAT_MenuTextInputState::ptr)();
        LAB_00495061:
            MACRO_CALL_MEMBER(Input::MouseState_Func::resetMouseState2, DAT_MouseState::ptr)();
        }

    }
}
}
