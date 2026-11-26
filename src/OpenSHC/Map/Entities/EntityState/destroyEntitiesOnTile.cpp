#include "../EntityState.func.hpp"

#include "OpenSHC/Map/Entities/EntityType.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        // FUNCTION: STRONGHOLDCRUSADER 0x004019D0
        void EntityState::destroyEntitiesOnTile(int tile)
        {
            if ((DAT_TileMapState::instance.MiscDisplayLayer[tile] & 4096) == 0) {
                return;
            }
            for (int i = 1; i < this->maxEntityCount; ++i) {
                if (this->entityArray[i].logicalState == 2
                    && (this->entityArray[i].entityType == OpenSHC::Map::Entities::ET_FLAG_1
                        || this->entityArray[i].entityType == OpenSHC::Map::Entities::ET_FLAG_4
                        || this->entityArray[i].entityType == OpenSHC::Map::Entities::ET_FLAG_2
                        || this->entityArray[i].entityType == OpenSHC::Map::Entities::ET_FLAG_3
                        || this->entityArray[i].entityType == OpenSHC::Map::Entities::ET_BRAZIER
                        || this->entityArray[i].entityType == OpenSHC::Map::Entities::ET_HEADS_ON_SPIKES)
                    && this->entityArray[i].tile == tile) {
                    this->entityArray[i].logicalState = 3;
                    DAT_TileMapState::instance.MiscDisplayLayer[tile] &= ~4096;
                }
            }
        }

    } // namespace Entities
} // namespace Map
} // namespace OpenSHC
