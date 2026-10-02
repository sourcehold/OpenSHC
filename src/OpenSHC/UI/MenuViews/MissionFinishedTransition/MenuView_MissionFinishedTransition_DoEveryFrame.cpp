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
#include "OpenSHC/Globals/INT_00ed279c.hpp"
#include "OpenSHC/Globals/SEC_SkirmishLobbySetupStructure.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuViews {

        using OpenSHC::Audio::MSS::enums::SHC_SoundStream;
        using OpenSHC::Commands::GameCommandType;
        using OpenSHC::Game::GameMode;
        using OpenSHC::Game::GameMode2;
        using OpenSHC::Game::TrailType;
        using OpenSHC::Map::MapType2;
        using OpenSHC::UI::Enums::MenuViewType;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          WARNING: Enum "UnsortedBinkFlagInt": Some values do not have unique names
         */
        /*
          WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
         */
        /*
          WARNING: Enum "DPERRInt": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004DC500
        void MissionFinishedTransition::MenuView_MissionFinishedTransition_DoEveryFrame()
        {
            short sVar1;
            DWORD DVar2;
            int iVar3;
            dword dVar4;
            MenuViewType menuID;
            if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SKIRMISH_AND_MULTIPLAYER) {
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
            } else if (DAT_BinkControlState::instance.binkObjPtrArray[0] == (HBINK)0x0) {
                DAT_MouseState::instance.draggingStopped = TRUE;
            }
            if (((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_CAMPAIGN_MISSION)
                    && (DAT_GameSynchronyState::instance.currentGameMode
                        != OpenSHC::Game::GM_SKIRMISH_END_OF_GAME_SINGLE_PLAYER))
                && (DAT_BinkControlState::instance.unknown02_zero[0] != 0)) {
                if (DWORD_00ed27b4::instance == 0) {
                    DWORD_00ed27b4::instance = timeGetTime();
                    goto LAB_004dc5a5;
                }
                DVar2 = timeGetTime();
                if (DVar2 - DWORD_00ed27b4::instance < 0x1389)
                    goto LAB_004dc5a5;
            } else {
            LAB_004dc5a5:
                if (((DAT_MouseState::instance.draggingStopped == FALSE)
                        || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SKIRMISH_AND_MULTIPLAYER))
                    && (INT_00ed279c::instance == 0)) {
                    return;
                }
            }
            DAT_SoundSystemState::instance.streamFlagsUnkAndLoopCount_0x34[4] = 0;
            DAT_SoundSystemState::instance.streamFlagsUnkAndLoopCount_0x34[3] = 0;
            MACRO_CALL_MEMBER(OpenSHC::Audio::MSS::SoundSystem_Func::endSoundStream, DAT_SoundSystemState::ptr)(
                OpenSHC::Audio::MSS::enums::SND_STR_SPEECH_1);
            MACRO_CALL_MEMBER(OpenSHC::Audio::MSS::SoundSystem_Func::endSoundStream, DAT_SoundSystemState::ptr)(
                OpenSHC::Audio::MSS::enums::SND_STR_SPEECH_2);
            MACRO_CALL_MEMBER(
                OpenSHC::Rendering::Bink::BinkControlClass_Func::stopAllBinkPlayback, DAT_BinkControlState::ptr)();
            if (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_SKIRMISH_AND_MULTIPLAYER) {
                if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_CAMPAIGN_MISSION) {
                    DAT_GameCore::instance.field22_0x64 = 0;
                    if (DAT_GameCore::instance.missionNumber1to20
                        <= (int)(DAT_GameCore::instance.historicCampaignNumber * 5)) {
                        MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                            OpenSHC::UI::Enums::MVT_HISTORIC_MISSION_PICTURE, 0);
                        DAT_GameCore::instance.skipStoreSKMasters = 0;
                        return;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                        OpenSHC::UI::Enums::MVT_HISTORIC_CAMPAIGN_OUTRO, 0);
                    DAT_GameCore::instance.skipStoreSKMasters = 0;
                    return;
                }
                if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_ECONOMIC_CAMPAIGN_SH1) {
                    DAT_GameCore::instance.field22_0x64 = 0;
                    if (DAT_GameCore::instance.missionNumber1to20 < 0x26) {
                        MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                            OpenSHC::UI::Enums::MVT_SCENARIO_DESCRIPTION, 0);
                        DAT_GameCore::instance.skipStoreSKMasters = 0;
                        return;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                        OpenSHC::UI::Enums::MVT_MAIN_MENU, 0);
                    DAT_GameCore::instance.skipStoreSKMasters = 0;
                    return;
                }
                if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_BUILDERUnk) {
                    if (DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 == OpenSHC::Map::MT_ECONOMIC) {
                        MACRO_CALL(OpenSHC::UI::MenuItems::MainMenu_Func::MenuItemActionHandler_MainMenu_Main)(3);
                        DAT_GameCore::instance.skipStoreSKMasters = 0;
                        return;
                    }
                    MACRO_CALL(
                        OpenSHC::UI::MenuItems::CustomScenarios_Func::MenuItemActionHandler_CustomScenarios_Main)(4);
                    DAT_GameCore::instance.skipStoreSKMasters = 0;
                    return;
                }
                menuID = OpenSHC::UI::Enums::MVT_MAIN_MENU;
                goto LAB_004dc9bd;
            }
            if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER) {
                if (DAT_GameSynchronyState::instance.currentGameMode
                    != OpenSHC::Game::GM_SKIRMISH_END_OF_GAME_SINGLE_PLAYER) {
                    DAT_MenuTextInputState::instance.DAT_MenuOptionsActionParameter = 7;
                    MACRO_CALL(OpenSHC::UI::MenuItems::General_Func::
                            MenuItemActionHandler_General_LaunchOrQuitMultiplayerGameUnk)(0x16);
                    if (DAT_GameSynchronyState::instance.isHost == FALSE) {
                        DAT_GameCore::instance.skipStoreSKMasters = 0;
                        return;
                    }
                    MACRO_CALL_MEMBER(
                        OpenSHC::Game::Skirmish::SkirmishLobbySetupStructure_Func::restoreSkirmishLobbySetup,
                        SEC_SkirmishLobbySetupStructure::ptr)();
                    MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                        DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_HOST_SHARE_LOBBY_STATE);
                    DAT_GameCore::instance.skipStoreSKMasters = 0;
                    return;
                }
                DAT_GameSynchronyState::instance.currentGameMode = OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER;
                menuID = OpenSHC::UI::Enums::MVT_RANKING_GAMES;
                goto LAB_004dc9bd;
            }
            if (DAT_GameCore::instance.isSkirmishTrail == FALSE) {
                if (DAT_GameCore::instance.skipStoreSKMasters == 0) {
                    MACRO_CALL(OpenSHC::Game::Skirmish_Func::StoreGameIntoSKMasters)(0);
                }
                MACRO_CALL(OpenSHC::UI::MenuItems::SelectCrusade_Func::MenuItemActionHandler_SelectCrusade_Main)(2);
                MACRO_CALL_MEMBER(OpenSHC::Game::Skirmish::SkirmishLobbySetupStructure_Func::restoreSkirmishLobbySetup,
                    SEC_SkirmishLobbySetupStructure::ptr)();
            }
            if (DAT_GameCore::instance.isSkirmishTrail != TRUE) {
                DAT_GameCore::instance.skipStoreSKMasters = 0;
                return;
            }
            if (DAT_GameCore::instance.skipStoreSKMasters == 0) {
                if (DAT_GameCore::instance.currentTrailType == OpenSHC::Game::TT_EXTREME) {
                    iVar3 = DAT_GameCore::instance.extremeTrailProgress + 0x51;
                } else if (DAT_GameCore::instance.currentTrailType == OpenSHC::Game::TT_WARCHEST) {
                    iVar3 = DAT_GameCore::instance.warchestTrailProgress + 0x33;
                } else {
                    iVar3 = DAT_GameCore::instance.skirmishTrailProgress + 1;
                }
                MACRO_CALL(OpenSHC::Game::Skirmish_Func::StoreGameIntoSKMasters)(iVar3);
            }
            dVar4 = DAT_GameCore::instance.extremeTrailProgress;
            if ((DAT_GameCore::instance.currentTrailType != OpenSHC::Game::TT_EXTREME)
                && (dVar4 = DAT_GameCore::instance.skirmishTrailProgress,
                    DAT_GameCore::instance.currentTrailType == OpenSHC::Game::TT_WARCHEST)) {
                dVar4 = DAT_GameCore::instance.warchestTrailProgress;
            }
            if (DAT_GameState::instance.mapAndTime.playerIsAlive[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                == 0) {
            LAB_004dc763:
                if (DAT_GameCore::instance.currentTrailType == OpenSHC::Game::TT_EXTREME) {
                LAB_004dc768:
                    sVar1 = DAT_GameState::instance.mapAndTime
                                .playerIsAlive[DAT_GameSynchronyState::instance.currentPlayerSlotID];
                    if (sVar1 == 0) {
                    LAB_004dc7be:
                        MACRO_CALL(
                            OpenSHC::UI::MenuItems::SelectCrusade_Func::MenuItemActionHandler_SelectCrusade_Main)(4);
                        DAT_GameCore::instance.skipStoreSKMasters = 0;
                        return;
                    }
                    if (DAT_GameCore::instance.extremeTrailProgress
                        < DAT_GameCore::instance.furthestExtremeTrailMission) {
                        if (sVar1 == 0)
                            goto LAB_004dc7be;
                    } else {
                        DAT_GameCore::instance.furthestExtremeTrailMission
                            = DAT_GameCore::instance.extremeTrailProgress + 1;
                    }
                    if (DAT_GameCore::instance.extremeTrailProgress < 0x13) {
                        DAT_GameCore::instance.extremeTrailProgress = DAT_GameCore::instance.extremeTrailProgress + 1;
                    }
                    if (((sVar1 == 0) || (DAT_GameCore::instance.extremeTrailProgress != 0x13)) || (dVar4 != 0x13))
                        goto LAB_004dc7be;
                } else {
                    if (DAT_GameCore::instance.currentTrailType == OpenSHC::Game::TT_WARCHEST)
                        goto LAB_004dc7d9;
                    sVar1 = DAT_GameState::instance.mapAndTime
                                .playerIsAlive[DAT_GameSynchronyState::instance.currentPlayerSlotID];
                    if (sVar1 == 0) {
                    LAB_004dc88c:
                        MACRO_CALL(
                            OpenSHC::UI::MenuItems::SelectCrusade_Func::MenuItemActionHandler_SelectCrusade_Main)(1);
                        DAT_GameCore::instance.skipStoreSKMasters = 0;
                        return;
                    }
                    if ((int)DAT_GameCore::instance.skirmishTrailProgress
                        < DAT_GameCore::instance.furthestSkirmishTrailMission) {
                        if (sVar1 == 0)
                            goto LAB_004dc88c;
                    } else {
                        DAT_GameCore::instance.furthestSkirmishTrailMission
                            = DAT_GameCore::instance.skirmishTrailProgress + 1;
                    }
                    if ((int)DAT_GameCore::instance.skirmishTrailProgress < 0x31) {
                        DAT_GameCore::instance.skirmishTrailProgress = DAT_GameCore::instance.skirmishTrailProgress + 1;
                    }
                    if (((sVar1 == 0) || (DAT_GameCore::instance.skirmishTrailProgress != 0x31)) || (dVar4 != 0x31))
                        goto LAB_004dc88c;
                }
            } else {
                iVar3 = DAT_GameState::instance.mapAndTime.month + DAT_GameState::instance.mapAndTime.year * 0xc;
                if (DAT_GameCore::instance.currentTrailType == OpenSHC::Game::TT_EXTREME) {
                    if (((int)(iVar3 - DAT_GameCore::instance.extremeTrailStartDateMonths) < DAT_GameCore::instance
                                .extremeTrailMonthsTakenOrChicken[DAT_GameCore::instance.extremeTrailProgress])
                        || (DAT_GameCore::instance
                                .extremeTrailMonthsTakenOrChicken[DAT_GameCore::instance.extremeTrailProgress]
                            < 0)) {
                        DAT_GameCore::instance
                            .extremeTrailMonthsTakenOrChicken[DAT_GameCore::instance.extremeTrailProgress]
                            = iVar3 - DAT_GameCore::instance.extremeTrailStartDateMonths;
                        iVar3 = 3;
                        goto LAB_004dc741;
                    }
                    goto LAB_004dc768;
                }
                if (DAT_GameCore::instance.currentTrailType != OpenSHC::Game::TT_WARCHEST) {
                    if ((DAT_GameCore::instance
                                .skirmishTrailMonthsTakenOrChicken[DAT_GameCore::instance.skirmishTrailProgress]
                            <= (int)(iVar3 - DAT_GameCore::instance.skirmishTrailStartDateMonths))
                        && (-1 < DAT_GameCore::instance
                                .skirmishTrailMonthsTakenOrChicken[DAT_GameCore::instance.skirmishTrailProgress]))
                        goto LAB_004dc763;
                    DAT_GameCore::instance
                        .skirmishTrailMonthsTakenOrChicken[DAT_GameCore::instance.skirmishTrailProgress]
                        = iVar3 - DAT_GameCore::instance.skirmishTrailStartDateMonths;
                    iVar3 = 1;
                LAB_004dc741:
                    MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::setStartDateUnk, DAT_GameCore::ptr)(iVar3);
                    goto LAB_004dc763;
                }
                if (((int)(iVar3 - DAT_GameCore::instance.warchestTrailStartDateMonths) < DAT_GameCore::instance
                            .warchestTrailMonthsTakenOrChicken[DAT_GameCore::instance.warchestTrailProgress])
                    || (DAT_GameCore::instance
                            .warchestTrailMonthsTakenOrChicken[DAT_GameCore::instance.warchestTrailProgress]
                        < 0)) {
                    DAT_GameCore::instance
                        .warchestTrailMonthsTakenOrChicken[DAT_GameCore::instance.warchestTrailProgress]
                        = iVar3 - DAT_GameCore::instance.warchestTrailStartDateMonths;
                    iVar3 = 2;
                    goto LAB_004dc741;
                }
            LAB_004dc7d9:
                sVar1 = DAT_GameState::instance.mapAndTime
                            .playerIsAlive[DAT_GameSynchronyState::instance.currentPlayerSlotID];
                if (sVar1 == 0) {
                LAB_004dc826:
                    MACRO_CALL(OpenSHC::UI::MenuItems::SelectCrusade_Func::MenuItemActionHandler_SelectCrusade_Main)(3);
                    DAT_GameCore::instance.skipStoreSKMasters = 0;
                    return;
                }
                if ((int)DAT_GameCore::instance.warchestTrailProgress
                    < DAT_GameCore::instance.furthestWarchestTrailMission) {
                    if (sVar1 == 0)
                        goto LAB_004dc826;
                } else {
                    DAT_GameCore::instance.furthestWarchestTrailMission
                        = DAT_GameCore::instance.warchestTrailProgress + 1;
                }
                if ((int)DAT_GameCore::instance.warchestTrailProgress < 0x1d) {
                    DAT_GameCore::instance.warchestTrailProgress = DAT_GameCore::instance.warchestTrailProgress + 1;
                }
                if (((sVar1 == 0) || (DAT_GameCore::instance.warchestTrailProgress != 0x1d)) || (dVar4 != 0x1d))
                    goto LAB_004dc826;
            }
            menuID = OpenSHC::UI::Enums::MVT_CRUSADE_ENDSCREEN;
        LAB_004dc9bd:
            MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(menuID, 0);
            DAT_GameCore::instance.skipStoreSKMasters = 0;
            return;
        }

    }
}
}
