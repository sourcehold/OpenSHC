#include "../TextureRenderCore.func.hpp"

#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        // FUNCTION: STRONGHOLDCRUSADER 0x004549F0
        void TextureRenderCore::renderGfxTgxWithBlending(int gfxIndex, int x, int y, int blendStrengthUnk)
        {
            RenderTargetInt RVar1;
            RVar1 = this->drawBufferChoiceValue;
            if ((uint)blendStrengthUnk <= 0x1f) {
                this->drawBufferChoiceValue = this->currentRenderSurfaceIdentifierUnk_0x8;
                MACRO_CALL_MEMBER(
                    UI::Rendering::TextureRenderCore_Func::renderInterfaceOrBuildingOccupationArea, this)(x, y,
                    this->loadedGfxArray[gfxIndex].width, this->loadedGfxArray[gfxIndex].height,
                    (ushort*)((int)(

                        (this->loadedGfxArray[gfxIndex].offsetInBuffer + 8 + (int)this->gmAndGfxImageDataBuffer))),
                    blendStrengthUnk);
            }
            this->drawBufferChoiceValue = RVar1;
        }

    }
}
}
