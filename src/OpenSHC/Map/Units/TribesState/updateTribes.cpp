#include "../../../Map.func.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/AI/Tribes/AIVUnitTypeTribeArrayOffset.hpp"
#include "OpenSHC/Game/GameMode.hpp"

#include "OpenSHC/Globals/DAT_CurrentTribeID.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using Game::GameMode;

        // FUNCTION: STRONGHOLDCRUSADER 0x0052B860
        void TribesState::updateTribes()
        {
            short* psVar1;
            uint _tickBasedNumberUpTo32;
            _tickBasedNumberUpTo32 = DAT_GameCore::instance.mapTimeInTicks & 0x1f;
            DAT_GameState::instance.mapAndTime.eventCountdownRabbitInfestation
                = DAT_GameState::instance.mapAndTime.eventCountdownRabbitInfestation + -1;
            DAT_CurrentTribeID::instance = 1;
            do {
                if (this->tribes[DAT_CurrentTribeID::instance].tribeState == 2) {
                    if (0 < this->tribes[DAT_CurrentTribeID::instance].countdown2) {
                        this->tribes[DAT_CurrentTribeID::instance].countdown2
                            = this->tribes[DAT_CurrentTribeID::instance].countdown2 + -1;
                    }
                    if ((DAT_CurrentTribeID::instance & 0x1f) == _tickBasedNumberUpTo32) {
                        MACRO_CALL_MEMBER(Map::Units::TribesState_Func::computeTribePercentages, this)(
                            DAT_CurrentTribeID::instance);
                    }
                    if ((DAT_GameSynchronyState::instance
                                .currentPlayerFullIDArray[this->tribes[DAT_CurrentTribeID::instance].owner]
                            != -1)
                        || (DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SOLITARY)) {
                        /*
                          For humans, do:
                         */
                        switch (this->tribes[DAT_CurrentTribeID::instance].tribeType) {
                        case AI::Tribes::AITT_SWORDSMEN | AI::Tribes::AITT_SPEARMEN:
                            goto switchD_0052b92a_caseD_d;
                        case AI::Tribes::AITT_SWORDSMEN | AI::Tribes::AITT_PIKEMEN:
                            goto switchD_0052b92a_caseD_e;
                        case AI::Tribes::AITT_SWORDSMEN | AI::Tribes::AITT_CROSSBOWMEN:
                            goto switchD_0052b92a_caseD_f;
                        case ((AITribeType)0x10):
                            goto switchD_0052b92a_caseD_10;
                        default:
                            goto switchD_0052b92a_caseD_4;
                        }
                    }
                    switch (this->tribes[DAT_CurrentTribeID::instance].tribeType) {
                    case AI::Tribes::AITT_TUNNELERS:
                    case AI::Tribes::AITT_ARCHERS:
                    case AI::Tribes::AITT_LADDERMEN:
                    case AI::Tribes::AITT_SPEARMEN:
                    case AI::Tribes::AITT_PIKEMEN:
                    case AI::Tribes::AITT_CROSSBOWMEN:
                    case AI::Tribes::AITT_SWORDSMEN:
                    case AI::Tribes::AITT_MACEMEN:
                    case AI::Tribes::AITT_KNIGHTS:
                    case AI::Tribes::AITT_ENGINEERS:
                    case AI::Tribes::AITT_SWORDSMEN | AI::Tribes::AITT_LADDERMEN:
                    case ((AITribeType)0x13):
                    case ((AITribeType)0x14):
                    case ((AITribeType)0x15):
                    case ((AITribeType)0x16):
                    case ((AITribeType)0x17):
                    case ((AITribeType)0x18):
                    case ((AITribeType)0x19):
                    case ((AITribeType)0x1a):
                    case ((AITribeType)0x1b):
                    case ((AITribeType)0x1c):
                    case ((AITribeType)0x1d):
                    case AI::Tribes::OFFSET_CROSSBOWMAN:
                    case ((AITribeType)0x1f):
                        MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::updateTribeBehaviorBasedOnBehaviorType,
                            DAT_TroopValueState::ptr)(DAT_CurrentTribeID::instance);
                        break;
                    case AI::Tribes::AITT_SWORDSMEN | AI::Tribes::AITT_SPEARMEN:
                    switchD_0052b92a_caseD_d:
                        MACRO_CALL_MEMBER(Map::Units::TribesState_Func::processDeerMoving, this)(
                            DAT_CurrentTribeID::instance);
                        break;
                    case AI::Tribes::AITT_SWORDSMEN | AI::Tribes::AITT_PIKEMEN:
                    switchD_0052b92a_caseD_e:
                        MACRO_CALL_MEMBER(Map::Units::TribesState_Func::updateLionWolfTribeBehavior, this)(
                            DAT_CurrentTribeID::instance);
                        break;
                    case AI::Tribes::AITT_SWORDSMEN | AI::Tribes::AITT_CROSSBOWMEN:
                    switchD_0052b92a_caseD_f:
                        MACRO_CALL_MEMBER(Map::Units::TribesState_Func::updateRabbitTribeBehavior, this)(
                            DAT_CurrentTribeID::instance);
                        break;
                    case ((AITribeType)0x10):
                    switchD_0052b92a_caseD_10:
                        MACRO_CALL_MEMBER(Map::Units::TribesState_Func::updateCamelTribeBehavior, this)(
                            DAT_CurrentTribeID::instance);
                        break;
                    case ((AITribeType)0x11):
                        MACRO_CALL_MEMBER(Map::Units::TribesState_Func::markTribeAsAnimalTribe, this)(
                            DAT_CurrentTribeID::instance);
                        break;
                    case ((AITribeType)0x12):
                        MACRO_CALL_MEMBER(Map::Units::TribesState_Func::markTribeAsAnimalTribe, this)(
                            DAT_CurrentTribeID::instance);
                        break;
                    default:
                    switchD_0052b92a_caseD_4:
                        MACRO_CALL_MEMBER(Map::Units::TribesState_Func::updateTribeCombatStanceBehavior, this)(
                            DAT_CurrentTribeID::instance);
                    }
                    psVar1 = (short*)&this->tribes[DAT_CurrentTribeID::instance].countdown;
                    if (this->tribes[DAT_CurrentTribeID::instance].countdown != 0) {
                        *psVar1 = *psVar1 + -1;
                    }
                }
                DAT_CurrentTribeID::instance = DAT_CurrentTribeID::instance + 1;
                if (1250 < DAT_CurrentTribeID::instance) {}
            } while (true);
        }

    }
}
}
