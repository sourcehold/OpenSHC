#include "../HistoricMissionPicture.func.hpp"

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

        // FUNCTION: STRONGHOLDCRUSADER 0x004DB4F0
        void HistoricMissionPicture::MenuView_HistoricMissionPicture_Prepare()
        {
            // the picture of the mission's campaign, five missions each: missions 1 to 5 show m1pic.tgx
            char fileName[16];
            // "m%dpic.tgx"
            MACRO_CALL(OpenSHC::OS_Func::_sprintf)(
                fileName, s_m_dpic_tgx_005ab0a0, (DAT_GameCore::instance.missionNumber1to20 - 1) / 5 + 1);
            MACRO_CALL(OpenSHC::UI::Helpers_Func::PrepareHistoryBook)();
            DAT_00eb0b20::instance = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                DAT_TextureRenderCoreObject::ptr)(fileName);
            // the mission's story group: "Mission N" and its title
            DAT_NumberOfStoredMenuStrings::instance = 0;
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
            FLOAT_00ec0834::instance = 0.0;
            DAT_00ed2780::instance = 1;
            MACRO_CALL(OpenSHC::Rendering_Func::TicksStartCounter)();
            MACRO_CALL(OpenSHC::UI::Helpers_Func::LoadTGX_shc_back)();
        }

    }
}
}
