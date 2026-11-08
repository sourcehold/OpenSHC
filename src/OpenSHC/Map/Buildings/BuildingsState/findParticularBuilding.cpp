#include "../BuildingsState.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0041BA00
        int BuildingsState::findParticularBuilding(
            int playerID, int x, int y, int buildingSize, BuildingType buildingType, int buildingID)
        {
            int const tileCount = DAT_BuildingDefinedData::instance.BuildingAccessibleTilesCount[buildingSize];
            int try_ = 0;
            for (int i = 0; i < tileCount; ++i) {
                MACRO_CALL_MEMBER(BuildingsState_Func::setupBuildingEntrancesOffset, this)(buildingSize, 1, try_, 0);
                int const tile
                    = DAT_ViewportRenderState::instance.translationMatrix[this->DAT_TempYOffset + y].addXgetTile
                    + this->DAT_TempXOffset + x;
                int const foundID = DAT_TileMapState::instance.BuildingLayer[tile];
                if (foundID > 0 && buildingID != foundID && this->buildings[foundID].logicalState == BLS_NORMAL
                    && this->buildings[foundID].buildingType == buildingType) {
                    return foundID;
                }
                ++try_;
                if (try_ >= tileCount) {
                    try_ = 0;
                }
            }
            return 0;
        }

    }
}
}
