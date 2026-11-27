#include "../Meta.func.hpp"

#include "OpenSHC/Global.func.hpp"

#include "OpenSHC/Globals/MenuView_UnusedDemoBuyItScreen.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x0059CF70
void Meta::Destructor_MenuView_UnusedDemoBuyItScreen()
{
    ((void(__fastcall*)(MenuView*))MACRO_CALL(Global_Func::DoNothing))(MenuView_UnusedDemoBuyItScreen::ptr);
}

}
