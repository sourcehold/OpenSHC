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

        using OpenSHC::UI::Enums::MenuModalType;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00425500
        void HistoricCampaignSelect::MenuView_HistoricCampaignSelect_Prepare()
        {
            DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                DAT_TextureRenderCoreObject::ptr)("frontend_combat.tgx");
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                DAT_TextureRenderCoreObject::ptr)("frontend_combat2.tgx");
            MACRO_CALL(OpenSHC::UI::Helpers_Func::LoadTGX_shc_back)();
            DAT_UIButtonDefinedData::instance.ButtonGmDataArray[0x166].stateTransitionTimeBaseUnk_0x18 = timeGetTime();
            DAT_UIButtonDefinedData::instance.ButtonGmDataArray[0x163].stateTransitionTimeBaseUnk_0x18
                = DAT_UIButtonDefinedData::instance.ButtonGmDataArray[0x166].stateTransitionTimeBaseUnk_0x18 - 0x12c0;
            DAT_UIButtonDefinedData::instance.ButtonGmDataArray[0x165].stateTransitionTimeBaseUnk_0x18
                = DAT_UIButtonDefinedData::instance.ButtonGmDataArray[0x166].stateTransitionTimeBaseUnk_0x18 - 0x640;
            DAT_UIButtonDefinedData::instance.ButtonGmDataArray[0x164].stateTransitionTimeBaseUnk_0x18
                = DAT_UIButtonDefinedData::instance.ButtonGmDataArray[0x166].stateTransitionTimeBaseUnk_0x18 - 0xc80;
            INT_00b95abc::instance = -1;
            DAT_UnknownGFXIndex::instance = 0;
            MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                DAT_MenuModalComposition3::ptr)(OpenSHC::UI::Enums::MMT_NONE, FALSE);
        }

    }
}
}
