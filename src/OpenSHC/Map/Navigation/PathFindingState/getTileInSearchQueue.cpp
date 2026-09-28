#include "../PathFindingState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00496E30
        int PathFindingState::getTileInSearchQueue(int index) { return this->searchQueue.tilesQueue[index]; }

    }
}
}
