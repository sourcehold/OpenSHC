#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"

namespace OpenSHC {
namespace Rendering {

    // FUNCTION: STRONGHOLDCRUSADER 0x004E8CA0
    void ViewportRenderState::focusOnCoordinate(int x, int y)
    {
        MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::focusOnTile, this)(
            this->translationMatrix[y].addXgetTile + x);
    }

}
}
