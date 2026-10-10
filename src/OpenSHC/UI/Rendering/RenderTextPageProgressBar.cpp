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
        RECT sourceRect;
        RECT destinationRect;
        DWORD DVar2 = timeGetTime();
        int iVar5 = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight;
        int iVar1 = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth;
        uint uVar3 = DVar2 - DAT_ARRAY_00ed26d0::instance[0].x;
        if (1000000 < uVar3) {
            uVar3 = 0;
        }
        DAT_00ed2784::instance = uVar3 / 0x50;
        if (0x244 < DAT_00ed2784::instance) {
            DAT_00ed2784::instance = 0x244;
        }
        int left = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0x14;
        int iVar4 = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 0x14;
        sourceRect.right = 0x21c;
        sourceRect.left = (int)((ulonglong)DAT_00ed2784::instance << 0x20);
        sourceRect.top = (int)(((ulonglong)DAT_00ed2784::instance << 0x20) >> 0x20);
        sourceRect.bottom = DAT_00ed2784::instance + 0xdc;
        destinationRect.top = iVar4;
        destinationRect.left = left;
        destinationRect.right = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0x230;
        destinationRect.bottom = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 0xf0;
        MACRO_CALL_MEMBER(UI::Rendering::WindowAndDirectDraw_Func::bltMapGameSurfaceToScreenMenuSurface,
            DAT_WindowAndDirectDraw::ptr)(sourceRect, destinationRect);
        int iVar6 = 0;
        do {
            MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox, DAT_PencilRenderCore::ptr)(
                left, iVar4, iVar1 + 0x22f, iVar4 + 1, iVar6 + 2);
            iVar6 = iVar6 + 1;
            iVar4 = iVar4 + 2;
        } while (iVar6 < 0x1e);
        iVar4 = 0;
        iVar5 = iVar5 + 0xf0;
        do {
            MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox, DAT_PencilRenderCore::ptr)(
                left, iVar5, iVar1 + 0x22f, iVar5 + 1, iVar4 + 2);
            iVar4 = iVar4 + 1;
            iVar5 = iVar5 + -2;
        } while (iVar4 < 0x1e);
        return;
    }

}
}
