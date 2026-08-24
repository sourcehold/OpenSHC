// ============================================================================
// Program   : Stronghold Crusader.exe
// Namespace : _HoldStrong::UI::Rendering::TextureRenderCore
// Function  : transformUncompressedImageToRGB565
// Address   : 004552e0
// Signature : void __thiscall transformUncompressedImageToRGB565(TextureRenderCore * this, int imageIndex)
// ============================================================================

#include "OpenSHC/UI/Rendering/TextureRenderCore.hpp"

#include "OpenSHC/Globals/DAT_GMImageOffsets.hpp"
#include "OpenSHC/Globals/DAT_GMImageSizes.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        // FUNCTION: STRONGHOLDCRUSADER 0x004552e0
        void TextureRenderCore::transformUncompressedImageToRGB565(int imageIndex)

        {
            transformRawToRGB555To565(DAT_GMImageOffsets::instance[imageIndex], DAT_GMImageSizes::instance[imageIndex]);
            return;
        }

    }
}
}
