#include "../GameStartEnterName.func.hpp"

#include "OpenSHC/Audio/MSS/SoundSystem.func.hpp"
#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/Text/UserTextHandler.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/UI/MenuViews/MainMenu.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/Audio/SFX/NameSpeechPair.hpp"
#include "OpenSHC/Audio/SFX/SpeechEffectID.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_MenuView_TriggerPrepare.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_SoundSystemState.hpp"
#include "OpenSHC/Globals/DAT_SpeechDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_UIDragDropDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UserTextHandlerState.hpp"
#include "OpenSHC/Globals/MSVC_SecurityCookie.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuViews {

        using OpenSHC::Audio::SFX::NameSpeechPair;
        using OpenSHC::Audio::SFX::SpeechEffectID;
        using OpenSHC::DE::SHCDE::eTextSections;
        using OpenSHC::UI::Enums::MenuModalType;
        using OpenSHC::UI::Enums::MenuViewType;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          Maybe this functions or part is always passed through on game start, which also triggers the name   call.
          --TheRedDaemon   decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00440560
        void GameStartEnterName::MenuView_GameStartEnterName_Prepare(void* param_1)
        {
            char cVar1;
            char* pcVar2;
            BOOLEnum _lordNameCallable;
            char* pcVar3;
            NameSpeechPair* _callableLordNamePtr;
            int _callableLordNameIndex;
            __time64_t local_10c;
            char _playerLordNameUnk[252];
            uint local_4;
            local_4 = MSVC_SecurityCookie::instance ^ (uint)&local_10c;
            MACRO_CALL(OpenSHC::OS_Func::__time64)(&local_10c);
            MACRO_CALL(OpenSHC::OS_Func::_localtime)(&local_10c);
            pcVar2 = MACRO_CALL_MEMBER(
                OpenSHC::Text::UserTextHandler_Func::getTextArrayPointer, DAT_UserTextHandlerState::ptr)(0);
            pcVar3 = _playerLordNameUnk;
            do {
                cVar1 = *pcVar2;
                *pcVar3 = cVar1;
                pcVar2 = pcVar2 + 1;
                pcVar3 = pcVar3 + 1;
            } while (cVar1 != '\0');
            _callableLordNameIndex = 0;
            _callableLordNamePtr = DAT_SpeechDefinedData::instance.LordNameToCall;
            do {
                _lordNameCallable = MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::isLordNameCallable,
                    DAT_LowLevelMemory::ptr)(_playerLordNameUnk, (char*)((int)(_callableLordNamePtr->name)));
                if (_lordNameCallable != FALSE) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::Audio::MSS::SoundSystem_Func::playSoundOnStream3Unk, DAT_SoundSystemState::ptr)(
                        DAT_SpeechDefinedData::instance.LordNameToCall[_callableLordNameIndex].source, 1);
                    goto LAB_004405eb;
                }
                _callableLordNamePtr = _callableLordNamePtr + 1;
                _callableLordNameIndex = _callableLordNameIndex + 1;
            } while ((int)_callableLordNamePtr < 0xab5708);
            MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSpeechSFX, DAT_SFXState::ptr)(
                OpenSHC::Audio::SFX::SEID_GENERAL_STARTGAME);
        LAB_004405eb:
            pcVar2 = MACRO_CALL_MEMBER(
                OpenSHC::Text::UserTextHandler_Func::getTextArrayPointer, DAT_UserTextHandlerState::ptr)(0);
            pcVar3 = pcVar2 + 1;
            do {
                cVar1 = *pcVar2;
                pcVar2 = pcVar2 + 1;
            } while (cVar1 != '\0');
            if (pcVar2 != pcVar3) {
                DAT_GameCore::instance.unknownFlag_0x118 = TRUE;
                DAT_GameCore::instance.unknownTime_0x11c = timeGetTime();
                MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    OpenSHC::UI::Enums::MVT_MAIN_MENU, 0);
                MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::processMenuViewSwitch, DAT_GameCore::ptr)();
                MACRO_CALL(OpenSHC::UI::MenuViews::MainMenu_Func::MenuView_MainMenu_Prepare)();
                MACRO_CALL(OpenSHC::UI::MenuViews::MainMenu_Func::MenuView_MainMenu_DoInitial)();
                MACRO_CALL(OpenSHC::UI::MenuViews::MainMenu_Func::MenuView_MainMenu_DoEveryFrame)();
                DAT_UIDragDropDefinedData::instance.MenuView_TriggerInitial = FALSE;
                DAT_MenuView_TriggerPrepare::instance = FALSE;
                ;
            }
            DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                DAT_TextureRenderCoreObject::ptr)("frontend_combat3.tgx");
            MACRO_CALL(OpenSHC::UI::Helpers_Func::LoadTGX_shc_back)();
            DAT_GameCore::instance.unknownFlag_0x118 = FALSE;
            MACRO_CALL_MEMBER(OpenSHC::Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(0);
            /*
              added by script: "Lord Crusader"
             */
            MACRO_CALL_MEMBER(OpenSHC::Text::UserTextHandler_Func::copyIntoTextArray, DAT_UserTextHandlerState::ptr)(MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_GAME_OPTIONS, 0x30));
            MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                DAT_MenuModalComposition1::ptr)(OpenSHC::UI::Enums::MMT_ENTER_TITLE_ON_GAME_START, FALSE);
            ;
        }

    }
}
}
