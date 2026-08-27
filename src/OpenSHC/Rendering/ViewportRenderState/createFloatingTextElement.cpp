#include "../ViewportRenderState.func.hpp"

#include "OpenSHC/IO/Graphics/GmID.hpp"

namespace OpenSHC {
namespace Rendering {

    using OpenSHC::IO::Graphics::GmID;

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */

    // FUNCTION: STRONGHOLDCRUSADER 0x004E8CC0
    void ViewportRenderState::createFloatingTextElement(int param_1, int param_2, int param_3, int param_4, int param_5)

    {
        MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::createFloatingLayerElement, this)(
            OpenSHC::IO::Graphics::GID_FLOATS, param_1, param_2, param_3, param_4, param_5);
        return;
    }

}
}
