#include "OpenSHC/UI.func.hpp"

#include "OpenSHC/Globals/DAT_StopHandlingMenuItems.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x00440410
void UI::MenuItemFunction_General_Unknown(int param_1, va_list args) { DAT_StopHandlingMenuItems::instance = 0; }

}
