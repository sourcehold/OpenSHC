#include "OpenSHC/UI/Credits.func.hpp"

#include "OpenSHC/Globals/DAT_ARRAY_00eb9b68.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_UnknownBinkCount.hpp"

namespace OpenSHC {
namespace UI {
    namespace Credits {

        // FUNCTION: STRONGHOLDCRUSADER 0x004DA8D0
        void AppendCreditsImageTransitionCommand(int command, int gfxIndex, int x, int y, int field10)
        {
            if (DAT_UnknownBinkCount::instance < 288 && gfxIndex >= 0
                && (command == 5 || command == 6 || command == 7)) {
                DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].commandType = command;
                DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].soundStream = gfxIndex;
                DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].field_0x38 = -1;
                DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].x = x;
                DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].y = y;
                DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].field_0x28 = field10;
                DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].field_0x1c = 0;
                DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].width
                    = DAT_TextureRenderCoreObject::instance.loadedGfxArray[gfxIndex].width;
                DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].height
                    = DAT_TextureRenderCoreObject::instance.loadedGfxArray[gfxIndex].height;
                if (command == 6) {
                    DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].field_0x1c = 1;
                } else if (command == 7) {
                    DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].field_0x1c = 2;
                }
                DAT_UnknownBinkCount::instance += 1;
            }
        }

    }
}
}
