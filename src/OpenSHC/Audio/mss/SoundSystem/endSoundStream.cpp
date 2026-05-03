#include "OpenSHC/Audio/mss/SoundSystem.hpp"

#include "OpenSHC/Audio/mss/_enums/AILStatus.hpp"
#include "OpenSHC/Audio/mss/_enums/SHC_SoundStream.hpp"

#include "Mss32.h"

#include <io.h>

#include "OpenSHC/Globals/DAT_00df3844.hpp"

// TODO:
// - DAT_00df3844 did not exist before and is therefore wrongly sorted into the status file
// - the mss types need to use the mss32 header, not the Ghidra exported one (how to handle this?)
// - "_close" is treaded like an OFFSET function and reduces the score of reccmp
// - "UnkSoundFlagsAndLoopCount" plays not nice with any number-like operation, the more likely thing therefore are
// either a union, which allows to access the different parts separately, but this would likely compile to WORD
// operations, or a bitfield, maybe like this:
//      int loopCount : 16;
//      int reserved : 13;
//      int unknownFlag1 : 1;
//      int unknownFlag2 : 1;
//      int uninterruptable : 1; // ?
// In a test in the current file it compiled to "& 0x80000000" properly when using the specific field, but no idea if
// this works for multifield checks or assigns

// FUNCTION: STRONGHOLDCRUSADER 0x004799A0
void OpenSHC::Audio::mss::SoundSystem::endSoundStream(SHC_SoundStreamInt sndStreamIndex)
{
    if (!this->waveOutOpenUnk_0x8) {
        return;
    }

    if (sndStreamIndex == _enums::SND_STR_MUSIC) {
        this->streamActiveUnk_0x20[0] = 0;
        *DAT_00df3844::ptr = 1;
        if (this->musicSampleFileHandleUnk_0x174 != -1) {
            AIL_end_sample(this->musicSampleUnk_0x170);
            _close(this->musicSampleFileHandleUnk_0x174);
        }
        if (this->musicFileHandle_0x178 != -1) {
            _close(this->musicFileHandle_0x178);
        }
        this->musicFileHandle_0x178 = -1;
        this->musicSampleFileHandleUnk_0x174 = -1;
        this->mbr_0x188 = 1;
        *DAT_00df3844::ptr = 0;
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
