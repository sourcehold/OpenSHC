#include "../EntityState.func.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        // FUNCTION: STRONGHOLDCRUSADER 0x00401460
        void EntityState::doSomethingWithOtherEntitiesOnTile(uint entityID)
        {
            int tile = this->entityArray[entityID].tile;
            int count = 0;
            if (tile != 0) {
                int prevID;
                if (static_cast<int>(entityID) < 25) {
                    prevID = static_cast<unsigned char>(DAT_TileMapState::instance.EntityLayerLT25[tile]);
                    if (prevID == static_cast<int>(entityID)) {
                        DAT_TileMapState::instance.EntityLayerLT25[tile]
                            = static_cast<char>(this->entityArray[entityID].nextEntityOnThisTileByID);
                        this->entityArray[entityID].nextEntityOnThisTileByID = 0;
                        return;
                    }
                    for (int currentID = prevID; currentID != 0;) {
                        ++count;
                        if (count >= 100) {
                            break;
                        }
                        prevID = currentID;
                        currentID = this->entityArray[currentID].nextEntityOnThisTileByID;
                        if (currentID == static_cast<int>(entityID)) {
                            break;
                        }
                        if (currentID == 0) {
                            return;
                        }
                    }
                } else {
                    prevID = DAT_TileMapState::instance.EntityLayer[tile];
                    if (prevID == static_cast<int>(entityID)) {
                        DAT_TileMapState::instance.EntityLayer[tile]
                            = this->entityArray[entityID].nextEntityOnThisTileByID;
                        this->entityArray[entityID].nextEntityOnThisTileByID = 0;
                        return;
                    }
                    for (int currentID = prevID; currentID != 0;) {
                        ++count;
                        if (count >= 100) {
                            break;
                        }
                        prevID = currentID;
                        currentID = this->entityArray[currentID].nextEntityOnThisTileByID;
                        if (currentID == static_cast<int>(entityID)) {
                            break;
                        }
                        if (currentID == 0) {
                            return;
                        }
                    }
                }
                this->entityArray[prevID].nextEntityOnThisTileByID
                    = this->entityArray[entityID].nextEntityOnThisTileByID;
                this->entityArray[entityID].nextEntityOnThisTileByID = 0;
            }
        }

    } // namespace Entities
} // namespace Map
} // namespace OpenSHC
