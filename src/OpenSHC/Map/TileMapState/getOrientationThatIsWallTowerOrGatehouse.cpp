#include "../TileMapState.func.hpp"

#include "OpenSHC/Map/MapConstants.hpp"

#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_CRENEL_VARIATIONUnk;
    using OpenSHC::Map::LogicHelpers::L_STOCKPILEUnk;
    using OpenSHC::Map::LogicHelpers::L_WALL_OR_GATEHOUSE;

    // FUNCTION: STRONGHOLDCRUSADER 0x004F8B50
    MapOrientation TileMapState::getOrientationThatIsWallTowerOrGatehouse(uint x, uint y)
    {
        if (x > MC_MAP_XY_LIMIT_INCLUSIVE || y > MC_MAP_XY_LIMIT_INCLUSIVE) {
            return OpenSHC::Map::Enums::MO_NONE;
        }
        if (DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y * MC_MAP_XY_LIMIT + x] == 0) {
            return OpenSHC::Map::Enums::MO_NONE;
        }

        int rowTile = DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x;
        for (int index = 0; index < countof(DAT_TerrainDefinedData::instance.SomeOrientationOrderArray); index++) {
            int orientation = DAT_TerrainDefinedData::instance.SomeOrientationOrderArray[index];
            int neighbour = this->directionTranslationMatrix[y][orientation] + rowTile;
            if ((this->LogicLayer[neighbour] & L_WALL_OR_GATEHOUSE) != 0
                && (this->LogicLayer[neighbour] & (L_STOCKPILEUnk | L_CRENEL_VARIATIONUnk)) == 0) {
                return (MapOrientation)orientation;
            }
        }
        return OpenSHC::Map::Enums::MO_NONE;
    }

}
}
