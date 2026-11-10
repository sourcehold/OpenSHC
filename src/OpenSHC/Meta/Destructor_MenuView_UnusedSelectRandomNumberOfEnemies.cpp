#include "../Meta.func.hpp"

#include "OpenSHC/Global.func.hpp"

#include "OpenSHC/Globals/MenuView_UnusedSelectRandomNumberOfEnemies.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x0059CFD0
void Meta::Destructor_MenuView_UnusedSelectRandomNumberOfEnemies()
{
    ((void(__fastcall*)(MenuView*))MACRO_CALL(Global_Func::DoNothing))(MenuView_UnusedSelectRandomNumberOfEnemies::ptr);
}

}
