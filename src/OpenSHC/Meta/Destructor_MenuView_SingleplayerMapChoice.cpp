#include "../Meta.func.hpp"

#include "OpenSHC/Global.func.hpp"

#include "OpenSHC/Globals/MenuView_SingleplayerMapChoice.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x0059CDE0
void Meta::Destructor_MenuView_SingleplayerMapChoice()
{
    ((void(__fastcall*)(MenuView*))MACRO_CALL(Global_Func::DoNothing))(MenuView_SingleplayerMapChoice::ptr);
}

}
