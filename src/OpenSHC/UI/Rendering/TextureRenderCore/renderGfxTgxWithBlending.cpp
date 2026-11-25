#include "../TextureRenderCore.func.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        // FUNCTION: STRONGHOLDCRUSADER 0x004549F0
        void TextureRenderCore::renderGfxTgxWithBlending(int gfxIndex, int x, int y, int blendStrengthUnk)
        {
            // Saved before the image address is worked out (address first: quick_diff 1.0000 -> 0.9211)
            RenderTargetInt const savedTarget = this->drawBufferChoiceValue;
            // The pixels follow the 8-byte header (width and height)
            ushort* const source
                = (ushort*)(this->gmAndGfxImageDataBuffer + this->loadedGfxArray[gfxIndex].offsetInBuffer + 8);
            // Only blend strengths 0-31 are drawn (the target restored on both paths: quick_diff 1.0000 -> 0.8947)
            if (blendStrengthUnk < 0 || blendStrengthUnk > 31) {
                return;
            }
            this->drawBufferChoiceValue = this->currentRenderSurfaceIdentifierUnk_0x8;
            MACRO_CALL_MEMBER(
                OpenSHC::UI::Rendering::TextureRenderCore_Func::renderInterfaceOrBuildingOccupationArea, this)(x, y,
                this->loadedGfxArray[gfxIndex].width, this->loadedGfxArray[gfxIndex].height, source, blendStrengthUnk);
            this->drawBufferChoiceValue = savedTarget;
        }

    }
}
}
