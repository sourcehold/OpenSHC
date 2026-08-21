#include "../FilePackager.func.hpp"

#include "OpenSHC/IO/DecoderState.func.hpp"
#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_DecoderState.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"

namespace OpenSHC {
namespace IO {

    // FUNCTION: STRONGHOLDCRUSADER 0x00475690
    int FilePackager::unpackAIVFile(AIVSectionAddress* array, char* fileName)
    {
        int _fileHandle = MACRO_CALL(OS_Func::_ucrt_open)(fileName, _O_BINARY, 0);
        if (_fileHandle == -1) {
            return FALSE;
        }

        this->tempMem = MACRO_CALL(OS_Func::_malloc)(6000000);
        if (!this->tempMem) {
            return FALSE;
        }

        int result = TRUE;
        MACRO_CALL(OS_Func::_ucrt_read)(_fileHandle, &this->directorySize, sizeof(this->directorySize));
        if (this->directorySize == sizeof(this->directorySize) + sizeof(this->oldDirectory)) {
            MACRO_CALL(OS_Func::_ucrt_read)(_fileHandle, &this->oldDirectory, sizeof(this->oldDirectory));
            MACRO_CALL_MEMBER(FilePackager_Func::copyFromOldToNewMapDirectory, this)();
        } else {
            MACRO_CALL(OS_Func::_ucrt_read)(
                _fileHandle, &this->directory, this->directorySize - sizeof(this->directorySize));
        }
        MACRO_CALL(OS_Func::_ucrt_read)(_fileHandle, this->tempMem, this->directory.filePayloadSize);
        MACRO_CALL(OS_Func::_ucrt_close)(_fileHandle);

        this->versionNumOfCurrentFileTypeUnk = this->directory.magicNumOfFileType;
        this->currentlyReadFileSectionIndex = 0;
        this->directory.filePayloadSize = 0;

        char errorMessage[200]; // string is unused in the final game
        AIVSectionAddress* _sectionAddressListStart = array;
        while (this->currentlyReadFileSectionIndex < this->directory.sectionCount) {
            array = _sectionAddressListStart;

            while (this->currentlyReadFileSectionIndex < 150) {
                this->currentlyReadFileSectionMemory = array->address;
                this->currentlyReadFileSectionSize = array->size;
                if (this->currentlyReadFileSectionMemory <= NULL) {

                    break;
                }
                if (this->directory.id[this->currentlyReadFileSectionIndex] == array->sectionId) {
                    break;
                }
                ++array;
            }

            if (this->currentlyReadFileSectionMemory <= NULL) {
                result = FALSE;
            } else if (!array->unknown) {
                if (!this->directory.isCompressed[this->currentlyReadFileSectionIndex]
                    || this->CRASHES_saveUncompressedUnk) {

                    MACRO_CALL_MEMBER(LowLevelMemory_Func::copyData, DAT_LowLevelMemory::ptr)(
                        this->directory.uncompressedSize[this->currentlyReadFileSectionIndex],
                        (void*)((int)this->tempMem + this->directory.offset[this->currentlyReadFileSectionIndex]),
                        this->currentlyReadFileSectionMemory);

                    if (array->size < this->directory.uncompressedSize[this->currentlyReadFileSectionIndex]) {
                        MACRO_CALL(OS_Func::_sprintf)(errorMessage, s_Err_raw__d_005a633c, array->sectionId);
                        result = FALSE;
                    }
                } else {

                    MACRO_CALL_MEMBER(DecoderState_Func::decodeData, DAT_DecoderState::ptr)(
                        (void*)((int)this->tempMem + this->directory.offset[this->currentlyReadFileSectionIndex]),
                        this->currentlyReadFileSectionMemory);

                    if (array->size < this->directory.uncompressedSize[this->currentlyReadFileSectionIndex]) {
                        MACRO_CALL(OS_Func::_sprintf)(errorMessage, s_Err_cmp__d_005a6348, array->sectionId);
                        result = FALSE;
                    }
                }
            }
            ++this->currentlyReadFileSectionIndex;
        }

        MACRO_CALL(OS_Func::_free_base)(this->tempMem);
        this->tempMem = NULL;
        return result;
    }

} // namespace IO
} // namespace OpenSHC
