#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/AI/AIType.hpp"
#include "OpenSHC/Map/Units/Behavior/UnitStanceEnum.hpp"
#include "OpenSHC/Map/Units/Instructions/UnitMatchSpeedEnum.hpp"
#include "OpenSHC/Map/Units/SomeTribeBehaviorType.hpp"

#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_SkirmishDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace AI {

    using OpenSHC::AI::AIType;
    using OpenSHC::Map::Units::SomeTribeBehaviorType;
    using OpenSHC::Map::Units::Behavior::UnitStanceEnum;
    using OpenSHC::Map::Units::Instructions::UnitMatchSpeedEnum;

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000 */

    // FUNCTION: STRONGHOLDCRUSADER 0x004D30E0
    undefined4 AICState ::sendUnitsToAttackBreachedCastle(int attackingPlayerIndex)

    {

        int tribeType;

        int _defendingLordIndex;

        int _successUnk;

        int iVar1;

        int _vector;

        int _tribeID;

        short* local_20;

        int local_18;

        int (*_ptrGroupCount)[2];

        int _attackedPlayerID;

        int _groupCount;

        short _targetUnit;

        bool sentUnitsToAttackLord;

        _vector = 0;

        if (DAT_GameState::instance.playerDataArray[attackingPlayerIndex].aiType == OpenSHC::AI::AIT_NULL) {

            return (undefined4)(1);
        }

        sentUnitsToAttackLord = false;

        _defendingLordIndex = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::getAliveLordForPlayer,
            DAT_UnitsState::ptr)(DAT_GameState::instance.playerDataArray[attackingPlayerIndex].attackedPlayerID);

        _ptrGroupCount = (int (*)[2])(&DAT_SkirmishDefinedData::instance.MaxBreachTribes[0].tribeCount);

        do {

            tribeType = _ptrGroupCount[-1][1];

            _groupCount = (*_ptrGroupCount)[0];

            if ((((tribeType != 18) && (tribeType != 14)) && (tribeType != 13)) && (local_18 = 0, 0 < _groupCount)) {

                local_20 = DAT_GameState::instance.playerDataArray[attackingPlayerIndex].aiTribeIDs + tribeType;

                do {

                    _tribeID = (int)*local_20;

                    if ((_tribeID != 0)
                        && (DAT_TribesState::instance.tribes[_tribeID].uid
                            == DAT_GameState::instance.playerDataArray[attackingPlayerIndex]
                                .aiTribeUIDs[local_18 + tribeType])) {

                        _targetUnit = DAT_TribesState::instance.tribes[_tribeID].selectionTargetUnitID;

                        DAT_TribesState::instance.tribes[_tribeID].unitStance
                            = OpenSHC::Map::Units::Behavior::USE_DEFENSIVE;

                        if ((sentUnitsToAttackLord) || ((_defendingLordIndex == 0 || (tribeType == 186)))) {

                            iVar1 = MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::giveSomeRaidCommand, this)(
                                _tribeID, tribeType);

                            if (iVar1 == 0) {

                                if (tribeType == 0xba) {

                                    _vector = _vector + 4;
                                }

                                DAT_TribesState::instance.tribes[_tribeID].tribeBehaviorType
                                    = OpenSHC::Map::Units::STBT_8;

                                DAT_TribesState::instance.tribes[_tribeID].unitStance
                                    = OpenSHC::Map::Units::Behavior::USE_AGGRESSIVE;

                                iVar1 = DAT_GameState::instance.playerDataArray[attackingPlayerIndex].attackedPlayerID;

                                MACRO_CALL_MEMBER(
                                    OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                                    DAT_DirectionAlgorithmState::ptr)(
                                    (int)DAT_UnitsState::instance.units[_targetUnit].x,
                                    (int)((int)(DAT_UnitsState::instance.units[_targetUnit].y)),
                                    DAT_GameState::instance.mapAndTime.attackVectors[iVar1][_vector].x,
                                    DAT_GameState::instance.mapAndTime.attackVectors[iVar1][_vector].y);

                                if (4 < DAT_DirectionAlgorithmState::instance.distanceHigh) {

                                    _attackedPlayerID = DAT_GameState::instance.playerDataArray[attackingPlayerIndex]
                                                            .attackedPlayerID;

                                    MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::giveTribeMoveInstruction,
                                        DAT_TribesState::ptr)(_tribeID,
                                        (uint)((int)(DAT_GameState::instance.mapAndTime
                                                .attackVectors[_attackedPlayerID][_vector]
                                                .x)),
                                        (uint)((int)(DAT_GameState::instance.mapAndTime
                                                .attackVectors[_attackedPlayerID][_vector]
                                                .y)),
                                        0, 0, OpenSHC::Map::Units::Instructions::UMSE_0);
                                }

                                _vector = _vector + 1;
                            }

                        }

                        else {

                            /*
                                          Send units to attack lord */

                            _successUnk = MACRO_CALL_MEMBER(
                                OpenSHC::Map::Units::TribesState_Func::giveTribeMoveInstruction, DAT_TribesState::ptr)(
                                _tribeID, (uint)((int)((int)DAT_UnitsState::instance.units[_defendingLordIndex].x)),
                                (uint)((int)((int)DAT_UnitsState::instance.units[_defendingLordIndex].y)), 0, 0,
                                OpenSHC::Map::Units::Instructions::UMSE_0);

                            if (_successUnk == 0) {

                                return (undefined4)(0);
                            }

                            sentUnitsToAttackLord = true;
                        }
                    }

                    local_20 = local_20 + 1;

                    local_18 = local_18 + 1;

                } while (local_18 < _groupCount);
            }

            _ptrGroupCount = _ptrGroupCount + 1;

        } while ((int)_ptrGroupCount < 0xb42acc);

        return (undefined4)(1);
    }

}
}
