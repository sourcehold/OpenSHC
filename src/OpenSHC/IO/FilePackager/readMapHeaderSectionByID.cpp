#include "../FilePackager.func.hpp"

#include "OpenSHC/IO/DecoderState.func.hpp"
#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/IO/ResourceManager.func.hpp"
#include "OpenSHC/OS.func.hpp"

#include "OpenSHC/Globals/DAT_DecoderState.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_ResourceManager.hpp"

namespace OpenSHC {
namespace IO {

    // FUNCTION: STRONGHOLDCRUSADER 0x004750E0
    void FilePackager::readMapHeaderSectionByID(MapSectionAddress* mapSectionAddrArray, int sectionID)
    {
        RenderLoadAndSaveBar* _loadAndSaveBarFunc = this->loadAndSaveBarFunc;
        this->loadAndSaveBarFunc = NULL;

        this->tempMem = MACRO_CALL(OS_Func::_malloc)(6000000);
        if (!this->tempMem) {
            return;
        }

        char* _Filename
            = MACRO_CALL_MEMBER(ResourceManager_Func::getFileNameOfCurrentActiveResource, DAT_ResourceManager::ptr)();

        int _fileDescriptor = MACRO_CALL(OS_Func::_ucrt_open)(_Filename, _O_BINARY, 0);
        if (_fileDescriptor == -1) {
            MACRO_CALL(OS_Func::_free_base)(this->tempMem);
            this->tempMem = NULL;
            return;
        }

        MACRO_CALL(OS_Func::_ucrt_read)(_fileDescriptor, &this->directorySize, sizeof(this->directorySize));
        if (this->directorySize < 0) {
            int _size;

            MACRO_CALL(OS_Func::_ucrt_read)(_fileDescriptor, &_size, sizeof(_size));
            while (_size) {
                MACRO_CALL(OS_Func::_ucrt_lseek)(_fileDescriptor, _size, FILE_CURRENT);
                MACRO_CALL(OS_Func::_ucrt_read)(_fileDescriptor, &_size, sizeof(_size));
            }
            MACRO_CALL(OS_Func::_ucrt_read)(_fileDescriptor, &this->directorySize, sizeof(this->directorySize));
        }

        if (this->directorySize == sizeof(this->directorySize) + sizeof(this->oldDirectory)) {
            MACRO_CALL(OS_Func::_ucrt_read)(_fileDescriptor, &this->oldDirectory, sizeof(this->oldDirectory));
            MACRO_CALL_MEMBER(FilePackager_Func::copyFromOldToNewMapDirectory, this)();
        } else {
            MACRO_CALL(OS_Func::_ucrt_read)(
                _fileDescriptor, &this->directory, this->directorySize - sizeof(this->directorySize));
        }

        MACRO_CALL(OS_Func::_ucrt_read)(_fileDescriptor, this->tempMem, this->directory.filePayloadSize);
        MACRO_CALL(OS_Func::_ucrt_close)(_fileDescriptor);
        this->versionNumOfCurrentFileTypeUnk = this->directory.magicNumOfFileType;

        if (_loadAndSaveBarFunc) {
            (*_loadAndSaveBarFunc)(50);
        }

        this->currentlyReadFileSectionIndex = 0;
        this->directory.filePayloadSize = 0;

        MapSectionAddress* _sectionAddressListStart = mapSectionAddrArray;
        while (this->currentlyReadFileSectionIndex < this->directory.sectionCount) {
            mapSectionAddrArray = _sectionAddressListStart;

            while (this->currentlyReadFileSectionIndex < 150) {
                this->currentlyReadFileSectionMemory = mapSectionAddrArray->address;
                this->currentlyReadFileSectionSize = mapSectionAddrArray->size;
                if (this->currentlyReadFileSectionMemory <= NULL
                    || this->directory.id[this->currentlyReadFileSectionIndex] == mapSectionAddrArray->sectionId) {
                    break;
                }
                ++mapSectionAddrArray;
            }

            if (this->currentlyReadFileSectionMemory > NULL && mapSectionAddrArray->sectionId == sectionID
                && !mapSectionAddrArray->unknown) {
                if (!this->directory.isCompressed[this->currentlyReadFileSectionIndex]
                    || this->CRASHES_saveUncompressedUnk) {
                    MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::copyData, DAT_LowLevelMemory::ptr)(
                        this->directory.uncompressedSize[this->currentlyReadFileSectionIndex],
                        (void*)((int)this->tempMem + this->directory.offset[this->currentlyReadFileSectionIndex]),
                        this->currentlyReadFileSectionMemory);
                } else {
                    MACRO_CALL_MEMBER(IO::DecoderState_Func::decodeData, DAT_DecoderState::ptr)(
                        (void*)((int)this->tempMem + this->directory.offset[this->currentlyReadFileSectionIndex]),
                        this->currentlyReadFileSectionMemory);
                }
            }
            ++this->currentlyReadFileSectionIndex;
        }

        MACRO_CALL(OS_Func::_free_base)(this->tempMem);
        this->tempMem = NULL;
    }

} // namespace IO
} // namespace OpenSHC
