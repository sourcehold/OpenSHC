#include "../HistoricCampaignOutro.func.hpp"

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

        // FUNCTION: STRONGHOLDCRUSADER 0x004DBE30
        void HistoricCampaignOutro::MenuView_HistoricCampaignOutro_Prepare()
        {
            MACRO_CALL(OpenSHC::UI::Helpers_Func::PrepareHistoryBook)();
            // the campaign's picture
            switch (DAT_GameCore::instance.historicCampaignNumber) {
            case 1:
                // "c1pic.tgx"
                DAT_00eb0b20::instance = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)(s_c1pic_tgx_005ab0ec);
                break;
            case 2:
                // "c2pic.tgx"
                DAT_00eb0b20::instance = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)(s_c2pic_tgx_005ab0e0);
                break;
            case 3:
                // "c3pic.tgx"
                DAT_00eb0b20::instance = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)(s_c3pic_tgx_005ab0d4);
                break;
            case 4:
                // "c4pic.tgx"
                DAT_00eb0b20::instance = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)(s_c4pic_tgx_005ab0c8);
                break;
            }
            MACRO_CALL(OpenSHC::UI::Helpers_Func::LoadTGX_shc_back)();
            // "Aftermath" and the campaign's closing text, the last two of its six in TEXT_CAMPAIGN_INFO
            DAT_NumberOfStoredMenuStrings::instance = 0;
            MACRO_CALL(OpenSHC::UI::Helpers_Func::StoreStringInMenuStringArray)(MACRO_CALL_MEMBER(
                OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                OpenSHC::DE::SHCDE::TEXT_CAMPAIGN_INFO, DAT_GameCore::instance.historicCampaignNumber * 6 - 2));
            MACRO_CALL(OpenSHC::UI::Helpers_Func::StoreStringInMenuStringArray)(MACRO_CALL_MEMBER(
                OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                OpenSHC::DE::SHCDE::TEXT_CAMPAIGN_INFO, DAT_GameCore::instance.historicCampaignNumber * 6 - 1));
            FLOAT_00ec0834::instance = 0.0;
            DAT_00ed2780::instance = 1;
            MACRO_CALL(OpenSHC::Rendering_Func::TicksStartCounter)();
        }

    }
}
}
