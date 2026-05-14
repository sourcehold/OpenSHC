#include "OpenSHC/Audio/MSS/SoundSystem.hpp"

#include "OpenSHC/Audio/MSS/enums/AILStatus.hpp"
#include "OpenSHC/Audio/MSS/enums/SHC_SoundStream.hpp"

#include "OpenSHC/OS.func.hpp"

#include "OpenSHC/Globals/DAT_SoundEffectsHelperData1.hpp"

// NOTE:
// "UnkSoundFlagsAndLoopCount" might be a bitfield, maybe like this:
//      int loopCount : 16;
//      int reserved : 13;
//      int unknownFlag1 : 1;
//      int unknownFlag2 : 1;
//      int uninterruptable : 1; // ?
// In a test in the current file it compiled to "& 0x80000000" properly when using the specific field, but no idea if
// this works for multifield checks or assigns

namespace OpenSHC {
namespace Audio {
    namespace MSS {

        // FUNCTION: STRONGHOLDCRUSADER 0x004799A0
        void SoundSystem::endSoundStream(SHC_SoundStreamInt sndStreamIndex)
        {
            if (!this->waveOutOpenUnk_0x8) {
                return;
            }

            if (sndStreamIndex == enums::SND_STR_MUSIC) {
                this->streamActiveUnk_0x20[0] = 0;
                DAT_SoundEffectsHelperData1::ptr->field14_0x54 = true;
                if (this->musicSampleFileHandleUnk_0x174 != -1) {
                    AIL_end_sample(this->musicSampleUnk_0x170);
                    MACRO_CALL(OS_Func::_ucrt_close)(this->musicSampleFileHandleUnk_0x174);
                }
                if (this->musicFileHandle_0x178 != -1) {
                    MACRO_CALL(OS_Func::_ucrt_close)(this->musicFileHandle_0x178);
                }
                this->musicFileHandle_0x178 = -1;
                this->musicSampleFileHandleUnk_0x174 = -1;
                this->mbr_0x188 = 1;
                DAT_SoundEffectsHelperData1::ptr->field14_0x54 = false;
                this->sec_Section1055_0x3274 = 0;
                return;
            }

            if (!this->streamActiveUnk_0x20[sndStreamIndex]) {
                return;
            }

            // flag seems to indicate an "uninterruptable" stream; if it is set, a playing stream can not be ended
            if ((*reinterpret_cast<unsigned int*>(&this->streamFlagsUnkAndLoopCount_0x34[sndStreamIndex]) & 0x80000000)
                && (AIL_stream_status(this->stream_0xc[sndStreamIndex]) == SMP_PLAYING)) {
                return;
            }
            AIL_close_stream(this->stream_0xc[sndStreamIndex]);
            this->streamActiveUnk_0x20[sndStreamIndex] = 0;
            this->stream_0xc[sndStreamIndex] = 0x0;
        }

    }
}
}
