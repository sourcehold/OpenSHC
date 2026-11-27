#include "../Init.func.hpp"

#include "OpenSHC/UI/HoveredState.func.hpp"

#include "OpenSHC/Globals/DAT_HoveredState.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059CCA0
    void Init::Constructor_HoveredState()
    {
        MACRO_CALL_MEMBER(UI::HoveredState_Func::Constructor_HoveredState, DAT_HoveredState::ptr)();
    }

}
}
