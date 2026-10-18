#include "OpenSHC/Map.func.hpp"

#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/Buildings/BuildingTypeShort.hpp"
#include "OpenSHC/Map/Units/Behavior/UnitStanceEnum.hpp"
#include "OpenSHC/Map/Units/Instructions/UnitMatchSpeedEnum.hpp"
#include "OpenSHC/Map/Units/SomeTribeBehaviorType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using Map::Buildings::BuildingType;
        using Map::Buildings::BuildingTypeShort;
        using Map::Units::SomeTribeBehaviorType;
        using Map::Units::Behavior::UnitStanceEnum;
        using Map::Units::Instructions::UnitMatchSpeedEnum;
        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0051D7F0
        void TroopValueState::updateTribeBehaviorBasedOnBehaviorType(int tribeID)
        {
            byte* _pTribeCounter;
            short _updateCounter;
            short _updateUpperLimit;
            short _rallyPointY;
            BuildingTypeShort _buildingType;
            undefined4 _retargetCount;
            int _tribeBehaviorType;
            int* _pAttackVectorTribeID;
            BOOLEnum _allUnitsArrived;
            uint _coordA;
            dword _targetTile;
            int _index;
            uint _coordB;
            int _attackWave_2;
            short _attackWave;
            int _playerID_7;
            _attackWave = DAT_TribesState::instance.tribes[tribeID].attackWave;
            if ((_attackWave) && (_attackWave < DAT_TroopValueState::instance.attackInfo.index)) {
                DAT_TribesState::instance.tribes[tribeID].attackWave
                    = (short)DAT_TroopValueState::instance.attackInfo.index;
            }
            _attackWave_2 = (int)DAT_TribesState::instance.tribes[tribeID].attackWave;
            _pTribeCounter = DAT_TroopValueState::instance.attackInfo.nof_tribes + _attackWave_2;
            *_pTribeCounter = *_pTribeCounter + 1;
            if (DAT_TribesState::instance.tribes[tribeID].percentageMovingUnk <= 0) {
                _pTribeCounter = DAT_TroopValueState::instance.attackInfo.unknownByteArray02 + _attackWave_2;
                *_pTribeCounter = *_pTribeCounter + 1;
            }
            _tribeBehaviorType = (int)(short)DAT_TribesState::instance.tribes[tribeID].tribeBehaviorType;
            DAT_TribesState::instance.tribes[tribeID].unknownAttackRelatedUpdateCounter
                = DAT_TribesState::instance.tribes[tribeID].unknownAttackRelatedUpdateCounter + 1;
            _updateCounter = DAT_TribesState::instance.tribes[tribeID].unknownAttackRelatedUpdateCounter;
            DAT_TribesState::instance.tribes[tribeID].field159_0x2ae = 0;
            _playerID_7 = DAT_GameSynchronyState::instance.currentPlayerSlotID;
            _retargetCount = DAT_TroopValueState::instance.attackInfo.attackWaveRetargetCount;
            if (_tribeBehaviorType < 1010) {
                switch (_tribeBehaviorType) {
                case 3:
                    _index = MACRO_CALL_MEMBER(
                        Map::Units::TribesState_Func::stopTribeMovementAndCheckIdle, DAT_TribesState::ptr)(tribeID);
                    if (_index) {
                        _index = DAT_TroopValueState::instance.attackInfo
                                     .unknownSignpostRelatedArray[DAT_TribesState::instance.tribes[tribeID].attackWave];
                        _updateCounter = DAT_TribesState::instance.tribes[tribeID].someIndex;
                        MACRO_CALL_MEMBER(Map::Units::TribesState_Func::giveTribeMoveInstruction, DAT_TribesState::ptr)(
                            tribeID,
                            (uint)((int)(DAT_GameState::instance.mapAndTime
                                    .unitMoveDestinationXYPairs[_index][_updateCounter]
                                    .x)),
                            (uint)((int)(DAT_GameState::instance.mapAndTime
                                    .unitMoveDestinationXYPairs[_index][_updateCounter]
                                    .y)),
                            0, 0, Map::Units::Instructions::UMSE_0);
                        DAT_TribesState::instance.tribes[tribeID].tribeBehaviorType = Map::Units::STBT_4;
                    }
                    break;
                case 4:
                case 6:
                    break;
                case 5:
                    if (DAT_TribesState::instance.tribes[tribeID].someUpdateUpperLimit <= _updateCounter) {
                        _updateCounter = DAT_TribesState::instance.tribes[tribeID].someIndex;
                        _coordA = DAT_GameState::instance.mapAndTime.somePairArray[_updateCounter].y;
                        _coordB = DAT_GameState::instance.mapAndTime.somePairArray[_updateCounter].x;
                        DAT_TribesState::instance.tribes[tribeID].unknownAttackRelatedUpdateCounter = 0;
                        MACRO_CALL_MEMBER(Map::Units::TribesState_Func::giveTribeMoveInstruction, DAT_TribesState::ptr)(
                            tribeID, _coordB, _coordA, 0, 0, Map::Units::Instructions::UMSE_0);
                        DAT_TribesState::instance.tribes[tribeID].tribeBehaviorType = Map::Units::STBT_6;
                    }
                    break;
                case 7:
                    if (DAT_TribesState::instance.tribes[tribeID].someUpdateUpperLimit <= _updateCounter) {
                        _index = 0;
                        DAT_TribesState::instance.tribes[tribeID].unknownAttackRelatedUpdateCounter = 0;
                        _pAttackVectorTribeID
                            = &DAT_GameState::instance.mapAndTime.attackVectors[_playerID_7][0].tribeID;
                        do {
                            if (*_pAttackVectorTribeID == 0) {
                                DAT_GameState::instance.mapAndTime.attackVectors[_playerID_7][_index].tribeID = tribeID;
                                break;
                            }
                            _index = _index + 1;
                            _pAttackVectorTribeID = _pAttackVectorTribeID + 4;
                        } while (_index < 49);
                        MACRO_CALL_MEMBER(Map::Units::TribesState_Func::giveTribeMoveInstruction, DAT_TribesState::ptr)(
                            tribeID, (uint)(DAT_GameState::instance.mapAndTime.attackVectors[_playerID_7][_index].x),
                            (uint)(DAT_GameState::instance.mapAndTime.attackVectors[_playerID_7][_index].y), 0, 0,
                            Map::Units::Instructions::UMSE_0);
                        DAT_TribesState::instance.tribes[tribeID].tribeBehaviorType = Map::Units::STBT_8;
                    }
                    break;
                case 8:
                    if (DAT_UnitsState::instance.units[DAT_TribesState::instance.tribes[tribeID].selectionTargetUnitID]
                            .totalSizeOfPathPlan
                        < 0x19) {
                        DAT_TribesState::instance.tribes[tribeID].unitStance = Map::Units::Behavior::USE_AGGRESSIVE;
                    }
                    break;
                case 1:
                    if (0x1e <= _updateCounter) {
                        DAT_TribesState::instance.tribes[tribeID].unknownAttackRelatedUpdateCounter = 0;
                        _index = MACRO_CALL_MEMBER(
                            Map::Units::TribesState_Func::isTribeUnitBlockedByOtherUnit, DAT_TribesState::ptr)(tribeID);
                        if (_index) {
                            MACRO_CALL_MEMBER(Map::Units::TribesState_Func::moveTribeToNearbyClearTile,
                                DAT_TribesState::ptr)(tribeID);
                        }
                    }
                    break;
                default:
                    MACRO_CALL_MEMBER(
                        Map::Units::TribesState_Func::updateTribeCombatStanceBehavior, DAT_TribesState::ptr)(tribeID);
                    break;
                }
            } else if (_tribeBehaviorType == 1010) {
                _updateUpperLimit = DAT_TribesState::instance.tribes[tribeID].someUpdateUpperLimit;
                DAT_TribesState::instance.tribes[tribeID].unitStance = Map::Units::Behavior::USE_STAND_GROUND;
                if (_updateUpperLimit && _updateUpperLimit <= _updateCounter) {
                    DAT_TribesState::instance.tribes[tribeID].unknownAttackRelatedUpdateCounter = 0;
                    DAT_TribesState::instance.tribes[tribeID].someUpdateUpperLimit = 0;
                    MACRO_CALL_MEMBER(Map::Units::TribesState_Func::assignAttackTargetsForTribe, DAT_TribesState::ptr)(
                        tribeID, Map::Units::STBT_0x3f2);
                }
            } else {
                switch (_tribeBehaviorType) {
                case 0x3ff:
                    if (DAT_TribesState::instance.tribes[tribeID].someUpdateUpperLimit <= _updateCounter) {
                        _index = DAT_TroopValueState::instance.attackInfo.unknownSignpostRelatedArray[_attackWave_2];
                        _coordA = DAT_GameState::instance.mapAndTime.signpostsMapEdge[_index][0].y;
                        _coordB = DAT_GameState::instance.mapAndTime.signpostsMapEdge[_index][0].x;
                        DAT_TribesState::instance.tribes[tribeID].unknownAttackRelatedUpdateCounter = 0;
                        MACRO_CALL_MEMBER(Map::Units::TribesState_Func::giveTribeMoveInstruction, DAT_TribesState::ptr)(
                            tribeID, _coordB, _coordA, 0, 0, Map::Units::Instructions::UMSE_0);
                        DAT_TribesState::instance.tribes[tribeID].tribeBehaviorType = Map::Units::STBT_0x400;
                    }
                    return;
                case 0x3f6:
                    _updateUpperLimit = DAT_TribesState::instance.tribes[tribeID].someUpdateUpperLimit;
                    DAT_TribesState::instance.tribes[tribeID].unitStance = Map::Units::Behavior::USE_STAND_GROUND;
                    if ((_updateUpperLimit) && (_updateUpperLimit <= _updateCounter)) {
                        DAT_TribesState::instance.tribes[tribeID].unknownAttackRelatedUpdateCounter = 0;
                        DAT_TribesState::instance.tribes[tribeID].someUpdateUpperLimit = 0;
                        MACRO_CALL_MEMBER(Map::Units::TribesState_Func::assignAttackTargetsForTribe,
                            DAT_TribesState::ptr)(tribeID, Map::Units::STBT_0x3f6);
                    }
                    return;
                case 0x413:
                    _updateUpperLimit = DAT_TribesState::instance.tribes[tribeID].someUpdateUpperLimit;
                    DAT_TribesState::instance.tribes[tribeID].unitStance = Map::Units::Behavior::USE_STAND_GROUND;
                    if ((_updateUpperLimit) && (_updateUpperLimit <= _updateCounter)) {
                        DAT_TribesState::instance.tribes[tribeID].unknownAttackRelatedUpdateCounter = 0;
                        DAT_TribesState::instance.tribes[tribeID].someUpdateUpperLimit = 0;
                        MACRO_CALL_MEMBER(Map::Units::TribesState_Func::assignAttackTargetsForTribe,
                            DAT_TribesState::ptr)(tribeID, Map::Units::STBT_0x413);
                    }
                    return;
                case 0x414:
                    _updateUpperLimit = DAT_TribesState::instance.tribes[tribeID].someUpdateUpperLimit;
                    DAT_TribesState::instance.tribes[tribeID].unitStance = Map::Units::Behavior::USE_STAND_GROUND;
                    if ((_updateUpperLimit) && (_updateUpperLimit <= _updateCounter)) {
                        DAT_TribesState::instance.tribes[tribeID].unknownAttackRelatedUpdateCounter = 0;
                        DAT_TribesState::instance.tribes[tribeID].someUpdateUpperLimit = 0;
                        MACRO_CALL_MEMBER(Map::Units::TribesState_Func::assignAttackTargetsForTribe,
                            DAT_TribesState::ptr)(tribeID, Map::Units::STBT_0x414);
                    }
                    return;
                case 0x3f5:
                    _updateUpperLimit = DAT_TribesState::instance.tribes[tribeID].someUpdateUpperLimit;
                    DAT_TribesState::instance.tribes[tribeID].unitStance = Map::Units::Behavior::USE_STAND_GROUND;
                    if ((_updateUpperLimit) && (_updateUpperLimit <= _updateCounter)) {
                        DAT_TribesState::instance.tribes[tribeID].unknownAttackRelatedUpdateCounter = 0;
                        DAT_TribesState::instance.tribes[tribeID].someUpdateUpperLimit = 0;
                        MACRO_CALL_MEMBER(Map::Units::TribesState_Func::assignAttackTargetsForTribe,
                            DAT_TribesState::ptr)(tribeID, Map::Units::STBT_0x3f5);
                    }
                    return;
                case 0x3fb:
                    _updateUpperLimit = DAT_TribesState::instance.tribes[tribeID].someUpdateUpperLimit;
                    if ((_updateUpperLimit) && (_updateUpperLimit <= _updateCounter)) {
                        DAT_TribesState::instance.tribes[tribeID].unknownAttackRelatedUpdateCounter = 0;
                        DAT_TribesState::instance.tribes[tribeID].someUpdateUpperLimit = 0;
                        DAT_TribesState::instance.tribes[tribeID].unitStance = Map::Units::Behavior::USE_AGGRESSIVE;
                        MACRO_CALL_MEMBER(Map::Units::TribesState_Func::assignAttackTargetsForTribe,
                            DAT_TribesState::ptr)(tribeID, Map::Units::STBT_0x3fb);
                    }
                    return;
                case 0x401:
                    DAT_TribesState::instance.tribes[tribeID].unitStance = Map::Units::Behavior::USE_AGGRESSIVE;
                    _allUnitsArrived = MACRO_CALL_MEMBER(
                        Map::Units::TribesState_Func::allUnitsReachedTheirDestination, DAT_TribesState::ptr)(tribeID);
                    if (_allUnitsArrived) {
                        DAT_TribesState::instance.tribes[tribeID].unknownAttackRelatedUpdateCounter = 0;
                        MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::buildRallyPointsFromSiegeUnits, this)(
                            tribeID);
                        _updateCounter = DAT_TribesState::instance.tribes[tribeID].rallyPointCount;
                        _index = DAT_TribesState::instance.tribes[tribeID].currentRallyPointIndex + 1;
                        if (_updateCounter <= _index) {
                            _index = 0;
                        }
                        _updateUpperLimit = DAT_TribesState::instance.tribes[tribeID].rallyPointArray[_index][0];
                        _rallyPointY = DAT_TribesState::instance.tribes[tribeID].rallyPointArray[_index][1];
                        DAT_TribesState::instance.tribes[tribeID].currentRallyPointIndex = (short)_index;
                        if ((1 < _updateCounter)
                            && (0x60 < DAT_UnitsState::instance
                                    .units[DAT_TribesState::instance.tribes[tribeID].selectionTargetUnitID]
                                    .closestEnemyMicroDistance)) {
                            MACRO_CALL_MEMBER(Map::Units::TribesState_Func::giveTribeMoveInstruction,
                                DAT_TribesState::ptr)(tribeID, (uint)(_updateUpperLimit), (uint)(_rallyPointY), 0, 0,
                                Map::Units::Instructions::UMSE_0);
                        }
                    }
                    return;
                case 0x3fe:
                    DAT_TribesState::instance.tribes[tribeID].unknownAttackRelatedUpdateCounter = 0;
                    DAT_TribesState::instance.tribes[tribeID].someUpdateUpperLimit = 0;
                    DAT_TribesState::instance.tribes[tribeID].unitStance = Map::Units::Behavior::USE_AGGRESSIVE;
                    return;
                case 0x3fd:
                    _updateUpperLimit = DAT_TribesState::instance.tribes[tribeID].someUpdateUpperLimit;
                    if ((_updateUpperLimit) && (_updateUpperLimit <= _updateCounter)) {
                        DAT_TribesState::instance.tribes[tribeID].unknownAttackRelatedUpdateCounter = 0;
                        DAT_TribesState::instance.tribes[tribeID].someUpdateUpperLimit = 0;
                        MACRO_CALL_MEMBER(Map::Units::TribesState_Func::assignAttackTargetsForTribe,
                            DAT_TribesState::ptr)(tribeID, Map::Units::STBT_0x3fd);
                    }
                    return;
                case 0x416:
                    _updateUpperLimit = DAT_TribesState::instance.tribes[tribeID].someUpdateUpperLimit;
                    if (_updateUpperLimit && _updateUpperLimit <= _updateCounter
                        && (_index = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::stopTribeMovementAndCheckIdle,
                                DAT_TribesState::ptr)(tribeID),
                            _index != 0)) {
                        _index = DAT_GameState::instance.playerDataArray[_playerID_7].keep.id;
                        DAT_TribesState::instance.tribes[tribeID].unknownAttackRelatedUpdateCounter = 0;
                        DAT_TribesState::instance.tribes[tribeID].someUpdateUpperLimit = 0;
                        if (0 < _index) {
                            _buildingType = DAT_BuildingsState::instance.buildings[_index].buildingType;
                            if (_buildingType == Map::Buildings::BT_MANORHOUSE) {
                                _coordA = (int)(short)DAT_BuildingsState::instance.buildings[_index].x + 3;
                                _coordB = (int)(short)DAT_BuildingsState::instance.buildings[_index].y + 8;
                            } else if (_buildingType == Map::Buildings::BT_STONEKEEP) {
                                _coordA = (int)(short)DAT_BuildingsState::instance.buildings[_index].x + 3;
                                _coordB = (int)(short)DAT_BuildingsState::instance.buildings[_index].y + 3;
                            } else if (_buildingType == Map::Buildings::BT_STRONGHOLD) {
                                _coordA = (int)(short)DAT_BuildingsState::instance.buildings[_index].x + 3;
                                _coordB = (int)(short)DAT_BuildingsState::instance.buildings[_index].y + 3;
                            } else if (_buildingType == Map::Buildings::BT_KEEPFOUR) {
                                _coordA = (int)(short)DAT_BuildingsState::instance.buildings[_index].x + 4;
                                _coordB = (int)(short)DAT_BuildingsState::instance.buildings[_index].y + 4;
                            } else if (_buildingType == Map::Buildings::BT_KEEPFIVE) {
                                _coordA = (int)(short)DAT_BuildingsState::instance.buildings[_index].x + 5;
                                _coordB = (int)(short)DAT_BuildingsState::instance.buildings[_index].y + 5;
                            } else {
                                break;
                            }
                            MACRO_CALL_MEMBER(
                                Map::Units::TribesState_Func::giveTribeMoveInstruction, DAT_TribesState::ptr)(
                                tribeID, _coordA, _coordB, 0, 0, Map::Units::Instructions::UMSE_0);
                            DAT_TribesState::instance.tribes[tribeID].unitStance = Map::Units::Behavior::USE_AGGRESSIVE;
                        }
                    }
                    return;
                case 0x3f8:
                    _updateUpperLimit = DAT_TribesState::instance.tribes[tribeID].someUpdateUpperLimit;
                    if ((_updateUpperLimit) && (_updateUpperLimit <= _updateCounter)) {
                        DAT_TribesState::instance.tribes[tribeID].unknownAttackRelatedUpdateCounter = 0;
                        DAT_TribesState::instance.tribes[tribeID].someUpdateUpperLimit = 0;
                        MACRO_CALL_MEMBER(
                            Map::Units::TroopValueState_Func::calculateHigh2ClostestToTribeTargetUnit, this)(tribeID);
                        MACRO_CALL_MEMBER(Map::Units::TribesState_Func::giveTribeMoveInstruction, DAT_TribesState::ptr)(
                            tribeID, (uint)(DAT_TroopValueState::instance.x), (uint)(DAT_TroopValueState::instance.y),
                            0, 0, Map::Units::Instructions::UMSE_0);
                    }
                    return;
                case 0x3f9:
                    _updateUpperLimit = DAT_TribesState::instance.tribes[tribeID].someUpdateUpperLimit;
                    if ((_updateUpperLimit) && (_updateUpperLimit <= _updateCounter)) {
                        DAT_TribesState::instance.tribes[tribeID].unknownAttackRelatedUpdateCounter = 0;
                        DAT_TribesState::instance.tribes[tribeID].someUpdateUpperLimit = 0;
                        MACRO_CALL_MEMBER(
                            Map::Units::TroopValueState_Func::calculateArch2ClosestToTribeTargetUnit, this)(tribeID);
                        MACRO_CALL_MEMBER(Map::Units::TribesState_Func::giveTribeMoveInstruction, DAT_TribesState::ptr)(
                            tribeID, (uint)(DAT_TroopValueState::instance.x), (uint)(DAT_TroopValueState::instance.y),
                            0, 0, Map::Units::Instructions::UMSE_0);
                    }
                    return;
                case 0x3f7:
                    _updateUpperLimit = DAT_TribesState::instance.tribes[tribeID].someUpdateUpperLimit;
                    if ((_updateUpperLimit) && (_updateUpperLimit <= _updateCounter)) {
                        DAT_TribesState::instance.tribes[tribeID].unknownAttackRelatedUpdateCounter = 0;
                        DAT_TribesState::instance.tribes[tribeID].someUpdateUpperLimit = 0;
                        MACRO_CALL_MEMBER(Map::Units::TribesState_Func::assignAttackTargetsForTribe,
                            DAT_TribesState::ptr)(tribeID, Map::Units::STBT_0x3f7);
                    }
                    return;
                case 0x418:
                    if (DAT_TribesState::instance.tribes[tribeID].someUpdateUpperLimit <= _updateCounter) {
                        DAT_TribesState::instance.tribes[tribeID].unknownAttackRelatedUpdateCounter = 0;
                        MACRO_CALL_MEMBER(
                            Map::Units::TroopValueState_Func::sendAttackingPatrolTribeToComputedDestination, this)(
                            tribeID);
                    }
                    return;
                case 0x41e:
                    _updateUpperLimit = DAT_TribesState::instance.tribes[tribeID].someUpdateUpperLimit;
                    if ((_updateUpperLimit) && (_updateUpperLimit <= _updateCounter)) {
                        DAT_TribesState::instance.tribes[tribeID].unknownAttackRelatedUpdateCounter = 0;
                        DAT_TribesState::instance.tribes[tribeID].someUpdateUpperLimit = 0;
                        MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::moveTribeToReachableNearbyTile, this)(
                            tribeID);
                    }
                    return;
                case 0x419:
                    _updateUpperLimit = DAT_TribesState::instance.tribes[tribeID].someUpdateUpperLimit;
                    if ((_updateUpperLimit) && (_updateUpperLimit <= _updateCounter)) {
                        DAT_TribesState::instance.tribes[tribeID].unknownAttackRelatedUpdateCounter = 0;
                        DAT_TribesState::instance.tribes[tribeID].someUpdateUpperLimit = 0;
                        MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::decideAndExecuteTribeAttackAction, this)(
                            tribeID);
                    }
                    return;
                case 0x41a:
                    _updateUpperLimit = DAT_TribesState::instance.tribes[tribeID].someUpdateUpperLimit;
                    if ((_updateUpperLimit) && (_updateUpperLimit <= _updateCounter)) {
                        DAT_TribesState::instance.tribes[tribeID].unknownAttackRelatedUpdateCounter = 0;
                        DAT_TribesState::instance.tribes[tribeID].someUpdateUpperLimit = 0;
                        MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::moveTribeToNearbyGatehouse, this)(tribeID);
                    }
                    return;
                case 0x41b:
                    _updateUpperLimit = DAT_TribesState::instance.tribes[tribeID].someUpdateUpperLimit;
                    if ((_updateUpperLimit) && (_updateUpperLimit <= _updateCounter)) {
                        DAT_TribesState::instance.tribes[tribeID].unknownAttackRelatedUpdateCounter = 0;
                        DAT_TribesState::instance.tribes[tribeID].someUpdateUpperLimit = 0;
                        MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::moveTowardsParticularUnits, this)(tribeID);
                    }
                    return;
                case 0x3fc:
                    _updateUpperLimit = DAT_TribesState::instance.tribes[tribeID].someUpdateUpperLimit;
                    if ((_updateUpperLimit) && (_updateUpperLimit <= _updateCounter)) {
                        DAT_TribesState::instance.tribes[tribeID].unknownAttackRelatedUpdateCounter = 0;
                        _updateCounter = DAT_TribesState::instance.tribes[tribeID].countdown2;
                        DAT_TribesState::instance.tribes[tribeID].someUpdateUpperLimit = 0;
                        DAT_TribesState::instance.tribes[tribeID].unitStance = (ushort)(2 < (int)_retargetCount);
                        if (_updateCounter <= 0) {
                            MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::claimArcherAttackPoint, this)(tribeID);
                        }
                    }
                    return;
                case 0x412:
                    _updateUpperLimit = DAT_TribesState::instance.tribes[tribeID].someUpdateUpperLimit;
                    if ((_updateUpperLimit) && (_updateUpperLimit <= _updateCounter)) {
                        _updateCounter = DAT_TribesState::instance.tribes[tribeID].countdown2;
                        DAT_TribesState::instance.tribes[tribeID].unknownAttackRelatedUpdateCounter = 0;
                        DAT_TribesState::instance.tribes[tribeID].someUpdateUpperLimit = 0;
                        if (_updateCounter <= 0) {
                            _index = MACRO_CALL_MEMBER(
                                Map::Units::TroopValueState_Func::findTribeWithMoatAttackBehavior, this)();
                            if (!_index) {
                                MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::claimArcherAttackPoint, this)(
                                    tribeID);
                                return;
                            }
                            MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::assignTribeToSupportPoint, this)(
                                DAT_TroopValueState::instance.x, (uint)(DAT_TroopValueState::instance.y), tribeID);
                            return;
                        }
                    }
                    return;
                case 0x406:
                    if (DAT_TribesState::instance.tribes[tribeID].someUpdateUpperLimit <= _updateCounter) {
                        DAT_TribesState::instance.tribes[tribeID].unknownAttackRelatedUpdateCounter = 0;
                        MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::setRallyPointForLaddermenTribe, this)(
                            tribeID);
                        if (DAT_TribesState::instance.tribes[tribeID].countdown2 <= 0) {
                            MACRO_CALL_MEMBER(
                                Map::Units::TribesState_Func::giveTribeMoveInstruction, DAT_TribesState::ptr)(tribeID,
                                (uint)(DAT_TribesState::instance.tribes[tribeID].rallyPointArray[0][0]),
                                (uint)(DAT_TribesState::instance.tribes[tribeID].rallyPointArray[0][1]), 0, 0,
                                Map::Units::Instructions::UMSE_0);
                        }
                    }
                    return;
                case 0x3f3:
                    _updateUpperLimit = DAT_TribesState::instance.tribes[tribeID].someUpdateUpperLimit;
                    if ((_updateUpperLimit) && (_updateUpperLimit <= _updateCounter)) {
                        DAT_TribesState::instance.tribes[tribeID].unknownAttackRelatedUpdateCounter = 0;
                        DAT_TribesState::instance.tribes[tribeID].someUpdateUpperLimit = 0;
                    }
                    return;
                case 0x3f4:
                    _updateUpperLimit = DAT_TribesState::instance.tribes[tribeID].someUpdateUpperLimit;
                    if ((_updateUpperLimit) && (_updateUpperLimit <= _updateCounter)) {
                        DAT_TribesState::instance.tribes[tribeID].unknownAttackRelatedUpdateCounter = 0;
                        DAT_TribesState::instance.tribes[tribeID].someUpdateUpperLimit = 0;
                        MACRO_CALL_MEMBER(Map::Units::TribesState_Func::assignAttackTargetsForTribe,
                            DAT_TribesState::ptr)(tribeID, Map::Units::STBT_0x3f4);
                    }
                    return;
                case 0x411:
                    _index = (int)DAT_TribesState::instance.tribes[tribeID].supportTribeID;
                    if ((!_index)
                        || (DAT_TribesState::instance.tribes[tribeID].uid2
                            != DAT_TribesState::instance.tribes[_index].uid)) {
                        DAT_TribesState::instance.tribes[tribeID].tribeBehaviorType = Map::Units::STBT_1;
                    }
                    if (DAT_TribesState::instance.tribes[tribeID].someUpdateUpperLimit <= _updateCounter) {
                        DAT_TribesState::instance.tribes[tribeID].unknownAttackRelatedUpdateCounter = 0;
                        int const _unitID = (int)DAT_TribesState::instance.tribes[_index].selectionTargetUnitID;
                        _targetTile = MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::pathFindingRelated,
                            DAT_PathFindingState::ptr)(2, (uint)(DAT_UnitsState::instance.units[_unitID].x),
                            (uint)(DAT_UnitsState::instance.units[_unitID].y),
                            (int)(DAT_UnitsState::instance.units[_unitID].siegeTargetPlayerID));
                        if (0 < (int)_targetTile) {
                            _coordB
                                = (uint)DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[_targetTile];
                            _coordA = _targetTile
                                - DAT_ViewportRenderState::instance.translationMatrix[_coordB].addXgetTile;
                            MACRO_CALL_MEMBER(
                                Map::Units::TribesState_Func::giveTribeMoveInstruction, DAT_TribesState::ptr)(
                                tribeID, _coordA, _coordB, 0, 0, Map::Units::Instructions::UMSE_0);
                            MACRO_CALL_MEMBER(
                                Map::Navigation::DirectionAlgorithmState_Func::calculatePreferredRelativeOrientation,
                                DAT_DirectionAlgorithmState::ptr)((int)DAT_UnitsState::instance.units[_unitID].x,
                                (int)(DAT_UnitsState::instance.units[_unitID].y), (int)(_coordA), (int)(_coordB));
                            DAT_TribesState::instance.tribes[tribeID].orientation
                                = (short)DAT_DirectionAlgorithmState::instance.orientation;
                        }
                    }
                    return;
                default:
                    MACRO_CALL_MEMBER(
                        Map::Units::TribesState_Func::updateTribeCombatStanceBehavior, DAT_TribesState::ptr)(tribeID);
                    return;
                case 0x400:
                    return;
                }
            }
        }

    }
}
}
