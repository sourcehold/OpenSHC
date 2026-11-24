#include "../OS.func.hpp"

namespace OpenSHC {
namespace CrtStatics {

    // FUNCTION: STRONGHOLDCRUSADER 0x00580CDF
    void __fastcall destroyException(void* object)
    {
        struct Exception {
            void* vtable;
            char* message;
            int ownsMessage;
        };
        Exception* ex = static_cast<Exception*>(object);
        ex->vtable = reinterpret_cast<void*>(Address::SHC_3BB0A8C1_0x005AC238);
        if (ex->ownsMessage)
            MACRO_CALL(OS_Func::_free_base)(ex->message);
    }

} // namespace CrtStatics
} // namespace OpenSHC
