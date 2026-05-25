
#include "../RNG.func.hpp"

namespace OpenSHC {
namespace Random {

    // FUNCTION: STRONGHOLDCRUSADER 0x0046A800
    void RNG::nextRandomNumber1()
    {
        this->currentNumber1 = this->randomNumbers[this->index1];
        this->index1 += 1;
        if (20000 <= this->index1) {
            this->index1 = 0;
        }
    }
}

}
