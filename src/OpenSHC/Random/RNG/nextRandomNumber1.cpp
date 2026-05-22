
#include "OpenSHC/Random/RNG.hpp"

namespace OpenSHC {
namespace Random {

    // FUNCTION: STRONGHOLDCRUSADER 0x0046a800
    void RNG::nextRandomNumber1()
    {
        this->currentNumber1 = this->randomNumbers[this->index1];
        this->index1 += 1;
        if (sizeof(this->randomNumbers) / sizeof(this->randomNumbers[0]) <= this->index1) {
            this->index1 = 0;
        }
    }
}

}
