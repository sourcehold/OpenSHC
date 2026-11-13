#include "OpenSHC/UI/Credits.func.hpp"

#include "OpenSHC/Globals/DAT_ARRAY_00eb9b68.hpp"
#include "OpenSHC/Globals/DAT_UnknownBinkCount.hpp"

namespace OpenSHC {
namespace UI {
    namespace Credits {

        // FUNCTION: STRONGHOLDCRUSADER 0x004DAB80
        void AppendCreditsBinkVideoWithAudioCommand(char* fileName, int binkObjIndex, int noLoop, int volume)
        {
            if (DAT_UnknownBinkCount::instance < 288) {
                DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].commandType = 13;
                // the file name is stored inline, in the 32 bytes from binkFileName on
                strcpy((char*)&DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].binkFileName, fileName);
                DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].binkObjIndex = binkObjIndex;
                DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].flagLoopCount
                    = (SoundFlagsAndLoopCount)(1 - noLoop);
                DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].volume = volume;
                DAT_UnknownBinkCount::instance += 1;
            }
        }

    }
}
}
