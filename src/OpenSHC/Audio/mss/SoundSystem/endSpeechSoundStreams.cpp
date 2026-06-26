#include "../SoundSystem.func.hpp"

#include "OpenSHC/Audio/mss/SoundFlagsAndLoopCountBitwiseFlagEnum.hpp"

#include "OpenSHC/Globals/DAT_SoundSystemState.hpp"

namespace OpenSHC {
namespace Audio {
    namespace MSS {

        // FUNCTION: STRONGHOLDCRUSADER 0x0047AA70
        void SoundSystem::endSpeechSoundStreams()
        {
            if (!this->waveOutOpenUnk_0x8) {
                return;
            }
            this->streamFlagsUnkAndLoopCount_0x34[1] = 1;
            this->streamFlagsUnkAndLoopCount_0x34[2] = 1;
            this->streamFlagsUnkAndLoopCount_0x34[3] &= ~FLAG_SOUND_UNINTERRUPTABLE;
            this->streamFlagsUnkAndLoopCount_0x34[4] &= ~FLAG_SOUND_UNINTERRUPTABLE;
            // Strangely only produces matching code if not using "this"
            MACRO_CALL_MEMBER(SoundSystem_Func::endSoundStream, DAT_SoundSystemState::ptr)(enums::SND_STR_SPEECH_1);
            MACRO_CALL_MEMBER(SoundSystem_Func::endSoundStream, DAT_SoundSystemState::ptr)(enums::SND_STR_SPEECH_2);
            for (int i = 1; i < 32; ++i) {
                AIL_end_sample(this->sample[i]);
                this->sampleSoundIndex_0x20c[i] = 0;
            }
            for (int i = 1; i < this->loadedSoundsCountAndIndex_0x316c; ++i) {
                this->soundFileCurrSampleNum_0x28c[i] = -1;
            }
        }

    }
}
}
