// disable deprecation warnings for strcpy
#pragma warning(disable : 4996)

#include "../ResourceManager.func.hpp"

namespace OpenSHC {
namespace IO {

    // FUNCTION: STRONGHOLDCRUSADER 0x0046C2E0
    char* ResourceManager::mapNames_getLoadedMapNameForIndex(int mapIndex)
    {
        if (mapIndex >= 500) {
            return NULL;
        }
        return this->loadedMapNames[mapIndex];
    }

    // FUNCTION: STRONGHOLDCRUSADER 0x00471C10
    void ResourceManager::mapNames_syncLoadedMapNames()
    {
        this->mapFileCounter = this->loadedMapsCount;
        for (int mapIndex = 0; mapIndex < (int)this->mapFileCounter; ++mapIndex) {
            strcpy(MACRO_CALL_MEMBER(ResourceManager_Func::mapNames_getLoadedMapNameForIndex, this)(mapIndex),
                this->mapNames[mapIndex]);
        }
    }

} // namespace IO
} // namespace OpenSHC
