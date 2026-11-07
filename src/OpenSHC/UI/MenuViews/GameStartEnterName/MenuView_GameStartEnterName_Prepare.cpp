// disable deprecation warnings for strcpy
#pragma warning(disable : 4996)

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
#include "OpenSHC/Audio/SFX/SpeechEffectID.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Text/TextArrayIndexType.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
#include "OpenSHC/string-literals.hpp"

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

namespace OpenSHC {
namespace UI {
    namespace MenuViews {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00440560
        void GameStartEnterName::MenuView_GameStartEnterName_Prepare()
        {
            // the original reads the local time and drops it
            __time64_t now;
            MACRO_CALL(OpenSHC::OS_Func::__time64)(&now);
            MACRO_CALL(OpenSHC::OS_Func::_localtime)(&now);
            // the lord's name, spoken when the game has a recording of it, otherwise the start-game line
            char lordName[256];
            strcpy(lordName,
                MACRO_CALL_MEMBER(
                    OpenSHC::Text::UserTextHandler_Func::getTextArrayPointer, DAT_UserTextHandlerState::ptr)(0));
            BOOLEnum named = FALSE;
            for (int lord = 0; lord < countof(DAT_SpeechDefinedData::instance.LordNameToCall); ++lord) {
                if (MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::isLordNameCallable, DAT_LowLevelMemory::ptr)(
                        lordName, DAT_SpeechDefinedData::instance.LordNameToCall[lord].name)) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::MSS::SoundSystem_Func::playSoundOnStream3Unk,
                        DAT_SoundSystemState::ptr)(DAT_SpeechDefinedData::instance.LordNameToCall[lord].source, 1);
                    named = TRUE;
                    break;
                }
            }
            if (!named) {
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSpeechSFX, DAT_SFXState::ptr)(
                    OpenSHC::Audio::SFX::SEID_GENERAL_STARTGAME);
            }
            // a name already entered: straight on to the main menu (strlen: quick_diff 0.9577 -> 0.9296)
            char* text = MACRO_CALL_MEMBER(
                OpenSHC::Text::UserTextHandler_Func::getTextArrayPointer, DAT_UserTextHandlerState::ptr)(0);
            char* const start = text + 1;
            for (;;) {
                char const c = *text++;
                if (c == '\0') {
                    break;
                }
            }
            if (text - start != 0) {
                DAT_GameCore::instance.isNameEntryActive = TRUE;
                DAT_GameCore::instance.nameEntryStartTime = timeGetTime();
                MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    OpenSHC::UI::Enums::MVT_MAIN_MENU, 0);
                MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::processMenuViewSwitch, DAT_GameCore::ptr)();
                MACRO_CALL(OpenSHC::UI::MenuViews::MainMenu_Func::MenuView_MainMenu_Prepare)();
                MACRO_CALL(OpenSHC::UI::MenuViews::MainMenu_Func::MenuView_MainMenu_DoInitial)();
                MACRO_CALL(OpenSHC::UI::MenuViews::MainMenu_Func::MenuView_MainMenu_DoEveryFrame)();
                DAT_UIDragDropDefinedData::instance.MenuView_TriggerInitial = FALSE;
                DAT_MenuView_TriggerPrepare::instance = FALSE;
                return;
            }
            // otherwise the name entry dialog, filled in with "Lord Crusader"
            DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
            // "frontend_combat3.tgx"
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                DAT_TextureRenderCoreObject::ptr)(s_frontend_combat3_tgx_005a2134);
            MACRO_CALL(OpenSHC::UI::Helpers_Func::LoadTGX_shc_back)();
            DAT_GameCore::instance.isNameEntryActive = FALSE;
            MACRO_CALL_MEMBER(OpenSHC::Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(
                OpenSHC::Text::TAIT_ZERO);
            // "Lord Crusader"
            MACRO_CALL_MEMBER(OpenSHC::Text::UserTextHandler_Func::copyIntoTextArray, DAT_UserTextHandlerState::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_GAME_OPTIONS, 48));
            MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                DAT_MenuModalComposition1::ptr)(OpenSHC::UI::Enums::MMT_ENTER_TITLE_ON_GAME_START, FALSE);
        }

    }
}
}
