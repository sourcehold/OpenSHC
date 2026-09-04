#include "OpenSHC/Map/LandscapeState.func.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004F2FB0
    uint LandscapeState::isTreeAliveAndMatchingUID(int treeID, int param_2)
    {
        if (this->trees[treeID].uid != param_2) {
            return FALSE;
        }
        return this->trees[treeID].zeroUpTo2 == 0;
    }

}
}
