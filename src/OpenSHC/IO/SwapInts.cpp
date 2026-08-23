#include "OpenSHC/IO.hpp"

namespace OpenSHC {
namespace IO {

    // FUNCTION: STRONGHOLDCRUSADER 0x0041a740
    void SwapInts(int* param_1, int* param_2)
    {
        int temp;
        temp = *param_1;
        *param_1 = *param_2;
        *param_2 = temp;
    }
}
}
