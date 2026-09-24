#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"
#include "OpenSHC/UI.func.hpp"

#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x004AAAC0
void UI::MenuModalRenderFunction_DebugDataMousePointing(int x, int y, int width, int height)
{
    MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::renderDebugDataMousePointing,
        DAT_ViewportRenderState::ptr)(x, y, width, height);
}

}
