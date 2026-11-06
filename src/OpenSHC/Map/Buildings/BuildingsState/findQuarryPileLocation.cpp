#include "../BuildingsState.func.hpp"

#include "OpenSHC/Map/TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0041B890
        void BuildingsState::findQuarryPileLocation(undefined4 playerID, int x, int y, int buildingSize, int pileSize,
            int tryUnk, MappersEnum commandBuildingType)
        {
            int const tileCount = DAT_BuildingDefinedData::instance.BuildingAccessibleTilesCount[buildingSize];
            int try_ = tileCount / 4;
            for (int i = 0; i < tileCount; ++i) {
                MACRO_CALL_MEMBER(BuildingsState_Func::setupBuildingEntrancesOffset, this)(
                    buildingSize, pileSize, try_, tryUnk);
                DAT_TileMapState::instance.DAT_TempBuildingRotation = 0;
                MACRO_CALL_MEMBER(TileMapState_Func::checkBuildingCanBePlacedHere, DAT_TileMapState::ptr)(
                    playerID, this->DAT_TempXOffset + x, this->DAT_TempYOffset + y, commandBuildingType, pileSize);
                if (DAT_TileMapState::instance.buildingPlacementFail == 0) {
                    return;
                }
                ++try_;
                if (try_ >= tileCount) {
                    try_ = 0;
                }
            }
        }

    }
}
}
