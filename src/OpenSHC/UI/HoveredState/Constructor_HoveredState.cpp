#include "../HoveredState.func.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x005119C0
    HoveredState* HoveredState::Constructor_HoveredState()
    {
        MACRO_CALL_MEMBER(OpenSHC::UI::HoveredState_Func::clearHoveredState, this)();
        return this;
    }

}
}
