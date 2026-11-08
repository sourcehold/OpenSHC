#include "../TextureRenderCore.func.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        // FUNCTION: STRONGHOLDCRUSADER 0x00454900
        void TextureRenderCore::renderLoadedGfx(int loadedGfxIndex, int xPos, int yPos)
        {
            // draws a gfx file loaded by loadGfxFile or loadGfxAtBufferEnd, on the surface
            // currentRenderSurfaceIdentifierUnk_0x8 names for this one call
            RenderTargetInt const savedTarget = this->drawBufferChoiceValue;
            // pixels after the 8-byte header, named before the target switch (inline: quick_diff 1.0000 -> 0.7500)
            ushort* const source
                = (ushort*)(this->gmAndGfxImageDataBuffer + this->loadedGfxArray[loadedGfxIndex].offsetInBuffer + 8);
            this->drawBufferChoiceValue = this->currentRenderSurfaceIdentifierUnk_0x8;
            MACRO_CALL_MEMBER(
                OpenSHC::UI::Rendering::TextureRenderCore_Func::renderFunctionResponsibleForManyGameObjects, this)(xPos,
                yPos, this->loadedGfxArray[loadedGfxIndex].width, this->loadedGfxArray[loadedGfxIndex].height, source);
            this->drawBufferChoiceValue = savedTarget;
        }

    }
}
}
