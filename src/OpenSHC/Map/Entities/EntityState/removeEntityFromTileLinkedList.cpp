#include "../EntityState.func.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        // FUNCTION: STRONGHOLDCRUSADER 0x00403900
        void EntityState::removeEntityFromTileLinkedList(int entityID)
        {
            int tile = this->entityArray[entityID].tile;
            int prevEntityID = DAT_TileMapState::instance.EntityLayer[tile];
            int guardCounter = 0;
            if (prevEntityID == entityID) {
                DAT_TileMapState::instance.EntityLayer[tile] = this->entityArray[entityID].nextEntityOnThisTileByID;
                this->entityArray[entityID].nextEntityOnThisTileByID = 0;
                return;
            }
            int nextEntityID = prevEntityID;
            if (prevEntityID != 0) {
                int currentEntityID;
                while (currentEntityID = nextEntityID, ++guardCounter < 100
                    && (prevEntityID = currentEntityID,
                        nextEntityID = this->entityArray[currentEntityID].nextEntityOnThisTileByID,
                        nextEntityID != entityID)) {
                    if (nextEntityID == 0) {
                        return;
                    }
                }
            }
            this->entityArray[prevEntityID].nextEntityOnThisTileByID
                = this->entityArray[entityID].nextEntityOnThisTileByID;
            this->entityArray[entityID].nextEntityOnThisTileByID = 0;
        }

    }
}
}
