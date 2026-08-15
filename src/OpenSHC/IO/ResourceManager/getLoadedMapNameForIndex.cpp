#include "../ResourceManager.func.hpp"

namespace OpenSHC {
namespace IO {

    // FUNCTION: STRONGHOLDCRUSADER 0x0046C2E0
    char* ResourceManager::getLoadedMapNameForIndex(int mapIndex)
    {
        if (mapIndex >= 500) {
            return NULL;
        }
        return this->loadedMapNames[mapIndex];
    }

} // namespace IO
} // namespace OpenSHC
