#include "OpenSHC/UI.func.hpp"

#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {
namespace MenuItems {
namespace UnusedOldTitleMenu {

// FUNCTION: STRONGHOLDCRUSADER 0x00440420
void MenuItemActionHandler_UnusedOldTitleMenu_General(int param_1, ...)
{
    DAT_WindowAndDirectDraw::instance.postWindowCloseMessage = 1;
}

}
}
}
}
