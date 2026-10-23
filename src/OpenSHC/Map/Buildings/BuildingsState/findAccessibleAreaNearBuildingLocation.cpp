#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0041BAB0
        int BuildingsState::findAccessibleAreaNearBuildingLocation(int x, int y, int buildingSize)
        {
            // Returns the path connection area of the first walkable tile around the building location
            int tileCount = DAT_BuildingDefinedData::instance.BuildingAccessibleTilesCount[buildingSize];
            for (int i = 0; i < tileCount; ++i) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::setupBuildingEntrancesOffset, this)(
                    buildingSize, 1, i, 0);
                int tile = DAT_ViewportRenderState::instance.translationMatrix[this->DAT_TempYOffset + y].addXgetTile
                    + this->DAT_TempXOffset + x;
                if (DAT_TileMapState::instance.PathConnectionLayer[tile] != 0) {
                    return (short)DAT_TileMapState::instance.PathConnectionLayer[tile];
                }
            }
            return 0;
        }

    }
}
}
