#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/AI/AITypeA.hpp"
#include "OpenSHC/AI/Tribes/AITribeType.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/Units/Behavior/UnitStanceEnum.hpp"
#include "OpenSHC/Map/Units/SomeTribeBehaviorType.hpp"
#include "OpenSHC/Map/Units/UnitInstructionType.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004D2500
    void AICState::aiRecruitEngineerForOilDuty(int playerID)
    {
        if (DAT_GameState::instance.playerDataArray[playerID].aiType == AITA_NULL)
            return;
        int guildID = DAT_GameState::instance.playerDataArray[playerID].engineersGuild.id;
        if (DAT_GameState::instance.playerDataArray[playerID].canStartSpending == 0)
            return;
        if (DAT_GameState::instance.playerDataArray[playerID].currentResources[Game::Resources::RT_GOLD] < 30)
            return;
        if (guildID <= 0)
            return;
        if (DAT_BuildingsState::instance.buildings[guildID].buildingType != Map::Buildings::BT_ENGINEERSGUILD)
            return;
        int smelterID = DAT_GameState::instance.playerDataArray[playerID].oilSmelter.id;
        if (smelterID <= 0)
            return;
        if (DAT_BuildingsState::instance.buildings[smelterID].buildingType != Map::Buildings::BT_OILSMELTER)
            return;
        int amount = DAT_GameState::instance.playerDataArray[playerID].aivUnitLocationSlotLocationCount[1] + 1;
        if (amount <= 1)
            return;

        if (DAT_BuildingsState::instance.buildings[smelterID].resources[Game::Resources::RT_PITCH] <= 0
            && DAT_GameState::instance.playerDataArray[playerID].currentResources[Game::Resources::RT_PITCH] <= 0) {
            DAT_GameState::instance.playerDataArray[playerID].resourcesToAcquireArray[Game::Resources::RT_PITCH] = 4;
            return;
        }
        if (MACRO_CALL_MEMBER(AICState_Func::checksAndGenerateAITribesForPlayerIfNotExisting, this)(playerID, amount, TRUE)
            == FALSE)
            return;

        int tribeID
            = MACRO_CALL_MEMBER(AICState_Func::checksAndGenerateAITribesForPlayerIfNotExisting, this)(playerID, amount, FALSE);
        int unitID = MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::nonEuroRecruit, DAT_UnitsState::ptr)(
            Map::Units::UT_E_ENGINEER, DAT_GameState::instance.playerDataArray[playerID].engineersGuild.id, playerID, 0);
        MACRO_CALL_MEMBER(Map::Units::TribesState_Func::addUnitToTribe, DAT_TribesState::ptr)(unitID, tribeID);
        if (unitID == 0)
            return;

        DAT_UnitsState::instance.units[unitID].engineerRelatedUnk = 1;
        DAT_TribesState::instance.tribes[tribeID].unitStance = Map::Units::Behavior::USE_DEFENSIVE;
        DAT_TribesState::instance.tribes[tribeID].tribeType = Tribes::AITT_ENGINEERS;
        DAT_TribesState::instance.tribes[tribeID].tribeBehaviorType = Map::Units::STBT_0x41d;
        MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::relayTribeInstruction, DAT_UnitsState::ptr)(tribeID,
            Map::Units::UIT_CONSTRUCT_SIEGE_EQUIPMENTOIL_DUTYENGINEERRELATED, smelterID,
            DAT_BuildingsState::instance.buildings[smelterID].uid, 0);
    }
}
}
