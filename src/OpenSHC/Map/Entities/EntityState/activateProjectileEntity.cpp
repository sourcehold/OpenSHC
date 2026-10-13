#include "../EntityState.func.hpp"

#include "OpenSHC/Map/Entities/EntityType.hpp"
#include "OpenSHC/Map/Entities/EntityTypeShort.hpp"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        using OpenSHC::Map::Entities::EntityType;
        using OpenSHC::Map::Entities::EntityTypeShort;

        // FUNCTION: STRONGHOLDCRUSADER 0x004039B0
        void EntityState::activateProjectileEntity(int entityID)
        {
            this->entityArray[entityID].logicalState = 2;
            this->entityArray[entityID].field72_0xa8 = 1;
            MACRO_CALL_MEMBER(OpenSHC::Map::Entities::EntityState_Func::setProjectileEntityValues2, this)(
                entityID, (EntityType)this->entityArray[entityID].entityType2);
        }

    }
}
}
