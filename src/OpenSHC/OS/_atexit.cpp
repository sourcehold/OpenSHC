#include "../OS.func.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x0057FA62
int __cdecl OS::_atexit(_atexit_t* callback)
{
    typedef _atexit_t* (__cdecl* OnExit)(_atexit_t*);
    return reinterpret_cast<OnExit>(&trampoline<Address::SHC_3BB0A8C1_0x0057FA26>)(callback) ? 0 : -1;
}

} // namespace OpenSHC
