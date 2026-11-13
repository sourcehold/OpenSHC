#include "OpenSHC/Map/MapPropertiesState.func.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004BA8B0
    void MapPropertiesState::removeEventAtIndex(int index)
    {
        this->eventsCount -= 1;
        for (int i = index; i < this->eventsCount; ++i) {
            memcpy(&this->scenarioEvents[i], &this->scenarioEvents[i + 1], sizeof(this->scenarioEvents[i]));
        }
    }

}
}
