// disable deprecation warnings for strcpy and strcat
#pragma warning(disable : 4996)

#include "../ResourceManager.func.hpp"

#include "OpenSHC/IO/FilePackager.func.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_ResourceManager.hpp"
#include "OpenSHC/Globals/FilePackagerObj.hpp"

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

    // FUNCTION: STRONGHOLDCRUSADER 0x00478C60
    void ResourceManager::mapNames_filterMapsIfMapLock()
    {
        int const currentFileNumber = DAT_ResourceManager::instance.mapFileCounter;

        int id2 = 0;
        for (int id1 = 0; id1 < currentFileNumber; ++id1) {
            char* mapName = MACRO_CALL_MEMBER(
                ResourceManager_Func::mapNames_getLoadedMapNameForIndex, DAT_ResourceManager::ptr)(id1);

            char local_3f0[1008];
            strcpy(local_3f0, mapName);
            strcat(local_3f0, s__map_005a2294);
            MACRO_CALL_MEMBER(ResourceManager_Func::resolveResourceFileName, this)(FRT_MAPS, local_3f0);
            MACRO_CALL_MEMBER(FilePackager_Func::readMapHeader, FilePackagerObj::ptr)(FALSE);
            if (DAT_GameCore::instance.savedMapLocked == Map::MLS_EDITABLE) {
                MACRO_CALL_MEMBER(ResourceManager_Func::replaceMapNameWith, this)(id1, id2);
                ++id2;
            } else {
                --DAT_ResourceManager::instance.mapFileCounter;
            }
        }
    }

} // namespace IO
} // namespace OpenSHC
