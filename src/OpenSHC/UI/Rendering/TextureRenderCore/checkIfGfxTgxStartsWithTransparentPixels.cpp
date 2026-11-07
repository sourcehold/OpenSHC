
#include "../TextureRenderCore.func.hpp"

#include "OpenSHC/IO/Graphics/TgxToken.hpp"

#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        // FUNCTION: STRONGHOLDCRUSADER 0x004549C0
        BOOLEnum TextureRenderCore::checkIfGfxTgxStartsWithTransparentPixels(int gfxIndex)
        {
            int byteIndex = this->loadedGfxArray[gfxIndex].offsetInBuffer + 8;
            byte checkByte = this->gmAndGfxImageDataBuffer[byteIndex];
            if ((checkByte & OpenSHC::IO::Graphics::TT_TGX_PIXEL_HEADER)
                == OpenSHC::IO::Graphics::TT_TRANSPARENT_PIXELS) {
                return TRUE;
            } else {
                return FALSE;
            }
        }

    }
}
}
