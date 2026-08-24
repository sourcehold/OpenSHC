#include "OpenSHC/Map/LandscapeState.func.hpp"





namespace OpenSHC {
namespace Map {




/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x004F2FB0
uint LandscapeState::isTreeAliveAndMatchingUID(int treeID,int param_2)

{
if (this->trees[treeID].uid != param_2) {
return 0;
}
return (uint)(this->trees[treeID].zeroUpTo2 == 0);
}


}
}