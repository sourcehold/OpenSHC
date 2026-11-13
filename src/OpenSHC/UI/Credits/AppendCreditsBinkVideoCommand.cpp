#include "OpenSHC/UI/Credits.func.hpp"

#include "OpenSHC/Globals/DAT_ARRAY_00eb9b68.hpp"
#include "OpenSHC/Globals/DAT_UnknownBinkCount.hpp"

namespace OpenSHC {
namespace UI {
    namespace Credits {

        // FUNCTION: STRONGHOLDCRUSADER 0x004DAA80
        void AppendCreditsBinkVideoCommand(
            undefined4 unused, char* fileName, int x, int y, int binkObjIndex, SoundFlagsAndLoopCount flagLoopCount)
        {
            if (DAT_UnknownBinkCount::instance < 288) {
                DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].commandType = 12;
                // the file name is stored inline, in the 32 bytes from binkFileName on
                strcpy((char*)&DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].binkFileName, fileName);
                DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].x = x;
                DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].y = y;
                DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].binkObjIndex = binkObjIndex;
                DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].flagLoopCount = flagLoopCount;
                DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].field_0x28 = 0;
                DAT_UnknownBinkCount::instance += 1;
            }
        }

    }
}
}
