#include "OpenSHC/Map/Entities/EntityState.func.hpp"
#include "OpenSHC/Map/Entities/EntityTypeShort.hpp"
#include "OpenSHC/Map/Entities/EntityType.hpp"





namespace OpenSHC {
namespace Map {
namespace Entities {

using OpenSHC::Map::Entities::EntityTypeShort;
using OpenSHC::Map::Entities::EntityType;


/* 
  decompilerscript: committed: 2025-01-30 21:56:35.138000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x004039B0
int EntityState::activateProjectileEntity(int entityID)

{
EntityTypeShort EVar1;

EVar1 = this->entityArray[entityID].entityType2;
this->entityArray[entityID].logicalState = 2;
this->entityArray[entityID].field72_0xa8 = 1;
MACRO_CALL_MEMBER(OpenSHC::Map::Entities::EntityState_Func::setProjectileEntityValues2, this)(entityID, (EntityType)((int)((int)(short)EVar1)));
return entityID;
}


}
}
}