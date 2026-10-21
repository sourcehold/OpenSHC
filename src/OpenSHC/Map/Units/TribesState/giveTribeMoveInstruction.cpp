#include "../../../Map.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Map/Units/Instructions/UnitMatchSpeedEnum.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitInstructionType.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitSelectionDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using Map::Units::UnitInstructionType;
        using Map::Units::UnitLogicState;
        using Map::Units::UnitType;
        using Map::Units::Instructions::UnitMatchSpeedEnum;
        using Map::Units::States::UnitState;
        using WindowsHelper::Enums::BOOLEnum;

        /*
          Two declaration moves were measured here and all of them reverted, because raw
          and normalized disagree and raw is what this function is scored on:

            as written                              raw 30.0%  norm 22.5%
            `_searchBudget` declared at this level   raw 28.0%  norm 26.1%
            plus `_tribeUnitIndex` scoped to its loop  raw 27.1%  norm 27.0%
            only `_tribeUnitIndex` scoped            raw 21.7%  norm 21.9%

          The original does declare the search budget at function scope - its prologue
          stores 0x1f4 into the slot alongside the zeroed locals, which is what the middle
          two variants reproduce - and `_tribeUnitIndex` is a slot too many when it does,
          so the frame only matches with both moves. Whatever is costing the raw match is
          downstream of the stack displacements those moves shift, so this needs the
          allocation understood rather than another declaration permutation.
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x005263A0
        undefined4 TribesState::giveTribeMoveInstruction(
            int tribeID, uint x1, uint y1, int rallyBool, int storeAsRallyPoint, UnitMatchSpeedEnum speedMatching)
        {
            UnitStateShort UVar1;
            UnitTypeShort UVar2;
            int _firstUnitID;
            int _navArea;
            uint _someUnitCanClimb;
            dword _area3;
            int iVar7;
            int _hasUnitInArea;
            BOOLEnum BVar8;
            int _unitID;
            dword dVar9;
            int _unitID_2;
            int _modulo;
            int _area_2;
            UnitTypeShort _unitType;
            int _targetUnitArea;
            uint _y = y1;
            int _bool1 = 0;
            int _tribeUnitIndex = 0;
            int bVar6 = 0;
            int _algTile2 = 0;
            int _algTile = 0;
            int bVar4 = 0;
            if (!x1) {
                if (!y1) {
                    return (undefined4)(0);
                }
            } else {
                if ((int)x1 < 0) {
                    return (undefined4)(0);
                }
                /*
                  `cmp 0x190; jge`, not `cmp 0x18f; jg`.
                 */
                if (400 <= (int)x1) {
                    return (undefined4)(0);
                }
            }
            if (399 < y1) {
                return (undefined4)(0);
            }
            if (DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y1 * 400 + x1] == 0) {
                return (undefined4)(0);
            }
            /*
              The subscript is repeated rather than bound to a `Tribe&`, although the
              original does take the address once (`lea eax, [edx + ecx]` at 0x526417, kept
              in a stack slot) and read every later field through it: binding all 21 uses to
              a reference costs 1.1 points (30.0% -> 28.9%, norm 65.2% -> 21.8%).
             */
            int _targetUnitID = (int)this->tribes[tribeID].selectionTargetUnitID;
            int _targetUnitX = (int)DAT_UnitsState::instance.units[_targetUnitID].x;
            int _targetUnitY = (int)DAT_UnitsState::instance.units[_targetUnitID].y;
            _targetUnitArea
                = (short)DAT_TileMapState::instance
                      .PathConnectionLayer[DAT_ViewportRenderState::instance.translationMatrix[_targetUnitY].addXgetTile
                          + _targetUnitX];
            int _tile = DAT_ViewportRenderState::instance.translationMatrix[y1].addXgetTile + x1;
            int _area = (int)(short)DAT_TileMapState::instance.PathConnectionLayer[_tile];
            if (!(DAT_TileMapState::instance.LogicLayer[_tile] & 0x30)) {
                DAT_PathFindingState::instance.field50_0x98 = 0;
                this->fcn_mtribe = this->fcn_mtribe + 1;
                _firstUnitID = MACRO_CALL_MEMBER(
                    Map::Units::TribesState_Func::getFirstUnitInTribeThatIsOnXTerrain, this)(tribeID);
                if (_targetUnitID == _firstUnitID) {
                    _navArea = MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::canNavigateFunctionReturnsArea,
                        DAT_PathFindingState::ptr)(this->tribes[tribeID].owner, (dword)((int)(_area)),
                        (uint)(DAT_UnitsState::instance.units[_targetUnitID].x),
                        (uint)(DAT_UnitsState::instance.units[_targetUnitID].y));
                    if (!_navArea) {
                        return (undefined4)(MACRO_CALL_MEMBER(
                            Map::Units::TribesState_Func::applyMoveCommandOrRallyCommandToTribe, this)(tribeID,
                            (undefined4)((int)(x1)), (undefined4)((int)(y1)), (undefined4)((int)(rallyBool)),
                            storeAsRallyPoint));
                    }
                    _targetUnitID = (int)this->tribes[tribeID].selectionTargetUnitID;
                    _bool1 = 1;
                    _area_2 = _navArea;
                } else {
                    _area_2 = _targetUnitArea;
                    if (!_targetUnitArea) {
                        return (undefined4)(MACRO_CALL_MEMBER(
                            Map::Units::TribesState_Func::applyMoveCommandOrRallyCommandToTribe, this)(tribeID,
                            (undefined4)((int)(x1)), (undefined4)((int)(y1)), (undefined4)((int)(rallyBool)),
                            storeAsRallyPoint));
                    }
                }
                /*
                  WARNING: y1 now is area2
                 */
                y1 = _area_2;
                if (0 < _area) {
                    int _firstUnit
                        = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::isTribeAllAssassins, this)(tribeID);
                    if (!_firstUnit) {
                        if (_area != y1) {
                            _someUnitCanClimb = MACRO_CALL_MEMBER(
                                Map::Units::TribesState_Func::tribeContainsUnitThatCanClimb, this)(tribeID);
                            _area3 = MACRO_CALL_MEMBER(
                                Map::Navigation::PathFindingState_Func::calculateCanPlayerUnitsNavigateToAreaFromArea,
                                DAT_PathFindingState::ptr)(this->tribes[tribeID].owner, (dword)((int)(y1)),
                                (dword)((int)(_area)), (int)(_someUnitCanClimb));
                            if (!_area3) {
                                iVar7 = MACRO_CALL_MEMBER(
                                    Map::Navigation::PathFindingState_Func::someBinaryAlgFunctionPathFinding,
                                    DAT_PathFindingState::ptr)(_targetUnitID);
                                if (!iVar7) {
                                    return (undefined4)(0);
                                }
                                iVar7 = MACRO_CALL_MEMBER(
                                    Map::Navigation::PathFindingState_Func::findCrossAreaBridgeTileToTarget,
                                    DAT_PathFindingState::ptr)(_targetUnitID, x1, _y);
                                if (!iVar7) {
                                    return (undefined4)(0);
                                }
                                bVar6 = 1;
                                _algTile2 = DAT_PathFindingState::instance.ALG_TargetTile;
                                _algTile = DAT_PathFindingState::instance.ALG_ResultTile;
                            } else {
                                iVar7 = MACRO_CALL_MEMBER(
                                    Map::Navigation::PathFindingState_Func::setClimbBasedOnClosestClimbData,
                                    DAT_PathFindingState::ptr)(_targetUnitID, (int)(y1), (int)(_area3));
                                if (!iVar7) {
                                    return (undefined4)(0);
                                }
                            }
                        }
                    } else {
                        bVar4 = 1;
                    }
                    if (storeAsRallyPoint) {
                        this->tribes[tribeID].isRallyingUnk = (short)rallyBool;
                        this->tribes[tribeID].rallyPointArray[0][0] = DAT_UnitsState::instance.units[_targetUnitID].x;
                        this->tribes[tribeID].rallyPointArray[0][1] = DAT_UnitsState::instance.units[_targetUnitID].y;
                        this->tribes[tribeID].rallyPointArray[1][0] = (short)x1;
                        this->tribes[tribeID].rallyPointArray[1][1] = (short)_y;
                        this->tribes[tribeID].currentRallyPointIndex = 1;
                        this->tribes[tribeID].rallyPointCount = 2;
                        this->tribes[tribeID].containsRabbit = 0;
                    }
                    this->ALG_ResultTileIndex = 0;
                    this->field6_0x18 = 0;
                    int _isWallGatehouseTower = (DAT_TileMapState::instance.LogicLayer[_tile] & 0x100U) != 0;
                    int bVar5 = 0;
                    int _isKeep = (DAT_TileMapState::instance.LogicLayer[_tile] & 0x10000000U) != 0;
                    int _isDefensiveStructure = _isKeep || _isWallGatehouseTower;
                    rallyBool = 1;
                    if (bVar4) {
                        MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::pathFindingWithBuildingsIncluded,
                            DAT_PathFindingState::ptr)(x1, _y, 0xffffffff, 0xffffffff, 500, 0);
                    } else if (_bool1) {
                        MACRO_CALL_MEMBER(
                            Map::Navigation::PathFindingState_Func::findPathUsingClimbingWithHeightMargin16,
                            DAT_PathFindingState::ptr)(x1, _y, 0xffffffff, 0xffffffff, 500, FALSE);
                    } else {
                        MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::findLinkageBasedPathOrWalkRadius,
                            DAT_PathFindingState::ptr)(x1, _y, -1, -1, 500, FALSE);
                    }
                    _hasUnitInArea = MACRO_CALL_MEMBER(
                        Map::Units::TribesState_Func::anyUnitsOfTribeAreOutsideCoverageOfPathFindingAlg, this)(
                        tribeID, DAT_PathFindingState::instance.searchGeneration);
                    if (!_hasUnitInArea) {
                        int _searchBudget = 500;
                        do {
                            _searchBudget = _searchBudget + 500;
                            if (0x13a10 <= _searchBudget
                                || ((_bool1 || (_isDefensiveStructure)) && (8000 <= _searchBudget))) {
                                if (!DAT_PathFindingState::instance.field50_0x98) {
                                    if (bVar4) {
                                        BVar8 = MACRO_CALL_MEMBER(
                                            Map::Navigation::PathFindingState_Func::pathFindingWithBuildingsIncluded,
                                            DAT_PathFindingState::ptr)(
                                            x1, _y, (uint)(_targetUnitX), (uint)(_targetUnitY), 100000, 0);
                                        if (!BVar8) {
                                            return (undefined4)(0);
                                        }
                                    } else if (_bool1) {
                                        BVar8 = MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::
                                                                      findPathUsingClimbingWithHeightMargin16,
                                            DAT_PathFindingState::ptr)(
                                            x1, _y, (uint)(_targetUnitX), (uint)(_targetUnitY), 100000, FALSE);
                                        if (!BVar8) {
                                            return (undefined4)(0);
                                        }
                                    } else {
                                        BVar8 = MACRO_CALL_MEMBER(
                                            Map::Navigation::PathFindingState_Func::findLinkageBasedPathOrWalkRadius,
                                            DAT_PathFindingState::ptr)(
                                            x1, _y, _targetUnitX, _targetUnitY, 100000, FALSE);
                                        if (!BVar8) {
                                            return (undefined4)(0);
                                        }
                                    }
                                }
                                MACRO_CALL_MEMBER(Map::Units::TribesState_Func::
                                                      applyMovementDistanceToUnitsInTribeBasedOnUnitNumberInTribe,
                                    this)(tribeID);
                                goto LAB_00526788;
                            }
                            rallyBool = DAT_PathFindingState::instance.searchQueue.currentDistance;
                            if (bVar4) {
                                MACRO_CALL_MEMBER(
                                    Map::Navigation::PathFindingState_Func::pathFindingWithBuildingsIncluded,
                                    DAT_PathFindingState::ptr)(x1, _y, 0xffffffff, 0xffffffff, _searchBudget, 1);
                            } else if (_bool1) {
                                MACRO_CALL_MEMBER(
                                    Map::Navigation::PathFindingState_Func::findPathUsingClimbingWithHeightMargin16,
                                    DAT_PathFindingState::ptr)(x1, _y, 200, 0, _searchBudget, TRUE);
                            } else {
                                MACRO_CALL_MEMBER(
                                    Map::Navigation::PathFindingState_Func::findLinkageBasedPathOrWalkRadius,
                                    DAT_PathFindingState::ptr)(x1, _y, -1, -1, _searchBudget, TRUE);
                            }
                            BVar8 = MACRO_CALL_MEMBER(
                                Map::Units::TribesState_Func::anyUnitsOfTribeAreOutsideCoverageOfPathFindingAlg, this)(
                                tribeID, DAT_PathFindingState::instance.searchGeneration);
                        } while (!BVar8);
                    }
                    MACRO_CALL_MEMBER(Map::Units::TribesState_Func::applyMovementDistanceToUnitsInTribe, this)(tribeID);
                LAB_00526788:
                    if (0 < this->tribes[tribeID].size) {
                        do {
                            /*
                              plan x and y for each unit in selection
                             */
                            _unitID = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::getUnitIDForIndexInTribe, this)(
                                tribeID, _tribeUnitIndex);
                            _tribeUnitIndex = _tribeUnitIndex + 1;
                            if (DAT_UnitsState::instance.units[_unitID].logicalState == Map::Units::ULS_NORMAL
                                && DAT_UnitsState::instance.units[_unitID].dying == 0
                                && DAT_UnitsState::instance.units[_unitID].usingTeleport == 0
                                && DAT_UnitsState::instance.units[_unitID].field303_0x413 == 0
                                && DAT_UnitsState::instance.units[_unitID].state.generic != (UnitStateShort)0xcf
                                && DAT_UnitsState::instance.units[_unitID].rallyRelatedFlag == 0
                                && DAT_UnitsState::instance.units[_unitID].moveRelatedFlag != 1
                                && DAT_UnitsState::instance.units[_unitID].moveableUnk != 0
                                && (_unitType = DAT_UnitsState::instance.units[_unitID].unitType,
                                    _unitType != Map::Units::UT_S_TREBUCHET)
                                && _unitType != Map::Units::UT_S_MANGONEL && _unitType != Map::Units::UT_S_BALLISTA
                                && (_unitType != Map::Units::UT_S_CATAPULT
                                    || (DAT_UnitsState::instance.units[_unitID]
                                            .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300
                                        == 2))
                                && (_unitType != Map::Units::UT_S_FBALLISTA
                                    || (DAT_UnitsState::instance.units[_unitID]
                                            .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300
                                        == 2))
                                && (_unitType != Map::Units::UT_S_TOWER
                                    || (DAT_UnitsState::instance.units[_unitID]
                                            .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300
                                        == 4))
                                && (_unitType != Map::Units::UT_S_BATTERINGRAM
                                    || (DAT_UnitsState::instance.units[_unitID]
                                            .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300
                                        == 4))
                                && (_unitType != Map::Units::UT_S_SHIELD
                                    || (DAT_UnitsState::instance.units[_unitID]
                                            .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300
                                        == 1))) {
                                if (_unitType == Map::Units::UT_E_ENGINEER) {
                                    DAT_UnitsState::instance.units[_unitID].field252_0x3c4 = 0;
                                }
                                if (bVar4) {
                                    if (!_isKeep && !_isWallGatehouseTower) {
                                        if (bVar5) {
                                            _modulo = 3;
                                        } else {
                                            /*
                                              fixme:ucp:feature?: change formations
                                             */
                                            dVar9 = MACRO_CALL_MEMBER(
                                                Map::Navigation::PathFindingState_Func::
                                                    findNextTileByModuloAmongPreviousSearchNotOnDefensiveStructure,
                                                DAT_PathFindingState::ptr)(3, (int)(x1), (int)(_y));
                                            this->ALG_ResultTileIndex = this->ALG_ResultTileIndex + 1;
                                            if (dVar9)
                                                goto LAB_0052691a;
                                            bVar5 = 1;
                                            this->ALG_ResultTileIndex = 0;
                                            _modulo = 3;
                                        }
                                        goto LAB_0052690c;
                                    }
                                    if (bVar5) {
                                    LAB_00526908:
                                        _modulo = 1;
                                        goto LAB_0052690c;
                                    }
                                    dVar9 = MACRO_CALL_MEMBER(
                                        Map::Navigation::PathFindingState_Func::pathFindingResultBased,
                                        DAT_PathFindingState::ptr)(1, (int)(x1), (int)(_y), rallyBool);
                                    this->ALG_ResultTileIndex = this->ALG_ResultTileIndex + 1;
                                    if (!dVar9) {
                                        bVar5 = 1;
                                        this->ALG_ResultTileIndex = 0;
                                        goto LAB_00526908;
                                    }
                                } else {
                                    if (this->tribes[tribeID].unkIsAnimalTribe == 0) {
                                        if ((_isDefensiveStructure) || (_bool1))
                                            goto LAB_00526908;
                                        if (_unitType == Map::Units::UT_S_CATAPULT
                                            || _unitType == Map::Units::UT_S_FBALLISTA
                                            || _unitType == Map::Units::UT_S_TOWER
                                            || _unitType == Map::Units::UT_S_BATTERINGRAM
                                            || _unitType == Map::Units::UT_S_SHIELD) {
                                            _modulo = 4;
                                        } else {
                                            _modulo = 2;
                                        }
                                    } else {
                                        _modulo = 3;
                                    }
                                LAB_0052690c:
                                    MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::
                                                          findNextTileInExistingSearchThatIsModuloDistanceAway,
                                        DAT_PathFindingState::ptr)(_modulo, (int)(x1), (int)(_y));
                                    this->ALG_ResultTileIndex = this->ALG_ResultTileIndex + 1;
                                }
                            LAB_0052691a:
                                if (3999 < this->ALG_ResultTileIndex)
                                    break;
                                DAT_UnitsState::instance.units[_unitID].plannedDestinationX = (short)this->ALG_ResultX;
                                DAT_UnitsState::instance.units[_unitID].plannedDestinationY = (short)this->ALG_ResultY;
                            }
                        } while (_tribeUnitIndex < this->tribes[tribeID].size);
                    }
                    int _tribeIndex_2 = 0;
                    if (0 < this->tribes[tribeID].size) {
                        do {
                            _unitID_2 = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::getUnitIDForIndexInTribe, this)(
                                tribeID, _tribeIndex_2);
                            _tribeIndex_2 = _tribeIndex_2 + 1;
                            if (DAT_UnitsState::instance.units[_unitID_2].logicalState == Map::Units::ULS_NORMAL
                                && DAT_UnitsState::instance.units[_unitID_2].dying == 0
                                && DAT_UnitsState::instance.units[_unitID_2].usingTeleport == 0
                                && DAT_UnitsState::instance.units[_unitID_2].field303_0x413 == 0
                                && (UVar1 = DAT_UnitsState::instance.units[_unitID_2].state.generic,
                                    UVar1 != ((UnitStateShort)0xcf))
                                && DAT_UnitsState::instance.units[_unitID_2].rallyRelatedFlag == 0
                                && DAT_UnitsState::instance.units[_unitID_2].moveRelatedFlag != 1
                                && DAT_UnitsState::instance.units[_unitID_2].moveableUnk != 0
                                && (UVar2 = DAT_UnitsState::instance.units[_unitID_2].unitType,
                                    UVar2 != Map::Units::UT_S_TREBUCHET)
                                && UVar2 != Map::Units::UT_S_MANGONEL && UVar2 != Map::Units::UT_S_BALLISTA
                                && (UVar2 != Map::Units::UT_S_CATAPULT
                                    || (DAT_UnitsState::instance.units[_unitID_2]
                                            .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300
                                        == 2))
                                && (UVar2 != Map::Units::UT_S_FBALLISTA
                                    || (DAT_UnitsState::instance.units[_unitID_2]
                                            .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300
                                        == 2))
                                && (UVar2 != Map::Units::UT_S_TOWER
                                    || (DAT_UnitsState::instance.units[_unitID_2]
                                            .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300
                                        == 4))
                                && (UVar2 != Map::Units::UT_S_BATTERINGRAM
                                    || (DAT_UnitsState::instance.units[_unitID_2]
                                            .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300
                                        == 4))
                                && (UVar2 != Map::Units::UT_S_SHIELD
                                    || (DAT_UnitsState::instance.units[_unitID_2]
                                            .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300
                                        == 1))) {
                                if (UVar1 == Map::Units::States::US_MELEE_ATTACK) {
                                    DAT_UnitsState::instance.units[_unitID_2].movementCooldown
                                        = DAT_UnitsState::instance.units[_unitID_2].movementSpeed * -4;
                                }
                                DAT_UnitsState::instance.units[_unitID_2].state.generic
                                    = Map::Units::States::US_MOVE_TO_DESTINATION;
                                DAT_UnitsState::instance.units[_unitID_2].movementType_OR_targetUnitID = 0;
                                DAT_UnitsState::instance.units[_unitID_2].targetedBuildingTile = 0;
                                if (bVar4) {
                                    DAT_PathFindingState::instance.allAssassinsUnk = 1;
                                } else if (_bool1) {
                                    DAT_PathFindingState::instance.notAllAssassinsUnk = 0;
                                } else {
                                    DAT_PathFindingState::instance.notAllAssassinsUnk
                                        = (int)(!DAT_EntityState::instance.fireCount);
                                }
                                DAT_UnitsState::instance.units[_unitID_2]._someX_2 = 0;
                                DAT_UnitsState::instance.units[_unitID_2]._someY_2 = 0;
                                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::throttledMultiplayerSyncUpdate,
                                    DAT_GameSynchronyState::ptr)();
                                if (UVar1 == Map::Units::States::US_MELEE_ATTACK
                                    || DAT_UnitsState::instance.units[_unitID_2].plannedDestinationX
                                        != DAT_UnitsState::instance.units[_unitID_2].destinationXPosition
                                    || DAT_UnitsState::instance.units[_unitID_2].plannedDestinationY
                                        != DAT_UnitsState::instance.units[_unitID_2].destinationYPosition
                                    || DAT_UnitsState::instance.units[_unitID_2].tunnelerFinishedDigging != 2) {
                                    BVar8 = MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::setDestinationForUnit,
                                        DAT_UnitsState::ptr)(_unitID_2,
                                        (uint)((
                                            int)((int)DAT_UnitsState::instance.units[_unitID_2].plannedDestinationX)),
                                        (uint)((
                                            int)((int)DAT_UnitsState::instance.units[_unitID_2].plannedDestinationY)),
                                        0);
                                    if (!BVar8) {
                                        if (bVar6
                                            && (DAT_TileMapState::instance
                                                    .LogicLayer[DAT_UnitsState::instance.units[_unitID_2].tile]
                                                & 0x10000100U)) {
                                            /*
                                              teleport?
                                             */
                                            MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::setDestinationForUnit,
                                                DAT_UnitsState::ptr)(_unitID_2,
                                                (uint)(_algTile2
                                                    - DAT_ViewportRenderState::instance
                                                        .translationMatrix[DAT_ViewportRenderState::instance
                                                                .tileTranslationMatrix_YComponent[_algTile2]]
                                                        .addXgetTile),
                                                (uint)(DAT_ViewportRenderState::instance
                                                        .tileTranslationMatrix_YComponent[_algTile2]),
                                                0);
                                            DAT_UnitsState::instance.units[_unitID_2].state.generic
                                                = Map::Units::States::US_APPEAR;
                                            DAT_UnitsState::instance.units[_unitID_2]
                                                .targetedUnitUIDUnk_OR_someAppearTileUnk_OR_buildingUID_OR_pitchDitchUID_OR_entityUID
                                                = _algTile;
                                            goto LAB_00526ce4;
                                        }
                                    } else {
                                    LAB_00526ce4:
                                        if (speedMatching != Map::Units::Instructions::UMSE_0)
                                            goto LAB_00526cea;
                                    }
                                } else {
                                LAB_00526cea:
                                    DAT_UnitsState::instance.units[_unitID_2].unitSpeedMatchingRelatedUnk = 0x10;
                                }
                                DAT_PathFindingState::instance.notAllAssassinsUnk = 0;
                                if (!DAT_PathFindingState::instance.field43_0x7c) {
                                    this->field6_0x18 = this->field6_0x18 + 1;
                                } else {
                                    this->field6_0x18 = this->field6_0x18 + -1;
                                }
                            }
                        } while (_tribeIndex_2 < this->tribes[tribeID].size);
                    }
                    MACRO_CALL_MEMBER(Map::Units::TribesState_Func::applyUnitTopSpeedDelayBasedOnTribeSize, this)(
                        tribeID, FALSE);
                    int _tribeIndex_4 = 0;
                    short _tribeSize = this->tribes[tribeID].size;
                    this->tribes[tribeID].someUnitID = 0;
                    if (0 < _tribeSize) {
                        do {
                            /*
                              set move delay
                             */
                            _targetUnitID = MACRO_CALL_MEMBER(
                                Map::Units::TribesState_Func::getUnitIDForIndexInTribe, this)(tribeID, _tribeIndex_4);
                            _tribeIndex_4 = _tribeIndex_4 + 1;
                            if (DAT_UnitsState::instance.units[_targetUnitID].logicalState == Map::Units::ULS_NORMAL
                                && DAT_UnitsState::instance.units[_targetUnitID].dying == 0
                                && DAT_UnitsState::instance.units[_targetUnitID].usingTeleport == 0
                                && DAT_UnitsState::instance.units[_targetUnitID].field303_0x413 == 0
                                && DAT_UnitsState::instance.units[_targetUnitID].state.generic != (UnitStateShort)0xcf
                                && DAT_UnitsState::instance.units[_targetUnitID].rallyRelatedFlag == 0
                                && DAT_UnitsState::instance.units[_targetUnitID].moveRelatedFlag != 1
                                && DAT_UnitsState::instance.units[_targetUnitID].moveableUnk != 0
                                && (UVar2 = DAT_UnitsState::instance.units[_targetUnitID].unitType,
                                    UVar2 != Map::Units::UT_S_TREBUCHET
                                        && ((
                                            ((UVar2 != Map::Units::UT_S_MANGONEL
                                                 && (UVar2 != Map::Units::UT_S_BALLISTA))
                                                && ((UVar2 != Map::Units::UT_S_CATAPULT
                                                    || (DAT_UnitsState::instance.units[_targetUnitID]
                                                            .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300
                                                        == 2))))
                                            && ((UVar2 != Map::Units::UT_S_FBALLISTA
                                                || (DAT_UnitsState::instance.units[_targetUnitID]
                                                        .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300
                                                    == 2))))))
                                && (UVar2 != Map::Units::UT_S_TOWER
                                    || (DAT_UnitsState::instance.units[_targetUnitID]
                                            .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300
                                        == 4))
                                && (UVar2 != Map::Units::UT_S_BATTERINGRAM
                                    || (DAT_UnitsState::instance.units[_targetUnitID]
                                            .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300
                                        == 4))
                                && (UVar2 != Map::Units::UT_S_SHIELD
                                    || (DAT_UnitsState::instance.units[_targetUnitID]
                                            .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300
                                        == 1))) {
                                short sVar3 = DAT_UnitsState::instance.units[_targetUnitID].topSpeedDelayIndex;
                                short sVar10
                                    = (short)DAT_UnitSelectionDefinedData::instance.UnitInstructionMoveDelay[sVar3];
                                if (this->tribes[tribeID].unkIsAnimalTribe == 0) {
                                    if (-1 < this->field6_0x18) {
                                        sVar10 = sVar10 * 2;
                                    }
                                } else {
                                    sVar10 = sVar10 * 3;
                                }
                                DAT_UnitsState::instance.units[_targetUnitID].moveInstructionSpeedDelayTracker = sVar10;
                                if (this->field6_0x18 < 0) {
                                    DAT_UnitsState::instance.units[_targetUnitID].moveDelay = 0;
                                } else {
                                    DAT_UnitsState::instance.units[_targetUnitID].moveDelay
                                        = (short)(DAT_UnitSelectionDefinedData::instance.UnitMoveDelay[sVar3] / 2);
                                }
                                if (DAT_UnitsState::instance.units[_targetUnitID].movementCooldown != 0) {
                                    DAT_UnitsState::instance.units[_targetUnitID].moveDelay = 0;
                                }
                                DAT_UnitsState::instance.units[_targetUnitID].moveInstructionSpeedDelayTracker = 0;
                                DAT_UnitsState::instance.units[_targetUnitID].moveDelay = 0;
                                DAT_UnitsState::instance.units[_targetUnitID].horseArcherShootingVariation = 0;
                                DAT_UnitsState::instance.units[_targetUnitID].targetingType
                                    = Map::Units::UIT_NO_INSTRUCTION_OR_MOVEUnk;
                            }
                        } while (_tribeIndex_4 < this->tribes[tribeID].size);
                    }
                    return (undefined4)(1);
                }
            }
            return (undefined4)(0);
        }

    }
}
}
