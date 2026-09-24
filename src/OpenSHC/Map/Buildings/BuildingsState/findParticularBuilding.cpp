#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        using OpenSHC::Map::Buildings::BuildingLogicalState;

        // FUNCTION: STRONGHOLDCRUSADER 0x0041BA00
        int BuildingsState::findParticularBuilding(
            undefined4 param_1, int x, int y, int buildingSize, BuildingType buildingType, int buildingID)
        {
            // Finds another building of the type that touches the given building location
            int tileCount = DAT_BuildingDefinedData::instance.BuildingAccessibleTilesCount[buildingSize];
            int index = 0;
            for (int tries = 0; tries < tileCount; ++tries) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::setupBuildingEntrancesOffset, this)(
                    buildingSize, 1, index, 0);
                int neighbourID
                    = (short)DAT_TileMapState::instance.BuildingLayer
                          [DAT_ViewportRenderState::instance.translationMatrix[this->DAT_TempYOffset + y].addXgetTile
                              + this->DAT_TempXOffset + x];
                if (neighbourID > 0 && buildingID != neighbourID
                    && this->buildings[neighbourID].logicalState == BLS_NORMAL
                    && this->buildings[neighbourID].buildingType == buildingType) {
                    return neighbourID;
                }
                ++index;
                if (index >= tileCount) {
                    index = 0;
                }
            }
            return 0;
        }

    }
}
}
