#include "../SoundSystem.func.hpp"

#include "OpenSHC/Globals/DAT_00b95954.hpp"
#include "OpenSHC/Globals/DAT_SFXDefinedData.hpp"

namespace OpenSHC {
namespace Audio {
    namespace MSS {

        // FUNCTION: STRONGHOLDCRUSADER 0x0047A5E0
        void SoundSystem::playDarMehqOrGlory()
        {
            if (*DAT_00b95954::ptr == 1) {
                MACRO_CALL_MEMBER(SoundSystem_Func::openSound, this)(
                    DAT_SFXDefinedData::ptr->DAT_SFX_Pointers[0x26].musicFile);
                return;
            }
            if (this->sec_Section1055_0x3274 != 0xf) {
                MACRO_CALL_MEMBER(SoundSystem_Func::setupVolumeAndSoundID, this)(DE::SHCDE::MUSIC_TUNE_OFF);
                return;
            }
            MACRO_CALL_MEMBER(SoundSystem_Func::openSound, this)(
                DAT_SFXDefinedData::ptr->DAT_SFX_Pointers[0x10].musicFile);
            this->sec_Section1055_0x3274 = 0;
        }

    }
}
}
