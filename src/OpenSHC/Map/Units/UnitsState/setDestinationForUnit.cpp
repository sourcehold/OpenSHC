#include "../UnitsState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitPropertiesDefinedData.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0053D3D0
        BOOLEnum UnitsState::setDestinationForUnit(int unitID, uint x, uint y, int reusePathingInfo)
        {
            /* check by unit type */
            int _ableToClimbTowers
                = DAT_UnitPropertiesDefinedData::instance.ABLE_TO_CLIMB_TOWERS[this->units[unitID].unitType];
            if (x > 399 || y > 399 || DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y * 400 + x] == 0) {
                DAT_PathFindingState::instance.allAssassinsUnk = 0;
                return FALSE;
            }
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::teleportUnitToUnitXAndY, this)(unitID);
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::unitIsInMoat, this)(unitID) != FALSE) {
                DAT_PathFindingState::instance.climbIsIllegal = 1;
            }
            int _unitX = this->units[unitID].x;
            this->units[unitID].climbDataID = 0;
            this->units[unitID].destinationX_2Unk = x;
            this->units[unitID].destinationY_2Unk = y;
            this->units[unitID].field_0x3f4 = 0;
            if (_unitX == x && this->units[unitID].y == y) {
                this->units[unitID].destinationYPosition = y;
                this->units[unitID].totalSizeOfPathPlan = 0;
                this->units[unitID].tunnelerFinishedDigging = 0;
                this->units[unitID].currentIndexInPathPlan = 0;
                this->units[unitID].destinationXPosition = x;
                this->units[unitID].destinationTilePosition
                    = (short)x + DAT_ViewportRenderState::instance.translationMatrix[(short)y].addXgetTile;
                this->units[unitID].ladderExitXPosition = this->units[unitID].x;
                this->units[unitID].ladderExitYPosition = this->units[unitID].y;
                this->units[unitID].previousTilePosition
                    = DAT_ViewportRenderState::instance.translationMatrix[this->units[unitID].y].addXgetTile + _unitX;
                DAT_PathFindingState::instance.climbIsIllegal = 0;
                DAT_PathFindingState::instance.allAssassinsUnk = 0;
                return TRUE;
            }
            dword _fromArea
                = (short)DAT_TileMapState::instance.PathConnectionLayer
                      [DAT_ViewportRenderState::instance.translationMatrix[this->units[unitID].y].addXgetTile + _unitX];
            int _destinationTile = DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x;
            dword _toArea = DAT_TileMapState::instance.PathConnectionLayer[_destinationTile];
            if ((DAT_TileMapState::instance.LogicLayer[_destinationTile] & 0x30) != 0) {
                DAT_PathFindingState::instance.allAssassinsUnk = 0;
                return FALSE;
            }
            this->units[unitID].field_0x2a8 = _toArea;
            if (_ableToClimbTowers == 0
                && (DAT_TileMapState::instance.LogicLayer[_destinationTile] & 0x10000100U) != 0) {
                DAT_PathFindingState::instance.allAssassinsUnk = 0;
                return FALSE;
            }
            if (_fromArea != _toArea) {
                if (DAT_PathFindingState::instance.climbIsIllegal != 0) {
                    _fromArea = MACRO_CALL_MEMBER(
                        OpenSHC::Map::Navigation::PathFindingState_Func::canNavigateFunctionReturnsArea,
                        DAT_PathFindingState::ptr)(
                        this->units[unitID].owner, _toArea, this->units[unitID].x, this->units[unitID].y);
                    if (_fromArea != _toArea) {
                        this->units[unitID].field_0x2a8
                            = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::
                                                    calculateCanPlayerUnitsNavigateToAreaFromArea,
                                DAT_PathFindingState::ptr)(
                                this->units[unitID].owner, _fromArea, _toArea, this->units[unitID].unitCanClimb);
                        if (this->units[unitID].field_0x2a8 == 0) {
                            DAT_PathFindingState::instance.climbIsIllegal = 0;
                            DAT_PathFindingState::instance.allAssassinsUnk = 0;
                            this->units[unitID].movementCooldown = 0;
                            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::despawnUnreachableUnit, this)(
                                unitID);
                            return FALSE;
                        }
                        this->units[unitID].climbDataID = MACRO_CALL_MEMBER(
                            OpenSHC::Map::Navigation::PathFindingState_Func::setClimbBasedOnClosestClimbData,
                            DAT_PathFindingState::ptr)(unitID, _fromArea, this->units[unitID].field_0x2a8);
                        if (this->units[unitID].climbDataID == 0) {
                            DAT_PathFindingState::instance.climbIsIllegal = 0;
                            DAT_PathFindingState::instance.allAssassinsUnk = 0;
                            this->units[unitID].movementCooldown = 0;
                            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::despawnUnreachableUnit, this)(
                                unitID);
                            return FALSE;
                        }
                        int const _registerResult = MACRO_CALL_MEMBER(
                            OpenSHC::Map::Navigation::PathFindingState_Func::registerUnitOnClimbData,
                            DAT_PathFindingState::ptr)(this->units[unitID].climbDataID, unitID);
                        if (_registerResult == 1) {
                            /* walk to the climb first */
                            x = DAT_PathFindingState::instance.climbX;
                            y = DAT_PathFindingState::instance.climbY;
                        } else if (_registerResult == -1) {
                            DAT_PathFindingState::instance.climbIsIllegal = 0;
                            DAT_PathFindingState::instance.allAssassinsUnk = 0;
                            this->units[unitID].movementCooldown = 0;
                            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::despawnUnreachableUnit, this)(
                                unitID);
                            return FALSE;
                        }
                    }
                } else if (DAT_PathFindingState::instance.allAssassinsUnk == 0 && reusePathingInfo == 0) {
                    this->units[unitID].field_0x2a8 = MACRO_CALL_MEMBER(
                        OpenSHC::Map::Navigation::PathFindingState_Func::calculateCanPlayerUnitsNavigateToAreaFromArea,
                        DAT_PathFindingState::ptr)(
                        this->units[unitID].owner, _fromArea, _toArea, this->units[unitID].unitCanClimb);
                    if (this->units[unitID].field_0x2a8 == 0) {
                        DAT_PathFindingState::instance.climbIsIllegal = 0;
                        DAT_PathFindingState::instance.allAssassinsUnk = 0;
                        this->units[unitID].movementCooldown = 0;
                        MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::despawnUnreachableUnit, this)(unitID);
                        return FALSE;
                    }
                    this->units[unitID].climbDataID = MACRO_CALL_MEMBER(
                        OpenSHC::Map::Navigation::PathFindingState_Func::setClimbBasedOnClosestClimbData,
                        DAT_PathFindingState::ptr)(unitID, _fromArea, this->units[unitID].field_0x2a8);
                    if (this->units[unitID].climbDataID == 0) {
                        DAT_PathFindingState::instance.climbIsIllegal = 0;
                        DAT_PathFindingState::instance.allAssassinsUnk = 0;
                        this->units[unitID].movementCooldown = 0;
                        MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::despawnUnreachableUnit, this)(unitID);
                        return FALSE;
                    }
                    int const _registerResult
                        = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::registerUnitOnClimbData,
                            DAT_PathFindingState::ptr)(this->units[unitID].climbDataID, unitID);
                    if (_registerResult == 1) {
                        /* walk to the climb first */
                        x = DAT_PathFindingState::instance.climbX;
                        y = DAT_PathFindingState::instance.climbY;
                    } else if (_registerResult == -1) {
                        DAT_PathFindingState::instance.climbIsIllegal = 0;
                        DAT_PathFindingState::instance.allAssassinsUnk = 0;
                        this->units[unitID].movementCooldown = 0;
                        MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::despawnUnreachableUnit, this)(unitID);
                        return FALSE;
                    }
                }
            }
            MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::copyData, DAT_LowLevelMemory::ptr)(
                sizeof(Unit), &this->units[unitID], this->units);
            MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                sizeof(this->units[unitID].pathPlanStart), '\0', this->units[unitID].pathPlanStart);
            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::bindPathPlanToAlgorithmStateAndReset,
                DAT_PathFindingState::ptr)(this->units[unitID].pathPlanStart);
            DAT_PathFindingState::instance.unitX = this->units[unitID].x;
            DAT_PathFindingState::instance.unitY = this->units[unitID].y;
            DAT_PathFindingState::instance.destinationX = x;
            DAT_PathFindingState::instance.destinationY = y;
            if (this->units[unitID].isSelectable_OR_matchTime == 0) {
                DAT_PathFindingState::instance.notAllAssassinsUnk = 1;
            }
            if (this->units[unitID].field_0x90 != 0) {
                DAT_PathFindingState::instance.notAllAssassinsUnk = 1;
            }
            int _pathPlanSize;
            if (reusePathingInfo != 0) {
                _pathPlanSize
                    = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::retraceAndCommitPathPlan,
                        DAT_PathFindingState::ptr)();
            } else {
                _pathPlanSize = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::doPathfinding,
                    DAT_PathFindingState::ptr)(this->units[unitID].owner, _ableToClimbTowers);
            }
            DAT_PathFindingState::instance.notAllAssassinsUnk = 0;
            if (_pathPlanSize <= 0) {
                DAT_PathFindingState::instance.climbIsIllegal = 0;
                DAT_PathFindingState::instance.allAssassinsUnk = 0;
                this->units[unitID].movementCooldown = 0;
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::despawnUnreachableUnit, this)(unitID);
                return FALSE;
            }
            this->units[unitID].totalSizeOfPathPlan = _pathPlanSize;
            this->units[unitID].tunnelerFinishedDigging = 2;
            this->units[unitID].currentIndexInPathPlan = 0;
            this->units[unitID].destinationXPosition = x;
            this->units[unitID].destinationYPosition = y;
            this->units[unitID].ladderExitYPosition = this->units[unitID].y;
            this->units[unitID].destinationTilePosition
                = (short)x + DAT_ViewportRenderState::instance.translationMatrix[(short)y].addXgetTile;
            this->units[unitID].ladderExitXPosition = this->units[unitID].x;
            this->units[unitID].previousTilePosition = this->units[unitID].x
                + DAT_ViewportRenderState::instance.translationMatrix[this->units[unitID].y].addXgetTile;
            this->units[unitID].cannotClimb = DAT_PathFindingState::instance.climbIsIllegal != 0;
            DAT_PathFindingState::instance.climbIsIllegal = 0;
            DAT_PathFindingState::instance.allAssassinsUnk = 0;
            return TRUE;
        }

    }
}
}
