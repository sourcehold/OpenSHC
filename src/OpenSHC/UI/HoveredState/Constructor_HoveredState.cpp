#include "../HoveredState.func.hpp"

#include "OpenSHC/UI/HoveredState.func.hpp"

namespace OpenSHC {
namespace UI {

    /*
      WARNING: Enum "MappersEnumInt": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x005119C0
    HoveredState* HoveredState::Constructor_HoveredState()
    {
        MACRO_CALL_MEMBER(OpenSHC::UI::HoveredState_Func::clearHoveredState, this)();
        return this;
    }

}
}
