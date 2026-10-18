#include "OpenSHC/Map.func.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/AI/Tribes/AITribeType.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using AI::Tribes::AITribeType;
        using Map::Units::UnitLogicState;
        using Map::Units::UnitType;
        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0051CCB0
        void TroopValueState::assignMacemenAndKnightsNotFromPlayer1ToTribes()
        {
            BOOLEnum isAIPlayerWithKeep;
            int _tribeID1;
            int _tribeID2;
            Unit* _pUnit2;
            int _knightCount;
            int _macemenLimit;
            int _tribeIndex;
            int _knightLimit;
            int _limitCounter;
            int const playerID = DAT_TroopValueState::instance.attackInfo.pitchRelatedPlayerID;
            uint _unitID0 = 1;
            int _macemenCount = 0;
            _knightCount = 0;
            if (1 < DAT_UnitsState::instance.maxUnitCount) {
                _pUnit2 = &DAT_UnitsState::instance.units[1];
                do {
                    if (_pUnit2->logicalState != Map::Units::ULS_INVISIBLE
                        && (isAIPlayerWithKeep
                            = MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::getPlayerNot1AndHasKeep,
                                DAT_TroopValueState::ptr)((int)_pUnit2->owner),
                            isAIPlayerWithKeep)) {
                        if (_pUnit2->unitType == Map::Units::UT_E_MACE) {
                            _macemenCount = _macemenCount + 1;
                            MACRO_CALL_MEMBER(Map::Units::TribesState_Func::removeUnitFromTribe, DAT_TribesState::ptr)(
                                _unitID0, (int)(_pUnit2->tribeID));
                        } else if (_pUnit2->unitType == Map::Units::UT_E_KNIGHT) {
                            _knightCount = _knightCount + 1;
                            MACRO_CALL_MEMBER(Map::Units::TribesState_Func::removeUnitFromTribe, DAT_TribesState::ptr)(
                                _unitID0, (int)(_pUnit2->tribeID));
                        }
                    }
                    _unitID0 = _unitID0 + 1;
                    _pUnit2 = _pUnit2 + 1;
                } while ((int)_unitID0 < DAT_UnitsState::instance.maxUnitCount);
            }
            if (0x28 < _macemenCount) {
                _macemenLimit = 10;
            } else if (0x14 < _macemenCount) {
                _macemenLimit = 8;
            } else {
                _macemenLimit = 5;
            }
            if (_knightCount < 19) {
                _knightLimit = (uint)(12 < _knightCount) * 2 + 2;
            } else {
                _knightLimit = 6;
            }
            if (_macemenCount <= 0) {
                DAT_TroopValueState::instance.attackInfo.macemenTribeCount = 0;
            } else if (_macemenLimit < _macemenCount) {
                DAT_TroopValueState::instance.attackInfo.macemenTribeCount = _macemenCount / _macemenLimit + 1;
                if (100 < DAT_TroopValueState::instance.attackInfo.macemenTribeCount) {
                    DAT_TroopValueState::instance.attackInfo.macemenTribeCount = 100;
                }
            } else {
                DAT_TroopValueState::instance.attackInfo.macemenTribeCount = 1;
            }
            if (_knightCount <= 0) {
                DAT_TroopValueState::instance.attackInfo.knightTribeCount = 0;
            } else if (_knightLimit < _knightCount) {
                DAT_TroopValueState::instance.attackInfo.knightTribeCount = _knightCount / _knightLimit + 1;
                if (100 < DAT_TroopValueState::instance.attackInfo.knightTribeCount) {
                    DAT_TroopValueState::instance.attackInfo.knightTribeCount = 100;
                }
            } else {
                DAT_TroopValueState::instance.attackInfo.knightTribeCount = 1;
            }
            _tribeIndex = 0;
            if (0 < DAT_TroopValueState::instance.attackInfo.macemenTribeCount) {
                uint _unitID1 = 0;
                do {
                    _tribeID1 = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::createTribe, DAT_TribesState::ptr)(
                        playerID, 0);
                    DAT_TroopValueState::instance.attackInfo.macemenTribeArray[_tribeIndex] = _tribeID1;
                    DAT_TribesState::instance.tribes[_tribeID1].tribeType = AI::Tribes::AITT_MACEMEN;
                    _limitCounter = 0;
                    if (_macemenLimit) {
                        do {
                            _unitID1 = _unitID1 + 1;
                            if (DAT_UnitsState::instance.units[_unitID1].logicalState != Map::Units::ULS_INVISIBLE
                                && (isAIPlayerWithKeep
                                    = MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::getPlayerNot1AndHasKeep,
                                        this)((int)DAT_UnitsState::instance.units[_unitID1].owner),
                                    isAIPlayerWithKeep)
                                && DAT_UnitsState::instance.units[_unitID1].unitType == Map::Units::UT_E_MACE) {
                                MACRO_CALL_MEMBER(Map::Units::TribesState_Func::addUnitToTribe, DAT_TribesState::ptr)(
                                    _unitID1, _tribeID1);
                                _macemenCount = _macemenCount + -1;
                                if (_macemenCount <= 0) {
                                    break;
                                }
                                _limitCounter = _limitCounter + 1;
                            }
                        } while (_limitCounter < _macemenLimit);
                    }
                } while ((0 < _macemenCount)
                    && (_tribeIndex = _tribeIndex + 1,
                        _tribeIndex < DAT_TroopValueState::instance.attackInfo.macemenTribeCount));
            }
            _tribeIndex = 0;
            if (0 < DAT_TroopValueState::instance.attackInfo.knightTribeCount) {
                uint _unitID2 = 0;
                do {
                    _tribeID2 = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::createTribe, DAT_TribesState::ptr)(
                        playerID, 0);
                    int _limitCounter2 = 0;
                    DAT_TroopValueState::instance.attackInfo.knightTribeArray[_tribeIndex] = _tribeID2;
                    DAT_TribesState::instance.tribes[_tribeID2].tribeType = AI::Tribes::AITT_KNIGHTS;
                    if (_knightLimit) {
                        do {
                            _unitID2 = _unitID2 + 1;
                            if (DAT_UnitsState::instance.units[_unitID2].logicalState != Map::Units::ULS_INVISIBLE
                                && (isAIPlayerWithKeep
                                    = MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::getPlayerNot1AndHasKeep,
                                        this)((int)DAT_UnitsState::instance.units[_unitID2].owner),
                                    isAIPlayerWithKeep)
                                && DAT_UnitsState::instance.units[_unitID2].unitType == Map::Units::UT_E_KNIGHT) {
                                MACRO_CALL_MEMBER(Map::Units::TribesState_Func::addUnitToTribe, DAT_TribesState::ptr)(
                                    _unitID2, _tribeID2);
                                _knightCount = _knightCount + -1;
                                if (_knightCount <= 0) {
                                    break;
                                }
                                _limitCounter2 = _limitCounter2 + 1;
                            }
                        } while (_limitCounter2 < _knightLimit);
                    }
                } while ((0 < _knightCount)
                    && (_tribeIndex = _tribeIndex + 1,
                        _tribeIndex < DAT_TroopValueState::instance.attackInfo.knightTribeCount));
            }
        }

    }
}
}
