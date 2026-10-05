#include "../AIVState.func.hpp"

#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_AIVDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004EFED0
    void AIVState::aiPlaceQuarryAndOxtether(int playerID)
    {
        if (!MACRO_CALL_MEMBER(Game::GameStateStructures_Func::checkRequiredResourcesForBuildingOrPlanToBuy,
                DAT_GameState::ptr)(Commands::M_MAPPER_QUARRY, playerID, FALSE)
            || DAT_BuildingsState::instance.unknownCountdown01 < 20) {
            return;
        }
        MACRO_CALL_MEMBER(AIVState_Func::findAppropriateGridLocationForResourceTypeBuilding, this)(
            playerID, AIGCRT_BOULDER);
        if (this->buildingApproriateGridXPosition == -1) {
            return;
        }

        ++this->heatMaps[this->buildingApproriateGridXPosition][this->buildingAppropriateGridYPosition].structureCount;
        int const quarryXOffset
            = DAT_AIVDefinedData::instance
                  .OffsetsForClockwiseThreeByThreeAreaCheck[this->mapExtraInfo.algBuildingPlacementNudge % 9]
                  .x;
        int const quarryYOffset
            = DAT_AIVDefinedData::instance
                  .OffsetsForClockwiseThreeByThreeAreaCheck[this->mapExtraInfo.algBuildingPlacementNudge % 9]
                  .y;
        MACRO_CALL_MEMBER(Map::TileMapState_Func::placeBuilding, DAT_TileMapState::ptr)(playerID,
            quarryXOffset + this->buildingApproriateGridXPosition * 5,
            quarryYOffset + this->buildingAppropriateGridYPosition * 5, Commands::M_MAPPER_QUARRY,
            MACRO_CALL_MEMBER(Map::TileMapState_Func::getBuildingSizeForCommandBuildingType, DAT_TileMapState::ptr)(
                Commands::M_MAPPER_QUARRY),
            15);
        if (DAT_TileMapState::instance.buildingPlacementFail) {
            return;
        }
        int const quarryID = DAT_TileMapState::instance.placedBuildingID;
        MACRO_CALL_MEMBER(AIVState_Func::findSuitableGridLocationFittingCriteria, this)(
            this->buildingApproriateGridXPosition, this->buildingAppropriateGridYPosition);
        if (this->buildingApproriateGridXPosition == -1) {
            return;
        }

        // place an ox tether on the first free side and link it to the quarry
        for (int side = 0; side < 4; ++side) {
            int const xOffset = DAT_AIVDefinedData::instance.OffsetsForSpotCheckThreeByThreeAreaOnTheSide[side].x;
            int const yOffset = DAT_AIVDefinedData::instance.OffsetsForSpotCheckThreeByThreeAreaOnTheSide[side].y;
            MACRO_CALL_MEMBER(Map::TileMapState_Func::placeBuilding, DAT_TileMapState::ptr)(playerID,
                xOffset + this->buildingApproriateGridXPosition * 5,
                yOffset + this->buildingAppropriateGridYPosition * 5, Commands::M_MAPPER_OXENBASE,
                MACRO_CALL_MEMBER(Map::TileMapState_Func::getBuildingSizeForCommandBuildingType, DAT_TileMapState::ptr)(
                    Commands::M_MAPPER_OXENBASE),
                15);
            if (!DAT_TileMapState::instance.buildingPlacementFail) {
                int const oxTetherID = DAT_TileMapState::instance.placedBuildingID;
                DAT_BuildingsState::instance.buildings[quarryID].quarryLinkedOxTethers[0] = (short)oxTetherID;
                DAT_BuildingsState::instance.buildings[oxTetherID].oxtetherLinkedQuarryID = (short)quarryID;
                return;
            }
        }
    }

}
}
