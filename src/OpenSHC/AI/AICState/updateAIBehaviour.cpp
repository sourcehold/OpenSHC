#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/AI/AIRecruitUnitChoice.hpp"
#include "OpenSHC/AI/AIType.hpp"
#include "OpenSHC/AI/AITypeInt.hpp"
#include "OpenSHC/Game/Player/PlayerData.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace AI {

    using OpenSHC::AI::AIRecruitUnitChoice;
    using OpenSHC::AI::AIType;
    using OpenSHC::AI::AITypeInt;
    using OpenSHC::Game::Player::PlayerData;

    // FUNCTION: STRONGHOLDCRUSADER 0x004D53E0
    void AICState::updateAIBehaviour()
    {
        if (DAT_GameState::instance.mapAndTime.dayTicks == 10) {
            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::makeOutpostTribesAttack, this)();
        }

        for (int _playerID = 1; _playerID < 9; _playerID++) {
            // Compiler doesn't optimize it with ADJ() like it should, not sure why it doesn't do it.
            PlayerData* const _pPlayerData = &DAT_GameState::instance.playerDataArray[_playerID];
            AITypeInt const _aiType = _pPlayerData->aiType;

            if (_aiType == OpenSHC::AI::AIT_NULL)
                continue;
            if (_pPlayerData->playerDeathRelated != 0)
                continue;
            if (_pPlayerData->lordKilledByPlayerID != 0)
                continue;

            if (DAT_GameState::instance.mapAndTime.dayTicks == _playerID) {
                if (DAT_GameState::instance.mapAndTime.totalNoRushTicks == 0) {
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
                if (DAT_GameState::instance.mapAndTime.totalNoRushTicks == 0) {
                    MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::aiRecruitEngineerForOilDuty, this)(_playerID);
                }
                MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::updateTribeLocations, this)(_playerID);
                MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::updateAIPlayerState, this)(_playerID);
                MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::aiUpdateTaxesAndRations, this)(_playerID);
                MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::setFoodBuyPlan, this)(_playerID);

                if (DAT_GameState::instance.mapAndTime.monthTicks != _playerID) {
                    MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::updateAIStrengthState, this)(_playerID, 0);
                }

                if (_pPlayerData->aiRequestDelay != 0) {
                    _pPlayerData->aiRequestDelay -= 1;
                }
                if (_pPlayerData->nervousBikCountdown != 0) {
                    _pPlayerData->nervousBikCountdown -= 1;
                }
                if (_pPlayerData->someAiCountdown3 != 0) {
                    _pPlayerData->someAiCountdown3 -= 1;
                }
                if (_pPlayerData->someAiCountdown4 != 0) {
                    _pPlayerData->someAiCountdown4 -= 1;
                }
                if (_pPlayerData->someAiCountdown5 != 0) {
                    _pPlayerData->someAiCountdown5 -= 1;
                }
                if (_pPlayerData->someAiCountdown6 != 0) {
                    _pPlayerData->someAiCountdown6 -= 1;
                }
            }

            if (DAT_GameState::instance.mapAndTime.monthTicks == _playerID) {
                MACRO_CALL_MEMBER(
                    OpenSHC::Map::TileMapState_Func::countMoatsOwnedByEachPlayer, DAT_TileMapState::ptr)();
                MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::instructTribe166ToMove, this)(_playerID);
                MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::giveMoveCommandToSortieUnits, this)(_playerID);
                MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::updateAIStrengthState, this)(_playerID, 1);
                MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::selectAttackTarget, this)(_playerID);

                if (_pPlayerData->aiRecruitUnitChoiceState == OpenSHC::AI::AIRUC_RAIDING) {
                    _pPlayerData->canStartSpending = 1;
                } else {
                    // shouldSpend = recruitGoldThreshold < currentGold
                    _pPlayerData->canStartSpending = (uint)(((int)this->aics[_aiType - 1].recruitGoldThreshold)
                        < _pPlayerData->currentResources[0xf]);
                }
            }
        }
    }

}
}
