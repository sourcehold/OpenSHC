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
        if ((int)DAT_00ed2784::instance > 580) {
            DAT_00ed2784::instance = 580;
        }
        RECT sourceRect;
        sourceRect.right = 540;
        sourceRect.left = 0;
        sourceRect.top = DAT_00ed2784::instance;
        sourceRect.bottom = DAT_00ed2784::instance + 220;
        int const left = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 20;
        int const top = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 20;
        RECT destinationRect;
        destinationRect.top = top;
        destinationRect.left = left;
        destinationRect.right = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 560;
        destinationRect.bottom = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 240;
        MACRO_CALL_MEMBER(UI::Rendering::WindowAndDirectDraw_Func::bltMapGameSurfaceToScreenMenuSurface,
            DAT_WindowAndDirectDraw::ptr)(sourceRect, destinationRect);
        // fade the top and bottom edges of the page
        for (int i = 0; i < 30; ++i) {
            MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox, DAT_PencilRenderCore::ptr)(
                left, top + i * 2, left + 539, top + i * 2 + 1, i + 2);
        }
        for (int i = 0; i < 30; ++i) {
            MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox, DAT_PencilRenderCore::ptr)(
                left, top + 220 - i * 2, left + 539, top + 220 - i * 2 + 1, i + 2);
        }
    }

}
}
