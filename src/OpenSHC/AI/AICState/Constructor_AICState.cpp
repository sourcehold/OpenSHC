#include "OpenSHC/AI/AICState.func.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004D3940
    AICState* AICState::Constructor_AICState()
    {
        MACRO_CALL_MEMBER(AICState_Func::setInitialAIC, this)();
        this->aiTauntResponseTimeWindow = 0;
        return this;
    }
}
}
