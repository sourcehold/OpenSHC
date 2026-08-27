
#include "../TextureRenderCore.func.hpp"

#include "OpenSHC/Globals/DAT_GMImageOffsets.hpp"
#include "OpenSHC/Globals/DAT_GMImageSizes.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        // FUNCTION: STRONGHOLDCRUSADER 0x004552e0
        void TextureRenderCore::transformUncompressedImageToRGB565(int imageIndex)
        {
            MACRO_CALL_MEMBER(TextureRenderCore_Func::transformRawToRGB555To565, this)(
                DAT_GMImageOffsets::instance[imageIndex], DAT_GMImageSizes::instance[imageIndex]);
        }

    }
}
}
