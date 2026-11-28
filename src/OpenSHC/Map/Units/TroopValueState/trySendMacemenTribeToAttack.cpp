#include "../TroopValueState.func.hpp"

#include "OpenSHC/Map.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Map/Units/Behavior/UnitStanceEnum.hpp"
#include "OpenSHC/Map/Units/Instructions/UnitMatchSpeedEnum.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0051CF90
        void TroopValueState::trySendMacemenTribeToAttack()
        {
            int const playerID = DAT_TroopValueState::instance.attackInfo.playerID_0x2c850;
            if (DAT_TroopValueState::instance.attackInfo.macemenTribeCount <= 0
                || DAT_TroopValueState::instance.attackInfo.attackInfoTickWrapCount < 4
                || (SEC_RNG::instance.currentNumber2 & 7)) {
                return;
            }
            BOOLEnum const isNotCampaignMission = DAT_GameCore::instance.gameMode_2 != Game::GM_CAMPAIGN_MISSION;
            --DAT_TroopValueState::instance.attackInfo.macemenTribeCount;
            int const macemenTribeID
                = DAT_TroopValueState::instance.attackInfo
                      .macemenTribeArray[DAT_TroopValueState::instance.attackInfo.macemenTribeCount];
            DAT_TribesState::instance.tribes[macemenTribeID].unitStance = Map::Units::Behavior::USE_AGGRESSIVE;
            if (isNotCampaignMission || 15 <= DAT_GameCore::instance.missionNumber1to20) {
                int const unitID = MACRO_CALL_MEMBER(
                    Map::Units::UnitsState_Func::getLivingSelectableUnit, DAT_UnitsState::ptr)(playerID);
                MACRO_CALL_MEMBER(Map::Units::TribesState_Func::giveTribeMoveInstruction, DAT_TribesState::ptr)(
                    macemenTribeID, DAT_UnitsState::instance.units[unitID].x, DAT_UnitsState::instance.units[unitID].y,
                    0, 0, Map::Units::Instructions::UMSE_0);
            }
        }

    }
}
}
