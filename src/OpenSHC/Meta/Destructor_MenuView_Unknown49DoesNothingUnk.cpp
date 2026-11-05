#include "../Meta.func.hpp"

#include "OpenSHC/Global.func.hpp"

#include "OpenSHC/Globals/MenuView_Unknown49DoesNothingUnk.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x0059CDF0
void Meta::Destructor_MenuView_Unknown49DoesNothingUnk()
{
    ((void(__fastcall*)(MenuView*))MACRO_CALL(Global_Func::DoNothing))(MenuView_Unknown49DoesNothingUnk::ptr);
}

}
