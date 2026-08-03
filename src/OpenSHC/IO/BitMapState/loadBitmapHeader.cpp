#include "../BitMapState.func.hpp"

#include "OpenSHC/IO/ResourceManager.func.hpp"
#include "OpenSHC/OS.func.hpp"

#include "OpenSHC/Globals/DAT_ResourceManager.hpp"

namespace OpenSHC {
namespace IO {

    // FUNCTION: STRONGHOLDCRUSADER 0x00472270
    void BitMapState::loadBitmapHeader()
    {
        char* fileName
            = MACRO_CALL_MEMBER(ResourceManager_Func::getFileNameOfCurrentActiveResource, DAT_ResourceManager::ptr)();
        int fileHandle = MACRO_CALL(OS_Func::_ucrt_open)(fileName, _O_BINARY, 0);
        MACRO_CALL(OS_Func::_ucrt_read)(fileHandle, &this->bitmapFileHeader, 0xe);
        MACRO_CALL(OS_Func::_ucrt_read)(fileHandle, &this->bitmapInfoHeader, 0x28);
        this->mbr_0x0 = 0;
        this->mbr_0x4 = 0;
        this->total = this->bitmapInfoHeader.biWidth;
        this->high = this->bitmapInfoHeader.biHeight;
        this->biBitCount = this->bitmapInfoHeader.biBitCount;

        this->stride24bit = this->bitmapInfoHeader.biWidth * 3 + this->bitmapInfoHeader.biWidth % 4;
        this->stride16bit = this->bitmapInfoHeader.biWidth * 2;
        this->stride8bit = this->bitmapInfoHeader.biWidth;
        this->stride32bit = this->bitmapInfoHeader.biWidth * 4;
        if (this->biBitCount == 8) {
            this->size = this->bitmapInfoHeader.biHeight * this->bitmapInfoHeader.biWidth;
        } else if (this->biBitCount == 16) {
            this->size = this->stride16bit * this->bitmapInfoHeader.biHeight;
        } else if (this->biBitCount == 24) {
            this->size = this->stride24bit * this->bitmapInfoHeader.biHeight;
        } else if (this->biBitCount == 32) {
            this->size = this->stride32bit * this->bitmapInfoHeader.biHeight;
        } else {
            this->size = 0;
        }
        MACRO_CALL(OS_Func::_ucrt_close)(fileHandle);
        if (this->biBitCount != 8) {
            return;
        }

        if (this->bitmapFileHeader.bfOffBits > 1000) {
            this->paletteSize = 1024;
        } else {
            this->paletteSize = 768;
        }
        this->paletteStart = this->bitmapFileHeader.bfOffBits - this->paletteSize;
        char* fileNameForReOpen
            = MACRO_CALL_MEMBER(ResourceManager_Func::getFileNameOfCurrentActiveResource, DAT_ResourceManager::ptr)();
        int fileHandleReOpen = MACRO_CALL(OS_Func::_ucrt_open)(fileNameForReOpen, _O_BINARY, 0);
        MACRO_CALL(OS_Func::_ucrt_lseek)(fileHandleReOpen, this->paletteStart, FILE_BEGIN);
        MACRO_CALL(OS_Func::_ucrt_read)(fileHandleReOpen, this->palette, this->paletteSize);
        MACRO_CALL(OS_Func::_ucrt_close)(fileHandleReOpen);
    }

}
}
