#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        using OpenSHC::Map::Buildings::BuildingLogicalState;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0041B940
        BOOLEnum BuildingsState::hasBuildingAsNeighbour(int playerID, int x, int y, int size, BuildingType type)
        {
            // Checks whether a building of the player and type touches the given building location
            int tileCount = DAT_BuildingDefinedData::instance.BuildingAccessibleTilesCount[size];
            int index = 0;
            for (int tries = 0; tries < tileCount; ++tries) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::setupBuildingEntrancesOffset, this)(
                    size, 1, index, 0);
                int buildingID
                    = (short)DAT_TileMapState::instance.BuildingLayer
                          [DAT_ViewportRenderState::instance.translationMatrix[this->DAT_TempYOffset + y].addXgetTile
                              + this->DAT_TempXOffset + x];
                if (buildingID > 0 && this->buildings[buildingID].logicalState == BLS_NORMAL
                    && this->buildings[buildingID].owner == playerID
                    && this->buildings[buildingID].buildingType == type) {
                    return TRUE;
                }
                ++index;
                if (index >= tileCount) {
                    index = 0;
                }
            }
            return FALSE;
        }

    }
}
}
