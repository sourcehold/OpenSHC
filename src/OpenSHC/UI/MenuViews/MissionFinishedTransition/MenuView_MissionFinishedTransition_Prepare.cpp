#include "../MissionFinishedTransition.func.hpp"

#include "OpenSHC/Audio/MSS/SoundSystem.func.hpp"
#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Game/Skirmish.func.hpp"
#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/IO/ResourceManager.func.hpp"
#include "OpenSHC/Map/MapPropertiesState.func.hpp"
#include "OpenSHC/Rendering/Bink/BinkControlClass.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/UI/MenuTextInputState.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/IO/FileResourceType.hpp"
#include "OpenSHC/Rendering/ScreenResolutionEnum.hpp"
#include "OpenSHC/Text/TextArrayIndexType.hpp"
#include "OpenSHC/UI/Enums/BuildingsAndStatusMenuTabType.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/BOOLEnum_00ed279c.hpp"
#include "OpenSHC/Globals/CHAR_00eb0e44.hpp"
#include "OpenSHC/Globals/CHAR_ARRAY_00eb9ac8.hpp"
#include "OpenSHC/Globals/COL_BLACK.hpp"
#include "OpenSHC/Globals/DAT_00eb9af8.hpp"
#include "OpenSHC/Globals/DAT_BinkControlState.hpp"
#include "OpenSHC/Globals/DAT_FinalResultsOrderByColumn.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition2.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition3.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_ResourceManager.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_SoundSystemState.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_VideoBikQueue.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"
#include "OpenSHC/Globals/DWORD_00ed27b4.hpp"
#include "OpenSHC/Globals/INT_00ec0828.hpp"
#include "OpenSHC/Globals/INT_00ec082c.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuViews {

        // FUNCTION: STRONGHOLDCRUSADER 0x004E1B30
        void MissionFinishedTransition::MenuView_MissionFinishedTransition_Prepare()
        {
            DAT_GameCore::instance.gameDuration = timeGetTime() - DAT_GameCore::instance.timeSum_2;
            BOOLEnum_00ed279c::instance = FALSE;
            DAT_FinalResultsOrderByColumn::instance = 0;
            DAT_00eb9af8::instance = 0;
            DAT_GameCore::instance.currentlyInGameUnk_0xa4 = FALSE;
            if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_800x600) {
                DAT_GameCore::instance.activeMenuTab.tabType = OpenSHC::UI::Enums::BASMTT_NONE;
                INT_00ec082c::instance = 0;
            } else {
                DAT_GameCore::instance.activeMenuTab.tabType = OpenSHC::UI::Enums::BASMTT_KEEP_OR_MPMENU_IPX;
                INT_00ec082c::instance = 2;
            }
            DAT_VideoBikQueue::instance.storedMessages_0x924 = 0;
            DWORD_00ed27b4::instance = 0;
            MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                DAT_MenuModalComposition1::ptr)(OpenSHC::UI::Enums::MMT_NONE, FALSE);
            MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                DAT_MenuModalComposition2::ptr)(OpenSHC::UI::Enums::MMT_NONE, FALSE);
            MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                DAT_MenuModalComposition3::ptr)(OpenSHC::UI::Enums::MMT_NONE, FALSE);
            CHAR_00eb0e44::instance = 0;
            MACRO_CALL(OpenSHC::Game::Skirmish_Func::StoreLocalTime)();
            int const menuY = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight;
            int const menuX = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth;
            Menu* const menu = DAT_MenuHandlerState::instance.currentMenu;
            menu->xPosition = menuX;
            menu->yPosition = menuY;
            DAT_MenuHandlerState::instance.y = menuY;
            DAT_MenuHandlerState::instance.x = menuX;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox, DAT_PencilRenderCore::ptr)(0,
                0, DAT_WindowAndDirectDraw::instance.resolutionX, DAT_WindowAndDirectDraw::instance.resolutionY,
                COL_BLACK::instance.shortValue);
            // the victory video unless at the skirmish end screen: Arabian for missions 7 to 11 or an Arabian lord
            // four calls (one call after picking the file: quick_diff 0.9845 -> 0.8421)
            if (DAT_GameSynchronyState::instance.currentGameMode
                != OpenSHC::Game::GM_SKIRMISH_END_OF_GAME_SINGLE_PLAYER) {
                if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_CAMPAIGN_MISSION) {
                    if (DAT_GameCore::instance.missionNumber1to20 >= 7
                        && DAT_GameCore::instance.missionNumber1to20 <= 11) {
                        // "arabian_win.bik"
                        MACRO_CALL_MEMBER(OpenSHC::Rendering::Bink::BinkControlClass_Func::playBINK,
                            DAT_BinkControlState::ptr)(0, (char*)s_arabian_win_bik_005ab800, 0, 0,
                            DAT_MenuHandlerState::instance.x + 80, DAT_MenuHandlerState::instance.y + 60, 2);
                    } else {
                        // "crusader_win.bik"
                        MACRO_CALL_MEMBER(OpenSHC::Rendering::Bink::BinkControlClass_Func::playBINK,
                            DAT_BinkControlState::ptr)(0, (char*)s_crusader_win_bik_005ab7ec, 0, 0,
                            DAT_MenuHandlerState::instance.x + 80, DAT_MenuHandlerState::instance.y + 60, 2);
                    }
                } else if (MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::getLordTypeForPlayer,
                               DAT_GameSynchronyState::ptr)(DAT_GameSynchronyState::instance.currentPlayerSlotID)
                    == 1) {
                    // "arabian_win.bik"
                    MACRO_CALL_MEMBER(OpenSHC::Rendering::Bink::BinkControlClass_Func::playBINK,
                        DAT_BinkControlState::ptr)(0, (char*)s_arabian_win_bik_005ab800, 0, 0,
                        DAT_MenuHandlerState::instance.x + 80, DAT_MenuHandlerState::instance.y + 60, 2);
                } else {
                    // "crusader_win.bik"
                    MACRO_CALL_MEMBER(OpenSHC::Rendering::Bink::BinkControlClass_Func::playBINK,
                        DAT_BinkControlState::ptr)(0, (char*)s_crusader_win_bik_005ab7ec, 0, 0,
                        DAT_MenuHandlerState::instance.x + 80, DAT_MenuHandlerState::instance.y + 60, 2);
                }
            }
            // a skirmish's end shows its stored end-screen picture
            if (DAT_GameSynchronyState::instance.currentGameMode
                == OpenSHC::Game::GM_SKIRMISH_END_OF_GAME_SINGLE_PLAYER) {
                DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)(CHAR_ARRAY_00eb9ac8::instance);
            }
            if (DAT_GameSynchronyState::instance.currentGameMode
                != OpenSHC::Game::GM_SKIRMISH_END_OF_GAME_SINGLE_PLAYER) {
                // the victory speech in a skirmish game or while any player is alive
                int alivePlayers = 0;
                for (int player = 1; player < countof(DAT_GameState::instance.mapAndTime.playerIsAlive); ++player) {
                    if (DAT_GameState::instance.mapAndTime.playerIsAlive[player]) {
                        ++alivePlayers;
                    }
                }
                if (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER
                    || alivePlayers != 0) {
                    if (SEC_RNG::instance.currentNumber1 % 3 != 0) {
                        // "Victory!" ("general_victory1.wav")
                        MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                            s_general_victory1_wav_005ab7d4);
                    } else {
                        // "We are victorious sire!" ("general_victory2.wav")
                        MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                            s_general_victory2_wav_005ab7bc);
                    }
                }
                MACRO_CALL_MEMBER(
                    OpenSHC::Audio::MSS::SoundSystem_Func::playWinMusicVariation, DAT_SoundSystemState::ptr)();
            }
            DAT_MenuTextInputState::instance.DAT_SomeTextArrayIndex = OpenSHC::Text::TAIT_NINE__FILTER_B;
            MACRO_CALL_MEMBER(
                OpenSHC::UI::MenuTextInputState_Func::clearAnyOtherModalDialogs, DAT_MenuTextInputState::ptr)();
            // outside skirmish and multiplayer, the mission's score goes into its .sco file
            if (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_SKIRMISH_AND_MULTIPLAYER) {
                INT_00ec0828::instance = 0;
                MACRO_CALL_MEMBER(OpenSHC::Map::MapPropertiesState_Func::computeMissionCompletionScore,
                    DAT_MapPropertiesState::ptr)();
                char fileName[256];
                // "sco"
                MACRO_CALL_MEMBER(
                    OpenSHC::IO::LowLevelMemory_Func::putFileNameAndAppendFileExtension, DAT_LowLevelMemory::ptr)(
                    (char*)DAT_MapPropertiesState::instance.SEC_Section1089, fileName, (char*)s_sco_005ab7b8);
                MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::resolveResourceFileName, DAT_ResourceManager::ptr)(
                    OpenSHC::IO::FRT_SCORES, fileName);
                // the file name first, then the call (the name inside the call: quick_diff 0.9845 -> 0.9741)
                char* const scoresFile = MACRO_CALL_MEMBER(
                    OpenSHC::IO::ResourceManager_Func::getFileNameOfCurrentActiveResource, DAT_ResourceManager::ptr)();
                MACRO_CALL(OpenSHC::UI::Helpers_Func::WriteMissionToScoresFile)(
                    scoresFile, DAT_MapPropertiesState::instance.missionScore);
            }
            MACRO_CALL(OpenSHC::UI::Helpers_Func::LoadTGX_shc_back)();
        }

    }
}
}
