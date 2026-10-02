#include "../HistoricMissionIntro.func.hpp"

#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Rendering.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"

#include "OpenSHC/Globals/DAT_00eb0b20.hpp"
#include "OpenSHC/Globals/DAT_00ed2780.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_NumberOfStoredMenuStrings.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/FLOAT_00ec0834.hpp"
#include "OpenSHC/Globals/MSVC_SecurityCookie.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuViews {

        using OpenSHC::DE::SHCDE::eTextSections;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004DB7B0
        void HistoricMissionIntro::MenuView_HistoricMissionIntro_Prepare()
        {
            char* pcVar1;
            char _tgxFileName[16];
            uint local_4;
            local_4 = MSVC_SecurityCookie::instance ^ (uint)_tgxFileName;
            MACRO_CALL(OpenSHC::UI::Helpers_Func::PrepareHistoryBook)();
            MACRO_CALL(OpenSHC::OS_Func::_sprintf)(
                _tgxFileName, "m%dmap.tgx", DAT_GameCore::instance.missionNumber1to20);
            DAT_00eb0b20::instance = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                DAT_TextureRenderCoreObject::ptr)(_tgxFileName);
            DAT_NumberOfStoredMenuStrings::instance = 0;
            pcVar1 = MACRO_CALL_MEMBER(
                OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                (OpenSHC::DE::SHCDE::eTextSections)(DAT_GameCore::instance.missionNumber1to20 * 4 + 95), 0);
            MACRO_CALL(OpenSHC::UI::Helpers_Func::StoreStringInMenuStringArray)(pcVar1);
            pcVar1 = MACRO_CALL_MEMBER(
                OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                (OpenSHC::DE::SHCDE::eTextSections)(DAT_GameCore::instance.missionNumber1to20 * 4
                    + OpenSHC::DE::SHCDE::TEXT_TUTORIAL),
                1);
            MACRO_CALL(OpenSHC::UI::Helpers_Func::StoreStringInMenuStringArray)(pcVar1);
            pcVar1 = MACRO_CALL_MEMBER(
                OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                (OpenSHC::DE::SHCDE::eTextSections)(DAT_GameCore::instance.missionNumber1to20 * 4
                    + OpenSHC::DE::SHCDE::TEXT_TUTORIAL),
                2);
            MACRO_CALL(OpenSHC::UI::Helpers_Func::StoreStringInMenuStringArray)(pcVar1);
            FLOAT_00ec0834::instance = 0.0;
            DAT_00ed2780::instance = 1;
            MACRO_CALL(OpenSHC::UI::Helpers_Func::TrimStoredMenuString)(
                2, (undefined4)((int)(30)), (undefined4)((int)(380)), (int)((int)(740)), 0, (int)((int)(17)));
            MACRO_CALL(OpenSHC::Rendering_Func::TicksStartCounter)();
            MACRO_CALL(OpenSHC::UI::Helpers_Func::LoadTGX_shc_back)();
            ;
        }

    }
}
}
