#include "../../../Map.func.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/AI/Tribes/AITribeType.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
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
            int playerID;
            BOOLEnum BVar1;
            int _tribeID1;
            int _tribeID2;
            int _count;
            uint _unitID1;
            uint _unitID2;
            int _macemenCount;
            int _limitCounter2;
            uint _unitID0;
            short* psVar2;
            Unit* _pUnit2;
            int _knightCount;
            int _macemenLimit;
            int local_14;
            int _knightLimit;
            int _limitCounter;
            short* _pUnit1;
            playerID = DAT_TroopValueState::instance.attackInfo.pitchRelatedPlayerID;
            _count = 0;
            _unitID0 = 1;
            _macemenCount = 0;
            _knightCount = 0;
            if (1 < DAT_UnitsState::instance.maxUnitCount) {
                _pUnit2 = &DAT_UnitsState::instance.units[1];
                do {
                    if ((_pUnit2->logicalState != Map::Units::ULS_INVISIBLE)
                        && (BVar1 = MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::getPlayerNot1AndHasKeep, this)(
                                (int)_pUnit2->owner),
                            BVar1)) {
                        if (_pUnit2->unitType == Map::Units::UT_E_MACE) {
                            _macemenCount = _macemenCount + 1;
                        } else {
                            if (_pUnit2->unitType != Map::Units::UT_E_KNIGHT)
                                goto LAB_0051cd29;
                            _knightCount = _count + 1;
                        }
                        MACRO_CALL_MEMBER(Map::Units::TribesState_Func::removeUnitFromTribe,
                            DAT_TribesState::ptr)(_unitID0, (int)((int)(_pUnit2->tribeID)));
                        _count = _knightCount;
                    }
                LAB_0051cd29:
                    _unitID0 = _unitID0 + 1;
                    _pUnit2 = _pUnit2 + 0x248;
                } while ((int)_unitID0 < DAT_UnitsState::instance.maxUnitCount);
                if (0x28 < _macemenCount) {
                    _macemenLimit = 10;
                    goto LAB_0051cd5e;
                }
                _macemenLimit = 8;
                if (0x14 < _macemenCount)
                    goto LAB_0051cd5e;
            }
            _macemenLimit = 5;
        LAB_0051cd5e:
            if (_count < 18) {
                _knightLimit = (uint)(12 < _count) * 2 + 2;
            } else {
                _knightLimit = 6;
            }
            if (_macemenCount < 1) {
                DAT_TroopValueState::instance.attackInfo.macemenTribeCount = 0;
            } else if (_macemenLimit < _macemenCount) {
                DAT_TroopValueState::instance.attackInfo.macemenTribeCount = _macemenCount / _macemenLimit + 1;
                _count = _knightCount;
                if (100 < DAT_TroopValueState::instance.attackInfo.macemenTribeCount) {
                    DAT_TroopValueState::instance.attackInfo.macemenTribeCount = 100;
                }
            } else {
                DAT_TroopValueState::instance.attackInfo.macemenTribeCount = 1;
            }
            if (_count < 1) {
                DAT_TroopValueState::instance.attackInfo.knightTribeCount = 0;
            } else if (_knightLimit < _count) {
                DAT_TroopValueState::instance.attackInfo.knightTribeCount = _count / _knightLimit + 1;
                if (100 < DAT_TroopValueState::instance.attackInfo.knightTribeCount) {
                    DAT_TroopValueState::instance.attackInfo.knightTribeCount = 100;
                }
            } else {
                DAT_TroopValueState::instance.attackInfo.knightTribeCount = 1;
            }
            local_14 = 0;
            if (0 < DAT_TroopValueState::instance.attackInfo.macemenTribeCount) {
                _unitID1 = 0;
                do {
                    _tribeID1 = MACRO_CALL_MEMBER(
                        Map::Units::TribesState_Func::createTribe, DAT_TribesState::ptr)(playerID, 0);
                    DAT_TroopValueState::instance.attackInfo.macemenTribeArray[local_14] = _tribeID1;
                    DAT_TribesState::instance.tribes[_tribeID1].tribeType = AI::Tribes::AITT_MACEMEN;
                    _limitCounter = 0;
                    if (_macemenLimit) {
                        _pUnit1 = &DAT_UnitsState::instance.units[_unitID1].owner;
                        do {
                            _unitID1 = _unitID1 + 1;
                            if (((_pUnit1[0x243] != 0)
                                    && (BVar1
                                        = MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::getPlayerNot1AndHasKeep,
                                            this)((int)_pUnit1[0x248]),
                                        BVar1))
                                && (_pUnit1[0x244] == 0x1a)) {
                                MACRO_CALL_MEMBER(Map::Units::TribesState_Func::addUnitToTribe,
                                    DAT_TribesState::ptr)(_unitID1, _tribeID1);
                                _macemenCount = _macemenCount + -1;
                                if (_macemenCount < 1)
                                    goto LAB_0051ceba;
                                _limitCounter = _limitCounter + 1;
                            }
                            _pUnit1 = _pUnit1 + 0x248;
                        } while (_limitCounter < _macemenLimit);
                    }
                } while (
                    (0 < _macemenCount) && (local_14 = local_14 + 1, local_14 < DAT_TroopValueState::instance.attackInfo.macemenTribeCount));
            }
        LAB_0051ceba:
            local_14 = 0;
            if (0 < DAT_TroopValueState::instance.attackInfo.knightTribeCount) {
                _unitID2 = 0;
                do {
                    _tribeID2 = MACRO_CALL_MEMBER(
                        Map::Units::TribesState_Func::createTribe, DAT_TribesState::ptr)(playerID, 0);
                    _limitCounter2 = 0;
                    DAT_TroopValueState::instance.attackInfo.knightTribeArray[local_14] = _tribeID2;
                    DAT_TribesState::instance.tribes[_tribeID2].tribeType = AI::Tribes::AITT_KNIGHTS;
                    if (_knightLimit) {
                        psVar2 = &DAT_UnitsState::instance.units[_unitID2].owner;
                        do {
                            _unitID2 = _unitID2 + 1;
                            if (((psVar2[0x243] != 0)
                                    && (BVar1
                                        = MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::getPlayerNot1AndHasKeep,
                                            this)((int)psVar2[0x248]),
                                        BVar1))
                                && (psVar2[0x244] == 0x1c)) {
                                MACRO_CALL_MEMBER(Map::Units::TribesState_Func::addUnitToTribe,
                                    DAT_TribesState::ptr)(_unitID2, _tribeID2);
                                _knightCount = _knightCount + -1;
                                if (_knightCount < 1) {}
                                _limitCounter2 = _limitCounter2 + 1;
                            }
                            psVar2 = psVar2 + 0x248;
                        } while (_limitCounter2 < _knightLimit);
                    }
                } while ((0 < _knightCount) && (local_14 = local_14 + 1, local_14 < DAT_TroopValueState::instance.attackInfo.knightTribeCount));
            }
        }

    }
}
}
