#include "../TextureRenderCore.func.hpp"

#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        // FUNCTION: STRONGHOLDCRUSADER 0x00455050
        TextureRenderCore* TextureRenderCore::Constructor_TextureRenderCore(
            int processedImageDataBufferSize, int gmAndGfxImageDataBufferSize, int unknownMemSize)
        {
            // the buffer sizes are kept here and allocated below; the second unknown buffer is half the first
            this->gmProcessedImageDataBufferSize_0x74 = processedImageDataBufferSize;
            this->gmAndGfxImageDataBufferSize_0x8c = gmAndGfxImageDataBufferSize;
            if (unknownMemSize != 0) {
                this->unknownMemSize_1_0x7c = unknownMemSize;
                this->unknownMemSize_2_0x84 = unknownMemSize / 2;
            } else {
                this->unknownMemSize_1_0x7c = 0;
                this->unknownMemSize_2_0x84 = 0;
            }
            this->bufferAllocStateUnk_0x0 = 0;
            this->drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            this->currentRenderSurfaceIdentifierUnk_0x8 = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
            this->field_0x128 = 0;
            this->field_0x12c = 0;
            this->field_0x2c = 1;
            this->isZoom2 = 0;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::clearSomeMemory, this)();
            this->unknownSfxAndGmRelatedFlag = FALSE;
            // bufferAllocStateUnk_0x0 records a failed allocation: 1 for an image buffer, 2 and 3 for the other two
            this->gmProcessedImageData
                = (byte*)MACRO_CALL(OpenSHC::OS_Func::_malloc)(this->gmProcessedImageDataBufferSize_0x74);
            if (!this->gmProcessedImageData) {
                this->bufferAllocStateUnk_0x0 = 1;
                return this;
            }
            if (unknownMemSize != 0) {
                this->unknownMemPtr_1_0x80 = MACRO_CALL(OpenSHC::OS_Func::_malloc)(this->unknownMemSize_1_0x7c);
                if (!this->unknownMemPtr_1_0x80) {
                    this->bufferAllocStateUnk_0x0 = 2;
                    return this;
                }
                this->address2 = MACRO_CALL(OpenSHC::OS_Func::_malloc)(this->unknownMemSize_2_0x84);
                if (!this->address2) {
                    this->bufferAllocStateUnk_0x0 = 3;
                    return this;
                }
            } else {
                this->unknownMemPtr_1_0x80 = NULL;
                this->address2 = NULL;
            }
            this->gmAndGfxImageDataBuffer
                = (byte*)MACRO_CALL(OpenSHC::OS_Func::_malloc)(this->gmAndGfxImageDataBufferSize_0x8c);
            if (!this->gmAndGfxImageDataBuffer) {
                this->bufferAllocStateUnk_0x0 = 1;
                return this;
            }
            this->totalLoadedGfx = 0;
            this->colorPaletteOverride = 0;
            // room for one 64 x 66 RGB565 face bitmap per entry of bitmapFaceSizes, and their sizes, none loaded yet
            this->bitmapsFaces_0x94 = (ushort*)MACRO_CALL(OpenSHC::OS_Func::_malloc)(
                countof(this->bitmapFaceSizes) * 66 * 64 * sizeof(ushort));
            for (int i = 0; i < countof(this->bitmapFaceSizes); ++i) {
                this->bitmapFaceSizes[i] = 0;
            }
            return this;
        }

    }
}
}
