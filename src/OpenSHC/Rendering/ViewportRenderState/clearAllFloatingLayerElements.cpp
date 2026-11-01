#include "../ViewportRenderState.func.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Rendering {

    // FUNCTION: STRONGHOLDCRUSADER 0x004E6340
    void ViewportRenderState::clearAllFloatingLayerElements()
    {
        for (int floaterIndex = 1; floaterIndex < this->availableFloaterIndex; floaterIndex++) {
            DAT_TileMapState::instance.FloatingLayer[this->floatersArray[floaterIndex].tile] = 0;
            this->floatersArray[floaterIndex].id = 0;
        }
        this->availableFloaterIndex = 1;
    }

}
}
