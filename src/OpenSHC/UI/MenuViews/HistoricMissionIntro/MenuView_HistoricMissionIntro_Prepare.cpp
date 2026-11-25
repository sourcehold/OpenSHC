#include "../HistoricMissionIntro.func.hpp"

#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Rendering.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_00eb0b20.hpp"
#include "OpenSHC/Globals/DAT_00ed2780.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_NumberOfStoredMenuStrings.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/FLOAT_00ec0834.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuViews {

        using OpenSHC::DE::SHCDE::eTextSections;

        // FUNCTION: STRONGHOLDCRUSADER 0x004DB7B0
        void HistoricMissionIntro::MenuView_HistoricMissionIntro_Prepare()
        {
            MACRO_CALL(OpenSHC::UI::Helpers_Func::PrepareHistoryBook)();
            // the mission's map
            char fileName[16];
            // "m%dmap.tgx"
            MACRO_CALL(OpenSHC::OS_Func::_sprintf)(
                fileName, s_m_dmap_tgx_005ab0b8, DAT_GameCore::instance.missionNumber1to20);
            DAT_00eb0b20::instance = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                DAT_TextureRenderCoreObject::ptr)(fileName);
            // the mission's story group: "Mission N", its title and the story
            DAT_NumberOfStoredMenuStrings::instance = 0;
            // three calls (a loop over the text number: quick_diff 0.9677 -> 0.6903)
            MACRO_CALL(OpenSHC::UI::Helpers_Func::StoreStringInMenuStringArray)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)((eTextSections)((DAT_GameCore::instance.missionNumber1to20 - 1) * 4
                                                    + OpenSHC::DE::SHCDE::TEXT_MISSION1_STORY),
                    0));
            MACRO_CALL(OpenSHC::UI::Helpers_Func::StoreStringInMenuStringArray)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)((eTextSections)((DAT_GameCore::instance.missionNumber1to20 - 1) * 4
                                                    + OpenSHC::DE::SHCDE::TEXT_MISSION1_STORY),
                    1));
            MACRO_CALL(OpenSHC::UI::Helpers_Func::StoreStringInMenuStringArray)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)((eTextSections)((DAT_GameCore::instance.missionNumber1to20 - 1) * 4
                                                    + OpenSHC::DE::SHCDE::TEXT_MISSION1_STORY),
                    2));
            FLOAT_00ec0834::instance = 0.0;
            DAT_00ed2780::instance = 1;
            // the story (stored text 2), 740 wide in font size 17
            MACRO_CALL(OpenSHC::UI::Helpers_Func::TrimStoredMenuString)(2, 30, 380, 740, 0, 17);
            MACRO_CALL(OpenSHC::Rendering_Func::TicksStartCounter)();
            MACRO_CALL(OpenSHC::UI::Helpers_Func::LoadTGX_shc_back)();
        }

    }
}
}
