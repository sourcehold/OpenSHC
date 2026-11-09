#include "../HistoricCampaignSelect.func.hpp"

#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_MenuModalComposition3.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_UIButtonDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UnknownGFXIndex.hpp"
#include "OpenSHC/Globals/INT_00b95abc.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuViews {

        using UI::Enums::MenuModalType;
        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00425500
        void HistoricCampaignSelect::MenuView_HistoricCampaignSelect_Prepare()
        {
            DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                DAT_TextureRenderCoreObject::ptr)("frontend_combat.tgx");
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                DAT_TextureRenderCoreObject::ptr)("frontend_combat2.tgx");
            MACRO_CALL(UI::Helpers_Func::LoadTGX_shc_back)();
            DWORD DVar1 = timeGetTime();
            DAT_UIButtonDefinedData::instance.ButtonGmDataArray[0x163].stateTransitionTimeBaseUnk_0x18
                = DVar1 - 0x12c0;
            DAT_UIButtonDefinedData::instance.ButtonGmDataArray[0x164].stateTransitionTimeBaseUnk_0x18 = DVar1 - 0xc80;
            DAT_UIButtonDefinedData::instance.ButtonGmDataArray[0x165].stateTransitionTimeBaseUnk_0x18 = DVar1 - 0x640;
            DAT_UIButtonDefinedData::instance.ButtonGmDataArray[0x166].stateTransitionTimeBaseUnk_0x18 = DVar1;
            INT_00b95abc::instance = -1;
            DAT_UnknownGFXIndex::instance = 0;
            MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog,
                DAT_MenuModalComposition3::ptr)(UI::Enums::MMT_NONE, FALSE);
        }

    }
}
}
