#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"

namespace OpenSHC {
namespace Rendering {

    // FUNCTION: STRONGHOLDCRUSADER 0x004092E0
    int ViewportRenderState::computeTileXOffset(int param_1, int param_2)
    {
        return param_1 - this->translationMatrix[param_2].addXgetTile;
    }

}
}
