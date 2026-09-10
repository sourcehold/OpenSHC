#include "../BinkControlClass.func.hpp"

namespace OpenSHC {
namespace Rendering {
    namespace Bink {

        // FUNCTION: STRONGHOLDCRUSADER 0x00408E10
        void BinkControlClass::zeroBinkPtrAndLoadBinkSoundSystem(HDIGDRIVER drvrPtr)
        {
            this->binkObjPtrArray[0] = NULL;
            this->binkObjPtrArray[1] = NULL;
            BinkSetSoundSystem(BinkOpenMiles, (ulong)drvrPtr);
            return;
        }

    }
}
}
