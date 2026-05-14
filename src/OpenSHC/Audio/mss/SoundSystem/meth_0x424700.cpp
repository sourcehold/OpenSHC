#include "OpenSHC/Audio/MSS/SoundSystem.hpp"

#include "OpenSHC/Audio/MSS/SoundSystem.func.hpp"

#include "OpenSHC/Audio/MSS/enums/SHC_SoundStream.hpp"

namespace OpenSHC {
namespace Audio {
    namespace MSS {

        // FUNCTION: STRONGHOLDCRUSADER 0x00424700
        void SoundSystem::meth_0x424700()
        {
            const UnkSoundFlagsAndLoopCount unkSoundFlagsAndLoopCount = {};
            this->streamFlagsUnkAndLoopCount_0x34[4] = unkSoundFlagsAndLoopCount;
            this->streamFlagsUnkAndLoopCount_0x34[3] = unkSoundFlagsAndLoopCount;
            MACRO_CALL_MEMBER(SoundSystem_Func::endSoundStream, this)(enums::SND_STR_SPEECH_1);
            MACRO_CALL_MEMBER(SoundSystem_Func::endSoundStream, this)(enums::SND_STR_SPEECH_2);
        }

    }
}
}
