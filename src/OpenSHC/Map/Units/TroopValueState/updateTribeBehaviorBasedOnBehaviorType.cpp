#include "../../../Map.func.hpp"

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

#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
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
            byte* pbVar1;
            short* psVar2;
            short sVar3;
            short sVar4;
            short sVar5;
            BuildingTypeShort BVar6;
            undefined4 uVar7;
            int _tribeBehaviorType;
            int* piVar8;
            BOOLEnum BVar9;
            uint uVar10;
            dword dVar11;
            int iVar12;
            uint uVar13;
            int _attackWave_2;
            short _attackWave;
            int _playerID_7;
            _attackWave = DAT_TribesState::instance.tribes[tribeID].attackWave;
            if ((_attackWave) && (_attackWave < DAT_TroopValueState::instance.attackInfo.index)) {
                DAT_TribesState::instance.tribes[tribeID].attackWave = (short)DAT_TroopValueState::instance.attackInfo.index;
            }
            _attackWave_2 = (int)DAT_TribesState::instance.tribes[tribeID].attackWave;
            pbVar1 = DAT_TroopValueState::instance.attackInfo.nof_tribes + _attackWave_2;
            *pbVar1 = *pbVar1 + 1;
            if (DAT_TribesState::instance.tribes[tribeID].percentageMovingUnk < 1) {
                pbVar1 = DAT_TroopValueState::instance.attackInfo.unknownByteArray02 + _attackWave_2;
                *pbVar1 = *pbVar1 + 1;
            }
            _tribeBehaviorType = (int)(short)DAT_TribesState::instance.tribes[tribeID].tribeBehaviorType;
            psVar2 = &DAT_TribesState::instance.tribes[tribeID].unknownAttackRelatedUpdateCounter;
            *psVar2 = *psVar2 + 1;
            sVar3 = DAT_TribesState::instance.tribes[tribeID].unknownAttackRelatedUpdateCounter;
            DAT_TribesState::instance.tribes[tribeID].field161_0x2ae = 0;
            _playerID_7 = DAT_GameSynchronyState::instance.currentPlayerSlotID;
            uVar7 = DAT_TroopValueState::instance.attackInfo.attackWaveRetargetCount;
            if (_tribeBehaviorType < 1010) {
                if (_tribeBehaviorType == 1010) {
                    sVar4 = DAT_TribesState::instance.tribes[tribeID].someUpdateUpperLimit;
                    DAT_TribesState::instance.tribes[tribeID].unitStance
                        = Map::Units::Behavior::USE_STAND_GROUND;
                    if (!sVar4) {}
                    if (sVar3 < sVar4) {}
                    DAT_TribesState::instance.tribes[tribeID].unknownAttackRelatedUpdateCounter = 0;
                    DAT_TribesState::instance.tribes[tribeID].someUpdateUpperLimit = 0;
                    MACRO_CALL_MEMBER(Map::Units::TribesState_Func::assignAttackTargetsForTribe,
                        DAT_TribesState::ptr)(tribeID, Map::Units::STBT_0x3f2);
                }
                switch (_tribeBehaviorType) {
                case 1:
                    if (0x1d < sVar3) {
                        DAT_TribesState::instance.tribes[tribeID].unknownAttackRelatedUpdateCounter = 0;
                        iVar12 = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::isTribeUnitBlockedByOtherUnit,
                            DAT_TribesState::ptr)(tribeID);
                        if (iVar12) {
                            MACRO_CALL_MEMBER(Map::Units::TribesState_Func::moveTribeToNearbyClearTile,
                                DAT_TribesState::ptr)(tribeID);
                        }
                    }
                    break;
                default:
                switchD_0051da70_caseD_3fa:
                    MACRO_CALL_MEMBER(Map::Units::TribesState_Func::updateTribeCombatStanceBehavior,
                        DAT_TribesState::ptr)(tribeID);
                    break;
                case 3:
                    iVar12 = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::stopTribeMovementAndCheckIdle,
                        DAT_TribesState::ptr)(tribeID);
                    if (iVar12) {
                        iVar12 = (&DAT_TroopValueState::instance.attackInfo
                                .unknownSignpostRelatedArray)[DAT_TribesState::instance.tribes[tribeID].attackWave];
                        sVar3 = DAT_TribesState::instance.tribes[tribeID].someIndex;
                        MACRO_CALL_MEMBER(Map::Units::TribesState_Func::giveTribeMoveInstruction,
                            DAT_TribesState::ptr)(tribeID,
                            (uint)((
                                int)(DAT_GameState::instance.mapAndTime.unitMoveDestinationXYPairs[iVar12][sVar3].x)),
                            (uint)((
                                int)(DAT_GameState::instance.mapAndTime.unitMoveDestinationXYPairs[iVar12][sVar3].y)),
                            0, 0, Map::Units::Instructions::UMSE_0);
                        DAT_TribesState::instance.tribes[tribeID].tribeBehaviorType = Map::Units::STBT_4;
                    }
                    break;
                case 4:
                case 6:
                    break;
                case 5:
                    if (DAT_TribesState::instance.tribes[tribeID].someUpdateUpperLimit <= sVar3) {
                        sVar3 = DAT_TribesState::instance.tribes[tribeID].someIndex;
                        uVar10 = (&DAT_GameState::instance.mapAndTime.somePairArray)[sVar3].y;
                        uVar13 = (&DAT_GameState::instance.mapAndTime.somePairArray)[sVar3].x;
                        DAT_TribesState::instance.tribes[tribeID].unknownAttackRelatedUpdateCounter = 0;
                        MACRO_CALL_MEMBER(
                            Map::Units::TribesState_Func::giveTribeMoveInstruction, DAT_TribesState::ptr)(
                            tribeID, uVar13, uVar10, 0, 0, Map::Units::Instructions::UMSE_0);
                        DAT_TribesState::instance.tribes[tribeID].tribeBehaviorType = Map::Units::STBT_6;
                    }
                    break;
                case 7:
                    if (DAT_TribesState::instance.tribes[tribeID].someUpdateUpperLimit <= sVar3) {
                        iVar12 = 0;
                        DAT_TribesState::instance.tribes[tribeID].unknownAttackRelatedUpdateCounter = 0;
                        piVar8 = &DAT_GameState::instance.mapAndTime.attackVectors[_playerID_7][0].tribeID;
                        do {
                            if (*piVar8 == 0) {
                                DAT_GameState::instance.mapAndTime.attackVectors[_playerID_7][iVar12].tribeID = tribeID;
                                break;
                            }
                            iVar12 = iVar12 + 1;
                            piVar8 = piVar8 + 4;
                        } while (iVar12 < 49);
                        MACRO_CALL_MEMBER(Map::Units::TribesState_Func::giveTribeMoveInstruction,
                            DAT_TribesState::ptr)(tribeID,
                            (uint)((int)(DAT_GameState::instance.mapAndTime.attackVectors[_playerID_7][iVar12].x)),
                            (uint)((int)(DAT_GameState::instance.mapAndTime.attackVectors[_playerID_7][iVar12].y)), 0,
                            0, Map::Units::Instructions::UMSE_0);
                        DAT_TribesState::instance.tribes[tribeID].tribeBehaviorType = Map::Units::STBT_8;
                    }
                    break;
                case 8:
                    if (DAT_UnitsState::instance.units[DAT_TribesState::instance.tribes[tribeID].selectionTargetUnitID]
                            .totalSizeOfPathPlan
                        < 0x19) {
                        DAT_TribesState::instance.tribes[tribeID].unitStance
                            = Map::Units::Behavior::USE_AGGRESSIVE;
                    }
                }
            } else {
                switch (_tribeBehaviorType) {
                case 0x3f3:
                    sVar4 = DAT_TribesState::instance.tribes[tribeID].someUpdateUpperLimit;
                    if ((sVar4) && (sVar4 <= sVar3)) {
                        DAT_TribesState::instance.tribes[tribeID].unknownAttackRelatedUpdateCounter = 0;
                        DAT_TribesState::instance.tribes[tribeID].someUpdateUpperLimit = 0;
                    }
                    break;
                case 0x3f4:
                    sVar4 = DAT_TribesState::instance.tribes[tribeID].someUpdateUpperLimit;
                    if ((sVar4) && (sVar4 <= sVar3)) {
                        DAT_TribesState::instance.tribes[tribeID].unknownAttackRelatedUpdateCounter = 0;
                        DAT_TribesState::instance.tribes[tribeID].someUpdateUpperLimit = 0;
                        MACRO_CALL_MEMBER(Map::Units::TribesState_Func::assignAttackTargetsForTribe,
                            DAT_TribesState::ptr)(tribeID, Map::Units::STBT_0x3f4);
                    }
                    break;
                case 0x3f5:
                    sVar4 = DAT_TribesState::instance.tribes[tribeID].someUpdateUpperLimit;
                    DAT_TribesState::instance.tribes[tribeID].unitStance
                        = Map::Units::Behavior::USE_STAND_GROUND;
                    if ((sVar4) && (sVar4 <= sVar3)) {
                        DAT_TribesState::instance.tribes[tribeID].unknownAttackRelatedUpdateCounter = 0;
                        DAT_TribesState::instance.tribes[tribeID].someUpdateUpperLimit = 0;
                        MACRO_CALL_MEMBER(Map::Units::TribesState_Func::assignAttackTargetsForTribe,
                            DAT_TribesState::ptr)(tribeID, Map::Units::STBT_0x3f5);
                    }
                    break;
                case 0x3f6:
                    sVar4 = DAT_TribesState::instance.tribes[tribeID].someUpdateUpperLimit;
                    DAT_TribesState::instance.tribes[tribeID].unitStance
                        = Map::Units::Behavior::USE_STAND_GROUND;
                    if ((sVar4) && (sVar4 <= sVar3)) {
                        DAT_TribesState::instance.tribes[tribeID].unknownAttackRelatedUpdateCounter = 0;
                        DAT_TribesState::instance.tribes[tribeID].someUpdateUpperLimit = 0;
                        MACRO_CALL_MEMBER(Map::Units::TribesState_Func::assignAttackTargetsForTribe,
                            DAT_TribesState::ptr)(tribeID, Map::Units::STBT_0x3f6);
                    }
                    break;
                case 0x3f7:
                    sVar4 = DAT_TribesState::instance.tribes[tribeID].someUpdateUpperLimit;
                    if ((sVar4) && (sVar4 <= sVar3)) {
                        DAT_TribesState::instance.tribes[tribeID].unknownAttackRelatedUpdateCounter = 0;
                        DAT_TribesState::instance.tribes[tribeID].someUpdateUpperLimit = 0;
                        MACRO_CALL_MEMBER(Map::Units::TribesState_Func::assignAttackTargetsForTribe,
                            DAT_TribesState::ptr)(tribeID, Map::Units::STBT_0x3f7);
                    }
                    break;
                case 0x3f8:
                    sVar4 = DAT_TribesState::instance.tribes[tribeID].someUpdateUpperLimit;
                    if ((sVar4) && (sVar4 <= sVar3)) {
                        DAT_TribesState::instance.tribes[tribeID].unknownAttackRelatedUpdateCounter = 0;
                        DAT_TribesState::instance.tribes[tribeID].someUpdateUpperLimit = 0;
                        MACRO_CALL_MEMBER(
                            Map::Units::TroopValueState_Func::calculateHigh2ClostestToTribeTargetUnit, this)(
                            tribeID);
                        MACRO_CALL_MEMBER(Map::Units::TribesState_Func::giveTribeMoveInstruction,
                            DAT_TribesState::ptr)(tribeID, (uint)((int)(DAT_TroopValueState::instance.x)), (uint)((int)(DAT_TroopValueState::instance.y)), 0, 0,
                            Map::Units::Instructions::UMSE_0);
                    }
                    break;
                case 0x3f9:
                    sVar4 = DAT_TribesState::instance.tribes[tribeID].someUpdateUpperLimit;
                    if ((sVar4) && (sVar4 <= sVar3)) {
                        DAT_TribesState::instance.tribes[tribeID].unknownAttackRelatedUpdateCounter = 0;
                        DAT_TribesState::instance.tribes[tribeID].someUpdateUpperLimit = 0;
                        MACRO_CALL_MEMBER(
                            Map::Units::TroopValueState_Func::calculateArch2ClosestToTribeTargetUnit, this)(
                            tribeID);
                        MACRO_CALL_MEMBER(Map::Units::TribesState_Func::giveTribeMoveInstruction,
                            DAT_TribesState::ptr)(tribeID, (uint)((int)(DAT_TroopValueState::instance.x)), (uint)((int)(DAT_TroopValueState::instance.y)), 0, 0,
                            Map::Units::Instructions::UMSE_0);
                    }
                    break;
                default:
                    goto switchD_0051da70_caseD_3fa;
                case 0x3fb:
                    sVar4 = DAT_TribesState::instance.tribes[tribeID].someUpdateUpperLimit;
                    if ((sVar4) && (sVar4 <= sVar3)) {
                        DAT_TribesState::instance.tribes[tribeID].unknownAttackRelatedUpdateCounter = 0;
                        DAT_TribesState::instance.tribes[tribeID].someUpdateUpperLimit = 0;
                        DAT_TribesState::instance.tribes[tribeID].unitStance
                            = Map::Units::Behavior::USE_AGGRESSIVE;
                        MACRO_CALL_MEMBER(Map::Units::TribesState_Func::assignAttackTargetsForTribe,
                            DAT_TribesState::ptr)(tribeID, Map::Units::STBT_0x3fb);
                    }
                    break;
                case 0x3fc:
                    sVar4 = DAT_TribesState::instance.tribes[tribeID].someUpdateUpperLimit;
                    if ((sVar4) && (sVar4 <= sVar3)) {
                        DAT_TribesState::instance.tribes[tribeID].unknownAttackRelatedUpdateCounter = 0;
                        sVar3 = DAT_TribesState::instance.tribes[tribeID].countdown2;
                        DAT_TribesState::instance.tribes[tribeID].someUpdateUpperLimit = 0;
                        DAT_TribesState::instance.tribes[tribeID].unitStance = (ushort)(2 < (int)uVar7);
                        if (sVar3 < 1) {
                        LAB_0051e032:
                            MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::claimArcherAttackPoint, this)(
                                tribeID);
                        }
                    }
                    break;
                case 0x3fd:
                    sVar4 = DAT_TribesState::instance.tribes[tribeID].someUpdateUpperLimit;
                    if ((sVar4) && (sVar4 <= sVar3)) {
                        DAT_TribesState::instance.tribes[tribeID].unknownAttackRelatedUpdateCounter = 0;
                        DAT_TribesState::instance.tribes[tribeID].someUpdateUpperLimit = 0;
                        MACRO_CALL_MEMBER(Map::Units::TribesState_Func::assignAttackTargetsForTribe,
                            DAT_TribesState::ptr)(tribeID, Map::Units::STBT_0x3fd);
                    }
                    break;
                case 0x3fe:
                    DAT_TribesState::instance.tribes[tribeID].unknownAttackRelatedUpdateCounter = 0;
                    DAT_TribesState::instance.tribes[tribeID].someUpdateUpperLimit = 0;
                    DAT_TribesState::instance.tribes[tribeID].unitStance
                        = Map::Units::Behavior::USE_AGGRESSIVE;
                    return;
                case 0x3ff:
                    if (DAT_TribesState::instance.tribes[tribeID].someUpdateUpperLimit <= sVar3) {
                        iVar12 = (&DAT_TroopValueState::instance.attackInfo.unknownSignpostRelatedArray)[_attackWave_2];
                        uVar10 = DAT_GameState::instance.mapAndTime.signpostsMapEdge[iVar12][0].y;
                        uVar13 = DAT_GameState::instance.mapAndTime.signpostsMapEdge[iVar12][0].x;
                        DAT_TribesState::instance.tribes[tribeID].unknownAttackRelatedUpdateCounter = 0;
                        MACRO_CALL_MEMBER(
                            Map::Units::TribesState_Func::giveTribeMoveInstruction, DAT_TribesState::ptr)(
                            tribeID, uVar13, uVar10, 0, 0, Map::Units::Instructions::UMSE_0);
                        DAT_TribesState::instance.tribes[tribeID].tribeBehaviorType = Map::Units::STBT_0x400;
                    }
                    break;
                case 0x400:
                    break;
                case 0x401:
                    DAT_TribesState::instance.tribes[tribeID].unitStance
                        = Map::Units::Behavior::USE_AGGRESSIVE;
                    BVar9 = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::allUnitsReachedTheirDestination,
                        DAT_TribesState::ptr)(tribeID);
                    if (BVar9) {
                        DAT_TribesState::instance.tribes[tribeID].unknownAttackRelatedUpdateCounter = 0;
                        MACRO_CALL_MEMBER(
                            Map::Units::TroopValueState_Func::buildRallyPointsFromSiegeUnits, this)(tribeID);
                        sVar3 = DAT_TribesState::instance.tribes[tribeID].rallyPointCount;
                        iVar12 = DAT_TribesState::instance.tribes[tribeID].currentRallyPointIndex + 1;
                        if (sVar3 <= iVar12) {
                            iVar12 = 0;
                        }
                        sVar4 = DAT_TribesState::instance.tribes[tribeID].rallyPointArray[iVar12][0];
                        sVar5 = DAT_TribesState::instance.tribes[tribeID].rallyPointArray[iVar12][1];
                        DAT_TribesState::instance.tribes[tribeID].currentRallyPointIndex = (short)iVar12;
                        if ((1 < sVar3)
                            && (0x60 < DAT_UnitsState::instance
                                    .units[DAT_TribesState::instance.tribes[tribeID].selectionTargetUnitID]
                                    .closestEnemyMicroDistance)) {
                            MACRO_CALL_MEMBER(Map::Units::TribesState_Func::giveTribeMoveInstruction,
                                DAT_TribesState::ptr)(tribeID, (uint)((int)((int)sVar4)), (uint)((int)((int)sVar5)), 0,
                                0, Map::Units::Instructions::UMSE_0);
                        }
                    }
                    break;
                case 0x406:
                    if (DAT_TribesState::instance.tribes[tribeID].someUpdateUpperLimit <= sVar3) {
                        DAT_TribesState::instance.tribes[tribeID].unknownAttackRelatedUpdateCounter = 0;
                        MACRO_CALL_MEMBER(
                            Map::Units::TroopValueState_Func::setRallyPointForLaddermenTribe, this)(tribeID);
                        if (DAT_TribesState::instance.tribes[tribeID].countdown2 < 1) {
                            MACRO_CALL_MEMBER(Map::Units::TribesState_Func::giveTribeMoveInstruction,
                                DAT_TribesState::ptr)(tribeID,
                                (uint)((int)((int)DAT_TribesState::instance.tribes[tribeID].rallyPointArray[0][0])),
                                (uint)((int)((int)DAT_TribesState::instance.tribes[tribeID].rallyPointArray[0][1])), 0,
                                0, Map::Units::Instructions::UMSE_0);
                        }
                    }
                    break;
                case 0x411:
                    iVar12 = (int)DAT_TribesState::instance.tribes[tribeID].supportTribeID;
                    if ((!iVar12)
                        || (DAT_TribesState::instance.tribes[tribeID].uid2
                            != DAT_TribesState::instance.tribes[iVar12].uid)) {
                        DAT_TribesState::instance.tribes[tribeID].tribeBehaviorType = Map::Units::STBT_1;
                    }
                    if (DAT_TribesState::instance.tribes[tribeID].someUpdateUpperLimit <= sVar3) {
                        DAT_TribesState::instance.tribes[tribeID].unknownAttackRelatedUpdateCounter = 0;
                        sVar3 = DAT_TribesState::instance.tribes[iVar12].selectionTargetUnitID;
                        dVar11 = MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::pathFindingRelated,
                            DAT_PathFindingState::ptr)(2, (uint)((int)((int)DAT_UnitsState::instance.units[sVar3].x)),
                            (uint)((int)((int)DAT_UnitsState::instance.units[sVar3].y)),
                            (int)((int)(DAT_UnitsState::instance.units[sVar3].siegeTargetPlayerID)));
                        if (0 < (int)dVar11) {
                            uVar13 = (uint)DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[dVar11];
                            uVar10 = dVar11 - DAT_ViewportRenderState::instance.translationMatrix[uVar13].addXgetTile;
                            MACRO_CALL_MEMBER(
                                Map::Units::TribesState_Func::giveTribeMoveInstruction, DAT_TribesState::ptr)(
                                tribeID, uVar10, uVar13, 0, 0, Map::Units::Instructions::UMSE_0);
                            MACRO_CALL_MEMBER(Map::Navigation::DirectionAlgorithmState_Func::
                                                  calculatePreferredRelativeOrientation,
                                DAT_DirectionAlgorithmState::ptr)((int)DAT_UnitsState::instance.units[sVar3].x,
                                (int)((int)(DAT_UnitsState::instance.units[sVar3].y)), (int)((int)(uVar10)),
                                (int)((int)(uVar13)));
                            DAT_TribesState::instance.tribes[tribeID].orientation
                                = (short)DAT_DirectionAlgorithmState::instance.orientation;
                        }
                    }
                    break;
                case 0x412:
                    sVar4 = DAT_TribesState::instance.tribes[tribeID].someUpdateUpperLimit;
                    if ((sVar4) && (sVar4 <= sVar3)) {
                        sVar3 = DAT_TribesState::instance.tribes[tribeID].countdown2;
                        DAT_TribesState::instance.tribes[tribeID].unknownAttackRelatedUpdateCounter = 0;
                        DAT_TribesState::instance.tribes[tribeID].someUpdateUpperLimit = 0;
                        if (sVar3 < 1) {
                            iVar12 = MACRO_CALL_MEMBER(
                                Map::Units::TroopValueState_Func::findTribeWithMoatAttackBehavior, this)();
                            if (iVar12) {
                                MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::assignTribeToSupportPoint,
                                    this)(DAT_TroopValueState::instance.x, (uint)((int)(DAT_TroopValueState::instance.y)), tribeID);
                            }
                            goto LAB_0051e032;
                        }
                    }
                    break;
                case 0x413:
                    sVar4 = DAT_TribesState::instance.tribes[tribeID].someUpdateUpperLimit;
                    DAT_TribesState::instance.tribes[tribeID].unitStance
                        = Map::Units::Behavior::USE_STAND_GROUND;
                    if ((sVar4) && (sVar4 <= sVar3)) {
                        DAT_TribesState::instance.tribes[tribeID].unknownAttackRelatedUpdateCounter = 0;
                        DAT_TribesState::instance.tribes[tribeID].someUpdateUpperLimit = 0;
                        MACRO_CALL_MEMBER(Map::Units::TribesState_Func::assignAttackTargetsForTribe,
                            DAT_TribesState::ptr)(tribeID, Map::Units::STBT_0x413);
                    }
                    break;
                case 0x414:
                    sVar4 = DAT_TribesState::instance.tribes[tribeID].someUpdateUpperLimit;
                    DAT_TribesState::instance.tribes[tribeID].unitStance
                        = Map::Units::Behavior::USE_STAND_GROUND;
                    if ((sVar4) && (sVar4 <= sVar3)) {
                        DAT_TribesState::instance.tribes[tribeID].unknownAttackRelatedUpdateCounter = 0;
                        DAT_TribesState::instance.tribes[tribeID].someUpdateUpperLimit = 0;
                        MACRO_CALL_MEMBER(Map::Units::TribesState_Func::assignAttackTargetsForTribe,
                            DAT_TribesState::ptr)(tribeID, Map::Units::STBT_0x414);
                    }
                    break;
                case 0x416:
                    sVar4 = DAT_TribesState::instance.tribes[tribeID].someUpdateUpperLimit;
                    if (((sVar4) && (sVar4 <= sVar3))
                        && (iVar12 = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::stopTribeMovementAndCheckIdle,
                                DAT_TribesState::ptr)(tribeID),
                            iVar12 != 0)) {
                        iVar12 = DAT_GameState::instance
                                     .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                     .keep.id;
                        DAT_TribesState::instance.tribes[tribeID].unknownAttackRelatedUpdateCounter = 0;
                        DAT_TribesState::instance.tribes[tribeID].someUpdateUpperLimit = 0;
                        if (0 < iVar12) {
                            BVar6 = DAT_BuildingsState::instance.buildings[iVar12].buildingType;
                            if (BVar6 == Map::Buildings::BT_MANORHOUSE) {
                                uVar10 = (int)(short)DAT_BuildingsState::instance.buildings[iVar12].x + 3;
                                uVar13 = (int)(short)DAT_BuildingsState::instance.buildings[iVar12].y + 8;
                            } else if ((BVar6 == Map::Buildings::BT_STONEKEEP)
                                || (BVar6 == Map::Buildings::BT_STRONGHOLD)) {
                                uVar10 = (int)(short)DAT_BuildingsState::instance.buildings[iVar12].x + 3;
                                uVar13 = (int)(short)DAT_BuildingsState::instance.buildings[iVar12].y + 3;
                            } else if (BVar6 == Map::Buildings::BT_KEEPFOUR) {
                                uVar10 = (int)(short)DAT_BuildingsState::instance.buildings[iVar12].x + 4;
                                uVar13 = (int)(short)DAT_BuildingsState::instance.buildings[iVar12].y + 4;
                            } else {
                                if (BVar6 != Map::Buildings::BT_KEEPFIVE) {}
                                uVar10 = (int)(short)DAT_BuildingsState::instance.buildings[iVar12].x + 5;
                                uVar13 = (int)(short)DAT_BuildingsState::instance.buildings[iVar12].y + 5;
                            }
                            MACRO_CALL_MEMBER(
                                Map::Units::TribesState_Func::giveTribeMoveInstruction, DAT_TribesState::ptr)(
                                tribeID, uVar10, uVar13, 0, 0, Map::Units::Instructions::UMSE_0);
                            DAT_TribesState::instance.tribes[tribeID].unitStance
                                = Map::Units::Behavior::USE_AGGRESSIVE;
                        }
                    }
                    break;
                case 0x418:
                    if (DAT_TribesState::instance.tribes[tribeID].someUpdateUpperLimit <= sVar3) {
                        DAT_TribesState::instance.tribes[tribeID].unknownAttackRelatedUpdateCounter = 0;
                        MACRO_CALL_MEMBER(
                            Map::Units::TroopValueState_Func::sendAttackingPatrolTribeToComputedDestination,
                            this)(tribeID);
                    }
                    break;
                case 0x419:
                    sVar4 = DAT_TribesState::instance.tribes[tribeID].someUpdateUpperLimit;
                    if ((sVar4) && (sVar4 <= sVar3)) {
                        DAT_TribesState::instance.tribes[tribeID].unknownAttackRelatedUpdateCounter = 0;
                        DAT_TribesState::instance.tribes[tribeID].someUpdateUpperLimit = 0;
                        MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::decideAndExecuteTribeAttackAction,
                            this)(tribeID);
                    }
                    break;
                case 0x41a:
                    sVar4 = DAT_TribesState::instance.tribes[tribeID].someUpdateUpperLimit;
                    if ((sVar4) && (sVar4 <= sVar3)) {
                        DAT_TribesState::instance.tribes[tribeID].unknownAttackRelatedUpdateCounter = 0;
                        DAT_TribesState::instance.tribes[tribeID].someUpdateUpperLimit = 0;
                        MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::moveTribeToNearbyGatehouse, this)(
                            tribeID);
                    }
                    break;
                case 0x41b:
                    sVar4 = DAT_TribesState::instance.tribes[tribeID].someUpdateUpperLimit;
                    if ((sVar4) && (sVar4 <= sVar3)) {
                        DAT_TribesState::instance.tribes[tribeID].unknownAttackRelatedUpdateCounter = 0;
                        DAT_TribesState::instance.tribes[tribeID].someUpdateUpperLimit = 0;
                        MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::moveTowardsParticularUnits, this)(
                            tribeID);
                    }
                    break;
                case 0x41e:
                    sVar4 = DAT_TribesState::instance.tribes[tribeID].someUpdateUpperLimit;
                    if ((sVar4) && (sVar4 <= sVar3)) {
                        DAT_TribesState::instance.tribes[tribeID].unknownAttackRelatedUpdateCounter = 0;
                        DAT_TribesState::instance.tribes[tribeID].someUpdateUpperLimit = 0;
                        MACRO_CALL_MEMBER(
                            Map::Units::TroopValueState_Func::moveTribeToReachableNearbyTile, this)(tribeID);
                    }
                }
            }
        }

    }
}
}
