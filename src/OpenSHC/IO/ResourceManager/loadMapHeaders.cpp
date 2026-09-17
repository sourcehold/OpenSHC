// disable deprecation warnings for strcpy and strcat
#pragma warning(disable : 4996)

#include "../ResourceManager.func.hpp"

#include "OpenSHC/IO/FilePackager.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_LoadingBarProgress.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_ResourceManager.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/FilePackagerObj.hpp"

namespace OpenSHC {
namespace IO {

    // FUNCTION: STRONGHOLDCRUSADER 0x00478AE0
    void ResourceManager::loadMapHeaders(BOOLEnum drawLoadingBar)
    {
        MACRO_CALL_MEMBER(ResourceManager_Func::discoverMapFiles, this)(s_maps_map_005a64b0);
        this->loadedMapsCount = this->mapFileCounter;

        for (int mapIndex = 0; mapIndex < this->mapFileCounter; ++mapIndex) {
            char* mapName = MACRO_CALL_MEMBER(ResourceManager_Func::mapNames_getLoadedMapNameForIndex, this)(mapIndex);
            strcpy(this->mapNames[mapIndex], mapName);

            char resourceFileName[1008];
            strcpy(resourceFileName, mapName);
            strcat(resourceFileName, s__map_005a2294);
            MACRO_CALL_MEMBER(ResourceManager_Func::resolveResourceFileName, DAT_ResourceManager::ptr)(
                FRT_MAPS, resourceFileName);
            MACRO_CALL_MEMBER(FilePackager_Func::readMapHeader, FilePackagerObj::ptr)(FALSE);

            this->mapMetaInfoArray[mapIndex].loadedMapsChecksumArray
                = MACRO_CALL_MEMBER(ResourceManager_Func::fileHashFunctionByteByByte, DAT_ResourceManager::ptr)();
            this->mapMetaInfoArray[mapIndex].mapType = DAT_GameCore::instance.mapType;
            this->mapMetaInfoArray[mapIndex].mapLocked = DAT_GameCore::instance.savedMapLocked;
            this->mapMetaInfoArray[mapIndex].mapBalance = DAT_GameCore::instance.savedMapBalance;
            this->mapMetaInfoArray[mapIndex].mapEndInt2 = DAT_GameCore::instance.savedMapEndInt2;
            this->mapMetaInfoArray[mapIndex].mapPlayerCount = DAT_GameCore::instance.mapPlayerCount;
            this->mapMetaInfoArray[mapIndex].int0 = DAT_MapPropertiesState::instance.scenarionMissionType;
            this->mapMetaInfoArray[mapIndex].mapType2 = DAT_MapPropertiesState::instance.scenarioMissionSiegeOrInvasion;

            int _progress = mapIndex * 100;
            if (drawLoadingBar == TRUE) {
                MACRO_CALL_MEMBER(
                    UI::Rendering::TextureRenderCore_Func::drawLoadingBarUnk, DAT_TextureRenderCoreObject::ptr)(
                    (Graphics::GmID)((_progress / this->mapFileCounter) + 80 + DAT_LoadingBarProgress::instance),
                    DAT_LoadingBarProgress::instance + 180);
            }
        }
    }

} // namespace IO
} // namespace OpenSHC
