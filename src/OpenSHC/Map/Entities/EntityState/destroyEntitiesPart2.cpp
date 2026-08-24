#include "OpenSHC/Map/Entities/EntityState.func.hpp"
#include "OpenSHC/Map/Entities/Entity.hpp"





namespace OpenSHC {
namespace Map {
namespace Entities {

using OpenSHC::Map::Entities::Entity;


/* 
  decompilerscript: committed: 2025-01-30 21:56:35.138000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x00401B60
void EntityState::destroyEntitiesPart2(int param_1)

{
Entity * psVar1;
int iVar1;

psVar1 = &this->entityArray[1];
iVar1 = 2999;
do {
if ((psVar1->logicalState == 2) && (psVar1->owner == param_1)) {
psVar1->logicalState = 3;
}
psVar1 = psVar1 + 0x74;
iVar1 = iVar1 + -1;
} while (iVar1 != 0);
return;
}


}
}
}