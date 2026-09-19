#include "OpenSHC/AI/AIVState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/AI/AICState.hpp"
#include "OpenSHC/AI/AITypeA.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"

#include "OpenSHC/Globals/DAT_AIVState.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004CB890
    BOOLEnum AICState::shouldDestroyWoodCutterUnk(int playerID)
    {
        if (DAT_GameState::instance.playerDataArray[playerID].aiType == AITA_NULL) {
            return FALSE;
        }

        int buildingID;
        if (DAT_AIVState::instance.mapExtraInfo.totalWoodAvailable <= 0) {
            buildingID = MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::findFirstBuildingIDForPlayerAndType,
                DAT_BuildingsState::ptr)(playerID, Map::Buildings::BT_WOODCUTTERSHUT);
        } else {
            if (DAT_GameState::instance.playerDataArray[playerID].currentResources[Game::Resources::RT_WOOD] <= 20) {
                return FALSE;
            }
            if (DAT_GameState::instance.playerDataArray[playerID].noLabourerBuildingCount < 2) {
                return FALSE;
            }
            if (DAT_GameState::instance.playerDataArray[playerID].someCount10 < 25) {
                return FALSE;
            }
            buildingID = DAT_GameState::instance.playerDataArray[playerID].someCount11;
        }

        if (buildingID != 0) {
            MACRO_CALL_MEMBER(AIVState_Func::resetCountdownInHeatMap, DAT_AIVState::ptr)(
                (short)DAT_BuildingsState::instance.buildings[buildingID].x,
                (short)DAT_BuildingsState::instance.buildings[buildingID].y);
            MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::giveBackResourceForDestroyedBuilding,
                DAT_BuildingsState::ptr)(buildingID, playerID, 50);
            MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::destroyBuilding, DAT_BuildingsState::ptr)(
                buildingID);
            return TRUE;
        }
        return FALSE;
    }
}
}
