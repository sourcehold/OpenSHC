// disable deprecation warnings for strcpy
#pragma warning(disable : 4996)

#include "../SoundSystem.func.hpp"

#include "OpenSHC/OS.func.hpp"

#include "OpenSHC/Globals/DAT_SoundEffectsHelperData1.hpp"

namespace OpenSHC {
namespace Audio {
    namespace MSS {

        // FUNCTION: STRONGHOLDCRUSADER 0x0047B490
        void SoundSystem::openSound(char* filePath)
        {
            if (!this->waveOutOpenUnk_0x8) {
                return;
            }

            strcpy(this->currIdSoundFilenameUnk_0x84, filePath);
            if (!this->mbr_0x188) {
                DAT_SoundEffectsHelperData1::ptr->field14_0x54 = TRUE;
                if (this->musicFileHandle_0x178 != -1) {
                    MACRO_CALL(OS_Func::_ucrt_close)(this->musicFileHandle_0x178);
                }
                this->musicFileHandle_0x178 = MACRO_CALL(OS_Func::_ucrt_open)(filePath, _O_BINARY, 0);
                DAT_SoundEffectsHelperData1::ptr->field14_0x54 = FALSE;
                return;
            }

            MACRO_CALL_MEMBER(SoundSystem_Func::playMusicFileByName, this)(filePath);
        }

    }
}
}
