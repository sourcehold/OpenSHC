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

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000 */

    // FUNCTION: STRONGHOLDCRUSADER 0x004D53E0
    void AICState ::updateAIBehaviour()

    {

        AITypeInt AVar1;

        PlayerData* _aiType;

        int _playerID;

        if (DAT_GameState::instance.mapAndTime.dayTicks == 10) {

            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::makeOutpostTribesAttack, this)();
        }

        _aiType = &DAT_GameState::instance.playerDataArray[1];

        _playerID = 1;

        do {

            AVar1 = _aiType->aiType;

            if (((AVar1 != OpenSHC::AI::AIT_NULL) && (_aiType->playerDeathRelated == 0))
                && (_aiType->lordKilledByPlayerID == 0)) {

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

                    if (_aiType->aiRequestDelay != 0) {

                        _aiType->aiRequestDelay = _aiType->aiRequestDelay + -1;
                    }

                    if (_aiType->nervousBikCountdown != 0) {

                        _aiType->nervousBikCountdown = _aiType->nervousBikCountdown + -1;
                    }

                    if (_aiType->someAiCountdown3 != 0) {

                        _aiType->someAiCountdown3 = _aiType->someAiCountdown3 + -1;
                    }

                    if (_aiType->someAiCountdown4 != 0) {

                        _aiType->someAiCountdown4 = _aiType->someAiCountdown4 + -1;
                    }

                    if (_aiType->someAiCountdown5 != 0) {

                        _aiType->someAiCountdown5 = _aiType->someAiCountdown5 + -1;
                    }

                    if (_aiType->someAiCountdown6 != 0) {

                        _aiType->someAiCountdown6 = _aiType->someAiCountdown6 + -1;
                    }
                }

                if (DAT_GameState::instance.mapAndTime.monthTicks == _playerID) {

                    MACRO_CALL_MEMBER(
                        OpenSHC::Map::TileMapState_Func::countMoatsOwnedByEachPlayer, DAT_TileMapState::ptr)();

                    MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::instructTribe166ToMove, this)(_playerID);

                    MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::giveMoveCommandToSortieUnits, this)(_playerID);

                    MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::updateAIStrengthState, this)(_playerID, 1);

                    MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::selectAttackTarget, this)(_playerID);

                    if (_aiType->aiRecruitUnitChoiceState == OpenSHC::AI::AIRUC_RAIDING) {

                        _aiType->canStartSpending = 1;

                    }

                    else {

                        /*
                                    shouldSpend = recruitGoldTreshold < currentGold */

                        _aiType->canStartSpending
                            = (uint)(*(int*)((int)this + (AVar1 + ~OpenSHC::AI::AIT_NULL) * 0x2a4 + 0xc4)
                                < _aiType->currentResources[0xf]);
                    }
                }
            }

            _aiType = _aiType + 0xe7d;

            _playerID = _playerID + 1;

        } while ((int)_aiType < 0x117ea8c);

        return;
    }

}
}
