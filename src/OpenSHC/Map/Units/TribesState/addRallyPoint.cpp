#include "../TribesState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00522C50
        void TribesState::addRallyPoint(int tribeID, short destinationX, short destinationY, int step)
        {
            this->tribes[tribeID].rallyPointArray[step][0] = destinationX;
            this->tribes[tribeID].rallyPointArray[step][1] = destinationY;
            this->tribes[tribeID].rallyPointCount = step + 1;
        }

    }
}
}
