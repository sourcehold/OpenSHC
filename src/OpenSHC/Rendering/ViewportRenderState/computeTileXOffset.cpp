#include "../ViewportRenderState.func.hpp"

namespace OpenSHC {
namespace Rendering {

    // FUNCTION: STRONGHOLDCRUSADER 0x004092E0
    int ViewportRenderState::computeTileXOffset(int tile, int y)
    {
        return tile - this->translationMatrix[y].addXgetTile;
    }

}
}
