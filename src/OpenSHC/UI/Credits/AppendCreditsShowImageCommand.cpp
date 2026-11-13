#include "OpenSHC/UI/Credits.func.hpp"

#include "OpenSHC/Globals/DAT_ARRAY_00eb9b68.hpp"
#include "OpenSHC/Globals/DAT_UnknownBinkCount.hpp"

namespace OpenSHC {
namespace UI {
    namespace Credits {

        // FUNCTION: STRONGHOLDCRUSADER 0x004DA9F0
        void AppendCreditsShowImageCommand(
            int command, int gfxIndex, int x, int y, int width, int height, undefined4 unused, int field10)
        {
            if (DAT_UnknownBinkCount::instance < 288 && gfxIndex >= 0 && command == 41) {
                DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].commandType = 41;
                DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].soundStream = gfxIndex;
                DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].field_0x38 = 0;
                DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].x = x;
                DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].y = y;
                DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].field_0x28 = field10;
                DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].field_0x1c = 0;
                DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].width = width;
                DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].height = height;
                DAT_UnknownBinkCount::instance += 1;
            }
        }

    }
}
}
