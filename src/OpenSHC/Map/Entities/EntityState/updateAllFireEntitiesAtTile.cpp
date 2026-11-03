#include "../EntityState.func.hpp"

#include "OpenSHC/Map/Entities/EntityType.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        // FUNCTION: STRONGHOLDCRUSADER 0x00401570
        int EntityState::updateAllFireEntitiesAtTile(int tileUnk)
        {
            int iteration = 0;
            int entityID = DAT_TileMapState::instance.EntityLayer[tileUnk];
            while (entityID != 0) {
                if (++iteration >= 10) {
                    break;
                }
                if (this->entityArray[entityID].entityType == OpenSHC::Map::Entities::ET_FIRE) {
                    this->entityArray[entityID].someTracker = 2;
                    this->entityArray[entityID].fireParameter_0xb6 = 1;
                    this->entityArray[entityID].unknownAnimationFrameRelated = 0;
                }
                if (entityID == this->entityArray[entityID].nextEntityOnThisTileByID) {
                    break;
                }
                entityID = this->entityArray[entityID].nextEntityOnThisTileByID;
            }
            return 0;
        }

    }
}
}
