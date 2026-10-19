#include "../../../Map.func.hpp"
#include "../TribesState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00522C50
        void TribesState::addRallyPoint(int section1016ID, short destinationX, short destinationY, int step)
        {
            this->tribes[section1016ID].rallyPointArray[step][0] = destinationX;
            this->tribes[section1016ID].rallyPointArray[step][1] = destinationY;
            this->tribes[section1016ID].rallyPointCount = (short)step + 1;
        }

    }
}
}
