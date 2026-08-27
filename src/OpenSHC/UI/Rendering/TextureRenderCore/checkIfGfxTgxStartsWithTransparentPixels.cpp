
#include "OpenSHC/IO/Graphics/GfxRef.hpp"
#include "OpenSHC/IO/Graphics/TgxToken.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.hpp"

#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        // FUNCTION: STRONGHOLDCRUSADER 0x004549C0
        BOOLEnum TextureRenderCore::checkIfGfxTgxStartsWithTransparentPixels(int gfxIndex)
        {
            // fixme: compiler picks different registers
            return (*(byte*)(this->loadedGfxArray[gfxIndex].offsetInBuffer + 8 + (int)this->gmAndGfxImageDataBuffer)
                       & OpenSHC::IO::Graphics::TT_TGX_PIXEL_HEADER)
                == OpenSHC::IO::Graphics::TT_TRANSPARENT_PIXELS;
        }

    }
}
}
