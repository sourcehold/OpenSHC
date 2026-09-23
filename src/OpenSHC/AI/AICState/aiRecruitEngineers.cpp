#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/AI/AICState.hpp"
#include "OpenSHC/AI/AITypeA.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004CC520
    void AICState::aiRecruitEngineers(int playerID)
    {
        int aiType = DAT_GameState::instance.playerDataArray[playerID].aiType;
        if (aiType == AITA_NULL)
            return;
        if (DAT_GameState::instance.playerDataArray[playerID].isEngineerRequired == FALSE)
            return;
        if (DAT_GameState::instance.playerDataArray[playerID].canStartSpending == 0)
            return;
        if (this->aics[aiType - 1].recruitGoldThreshold
                + DAT_GameState::instance.playerDataArray[playerID].currentResources[Game::Resources::RT_GOLD]
            < 30)
            return;
        int guildID = DAT_GameState::instance.playerDataArray[playerID].engineersGuild.id;
        if (guildID <= 0)
            return;
        if (DAT_BuildingsState::instance.buildings[guildID].buildingType != Map::Buildings::BT_ENGINEERSGUILD)
            return;

        MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::nonEuroRecruit, DAT_UnitsState::ptr)(
            Map::Units::UT_E_ENGINEER, guildID, playerID, 0);
        DAT_GameState::instance.playerDataArray[playerID].isEngineerRequired = FALSE;
    }
}
}
