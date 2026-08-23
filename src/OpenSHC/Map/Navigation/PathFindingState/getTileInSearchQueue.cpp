#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        // FUNCTION: STRONGHOLDCRUSADER 0x00496E30
        int PathFindingState::getTileInSearchQueue(int index) { return this->searchQueue.tilesQueue[index]; }

    }
}
}
