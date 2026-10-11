#include "../TribesState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00523730
        void TribesState::markTribeAsAnimalTribe(int tribeID) { this->tribes[tribeID].unkIsAnimalTribe = 1; }

    }
}
}
