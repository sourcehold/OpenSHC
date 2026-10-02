#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/UI/HoveredState.func.hpp"

#include "OpenSHC/Globals/DAT_HoveredState.hpp"

namespace OpenSHC {
namespace Global {

    /*
      WARNING: Enum "MappersEnumInt": Some values do not have unique names
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x0059CCA0
    void Init::Constructor_HoveredState()
    {
        MACRO_CALL_MEMBER(OpenSHC::UI::HoveredState_Func::Constructor_HoveredState, DAT_HoveredState::ptr)();
    }

}
}
