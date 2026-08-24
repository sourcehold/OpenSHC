#include "OpenSHC/Map/MapPropertiesState.func.hpp"
#include "OpenSHC/UI.func.hpp"

#include "OpenSHC/Globals/DAT_ButtonUnknownZero.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"

namespace OpenSHC {

/*
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */

// FUNCTION: STRONGHOLDCRUSADER 0x00466920
void UI::MenuItemRenderFunction_BuildMenu_BuildingSubcategoryButton(int param_1, ...)

{
    int iVar1;

    iVar1 = MACRO_CALL_MEMBER(
        OpenSHC::Map::MapPropertiesState_Func::isMercRecruitableForBuildingType, DAT_MapPropertiesState::ptr)(param_1);
    if (iVar1 != 0) {
        MACRO_CALL(OpenSHC::UI_Func::
                MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
        DAT_ButtonUnknownZero::instance = 0;
        return;
    }
    DAT_ButtonUnknownZero::instance = 1;
    return;
}

}
