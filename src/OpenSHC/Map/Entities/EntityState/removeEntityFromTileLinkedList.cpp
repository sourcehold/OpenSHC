#include "../EntityState.func.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        // FUNCTION: STRONGHOLDCRUSADER 0x00403900
        void EntityState::removeEntityFromTileLinkedList(int param_1)
        {
            int tile = this->entityArray[param_1].tile;
            int prevID = DAT_TileMapState::instance.EntityLayer[tile];
            int count = 0;
            if (prevID == param_1) {
                DAT_TileMapState::instance.EntityLayer[tile] = this->entityArray[param_1].nextEntityOnThisTileByID;
                this->entityArray[param_1].nextEntityOnThisTileByID = 0;
                return;
            }
            for (int currentID = prevID; currentID != 0;) {
                ++count;
                if (count >= 100) {
                    break;
                }
                prevID = currentID;
                currentID = this->entityArray[currentID].nextEntityOnThisTileByID;
                if (currentID == param_1) {
                    break;
                }
                if (currentID == 0) {
                    return;
                }
            }
            this->entityArray[prevID].nextEntityOnThisTileByID = this->entityArray[param_1].nextEntityOnThisTileByID;
            this->entityArray[param_1].nextEntityOnThisTileByID = 0;
        }

    } // namespace Entities
} // namespace Map
} // namespace OpenSHC
