#include "OpenSHC/Map/MapPropertiesState.func.hpp"
#include "OpenSHC/UI.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_ButtonUnknownZero.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"

namespace OpenSHC {

using OpenSHC::WindowsHelper::Enums::BOOLEnum;

/*
  WARNING: Enum "MappersEnum": Some values do not have unique names
 */

/*
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */

// FUNCTION: STRONGHOLDCRUSADER 0x004668F0
void UI::MenuItemRenderFunction_BuildMenu_BuildingIcons(int param_1, ...)

{
    BOOLEnum BVar1;

    BVar1 = MACRO_CALL_MEMBER(OpenSHC::Map::MapPropertiesState_Func::isMapperAvailable, DAT_MapPropertiesState::ptr)(
        (MappersEnum)param_1);
    if (BVar1 != FALSE) {
        MACRO_CALL(OpenSHC::UI_Func::
                MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
        DAT_ButtonUnknownZero::instance = 0;
        return;
    }
    DAT_ButtonUnknownZero::instance = 1;
    return;
}

}
