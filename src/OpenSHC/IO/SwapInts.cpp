#include "../IO.func.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x0041A740
void IO::SwapInts(int* param_1, int* param_2)
{
    int uVar1;
    uVar1 = *param_1;
    *param_1 = *param_2;
    *param_2 = uVar1;
}

}
