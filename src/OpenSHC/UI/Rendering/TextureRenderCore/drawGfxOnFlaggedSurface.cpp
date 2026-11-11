#include "../TextureRenderCore.func.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        // FUNCTION: STRONGHOLDCRUSADER 0x004558E0
        void TextureRenderCore::drawGfxOnFlaggedSurface(int gfxIndex, int xPos, int yPos)
        {
            // The pixels follow the 8-byte header (width and height)
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::drawTgxOnFlaggedSurface, this)(xPos, yPos,
                this->loadedGfxArray[gfxIndex].width, this->loadedGfxArray[gfxIndex].height,
                (ushort*)(this->gmAndGfxImageDataBuffer + this->loadedGfxArray[gfxIndex].offsetInBuffer + 8));
        }

    }
}
}
