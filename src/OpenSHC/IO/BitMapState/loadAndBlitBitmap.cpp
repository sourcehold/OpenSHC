#include "../BitMapState.func.hpp"

#include "OpenSHC/IO/ResourceManager.func.hpp"
#include "OpenSHC/OS.func.hpp"

#include "OpenSHC/Globals/DAT_ResourceManager.hpp"

namespace OpenSHC {
namespace IO {

    // FUNCTION: STRONGHOLDCRUSADER 0x004723E0
    void BitMapState::loadAndBlitBitmap(void* surface)
    {
        this->address = (dword)MACRO_CALL(OS_Func::_malloc)(this->size);
        if (!this->address) {
            return;
        }

        this->surface = (unsigned short*)surface;
        this->mbr_0x47c = 0;
        char* _Filename
            = MACRO_CALL_MEMBER(ResourceManager_Func::getFileNameOfCurrentActiveResource, DAT_ResourceManager::ptr)();
        int _fileDescriptor = MACRO_CALL(OS_Func::_ucrt_open)(_Filename, _O_BINARY, 0);
        MACRO_CALL(OS_Func::_ucrt_lseek)(_fileDescriptor, this->bitmapFileHeader.bfOffBits, FILE_BEGIN);
        MACRO_CALL(OS_Func::_ucrt_read)(_fileDescriptor, (void*)this->address, this->size);
        MACRO_CALL(OS_Func::_ucrt_close)(_fileDescriptor);
        if (this->biBitCount == 8) {
            MACRO_CALL_MEMBER(BitMapState_Func::copyBitmapToTextureBuffer, this)();
        }
        this->step2 = 1;
        this->step = 1;
        if (this->biBitCount == 24) {
            MACRO_CALL_MEMBER(BitMapState_Func::blitBitmap24BitToSurface565, this)(0);
        } else if (this->biBitCount == 8) {
            MACRO_CALL_MEMBER(BitMapState_Func::blitPalettedBitmapToSurface565, this)(0);
        }
        MACRO_CALL(OS_Func::_free_base)((void*)this->address);
        this->address = 0;
        this->surface = 0;
    }

}
}
