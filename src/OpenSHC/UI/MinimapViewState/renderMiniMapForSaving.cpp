#include "../MinimapViewState.func.hpp"

#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MinimapViewState.func.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace UI {

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004B7600
    void MinimapViewState::renderMiniMapForSaving(int param_1, int param_2, int param_3, int param_4)
    {
        int iVar1;
        int iVar2;
        int iVar3;
        int iVar4;
        iVar1 = 400 - DAT_TileMapState::instance.mapSize;
        if (iVar1 == 400) {
            iVar1 = 0;
        }
        iVar2 = ((iVar1 / 2) / 2 + 1) * 0x20;
        iVar2 = ((int)(iVar2 + (iVar2 >> 0x1f & 0x1fU)) >> 5)
            + (DAT_ViewportRenderState::instance.viewportState.viewportHeight + -5) / 2;
        iVar1 = (iVar1 / 2) * 8 + 8;
        iVar1 = ((int)(iVar1 + (iVar1 >> 0x1f & 7U)) >> 3)
            + DAT_ViewportRenderState::instance.viewportState.viewportWidth / 2;
        MACRO_CALL(OpenSHC::OS_Func::_memset)(this->loadedMiniMap, 0, 80000);
        if (DAT_TileMapState::instance.mapSize < 0xc9) {
            MACRO_CALL_MEMBER(OpenSHC::UI::MinimapViewState_Func::drawMinimap, this)(
                param_1, param_2, param_3, param_4, 5, iVar2, iVar1, 4, 2, 1);
            iVar4 = 2;
            iVar3 = 4;
        } else {
            MACRO_CALL_MEMBER(OpenSHC::UI::MinimapViewState_Func::drawMinimap, this)(
                param_1, param_2, param_3, param_4, 5, iVar2, iVar1, 2, 1, 1);
            iVar4 = 1;
            iVar3 = 2;
        }
        MACRO_CALL_MEMBER(OpenSHC::UI::MinimapViewState_Func::locatePlayerKeepPositionsOnMinimap, this)(
            4, iVar3, iVar4);
        this->field1_0x4 = iVar2;
        this->field2_0x8 = iVar1;
        this->field0_0x0 = 1;
        this->field3_0xc = 0;
    }

}
}
