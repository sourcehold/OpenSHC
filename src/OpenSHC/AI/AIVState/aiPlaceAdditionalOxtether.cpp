#include "../AIVState.func.hpp"

#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_AIVDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004EFC30
    void AIVState::aiPlaceAdditionalOxtether(PlayerID playerID)
    {
        if (!MACRO_CALL_MEMBER(Game::GameStateStructures_Func::checkRequiredResourcesForBuildingOrPlanToBuy,
                DAT_GameState::ptr)(Commands::M_MAPPER_OXENBASE, playerID, FALSE)
            || DAT_BuildingsState::instance.unknownCountdown01 < 20) {
            return;
        }

        int const quarryID = DAT_GameState::instance.playerDataArray[playerID].highestLoadedQuarryUnk;
        MACRO_CALL_MEMBER(AIVState_Func::findSuitableGridLocationFittingCriteria, this)(
            (short)DAT_BuildingsState::instance.buildings[quarryID].x / 5
                + DAT_AIVDefinedData::instance
                    .OffsetsForFiveByFiveAreaSpotCheck[this->mapExtraInfo.algBuildingPlacementNudge % 9]
                    .x,
            (short)DAT_BuildingsState::instance.buildings[quarryID].y / 5
                + DAT_AIVDefinedData::instance
                    .OffsetsForFiveByFiveAreaSpotCheck[this->mapExtraInfo.algBuildingPlacementNudge % 9]
                    .y);
        if (this->buildingApproriateGridXPosition == -1) {
            return;
        }

        ++this->heatMaps[this->buildingApproriateGridXPosition][this->buildingAppropriateGridYPosition].structureCount;
        MACRO_CALL_MEMBER(Map::TileMapState_Func::placeBuilding, DAT_TileMapState::ptr)(playerID,
            this->buildingApproriateGridXPosition * 5, this->buildingAppropriateGridYPosition * 5,
            Commands::M_MAPPER_OXENBASE,
            MACRO_CALL_MEMBER(Map::TileMapState_Func::getBuildingSizeForCommandBuildingType, DAT_TileMapState::ptr)(
                Commands::M_MAPPER_OXENBASE),
            15);

        // link the new ox tether to the first free slot of the quarry
        int const oxTetherID = DAT_TileMapState::instance.placedBuildingID;
        for (int tetherIndex = 0; tetherIndex < 3; ++tetherIndex) {
            if (DAT_BuildingsState::instance.buildings[quarryID].quarryLinkedOxTethers[tetherIndex] == 0) {
                DAT_BuildingsState::instance.buildings[quarryID].quarryLinkedOxTethers[tetherIndex] = (short)oxTetherID;
                break;
            }
        }
        DAT_BuildingsState::instance.buildings[oxTetherID].oxtetherLinkedQuarryID = (short)quarryID;
    }

}
}
