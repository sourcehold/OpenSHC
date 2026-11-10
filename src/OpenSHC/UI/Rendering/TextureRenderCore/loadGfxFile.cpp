#include "../TextureRenderCore.func.hpp"

#include "OpenSHC/IO/ResourceManager.func.hpp"

#include "OpenSHC/Globals/DAT_ResourceManager.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        // FUNCTION: STRONGHOLDCRUSADER 0x00454620
        int TextureRenderCore::loadGfxFile(char const* tgxFileName)
        {
            // loads a gfx file after the ones loaded so far, if it still fits into the buffer's 18250000 bytes
            MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::resolveResourceFileName, DAT_ResourceManager::ptr)(
                OpenSHC::IO::FRT_GFX, tgxFileName);
            int const size = MACRO_CALL_MEMBER(
                OpenSHC::IO::ResourceManager_Func::getCurrentResourceSize, DAT_ResourceManager::ptr)();
            int const offset = this->loadedGfxArray[this->totalLoadedGfx].offsetInBuffer;
            if (offset + size > 18250000) {
                return -1;
            }
            byte* const destination = this->gmAndGfxImageDataBuffer + offset;
            if (!MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::readCurrentResourceIntoDestination,
                    DAT_ResourceManager::ptr)(destination, size)) {
                return -1;
            }
            // the picture's 8-byte header holds its width and height
            if (DAT_WindowAndDirectDraw::instance.colorBitMode == OpenSHC::Rendering::RGB_565) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::transformTgxFromRGB555ToRGB565, this)(
                    (ushort*)(destination + 8), DAT_ResourceManager::instance.loadPositionInCurrentResource - 8);
            }
            this->loadedGfxArray[this->totalLoadedGfx + 1].offsetInBuffer
                = this->loadedGfxArray[this->totalLoadedGfx].offsetInBuffer
                + DAT_ResourceManager::instance.loadPositionInCurrentResource;
            this->loadedGfxArray[this->totalLoadedGfx].width = ((int*)destination)[0];
            this->loadedGfxArray[this->totalLoadedGfx].height = ((int*)destination)[1];
            ++this->totalLoadedGfx;
            return this->totalLoadedGfx - 1;
        }

    }
}
}
