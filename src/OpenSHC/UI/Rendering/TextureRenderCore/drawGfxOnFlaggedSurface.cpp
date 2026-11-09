#include "../TextureRenderCore.func.hpp"

#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        // FUNCTION: STRONGHOLDCRUSADER 0x004558E0
        void TextureRenderCore::drawGfxOnFlaggedSurface(int gfxIndex, int xPos, int yPos)
        {
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::drawTgxOnFlaggedSurface, this)(xPos, yPos,
                this->loadedGfxArray[gfxIndex].width, this->loadedGfxArray[gfxIndex].height,
                (ushort*)((int)(

                    (this->loadedGfxArray[gfxIndex].offsetInBuffer + 8 + (int)this->gmAndGfxImageDataBuffer))));
        }

    }
}
}
