#include "OpenSHC/UI.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"

namespace OpenSHC {

using OpenSHC::UI::Enums::MenuModalType;
using OpenSHC::WindowsHelper::Enums::BOOLEnum;

/*
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */

// FUNCTION: STRONGHOLDCRUSADER 0x004B1090
void UI::MenuItemActionHandler_UnusedWinCondition_Options(int param_1, ...)

{
    if (param_1 < (int)DAT_MenuModalComposition1::instance.mbr_0x64) {
        DAT_MenuModalComposition1::instance.sliderValue = param_1;
        *DAT_MenuModalComposition1::instance.destination = param_1;
        MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog, DAT_MenuModalComposition1::ptr)(
            OpenSHC::UI::Enums::MMT_NONE, FALSE);
        if (DAT_MenuModalComposition1::instance.sliderCallbackFunction != (undefined*)0x0) {
            /*
              WARNING: Could not recover jumptable at 0x004b10c0. Too many branches
             */

            /*
              WARNING: Treating indirect jump as call
             */

            ((void (*)())DAT_MenuModalComposition1::instance.sliderCallbackFunction)();
            return;
        }
    }
    return;
}

}
