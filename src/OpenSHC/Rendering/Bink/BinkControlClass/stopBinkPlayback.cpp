#include "../../../Rendering.func.hpp"
#include "../BinkControlClass.func.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"

namespace OpenSHC {
namespace Rendering {
    namespace Bink {

        /*
          WARNING: Enum "UnsortedBinkFlagInt": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00408E30
        void BinkControlClass::stopBinkPlayback(int binkObjIndex)
        {
            if (this->binkObjPtrArray[binkObjIndex] != (HBINK)0x0) {
                BinkClose(this->binkObjPtrArray[binkObjIndex]);
                this->binkObjPtrArray[binkObjIndex] = (HBINK)0x0;
                if (binkObjIndex == 1) {
                    DAT_GameCore::instance.isBinkVideoPlaying = 0;
                    DAT_GameCore::instance.countdown = binkObjIndex;
                }
            }
        }

    }
}
}
