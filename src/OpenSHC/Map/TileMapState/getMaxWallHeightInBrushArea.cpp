
#include "OpenSHC/Map/TileMapState.func.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_CRENEL;
    using OpenSHC::Map::LogicHelpers::L_STOCKPILEUnk;
    using OpenSHC::Map::LogicHelpers::L_WALL_OR_GATEHOUSE;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00502950
    int TileMapState::getMaxWallHeightInBrushArea(int param_1, uint param_2)
    {
        int baseTile = param_1;
        uint baseY = param_2;
        int maxWallHeight = 0;
        for (int index = 1; index < 5; index++) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getTileForBrush, this)(
                1, index, &param_1, (int*)&param_2, baseTile, baseY);
            if ((this->LogicLayer[param_1] & L_WALL_OR_GATEHOUSE) == 0) {
                continue;
            }
            if ((this->LogicLayer[param_1] & L_STOCKPILEUnk) != 0) {
                continue;
            }
            if ((this->LogicLayer[param_1] & L_CRENEL) != 0) {
                continue;
            }
            if (this->HeightLayer[param_1] > maxWallHeight) {
                maxWallHeight = this->HeightLayer[param_1];
            }
        }
        return maxWallHeight;
    }

}
}
