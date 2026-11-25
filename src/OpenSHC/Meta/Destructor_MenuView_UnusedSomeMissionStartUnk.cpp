#include "../Meta.func.hpp"

#include "OpenSHC/Global.func.hpp"

#include "OpenSHC/Globals/MenuView_UnusedSomeMissionStartUnk.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x0059CD70
void Meta::Destructor_MenuView_UnusedSomeMissionStartUnk()
{
    ((void(__fastcall*)(MenuView*))MACRO_CALL(Global_Func::DoNothing))(MenuView_UnusedSomeMissionStartUnk::ptr);
}

}
