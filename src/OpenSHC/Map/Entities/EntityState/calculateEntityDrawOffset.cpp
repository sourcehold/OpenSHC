#include "../EntityState.func.hpp"

#include "OpenSHC/Globals/DAT_EntityDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        // FUNCTION: STRONGHOLDCRUSADER 0x004036F0
        void EntityState::calculateEntityDrawOffset(int entityID)
        {
            int x = this->entityArray[entityID].microX & 7;
            int y = this->entityArray[entityID].microY & 7;
            if (DAT_TileMapState::instance.mapOrientation == 4) {
                x = 7 - x;
                y = 7 - y;
            } else if (DAT_TileMapState::instance.mapOrientation == 2) {
                x = 7 - x;
            } else if (DAT_TileMapState::instance.mapOrientation == 6) {
                y = 7 - y;
            }
            if (DAT_TileMapState::instance.mapOrientation == 0 || DAT_TileMapState::instance.mapOrientation == 4) {
                x *= 2;
                y *= 16;
            } else {
                x *= 16;
                y *= 2;
            }
            int idx = (y + x) * 2;
            short* offsets = &DAT_EntityDefinedData::instance.EntitySubTileDrawOffsets[0].x;
            this->entityArray[entityID].x1 = offsets[idx];
            this->entityArray[entityID].y1 = offsets[idx + 2];
        }

    } // namespace Entities
} // namespace Map
} // namespace OpenSHC
