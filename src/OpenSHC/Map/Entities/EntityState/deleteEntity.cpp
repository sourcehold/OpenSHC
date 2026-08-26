#include "../EntityState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"

#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        // FUNCTION: STRONGHOLDCRUSADER 0x004039F0
        void EntityState::deleteEntity(uint entityID)
        {
            MACRO_CALL_MEMBER(OpenSHC::Map::Entities::EntityState_Func::doSomethingWithOtherEntitiesOnTile, this)(
                entityID);
            MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                sizeof(Entity), 0, (void*)&this->entityArray[entityID]);
        }

    }
}
}
