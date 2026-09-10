#include "OpenSHC/Rendering/Bink/BinkControlClass.func.hpp"

namespace OpenSHC {
namespace Rendering {
    namespace Bink {

        // FUNCTION: STRONGHOLDCRUSADER 0x00408EB0
        void BinkControlClass::stopAllBinkPlayback()
        {
            for (int binkObjIndex = 0; binkObjIndex < 2; binkObjIndex++)
                MACRO_CALL_MEMBER(BinkControlClass_Func::stopBinkPlayback, this)(binkObjIndex);
        }

    } // namespace Bink
} // namespace Rendering
} // namespace OpenSHC
