#include "../Meta.func.hpp"

#include "OpenSHC/Global.func.hpp"

#include "OpenSHC/Globals/MenuView_NewMapMapsize.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x0059CE60
void Meta::Destructor_MenuView_NewMapMapsize()
{
    ((void(__fastcall*)(MenuView*))MACRO_CALL(Global_Func::DoNothing))(MenuView_NewMapMapsize::ptr);
}

}
