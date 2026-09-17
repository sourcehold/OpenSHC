#include "../ResourceManager.func.hpp"

#include "OpenSHC/OS.func.hpp"

namespace OpenSHC {
namespace IO {

    // FUNCTION: STRONGHOLDCRUSADER 0x0046C280
    dword ResourceManager::getChecksumOfMapByName(char* mapNameAddress)
    {
        for (int _mapIndex = 0; _mapIndex < this->loadedMapsCount; ++_mapIndex) {
            if (!MACRO_CALL(OS_Func::__stricmp)(this->mapNames[_mapIndex], mapNameAddress)) {
                return this->mapMetaInfoArray[_mapIndex].loadedMapsChecksumArray;
            }
        }
        return 0;
    }

} // namespace IO
} // namespace OpenSHC
