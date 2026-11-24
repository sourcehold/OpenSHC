#include "../Units.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/DE/SHCDE/eSFX.hpp"
#include "OpenSHC/Map/Entities/EntityType.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitInstructionType.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentUnitSlotID.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitPropertiesDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x0056ECD0
    void Units::UpdateBallista()
    {
        int const owner = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].owner;
        // counted in the waiting state only, but zeroed here, where the original zeroes it
        int present = 0;
        DAT_GameState::instance.playerDataArray[owner].currentSiegeWeaponCount++;
        DAT_GameState::instance.playerDataArray[owner].armySize++;
        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].isSelectable_OR_matchTime = 1;
        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].calculatedOwnerPlayerIndex = owner;
        UnitStateShort const state = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic;
        if (state == OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk) {
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate = -1;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                = (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                          .facingDirectionMapOrientationCorrected
                      + 4)
                    % 8
                + 1;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].imageIDUnk
                = (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                          .facingDirectionMapOrientationCorrected
                      + 4)
                    % 8
                + 169;
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                    .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300
                != 2) {
                // not fully manned
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = OpenSHC::Map::Units::States::US_FIRE_WEAPONUnk;
                return;
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x3bc < 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x3bc++;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
                return;
            }
            if (DAT_GameSynchronyState::instance
                    .currentPlayerFullIDArray[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].owner]
                == -1) {
                if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::acquireShootTarget, DAT_UnitsState::ptr)(
                        DAT_CurrentUnitSlotID::instance)) {
                    if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                        != OpenSHC::Map::Units::States::US_MOVE_TO_DESTINATION) {
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                            = OpenSHC::Map::Units::States::US_STAND_UPUnk;
                    }
                    return;
                }
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x3bc = -40;
                return;
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].closestEnemyMicroDistance > 680
                && DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetingType
                    != OpenSHC::Map::Units::UIT_ATTACK_LAND
                && DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetingType
                    != OpenSHC::Map::Units::UIT_ATTACK_BUILDING) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x3bc = -40;
                return;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::acquireShootTarget, DAT_UnitsState::ptr)(
                    DAT_CurrentUnitSlotID::instance)) {
                if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::checkTargetBuildingPossibilityOrState,
                        DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance)) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].shootBeforeStop = 10;
                } else if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].shootBeforeStop > 0) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].shootBeforeStop--;
                } else if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].shootBeforeStop == 0) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x3bc = -80;
                    return;
                }
                if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    != OpenSHC::Map::Units::States::US_MOVE_TO_DESTINATION) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                        = OpenSHC::Map::Units::States::US_STAND_UPUnk;
                }
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x3bc = -40;
            }
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_FIRE_WEAPONUnk) {
            // waiting for engineers to man the ballista
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x58 = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                = (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                          .facingDirectionMapOrientationCorrected
                      + 4)
                    % 8
                + 1;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].imageIDUnk = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
            if (DAT_GameSynchronyState::instance
                        .currentPlayerFullIDArray[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].owner]
                    == -1
                && DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                        .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300
                    == 2) {
                // the AI's engineers have been moved away: check whether both are back
                for (int i = 0; i < 2; ++i) {
                    int const engineer
                        = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].manningEngineerRef[i];
                    if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].manningEngineerUIDRef[i]
                            != DAT_UnitsState::instance.units[engineer].uid
                        || !MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::hasUnitReachedDestination,
                            DAT_UnitsState::ptr)(engineer)
                        || abs(DAT_UnitsState::instance.units[engineer].terrainOrClimbHeight
                               - DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].terrainOrClimbHeight
                               - DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].buildingHeight
                               + DAT_UnitsState::instance.units[engineer].buildingHeight)
                            > 16) {
                        break;
                    }
                    short const ownX = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].microXPosition;
                    short const otherX = DAT_UnitsState::instance.units[engineer].microXPosition;
                    int dx;
                    if (otherX > ownX) {
                        dx = otherX - ownX;
                    } else {
                        dx = ownX - otherX;
                    }
                    short const ownY = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].microYPosition;
                    short const otherY = DAT_UnitsState::instance.units[engineer].microYPosition;
                    int dy;
                    if (otherY > ownY) {
                        dy = otherY - ownY;
                    } else {
                        dy = ownY - otherY;
                    }
                    int distance = dy;
                    if (dx > dy) {
                        distance = dx;
                    }
                    if (distance < 30) {
                        present++;
                    }
                }
                if (present == 2) {
                    for (int i = 0; i < 2; ++i) {
                        int const engineer
                            = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].manningEngineerRef[i];
                        DAT_UnitsState::instance.units[engineer].animationCycleNumber = 0;
                        DAT_UnitsState::instance.units[engineer].state.generic
                            = OpenSHC::Map::Units::States::US_JESTER_ROAM_TO;
                        DAT_UnitsState::instance.units[engineer].disappearFadeAlphaCountdown = 0;
                        DAT_UnitsState::instance.units[engineer].engineerManningSiegeStateRef_checkType = 2;
                        DAT_UnitsState::instance.units[engineer].cachedState
                            = OpenSHC::Map::Units::States::US_AIM_WEAPONUnk;
                        DAT_UnitsState::instance.units[engineer].updateTickTracker = 0;
                    }
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                        = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
                    return;
                }
            }
            if (((DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].fixedRng
                     ^ DAT_GameState::instance.mapAndTime.totalGameTicksUnk ^ 8)
                    & 15)
                != 0) {
                return;
            }
            // look for two engineers that were sent to man this ballista
            int crew[2];
            int count = 0;
            for (int i = 1; i < DAT_UnitsState::instance.maxUnitCount; ++i) {
                if (DAT_UnitsState::instance.units[i].logicalState != OpenSHC::Map::Units::ULS_NORMAL
                    || DAT_UnitsState::instance.units[i].dying != 0 || DAT_UnitsState::instance.units[i].owner != owner
                    || DAT_UnitsState::instance.units[i].unitType != OpenSHC::Map::Units::UT_E_ENGINEER
                    || DAT_UnitsState::instance.units[i].targetingType != OpenSHC::Map::Units::UIT_MAN_SIEGE_EQUIPMENT
                    || DAT_UnitsState::instance.units[i].targetedUnitID__OR__engineerMannedSiegeEngineRef
                        != DAT_CurrentUnitSlotID::instance
                    || abs(DAT_UnitsState::instance.units[i].terrainOrClimbHeight
                           - DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].buildingHeight
                           - DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].terrainOrClimbHeight
                           + DAT_UnitsState::instance.units[i].buildingHeight)
                        > 16) {
                    continue;
                }
                int dx;
                if (DAT_UnitsState::instance.units[i].microXPosition
                    > DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].microXPosition) {
                    dx = DAT_UnitsState::instance.units[i].microXPosition
                        - DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].microXPosition;
                } else {
                    dx = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].microXPosition
                        - DAT_UnitsState::instance.units[i].microXPosition;
                }
                int dy;
                if (DAT_UnitsState::instance.units[i].microYPosition
                    > DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].microYPosition) {
                    dy = DAT_UnitsState::instance.units[i].microYPosition
                        - DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].microYPosition;
                } else {
                    dy = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].microYPosition
                        - DAT_UnitsState::instance.units[i].microYPosition;
                }
                int distance = dy;
                if (dx > dy) {
                    distance = dx;
                }
                if (distance < 30) {
                    crew[count] = i;
                    count++;
                    if (count >= 2) {
                        break;
                    }
                }
            }
            if (count != 2) {
                return;
            }
            for (int i = 0; i < countof(crew); ++i) {
                int const engineer = crew[i];
                DAT_UnitsState::instance.units[engineer].animationCycleNumber = 0;
                DAT_UnitsState::instance.units[engineer].disappearFadeAlphaCountdown = 0;
                DAT_UnitsState::instance.units[engineer].updateTickTracker = 0;
                DAT_UnitsState::instance.units[engineer].state.generic = OpenSHC::Map::Units::States::US_JESTER_ROAM_TO;
                DAT_UnitsState::instance.units[engineer].engineerManningSiegeStateRef_checkType = 2;
                DAT_UnitsState::instance.units[engineer].cachedState = OpenSHC::Map::Units::States::US_AIM_WEAPONUnk;
                DAT_UnitsState::instance.units[engineer].targetingType
                    = OpenSHC::Map::Units::UIT_NO_INSTRUCTION_OR_MOVEUnk;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].manningEngineerRef[i] = engineer;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].manningEngineerUIDRef[i]
                    = DAT_UnitsState::instance.units[engineer].uid;
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::deselectUnit, DAT_UnitsState::ptr)(engineer);
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::clearOrDeselectUnitFromSelection,
                    DAT_UnitsState::ptr)(DAT_UnitsState::instance.units[engineer].owner, engineer, 0);
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300 = 2;
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_LOOK_AROUNDUnk) {
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x58 = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                = (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                          .facingDirectionMapOrientationCorrected
                      + 4)
                    % 8
                + 1;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].imageIDUnk
                = (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                          .facingDirectionMapOrientationCorrected
                      + 4)
                    % 8
                + 169;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x3bc < 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x3bc++;
                return;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::acquireShootTarget, DAT_UnitsState::ptr)(
                    DAT_CurrentUnitSlotID::instance)) {
                if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    != OpenSHC::Map::Units::States::US_MOVE_TO_DESTINATION) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                        = OpenSHC::Map::Units::States::US_FIRE_WEAPONUnk;
                }
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x3bc = -200;
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_STAND_UPUnk) {
            // aiming
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSpeed = 4;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x58 = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                = (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                          .facingDirectionMapOrientationCorrected
                      + 4)
                    % 8
                + 1;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].imageIDUnk
                = (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                          .facingDirectionMapOrientationCorrected
                      + 4)
                    % 8
                + 169;
            if (!DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                    .animationCycleNumberHasJustIncremented) {
                return;
            }
            int targetX = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].shootTargetMicroX / 8;
            int targetY = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].shootTargetMicroY / 8;
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetingType
                    == OpenSHC::Map::Units::UIT_ATTACK_BUILDING
                && DAT_BuildingsState::instance
                        .buildings[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                                .targetID_OR_targetBuildingID]
                        .uid
                    == DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                        .targetedUnitUIDUnk_OR_someAppearTileUnk_OR_buildingUID_OR_pitchDitchUID_OR_entityUID) {
                int const halfSize = (int)DAT_BuildingsState::instance
                                         .buildings[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                                                 .targetID_OR_targetBuildingID]
                                         .widthOrHeight
                    / 2;
                targetX = DAT_BuildingsState::instance
                              .buildings[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                                      .targetID_OR_targetBuildingID]
                              .x
                    + halfSize;
                targetY = DAT_BuildingsState::instance
                              .buildings[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                                      .targetID_OR_targetBuildingID]
                              .y
                    + halfSize;
            }
            int const dy = targetY - DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].y;
            int const dx = targetX - DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].x;
            if (dx * dx + dy * dy > 7225) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x3bc = -40;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
                return;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setUnitFacingDirectionForTargetXandY,
                    DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance, targetX, targetY)) {
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                = OpenSHC::Map::Units::States::US_STATE_2Unk;
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_STATE_2Unk) {
            // loading
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSpeed = 8;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x58 = 0;
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumberHasJustIncremented
                && DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber == 2) {
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].x,
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].y,
                    OpenSHC::DE::SHCDE::FX_BALLISTA_LOAD);
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.field_0x1b14
                      [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame <= 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = OpenSHC::Map::Units::States::US_RELOAD_WEAPONUnk;
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                = (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                          .facingDirectionMapOrientationCorrected
                      + 4)
                    % 8
                - 7 + DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame * 8;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].imageIDUnk
                = (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                          .facingDirectionMapOrientationCorrected
                      + 4)
                    % 8
                - 7
                + (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.field_0x1b50
                        [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber]
                    * 8;
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_RELOAD_WEAPONUnk) {
            // firing
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSpeed = 2;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumberHasJustIncremented
                && DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber == 2) {
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].x,
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].y,
                    OpenSHC::DE::SHCDE::FX_BALLISTA_FIRE);
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.field_0x1b8c
                      [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame > 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                              .facingDirectionMapOrientationCorrected
                          + 4)
                        % 8
                    - 7 + DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame * 8;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].imageIDUnk
                    = (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                              .facingDirectionMapOrientationCorrected
                          + 4)
                        % 8
                    - 7
                    + (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.field_0x1bc8
                            [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber]
                        * 8;
            }
            if (DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.field_0x1b8c
                        [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber]
                    == 12
                && DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                    .animationCycleNumberHasJustIncremented) {
                int heightOffset = 26;
                if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].shootTargetedUnit < 0) {
                    heightOffset = 0;
                }
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::prepareProjectileTarget, DAT_UnitsState::ptr)(
                    DAT_CurrentUnitSlotID::instance, -1, 200);
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::shootProjectile, DAT_UnitsState::ptr)(
                    DAT_CurrentUnitSlotID::instance, OpenSHC::Map::Entities::ET_BALLISTA,
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].shootTargetMicroX,
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].shootTargetMicroY,
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].shootTargetZ + heightOffset);
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame == 0
                && DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                    .animationCycleNumberHasJustIncremented) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame > 0) {
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_DEATH_01 || state == OpenSHC::Map::Units::States::US_DEATH_03
            || state == OpenSHC::Map::Units::States::US_STONE_DEATH_01) {
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSpeed = 2;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                = (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                          .facingDirectionMapOrientationCorrected
                      + 4)
                    % 8
                + 337;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].imageIDUnk = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].imageID2 = 0;
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber == 0
                && DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].killedFlagUnk == 0) {
                // the crew dies with the ballista
                for (int i = 0; i < DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                                    .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300;
                    ++i) {
                    int const engineer
                        = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].manningEngineerRef[i];
                    if (DAT_UnitsState::instance.units[engineer].uid
                        != DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].manningEngineerUIDRef[i]) {
                        continue;
                    }
                    DAT_UnitsState::instance.units[engineer].logicalState = OpenSHC::Map::Units::ULS_REMOVE;
                    if (owner == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                        DAT_GameState::instance.mapAndTime
                            .hitsDealtToPlayerArray[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                                    .lastEncounteredEnemyPlayerID]++;
                    } else if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                                   .lastEncounteredEnemyPlayerID
                        == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                        DAT_GameState::instance.mapAndTime.emenyHitArray[owner]++;
                    }
                }
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber++;
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber > 900) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].logicalState
                    = OpenSHC::Map::Units::ULS_REMOVE;
                int const building
                    = DAT_TileMapState::instance
                          .BuildingLayer[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].tile];
                if (building != 0) {
                    DAT_BuildingsState::instance.buildings[building].defensiveTowerEngineType = 0;
                }
            }
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_MOVE_TO_DESTINATION) {
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSpeed = 2;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].facingDirectionMapOrientationCorrected
                + 1;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_DISAPPEAR
            || state == OpenSHC::Map::Units::States::US_JESTER_ROAM_TO) {
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].disappearFadeAlphaCountdown++;
            if ((char)DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].disappearFadeAlphaCountdown
                > 32) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].disappearFadeAlphaCountdown = 32;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].updateTickTracker++;
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].updateTickTracker > 32) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].logicalState
                    = OpenSHC::Map::Units::ULS_REMOVE;
                int const building
                    = DAT_TileMapState::instance
                          .BuildingLayer[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].tile];
                if (building != 0) {
                    DAT_BuildingsState::instance.buildings[building].defensiveTowerEngineType = 0;
                }
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].killedFlagUnk == 0
                && DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                        .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300
                    == 2) {
                MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::processUnitLossStatistic,
                    DAT_GameState::ptr)(owner, DAT_CurrentUnitSlotID::instance);
            }
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_STATE_9Unk) {
            // dismantled
            for (int i = 0; i < DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                                .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300;
                ++i) {
                int const engineer
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].manningEngineerRef[i];
                if (DAT_UnitsState::instance.units[engineer].uid
                    == DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].manningEngineerUIDRef[i]) {
                    DAT_UnitsState::instance.units[engineer].logicalState = OpenSHC::Map::Units::ULS_REMOVE;
                }
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].logicalState
                = OpenSHC::Map::Units::ULS_REMOVE;
        }
    }

}
}
