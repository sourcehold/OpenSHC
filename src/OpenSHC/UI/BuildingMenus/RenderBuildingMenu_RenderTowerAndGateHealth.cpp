#include "../BuildingMenus.func.hpp"

#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/COL_BLACK.hpp"
#include "OpenSHC/Globals/COL_LIME.hpp"
#include "OpenSHC/Globals/COL_RED.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/MSVC_SecurityCookie.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::Text::TextAlignment;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x0043E350
    void BuildingMenus::RenderBuildingMenu_RenderTowerAndGateHealth()
    {
        short sVar1;
        int local_20;
        ColorUnion local_18;
        char local_14[16];
        int iVar4 = DAT_MenuHandlerState::instance.y;
        int iVar2 = DAT_MenuHandlerState::instance.x;
        uint local_4 = MSVC_SecurityCookie::instance ^ (uint)&local_20;
        int local_1c = DAT_BuildingsState::instance.menuSelectedBuildingID * 0x32c;
        int iVar3 = (int)DAT_BuildingsState::instance.buildings[DAT_BuildingsState::instance.menuSelectedBuildingID]
                        .currentHealth;
        local_18.shortValue = COL_LIME::instance.shortValue;
        if ((iVar3 < 1)
            || (sVar1
                = DAT_BuildingsState::instance.buildings[DAT_BuildingsState::instance.menuSelectedBuildingID].maxHealth,
                sVar1 < 1)) {
            iVar3 = 0;
        } else {
            iVar3 = (iVar3 * 100) / (int)sVar1;
        }
        int left = DAT_MenuHandlerState::instance.x + 0x1d6;
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBorderBox, DAT_PencilRenderCore::ptr)(left,
            DAT_MenuHandlerState::instance.y + 0x1d3, DAT_MenuHandlerState::instance.x + 0x209,
            DAT_MenuHandlerState::instance.y + 0x1de, (ushort)(COL_BLACK::instance.shortValue));
        int bottom = iVar4 + 0x1dd;
        iVar4 = iVar4 + 0x1d4;
        local_20 = iVar2 + 0x1d7;
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox, DAT_PencilRenderCore::ptr)(
            local_20, iVar4, iVar2 + 0x208, bottom, (ushort)(COL_RED::instance.shortValue));
        if (1 < iVar3) {
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox, DAT_PencilRenderCore::ptr)(
                local_20, iVar4, (iVar3 >> 1) + left, bottom, local_18.shortValue);
        }
        MACRO_CALL(OpenSHC::OS_Func::_sprintf)(local_14, "%d/%d",
            (int)*(short*)((int)DAT_BuildingsState::instance.buildings[0].resources + local_1c + -0x14),
            (int)*(short*)((int)DAT_BuildingsState::instance.buildings[0].resources + local_1c + -0x12));
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(local_14,
            DAT_MenuHandlerState::instance.x + 0x1ef, DAT_MenuHandlerState::instance.y + 0x1e2,
            OpenSHC::Text::TTA_CENTER, 0, 0x12, FALSE, 0);
        ;
    }

}
}
