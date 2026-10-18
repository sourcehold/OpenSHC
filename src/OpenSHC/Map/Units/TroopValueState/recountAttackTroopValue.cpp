#include "../TroopValueState.func.hpp"

#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map.func.hpp"
#include "OpenSHC/AI/Tribes/AITribeType.hpp"
#include "OpenSHC/AI/Tribes/AIVUnitTypeTribeArrayOffset.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using AI::Tribes::AITribeType;
        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0051FB90
        void TroopValueState::recountAttackTroopValue(int param_1)
        {
            int counter = 0x10;
            if (!param_1) {
                counter = DAT_TroopValueState::instance.attackInfo.counter;
            }
            DAT_TroopValueState::instance.attackInfo.counter = counter + 1;
            if (16 <= DAT_TroopValueState::instance.attackInfo.counter) {
                DAT_TroopValueState::instance.attackInfo.counter = 0;
                MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                    sizeof(DAT_TroopValueState::instance.attackInfo.aiTribeSizesPerTribeType), '\0',
                    (void*)((int)(&DAT_TroopValueState::instance.attackInfo.aiTribeSizesPerTribeType)));
                DAT_TroopValueState::instance.attackInfo.lowTroopValueRelated = 0;
                DAT_TroopValueState::instance.attackInfo.size = 0;
                DAT_TroopValueState::instance.attackInfo.aiTroops = 0;
                DAT_TroopValueState::instance.attackInfo.attackTribeCount = 0;
                DAT_TroopValueState::instance.attackInfo.spearmenAndMacemen = 0;
                DAT_TroopValueState::instance.attackInfo.pikemenSwordsmenAndMore = 0;
                DAT_TroopValueState::instance.attackInfo.engineers = 0;
                DAT_TroopValueState::instance.attackInfo.laddermen = 0;
                DAT_TroopValueState::instance.attackInfo.assassinTribeCount = 0;
                DAT_TroopValueState::instance.attackInfo.catapults = 0;
                DAT_TroopValueState::instance.attackInfo.knights = 0;
                DAT_TroopValueState::instance.attackInfo.ranged = 0;
                for (int _tribeID = 1; _tribeID < 1250; _tribeID = _tribeID + 1) {
                    if (DAT_TribesState::instance.tribes[_tribeID].tribeState) {
                        BOOLEnum fullIDIsMinus1
                            = MACRO_CALL_MEMBER(Game::GameStateStructures_Func::isFullIDEqualsToMinus1,
                                DAT_GameState::ptr)(DAT_TribesState::instance.tribes[_tribeID].owner);
                        if (!fullIDIsMinus1) {
                            if (DAT_TribesState::instance.tribes[_tribeID].owner
                                == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                                DAT_TroopValueState::instance.attackInfo.size
                                    = DAT_TroopValueState::instance.attackInfo.size
                                    + DAT_TribesState::instance.tribes[_tribeID].size;
                            }
                        } else {
                            AITribeTypeShort _tribeType = DAT_TribesState::instance.tribes[_tribeID].tribeType;
                            int _size = DAT_TribesState::instance.tribes[_tribeID].size;
                            ((int*)&DAT_TroopValueState::instance.attackInfo
                                    .aiTribeSizesPerTribeType)[(short)_tribeType]
                                = ((int*)&DAT_TroopValueState::instance.attackInfo
                                          .aiTribeSizesPerTribeType)[(short)_tribeType]
                                + _size;
                            if (_tribeType == AI::Tribes::AITT_ENGINEERS) {
                                DAT_TroopValueState::instance.attackInfo.engineers
                                    = DAT_TroopValueState::instance.attackInfo.engineers + 1;
                            } else if (_tribeType == AI::Tribes::AITT_LADDERMEN) {
                                DAT_TroopValueState::instance.attackInfo.laddermen
                                    = DAT_TroopValueState::instance.attackInfo.laddermen + 1;
                            } else if (_tribeType != (AITribeType)0x13 && _tribeType != (AITribeType)0x14
                                && _tribeType != (AITribeType)0x15) {
                                if (_tribeType == (AITribeType)0x16) {
                                    if (0 < DAT_UnitsState::instance
                                            .units[DAT_TribesState::instance.tribes[_tribeID].selectionTargetUnitID]
                                            .stoneAmmunition) {
                                        DAT_TroopValueState::instance.attackInfo.catapults
                                            = DAT_TroopValueState::instance.attackInfo.catapults + 1;
                                    }
                                } else if (_tribeType == (AITribeType)0x17) {
                                    if (0 < DAT_UnitsState::instance
                                            .units[DAT_TribesState::instance.tribes[_tribeID].selectionTargetUnitID]
                                            .stoneAmmunition) {
                                        DAT_TroopValueState::instance.attackInfo.catapults
                                            = DAT_TroopValueState::instance.attackInfo.catapults + 1;
                                    }
                                } else if (_tribeType != AI::Tribes::AITT_TUNNELERS
                                    && ((short)_tribeType < 0xd || (0x19 <= (short)_tribeType))) {
                                    DAT_TroopValueState::instance.attackInfo.aiTroops
                                        = DAT_TroopValueState::instance.attackInfo.aiTroops + _size;
                                    DAT_TroopValueState::instance.attackInfo.attackTribeCount
                                        = DAT_TroopValueState::instance.attackInfo.attackTribeCount + 1;
                                    if (_tribeType == AI::Tribes::AITT_SPEARMEN) {
                                        DAT_TroopValueState::instance.attackInfo.spearmenAndMacemen
                                            = DAT_TroopValueState::instance.attackInfo.spearmenAndMacemen + 1;
                                    } else if (_tribeType == AI::Tribes::AITT_MACEMEN) {
                                        DAT_TroopValueState::instance.attackInfo.spearmenAndMacemen
                                            = DAT_TroopValueState::instance.attackInfo.spearmenAndMacemen + 1;
                                    } else if (_tribeType == (AITribeType)0x1a) {
                                        DAT_TroopValueState::instance.attackInfo.assassinTribeCount
                                            = DAT_TroopValueState::instance.attackInfo.assassinTribeCount + 1;
                                    } else if (_tribeType == AI::Tribes::AITT_PIKEMEN) {
                                        DAT_TroopValueState::instance.attackInfo.pikemenSwordsmenAndMore
                                            = DAT_TroopValueState::instance.attackInfo.pikemenSwordsmenAndMore + 1;
                                    } else if (_tribeType == AI::Tribes::AITT_SWORDSMEN) {
                                        DAT_TroopValueState::instance.attackInfo.pikemenSwordsmenAndMore
                                            = DAT_TroopValueState::instance.attackInfo.pikemenSwordsmenAndMore + 1;
                                    } else if (_tribeType == AI::Tribes::OFFSET_CROSSBOWMAN) {
                                        DAT_TroopValueState::instance.attackInfo.pikemenSwordsmenAndMore
                                            = DAT_TroopValueState::instance.attackInfo.pikemenSwordsmenAndMore + 1;
                                    } else if (_tribeType == (AITribeType)0x1c) {
                                        DAT_TroopValueState::instance.attackInfo.pikemenSwordsmenAndMore
                                            = DAT_TroopValueState::instance.attackInfo.pikemenSwordsmenAndMore + 1;
                                    } else if (_tribeType == AI::Tribes::AITT_KNIGHTS) {
                                        DAT_TroopValueState::instance.attackInfo.knights
                                            = DAT_TroopValueState::instance.attackInfo.knights + 1;
                                    } else if (_tribeType
                                        == (AI::Tribes::AITT_SWORDSMEN | AI::Tribes::AITT_LADDERMEN)) {
                                        DAT_TroopValueState::instance.attackInfo.pikemenSwordsmenAndMore
                                            = DAT_TroopValueState::instance.attackInfo.pikemenSwordsmenAndMore + 1;
                                    } else if (_tribeType == AI::Tribes::AITT_ARCHERS
                                        || _tribeType == AI::Tribes::AITT_CROSSBOWMEN || _tribeType == (AITribeType)0x19
                                        || _tribeType == (AITribeType)0x1d || _tribeType == (AITribeType)0x1b
                                        || _tribeType == (AITribeType)0x1f) {
                                        DAT_TroopValueState::instance.attackInfo.ranged
                                            = DAT_TroopValueState::instance.attackInfo.ranged + 1;
                                    }
                                }
                            }
                        }
                    }
                }
                if (DAT_TroopValueState::instance.attackInfo.knights) {
                    if (DAT_TroopValueState::instance.attackInfo.spearmenAndMacemen) {
                        DAT_TroopValueState::instance.attackInfo.knights = 0;
                    }
                    if (DAT_TroopValueState::instance.attackInfo.pikemenSwordsmenAndMore) {
                        DAT_TroopValueState::instance.attackInfo.knights = 0;
                    }
                }
                int _limit = 6;
                if (!DAT_GameState::instance.mapAndTime.difficulty) {
                    _limit = 3;
                }
                if ((DAT_TroopValueState::instance.attackInfo.aiTroops <= 0)
                    || (DAT_TroopValueState::instance.attackInfo.attackTribeCount <= 0)) {
                    DAT_TroopValueState::instance.attackInfo.lowTroopValueRelated = 1;
                }
                if ((DAT_TroopValueState::instance.attackInfo.size
                        > DAT_TroopValueState::instance.attackInfo.aiTroops * 3)
                    && (DAT_TroopValueState::instance.attackInfo.aiTroops < _limit)) {
                    MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::recountTotalTroopValue, this)();
                    if (DAT_TroopValueState::instance.attackInfo.playerTotalTroopValueArray[5]
                            + DAT_TroopValueState::instance.attackInfo.playerTotalTroopValueArray[4]
                            + DAT_TroopValueState::instance.attackInfo.playerTotalTroopValueArray[3]
                            + DAT_TroopValueState::instance.attackInfo.playerTotalTroopValueArray[2]
                        < 30) {
                        DAT_TroopValueState::instance.attackInfo.lowTroopValueRelated = 1;
                    }
                }
            }
        }

    }
}
}
