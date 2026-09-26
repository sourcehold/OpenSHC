#include "../AIVState.func.hpp"

namespace OpenSHC {
namespace AI {

    // blocks building on the 5x5 heat map cell of the given tile for a while, e.g. after a building got destroyed
    // FUNCTION: STRONGHOLDCRUSADER 0x004EDCB0
    void AIVState::resetCountdownInHeatMap(int x, int y)
    {
        this->heatMaps[x / 5][y / 5].destructionBasedPlacementCooldown = 10;
    }

}
}
