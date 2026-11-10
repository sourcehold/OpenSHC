#include "../TextureRenderCore.func.hpp"

#include "OpenSHC/IO/ResourceManager.func.hpp"

#include "OpenSHC/Globals/DAT_ResourceManager.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        // FUNCTION: STRONGHOLDCRUSADER 0x004547C0
        int TextureRenderCore::loadGfxAtBufferEnd(char* fileName)
        {
            // loads a gfx file (the menu edges, for example), packed backwards from the end of the buffer's 18250000
            // bytes
            MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::resolveResourceFileName, DAT_ResourceManager::ptr)(
                OpenSHC::IO::FRT_GFX, fileName);
            int const size = MACRO_CALL_MEMBER(
                OpenSHC::IO::ResourceManager_Func::getCurrentResourceSize, DAT_ResourceManager::ptr)();
            byte* const destination = this->gmAndGfxImageDataBuffer
                - this->loadedGfxArray[this->backwardsLoadedGfxIndex_0x16C850].backwardsOffsetInBuffer - size
                + 18250000;
            if (!MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::readCurrentResourceIntoDestination,
                    DAT_ResourceManager::ptr)(destination, size)) {
                return -1;
            }
            // the picture's 8-byte header holds its width and height
            if (DAT_WindowAndDirectDraw::instance.colorBitMode == OpenSHC::Rendering::RGB_565) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::transformTgxFromRGB555ToRGB565, this)(
                    (ushort*)(destination + 8), DAT_ResourceManager::instance.loadPositionInCurrentResource - 8);
            }
            this->loadedGfxArray[this->backwardsLoadedGfxIndex_0x16C850].offsetInBuffer = 18250000
                - this->loadedGfxArray[this->backwardsLoadedGfxIndex_0x16C850].backwardsOffsetInBuffer - size;
            this->loadedGfxArray[this->backwardsLoadedGfxIndex_0x16C850 - 1].backwardsOffsetInBuffer
                = this->loadedGfxArray[this->backwardsLoadedGfxIndex_0x16C850].backwardsOffsetInBuffer
                + DAT_ResourceManager::instance.loadPositionInCurrentResource;
            this->loadedGfxArray[this->backwardsLoadedGfxIndex_0x16C850].backwardsOffsetInBuffer
                = this->loadedGfxArray[this->backwardsLoadedGfxIndex_0x16C850 - 1].backwardsOffsetInBuffer;
            this->loadedGfxArray[this->backwardsLoadedGfxIndex_0x16C850].width = ((int*)destination)[0];
            this->loadedGfxArray[this->backwardsLoadedGfxIndex_0x16C850].height = ((int*)destination)[1];
            --this->backwardsLoadedGfxIndex_0x16C850;
            return this->backwardsLoadedGfxIndex_0x16C850 + 1;
        }

    }
}
}
