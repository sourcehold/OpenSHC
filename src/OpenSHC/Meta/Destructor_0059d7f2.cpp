#include "../Meta.func.hpp"

namespace OpenSHC {
namespace CrtStatics {
    void __fastcall destroyException(void* object);
}

// File scope gives MSVC the original absolute store to the exception object.
static void** const exceptionObject = reinterpret_cast<void**>(Address::SHC_3BB0A8C1_0x024275A8);
static void* const badAllocVtable = reinterpret_cast<void*>(Address::SHC_3BB0A8C1_0x005A59B0);

// FUNCTION: STRONGHOLDCRUSADER 0x0059D7F2
void Meta::Destructor_0059d7f2()
{
    *exceptionObject = badAllocVtable;
    CrtStatics::destroyException(exceptionObject);
}

} // namespace OpenSHC
