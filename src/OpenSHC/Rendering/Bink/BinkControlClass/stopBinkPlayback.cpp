#include "../../../Rendering.func.hpp"
#include "../BinkControlClass.func.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"

namespace OpenSHC {
namespace Rendering {
    namespace Bink {

        // FUNCTION: STRONGHOLDCRUSADER 0x00408E30
        void BinkControlClass::stopBinkPlayback(int binkObjIndex)
        {
            if (this->binkObjPtrArray[binkObjIndex] != NULL) {
                BinkClose(this->binkObjPtrArray[binkObjIndex]);
                this->binkObjPtrArray[binkObjIndex] = NULL;
                if (binkObjIndex == 1) {
                    DAT_GameCore::instance.isBinkVideoPlaying = 0;
                    DAT_GameCore::instance.countdown = binkObjIndex;
                }
            }
        }

    }
}
}
