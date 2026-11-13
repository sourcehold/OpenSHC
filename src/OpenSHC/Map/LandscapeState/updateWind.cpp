#include "OpenSHC/Map/LandscapeState.func.hpp"

#include "OpenSHC/Globals/DAT_OrganismDefinedData.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004F3730
    void LandscapeState::updateWind()
    {
        this->wind.counter += 1;
        if (this->wind.counter >= 2) {
            this->wind.counter = 0;
            this->wind.countdown -= 1;
            this->wind.valueIs2 = 0;
            this->wind.valueIs1 = 0;
            if (this->wind.countdown < 0) {
                this->wind.countdown = 32;
                this->wind.value = DAT_OrganismDefinedData::instance.WindRelatedArray[this->wind.index];
                if (this->wind.value == 2) {
                    this->wind.valueIs2 = 1;
                } else if (this->wind.value == 1) {
                    this->wind.valueIs1 = 1;
                }
                this->wind.index += 1;
                if (this->wind.index >= 40) {
                    this->wind.index = 0;
                }
            }
        }
    }

}
}
