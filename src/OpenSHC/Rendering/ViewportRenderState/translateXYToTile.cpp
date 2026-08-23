#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"

namespace OpenSHC {
namespace Rendering {

    // FUNCTION: STRONGHOLDCRUSADER 0x00401040
    int ViewportRenderState::translateXYToTile(int x, int y) { return this->translationMatrix[y].addXgetTile + x; }

}
}
