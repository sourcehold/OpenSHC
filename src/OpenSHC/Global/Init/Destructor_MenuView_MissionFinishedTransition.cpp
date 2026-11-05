#include "../Init.func.hpp"

#include "OpenSHC/Global.func.hpp"

#include "OpenSHC/Globals/MenuView_MissionFinishedTransition.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059CED0
    void Init::Destructor_MenuView_MissionFinishedTransition()
    {
        ((void(__fastcall*)(MenuView*))MACRO_CALL(Global_Func::DoNothing))(MenuView_MissionFinishedTransition::ptr);
    }

}
}
