#include "../DisplayElements.func.hpp"

#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/UI/Enums/BuildingsAndStatusMenuTabType.hpp"
#include "OpenSHC/UI/Enums/DisplayElementPositionModifier.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_PointerToDisplayElementStackTop.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004AF700
    void DisplayElements::RenderDisplayElementsUnk()
    {
        DWORD const now = timeGetTime();
        for (DisplayElement* displayElement = DAT_PointerToDisplayElementStackTop::instance; displayElement != NULL;
            displayElement = displayElement->nextDisplayElement_0x20) {
            if (displayElement->elementStateUnk_0xc != 0) {
                int xPos = displayElement->x_0x0 + DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetX;
                int yPos = displayElement->y_0x4 + DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetY;
                DisplayElementPositionModifierInt const yModifier = displayElement->positionModifier_0x1c
                    & (OpenSHC::UI::Enums::DEPM_TOWARDS_MID_Y | OpenSHC::UI::Enums::DEPM_RESOLUTION_Y);
                switch (yModifier) {
                case OpenSHC::UI::Enums::DEPM_RESOLUTION_Y:
                    break;
                case OpenSHC::UI::Enums::DEPM_TOWARDS_MID_Y: {
                    yPos = yPos - 600 + DAT_WindowAndDirectDraw::instance.resolutionY;
                    if (((DAT_GameCore::instance.currentMenuViewType == OpenSHC::UI::Enums::MVT_BUILD_MENU)
                            || (DAT_GameCore::instance.currentMenuViewType
                                == OpenSHC::UI::Enums::MVT_MAP_EDITOR_LANDSCAPING))
                        && (DAT_GameCore::instance.activeMenuTab.tabType
                                == OpenSHC::UI::Enums::BASMTT_SIEGETENT_SIEGETOWER
                            || (DAT_GameCore::instance.activeMenuTab.tabType
                                == OpenSHC::UI::Enums::BASMTT_SIEGETENT_SHIELD))) {
                        yPos += 128;
                    }
                    if (DAT_GameCore::instance.currentMenuViewType
                        == OpenSHC::UI::Enums::MVT_BUILDING_AND_STATUS_MENU) {
                        yPos -= 20;
                    }
                    break;
                }
                default:
                    yPos += DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight;
                }
                DisplayElementPositionModifierInt const xModifier = displayElement->positionModifier_0x1c
                    & (OpenSHC::UI::Enums::DEPM_TOWARDS_MID_X | OpenSHC::UI::Enums::DEPM_RESOLUTION_X);
                if (xModifier != OpenSHC::UI::Enums::DEPM_RESOLUTION_X) {
                    if (xModifier != OpenSHC::UI::Enums::DEPM_TOWARDS_MID_X) {
                        xPos += DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth;
                    } else {
                        xPos = xPos - 800 + DAT_WindowAndDirectDraw::instance.resolutionX;
                    }
                }
                DAT_TextManagerObject::instance.textSurfaceTarget = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                (*displayElement->renderFunction_0x18)(xPos, yPos, displayElement->elementStateUnk_0xc);
                DAT_TextManagerObject::instance.textSurfaceTarget = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                if (displayElement->displayDuration_0x14 >= 0
                    && (int)(now - displayElement->activationTime_0x10) > displayElement->displayDuration_0x14) {
                    displayElement->elementStateUnk_0xc = 0;
                }
            }
        }
    }

}
}
