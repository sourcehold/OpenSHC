#include "OpenSHC/UI.func.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x00434260
void __cdecl UI::MenuItemActionHandler_General_Unknown2(int param_1, ...)
{
    DAT_GameCore::instance.field12_0x30 = param_1;
}

}
