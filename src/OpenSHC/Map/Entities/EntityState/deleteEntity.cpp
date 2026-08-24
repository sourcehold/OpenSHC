#include "OpenSHC/Map/Entities/EntityState.func.hpp"
#include "OpenSHC/IO/LowLevelMemory.func.hpp"



#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"

namespace OpenSHC {
namespace Map {
namespace Entities {




/* 
  decompilerscript: committed: 2025-01-30 21:56:35.138000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x004039F0
void EntityState::deleteEntity(uint entityID)

{
MACRO_CALL_MEMBER(OpenSHC::Map::Entities::EntityState_Func::doSomethingWithOtherEntitiesOnTile, this)(entityID);
MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(232, '\0', (void *)((int)(this->entityArray + entityID)));
return;
}


}
}
}