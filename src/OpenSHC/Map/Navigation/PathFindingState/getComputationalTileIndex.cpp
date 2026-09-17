#include "OpenSHC/Map/Navigation/PathFindingState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        // FUNCTION: STRONGHOLDCRUSADER 0x00496E20
        undefined4 PathFindingState::getComputationalTileIndex() { return this->searchQueue.writeIndex; }

    } // namespace Navigation
} // namespace Map
} // namespace OpenSHC
