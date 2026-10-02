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
#include "OpenSHC/UI/Enums/BuildingsAndStatusMenuTabType.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/CHAR_ARRAY_00eb9ac8.hpp"
#include "OpenSHC/Globals/COL_BLACK.hpp"
#include "OpenSHC/Globals/DAT_00eb9af8.hpp"
#include "OpenSHC/Globals/DAT_00ec082c.hpp"
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
#include "OpenSHC/Globals/INT_00eb0e44.hpp"
#include "OpenSHC/Globals/INT_00ec0828.hpp"
#include "OpenSHC/Globals/INT_00ed279c.hpp"
#include "OpenSHC/Globals/MSVC_SecurityCookie.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuViews {

        using OpenSHC::Game::GameMode;
        using OpenSHC::Game::GameMode2;
        using OpenSHC::IO::FileResourceType;
        using OpenSHC::Rendering::ScreenResolutionEnum;
        using OpenSHC::UI::Enums::BuildingsAndStatusMenuTabType;
        using OpenSHC::UI::Enums::MenuModalType;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
         */
        /*
          WARNING: Enum "DPERRInt": Some values do not have unique names
         */
        /*
          WARNING: Enum "UnsortedBinkFlagInt": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004E1B30
        void MissionFinishedTransition::MenuView_MissionFinishedTransition_Prepare()
        {
            Menu* pMVar1;
            DWORD DVar2;
            int iVar3;
            int xPos;
            char cVar4;
            char* pcVar5;
            char local_104[256];
            uint local_4;
            local_4 = MSVC_SecurityCookie::instance ^ (uint)local_104;
            DVar2 = timeGetTime();
            DAT_GameCore::instance.gameDuration = DVar2 - DAT_GameCore::instance.timeSum_2;
            INT_00ed279c::instance = 0;
            DAT_FinalResultsOrderByColumn::instance = 0;
            DAT_00eb9af8::instance = 0;
            DAT_GameCore::instance.currentlyInGameUnk_0xa4 = FALSE;
            if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_800x600) {
                DAT_GameCore::instance.activeMenuTab.tabType = ((BuildingsAndStatusMenuTabType)0);
                DAT_00ec082c::instance = 0;
            } else {
                DAT_GameCore::instance.activeMenuTab.tabType = OpenSHC::UI::Enums::BASMTT_KEEP_OR_MPMENU_IPX;
                DAT_00ec082c::instance = 2;
            }
            DAT_VideoBikQueue::instance.storedMessages_0x924 = 0;
            DWORD_00ed27b4::instance = 0;
            MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                DAT_MenuModalComposition1::ptr)(OpenSHC::UI::Enums::MMT_NONE, FALSE);
            MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                DAT_MenuModalComposition2::ptr)(OpenSHC::UI::Enums::MMT_NONE, FALSE);
            MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                DAT_MenuModalComposition3::ptr)(OpenSHC::UI::Enums::MMT_NONE, FALSE);
            (*(char*)&INT_00eb0e44::instance) = 0;
            MACRO_CALL(OpenSHC::Game::Skirmish_Func::StoreLocalTime)();
            DAT_MenuHandlerState::instance.y = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight;
            DAT_MenuHandlerState::instance.x = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth;
            pMVar1 = DAT_MenuHandlerState::instance.currentMenu;
            (DAT_MenuHandlerState::instance.currentMenu)->xPosition
                = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth;
            pMVar1->yPosition = DAT_MenuHandlerState::instance.y;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox, DAT_PencilRenderCore::ptr)(0,
                0, DAT_WindowAndDirectDraw::instance.resolutionX, DAT_WindowAndDirectDraw::instance.resolutionY,
                (ushort)((int)(COL_BLACK::instance.shortValue)));
            if (DAT_GameSynchronyState::instance.currentGameMode
                == OpenSHC::Game::GM_SKIRMISH_END_OF_GAME_SINGLE_PLAYER) {
            LAB_004e1cdd:
                DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)(CHAR_ARRAY_00eb9ac8::instance);
                if (DAT_GameSynchronyState::instance.currentGameMode
                    == OpenSHC::Game::GM_SKIRMISH_END_OF_GAME_SINGLE_PLAYER)
                    goto LAB_004e1da4;
            } else {
                if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_CAMPAIGN_MISSION) {
                    if (DAT_GameCore::instance.missionNumber1to20 - 7U < 5) {
                        iVar3 = DAT_MenuHandlerState::instance.y + 0x3c;
                        xPos = DAT_MenuHandlerState::instance.x + 0x50;
                        pcVar5 = "arabian_win.bik";
                    } else {
                    LAB_004e1cbd:
                        iVar3 = DAT_MenuHandlerState::instance.y + 0x3c;
                        xPos = DAT_MenuHandlerState::instance.x + 0x50;
                        pcVar5 = "crusader_win.bik";
                    }
                } else {
                    iVar3 = MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::getLordTypeForPlayer,
                        DAT_GameSynchronyState::ptr)(DAT_GameSynchronyState::instance.currentPlayerSlotID);
                    if (iVar3 != 1)
                        goto LAB_004e1cbd;
                    iVar3 = DAT_MenuHandlerState::instance.y + 0x3c;
                    xPos = DAT_MenuHandlerState::instance.x + 0x50;
                    pcVar5 = "arabian_win.bik";
                }
                MACRO_CALL_MEMBER(OpenSHC::Rendering::Bink::BinkControlClass_Func::playBINK, DAT_BinkControlState::ptr)(
                    0, pcVar5, 0, 0, xPos, iVar3, 2);
                if (DAT_GameSynchronyState::instance.currentGameMode
                    == OpenSHC::Game::GM_SKIRMISH_END_OF_GAME_SINGLE_PLAYER)
                    goto LAB_004e1cdd;
            }
            cVar4 = DAT_GameState::instance.mapAndTime.playerIsAlive[1] != 0;
            if (DAT_GameState::instance.mapAndTime.playerIsAlive[2] != 0) {
                cVar4 = cVar4 + '\x01';
            }
            if (DAT_GameState::instance.mapAndTime.playerIsAlive[3] != 0) {
                cVar4 = cVar4 + '\x01';
            }
            if (DAT_GameState::instance.mapAndTime.playerIsAlive[4] != 0) {
                cVar4 = cVar4 + '\x01';
            }
            if (DAT_GameState::instance.mapAndTime.playerIsAlive[5] != 0) {
                cVar4 = cVar4 + '\x01';
            }
            if (DAT_GameState::instance.mapAndTime.playerIsAlive[6] != 0) {
                cVar4 = cVar4 + '\x01';
            }
            if (DAT_GameState::instance.mapAndTime.playerIsAlive[7] != 0) {
                cVar4 = cVar4 + '\x01';
            }
            if (DAT_GameState::instance.mapAndTime.playerIsAlive[8] != 0) {
                cVar4 = cVar4 + '\x01';
            }
            if ((DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER)
                || (cVar4 != '\0')) {
                if ((int)SEC_RNG::instance.currentNumber1 % 3 == 0) {
                    /*
                      "We are victorious sire!"
                     */
                    pcVar5 = "general_victory2.wav";
                } else {
                    /*
                      "Victory!"
                     */
                    pcVar5 = "general_victory1.wav";
                }
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(pcVar5);
            }
            MACRO_CALL_MEMBER(
                OpenSHC::Audio::MSS::SoundSystem_Func::playWinMusicVariation, DAT_SoundSystemState::ptr)();
        LAB_004e1da4:
            DAT_MenuTextInputState::instance.DAT_SomeTextArrayIndex = 9;
            MACRO_CALL_MEMBER(
                OpenSHC::UI::MenuTextInputState_Func::clearAnyOtherModalDialogs, DAT_MenuTextInputState::ptr)();
            if (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_SKIRMISH_AND_MULTIPLAYER) {
                INT_00ec0828::instance = 0;
                MACRO_CALL_MEMBER(OpenSHC::Map::MapPropertiesState_Func::computeMissionCompletionScore,
                    DAT_MapPropertiesState::ptr)();
                MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::putFileNameAndAppendFileExtension,
                    DAT_LowLevelMemory::ptr)((char*)DAT_MapPropertiesState::ptr, (char*)((int)(local_104)), "sco");
                MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::resolveResourceFileName, DAT_ResourceManager::ptr)(
                    OpenSHC::IO::FRT_SCORES, (char const*)((int)(local_104)));
                pcVar5 = MACRO_CALL_MEMBER(
                    OpenSHC::IO::ResourceManager_Func::getFileNameOfCurrentActiveResource, DAT_ResourceManager::ptr)();
                MACRO_CALL(OpenSHC::UI::Helpers_Func::WriteMissionToScoresFile)(
                    pcVar5, (int)((int)(DAT_MapPropertiesState::instance.field91_0x14554)));
            }
            MACRO_CALL(OpenSHC::UI::Helpers_Func::LoadTGX_shc_back)();
            ;
        }

    }
}
}
