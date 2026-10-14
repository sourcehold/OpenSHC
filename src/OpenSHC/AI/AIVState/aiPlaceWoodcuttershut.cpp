#include "../AIVState.func.hpp"

#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004EFAB0
    void AIVState::aiPlaceWoodcuttershut(int playerID)
    {
        if (!MACRO_CALL_MEMBER(Game::GameStateStructures_Func::checkRequiredResourcesForBuildingOrPlanToBuy,
                DAT_GameState::ptr)(Commands::M_MAPPER_WOODSMAN, playerID, FALSE)
            || DAT_BuildingsState::instance.unknownCountdown01 < 20) {
            return;
        }
        MACRO_CALL_MEMBER(AIVState_Func::findAppropriateWoodCutterGridLocation, this)(playerID);
        if (this->buildingApproriateGridXPosition == -1) {
            return;
        }
        this->heatMaps[this->buildingApproriateGridXPosition][this->buildingAppropriateGridYPosition]
            .woodRelatedCountdownTo0 = 4;
        // search around the result of the woodcutter search
        MACRO_CALL_MEMBER(AIVState_Func::findSuitableGridLocationFittingCriteria, this)(
            this->buildingApproriateGridXPosition, this->buildingAppropriateGridYPosition);
        if (this->buildingApproriateGridXPosition == -1) {
            return;
        }
        ++this->heatMaps[this->buildingApproriateGridXPosition][this->buildingAppropriateGridYPosition].structureCount;
        MACRO_CALL_MEMBER(Map::TileMapState_Func::placeBuilding, DAT_TileMapState::ptr)(playerID,
            this->buildingApproriateGridXPosition * 5, this->buildingAppropriateGridYPosition * 5,
            Commands::M_MAPPER_WOODSMAN,
            MACRO_CALL_MEMBER(Map::TileMapState_Func::getBuildingSizeForCommandBuildingType, DAT_TileMapState::ptr)(
                Commands::M_MAPPER_WOODSMAN),
            15);
    }

}
}
