#include "../TileMapState.func.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_CRENEL;
    using OpenSHC::Map::LogicHelpers::L_STOCKPILEUnk;
    using OpenSHC::Map::LogicHelpers::L_WALL_OR_GATEHOUSE;

    // FUNCTION: STRONGHOLDCRUSADER 0x00502950
    int TileMapState::getMaxWallHeightInBrushArea(int tile, uint y)
    {
        int baseTile = tile;
        uint baseY = y;
        int maxWallHeight = 0;
        for (int index = 1; index < 5; index++) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getTileForBrush, this)(
                1, index, &tile, (int*)&y, baseTile, baseY);
            if ((this->LogicLayer[tile] & L_WALL_OR_GATEHOUSE) == 0) {
                continue;
            }
            if ((this->LogicLayer[tile] & L_STOCKPILEUnk) != 0) {
                continue;
            }
            if ((this->LogicLayer[tile] & L_CRENEL) != 0) {
                continue;
            }
            if (this->HeightLayer[tile] > maxWallHeight) {
                maxWallHeight = this->HeightLayer[tile];
            }
        }
        return maxWallHeight;
    }

}
}
