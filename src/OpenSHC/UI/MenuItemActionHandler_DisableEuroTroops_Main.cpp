#include "OpenSHC/UI.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"

namespace OpenSHC {

using OpenSHC::UI::Enums::MenuModalType;
using OpenSHC::WindowsHelper::Enums::BOOLEnum;

/*
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */

// FUNCTION: STRONGHOLDCRUSADER 0x004BB540
void UI::MenuItemActionHandler_DisableEuroTroops_Main(int param_1, ...)

{
    if ((uint)param_1 < 8) {
        DAT_MapPropertiesState::instance.SEC_MercRecruitable[param_1 + -7]
            = DAT_MapPropertiesState::instance.SEC_MercRecruitable[param_1 + -7] ^ 1;
        return;
    }
    if (param_1 == -3) {
        MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog, DAT_MenuModalComposition1::ptr)(
            OpenSHC::UI::Enums::MMT_BUILDING_AVAILABILITY, FALSE);
    }
    return;
}

}
