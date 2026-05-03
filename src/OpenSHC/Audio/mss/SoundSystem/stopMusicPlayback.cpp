#include "OpenSHC/Audio/mss/SoundSystem.hpp"

#include "OpenSHC/Audio/mss/SoundSystem.func.hpp"
#include "OpenSHC/Audio/mss/_enums/SHC_SoundStream.hpp"

// FUNCTION: STRONGHOLDCRUSADER 0x00467810
void OpenSHC::Audio::mss::SoundSystem::stopMusicPlayback()
{
    MACRO_CALL_MEMBER(OpenSHC::Audio::mss::SoundSystem_Func::endSoundStream, this)(_enums::SND_STR_MUSIC);
    this->mbr_0x154 = 0;
    this->sec_Section1055_0x3274 = 0;
}
