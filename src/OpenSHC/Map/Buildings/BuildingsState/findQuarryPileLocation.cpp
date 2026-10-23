#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0041B890
        void BuildingsState::findQuarryPileLocation(undefined4 playerID, int x, int y, int buildingSize, int pileSize,
            int tryUnk, MappersEnum commandBuildingType)
        {
            // Places the pile at the first free location around the quarry, starting at the second side
            int tileCount = DAT_BuildingDefinedData::instance.BuildingAccessibleTilesCount[buildingSize];
            int index = tileCount / 4;
            for (int tries = 0; tries < tileCount; ++tries) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::setupBuildingEntrancesOffset, this)(
                    buildingSize, pileSize, index, tryUnk);
                DAT_TileMapState::instance.DAT_TempBuildingRotation = 0;
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::checkBuildingCanBePlacedHere, DAT_TileMapState::ptr)(
                    playerID, this->DAT_TempXOffset + x, this->DAT_TempYOffset + y, commandBuildingType, pileSize);
                if (DAT_TileMapState::instance.buildingPlacementFail == FALSE) {
                    return;
                }
                ++index;
                if (index >= tileCount) {
                    index = 0;
                }
            }
        }

    }
}
}
