#include "../GameCore.func.hpp"

#include "OpenSHC/Audio/MSS/SoundSystem.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Rendering/Bink/BinkControlClass.func.hpp"
#include "OpenSHC/UI/Credits.func.hpp"
#include "OpenSHC/UI/DisplayElements.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/MenuHandlerState.func.hpp"

#include "OpenSHC/Globals/DAT_00b95954.hpp"
#include "OpenSHC/Globals/DAT_BinkControlState.hpp"
#include "OpenSHC/Globals/DAT_CurrentMenuID_3.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_SoundSystemState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Game {

    // FUNCTION: STRONGHOLDCRUSADER 0x0046B340
    void GameCore::switchToMenuView(MenuViewType menuID, int delay)
    {
        if (menuID == 23) {
            menuID = UI::Enums::MVT_MAIN_MENU;
        }
        this->menuViewToSwitchTo = menuID;
        this->menuSwitchDelay = delay;
        this->menuRenderMoment = timeGetTime();

        switch (menuID) {
        case UI::Enums::MVT_MAP_EDITOR_LANDSCAPING:
            this->menuTabToSwitchTo.tabType = this->landscapingmenuMenuTabToSwitchTo;
            DAT_TileMapState::instance.unknownBrushRelated = (int)DAT_TileMapState::instance.editorActiveBrush >> 1;
            if (this->landscapingmenuMenuTabToSwitchTo != UI::Enums::BMTT_MENU_HIDDEN
                && this->activeMenuTab.buildMenuTab != UI::Enums::BMTT_MENU_HIDDEN) {
                DAT_TileMapState::instance.currentMapperCommand = Commands::M_MAPPER_NULL;
            }
            break;
        case UI::Enums::MVT_BUILD_MENU:
            this->menuTabToSwitchTo = this->buildmenuMenuTabToSwitchTo;
            MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::setSection1079_28_4_, DAT_SoundSystemState::ptr)(0);
            if (this->menuTabToSwitchTo.buildMenuTab == 48) {
                break;
            }
            if (DAT_GameCore::instance.gameMode_2 == GM_CRUSADER_TUTORIAL) {
                MACRO_CALL(UI::Helpers_Func::SetTutorialBuildingActionState)(11, Map::Buildings::BT_HOVEL);
            }
            if (MACRO_CALL(UI::DisplayElements_Func::GetIfDisplayElementStateNotZero)(
                    UI::Enums::DEID_MISSION_WIN_DEFEAT_BANNER)) {
                this->buildmenuMenuTabToSwitchTo.buildMenuTab = 48;
                this->menuTabToSwitchTo.buildMenuTab = 48;
            } else if (((DAT_GameCore::instance.gameMode_2 == GM_BUILDERUnk
                            || DAT_GameCore::instance.gameMode_2 == GM_CRUSADER_TUTORIAL)
                           && DAT_GameSynchronyState::instance.currentPlayerSlotID == 2)
                || (DAT_GameSynchronyState::instance.currentPlayerSlotID == 1
                    && MACRO_CALL_MEMBER(
                           GameStateStructures_Func::singlePlayerHasKeepAndGranaryCheck, DAT_GameState::ptr)()
                        == 0
                    && MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::getArmySize, DAT_UnitsState::ptr)(
                           DAT_GameSynchronyState::instance.currentPlayerSlotID)
                        != 0)
                || (DAT_GameCore::instance.gameMode_2 == GM_BUILDERUnk
                    && DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 == Map::MT_SIEGE)
                || (DAT_GameCore::instance.gameMode_2 == GM_SKIRMISH_AND_MULTIPLAYER
                    && DAT_GameSynchronyState::instance.currentGameMode == GM_SKIRMISH_SINGLE_PLAYER
                    && DAT_GameSynchronyState::instance.currentPlayerSlotID == 0)) {
                // all this is custom code for some single player modes
                if (this->buildmenuMenuTabToSwitchTo.buildMenuTab != UI::Enums::BMTT_MENU_HIDDEN
                    && this->buildmenuMenuTabToSwitchTo.buildMenuTab != UI::Enums::BMTT_SOLDIERS
                    && this->buildmenuMenuTabToSwitchTo.buildMenuTab != 62) {
                    this->buildmenuMenuTabToSwitchTo.buildMenuTab = 48;
                    this->menuTabToSwitchTo.buildMenuTab = 48;
                    MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::setSection1079_28_4_, DAT_SoundSystemState::ptr)(1);
                }
            } else if (this->currentMenuViewType == UI::Enums::MVT_BUILD_MENU
                && this->buildmenuMenuTabToSwitchTo.buildMenuTab >= 10
                && this->buildmenuMenuTabToSwitchTo.buildMenuTab <= 49 && this->activeMenuTab.buildMenuTab >= 10
                && this->activeMenuTab.buildMenuTab <= 49) {
                this->menuSwitchDelay = 150;
                MACRO_CALL_MEMBER(UI::MenuHandlerState_Func::startBuildMenuTransition, DAT_MenuHandlerState::ptr)(300);
                if (this->buildmenuMenuTabToSwitchTo.buildMenuTab != 49
                    && this->buildmenuMenuTabToSwitchTo.buildMenuTab != UI::Enums::BMTT_CASTLE_KEEPS) {
                    if (MACRO_CALL_MEMBER(
                            GameStateStructures_Func::singlePlayerHasKeepAndGranaryCheck, DAT_GameState::ptr)()
                        == 0) {
                        if (this->buildmenuMenuTabToSwitchTo.buildMenuTab != UI::Enums::BMTT_CASTLE_KEEPS) {
                            this->buildmenuMenuTabToSwitchTo.buildMenuTab = UI::Enums::BMTT_CASTLE_KEEPS;
                            this->menuTabToSwitchTo.buildMenuTab = UI::Enums::BMTT_CASTLE_KEEPS;
                        } else {
                            this->menuSwitchDelay = 0;
                            DAT_MenuHandlerState::instance.isBuildMenuTransitioning_0x18 = FALSE;
                        }
                    } else if (MACRO_CALL_MEMBER(
                                   GameStateStructures_Func::singlePlayerHasKeepAndGranaryCheck, DAT_GameState::ptr)()
                        < 0) {
                        if (this->buildmenuMenuTabToSwitchTo.buildMenuTab != 49) {
                            this->buildmenuMenuTabToSwitchTo.buildMenuTab = 49;
                            this->menuTabToSwitchTo.buildMenuTab = 49;
                        } else {
                            this->menuSwitchDelay = 0;
                            DAT_MenuHandlerState::instance.isBuildMenuTransitioning_0x18 = FALSE;
                        }
                    }
                }
            } else if (this->currentMenuViewType != UI::Enums::MVT_BUILD_MENU
                || (this->buildmenuMenuTabToSwitchTo.buildMenuTab >= 10
                    && this->buildmenuMenuTabToSwitchTo.buildMenuTab <= 49)) {
                if (this->buildmenuMenuTabToSwitchTo.buildMenuTab != 49
                    && this->buildmenuMenuTabToSwitchTo.buildMenuTab != UI::Enums::BMTT_CASTLE_KEEPS) {
                    if (MACRO_CALL_MEMBER(
                            GameStateStructures_Func::singlePlayerHasKeepAndGranaryCheck, DAT_GameState::ptr)()
                        == 0) {
                        if (this->buildmenuMenuTabToSwitchTo.buildMenuTab != UI::Enums::BMTT_CASTLE_KEEPS) {
                            this->buildmenuMenuTabToSwitchTo.buildMenuTab = UI::Enums::BMTT_CASTLE_KEEPS;
                            this->menuTabToSwitchTo.buildMenuTab = UI::Enums::BMTT_CASTLE_KEEPS;
                        }
                    } else if (MACRO_CALL_MEMBER(
                                   GameStateStructures_Func::singlePlayerHasKeepAndGranaryCheck, DAT_GameState::ptr)()
                        < 0) {
                        if (this->buildmenuMenuTabToSwitchTo.buildMenuTab != 49) {
                            this->buildmenuMenuTabToSwitchTo.buildMenuTab = 49;
                            this->menuTabToSwitchTo.buildMenuTab = 49;
                        }
                    }
                }
            }
            break;
        case UI::Enums::MVT_BUILDING_AND_STATUS_MENU:
            this->menuTabToSwitchTo.tabType = this->buildingandstatusmenuMenuTabToSwitchTo;
            break;
        default:
            MACRO_CALL_MEMBER(Rendering::Bink::BinkControlClass_Func::stopBinkPlayback, DAT_BinkControlState::ptr)(0);
            MACRO_CALL_MEMBER(Rendering::Bink::BinkControlClass_Func::stopBinkPlayback, DAT_BinkControlState::ptr)(1);
            break;
        }

        if (menuID == this->currentMenuViewType) {
            return;
        }

        // handle sound
        switch (menuID) {
        case UI::Enums::MVT_MAP_EDITOR_LANDSCAPING:
        case UI::Enums::MVT_MAP_EDITOR_PROPERTIES:
            MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::setupVolumeAndSoundID0xF0_100, DAT_SoundSystemState::ptr)();
            return;
        case UI::Enums::MVT_BUILD_MENU:
            if (this->currentMenuViewType == UI::Enums::MVT_BUILDING_AND_STATUS_MENU
                || this->currentMenuViewType == UI::Enums::MVT_MAP_EDITOR_LANDSCAPING
                || (this->currentMenuViewType == UI::Enums::MVT_SCENARIO_DESCRIPTION
                    && DAT_GameCore::instance.field22_0x64 != 0)) {
                return;
            }
            if (this->gameMode_2 == GM_CRUSADER_TUTORIAL) {
                if (DAT_SoundSystemState::instance.currentSoundID_0x3278 == 9) {
                    return;
                }
                MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::setSomeSoundTime, DAT_SoundSystemState::ptr)();
                MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::setupVolumeAndSoundIDWithMultiplier,
                    DAT_SoundSystemState::ptr)(DE::SHCDE::MUSIC_TUNE_TUTORIAL, 70);
                return;
            }
            MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::setSomeSoundTime, DAT_SoundSystemState::ptr)();
            DAT_SoundSystemState::instance.mbr_0x3288 = timeGetTime() >> 1;
            DAT_SoundSystemState::instance.currentSoundID_0x3278 = -1;
            return;
        case UI::Enums::MVT_CRUSADE_MAP:
            if (this->currentMenuViewType == UI::Enums::MVT_SELECT_CRUSADE
                || this->currentMenuViewType == UI::Enums::MVT_CRUSADE_MISSION_INTRO
                || this->currentMenuViewType == UI::Enums::MVT_RANKING_GAMES) {
                return;
            }
            MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::setSomeSoundTime, DAT_SoundSystemState::ptr)();
            MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::setupVolumeAndSoundIDWithMultiplier,
                DAT_SoundSystemState::ptr)(DE::SHCDE::MUSIC_TUNE_INTRO, 100);
            return;
        case UI::Enums::MVT_RANKING_GAMES:
            if (this->currentMenuViewType == UI::Enums::MVT_LOBBY_MENU) {
                MACRO_CALL(UI::Credits_Func::SetActiveCreditsSequenceIndex)(2);
                DAT_CurrentMenuID_3::instance = this->currentMenuViewType;
            }
            if (this->currentMenuViewType == UI::Enums::MVT_CRUSADE_MAP) {
                MACRO_CALL(UI::Credits_Func::SetActiveCreditsSequenceIndex)(1);
                DAT_CurrentMenuID_3::instance = this->currentMenuViewType;
            }
            return;
        case UI::Enums::MVT_HISTORIC_MISSION_PICTURE:
            if (this->currentMenuViewType == UI::Enums::MVT_HISTORIC_CAMPAIGN_INTRO) {
                return;
            }
            if (this->currentMenuViewType == UI::Enums::MVT_MISSION_FINISHED_TRANSITION) {
                MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::stopMusicPlayback, DAT_SoundSystemState::ptr)();
                MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::setupVolumeAndSoundID, DAT_SoundSystemState::ptr)(
                    DE::SHCDE::MUSIC_TUNE_NARR1);
                return;
            }
            if (DAT_GameCore::instance.missionNumber1to20 == 1000) {
                if (DAT_SoundSystemState::instance.sec_Section1055_0x3274 != 7) {
                    MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::setSomeSoundTime, DAT_SoundSystemState::ptr)();
                }
                MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::setupVolumeAndSoundIDWithMultiplier,
                    DAT_SoundSystemState::ptr)(DE::SHCDE::MUSIC_TUNE_CHOIR, 100);
                return;
            }
            if (DAT_SoundSystemState::instance.currentSoundID_0x3278 == 4 || DAT_GameCore::instance.field22_0x64 != 0
                || DAT_GameCore::instance.currentlyInGameUnk_0xa4 == TRUE) {
                return;
            }
            MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::setSomeSoundTime, DAT_SoundSystemState::ptr)();
            MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::setupVolumeAndSoundID, DAT_SoundSystemState::ptr)(
                DE::SHCDE::MUSIC_TUNE_NARR1);
            return;
        case UI::Enums::MVT_HISTORIC_CAMPAIGN_INTRO:
            MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::setSomeSoundTime, DAT_SoundSystemState::ptr)();
            MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::setupVolumeAndSoundID, DAT_SoundSystemState::ptr)(
                (DE::SHCDE::eMusicIDs)(DAT_GameCore::instance.historicCampaignNumber * 5 + DE::SHCDE::MUSIC_TUNE_WIN1));
            return;
        case UI::Enums::MVT_HISTORIC_CAMPAIGN_OUTRO:
            MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::setSomeSoundTime, DAT_SoundSystemState::ptr)();
            MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::setupVolumeAndSoundID, DAT_SoundSystemState::ptr)(
                (DE::SHCDE::eMusicIDs)(DAT_GameCore::instance.historicCampaignNumber + 0x42));
            return;
        case UI::Enums::MVT_CREDITS:
            MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::setSomeSoundTime, DAT_SoundSystemState::ptr)();
            if (DAT_00b95954::instance == 0) {
                MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::setupVolumeAndSoundIDWithMultiplier,
                    DAT_SoundSystemState::ptr)((DE::SHCDE::eMusicIDs)15, 100);
            }
            if (DAT_00b95954::instance == 1) {
                MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::setupVolumeAndSoundIDWithMultiplier,
                    DAT_SoundSystemState::ptr)((DE::SHCDE::eMusicIDs)38, 100);
                MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::markMusicChangePending, DAT_SoundSystemState::ptr)();
            }
            return;
        case UI::Enums::MVT_MISSION_FINISHED_TRANSITION:
        case UI::Enums::MVT_GAME_LOSTUnk:
            if (this->currentMenuViewType == UI::Enums::MVT_RANKING_GAMES) {
                return;
            }
            MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::setSomeSoundTime, DAT_SoundSystemState::ptr)();
            MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::setupVolumeAndSoundID, DAT_SoundSystemState::ptr)(
                DE::SHCDE::MUSIC_TUNE_OFF);
            return;
        case UI::Enums::MVT_MP_CONNECTION:
        case UI::Enums::MVT_LOBBY_MENU:
        case UI::Enums::MVT_GAME_START_ENTER_NAME:
        case UI::Enums::MVT_MAIN_MENU:
        case UI::Enums::MVT_HISTORIC_CAMPAIGN_SELECT:
        case UI::Enums::MVT_UNUSED_ECONOMIC_GAMETYPE_SELECT:
        case UI::Enums::MVT_CUSTOM_SCENARIOS:
        case UI::Enums::MVT_UNUSED_SELECT_RANDOM_NUMBER_OF_ENEMIES:
            if (DAT_SoundSystemState::instance.currentSoundID_0x3278 == 3
                && DAT_SoundSystemState::instance.mbr_0x154 == 0) {
                return;
            }
            MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::setSomeSoundTime, DAT_SoundSystemState::ptr)();
            MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::setupVolumeAndSoundIDWithMultiplier,
                DAT_SoundSystemState::ptr)(DE::SHCDE::MUSIC_TUNE_INTRO, 100);
            return;
        case UI::Enums::MVT_UNUSED_EXTREME_AD:
            MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::endSoundStreamsUnk, DAT_SoundSystemState::ptr)();
            MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::setSomeSoundTime, DAT_SoundSystemState::ptr)();
            MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::setupVolumeAndSoundIDWithMultiplier,
                DAT_SoundSystemState::ptr)(DE::SHCDE::MUSIC_TUNE_TUTORIAL, 50);
            return;
        case UI::Enums::MVT_CRUSADE_ENDSCREEN:
            MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::setSomeSoundTime, DAT_SoundSystemState::ptr)();
            MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::setupVolumeAndSoundIDWithMultiplier,
                DAT_SoundSystemState::ptr)(DE::SHCDE::MUSIC_TUNE_HAPPY2, 50);
            return;
        case UI::Enums::MVT_BUILDING_AND_STATUS_MENU:
        case UI::Enums::MVT_UNKNOWN_21:
        case UI::Enums::MVT_UNUSED_HELP_TEXT_EDITOR:
        case 23:
        case 24:
        case UI::Enums::MVT_UNKNOWN_26_CAMPAIGN_RELATEDUnk:
        case UI::Enums::MVT_UNKNOWN_27_CAMPAIGNUnk:
        case UI::Enums::MVT_SCENARIO_DESCRIPTION:
        case UI::Enums::MVT_NEW_MAP_MAPSIZE:
        case UI::Enums::MVT_UNUSED_CHOOSE_AVAILABLE_KEEPS:
        case UI::Enums::MVT_UNKNOWN_33:
        case UI::Enums::MVT_SINGLEPLAYER_MAP_CHOICE:
        case 36:
        case UI::Enums::MVT_UNUSED_CHOOSE_GAME_TYPE:
        case UI::Enums::MVT_HISTORIC_MISSION_SELECT:
        case UI::Enums::MVT_UNUSED_ECONOMIC_MISSION_SELECTUnk:
        case UI::Enums::MVT_INTRO_VIDEO:
        case UI::Enums::MVT_HISTORIC_MISSION_INTRO:
        case UI::Enums::MVT_SELECT_CRUSADE:
        case UI::Enums::MVT_CRUSADE_MISSION_INTRO:
        case UI::Enums::MVT_EDIT_SCENARIO:
            return;
        default:
            MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::setSomeSoundTime, DAT_SoundSystemState::ptr)();
            MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::setupVolumeAndSoundIDWithMultiplier,
                DAT_SoundSystemState::ptr)(DE::SHCDE::MUSIC_TUNE_INTRO, 100);
            return;
        }
    }

}
}
