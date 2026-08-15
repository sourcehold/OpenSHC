#include "../ResourceManager.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"

#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"

namespace OpenSHC {
namespace IO {

    // FUNCTION: STRONGHOLDCRUSADER 0x00471BE0
    ResourceManager* ResourceManager::Constructor_ResourceManager()
    {
        this->mapFileCounter = 0;

        // FIXME?: Assuming the loadedMapNames is [500][1001], then this fill does not null the entire array.
        MACRO_CALL_MEMBER(LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
            500000, 0, this->loadedMapNames);
        return this;
    }

} // namespace IO
} // namespace OpenSHC
