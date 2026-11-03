#include "../EntityState.func.hpp"

#include "OpenSHC/Map/Entities/EntityType.hpp"

#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        // FUNCTION: STRONGHOLDCRUSADER 0x00401620
        void EntityState::recountActiveFires()
        {
            DAT_EntityState::instance.fireCount = 0;
            for (int entityID = 1; entityID < (int)this->maxEntityCount; entityID++) {
                if (this->entityArray[entityID].logicalState != 0 && this->entityArray[entityID].logicalState == 2
                    && this->entityArray[entityID].entityType == OpenSHC::Map::Entities::ET_FIRE) {
                    DAT_TileMapState::instance.OccupancyLayer[this->entityArray[entityID].tile]
                        |= (uchar)(1 << (this->entityArray[entityID].owner - 1));
                    DAT_EntityState::instance.fireCount += 1;
                }
            }
        }

    }
}
}
