#include "../MinimapViewState.func.hpp"

#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"

#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004B5280
    void MinimapViewState::renderMinimapPreview(int screenX, int screenY)
    {
        int iVar5;
        MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::setupPencilSurface, DAT_PencilRenderCore::ptr)();
        iVar5 = (int)DAT_PencilRenderCore::instance.surfacePtr
            + screenY * DAT_PencilRenderCore::instance.horizontalByteSize + screenX * 2;
        int iVar4 = 0x1a7f854;
        int iVar2 = 200;
        do {
            int iVar1 = 200;
            int iVar3 = 0;
            do {
                if (*(short*)(iVar4 + iVar3) != 0) {
                    *(short*)(iVar5 + iVar3) = *(short*)(iVar4 + iVar3);
                }
                iVar3 = iVar3 + 2;
                iVar1 = iVar1 + -1;
            } while (iVar1);
            iVar4 = iVar4 + 400;
            iVar5 = iVar5 + DAT_PencilRenderCore::instance.horizontalByteSize;
            iVar2 = iVar2 + -1;
        } while (iVar2);
    }

}
}
