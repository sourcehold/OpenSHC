#include "OpenSHC/Map/Units/TribesState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00523730
        void TribesState::markTribeAsAnimalTribe(int param_1) { this->tribes[param_1].unkIsAnimalTribe = 1; }

    }
}
}
