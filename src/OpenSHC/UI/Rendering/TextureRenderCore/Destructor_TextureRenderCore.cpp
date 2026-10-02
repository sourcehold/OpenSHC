#include "../TextureRenderCore.func.hpp"

#include "OpenSHC/OS.func.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x0044C7E0
        void TextureRenderCore::Destructor_TextureRenderCore()
        {
            if (this->gmProcessedImageData != (void*)0x0) {
                MACRO_CALL(OpenSHC::OS_Func::_free_base)(this->gmProcessedImageData);
            }
            if (this->unknownMemPtr_1_0x80 != (void*)0x0) {
                MACRO_CALL(OpenSHC::OS_Func::_free_base)(this->unknownMemPtr_1_0x80);
            }
            if (this->address2 != (void*)0x0) {
                MACRO_CALL(OpenSHC::OS_Func::_free_base)(this->address2);
            }
            if (this->bitmapsFaces_0x94 != (void*)0x0) {
                MACRO_CALL(OpenSHC::OS_Func::_free_base)(this->bitmapsFaces_0x94);
            }
            if (this->gmAndGfxImageDataBuffer != (void*)0x0) {
                MACRO_CALL(OpenSHC::OS_Func::_free_base)(this->gmAndGfxImageDataBuffer);
            }
        }

    }
}
}
