#include "../SFXState.func.hpp"

#include "OpenSHC/OS.func.hpp"

namespace OpenSHC {
namespace Audio {
    namespace SFX {

        // FUNCTION: STRONGHOLDCRUSADER 0x00449B20
        void SFXState::freeMemoryAt()
        {
            if (!this->DAT_SoundFileNameArrayMemoryPointer) {
                return;
            }
            MACRO_CALL(OS_Func::_free_base)(this->DAT_SoundFileNameArrayMemoryPointer);
        }

    }
}
}
