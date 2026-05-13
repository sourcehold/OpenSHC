
#include "OpenSHC/Random/RNG.hpp"

namespace OpenSHC {
namespace Random {

    // FUNCTION: STRONGHOLDCRUSADER 0x0046a7d0
    void RNG::nextRandomNumber2()
    {
        this->currentNumber2 = this->randomNumbers[this->index2];
        this->index2 = this->index2 + 1;
        if (20000 <= this->index2) {
            this->index2 = 0;
        }
        return;
    }
}

}
