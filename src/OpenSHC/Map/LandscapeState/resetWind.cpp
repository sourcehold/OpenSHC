#include "OpenSHC/Map/LandscapeState.func.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004F3700
    void LandscapeState::resetWind()
    {
        this->wind.value = 0;
        this->wind.index = 0;
        this->wind.countdown = 0;
        this->wind.field4_0x10 = 0;
        this->wind.counter = 0;
    }

}
}
