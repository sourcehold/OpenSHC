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

#include "OpenSHC/Globals/DAT_BinkControlState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_SoundSystemState.hpp"
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
        // FUNCTION: STRONGHOLDCRUSADER 0x004DC9E0
        void GameLost::MenuView_GameLost_DoEveryFrame()
        {
            DWORD DVar1;
            if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SKIRMISH_AND_MULTIPLAYER) {
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
                } else {
                    DVar1 = timeGetTime();
                    if (5000 < DVar1 - DWORD_00ed27b4::instance)
                        goto LAB_004dca69;
                }
            }
            if (((DAT_MouseState::instance.draggingStopped == FALSE)
                    || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SKIRMISH_AND_MULTIPLAYER))
                && (INT_00ed279c::instance == 0)) {}
        LAB_004dca69:
            DAT_SoundSystemState::instance.streamFlagsUnkAndLoopCount_0x34[4] = 0;
            DAT_SoundSystemState::instance.streamFlagsUnkAndLoopCount_0x34[3] = 0;
            MACRO_CALL_MEMBER(OpenSHC::Audio::MSS::SoundSystem_Func::endSoundStream, DAT_SoundSystemState::ptr)(
                OpenSHC::Audio::MSS::enums::SND_STR_SPEECH_1);
            MACRO_CALL_MEMBER(OpenSHC::Audio::MSS::SoundSystem_Func::endSoundStream, DAT_SoundSystemState::ptr)(
                OpenSHC::Audio::MSS::enums::SND_STR_SPEECH_2);
            MACRO_CALL_MEMBER(
                OpenSHC::Rendering::Bink::BinkControlClass_Func::stopAllBinkPlayback, DAT_BinkControlState::ptr)();
            if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SKIRMISH_AND_MULTIPLAYER) {
                if (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER) {
                    if (DAT_GameCore::instance.isSkirmishTrail == FALSE) {
                        if (DAT_GameCore::instance.skipStoreSKMasters == 0) {
                            MACRO_CALL(OpenSHC::Game::Skirmish_Func::StoreGameIntoSKMasters)(0);
                        }
                        MACRO_CALL(
                            OpenSHC::UI::MenuItems::SelectCrusade_Func::MenuItemActionHandler_SelectCrusade_Main)(2);
                        MACRO_CALL_MEMBER(
                            OpenSHC::Game::Skirmish::SkirmishLobbySetupStructure_Func::restoreSkirmishLobbySetup,
                            SEC_SkirmishLobbySetupStructure::ptr)();
                    }
                    if (DAT_GameCore::instance.isSkirmishTrail == TRUE) {
                        if (DAT_GameCore::instance.currentTrailType == OpenSHC::Game::TT_EXTREME) {
                            if (DAT_GameCore::instance.skipStoreSKMasters == 0) {
                                MACRO_CALL(OpenSHC::Game::Skirmish_Func::StoreGameIntoSKMasters)(
                                    DAT_GameCore::instance.extremeTrailProgress + 0x51);
                            }
                            MACRO_CALL(
                                OpenSHC::UI::MenuItems::SelectCrusade_Func::MenuItemActionHandler_SelectCrusade_Main)(
                                4);
                            DAT_GameCore::instance.skipStoreSKMasters = 0;
                        }
                        if (DAT_GameCore::instance.currentTrailType != OpenSHC::Game::TT_WARCHEST) {
                            if (DAT_GameCore::instance.skipStoreSKMasters == 0) {
                                MACRO_CALL(OpenSHC::Game::Skirmish_Func::StoreGameIntoSKMasters)(
                                    DAT_GameCore::instance.skirmishTrailProgress + 1);
                            }
                            MACRO_CALL(
                                OpenSHC::UI::MenuItems::SelectCrusade_Func::MenuItemActionHandler_SelectCrusade_Main)(
                                1);
                            DAT_GameCore::instance.skipStoreSKMasters = 0;
                        }
                        if (DAT_GameCore::instance.skipStoreSKMasters == 0) {
                            MACRO_CALL(OpenSHC::Game::Skirmish_Func::StoreGameIntoSKMasters)(
                                DAT_GameCore::instance.warchestTrailProgress + 0x33);
                        }
                        MACRO_CALL(
                            OpenSHC::UI::MenuItems::SelectCrusade_Func::MenuItemActionHandler_SelectCrusade_Main)(3);
                        DAT_GameCore::instance.skipStoreSKMasters = 0;
                    }
                } else {
                    if (DAT_GameSynchronyState::instance.currentGameMode
                        == OpenSHC::Game::GM_SKIRMISH_END_OF_GAME_SINGLE_PLAYER) {
                        DAT_GameSynchronyState::instance.currentGameMode = OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER;
                        MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                            OpenSHC::UI::Enums::MVT_RANKING_GAMES, 0);
                        DAT_GameCore::instance.skipStoreSKMasters = 0;
                    }
                    DAT_MenuTextInputState::instance.DAT_MenuOptionsActionParameter = 7;
                    MACRO_CALL(OpenSHC::UI::MenuItems::General_Func::
                            MenuItemActionHandler_General_LaunchOrQuitMultiplayerGameUnk)(0x16);
                    if (DAT_GameSynchronyState::instance.isHost != FALSE) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::Game::Skirmish::SkirmishLobbySetupStructure_Func::restoreSkirmishLobbySetup,
                            SEC_SkirmishLobbySetupStructure::ptr)();
                        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                            DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_HOST_SHARE_LOBBY_STATE);
                        DAT_GameCore::instance.skipStoreSKMasters = 0;
                    }
                }
            } else {
                if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_CAMPAIGN_MISSION) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::Game::GameCore_Func::switchToScenarioDescriptionMenuView, DAT_GameCore::ptr)();
                    DAT_GameCore::instance.skipStoreSKMasters = 0;
                }
                if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_ECONOMIC_CAMPAIGN_SH1) {
                    MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::exitToScenarioDescriptionMenu, DAT_GameCore::ptr)();
                    DAT_GameCore::instance.skipStoreSKMasters = 0;
                }
                if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_BUILDERUnk) {
                    if (DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 == OpenSHC::Map::MT_ECONOMIC) {
                        MACRO_CALL(OpenSHC::UI::MenuItems::MainMenu_Func::MenuItemActionHandler_MainMenu_Main)(3);
                        DAT_GameCore::instance.skipStoreSKMasters = 0;
                    }
                    MACRO_CALL(
                        OpenSHC::UI::MenuItems::CustomScenarios_Func::MenuItemActionHandler_CustomScenarios_Main)(4);
                    DAT_GameCore::instance.skipStoreSKMasters = 0;
                }
                MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    OpenSHC::UI::Enums::MVT_MAIN_MENU, 0);
            }
            DAT_GameCore::instance.skipStoreSKMasters = 0;
        }

    }
}
}
