#include "OpenSHC/Global.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Random/RNG.func.hpp"
#include "OpenSHC/Random/RNG.hpp"

namespace OpenSHC {
namespace Random {

    // FUNCTION: STRONGHOLDCRUSADER 0x0046a760
    void RNG::populateRNG1040()

    {

        MACRO_CALL(OpenSHC::Global_Func::SetRNGSeed)(this->seed);
        this->index2 = 0;
        this->index1 = 0;
        for (int i = 0; i < sizeof(this->randomNumbers) / sizeof(this->randomNumbers[0]); i++) {
            this->randomNumbers[i] = MACRO_CALL(OpenSHC::OS_Func::_rand)();
        }

        this->currentNumber2 = this->randomNumbers[this->index2];
        this->index2 += 1;

        this->currentNumber1 = this->randomNumbers[this->index1];
        this->index1 += 1;

        return;
    }

}
}
