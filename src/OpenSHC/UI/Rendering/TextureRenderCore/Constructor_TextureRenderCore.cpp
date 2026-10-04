#include "../TextureRenderCore.func.hpp"

#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        using OpenSHC::Rendering::Enums::RenderTarget;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00455050
        TextureRenderCore* TextureRenderCore::Constructor_TextureRenderCore(
            int processedImageDataBufferSize, int gmAndGfxImageDataBufferSize, int unknownMemSize)
        {
            /*
              generates rendering class?
             */
            this->gmProcessedImageDataBufferSize_0x74 = processedImageDataBufferSize;
            this->gmAndGfxImageDataBufferSize_0x8c = gmAndGfxImageDataBufferSize;
            if (unknownMemSize == 0) {
                this->unknownMemSize_1_0x7c = 0;
                this->unknownMemSize_2_0x84 = 0;
            } else {
                this->unknownMemSize_2_0x84 = unknownMemSize / 2;
                this->unknownMemSize_1_0x7c = unknownMemSize;
            }
            this->bufferAllocStateUnk_0x0 = 0;
            this->drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            this->currentRenderSurfaceIdentifierUnk_0x8 = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
            this->field79_0x128 = 0;
            this->field80_0x12c = 0;
            this->field29_0x2c = 1;
            this->isZoom2 = 0;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::clearSomeMemory, this)();
            this->unknownSfxAndGmRelatedFlag = FALSE;
            this->gmProcessedImageData
                = MACRO_CALL(OpenSHC::OS_Func::_malloc)(this->gmProcessedImageDataBufferSize_0x74);
            if (this->gmProcessedImageData != (void*)0x0) {
                if (unknownMemSize == 0) {
                    this->unknownMemPtr_1_0x80 = (void*)0x0;
                    this->address2 = (void*)0x0;
                } else {
                    this->unknownMemPtr_1_0x80 = MACRO_CALL(OpenSHC::OS_Func::_malloc)(this->unknownMemSize_1_0x7c);
                    if (this->unknownMemPtr_1_0x80 == (void*)0x0) {
                        this->bufferAllocStateUnk_0x0 = 2;
                        return this;
                    }
                    this->address2 = MACRO_CALL(OpenSHC::OS_Func::_malloc)(this->unknownMemSize_2_0x84);
                    if (this->address2 == (void*)0x0) {
                        this->bufferAllocStateUnk_0x0 = 3;
                        return this;
                    }
                }
                this->gmAndGfxImageDataBuffer
                    = MACRO_CALL(OpenSHC::OS_Func::_malloc)(this->gmAndGfxImageDataBufferSize_0x8c);
                if (this->gmAndGfxImageDataBuffer != (void*)0x0) {
                    this->totalLoadedGfx = 0;
                    this->mbr_0x70 = 0;
                    this->bitmapsFaces_0x94 = MACRO_CALL(OpenSHC::OS_Func::_malloc)(304128);
                    this->field69_0x98[0] = 0;
                    this->field69_0x98[1] = 0;
                    this->field69_0x98[2] = 0;
                    this->field69_0x98[3] = 0;
                    this->field69_0x98[4] = 0;
                    this->field69_0x98[5] = 0;
                    this->field69_0x98[6] = 0;
                    this->field69_0x98[7] = 0;
                    this->field69_0x98[8] = 0;
                    this->field69_0x98[9] = 0;
                    this->field69_0x98[10] = 0;
                    this->field69_0x98[0xb] = 0;
                    this->field69_0x98[0xc] = 0;
                    this->field69_0x98[0xd] = 0;
                    this->field69_0x98[0xe] = 0;
                    this->field69_0x98[0xf] = 0;
                    this->field69_0x98[0x10] = 0;
                    this->field69_0x98[0x11] = 0;
                    this->field69_0x98[0x12] = 0;
                    this->field69_0x98[0x13] = 0;
                    this->unknownPlayerDependentRenderValue[0] = 0;
                    this->unknownPlayerDependentRenderValue[1] = 0;
                    this->unknownPlayerDependentRenderValue[2] = 0;
                    this->unknownPlayerDependentRenderValue[3] = 0;
                    this->unknownPlayerDependentRenderValue[4] = 0;
                    this->unknownPlayerDependentRenderValue[5] = 0;
                    this->unknownPlayerDependentRenderValue[6] = 0;
                    this->unknownPlayerDependentRenderValue[7] = 0;
                    this->field71_0x108 = 0;
                    this->field72_0x10c = 0;
                    this->field73_0x110 = 0;
                    this->field74_0x114 = 0;
                    this->field75_0x118 = 0;
                    this->field76_0x11c = 0;
                    this->field77_0x120 = 0;
                    this->field78_0x124 = 0;
                    return this;
                }
            }
            this->bufferAllocStateUnk_0x0 = 1;
            return this;
        }

    }
}
}
