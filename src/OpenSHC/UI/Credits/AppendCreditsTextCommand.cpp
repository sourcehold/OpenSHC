#include "OpenSHC/UI/Credits.func.hpp"

#include "OpenSHC/Globals/DAT_ARRAY_00eb9b68.hpp"
#include "OpenSHC/Globals/DAT_NumberOfStoredMenuStrings.hpp"
#include "OpenSHC/Globals/DAT_UnknownBinkCount.hpp"

namespace OpenSHC {
namespace UI {
    namespace Credits {

        // FUNCTION: STRONGHOLDCRUSADER 0x004DAC30
        void AppendCreditsTextCommand(
            int command, int textIndex, int field6, int field13, int x, int y, int width, int field12)
        {
            if (DAT_UnknownBinkCount::instance < 288 && textIndex >= 0
                && textIndex < (int)DAT_NumberOfStoredMenuStrings::instance) {
                DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].commandType = command;
                DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].soundStream = textIndex;
                DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].field_0x18 = field6;
                DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].x = x;
                DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].y = y;
                DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].width = width;
                DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].field_0x30 = field12;
                DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].field_0x1c = 0;
                DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].field_0x34 = field13;
                if (command == 15) {
                    DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].field_0x1c = 1;
                } else if (command == 16) {
                    DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].field_0x1c = 2;
                }
                DAT_UnknownBinkCount::instance += 1;
            }
        }

    }
}
}
