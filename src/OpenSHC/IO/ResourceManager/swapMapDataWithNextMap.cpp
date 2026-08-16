#include "../ResourceManager.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"

#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"

namespace OpenSHC {
namespace IO {

    // FUNCTION: STRONGHOLDCRUSADER 0x00471C50
    void ResourceManager::swapMapDataWithNextMap(int _mapFileIndex)
    {
        MACRO_CALL_MEMBER(LowLevelMemory_Func::copyData, DAT_LowLevelMemory::ptr)(
            1000, this->loadedMapNames[_mapFileIndex], this->resourceFileNameArray);
        MACRO_CALL_MEMBER(LowLevelMemory_Func::copyData, DAT_LowLevelMemory::ptr)(
            1000, this->loadedMapNames[_mapFileIndex + 1], this->loadedMapNames[_mapFileIndex]);
        MACRO_CALL_MEMBER(LowLevelMemory_Func::copyData, DAT_LowLevelMemory::ptr)(
            1000, this->resourceFileNameArray, this->loadedMapNames[_mapFileIndex + 1]);

        dword const nextFileTime = this->mapFileTimes[_mapFileIndex];
        this->mapFileTimes[_mapFileIndex] = this->mapFileTimes[_mapFileIndex + 1];
        this->mapFileTimes[_mapFileIndex + 1] = nextFileTime;
    }

} // namespace IO
} // namespace OpenSHC
