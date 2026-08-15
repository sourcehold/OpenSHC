#include "../ResourceManager.func.hpp"

namespace OpenSHC {
namespace IO {

    // FUNCTION: STRONGHOLDCRUSADER 0x0046C300
    char* ResourceManager::getFileNameOfCurrentActiveResource()
    {
        return this->resourceFileNameArray[this->currentActiveResourceType];
    }

} // namespace IO
} // namespace OpenSHC
