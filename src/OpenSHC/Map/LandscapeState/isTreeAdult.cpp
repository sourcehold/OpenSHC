#include "OpenSHC/Map/LandscapeState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"





namespace OpenSHC {
namespace Map {

using OpenSHC::WindowsHelper::Enums::BOOLEnum;


/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x004F2FE0
BOOLEnum LandscapeState::isTreeAdult(int treeID,int treeUID)

{
if (this->trees[treeID].uid != treeUID) {
return FALSE;
}
return (uint)(0 < (short)this->trees[treeID].treeAdultHoodStageRelatedVisual3);
}


}
}