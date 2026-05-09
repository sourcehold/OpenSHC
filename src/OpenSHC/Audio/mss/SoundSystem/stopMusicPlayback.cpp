#include "OpenSHC/Audio/MSS/SoundSystem.hpp"

#include "OpenSHC/Audio/MSS/SoundSystem.func.hpp"
#include "OpenSHC/Audio/MSS/enums/SHC_SoundStream.hpp"

// FUNCTION: STRONGHOLDCRUSADER 0x00467810
void OpenSHC::Audio::MSS::SoundSystem::stopMusicPlayback()
{
    MACRO_CALL_MEMBER(OpenSHC::Audio::MSS::SoundSystem_Func::endSoundStream, this)(enums::SND_STR_MUSIC);
    this->mbr_0x154 = 0;
    this->sec_Section1055_0x3274 = 0;
}
