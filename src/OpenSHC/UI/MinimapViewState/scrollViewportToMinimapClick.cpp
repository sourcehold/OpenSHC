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

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      Converts the current mouse screen position into viewport coordinates using the minimap's   position, scale
      factors, and map offsets, then calls setViewportBasedOnMapSize to scroll the main   view. Skipped if in build menu
      with soldiers tab active, shift-related state is 1, or right mouse   button is held.      renamed by: Claude
      Sonnet 4.6
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004B5110
    void MinimapViewState::scrollViewportToMinimapClick()
    {
        if ((DAT_GameCore::instance.currentMenuViewType == OpenSHC::UI::Enums::MVT_BUILD_MENU)
            && (((DAT_GameCore::instance.activeMenuTab.buildMenuTab == OpenSHC::UI::Enums::BMTT_SOLDIERS
                     || (DAT_TileMapState::instance.shiftRelated0or3 == 1))
                && (DAT_MouseState::instance.rightClickState == FALSE)))) {}
        DAT_ViewportRenderState::instance.viewportState.viewportX
            = ((((DAT_MouseState::instance.screenSpaceX - this->x) / this->widthFactor) * this->oneOrTwo
                   - (DAT_ViewportRenderState::instance.viewportState.viewportHeight + -5) / 2)
                  + this->field5_0x14)
            * 0x20;
        DAT_ViewportRenderState::instance.viewportState.viewportY
            = ((((DAT_MouseState::instance.screenSpaceY - this->y) / this->heightFactor) * this->oneOrTwo
                   - DAT_ViewportRenderState::instance.viewportState.viewportWidth / 2)
                  + this->field4_0x10)
            * 8;
        MACRO_CALL_MEMBER(
            OpenSHC::Rendering::ViewportRenderState_Func::setViewportBasedOnMapSize, DAT_ViewportRenderState::ptr)();
    }

}
}
