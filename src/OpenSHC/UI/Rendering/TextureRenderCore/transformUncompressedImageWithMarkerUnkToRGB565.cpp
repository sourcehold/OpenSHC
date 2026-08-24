// ============================================================================
// Program   : Stronghold Crusader.exe
// Namespace : _HoldStrong::UI::Rendering::TextureRenderCore
// Function  : transformUncompressedImageWithMarkerUnkToRGB565
// Address   : 00455250
// Signature : void __thiscall transformUncompressedImageWithMarkerUnkToRGB565(TextureRenderCore * this, int imageIndex)
// ============================================================================

#include "OpenSHC/UI/Rendering/TextureRenderCore.hpp"

#include "OpenSHC/Globals/DAT_GMImageOffsets.hpp"
#include "OpenSHC/Globals/DAT_GMImageSizes.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        // FUNCTION: STRONGHOLDCRUSADER 0x00455250
        void TextureRenderCore::transformUncompressedImageWithMarkerUnkToRGB565(int imageIndex)
        {
            transformRawWithMarkerUnkToRGB555To565(
                DAT_GMImageOffsets::instance[imageIndex], DAT_GMImageSizes::instance[imageIndex]);
        }

    }
}
}
