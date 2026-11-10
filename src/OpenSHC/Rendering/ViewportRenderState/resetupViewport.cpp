#include "../ViewportRenderState.func.hpp"

#include "OpenSHC/Rendering/Enums/ViewportConstants.hpp"
#include "OpenSHC/UI/Enums/BuildingsAndStatusMenuTabType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace Rendering {

    using OpenSHC::UI::Enums::BuildingsAndStatusMenuTabType;
    using OpenSHC::UI::Enums::MenuViewType;

    // FUNCTION: STRONGHOLDCRUSADER 0x004E7770
    void ViewportRenderState::resetupViewport(int zoomUnk)
    {
        int savedViewportY
            = this->viewportState.viewportY + this->viewportState.mbr_0xb0 * Enums::VC_TILE_ROW_PIXEL_HEIGHT;
        int savedViewportX = this->viewportState.mbr_0xac * Enums::VC_TILE_PIXEL_WIDTH + this->viewportState.viewportX;
        this->viewportState.isZoomedOutUnk = zoomUnk;

        if ((DAT_GameCore::instance.currentMenuViewType == OpenSHC::UI::Enums::MVT_BUILD_MENU
                || DAT_GameCore::instance.currentMenuViewType == OpenSHC::UI::Enums::MVT_MAP_EDITOR_LANDSCAPING)
            && (DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_SIEGETENT_SIEGETOWER
                || DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_SIEGETENT_SHIELD)) {
            MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::setupViewport, this)
            (0, 0, DAT_WindowAndDirectDraw::instance.resolutionX, DAT_WindowAndDirectDraw::instance.resolutionY);
        } else {
            MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::setupViewport, this)
            (0, 0, DAT_WindowAndDirectDraw::instance.resolutionX, DAT_WindowAndDirectDraw::instance.resolutionY - 128);
        }
        this->viewportState.viewportX = savedViewportX - this->viewportState.mbr_0xac * Enums::VC_TILE_PIXEL_WIDTH;
        this->viewportState.viewportY = savedViewportY - this->viewportState.mbr_0xb0 * Enums::VC_TILE_ROW_PIXEL_HEIGHT;
        MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::setViewportBasedOnMapSize, this)();
    }

}
}
