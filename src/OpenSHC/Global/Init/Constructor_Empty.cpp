#include "../../Global.func.hpp"
#include "../Init.func.hpp"

namespace OpenSHC {
namespace Global {

    /*
      The original is `mov eax, ecx; ret`: it returns the incoming ecx unchanged, which a
      __cdecl free function cannot name in C++, so the single move is written out directly.
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00467F50
#pragma warning(push)
#pragma warning(disable : 4716) // must return a value
    void* Init::Constructor_Empty()
    {
        __asm { mov eax, ecx }
    }
#pragma warning(pop)

}
}
