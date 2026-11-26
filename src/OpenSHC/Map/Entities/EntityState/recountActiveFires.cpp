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
            for (int i = 1; i < this->maxEntityCount; ++i) {
                if (this->entityArray[i].logicalState != 0 && this->entityArray[i].logicalState == 2
                    && this->entityArray[i].entityType == OpenSHC::Map::Entities::ET_FIRE) {
                    DAT_TileMapState::instance.OccupancyLayer[this->entityArray[i].tile]
                        |= (1 << (this->entityArray[i].owner - 1));
                    DAT_EntityState::instance.fireCount += 1;
                }
            }
        }

    } // namespace Entities
} // namespace Map
} // namespace OpenSHC
