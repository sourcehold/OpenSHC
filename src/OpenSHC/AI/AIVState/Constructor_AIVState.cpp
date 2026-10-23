#include "../AIVState.func.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004F13E0
    AIVState* AIVState::Constructor_AIVState()
    {
        MACRO_CALL_MEMBER(AIVState_Func::wipeAIVsAndHeatMaps, this)();
        return this;
    }

}
}
