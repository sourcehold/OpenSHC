#include "../../Map.func.hpp"
#include "../WildlifeState.func.hpp"

#include "OpenSHC/Map/Location/Point8IntXY.hpp"

#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"

namespace OpenSHC {
namespace Map {
    using Map::Location::Point8IntXY;

    /*
      Boolean adjacency check. Walks all cardinal neighbours of cell (param_1, param_2) and returns 1   immediately if
      any valid neighbour has a non-zero field24_0x60 or field25_0x64. Returns 0 if no   such neighbour exists. Used to
      determine whether a cell is adjacent to some kind of marked zone   or resource.      renamed by: Claude Sonnet 4.6
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x0052D620
    undefined4 WildlifeState::hasAdjacentCellWithField24Or25(int param_1, int param_2)
    {
        for (int direction = 0; direction < 8; ++direction) {
            uint const x
                = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[direction].int_.xOffset + param_1;
            uint const y
                = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[direction].int_.yOffset + param_2;
            if (x < 0x28 && y < 0x28 && 0 < this->grid[x][y].firstMember
                && ((this->grid[x][y].field24_0x60 != 0) || (this->grid[x][y].field25_0x64 != 0))) {
                return (undefined4)(1);
            }
        }
        return (undefined4)(0);
    }

}
}
