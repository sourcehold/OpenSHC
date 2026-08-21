// disable deprecation warnings for strcpy and strcat
#pragma warning(disable : 4996)

#include "../ResourceManager.func.hpp"

#include "OpenSHC/IO/FileResourceType.hpp"
#include "OpenSHC/string-macros.hpp"

namespace OpenSHC {
namespace IO {

    // FUNCTION: STRONGHOLDCRUSADER 0x00478360
    void ResourceManager::resolveResourceFileName(FileResourceType resourceType, char const* shortFileName)
    {
        this->currentActiveResourceType = resourceType;
        switch (resourceType) {
        case FRT_GM:
            strcpy(this->resourceFileNameArray[resourceType], S_GM);
            strcat(this->resourceFileNameArray[resourceType], shortFileName);
            return;

        case FRT_SCENARIOS:
            strcpy(this->resourceFileNameArray[resourceType], S_SCENARIOS__005A64F4);
            strcat(this->resourceFileNameArray[resourceType], shortFileName);
            return;

        case FRT_GFX:
            strcpy(this->resourceFileNameArray[resourceType], S_GFX__005A5A1C);
            strcat(this->resourceFileNameArray[resourceType], shortFileName);
            return;

        case FRT_GFX8:
            strcpy(this->resourceFileNameArray[resourceType], S_GFX8__005A64EC);
            strcat(this->resourceFileNameArray[resourceType], shortFileName);
            return;

        case FRT_CASTLES:
            strcpy(this->resourceFileNameArray[resourceType], S_CASTLES__005A64E0);
            strcat(this->resourceFileNameArray[resourceType], shortFileName);
            return;

        case FRT_UNKNOWN: {
            // NOTE: Requires direct, non-resolved call due to copy elision.
            std::string savePath(this->paths_getSavesPath(true));
            strcpy(this->resourceFileNameArray[resourceType], savePath.c_str());
            strcat(this->resourceFileNameArray[resourceType], shortFileName);
            return;
        }

        case FRT_HELP:
            strcpy(this->resourceFileNameArray[resourceType], S_HELP__005A5A24);
            strcat(this->resourceFileNameArray[resourceType], shortFileName);
            return;

        case FRT_BINKS:
            strcpy(this->resourceFileNameArray[resourceType], S_BINKS__005A64D8);
            strcat(this->resourceFileNameArray[resourceType], shortFileName);
            return;

        case FRT_FX:
            strcpy(this->resourceFileNameArray[resourceType], S_FX__005A5A2C);
            strcat(this->resourceFileNameArray[resourceType], shortFileName);
            return;

        case FRT_GFX_SPEECH: // FIXME: Wrong name? Should be FRT_FX_SPEECH, or not?
            strcpy(this->resourceFileNameArray[resourceType], S_FX_SPEECH__005A64CC);
            strcat(this->resourceFileNameArray[resourceType], shortFileName);
            return;

        case FRT_MAPS: {
            strcpy(this->resourceFileNameArray[resourceType], S_MAPS__005A64C4);
            strcat(this->resourceFileNameArray[resourceType], shortFileName);

            if (MACRO_CALL_MEMBER(ResourceManager_Func::doesFileExist, this)(
                    this->resourceFileNameArray[resourceType])) {
                return;
            }
            // NOTE: Requires direct, non-resolved calls due to copy elision.
            std::string documentMapsFolder(this->paths_getDocumentsMapsFolderString(true));
            strcpy(this->resourceFileNameArray[resourceType], documentMapsFolder.c_str());
            strcat(this->resourceFileNameArray[resourceType], shortFileName);
            return;
        }

        case FRT_SCORES:
            strcpy(this->resourceFileNameArray[resourceType], S_SCORES__005A64BC);
            strcat(this->resourceFileNameArray[resourceType], shortFileName);
            return;

        case FRT_BMP:
            strcpy(this->resourceFileNameArray[resourceType], "");
            strcat(this->resourceFileNameArray[resourceType], shortFileName);
            return;

        default:
            strcpy(this->resourceFileNameArray[resourceType], shortFileName);
            return;
        }
    }

} // namespace IO
} // namespace OpenSHC
