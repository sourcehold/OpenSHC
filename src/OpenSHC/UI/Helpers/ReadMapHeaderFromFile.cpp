// disable deprecation warnings for strcpy and strcat
#pragma warning(disable : 4996)

#include "../Helpers.func.hpp"

#include "OpenSHC/IO/FilePackager.func.hpp"
#include "OpenSHC/IO/ResourceManager.func.hpp"
#include "OpenSHC/IO/FileResourceType.hpp"
#include "OpenSHC/string-macros.hpp"

#include "OpenSHC/Globals/DAT_ResourceManager.hpp"
#include "OpenSHC/Globals/FilePackagerObj.hpp"
#include "OpenSHC/Globals/INT_00eb9ae8.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004D8A20
    void Helpers::ReadMapHeaderFromFile(char* mapName)
    {
        // The original copies the name and appends the extension inline, so the macro is used here.
        char fileName[1008]; // the size of the original's buffer
        strcpy(fileName, mapName);
        // ".map"
        strcat(fileName, S__MAP_005A2294);
        MACRO_CALL_MEMBER(IO::ResourceManager_Func::resolveResourceFileName, DAT_ResourceManager::ptr)(
            IO::FRT_MAPS, fileName);
        MACRO_CALL_MEMBER(IO::FilePackager_Func::readMapHeader, FilePackagerObj::ptr)(TRUE);
        INT_00eb9ae8::instance = 1;
    }

}
}
