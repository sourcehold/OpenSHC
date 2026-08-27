#include "../IO.func.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x0041A740
void IO::SwapInts(undefined4* param_1, undefined4* param_2)
{
    undefined4 uVar1;
    uVar1 = *param_1;
    *param_1 = *param_2;
    *param_2 = uVar1;
}

}
