#include "../Rendering.func.hpp"

#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/UI/Rendering/WindowAndDirectDraw.func.hpp"

#include "OpenSHC/Globals/DAT_00ed2784.hpp"
#include "OpenSHC/Globals/DAT_ARRAY_00ed26d0.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004DAFB0
    void Rendering::RenderTextPageProgressBar()
    {
        DWORD elapsed = timeGetTime() - DAT_ARRAY_00ed26d0::instance[0].x;
        if (elapsed > 1000000) {
            elapsed = 0;
        }
        DAT_00ed2784::instance = elapsed / 80;
        if (DAT_00ed2784::instance > 580) {
            DAT_00ed2784::instance = 580;
        }
        RECT sourceRect;
        sourceRect.left = 0;
        sourceRect.right = 540;
        sourceRect.top = DAT_00ed2784::instance;
        sourceRect.bottom = DAT_00ed2784::instance + 220;
        RECT destinationRect;
        destinationRect.left = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 20;
        destinationRect.top = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 20;
        destinationRect.right = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 560;
        destinationRect.bottom = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 240;
        MACRO_CALL_MEMBER(UI::Rendering::WindowAndDirectDraw_Func::bltMapGameSurfaceToScreenMenuSurface,
            DAT_WindowAndDirectDraw::ptr)(sourceRect, destinationRect);
        // fade the top and bottom edges of the page
        for (int i = 0; i < 30; ++i) {
            MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox, DAT_PencilRenderCore::ptr)(
                destinationRect.left, destinationRect.top + i * 2, destinationRect.left + 539,
                destinationRect.top + i * 2 + 1, i + 2);
        }
        for (int i = 0; i < 30; ++i) {
            int const y = destinationRect.top + 220 - i * 2;
            MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox, DAT_PencilRenderCore::ptr)(
                destinationRect.left, y, destinationRect.left + 539, y + 1, i + 2);
        }
    }

}
}
