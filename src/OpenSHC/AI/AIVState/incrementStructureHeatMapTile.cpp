#include "../AIVState.func.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace AI {

    // records a structure in the 5x5 tile heat map cell of the given tile coordinates
    // FUNCTION: STRONGHOLDCRUSADER 0x004ED3B0
    void AIVState::incrementStructureHeatMapTile(int x, int y)
    {
        if (DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SOLITARY) {
            return;
        }
        ++this->heatMaps[x / 5][y / 5].structureCount;
    }

}
}
