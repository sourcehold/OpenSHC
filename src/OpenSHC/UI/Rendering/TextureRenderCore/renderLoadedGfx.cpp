#include "../TextureRenderCore.func.hpp"

#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00454900
        void TextureRenderCore::renderLoadedGfx(int loadedGfxIndex, int xPos, int yPos)
        {
            RenderTargetInt RVar1;
            RVar1 = this->drawBufferChoiceValue;
            this->drawBufferChoiceValue = this->currentRenderSurfaceIdentifierUnk_0x8;
            MACRO_CALL_MEMBER(
                OpenSHC::UI::Rendering::TextureRenderCore_Func::renderFunctionResponsibleForManyGameObjects, this)(xPos,
                yPos, this->loadedGfxArray[loadedGfxIndex].width, this->loadedGfxArray[loadedGfxIndex].height,
                (ushort*)((int)(

                    (this->loadedGfxArray[loadedGfxIndex].offsetInBuffer + 8 + (int)this->gmAndGfxImageDataBuffer))));
            this->drawBufferChoiceValue = RVar1;
        }

    }
}
}
