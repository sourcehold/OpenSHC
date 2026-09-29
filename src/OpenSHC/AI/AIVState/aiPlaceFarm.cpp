#include "../AIVState.func.hpp"

#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004EFA60
    BOOLEnum AIVState::aiPlaceFarm(int playerID, MappersEnum buildingType)
    {
        // despite its declared type, buildingType holds a BuildingType
        if (buildingType <= 0) {
            return FALSE;
        }
        if (!MACRO_CALL_MEMBER(
                Game::GameStateStructures_Func::checkRequiredResourcesForBuildingOrPlanToBuy, DAT_GameState::ptr)(
                MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::convertBuildingTypeToCommandBuildingType,
                    DAT_BuildingsState::ptr)((Map::Buildings::BuildingType)buildingType),
                playerID, FALSE)) {
            return FALSE;
        }
        return MACRO_CALL_MEMBER(AIVState_Func::findSuitableFarmLocationAndPlaceFarm, this)(playerID, buildingType)
            != 0;
    }

}
}
