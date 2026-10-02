#include "../../../Rendering.func.hpp"

#include "OpenSHC/Rendering/Bink/BinkControlClass.func.hpp"

namespace OpenSHC {
namespace Rendering {
    namespace Bink {

        /*
          WARNING: Enum "UnsortedBinkFlagInt": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00408EB0
        void BinkControlClass::stopAllBinkPlayback()
        {
            int binkObjIndex;
            binkObjIndex = 0;
            do {
                MACRO_CALL_MEMBER(OpenSHC::Rendering::Bink::BinkControlClass_Func::stopBinkPlayback, this)(
                    binkObjIndex);
                binkObjIndex = binkObjIndex + 1;
            } while (binkObjIndex < 2);
        }

    }
}
}
