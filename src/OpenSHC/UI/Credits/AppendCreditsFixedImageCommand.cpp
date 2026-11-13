#include "OpenSHC/UI/Credits.func.hpp"

#include "OpenSHC/Globals/DAT_ARRAY_00eb9b68.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_UnknownBinkCount.hpp"

namespace OpenSHC {
namespace UI {
    namespace Credits {

        // FUNCTION: STRONGHOLDCRUSADER 0x004DAB00
        void AppendCreditsFixedImageCommand(int gfxIndex, int x, int y)
        {
            if (DAT_UnknownBinkCount::instance < 288) {
                DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].commandType = 21;
                DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].soundStream = gfxIndex;
                DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].x = x;
                DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].y = y;
                DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].field_0x28 = 7;
                DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].field_0x1c = 0;
                DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].width
                    = DAT_TextureRenderCoreObject::instance.loadedGfxArray[gfxIndex].width;
                DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].height
                    = DAT_TextureRenderCoreObject::instance.loadedGfxArray[gfxIndex].height;
                DAT_UnknownBinkCount::instance += 1;
            }
        }

    }
}
}
