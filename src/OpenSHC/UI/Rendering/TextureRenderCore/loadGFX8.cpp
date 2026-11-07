#include "../TextureRenderCore.func.hpp"

#include "OpenSHC/IO/ResourceManager.func.hpp"

#include "OpenSHC/Globals/DAT_ResourceManager.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        // FUNCTION: STRONGHOLDCRUSADER 0x00454700
        int TextureRenderCore::loadGFX8(char* gfx8Filename)
        {
            MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::resolveResourceFileName, DAT_ResourceManager::ptr)(
                OpenSHC::IO::FRT_GFX8, gfx8Filename);
            int const size = MACRO_CALL_MEMBER(
                OpenSHC::IO::ResourceManager_Func::getCurrentResourceSize, DAT_ResourceManager::ptr)();
            int const offset = this->loadedGfxArray[this->totalLoadedGfx].offsetInBuffer;
            // Only if it still fits into the buffer's 18250000 bytes
            if (offset + size > 18250000) {
                return -1;
            }
            byte* const destination = this->gmAndGfxImageDataBuffer + offset;
            if (!MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::readCurrentResourceIntoDestination,
                    DAT_ResourceManager::ptr)(destination, size)) {
                return -1;
            }
            this->loadedGfxArray[this->totalLoadedGfx + 1].offsetInBuffer
                = this->loadedGfxArray[this->totalLoadedGfx].offsetInBuffer
                + DAT_ResourceManager::instance.loadPositionInCurrentResource;
            // The file starts with the image's width and height
            this->loadedGfxArray[this->totalLoadedGfx].width = ((int*)destination)[0];
            this->loadedGfxArray[this->totalLoadedGfx].height = ((int*)destination)[1];
            ++this->totalLoadedGfx;
            return this->totalLoadedGfx - 1;
        }

    }
}
}
