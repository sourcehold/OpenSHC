#include "../BuildingMenus.func.hpp"

#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/IO/Helpers/ColorUnion.hpp"
#include "OpenSHC/Map/Buildings/Building.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/COL_BLACK.hpp"
#include "OpenSHC/Globals/COL_LIME.hpp"
#include "OpenSHC/Globals/COL_RED.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::IO::Helpers::ColorUnion;
    using OpenSHC::Text::TextAlignment;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x0043E350
    void BuildingMenus::RenderBuildingMenu_RenderTowerAndGateHealth()
    {
        int id = DAT_BuildingsState::instance.menuSelectedBuildingID;
        int health = DAT_BuildingsState::instance.buildings[id].currentHealth;
        ColorUnion healthColor;
        healthColor.shortValue = COL_LIME::instance.shortValue;
        int percent;
        if (health <= 0 || DAT_BuildingsState::instance.buildings[id].maxHealth <= 0) {
            percent = 0;
        } else {
            percent = health * 100 / DAT_BuildingsState::instance.buildings[id].maxHealth;
        }
        int left = DAT_MenuHandlerState::instance.x + 470;
        int top = DAT_MenuHandlerState::instance.y + 467;
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBorderBox, DAT_PencilRenderCore::ptr)(
            left, top, left + 51, top + 11, COL_BLACK::instance.shortValue);
        int innerBottom = top + 10;
        int innerTop = top + 1;
        int innerLeft = left + 1;
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox, DAT_PencilRenderCore::ptr)(
            innerLeft, innerTop, left + 50, innerBottom, COL_RED::instance.shortValue);
        if (percent >= 2) {
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox, DAT_PencilRenderCore::ptr)(
                innerLeft, innerTop, (percent >> 1) + left, innerBottom, healthColor.shortValue);
        }
        char text[16];
        MACRO_CALL(OpenSHC::OS_Func::_sprintf)(text, "%d/%d",
            (int)DAT_BuildingsState::instance.buildings[id].currentHealth,
            (int)DAT_BuildingsState::instance.buildings[id].maxHealth);
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(text,
            DAT_MenuHandlerState::instance.x + 495, DAT_MenuHandlerState::instance.y + 482, OpenSHC::Text::TTA_CENTER,
            0, 18, FALSE, 0);
    }

}
}
