#include "OpenSHC/Rendering/Bink/BinkControlClass.func.hpp"

namespace OpenSHC {
namespace Rendering {
    namespace Bink {

        // FUNCTION: STRONGHOLDCRUSADER 0x00408EB0
        void BinkControlClass::stopAllBinkPlayback()
        {
            int binkObjIndex = 0;
            do {
                MACRO_CALL_MEMBER(BinkControlClass_Func::stopBinkPlayback, this)(binkObjIndex);
                binkObjIndex = binkObjIndex + 1;
            } while (binkObjIndex < 2);
        }

    } // namespace Bink
} // namespace Rendering
} // namespace OpenSHC
