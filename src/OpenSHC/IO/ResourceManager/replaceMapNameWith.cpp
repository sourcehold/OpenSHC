#include "../ResourceManager.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"

#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"

namespace OpenSHC {
namespace IO {

    // FUNCTION: STRONGHOLDCRUSADER 0x00471CD0
    void ResourceManager::replaceMapNameWith(dword id1, dword id2)
    {
        if (id1 == id2) {
            return;
        }
        MACRO_CALL_MEMBER(LowLevelMemory_Func::copyData, DAT_LowLevelMemory::ptr)(
            1000, this->loadedMapNames[id1], this->loadedMapNames[id2]);
        this->mapFileTimes[id2] = this->mapFileTimes[id1];
    }

} // namespace IO
} // namespace OpenSHC
