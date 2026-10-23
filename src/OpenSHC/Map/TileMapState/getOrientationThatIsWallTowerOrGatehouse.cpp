#include "OpenSHC/Map/TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_CRENEL_VARIATIONUnk;
    using OpenSHC::Map::LogicHelpers::L_STOCKPILEUnk;
    using OpenSHC::Map::LogicHelpers::L_WALL_OR_GATEHOUSE;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004F8B50
    int TileMapState::getOrientationThatIsWallTowerOrGatehouse(uint x, uint y)
    {
        if (x > 399 || y > 399) {
            return 0xf;
        }
        if (DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y * 400 + x] == 0) {
            return 0xf;
        }

        int rowTile = DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x;
        for (int index = 0; index < 8; index++) {
            int orientation = DAT_TerrainDefinedData::instance.SomeOrientationOrderArray[index];
            int neighbour = this->directionTranslationMatrix[y][orientation] + rowTile;
            if ((this->LogicLayer[neighbour] & L_WALL_OR_GATEHOUSE) != 0
                && (this->LogicLayer[neighbour] & (L_STOCKPILEUnk | L_CRENEL_VARIATIONUnk)) == 0) {
                return orientation;
            }
        }
        return 0xf;
    }

}
}
