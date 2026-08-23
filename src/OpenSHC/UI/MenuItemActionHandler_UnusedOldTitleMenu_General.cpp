#include "OpenSHC/UI.func.hpp"

#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x00440420
void UI::MenuItemActionHandler_UnusedOldTitleMenu_General(int param_1, va_list args)
{
    DAT_WindowAndDirectDraw::instance.postWindowCloseMessage = 1;
}

}
