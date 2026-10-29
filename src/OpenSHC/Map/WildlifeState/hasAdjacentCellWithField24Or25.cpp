#include "OpenSHC/Map/WildlifeState.func.hpp"

#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"

namespace OpenSHC {
namespace Map {

    // only the four edge neighbours (every second entry of the clockwise offsets)
    // FUNCTION: STRONGHOLDCRUSADER 0x0052D620
    undefined4 WildlifeState::hasAdjacentCellWithField24Or25(int cellX, int cellY)
    {
        for (int direction = 0; direction < 8; direction += 2) {
            uint const x = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[direction].int_.xOffset + cellX;
            uint const y = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[direction].int_.yOffset + cellY;
            if (x <= 39 && y <= 39 && this->grid[x][y].firstMember > 0
                && (this->grid[x][y].field24_0x60 != 0 || this->grid[x][y].field25_0x64 != 0)) {
                return 1;
            }
        }
        return 0;
    }

}
}
