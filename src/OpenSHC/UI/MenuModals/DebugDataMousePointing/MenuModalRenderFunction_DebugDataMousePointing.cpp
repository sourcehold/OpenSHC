#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"
#include "OpenSHC/UI/MenuModals/DebugDataMousePointing.func.hpp"

#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuModals {
        namespace DebugDataMousePointing {

            // FUNCTION: STRONGHOLDCRUSADER 0x004AAAC0
            void MenuModalRenderFunction_DebugDataMousePointing(int x, int y, int width, int height)
            {
                MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::renderDebugDataMousePointing,
                    DAT_ViewportRenderState::ptr)(x, y, width, height);
            }

        }
    }
}
}
