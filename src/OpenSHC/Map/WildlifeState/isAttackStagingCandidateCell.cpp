#include "OpenSHC/Map/WildlifeState.func.hpp"

#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x0052D690
    BOOLEnum WildlifeState::isAttackStagingCandidateCell(int cellX, int cellY)
    {
        if (this->grid[cellX][cellY].unclaimedArea > 8) {
            return FALSE;
        }
        if (this->grid[cellX][cellY].trees > 4) {
            return FALSE;
        }
        if (this->grid[cellX][cellY].firstMember < 50) {
            return FALSE;
        }
        for (int direction = 0; direction < 8; direction += 2) {
            uint const x
                = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[direction].int_.xOffset + cellX;
            uint const y
                = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[direction].int_.yOffset + cellY;
            if (x <= 39 && y <= 39 && this->grid[x][y].firstMember > 0 && this->grid[x][y].unknownNonZero01 != 0) {
                return TRUE;
            }
        }
        return FALSE;
    }

}
}
