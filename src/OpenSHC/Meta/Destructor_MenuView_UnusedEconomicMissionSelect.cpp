#include "../Meta.func.hpp"

#include "OpenSHC/Global.func.hpp"

#include "OpenSHC/Globals/MenuView_UnusedEconomicMissionSelect.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x0059CD60
void Meta::Destructor_MenuView_UnusedEconomicMissionSelect()
{
    ((void(__fastcall*)(MenuView*))MACRO_CALL(Global_Func::DoNothing))(MenuView_UnusedEconomicMissionSelect::ptr);
}

}
