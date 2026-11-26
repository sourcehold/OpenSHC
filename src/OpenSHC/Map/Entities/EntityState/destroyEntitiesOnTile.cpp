#include "../EntityState.func.hpp"

#include "OpenSHC/Map/Entities/EntityType.hpp"
#include "OpenSHC/Map/LogicHelpers/MiscDisplay.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        // FUNCTION: STRONGHOLDCRUSADER 0x004019D0
        void EntityState::destroyEntitiesOnTile(int tile)
        {
            if ((DAT_TileMapState::instance.MiscDisplayLayer[tile] & OpenSHC::Map::LogicHelpers::MD_DECORATION_ENTITY)
                == 0) {
                return;
            }
            for (int entityID = 1; entityID < this->maxEntityCount; entityID++) {
                if (this->entityArray[entityID].logicalState == 2
                    && (this->entityArray[entityID].entityType == OpenSHC::Map::Entities::ET_FLAG_1
                        || this->entityArray[entityID].entityType == OpenSHC::Map::Entities::ET_FLAG_4
                        || this->entityArray[entityID].entityType == OpenSHC::Map::Entities::ET_FLAG_2
                        || this->entityArray[entityID].entityType == OpenSHC::Map::Entities::ET_FLAG_3
                        || this->entityArray[entityID].entityType == OpenSHC::Map::Entities::ET_BRAZIER
                        || this->entityArray[entityID].entityType == OpenSHC::Map::Entities::ET_HEADS_ON_SPIKES)
                    && this->entityArray[entityID].tile == tile) {
                    this->entityArray[entityID].logicalState = 3;
                    DAT_TileMapState::instance.MiscDisplayLayer[tile]
                        &= ~OpenSHC::Map::LogicHelpers::MD_DECORATION_ENTITY;
                }
            }
        }

    }
}
}
