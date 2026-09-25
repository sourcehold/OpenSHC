#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Units.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/DE/SHCDE/eSFX.hpp"
#include "OpenSHC/Map/Entities/EntityType.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitInstructionType.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

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

    using OpenSHC::DE::SHCDE::eSFX;
    using OpenSHC::Map::Entities::EntityType;
    using OpenSHC::Map::Units::UnitInstructionType;
    using OpenSHC::Map::Units::UnitLogicState;
    using OpenSHC::Map::Units::UnitType;
    using OpenSHC::Map::Units::States::UnitState;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x0056ECD0
    void Units::UpdateBallista()
    {
        int unitID = DAT_CurrentUnitSlotID::instance;
        int owner = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].owner;
        DAT_GameState::instance.playerDataArray[owner].currentSiegeWeaponCount += 1;
        DAT_GameState::instance.playerDataArray[owner].armySize += 1;
        DAT_UnitsState::instance.units[unitID].isSelectable_OR_matchTime = 1;
        DAT_UnitsState::instance.units[unitID].calculatedOwnerPlayerIndex = owner;
        UnitStateShort state = DAT_UnitsState::instance.units[unitID].state.generic;
        if (state == OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk) {
            DAT_UnitsState::instance.units[unitID].substate = -1;
            DAT_UnitsState::instance.units[unitID].stateBasedSpeed = 0;
            DAT_UnitsState::instance.units[unitID].gfxNumber
                = (DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected + 4) % 8 + 1;
            DAT_UnitsState::instance.units[unitID].imageIDUnk
                = (DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected + 4) % 8 + 0xa9;
            if (DAT_UnitsState::instance.units[unitID]
                    .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300
                != 2) {
                // not fully manned
                DAT_UnitsState::instance.units[unitID].state.generic = OpenSHC::Map::Units::States::US_FIRE_WEAPONUnk;
                return;
            }
            if (DAT_UnitsState::instance.units[unitID].field248_0x3bc < 0) {
                DAT_UnitsState::instance.units[unitID].field248_0x3bc += 1;
                DAT_UnitsState::instance.units[unitID].state.generic
                    = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
                return;
            }
            if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[DAT_UnitsState::instance.units[unitID].owner]
                == -1) {
                if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::acquireShootTarget, DAT_UnitsState::ptr)(
                        unitID)
                    == FALSE) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field248_0x3bc = -40;
                    return;
                }
                if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    != OpenSHC::Map::Units::States::US_MOVE_TO_DESTINATION) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                        = OpenSHC::Map::Units::States::US_STAND_UPUnk;
                }
                return;
            }
            if (DAT_UnitsState::instance.units[unitID].closestEnemyMicroDistance > 680
                && DAT_UnitsState::instance.units[unitID].targetingType != OpenSHC::Map::Units::UIT_ATTACK_LAND
                && DAT_UnitsState::instance.units[unitID].targetingType != OpenSHC::Map::Units::UIT_ATTACK_BUILDING) {
                DAT_UnitsState::instance.units[unitID].field248_0x3bc = -40;
                return;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::acquireShootTarget, DAT_UnitsState::ptr)(unitID)
                == FALSE) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field248_0x3bc = -40;
                return;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::checkTargetBuildingPossibilityOrState,
                    DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance)
                != FALSE) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].shootBeforeStop = 10;
            } else if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].shootBeforeStop > 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].shootBeforeStop -= 1;
            } else if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].shootBeforeStop == 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field248_0x3bc = -80;
                return;
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                != OpenSHC::Map::Units::States::US_MOVE_TO_DESTINATION) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = OpenSHC::Map::Units::States::US_STAND_UPUnk;
            }
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_FIRE_WEAPONUnk) {
            // waiting for engineers to man the ballista
            DAT_UnitsState::instance.units[unitID].field39_0x58 = 0;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[unitID].gfxNumber
                = (DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected + 4) % 8 + 1;
            DAT_UnitsState::instance.units[unitID].imageIDUnk = 0;
            DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
            if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[DAT_UnitsState::instance.units[unitID].owner]
                    == -1
                && DAT_UnitsState::instance.units[unitID]
                        .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300
                    == 2) {
                // the AI's engineers have been moved away: check whether both are back
                int present = 0;
                for (int i = 0; i < 2; ++i) {
                    int engineer = DAT_UnitsState::instance.units[unitID].manningEngineerRef[i];
                    if (DAT_UnitsState::instance.units[unitID].manningEngineerUIDRef[i]
                            != DAT_UnitsState::instance.units[engineer].uid
                        || MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::hasUnitReachedDestination,
                               DAT_UnitsState::ptr)(engineer)
                            == FALSE
                        || abs(DAT_UnitsState::instance.units[engineer].buildingHeight
                               - DAT_UnitsState::instance.units[unitID].buildingHeight
                               - DAT_UnitsState::instance.units[unitID].terrainOrClimbHeight
                               + DAT_UnitsState::instance.units[engineer].terrainOrClimbHeight)
                            > 16) {
                        break;
                    }
                    int dx = DAT_UnitsState::instance.units[unitID].microXPosition
                            < DAT_UnitsState::instance.units[engineer].microXPosition
                        ? DAT_UnitsState::instance.units[engineer].microXPosition
                            - DAT_UnitsState::instance.units[unitID].microXPosition
                        : DAT_UnitsState::instance.units[unitID].microXPosition
                            - DAT_UnitsState::instance.units[engineer].microXPosition;
                    int dy = DAT_UnitsState::instance.units[unitID].microYPosition
                            < DAT_UnitsState::instance.units[engineer].microYPosition
                        ? DAT_UnitsState::instance.units[engineer].microYPosition
                            - DAT_UnitsState::instance.units[unitID].microYPosition
                        : DAT_UnitsState::instance.units[unitID].microYPosition
                            - DAT_UnitsState::instance.units[engineer].microYPosition;
                    if ((dy < dx ? dx : dy) < 30) {
                        present += 1;
                    }
                }
                if (present == 2) {
                    int first = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].manningEngineerRef[0];
                    DAT_UnitsState::instance.units[first].animationCycleNumber = 0;
                    DAT_UnitsState::instance.units[first].disappearFadeAlphaCountdown = 0;
                    DAT_UnitsState::instance.units[first].engineerManningSiegeStateRef_checkType = 2;
                    DAT_UnitsState::instance.units[first].updateTickTracker = 0;
                    DAT_UnitsState::instance.units[first].state.generic
                        = OpenSHC::Map::Units::States::US_JESTER_ROAM_TO;
                    DAT_UnitsState::instance.units[first].cachedState = OpenSHC::Map::Units::States::US_AIM_WEAPONUnk;
                    int second = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].manningEngineerRef[1];
                    DAT_UnitsState::instance.units[second].animationCycleNumber = 0;
                    DAT_UnitsState::instance.units[second].state.generic
                        = OpenSHC::Map::Units::States::US_JESTER_ROAM_TO;
                    DAT_UnitsState::instance.units[second].disappearFadeAlphaCountdown = 0;
                    DAT_UnitsState::instance.units[second].engineerManningSiegeStateRef_checkType = 2;
                    DAT_UnitsState::instance.units[second].cachedState = OpenSHC::Map::Units::States::US_AIM_WEAPONUnk;
                    DAT_UnitsState::instance.units[second].updateTickTracker = 0;
                    DAT_UnitsState::instance.units[unitID].state.generic
                        = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
                    return;
                }
            }
            if (((DAT_UnitsState::instance.units[unitID].fixedRng
                     ^ DAT_GameState::instance.mapAndTime.totalGameTicksUnk)
                    & 15)
                != 8) {
                return;
            }
            // look for two engineers that were sent to man this ballista
            int crew[2];
            int count = 0;
            for (int i = 1; i < (int)DAT_UnitsState::instance.maxUnitCount; ++i) {
                if (DAT_UnitsState::instance.units[i].logicalState != OpenSHC::Map::Units::ULS_NORMAL
                    || DAT_UnitsState::instance.units[i].dying != 0 || DAT_UnitsState::instance.units[i].owner != owner
                    || DAT_UnitsState::instance.units[i].unitType != OpenSHC::Map::Units::UT_E_ENGINEER
                    || DAT_UnitsState::instance.units[i].targetingType != OpenSHC::Map::Units::UIT_MAN_SIEGE_EQUIPMENT
                    || DAT_UnitsState::instance.units[i].targetedUnitID__OR__engineerMannedSiegeEngineRef
                        != DAT_CurrentUnitSlotID::instance
                    || abs(DAT_UnitsState::instance.units[i].terrainOrClimbHeight
                           - DAT_UnitsState::instance.units[unitID].buildingHeight
                           - DAT_UnitsState::instance.units[unitID].terrainOrClimbHeight
                           + DAT_UnitsState::instance.units[i].buildingHeight)
                        > 16) {
                    continue;
                }
                int dx = DAT_UnitsState::instance.units[unitID].microXPosition
                        < DAT_UnitsState::instance.units[i].microXPosition
                    ? DAT_UnitsState::instance.units[i].microXPosition
                        - DAT_UnitsState::instance.units[unitID].microXPosition
                    : DAT_UnitsState::instance.units[unitID].microXPosition
                        - DAT_UnitsState::instance.units[i].microXPosition;
                int dy = DAT_UnitsState::instance.units[unitID].microYPosition
                        < DAT_UnitsState::instance.units[i].microYPosition
                    ? DAT_UnitsState::instance.units[i].microYPosition
                        - DAT_UnitsState::instance.units[unitID].microYPosition
                    : DAT_UnitsState::instance.units[unitID].microYPosition
                        - DAT_UnitsState::instance.units[i].microYPosition;
                if ((dy < dx ? dx : dy) < 30) {
                    crew[count] = i;
                    count += 1;
                    if (count >= 2) {
                        break;
                    }
                }
            }
            if (count != 2) {
                return;
            }
            for (int i = 0; i < 2; ++i) {
                DAT_UnitsState::instance.units[crew[i]].animationCycleNumber = 0;
                DAT_UnitsState::instance.units[crew[i]].disappearFadeAlphaCountdown = 0;
                DAT_UnitsState::instance.units[crew[i]].updateTickTracker = 0;
                DAT_UnitsState::instance.units[crew[i]].state.generic = OpenSHC::Map::Units::States::US_JESTER_ROAM_TO;
                DAT_UnitsState::instance.units[crew[i]].engineerManningSiegeStateRef_checkType = 2;
                DAT_UnitsState::instance.units[crew[i]].cachedState = OpenSHC::Map::Units::States::US_AIM_WEAPONUnk;
                DAT_UnitsState::instance.units[crew[i]].targetingType
                    = OpenSHC::Map::Units::UIT_NO_INSTRUCTION_OR_MOVEUnk;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].manningEngineerRef[i] = (short)crew[i];
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].manningEngineerUIDRef[i]
                    = DAT_UnitsState::instance.units[crew[i]].uid;
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::deselectUnit, DAT_UnitsState::ptr)(crew[i]);
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::clearOrDeselectUnitFromSelection,
                    DAT_UnitsState::ptr)(DAT_UnitsState::instance.units[crew[i]].owner, crew[i], 0);
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300 = 2;
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_LOOK_AROUNDUnk) {
            DAT_UnitsState::instance.units[unitID].field39_0x58 = 0;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[unitID].gfxNumber
                = (DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected + 4) % 8 + 1;
            DAT_UnitsState::instance.units[unitID].imageIDUnk
                = (DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected + 4) % 8 + 0xa9;
            DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
            if (DAT_UnitsState::instance.units[unitID].field248_0x3bc < 0) {
                DAT_UnitsState::instance.units[unitID].field248_0x3bc += 1;
                return;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::acquireShootTarget, DAT_UnitsState::ptr)(unitID)
                == FALSE) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field248_0x3bc = -200;
                return;
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                != OpenSHC::Map::Units::States::US_MOVE_TO_DESTINATION) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = OpenSHC::Map::Units::States::US_FIRE_WEAPONUnk;
            }
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_STAND_UPUnk) {
            // aiming
            DAT_UnitsState::instance.units[unitID].animationSpeed = 4;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[unitID].field39_0x58 = 0;
            DAT_UnitsState::instance.units[unitID].gfxNumber
                = (DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected + 4) % 8 + 1;
            DAT_UnitsState::instance.units[unitID].imageIDUnk
                = (DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected + 4) % 8 + 0xa9;
            if (DAT_UnitsState::instance.units[unitID].animationCycleNumberHasJustIncremented == FALSE) {
                return;
            }
            int targetX = DAT_UnitsState::instance.units[unitID].shootTargetMicroX / 8;
            int targetY = DAT_UnitsState::instance.units[unitID].shootTargetMicroY / 8;
            if (DAT_UnitsState::instance.units[unitID].targetingType == OpenSHC::Map::Units::UIT_ATTACK_BUILDING
                && DAT_BuildingsState::instance
                        .buildings[DAT_UnitsState::instance.units[unitID].targetID_OR_targetBuildingID]
                        .uid
                    == DAT_UnitsState::instance.units[unitID]
                        .targetedUnitUIDUnk_OR_someAppearTileUnk_OR_buildingUID_OR_pitchDitchUID_OR_entityUID) {
                int halfSize = DAT_BuildingsState::instance
                                   .buildings[DAT_UnitsState::instance.units[unitID].targetID_OR_targetBuildingID]
                                   .widthOrHeight
                    / 2;
                targetX = DAT_BuildingsState::instance
                              .buildings[DAT_UnitsState::instance.units[unitID].targetID_OR_targetBuildingID]
                              .x
                    + halfSize;
                targetY = DAT_BuildingsState::instance
                              .buildings[DAT_UnitsState::instance.units[unitID].targetID_OR_targetBuildingID]
                              .y
                    + halfSize;
            }
            int dy = targetY - DAT_UnitsState::instance.units[unitID].y;
            int dx = targetX - DAT_UnitsState::instance.units[unitID].x;
            if (dx * dx + dy * dy > 7225) {
                DAT_UnitsState::instance.units[unitID].field248_0x3bc = -40;
                DAT_UnitsState::instance.units[unitID].state.generic
                    = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
                return;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setUnitFacingDirectionForTargetXandY,
                    DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance, targetX, targetY)
                != FALSE) {
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic = (UnitState)2;
            return;
        }
        if (state == (UnitState)2) {
            // loading
            DAT_UnitsState::instance.units[unitID].animationSpeed = 8;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[unitID].field39_0x58 = 0;
            if (DAT_UnitsState::instance.units[unitID].animationCycleNumberHasJustIncremented != FALSE
                && DAT_UnitsState::instance.units[unitID].animationCycleNumber == 2) {
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    DAT_UnitsState::instance.units[unitID].x, DAT_UnitsState::instance.units[unitID].y,
                    OpenSHC::DE::SHCDE::FX_BALLISTA_LOAD);
            }
            DAT_UnitsState::instance.units[unitID].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp
                      .field88_0x1b14[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
            if (DAT_UnitsState::instance.units[unitID].animationFrame <= 0) {
                DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
                DAT_UnitsState::instance.units[unitID].state.generic = OpenSHC::Map::Units::States::US_RELOAD_WEAPONUnk;
                return;
            }
            DAT_UnitsState::instance.units[unitID].gfxNumber
                = (DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected + 4) % 8 - 7
                + DAT_UnitsState::instance.units[unitID].animationFrame * 8;
            DAT_UnitsState::instance.units[unitID].imageIDUnk
                = (DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected + 4) % 8 - 7
                + (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp
                        .field89_0x1b50[DAT_UnitsState::instance.units[unitID].animationCycleNumber]
                    * 8;
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_RELOAD_WEAPONUnk) {
            // firing
            DAT_UnitsState::instance.units[unitID].animationSpeed = 2;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            if (DAT_UnitsState::instance.units[unitID].animationCycleNumberHasJustIncremented != FALSE
                && DAT_UnitsState::instance.units[unitID].animationCycleNumber == 2) {
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    DAT_UnitsState::instance.units[unitID].x, DAT_UnitsState::instance.units[unitID].y,
                    OpenSHC::DE::SHCDE::FX_BALLISTA_FIRE);
            }
            DAT_UnitsState::instance.units[unitID].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp
                      .field90_0x1b8c[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
            if (DAT_UnitsState::instance.units[unitID].animationFrame > 0) {
                DAT_UnitsState::instance.units[unitID].gfxNumber
                    = (DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected + 4) % 8 - 7
                    + DAT_UnitsState::instance.units[unitID].animationFrame * 8;
                DAT_UnitsState::instance.units[unitID].imageIDUnk
                    = (DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected + 4) % 8 - 7
                    + (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp
                            .field91_0x1bc8[DAT_UnitsState::instance.units[unitID].animationCycleNumber]
                        * 8;
            }
            if (DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp
                        .field90_0x1b8c[DAT_UnitsState::instance.units[unitID].animationCycleNumber]
                    == 12
                && DAT_UnitsState::instance.units[unitID].animationCycleNumberHasJustIncremented != FALSE) {
                int heightOffset = DAT_UnitsState::instance.units[unitID].shootTargetedUnit < 0 ? 0 : 26;
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::prepareProjectileTarget, DAT_UnitsState::ptr)(
                    unitID, -1, 200);
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::shootProjectile, DAT_UnitsState::ptr)(
                    DAT_CurrentUnitSlotID::instance, OpenSHC::Map::Entities::ET_BALLISTA,
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].shootTargetMicroX,
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].shootTargetMicroY,
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].shootTargetZ + heightOffset);
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame == 0
                && DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                        .animationCycleNumberHasJustIncremented
                    != FALSE) {
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
            DAT_UnitsState::instance.units[unitID].animationSpeed = 2;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[unitID].gfxNumber
                = (DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected + 4) % 8 + 0x151;
            DAT_UnitsState::instance.units[unitID].imageIDUnk = 0;
            DAT_UnitsState::instance.units[unitID].imageID2 = 0;
            if (DAT_UnitsState::instance.units[unitID].animationCycleNumber == 0
                && DAT_UnitsState::instance.units[unitID].killedFlagUnk == 0) {
                // the crew dies with the ballista
                for (int i = 0; i < DAT_UnitsState::instance.units[unitID]
                                    .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300;
                    ++i) {
                    if (DAT_UnitsState::instance.units[DAT_UnitsState::instance.units[unitID].manningEngineerRef[i]].uid
                        != DAT_UnitsState::instance.units[unitID].manningEngineerUIDRef[i]) {
                        continue;
                    }
                    DAT_UnitsState::instance.units[DAT_UnitsState::instance.units[unitID].manningEngineerRef[i]]
                        .logicalState = OpenSHC::Map::Units::ULS_REMOVE;
                    if (owner == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                        DAT_GameState::instance.mapAndTime
                            .ownLossesArray[DAT_UnitsState::instance.units[unitID].lastEncounteredEnemyPlayerID] += 1;
                    } else if (DAT_UnitsState::instance.units[unitID].lastEncounteredEnemyPlayerID
                        == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                        DAT_GameState::instance.mapAndTime.emenyHitArray[owner] += 1;
                    }
                }
            }
            DAT_UnitsState::instance.units[unitID].animationCycleNumber += 1;
            if (DAT_UnitsState::instance.units[unitID].animationCycleNumber > 900) {
                DAT_UnitsState::instance.units[unitID].logicalState = OpenSHC::Map::Units::ULS_REMOVE;
                if ((short)DAT_TileMapState::instance.BuildingLayer[DAT_UnitsState::instance.units[unitID].tile] != 0) {
                    DAT_BuildingsState::instance
                        .buildings[(
                            short)DAT_TileMapState::instance.BuildingLayer[DAT_UnitsState::instance.units[unitID].tile]]
                        .containsSiegeMangonel1OrBallista2 = 0;
                }
            }
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_MOVE_TO_DESTINATION) {
            DAT_UnitsState::instance.units[unitID].animationSpeed = 2;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[unitID].gfxNumber
                = DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected + 1;
            DAT_UnitsState::instance.units[unitID].state.generic
                = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_DISAPPEAR
            || state == OpenSHC::Map::Units::States::US_JESTER_ROAM_TO) {
            DAT_UnitsState::instance.units[unitID].disappearFadeAlphaCountdown += 1;
            if ((char)DAT_UnitsState::instance.units[unitID].disappearFadeAlphaCountdown > 32) {
                DAT_UnitsState::instance.units[unitID].disappearFadeAlphaCountdown = 32;
            }
            DAT_UnitsState::instance.units[unitID].updateTickTracker += 1;
            if (DAT_UnitsState::instance.units[unitID].updateTickTracker > 32) {
                DAT_UnitsState::instance.units[unitID].logicalState = OpenSHC::Map::Units::ULS_REMOVE;
                if ((short)DAT_TileMapState::instance.BuildingLayer[DAT_UnitsState::instance.units[unitID].tile] != 0) {
                    DAT_BuildingsState::instance
                        .buildings[(
                            short)DAT_TileMapState::instance.BuildingLayer[DAT_UnitsState::instance.units[unitID].tile]]
                        .containsSiegeMangonel1OrBallista2 = 0;
                }
            }
            if (DAT_UnitsState::instance.units[unitID].killedFlagUnk == 0
                && DAT_UnitsState::instance.units[unitID]
                        .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300
                    == 2) {
                MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::processUnitLossStatistic,
                    DAT_GameState::ptr)(owner, unitID);
            }
            return;
        }
        if (state == (UnitState)9) {
            // dismantled
            for (int i = 0; i < DAT_UnitsState::instance.units[unitID]
                                .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300;
                ++i) {
                if (DAT_UnitsState::instance.units[DAT_UnitsState::instance.units[unitID].manningEngineerRef[i]].uid
                    == DAT_UnitsState::instance.units[unitID].manningEngineerUIDRef[i]) {
                    DAT_UnitsState::instance.units[DAT_UnitsState::instance.units[unitID].manningEngineerRef[i]]
                        .logicalState = OpenSHC::Map::Units::ULS_REMOVE;
                }
            }
            DAT_UnitsState::instance.units[unitID].logicalState = OpenSHC::Map::Units::ULS_REMOVE;
        }
    }

}
}
