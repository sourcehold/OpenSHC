#include "OpenSHC/Global.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Random/RNG.func.hpp"
#include "OpenSHC/Random/RNG.hpp"

namespace OpenSHC {
namespace Random {

    // FUNCTION: STRONGHOLDCRUSADER 0x0046a760
    void RNG::populateRNG1040()

    {
        int iVar1;
        int iVar2;
        short* _pRandomNumber;

        MACRO_CALL(OpenSHC::Global_Func::SetRNGSeed)(this->seed);
        this->index2 = 0;
        this->index1 = 0;
        _pRandomNumber = &this->randomNumbers[0];
        iVar2 = 20000;
        do {
            iVar1 = MACRO_CALL(OpenSHC::OS_Func::_rand)();
            *_pRandomNumber = (short)iVar1;
            _pRandomNumber = _pRandomNumber + 1;
            iVar2 = iVar2 + -1;
        } while (iVar2 != 0);

        this->currentNumber2 = this->randomNumbers[this->index2];
        this->index2 = this->index2 + 1;

        this->currentNumber1 = this->randomNumbers[this->index1];
        this->index1 = this->index1 + 1;

        return;
    }

}
}
