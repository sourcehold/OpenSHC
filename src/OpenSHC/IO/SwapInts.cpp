#include "../IO.func.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x0041A740
void IO::SwapInts(int* first, int* second)
{
    int temp;
    temp = *first;
    *first = *second;
    *second = temp;
}

}
