#include "../ViewportRenderState.func.hpp"

namespace OpenSHC {
namespace Rendering {

    // FUNCTION: STRONGHOLDCRUSADER 0x004E8C90
    void ViewportRenderState::restoreFocusTile()
    {
        MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::focusOnTile, this)(this->field44_0x18b738);
    }

}
}
