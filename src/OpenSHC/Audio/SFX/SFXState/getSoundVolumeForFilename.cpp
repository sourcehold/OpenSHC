#include "../SFXState.func.hpp"

#include "OpenSHC/OS.func.hpp"

namespace OpenSHC {
namespace Audio {
    namespace SFX {

        // FUNCTION: STRONGHOLDCRUSADER 0x0044A240
        int SFXState::getSoundVolumeForFilename(char* soundFileName)
        {
            for (int _runCounter = 0; _runCounter < this->DAT_SoundTotalCount; ++_runCounter) {
                if (!MACRO_CALL(OpenSHC::OS_Func::__stricmp)(
                        soundFileName, this->DAT_SoundFileNamePointersArray[_runCounter])) {
                    return this->DAT_SoundVolumeArray[_runCounter];
                }
            }
            return 100;
        }

    }
}
}
