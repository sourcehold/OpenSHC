#include "OpenSHC/IO/ResourceManager.func.hpp"





namespace OpenSHC {
namespace IO {




/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0046C2E0
char * ResourceManager::mapNames_getLoadedMapNameForIndex(int mapIndex)

{
if (499 < mapIndex) {
return (char *)0x0;
}
return(char *)( this->loadedMapNames[mapIndex]);
}


}
}