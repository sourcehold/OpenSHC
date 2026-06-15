#include "../SoundSystem.func.hpp"
namespace OpenSHC {
namespace Audio {
    namespace MSS {

        // FUNCTION: STRONGHOLDCRUSADER 0x00467810
        void SoundSystem::stopMusicPlayback()
        {
            MACRO_CALL_MEMBER(OpenSHC::Audio::MSS::SoundSystem_Func::endSoundStream, this)(enums::SND_STR_MUSIC);
            this->mbr_0x154 = 0;
            this->sec_Section1055_0x3274 = 0;
        }

    }
}
}
