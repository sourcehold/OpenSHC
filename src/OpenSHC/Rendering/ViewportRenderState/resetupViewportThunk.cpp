#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"

namespace OpenSHC {
namespace Rendering {

    // FUNCTION: STRONGHOLDCRUSADER 0x004E7800
    void ViewportRenderState::resetupViewportThunk()
    {
        MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::resetupViewport, this)(
            this->viewportState.isZoomedOutUnk);
    }

}
}
