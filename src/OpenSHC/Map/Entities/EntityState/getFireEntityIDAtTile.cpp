#include "../EntityState.func.hpp"

#include "OpenSHC/Map/Entities/EntityType.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        using OpenSHC::Map::Entities::EntityType;

        // FUNCTION: STRONGHOLDCRUSADER 0x00401540
        int EntityState::getFireEntityIDAtTile(int tile)
        {
            for (int entityID = DAT_TileMapState::instance.EntityLayer[tile]; entityID != 0;
                entityID = this->entityArray[entityID].nextEntityOnThisTileByID) {
                if (this->entityArray[entityID].entityType == OpenSHC::Map::Entities::ET_FIRE) {
                    return entityID;
                }
            }
            return 0;
        }

    }
}
}
