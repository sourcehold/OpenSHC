/**
  path: 'OpenSHC/Random/RNG.func.hpp'
*/

#include "OpenSHC/Random/RNG.hpp"
namespace OpenSHC {
namespace Random {
    namespace RNG_Func {

        MACRO_FUNCTION_RESOLVER(void (RNG::*)(), false, Address::SHC_3BB0A8C1_0x0046A740, &RNG::setTimeBasedSeed)
        setTimeBasedSeed;

        MACRO_FUNCTION_RESOLVER(void (RNG::*)(), false, Address::SHC_3BB0A8C1_0x0046A760, &RNG::populateRNG1040)
        populateRNG1040;

        MACRO_FUNCTION_RESOLVER(void (RNG::*)(), false, Address::SHC_3BB0A8C1_0x0046A7D0, &RNG::nextRandomNumber2)
        nextRandomNumber2;

        MACRO_FUNCTION_RESOLVER(void (RNG::*)(), false, Address::SHC_3BB0A8C1_0x0046A800, &RNG::nextRandomNumber1)
        nextRandomNumber1;

    } // namespace RNG_Func
} // namespace Random
} // namespace OpenSHC
