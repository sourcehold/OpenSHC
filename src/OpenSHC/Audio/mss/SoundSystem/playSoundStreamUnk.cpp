#include "../SoundSystem.func.hpp"

#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Audio/mss/SoundFlagsAndLoopCountBitwiseFlagEnum.hpp"

#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace Audio {
    namespace MSS {

        // FUNCTION: STRONGHOLDCRUSADER 0x0047B060
        void SoundSystem::playSoundStreamUnk(
            SHC_SoundStream sndStreamIndex, char* filename, SoundFlagsAndLoopCount flagsAndLoopCount)
        {
            if (!this->waveOutOpenUnk_0x8) {
                return;
            }

            if (flagsAndLoopCount & FLAG_SOUND_UNKNOWN_FLAG_2) {
                this->streamFlagsUnkAndLoopCount_0x34[sndStreamIndex] = 1;
            }
            MACRO_CALL_MEMBER(SoundSystem_Func::endSoundStream, this)(sndStreamIndex);

            if (!this->soundActiveUnk_0x0 || DAT_WindowAndDirectDraw::ptr->isNotProcessingInputEvents
                || !DAT_WindowAndDirectDraw::ptr->gameFocused || this->streamActiveUnk_0x20[sndStreamIndex]) {
                return;
            }

            if (sndStreamIndex == enums::SND_STR_MUSIC) {
                AIL_init_sample(this->musicSampleUnk_0x170);
                AIL_set_sample_type(this->musicSampleUnk_0x170, DIG_F_STEREO_16, 0);
                AIL_set_sample_playback_rate(this->musicSampleUnk_0x170, 22050);
                AIL_set_sample_pan(this->musicSampleUnk_0x170, 64);
                AIL_set_sample_volume(this->musicSampleUnk_0x170,
                    (this->streamVolume[sndStreamIndex] * this->streamFileVolumeNextUnk_0x48[sndStreamIndex]) / 100);
                this->streamFileVolumeCurrentUnk_0x5c[sndStreamIndex]
                    = this->streamFileVolumeNextUnk_0x48[sndStreamIndex];
                this->musicSampleFileHandleUnk_0x174 = MACRO_CALL(OS_Func::_ucrt_open)(filename, _O_BINARY, 0);
                this->streamFlagsUnkAndLoopCount_0x34[sndStreamIndex] = flagsAndLoopCount;
                this->mbr_0x188 = 0;
                if (this->musicSampleFileHandleUnk_0x174 == -1) {
                    return;
                }
                MACRO_CALL_MEMBER(SoundSystem_Func::playMusicUnk, this)();
                MACRO_CALL_MEMBER(SoundSystem_Func::playMusicUnk, this)();
                this->streamActiveUnk_0x20[sndStreamIndex] = true;
                return;
            }

            this->stream_0xc[sndStreamIndex] = AIL_open_stream(this->digSndDriver_0x4, filename, 0);
            if (!this->stream_0xc[sndStreamIndex]) {
                return;
            }

            this->streamActiveUnk_0x20[sndStreamIndex] = true;
            this->streamFlagsUnkAndLoopCount_0x34[sndStreamIndex] = flagsAndLoopCount;
            // "!sndStreamIndex" was required to get the full byte match. This might indicate that instead of using "0"
            // directly to refer to the first/music stream, the just negate the given stream index, which is always 0.
            // It might be a coincidence or the current re-implementation of this method lacks some other pattern, but
            // it works for now and could be something to consider should other behaviors like this show up.
            if ((flagsAndLoopCount & FLAG_SOUND_UNKNOWN_FLAG_1) && this->streamActiveUnk_0x20[!sndStreamIndex]) {
                AIL_set_sample_volume(this->musicSampleUnk_0x170,
                    this->streamVolume[!sndStreamIndex] * (this->streamFileVolumeNextUnk_0x48[!sndStreamIndex] / 2)
                        / 100);
                this->streamFileVolumeCurrentUnk_0x5c[!sndStreamIndex]
                    = this->streamFileVolumeNextUnk_0x48[!sndStreamIndex] / 2;
            }
            if (flagsAndLoopCount & (FLAG_SOUND_UNKNOWN_FLAG_2 | FLAG_SOUND_UNINTERRUPTABLE)) {
                flagsAndLoopCount = 1;
            }
            AIL_set_stream_volume(this->stream_0xc[sndStreamIndex],
                (this->streamVolume[sndStreamIndex] * this->streamFileVolumeNextUnk_0x48[sndStreamIndex]) / 100);
            this->streamFileVolumeCurrentUnk_0x5c[sndStreamIndex] = this->streamFileVolumeNextUnk_0x48[sndStreamIndex];
            AIL_set_stream_loop_count(
                this->stream_0xc[sndStreamIndex], flagsAndLoopCount & FLAG_SOUND_LOOP_COUNT_FIELD);
            AIL_start_stream(this->stream_0xc[sndStreamIndex]);
        }

    }
}
}
