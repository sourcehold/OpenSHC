#include "../MinimapViewState.func.hpp"

#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MinimapViewState.func.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004B7600
    void MinimapViewState::renderMiniMapForSaving(int param_1, int param_2, int param_3, int param_4)
    {
        int iVar3;
        int iVar4;
        int iVar1 = 400 - DAT_TileMapState::instance.mapSize;
        if (iVar1 == 400) {
            iVar1 = 0;
        }
        int iVar2 = ((iVar1 / 2) / 2 + 1) * 0x20;
        iVar2 = (iVar2 / 32) + (DAT_ViewportRenderState::instance.viewportState.viewportHeight + -5) / 2;
        iVar1 = (iVar1 / 2) * 8 + 8;
        iVar1 = (iVar1 / 8) + DAT_ViewportRenderState::instance.viewportState.viewportWidth / 2;
        MACRO_CALL(OS_Func::_memset)(this->loadedMiniMap, 0, 80000);
        if (DAT_TileMapState::instance.mapSize < 0xc9) {
            MACRO_CALL_MEMBER(UI::MinimapViewState_Func::drawMinimap, this)(
                param_1, param_2, param_3, param_4, 5, iVar2, iVar1, 4, 2, 1);
            iVar4 = 2;
            iVar3 = 4;
        } else {
            MACRO_CALL_MEMBER(UI::MinimapViewState_Func::drawMinimap, this)(
                param_1, param_2, param_3, param_4, 5, iVar2, iVar1, 2, 1, 1);
            iVar4 = 1;
            iVar3 = 2;
        }
        MACRO_CALL_MEMBER(UI::MinimapViewState_Func::locatePlayerKeepPositionsOnMinimap, this)(4, iVar3, iVar4);
        this->lastRenderedXOffset = iVar2;
        this->lastRenderedYOffset = iVar1;
        this->needsRedraw = 1;
        this->field3_0xc = 0;
    }

}
}
