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
        for (int playerID = 1; playerID < 9; playerID++) {
            if (DAT_GameState::instance.playerDataArray[playerID].aiType == OpenSHC::AI::AIT_NULL)
                continue;
            if (DAT_GameState::instance.playerDataArray[playerID].playerDeathRelated != 0)
                continue;
            if (DAT_GameState::instance.playerDataArray[playerID].lordKilledByPlayerID != 0)
                continue;
            int aicIndex = DAT_GameState::instance.playerDataArray[playerID].aiType - 1;

            if (DAT_GameState::instance.mapAndTime.dayTicks == playerID) {
                if (DAT_GameState::instance.mapAndTime.skirmishNoRushTicks == 0) {
                    MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::aiRecruitSortieRangedUnits, this)(playerID);
                    MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::aiRecruitSortieMeleeUnits, this)(playerID);
                    MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::aiRecruitUnits, this)(playerID);
                    MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::recruitHarrassingSiegeEngines, this)(playerID);
                    MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::aiAssignMoatDiggers, this)(playerID);
                    MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::aiCreateSiegeUnits, this)(playerID);
                    MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::aiRecruitEngineers, this)(playerID);
                }
                MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::aiBuyAndSellGoods, this)(playerID);
                MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::aiGiveRaidInstructions, this)(playerID);
            }

            if (DAT_GameState::instance.mapAndTime.weekTicks == playerID) {
                if (DAT_GameState::instance.mapAndTime.skirmishNoRushTicks == 0)
                    MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::aiRecruitEngineerForOilDuty, this)(playerID);
                MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::updateTribeLocations, this)(playerID);
                MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::updateAIPlayerState, this)(playerID);
                MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::aiUpdateTaxesAndRations, this)(playerID);
                MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::setFoodBuyPlan, this)(playerID);

                // on the month tick the strength update happens below, with the nervousness handling enabled
                if (DAT_GameState::instance.mapAndTime.monthTicks != playerID)
                    MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::updateAIStrengthState, this)(playerID, 0);

                if (DAT_GameState::instance.playerDataArray[playerID].aiRequestDelay != 0)
                    DAT_GameState::instance.playerDataArray[playerID].aiRequestDelay--;
                if (DAT_GameState::instance.playerDataArray[playerID].nervousBikCountdown != 0)
                    DAT_GameState::instance.playerDataArray[playerID].nervousBikCountdown--;
                if (DAT_GameState::instance.playerDataArray[playerID].someAiCountdown3 != 0)
                    DAT_GameState::instance.playerDataArray[playerID].someAiCountdown3--;
                if (DAT_GameState::instance.playerDataArray[playerID].someAiCountdown4 != 0)
                    DAT_GameState::instance.playerDataArray[playerID].someAiCountdown4--;
                if (DAT_GameState::instance.playerDataArray[playerID].someAiCountdown5 != 0)
                    DAT_GameState::instance.playerDataArray[playerID].someAiCountdown5--;
                if (DAT_GameState::instance.playerDataArray[playerID].someAiCountdown6 != 0)
                    DAT_GameState::instance.playerDataArray[playerID].someAiCountdown6--;
            }

            if (DAT_GameState::instance.mapAndTime.monthTicks == playerID) {
                MACRO_CALL_MEMBER(
                    OpenSHC::Map::TileMapState_Func::countMoatsOwnedByEachPlayer, DAT_TileMapState::ptr)();
                MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::instructTribe166ToMove, this)(playerID);
                MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::giveMoveCommandToSortieUnits, this)(playerID);
                MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::updateAIStrengthState, this)(playerID, 1);
                MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::selectAttackTarget, this)(playerID);

                if (DAT_GameState::instance.playerDataArray[playerID].aiRecruitUnitChoiceState
                    == OpenSHC::AI::AIRUC_RAIDING) {
                    DAT_GameState::instance.playerDataArray[playerID].canStartSpending = 1;
                } else {
                    // only spend on recruiting while gold is above the AIC's threshold
                    DAT_GameState::instance.playerDataArray[playerID].canStartSpending
                        = DAT_GameState::instance.playerDataArray[playerID].currentResources[0xf]
                        > this->aics[aicIndex].recruitGoldThreshold;
                }
            }
        }
    }

}
}
