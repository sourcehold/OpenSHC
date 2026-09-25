#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Units.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/DE/SHCDE/eSFX.hpp"
#include "OpenSHC/Map/Units/Pathfinding/DestinationNeededEnum.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentUnitSlotID.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitHasBecomeIdle.hpp"
#include "OpenSHC/Globals/DAT_UnitPropertiesDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::DE::SHCDE::eSFX;
    using OpenSHC::Map::Units::UnitLogicState;
    using OpenSHC::Map::Units::Pathfinding::DestinationNeededEnum;
    using OpenSHC::Map::Units::States::UnitState;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x0056F9B0
    void Units::UpdateCageDog()
    {
        int unitID = DAT_CurrentUnitSlotID::instance;
        int tribe = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].tribeID;
        int kennel = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].workplaceBuildingID_1;
        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed = 0;
        DAT_GameState::instance.mapAndTime.field3172_0x27ac += 1;
        if ((char)DAT_UnitsState::instance.units[unitID].disappearFadeAlphaCountdown > 0
            && DAT_UnitsState::instance.units[unitID].state.generic != OpenSHC::Map::Units::States::US_DISAPPEAR) {
            DAT_UnitsState::instance.units[unitID].disappearFadeAlphaCountdown -= 1;
        }
        if (DAT_UnitsState::instance.units[unitID].unknownBool01 != 0) {
            DAT_UnitsState::instance.units[unitID].unknownBool01 -= 1;
        }
        // the dogs vanish together with their kennel
        if (DAT_UnitsState::instance.units[unitID].dying == 0
            && DAT_BuildingsState::instance.buildings[DAT_UnitsState::instance.units[unitID].workplaceBuildingID_1].uid
                != DAT_UnitsState::instance.units[unitID].workplaceBuildingUID) {
            DAT_UnitsState::instance.units[unitID].dying = 1;
            DAT_UnitsState::instance.units[unitID].state.generic = OpenSHC::Map::Units::States::US_DISAPPEAR;
            DAT_UnitsState::instance.units[unitID].disappearFadeAlphaCountdown = 0;
            DAT_UnitsState::instance.units[unitID].updateTickTracker = 0;
        }
        UnitStateShort state = DAT_UnitsState::instance.units[unitID].state.generic;
        if (state == OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk) {
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            MACRO_CALL_MEMBER(
                OpenSHC::Map::Units::UnitsState_Func::setUnitFacingDirectionTowardsTarget, DAT_UnitsState::ptr)(
                DAT_CurrentUnitSlotID::instance, DAT_TribesState::instance.tribes[tribe].selectionTargetUnitID);
            int enemy = MACRO_CALL_MEMBER(
                OpenSHC::Map::Units::UnitsState_Func::findClosestEnemyByAreaAndRange, DAT_UnitsState::ptr)(15,
                DAT_BuildingsState::instance
                    .buildings[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].workplaceBuildingID_1]
                    .buildingEntryX,
                DAT_BuildingsState::instance
                    .buildings[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].workplaceBuildingID_1]
                    .buildingEntryY,
                DAT_BuildingsState::instance.buildings[kennel].owner);
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::tryAttackUnitID, DAT_UnitsState::ptr)(
                    DAT_CurrentUnitSlotID::instance, enemy)
                == 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic = (UnitState)0xd3;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].destinationNeeded
                    = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_NEEDED;
            }
            return;
        }
        if (state == (UnitState)0xd2) {
            // waiting in the kennel until enough enemies are close
            DAT_UnitsState::instance.units[unitID].updateTickTracker += 1;
            if (DAT_UnitsState::instance.units[unitID].updateTickTracker
                <= DAT_UnitsState::instance.units[unitID].cagedogReleaseCheckMoment * 8 + 32) {
                return;
            }
            DAT_UnitsState::instance.units[unitID].updateTickTracker
                = DAT_UnitsState::instance.units[unitID].cagedogReleaseCheckMoment * 8;
            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::computeTotalUnitsWithinDistance,
                DAT_PathFindingState::ptr)(DAT_BuildingsState::instance.buildings[kennel].owner, 0, 1,
                DAT_UnitsState::instance.units[unitID].tile, 16);
            if (DAT_PathFindingState::instance.ALGO_TotalTroopValue > 25
                || DAT_PathFindingState::instance.ALGO_TotalTroopCount > 5) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::resetUnitMovementState, DAT_UnitsState::ptr)(
                    DAT_CurrentUnitSlotID::instance);
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = OpenSHC::Map::Units::States::US_JESTER_ROAM_TO;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].disappearFadeAlphaCountdown = 31;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].engineerManningSiegeStateRef_checkType
                    = 0xfe;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].cachedState
                    = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
            }
            return;
        }
        if (state == (UnitState)0xd3) {
            // returning to the kennel
            DAT_UnitsState::instance.units[unitID].movementSpeed = 3;
            DAT_UnitsState::instance.units[unitID].stateBasedSpeed = 1;
            DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset = 1;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0x10;
            if (DAT_UnitsState::instance.units[unitID].destinationNeeded
                    != OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET
                && MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::buildingIsAccessible,
                       DAT_BuildingsState::ptr)(kennel, 1)
                    != 0
                && MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit, DAT_UnitsState::ptr)(
                       DAT_CurrentUnitSlotID::instance, DAT_BuildingsState::instance.buildings[kennel].buildingEntryX,
                       DAT_BuildingsState::instance.buildings[kennel].buildingEntryY, 0)
                    != FALSE) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].destinationNeeded
                    = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::hasUnitReachedDestination, DAT_UnitsState::ptr)(
                    DAT_CurrentUnitSlotID::instance)
                != FALSE) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = OpenSHC::Map::Units::States::US_JESTER_ROAM_TO;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].disappearFadeAlphaCountdown = 0;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].engineerManningSiegeStateRef_checkType
                    = 2;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].cachedState = 0xd2;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].updateTickTracker = 0;
            }
            return;
        }
        if (state == (UnitState)0xd0) {
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::makeUnitStopWalkingByClearingPathProgressState,
                DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance);
            if (DAT_UnitsState::instance.units[unitID].movementRelated > 7) {
                DAT_UnitsState::instance.units[unitID].state.generic
                    = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
            }
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_MOVE_TO_DESTINATION || state == (UnitState)120) {
            if (DAT_UnitsState::instance.units[unitID].substate == 100) {
                DAT_UnitsState::instance.units[unitID].movementSpeed = 20;
                DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
                DAT_UnitsState::instance.units[unitID].animationSpeed
                    = (DAT_UnitsState::instance.units[unitID].fixedRng & 7) + 1;
                if (DAT_UnitsState::instance.units[unitID].field250_0x3c2 == 0) {
                    DAT_UnitsState::instance.units[unitID].animationFrame
                        = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp
                              .field346_0x6d98[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
                } else {
                    DAT_UnitsState::instance.units[unitID].animationFrame
                        = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp
                              .field347_0x6db8[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
                }
                if (DAT_UnitsState::instance.units[unitID].animationFrame > 0) {
                    if (DAT_UnitsState::instance.units[unitID].field250_0x3c2 == 0) {
                        DAT_UnitsState::instance.units[unitID].gfxNumber
                            = DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected + 0x2b0
                            + DAT_UnitsState::instance.units[unitID].animationFrame * 8;
                        return;
                    }
                    DAT_UnitsState::instance.units[unitID].gfxNumber
                        = DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected + 0x270
                        + DAT_UnitsState::instance.units[unitID].animationFrame * 8;
                    return;
                }
                DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
                DAT_UnitsState::instance.units[unitID].seated = 0;
                DAT_UnitsState::instance.units[unitID].substate = DAT_UnitsState::instance.units[unitID].fixedRng & 1;
                DAT_UnitsState::instance.units[unitID].gfxNumber
                    += DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected;
                return;
            }
            DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
            if (DAT_TribesState::instance.tribes[tribe].field133_0x278 == 0) {
                DAT_UnitsState::instance.units[unitID].movementSpeed = 3;
                DAT_UnitsState::instance.units[unitID].stateBasedSpeed = 1;
                DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset = 1;
            } else {
                DAT_UnitsState::instance.units[unitID].movementSpeed = 1;
                DAT_UnitsState::instance.units[unitID].moveInstructionSpeedDelayTracker = 0;
                DAT_UnitsState::instance.units[unitID].stateBasedSpeed = 2;
                DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset = 0x101;
            }
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0x10;
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::hasUnitReachedDestination, DAT_UnitsState::ptr)(
                    DAT_CurrentUnitSlotID::instance)
                != FALSE) {
                DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
                DAT_UnitsState::instance.units[unitID].substate = DAT_UnitsState::instance.units[unitID].fixedRng & 1;
                DAT_UnitsState::instance.units[unitID].state.generic
                    = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
            }
            return;
        }
        if (state == (UnitState)0xcf) {
            // chasing an enemy
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0x10;
            DAT_UnitsState::instance.units[unitID].movementSpeed = 2;
            DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
            if (DAT_UnitsState::instance.units[unitID].destinationNeeded
                != OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET) {
                DAT_UnitsState::instance.units[unitID].destinationNeeded
                    = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET;
                short enemy = DAT_UnitsState::instance.units[unitID].targetedUnitID__OR__engineerMannedSiegeEngineRef;
                if (enemy != 0) {
                    if (DAT_UnitsState::instance.units[unitID]
                                .targetedUnitUIDUnk_OR_someAppearTileUnk_OR_buildingUID_OR_pitchDitchUID_OR_entityUID
                            == DAT_UnitsState::instance.units[enemy].uid
                        && DAT_UnitsState::instance.units[enemy].dying == 0
                        && DAT_UnitsState::instance.units[enemy].unknownTestAgainst0_2 == 0) {
                        if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit,
                                DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance,
                                DAT_UnitsState::instance.units[enemy].x, DAT_UnitsState::instance.units[enemy].y, 0)
                            == FALSE) {
                            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                                .targetedUnitID__OR__engineerMannedSiegeEngineRef = 0;
                        }
                    } else {
                        DAT_UnitsState::instance.units[unitID].targetedUnitID__OR__engineerMannedSiegeEngineRef = 0;
                    }
                }
                if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                        .targetedUnitID__OR__engineerMannedSiegeEngineRef
                    == 0) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].movementType_OR_targetUnitID = 0;
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate
                        = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].fixedRng & 1;
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                        = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
                    return;
                }
            }
            if (DAT_UnitsState::instance.units[unitID].currentIndexInPathPlan < 5
                && DAT_UnitsState::instance.units[unitID].totalSizeOfPathPlan > 8) {
                DAT_UnitsState::instance.units[unitID].stateBasedSpeed = 0;
                DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset = 0x81;
                DAT_UnitsState::instance.units[unitID].movementSpeed = 2;
            } else {
                DAT_UnitsState::instance.units[unitID].moveInstructionSpeedDelayTracker = 0;
                DAT_UnitsState::instance.units[unitID].stateBasedSpeed = 1;
                DAT_UnitsState::instance.units[unitID].movementSpeed = 1;
                DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset = 0x101;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::hasUnitReachedDestination, DAT_UnitsState::ptr)(
                    DAT_CurrentUnitSlotID::instance)
                != FALSE) {
                DAT_UnitsState::instance.units[unitID].destinationNeeded
                    = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_NEEDED;
            }
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_MELEE_ATTACK) {
            DAT_UnitsState::instance.units[unitID].animationSpeed = 2;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            if (DAT_UnitsState::instance.units[unitID].animationCycleNumber > 50) {
                DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
            }
            if (DAT_UnitsState::instance.units[unitID].substate == 0) {
                DAT_UnitsState::instance.units[unitID].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp
                          .field350_0x7060[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
            } else if (DAT_UnitsState::instance.units[unitID].substate == 1) {
                DAT_UnitsState::instance.units[unitID].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp
                          .field351_0x7078[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
            } else if (DAT_UnitsState::instance.units[unitID].substate == 2) {
                DAT_UnitsState::instance.units[unitID].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp
                          .field352_0x7098[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
            } else if (DAT_UnitsState::instance.units[unitID].substate == 3) {
                DAT_UnitsState::instance.units[unitID].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp
                          .field353_0x70c0[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
            } else {
                DAT_UnitsState::instance.units[unitID].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp
                          .field354_0x70e0[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
            }
            if (DAT_UnitsState::instance.units[unitID].animationCycleNumber == 1
                && DAT_UnitsState::instance.units[unitID].animationCycleNumberHasJustIncremented != FALSE) {
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    DAT_UnitsState::instance.units[unitID].x, DAT_UnitsState::instance.units[unitID].y,
                    OpenSHC::DE::SHCDE::FX_WOLF_ATTACK);
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame <= 0) {
                DAT_UnitHasBecomeIdle::instance = 1;
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                          .facingDirectionMapOrientationCorrected
                    + 0x179 + DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame * 8;
            }
            if (DAT_UnitHasBecomeIdle::instance == 0) {
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate += 1;
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate > 4) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate = 1;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::resumeMovementIfNoAttackTarget,
                DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance);
            DAT_TribesState::instance.tribes[tribe].unknownCounter01 = 0;
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_JESTER_ROAM_TO) {
            DAT_UnitsState::instance.units[unitID].disappearFadeAlphaCountdown
                += DAT_UnitsState::instance.units[unitID].engineerManningSiegeStateRef_checkType;
            if ((char)DAT_UnitsState::instance.units[unitID].disappearFadeAlphaCountdown < 0) {
                DAT_UnitsState::instance.units[unitID].disappearFadeAlphaCountdown = 0;
            } else if ((char)DAT_UnitsState::instance.units[unitID].disappearFadeAlphaCountdown > 31) {
                DAT_UnitsState::instance.units[unitID].disappearFadeAlphaCountdown = 31;
            }
            if (DAT_UnitsState::instance.units[unitID].disappearFadeAlphaCountdown == 0
                && (char)DAT_UnitsState::instance.units[unitID].engineerManningSiegeStateRef_checkType < 0) {
                DAT_UnitsState::instance.units[unitID].updateTickTracker = 0;
                DAT_UnitsState::instance.units[unitID].state.generic
                    = DAT_UnitsState::instance.units[unitID].cachedState;
            }
            if (DAT_UnitsState::instance.units[unitID].disappearFadeAlphaCountdown == 31
                && (char)DAT_UnitsState::instance.units[unitID].engineerManningSiegeStateRef_checkType > 0) {
                DAT_UnitsState::instance.units[unitID].updateTickTracker = 0;
                DAT_UnitsState::instance.units[unitID].disappearFadeAlphaCountdown = 0;
                DAT_UnitsState::instance.units[unitID].state.generic
                    = DAT_UnitsState::instance.units[unitID].cachedState;
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::commitUnitLocation, DAT_UnitsState::ptr)(
                    DAT_CurrentUnitSlotID::instance);
            }
            return;
        }
        if (state == (UnitState)0xce) {
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[unitID].animationSpeed = 4;
            DAT_UnitsState::instance.units[unitID].gfxNumber = 0x278;
            DAT_UnitsState::instance.units[unitID].field250_0x3c2 = 1;
            if (DAT_UnitsState::instance.units[unitID].seated == 0) {
                DAT_UnitsState::instance.units[unitID].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp
                          .field345_0x6d7c[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
            } else {
                DAT_UnitsState::instance.units[unitID].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp
                          .field355_0x7134[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
            }
            if (DAT_UnitsState::instance.units[unitID].animationFrame <= 0) {
                DAT_UnitsState::instance.units[unitID].gfxNumber
                    += DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected + 0x18;
                DAT_UnitHasBecomeIdle::instance = 1;
            } else {
                DAT_UnitsState::instance.units[unitID].gfxNumber
                    += DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected - 8
                    + DAT_UnitsState::instance.units[unitID].animationFrame * 8;
            }
            if (DAT_UnitHasBecomeIdle::instance == 0) {
                return;
            }
            DAT_UnitsState::instance.units[unitID].substate += 1;
            if (DAT_UnitsState::instance.units[unitID].substate > 1) {
                DAT_UnitsState::instance.units[unitID].substate = 0;
            }
            DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
            DAT_UnitsState::instance.units[unitID].seated = 1;
            DAT_UnitsState::instance.units[unitID].state.generic
                = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_DEATH_01) {
            DAT_UnitsState::instance.units[unitID].facingDirection = 0;
            DAT_UnitsState::instance.units[unitID].animationSpeed = 2;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[unitID].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp
                      .ANIM_Worker_Shared1[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
            if (DAT_UnitsState::instance.units[unitID].animationFrame <= 0) {
                DAT_UnitsState::instance.units[unitID].gfxNumber = 0x338;
                DAT_UnitsState::instance.units[unitID].state.generic = (UnitState)117;
                DAT_UnitsState::instance.units[unitID].updateTickTracker = 0;
            } else {
                DAT_UnitsState::instance.units[unitID].gfxNumber
                    = DAT_UnitsState::instance.units[unitID].animationFrame + 800;
            }
            if (DAT_UnitsState::instance.units[unitID].animationCycleNumber == 1
                && DAT_UnitsState::instance.units[unitID].animationCycleNumberHasJustIncremented != FALSE) {
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    DAT_UnitsState::instance.units[unitID].x, DAT_UnitsState::instance.units[unitID].y,
                    OpenSHC::DE::SHCDE::FX_WOLF_DIE);
            }
            return;
        }
        if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::checkIfCitizenUnitIsAliveBasedOnState,
                DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance)
            != FALSE) {
            DAT_UnitsState::instance.units[unitID].facingDirection = 0;
            DAT_UnitsState::instance.units[unitID].animationSpeed = 2;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[unitID].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp
                      .field341_0x6c64[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
            if (DAT_UnitsState::instance.units[unitID].animationFrame <= 0) {
                DAT_UnitsState::instance.units[unitID].gfxNumber = 0x340;
                DAT_UnitsState::instance.units[unitID].state.generic = (UnitState)117;
                DAT_UnitsState::instance.units[unitID].updateTickTracker = 0;
            } else {
                DAT_UnitsState::instance.units[unitID].gfxNumber
                    = DAT_UnitsState::instance.units[unitID].animationFrame + 0x338;
            }
            if (DAT_UnitsState::instance.units[unitID].animationCycleNumber == 1
                && DAT_UnitsState::instance.units[unitID].animationCycleNumberHasJustIncremented != FALSE) {
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    DAT_UnitsState::instance.units[unitID].x, DAT_UnitsState::instance.units[unitID].y,
                    OpenSHC::DE::SHCDE::FX_WOLF_DIE);
            }
            return;
        }
        if (state == (UnitState)117) {
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[unitID].updateTickTracker += 1;
            if (DAT_UnitsState::instance.units[unitID].updateTickTracker > 50) {
                DAT_UnitsState::instance.units[unitID].updateTickTracker = 0;
                DAT_UnitsState::instance.units[unitID].state.generic = OpenSHC::Map::Units::States::US_DISAPPEAR;
            }
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_DISAPPEAR) {
            DAT_UnitsState::instance.units[unitID].disappearFadeAlphaCountdown += 1;
            if ((char)DAT_UnitsState::instance.units[unitID].disappearFadeAlphaCountdown > 32) {
                DAT_UnitsState::instance.units[unitID].disappearFadeAlphaCountdown = 32;
            }
            DAT_UnitsState::instance.units[unitID].updateTickTracker += 1;
            if (DAT_UnitsState::instance.units[unitID].updateTickTracker > 32) {
                DAT_UnitsState::instance.units[unitID].logicalState = OpenSHC::Map::Units::ULS_REMOVE;
            }
            return;
        }
        DAT_UnitsState::instance.units[unitID].state.generic = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
        MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::makeUnitStopWalkingByClearingPathProgressState,
            DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance);
    }

}
}
