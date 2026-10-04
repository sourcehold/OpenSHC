#include "../TextureRenderCore.func.hpp"

#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"

#include "OpenSHC/Globals/DAT_GMImageHeaders.hpp"
#include "OpenSHC/Globals/DAT_GMImageOffsets.hpp"
#include "OpenSHC/Globals/DAT_GMImageSizes.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        // FUNCTION: STRONGHOLDCRUSADER 0x00455290
        void TextureRenderCore::transformTilesetToRGB565(int imageIndex)
        {
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::transformTileObjectToRGB565, this)(
                DAT_GMImageOffsets::instance[imageIndex]);
            if (DAT_GMImageHeaders::instance.imh[imageIndex].direction != 0) {
                MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::transformTgxFromRGB555ToRGB565, this)(
                    (ushort*)((int)this->gmProcessedImageData + DAT_GMImageOffsets::instance[imageIndex] + 0x200),
                    (int)((int)(DAT_GMImageSizes::instance[imageIndex] + -0x200)));
            }
        }

    }
}
}
