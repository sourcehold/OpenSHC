// ============================================================================
// Program   : Stronghold Crusader.exe
// Namespace : _HoldStrong::UI::Rendering::TextureRenderCore
// Function  : transformTgxCompressedImageToRGB565
// Address   : 00455270
// Signature : void __thiscall transformTgxCompressedImageToRGB565(TextureRenderCore * this, int imageIndex)
// ============================================================================

#include "OpenSHC/UI/Rendering/TextureRenderCore.hpp"

#include "OpenSHC/Globals/DAT_GMImageOffsets.hpp"
#include "OpenSHC/Globals/DAT_GMImageSizes.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        /* decompilerscript: committed: 2025-01-30 21:57:43.216000 */
        // FUNCTION: STRONGHOLDCRUSADER 0x00455270
        void TextureRenderCore::transformTgxCompressedImageToRGB565(int imageIndex)

        {
            this->transformTgxFromRGB555ToRGB565(
                (ushort*)(DAT_GMImageOffsets::instance[imageIndex] + (int)this->gmProcessedImageData),
                DAT_GMImageSizes::instance[imageIndex]);
            return;
        }

    }
}
}
