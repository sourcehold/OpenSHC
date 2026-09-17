#include "../ResourceManager.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/OS.func.hpp"

#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"

namespace OpenSHC {
namespace IO {

    // FUNCTION: STRONGHOLDCRUSADER 0x00471F10
    BOOLEnum ResourceManager::readFirstPartOfCurrentResourceIntoMemory(
        void* destination, int partSize, char* fileExtension)
    {
        // Why do these not use the complete size? Or it the array not 1001 bytes? But what about the instructions that
        // basically use this number?
        MACRO_CALL_MEMBER(LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
            1000, '\0', this->resourceFileNameArray[0]);
        MACRO_CALL_MEMBER(LowLevelMemory_Func::putFileNameAndAppendFileExtension, DAT_LowLevelMemory::ptr)(
            this->resourceFileNameArray[this->currentActiveResourceType], this->resourceFileNameArray[0],
            fileExtension);

        FileResourceTypeInt tempActiveResource = this->currentActiveResourceType;
        this->currentActiveResourceType = NULL;

        char* _Filename = MACRO_CALL_MEMBER(ResourceManager_Func::getFileNameOfCurrentActiveResource, this)();
        this->fileHandle = MACRO_CALL(OS_Func::_ucrt_open)(_Filename, _O_BINARY, 0);

        this->currentActiveResourceType = tempActiveResource;

        if (this->fileHandle == -1) {
            return FALSE;
        }
        this->loadPositionInCurrentResource = MACRO_CALL(OS_Func::_ucrt_read)(this->fileHandle, destination, partSize);
        MACRO_CALL(OS_Func::_ucrt_close)(this->fileHandle);
        return TRUE;
    }

} // namespace IO
} // namespace OpenSHC
