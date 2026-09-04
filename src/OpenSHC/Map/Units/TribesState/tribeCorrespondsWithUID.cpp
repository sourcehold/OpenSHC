#include "OpenSHC/Map/Units/TribesState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00522360
        uint TribesState::tribeCorrespondsWithUID(int tribeID, uint tribeUID)
        {
            if (tribeUID == 0) {
                return 0;
            }
            return this->tribes[tribeID].uid == tribeUID;
        }

    }
}
}
