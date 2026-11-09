#include "../HistoricCampaignIntro.func.hpp"

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

        // FUNCTION: STRONGHOLDCRUSADER 0x004DBAF0
        void HistoricCampaignIntro::MenuView_HistoricCampaignIntro_Prepare()
        {
            MACRO_CALL(UI::Helpers_Func::PrepareHistoryBook)();
            switch (DAT_GameCore::instance.historicCampaignNumber) {
            case 1:
                DAT_00eb0b20::instance = MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)(s_c1pic_tgx_005ab0ec);
                break;
            case 2:
                DAT_00eb0b20::instance = MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)(s_c2pic_tgx_005ab0e0);
                break;
            case 3:
                DAT_00eb0b20::instance = MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)(s_c3pic_tgx_005ab0d4);
                break;
            case 4:
                DAT_00eb0b20::instance = MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)(s_c4pic_tgx_005ab0c8);
                break;
            }
            DAT_NumberOfStoredMenuStrings::instance = 0;
            char* text
                = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                    DE::SHCDE::TEXT_CAMPAIGN_INFO, (int)(DAT_GameCore::instance.historicCampaignNumber * 6 - 5));
            MACRO_CALL(UI::Helpers_Func::StoreStringInMenuStringArray)(text);
            text = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                DE::SHCDE::TEXT_CAMPAIGN_INFO, (int)(DAT_GameCore::instance.historicCampaignNumber * 6 - 4));
            MACRO_CALL(UI::Helpers_Func::StoreStringInMenuStringArray)(text);
            MACRO_CALL(UI::Helpers_Func::LoadTGX_shc_back)();
            FLOAT_00ec0834::instance = 0.0;
            DAT_00ed2780::instance = 1;
            MACRO_CALL(Rendering_Func::TicksStartCounter)();
        }

    }
}
}
