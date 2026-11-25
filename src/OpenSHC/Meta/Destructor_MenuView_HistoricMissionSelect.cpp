#include "../Meta.func.hpp"

#include "OpenSHC/Global.func.hpp"

#include "OpenSHC/Globals/MenuView_HistoricMissionSelect.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x0059CD50
void Meta::Destructor_MenuView_HistoricMissionSelect()
{
    ((void(__fastcall*)(MenuView*))MACRO_CALL(Global_Func::DoNothing))(MenuView_HistoricMissionSelect::ptr);
}

}
