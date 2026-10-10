#include "../../Map.func.hpp"
#include "../WildlifeState.func.hpp"

#include "OpenSHC/Map/Location/Point8IntXY.hpp"

#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"

namespace OpenSHC {
namespace Map {
    using Map::Location::Point8IntXY;

    /*
      Returns 1 if cell (param_1, param_2) is suitable for wildlife spawning, 0 otherwise. Conditions:   unclaimedArea <
      9, trees < 5, firstMember > 49 (open area with enough space), AND at least one   cardinal neighbour has
      unknownNonZero01 set. All conditions must be met. The neighbour check   likely ensures proximity to a valid
      habitat or patrol zone.      renamed by: Claude Sonnet 4.6
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x0052D690
    undefined4 WildlifeState::isSuitableWildlifeSpawnCell(int param_1, int param_2)
    {
        if (8 < this->grid[param_1][param_2].unclaimedArea) {
            return (undefined4)(0);
        }
        if (4 < this->grid[param_1][param_2].trees) {
            return (undefined4)(0);
        }
        if (this->grid[param_1][param_2].firstMember < 0x32) {
            return (undefined4)(0);
        }
        for (int direction = 0; direction < 8; direction += 2) {
            uint const x
                = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[direction].int_.xOffset
                + param_1;
            uint const y
                = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[direction].int_.yOffset
                + param_2;
            if (x <= 0x27 && y <= 0x27 && 0 < this->grid[x][y].firstMember
                && this->grid[x][y].unknownNonZero01 != 0) {
                return (undefined4)(1);
            }
        }
        return (undefined4)(0);
    }

}
}
