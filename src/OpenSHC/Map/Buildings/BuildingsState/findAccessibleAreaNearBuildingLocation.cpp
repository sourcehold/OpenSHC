#include "../BuildingsState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0041BAB0
        int BuildingsState::findAccessibleAreaNearBuildingLocation(int x, int y, int buildingSize)
        {
            int const tileCount = DAT_BuildingDefinedData::instance.BuildingAccessibleTilesCount[buildingSize];
            for (int try_ = 0; try_ < tileCount; ++try_) {
                MACRO_CALL_MEMBER(BuildingsState_Func::setupBuildingEntrancesOffset, this)(buildingSize, 1, try_, 0);
                int const tile
                    = DAT_ViewportRenderState::instance.translationMatrix[this->DAT_TempYOffset + y].addXgetTile
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
