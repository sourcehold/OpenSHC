#include "../HistoricCampaignOutro.func.hpp"

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

namespace OpenSHC {
namespace UI {
    namespace MenuViews {

        using OpenSHC::DE::SHCDE::eTextSections;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004DBE30
        void HistoricCampaignOutro::MenuView_HistoricCampaignOutro_Prepare()
        {
            MACRO_CALL(OpenSHC::UI::Helpers_Func::PrepareHistoryBook)();
            switch (DAT_GameCore::instance.historicCampaignNumber) {
            case 1:
                DAT_00eb0b20::instance = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)("c1pic.tgx");
                break;
            case 2:
                DAT_00eb0b20::instance = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)("c2pic.tgx");
                break;
            case 3:
                DAT_00eb0b20::instance = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)("c3pic.tgx");
                break;
            case 4:
                DAT_00eb0b20::instance = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)("c4pic.tgx");
                break;
            }
            MACRO_CALL(OpenSHC::UI::Helpers_Func::LoadTGX_shc_back)();
            DAT_NumberOfStoredMenuStrings::instance = 0;
            MACRO_CALL(OpenSHC::UI::Helpers_Func::StoreStringInMenuStringArray)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_CAMPAIGN_INFO,
                    (int)((int)(DAT_GameCore::instance.historicCampaignNumber * 6 + -2))));
            MACRO_CALL(OpenSHC::UI::Helpers_Func::StoreStringInMenuStringArray)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_CAMPAIGN_INFO,
                    (int)((int)(DAT_GameCore::instance.historicCampaignNumber * 6 + -1))));
            FLOAT_00ec0834::instance = 0.0;
            DAT_00ed2780::instance = 1;
            MACRO_CALL(OpenSHC::Rendering_Func::TicksStartCounter)();
        }

    }
}
}
