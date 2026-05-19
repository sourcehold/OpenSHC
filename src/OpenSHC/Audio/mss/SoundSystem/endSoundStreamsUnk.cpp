#include "OpenSHC/Audio/MSS/SoundSystem.hpp"

#include "OpenSHC/Audio/MSS/SoundSystem.func.hpp"

#include "OpenSHC/Audio/MSS/enums/SHC_SoundStream.hpp"

namespace OpenSHC {
namespace Audio {
    namespace MSS {

        // FUNCTION: STRONGHOLDCRUSADER 0x00467830
        void SoundSystem::endSoundStreamsUnk()
        {
            MACRO_CALL_MEMBER(SoundSystem_Func::endSoundStream, this)(enums::SND_STR_SPEECH_1);
            MACRO_CALL_MEMBER(SoundSystem_Func::endSoundStream, this)(enums::SND_STR_SPEECH_2);
        }

    }
}
}
