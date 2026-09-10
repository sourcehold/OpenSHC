
#include "../TextureRenderCore.func.hpp"

#include "OpenSHC/Globals/DAT_GMImageOffsets.hpp"
#include "OpenSHC/Globals/DAT_GMImageSizes.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        // FUNCTION: STRONGHOLDCRUSADER 0x00455270
        void TextureRenderCore::transformTgxCompressedImageToRGB565(int imageIndex)
        {
            MACRO_CALL_MEMBER(TextureRenderCore_Func::transformTgxFromRGB555ToRGB565, this)(
                (ushort*)(&(((byte*)this->gmProcessedImageData)[DAT_GMImageOffsets::instance[imageIndex]])),
                DAT_GMImageSizes::instance[imageIndex]);
        }

    }
}
}
