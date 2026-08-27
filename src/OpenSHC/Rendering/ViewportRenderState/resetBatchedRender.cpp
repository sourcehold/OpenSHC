#include "../ViewportRenderState.func.hpp"

namespace OpenSHC {
namespace Rendering {

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */

    // FUNCTION: STRONGHOLDCRUSADER 0x004E2600
    int ViewportRenderState::resetBatchedRender()

    {
        this->unitBatchedRenderCounterUntil6 = 1;
        this->unitRender1 = 0;
        this->unitRender2 = 0;
        this->unitRender3 = 0;
        this->unitRender4 = 0;
        this->unitRender5 = 0;
        return 0;
    }

}
}
