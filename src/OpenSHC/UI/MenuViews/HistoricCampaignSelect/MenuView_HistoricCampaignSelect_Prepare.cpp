#include "../HistoricCampaignSelect.func.hpp"

#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_MenuModalComposition3.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_UIButtonDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UnknownGFXIndex.hpp"
#include "OpenSHC/Globals/INT_00b95abc.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuViews {

        // FUNCTION: STRONGHOLDCRUSADER 0x00425500
        void HistoricCampaignSelect::MenuView_HistoricCampaignSelect_Prepare()
        {
            DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
                s_frontend_combat_tgx_005a2028);
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
                s_frontend_combat2_tgx_005a2010);
            MACRO_CALL(UI::Helpers_Func::LoadTGX_shc_back)();
            DWORD DVar1 = timeGetTime();
            DAT_UIButtonDefinedData::instance.ButtonGmDataArray[355].stateTransitionTimeBaseUnk_0x18 = DVar1 - 4800;
            DAT_UIButtonDefinedData::instance.ButtonGmDataArray[356].stateTransitionTimeBaseUnk_0x18 = DVar1 - 3200;
            DAT_UIButtonDefinedData::instance.ButtonGmDataArray[357].stateTransitionTimeBaseUnk_0x18 = DVar1 - 1600;
            DAT_UIButtonDefinedData::instance.ButtonGmDataArray[358].stateTransitionTimeBaseUnk_0x18 = DVar1;
            INT_00b95abc::instance = -1;
            DAT_UnknownGFXIndex::instance = 0;
            MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog, DAT_MenuModalComposition3::ptr)(
                UI::Enums::MMT_NONE, FALSE);
        }

    }
}
}
