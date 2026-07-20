#include "OpenSHC/AI/AICState.hpp"
#include "OpenSHC/AI/AITypeA.hpp"

#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004CC520
    void AICState::aiRecruitEngineers(int playerID)
    {
        int recruitmentBuilding;
        int _aiType = DAT_GameState::instance.playerDataArray[playerID].aiType;
        if ((((_aiType != AITA_NULL) &&
            (DAT_GameState::instance.playerDataArray[playerID].isEngineerRequired != FALSE)) &&
            (DAT_GameState::instance.playerDataArray[playerID].canStartSpending != 0)) &&
            (((0x1d < (int)this->aics[_aiType - 1].recruitGoldThreshold + DAT_GameState::instance.playerDataArray[playerID].currentResources[0xf] &&
            (recruitmentBuilding = DAT_GameState::instance.playerDataArray[playerID].engineersGuild.id,
            0 < recruitmentBuilding)) &&
            (DAT_BuildingsState::instance.buildings[recruitmentBuilding].buildingType == Map::Buildings::BT_ENGINEERSGUILD)))) {
            MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::nonEuroRecruit, DAT_UnitsState::ptr)(Map::Units::UT_E_ENGINEER, recruitmentBuilding, playerID, 0);
            DAT_GameState::instance.playerDataArray[playerID].isEngineerRequired = FALSE;
        }
    }
}
}
