#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/LandscapeState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentUnitSlotID.hpp"
#include "OpenSHC/Globals/DAT_LandscapeState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitPropertiesDefinedData.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Buildings::BuildingType;
        using OpenSHC::Map::Units::UnitType;
        using OpenSHC::Map::Units::States::UnitState;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00578C40
        undefined4 UnitsState::processUnitMove(int unitID, int speedCategory)
        {
            if (this->units[unitID].unitType != OpenSHC::Map::Units::UT_BURNINGMAN) {
                if (this->units[unitID].unitType == OpenSHC::Map::Units::UT_A_ASSASSIN
                    && (this->units[unitID].state.generic == OpenSHC::Map::Units::States::US_ASSASSIN_THROWING_HOOK
                        || this->units[unitID].state.generic
                            == OpenSHC::Map::Units::States::US_ASSASSIN_START_CLIMBING_DOWN
                        || this->units[unitID].state.generic == OpenSHC::Map::Units::States::US_ASSASSIN_CLIMBING_UP
                        || this->units[unitID].state.generic
                            == OpenSHC::Map::Units::States::US_ASSASSIN_CLIMBING_DOWN)) {
                    return 0;
                }
                if (this->units[unitID].dying != 0) {
                    return 0;
                }
            }
            if (this->units[unitID].tunnelerFinishedDigging == 5) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setupUnitSharingCurrentTilePosition, this)(
                    unitID);
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::commitPendingUnitPosition, this)(unitID);
                this->units[unitID].field39_0x58 = 0;
                return 0;
            }
            if (this->units[unitID].tunnelerFinishedDigging != 4 && this->units[unitID].tunnelerFinishedDigging != 2) {
                this->units[unitID].movementRelated = 8;
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::updateMicroPosition, this)(unitID);
                if (this->units[unitID].climbDataID != 0
                    && MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::updateClimbing, this)(unitID) == FALSE) {
                    MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit, this)(
                        unitID, this->units[unitID].destinationX_2Unk, this->units[unitID].destinationY_2Unk, 0);
                    MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::changeDestinationByLeftover, this)(unitID);
                }
                return 0;
            }
            this->units[unitID].field39_0x58 = 0;
            if (this->units[unitID].moveInstructionSpeedDelayTracker != 0) {
                this->units[unitID].moveInstructionSpeedDelayTracker
                    = this->units[unitID].moveInstructionSpeedDelayTracker - 1;
            }
            if (this->units[unitID].moveDelay < 2) {
                this->units[unitID].moveDelay = 0;
            } else {
                this->units[unitID].moveDelay = this->units[unitID].moveDelay - 2;
            }
            int _steps = speedCategory + this->units[unitID].field259_0x3d2;
            for (int _step = 0; _step <= _steps; ++_step) {
                if (this->units[DAT_CurrentUnitSlotID::instance].field180_0x32d == '\x01') {
                    if (this->units[DAT_CurrentUnitSlotID::instance].field218_0x37e < 4
                        || this->units[DAT_CurrentUnitSlotID::instance].field218_0x37e > 0xb) {
                        continue;
                    }
                } else if (this->units[DAT_CurrentUnitSlotID::instance].field180_0x32d == '\x02') {
                    if (this->units[DAT_CurrentUnitSlotID::instance].field218_0x37e <= 4) {
                        continue;
                    }
                    if (this->units[DAT_CurrentUnitSlotID::instance].field218_0x37e >= 10) {
                        if (this->units[DAT_CurrentUnitSlotID::instance].field218_0x37e > 0xb) {
                            this->units[DAT_CurrentUnitSlotID::instance].field218_0x37e = 3;
                        }
                        continue;
                    }
                }
                this->units[unitID].field105_0xe8 = 0;
                this->units[unitID].movementRelated = this->units[unitID].movementRelated + 1;
                if (this->units[unitID].movementRelated < 8) {
                    if (DAT_UnitPropertiesDefinedData::instance.field79_0x119cc[this->units[unitID].facingDirection]
                        <= this->units[unitID].movementRelated) {
                        this->units[unitID].field105_0xe8 = 1;
                    }
                } else {
                    int _pathIndex = this->units[unitID].currentIndexInPathPlan;
                    if (this->units[unitID].totalSizeOfPathPlan <= (short)_pathIndex
                        && this->units[unitID].field280_0x3f4 == 0) {
                        this->units[unitID].unknownMovementRelated_0x2d2 = 0;
                        this->units[unitID].tunnelerFinishedDigging = 0;
                        this->units[unitID].movementRelated = 8;
                        this->units[unitID].destinationY_2Unk = this->units[unitID].y;
                        this->units[unitID].destinationX_2Unk = this->units[unitID].x;
                        return 0;
                    }
                    this->units[unitID].movementRelated = 0;
                    uint _direction = (char)this->units[unitID].pathPlanStart[(short)_pathIndex / 2];
                    if ((_pathIndex & 1) == 0) {
                        _direction = _direction & 0xf;
                    } else {
                        _direction = (int)_direction >> 4;
                    }
                    this->units[unitID].facingDirection = (short)_direction;
                    if (this->units[unitID].field280_0x3f4 == 0) {
                        this->units[unitID].currentIndexInPathPlan = _pathIndex + 1;
                    }
                    if (this->units[unitID].field259_0x3d2 != 0) {
                        MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::saveUnitStateBeforeInterruption, this)(
                            unitID);
                        this->units[unitID].movementRelated = 8;
                        this->units[unitID].lookForEnemy = 0;
                        this->units[unitID].state.generic = OpenSHC::Map::Units::States::US_MELEE_ATTACK;
                        this->units[unitID].SA = 0;
                        this->units[unitID].animationCycleNumber = 0;
                        return 0;
                    }
                    if (this->units[unitID].moveRelatedFlag != 1) {
                        if (this->units[unitID].field280_0x3f4 != 0
                            || MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::doMoveFromTileToTile,
                                   DAT_PathFindingState::ptr)(unitID, this->units[unitID].tile, this->units[unitID].y,
                                   _direction, this->units[unitID].moveRelatedFlag, this->units[unitID].cannotClimb)
                                == FALSE) {
                            this->units[unitID].movementRelated = 8;
                            if (this->units[unitID].field280_0x3f4 > 0) {
                                this->units[unitID].field280_0x3f4 = this->units[unitID].field280_0x3f4 - 1;
                                if (this->units[unitID].field280_0x3f4 > 0) {
                                    return 0;
                                }
                            }
                            this->unknownInitially0_01 = this->unknownInitially0_01 + 1;
                            int _destinationY = this->units[unitID].destinationYPosition;
                            int _destinationX = this->units[unitID].destinationXPosition;
                            bool _destinationReachable = false;
                            if (MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::xyAreValid,
                                    DAT_ViewportRenderState::ptr)(_destinationX, _destinationY)
                                == FALSE) {
                                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::
                                                      makeUnitStopWalkingByClearingPathProgressState,
                                    this)(unitID);
                            } else if ((short)DAT_TileMapState::instance
                                           .PathConnectionLayer[DAT_ViewportRenderState::instance
                                                                    .translationMatrix[_destinationY]
                                                                    .addXgetTile
                                               + _destinationX]
                                != 0) {
                                if (MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::
                                                          calculateCanPlayerUnitsNavigateToAreaFromArea,
                                        DAT_PathFindingState::ptr)(this->units[unitID].owner,
                                        (short)DAT_TileMapState::instance.PathConnectionLayer[this->units[unitID].tile],
                                        (short)DAT_TileMapState::instance
                                            .PathConnectionLayer[DAT_ViewportRenderState::instance
                                                                     .translationMatrix[_destinationY]
                                                                     .addXgetTile
                                                + _destinationX],
                                        0)
                                    != 0) {
                                    _destinationReachable = true;
                                }
                            }
                            if (!_destinationReachable) {
                                if (this->units[unitID].unitType == OpenSHC::Map::Units::UT_LORD) {
                                    return 0;
                                }
                                if (this->units[unitID].isSelectable_OR_matchTime != 0) {
                                    return 0;
                                }
                                if (this->units[unitID].unitType == OpenSHC::Map::Units::UT_CAGEDOG) {
                                    MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::
                                                          makeUnitStopWalkingByClearingPathProgressState,
                                        this)(unitID);
                                    return 0;
                                }
                                if (this->units[unitID].state.generic != OpenSHC::Map::Units::States::US_DISAPPEAR) {
                                    this->units[unitID].state.generic = OpenSHC::Map::Units::States::US_DISAPPEAR;
                                    this->units[unitID].updateTickTracker = 0;
                                    return 0;
                                }
                            }
                            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit, this)(
                                    DAT_CurrentUnitSlotID::instance, this->units[unitID].destinationXPosition,
                                    this->units[unitID].destinationYPosition, 0)
                                == FALSE) {
                                this->units[unitID].field280_0x3f4 = 0x28;
                                return 0;
                            }
                            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::changeDestinationByLeftover, this)(
                                unitID);
                            return 0;
                        }
                        MACRO_CALL_MEMBER(OpenSHC::Map::LandscapeState_Func::spawnCrowFromNearbyTree,
                            DAT_LandscapeState::ptr)(unitID);
                    }
                    this->units[unitID].currentTilePosition_2Unk = this->units[unitID].tile;
                    this->units[unitID].nextTileUnk
                        = DAT_TileMapState::instance.directionTranslationMatrix[this->units[unitID].y][_direction]
                        + this->units[unitID].tile;
                    this->units[unitID].mimicCurrentXPosition
                        = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction].short_.xOffset
                        + this->units[unitID].x;
                    this->units[unitID].mimicCurrentYPosition
                        = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction].short_.yOffset
                        + this->units[unitID].y;
                    this->units[unitID].microXPosition = this->units[unitID].x * 8 + 4;
                    this->units[unitID].microYPosition = this->units[unitID].y * 8 + 4;
                }
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setupUnitSharingCurrentTilePosition, this)(
                    unitID);
                switch (this->units[unitID].facingDirection) {
                case 0:
                    this->units[unitID].microYPosition = this->units[unitID].microYPosition - 1;
                    break;
                case 1:
                    this->units[unitID].microYPosition = this->units[unitID].microYPosition - 1;
                case 2:
                    this->units[unitID].microXPosition = this->units[unitID].microXPosition + 1;
                    break;
                case 3:
                    this->units[unitID].microYPosition = this->units[unitID].microYPosition + 1;
                    this->units[unitID].microXPosition = this->units[unitID].microXPosition + 1;
                    break;
                case 4:
                    this->units[unitID].microYPosition = this->units[unitID].microYPosition + 1;
                    break;
                case 5:
                    this->units[unitID].microYPosition = this->units[unitID].microYPosition + 1;
                case 6:
                    this->units[unitID].microXPosition = this->units[unitID].microXPosition - 1;
                    break;
                case 7:
                    this->units[unitID].microYPosition = this->units[unitID].microYPosition - 1;
                    this->units[unitID].microXPosition = this->units[unitID].microXPosition - 1;
                }
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::commitPendingUnitPosition, this)(unitID);
                if (this->units[unitID].field105_0xe8 == 0) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::Map::Units::UnitsState_Func::
                            adjustUnitMapOrientationRelatedPositionBasedOnMapOrientationCorrectedFacingDirection,
                        this)(unitID);
                } else {
                    MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::updateMicroPosition, this)(unitID);
                    MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::processDamageFromKillingPit,
                        DAT_BuildingsState::ptr)(unitID);
                    if (DAT_TileMapState::instance.BuildingLayer[this->units[unitID].tile] != 0
                        && (DAT_BuildingsState::instance
                                    .buildings[DAT_TileMapState::instance.BuildingLayer[this->units[unitID].tile]]
                                    .buildingType
                                == OpenSHC::Map::Buildings::BT_TOWER1
                            || DAT_BuildingsState::instance
                                    .buildings[DAT_TileMapState::instance.BuildingLayer[this->units[unitID].tile]]
                                    .buildingType
                                == OpenSHC::Map::Buildings::BT_TOWER4)) {
                        DAT_BuildingsState::instance
                            .buildings[DAT_TileMapState::instance.BuildingLayer[this->units[unitID].tile]]
                            .hasUnitsOntop = 1;
                        DAT_BuildingsState::instance
                            .buildings[DAT_TileMapState::instance.BuildingLayer[this->units[unitID].tile]]
                            .field261_0x2fa = 100;
                    }
                }
                this->units[unitID].field105_0xe8 = 0;
                MACRO_CALL_MEMBER(
                    OpenSHC::Map::Units::UnitsState_Func::updateUnitFadeAndVisibilityNearStructures, this)(unitID);
            }
            return 1;
        }

    }
}
}
