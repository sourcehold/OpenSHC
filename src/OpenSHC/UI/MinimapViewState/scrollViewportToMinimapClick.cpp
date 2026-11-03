#include "../MinimapViewState.func.hpp"

#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"
#include "OpenSHC/UI/Enums/BuildMenuTabType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::UI::Enums::BuildMenuTabType;
    using OpenSHC::UI::Enums::MenuViewType;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // Scrolls the main view to the minimap point under the mouse. Skipped in the build menu when its soldiers tab is
    // open or the shift-related state is 1, unless the right button is down.
    // FUNCTION: STRONGHOLDCRUSADER 0x004B5110
    void MinimapViewState::scrollViewportToMinimapClick()
    {
        if (DAT_GameCore::instance.currentMenuViewType == OpenSHC::UI::Enums::MVT_BUILD_MENU
            && (DAT_GameCore::instance.activeMenuTab.buildMenuTab == OpenSHC::UI::Enums::BMTT_SOLDIERS
                || DAT_TileMapState::instance.shiftRelated0or3 == 1)
            && DAT_MouseState::instance.rightClickState == FALSE) {
            return;
        }
        int const mouseY = DAT_MouseState::instance.screenSpaceY - this->y;
        DAT_ViewportRenderState::instance.viewportState.viewportX
            = ((DAT_MouseState::instance.screenSpaceX - this->x) / this->widthFactor * this->oneOrTwo
                  - (DAT_ViewportRenderState::instance.viewportState.viewportHeight - 5) / 2 + this->tileOffsetX)
            * 32;
        DAT_ViewportRenderState::instance.viewportState.viewportY
            = (mouseY / this->heightFactor * this->oneOrTwo
                  - DAT_ViewportRenderState::instance.viewportState.viewportWidth / 2 + this->tileOffsetY)
            * 8;
        MACRO_CALL_MEMBER(
            OpenSHC::Rendering::ViewportRenderState_Func::setViewportBasedOnMapSize, DAT_ViewportRenderState::ptr)();
    }

}
}
