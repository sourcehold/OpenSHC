#include "OpenSHC/Map/Units/TribesState.func.hpp"





namespace OpenSHC {
namespace Map {
namespace Units {




/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x00522360
uint TribesState::tribeCorrespondsWithUID(int tribeID,uint tribeUID)

{
if (tribeUID == 0) {
return 0;
}
return (uint)(this->tribes[tribeID].uid == tribeUID);
}


}
}
}