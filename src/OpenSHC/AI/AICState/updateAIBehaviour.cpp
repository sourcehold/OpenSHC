#include "../AICState.func.hpp"

#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/AI/AIRecruitUnitChoice.hpp"
#include "OpenSHC/AI/AIType.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace AI {

    using OpenSHC::AI::AIRecruitUnitChoice;
    using OpenSHC::AI::AIType;

    // FUNCTION: STRONGHOLDCRUSADER 0x004D53E0
    void AICState::updateAIBehaviour()
    {
        if (DAT_GameState::instance.mapAndTime.dayTicks == 10)
            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::makeOutpostTribesAttack, this)();

        // every AI gets its own tick of the day, week and month, so the work is spread out
        for (int _playerID = 1; _playerID < 9; _playerID++) {
            if (DAT_GameState::instance.playerDataArray[_playerID].aiType == OpenSHC::AI::AIT_NULL)
                continue;
            if (DAT_GameState::instance.playerDataArray[_playerID].playerDeathRelated != 0)
                continue;
            if (DAT_GameState::instance.playerDataArray[_playerID].lordKilledByPlayerID != 0)
                continue;
            int _aicIndex = DAT_GameState::instance.playerDataArray[_playerID].aiType - 1;

            if (DAT_GameState::instance.mapAndTime.dayTicks == _playerID) {
                if (DAT_GameState::instance.mapAndTime.skirmishNoRushTicks == 0) {
                    MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::aiRecruitSortieRangedUnits, this)(_playerID);
                    MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::aiRecruitSortieMeleeUnits, this)(_playerID);
                    MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::aiRecruitUnits, this)(_playerID);
                    MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::recruitHarrassingSiegeEngines, this)(_playerID);
                    MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::aiAssignMoatDiggers, this)(_playerID);
                    MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::aiCreateSiegeUnits, this)(_playerID);
                    MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::aiRecruitEngineers, this)(_playerID);
                }
                MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::aiBuyAndSellGoods, this)(_playerID);
                MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::aiGiveRaidInstructions, this)(_playerID);
            }

            if (DAT_GameState::instance.mapAndTime.weekTicks == _playerID) {
                if (DAT_GameState::instance.mapAndTime.skirmishNoRushTicks == 0)
                    MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::aiRecruitEngineerForOilDuty, this)(_playerID);
                MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::updateTribeLocations, this)(_playerID);
                MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::updateAIPlayerState, this)(_playerID);
                MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::aiUpdateTaxesAndRations, this)(_playerID);
                MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::setFoodBuyPlan, this)(_playerID);

                // on the month tick the strength update happens below, with the nervousness handling enabled
                if (DAT_GameState::instance.mapAndTime.monthTicks != _playerID)
                    MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::updateAIStrengthState, this)(_playerID, 0);

                if (DAT_GameState::instance.playerDataArray[_playerID].aiRequestDelay != 0)
                    DAT_GameState::instance.playerDataArray[_playerID].aiRequestDelay--;
                if (DAT_GameState::instance.playerDataArray[_playerID].nervousBikCountdown != 0)
                    DAT_GameState::instance.playerDataArray[_playerID].nervousBikCountdown--;
                if (DAT_GameState::instance.playerDataArray[_playerID].someAiCountdown3 != 0)
                    DAT_GameState::instance.playerDataArray[_playerID].someAiCountdown3--;
                if (DAT_GameState::instance.playerDataArray[_playerID].someAiCountdown4 != 0)
                    DAT_GameState::instance.playerDataArray[_playerID].someAiCountdown4--;
                if (DAT_GameState::instance.playerDataArray[_playerID].someAiCountdown5 != 0)
                    DAT_GameState::instance.playerDataArray[_playerID].someAiCountdown5--;
                if (DAT_GameState::instance.playerDataArray[_playerID].someAiCountdown6 != 0)
                    DAT_GameState::instance.playerDataArray[_playerID].someAiCountdown6--;
            }

            if (DAT_GameState::instance.mapAndTime.monthTicks == _playerID) {
                MACRO_CALL_MEMBER(
                    OpenSHC::Map::TileMapState_Func::countMoatsOwnedByEachPlayer, DAT_TileMapState::ptr)();
                MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::instructTribe166ToMove, this)(_playerID);
                MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::giveMoveCommandToSortieUnits, this)(_playerID);
                MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::updateAIStrengthState, this)(_playerID, 1);
                MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::selectAttackTarget, this)(_playerID);

                if (DAT_GameState::instance.playerDataArray[_playerID].aiRecruitUnitChoiceState
                    == OpenSHC::AI::AIRUC_RAIDING) {
                    DAT_GameState::instance.playerDataArray[_playerID].canStartSpending = 1;
                } else {
                    // only spend on recruiting while gold is above the AIC's threshold
                    DAT_GameState::instance.playerDataArray[_playerID].canStartSpending
                        = DAT_GameState::instance.playerDataArray[_playerID].currentResources[0xf]
                        > this->aics[_aicIndex].recruitGoldThreshold;
                }
            }
        }
    }

}
}
