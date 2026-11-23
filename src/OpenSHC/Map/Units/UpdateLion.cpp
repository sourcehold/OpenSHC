#include "../Units.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/DE/SHCDE/eSFX.hpp"
#include "OpenSHC/Map/Units/Pathfinding/DestinationNeededEnum.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_CurrentUnitSlotID.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitHasBecomeIdle.hpp"
#include "OpenSHC/Globals/DAT_UnitPropertiesDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DWORD_00ee1058.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x0056B0E0
    void Units::UpdateLion()
    {
        int const unitID = DAT_CurrentUnitSlotID::instance;
        int const tribe = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].tribeID;
        DAT_GameState::instance.mapAndTime.field3170_0x27a4++;
        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed = 0;
        if ((char)DAT_UnitsState::instance.units[unitID].disappearFadeAlphaCountdown > 0
            && DAT_UnitsState::instance.units[unitID].state.generic != OpenSHC::Map::Units::States::US_DISAPPEAR) {
            DAT_UnitsState::instance.units[unitID].disappearFadeAlphaCountdown--;
        }
        if (DAT_UnitsState::instance.units[unitID].unknownBool01 != 0) {
            DAT_UnitsState::instance.units[unitID].unknownBool01--;
        }
        if (DAT_TribesState::instance.tribes[tribe].unknownBool01 != 0) {
            DAT_UnitsState::instance.units[unitID].unknownBool01 = 0;
            DAT_TribesState::instance.tribes[tribe].unknownBool02 = 0;
        }
        OpenSHC::Map::Units::States::UnitStateShort const state = DAT_UnitsState::instance.units[unitID].state.generic;
        if (state == OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk) {
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            MACRO_CALL_MEMBER(
                OpenSHC::Map::Units::UnitsState_Func::setUnitFacingDirectionTowardsTarget, DAT_UnitsState::ptr)(
                DAT_CurrentUnitSlotID::instance, DAT_TribesState::instance.tribes[tribe].selectionTargetUnitID);
            // hungry lions search for prey in a growing radius
            int slot = DAT_CurrentUnitSlotID::instance;
            int prey = 0;
            if (DAT_UnitsState::instance.units[slot].unknownBool01 == 0
                && DAT_TribesState::instance.tribes[tribe].unknownBool02 == 0) {
                if (DAT_TribesState::instance.tribes[tribe].unknownBool01 != 0) {
                    prey = MACRO_CALL_MEMBER(
                        OpenSHC::Map::Units::UnitsState_Func::findClosestAnimalStoreResult, DAT_UnitsState::ptr)(
                        200, TRUE, DAT_UnitsState::instance.units[slot].x, DAT_UnitsState::instance.units[slot].y);
                    slot = DAT_CurrentUnitSlotID::instance;
                } else {
                    DAT_TribesState::instance.tribes[tribe].unknownCounter01++;
                    if (DAT_TribesState::instance.tribes[tribe].unknownCounter01 >= 3000) {
                        prey = MACRO_CALL_MEMBER(
                            OpenSHC::Map::Units::UnitsState_Func::findClosestAnimalStoreResult, DAT_UnitsState::ptr)(
                            50, TRUE, DAT_UnitsState::instance.units[slot].x, DAT_UnitsState::instance.units[slot].y);
                        slot = DAT_CurrentUnitSlotID::instance;
                    } else if (DAT_TribesState::instance.tribes[tribe].unknownCounter01 >= 10) {
                        prey = MACRO_CALL_MEMBER(
                            OpenSHC::Map::Units::UnitsState_Func::findClosestAnimalStoreResult, DAT_UnitsState::ptr)(
                            25, FALSE, DAT_UnitsState::instance.units[slot].x, DAT_UnitsState::instance.units[slot].y);
                        slot = DAT_CurrentUnitSlotID::instance;
                    }
                }
            }
            if (!MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::tryAttackUnitID, DAT_UnitsState::ptr)(
                    slot, prey)) {
                DAT_UnitsState::instance.units[slot].state.generic = OpenSHC::Map::Units::States::US_UNKNOWN_205;
            }
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_UNKNOWN_208) {
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::makeUnitStopWalkingByClearingPathProgressState,
                DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance);
            if (DAT_UnitsState::instance.units[unitID].movementRelated >= 8) {
                DAT_UnitsState::instance.units[unitID].state.generic
                    = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
            }
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_MOVE_TO_DESTINATION
            || state == OpenSHC::Map::Units::States::US_UNKNOWN_120) {
            if (DAT_UnitsState::instance.units[unitID].substate == 100) {
                DAT_UnitsState::instance.units[unitID].movementSpeed = 20;
                DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSpeed
                    = (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].fixedRng & 7) + 1;
                DAT_UnitsState::instance.units[unitID].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp
                          .field_0x6d14[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
                if (DAT_UnitsState::instance.units[unitID].animationFrame <= 0) {
                    DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].seated = 0;
                    DAT_UnitsState::instance.units[unitID].substate
                        = DAT_UnitsState::instance.units[unitID].fixedRng & 1;
                    return;
                }
                DAT_UnitsState::instance.units[unitID].gfxNumber
                    = DAT_UnitsState::instance.units[unitID].animationFrame + 368;
                return;
            }
            DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
            if (DAT_TribesState::instance.tribes[tribe].predatorNearby != 0) {
                DAT_UnitsState::instance.units[unitID].movementSpeed = 1;
                DAT_UnitsState::instance.units[unitID].moveInstructionSpeedDelayTracker = 0;
                DAT_UnitsState::instance.units[unitID].stateBasedSpeed = 2;
                DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset = 129;
            } else {
                DAT_UnitsState::instance.units[unitID].movementSpeed = 3;
                DAT_UnitsState::instance.units[unitID].stateBasedSpeed = 0;
                DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset = 1;
            }
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 16;
            if (!MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::hasUnitReachedDestination,
                    DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance)) {
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
            DAT_UnitsState::instance.units[unitID].substate = DAT_UnitsState::instance.units[unitID].fixedRng & 1;
            DAT_UnitsState::instance.units[unitID].state.generic
                = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_UNKNOWN_207) {
            // chasing prey
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 16;
            DAT_UnitsState::instance.units[unitID].movementSpeed = 2;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
            if (DAT_UnitsState::instance.units[unitID].destinationNeeded
                != OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].destinationNeeded
                    = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET;
                short const target
                    = DAT_UnitsState::instance.units[unitID].targetedUnitID__OR__engineerMannedSiegeEngineRef;
                int const prey = target;
                if (target != 0) {
                    if (DAT_UnitsState::instance.units[unitID]
                                .targetedUnitUIDUnk_OR_someAppearTileUnk_OR_buildingUID_OR_pitchDitchUID_OR_entityUID
                            == DAT_UnitsState::instance.units[prey].uid
                        && DAT_UnitsState::instance.units[prey].dying == 0
                        && DAT_UnitsState::instance.units[prey].unknownTestAgainst0_2 == 0) {
                        if (!MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit,
                                DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance,
                                DAT_UnitsState::instance.units[prey].x, DAT_UnitsState::instance.units[prey].y, 0)) {
                            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                                .targetedUnitID__OR__engineerMannedSiegeEngineRef = 0;
                        }
                    } else {
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                            .targetedUnitID__OR__engineerMannedSiegeEngineRef = 0;
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
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].currentIndexInPathPlan <= 4
                && DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].totalSizeOfPathPlan > 8) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed = 0;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSheetFrameOffset = 1;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].movementSpeed = 3;
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].moveInstructionSpeedDelayTracker = 0;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed = 1;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].movementSpeed = 1;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSheetFrameOffset = 129;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::hasUnitReachedDestination, DAT_UnitsState::ptr)(
                    DAT_CurrentUnitSlotID::instance)) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].destinationNeeded
                    = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_NEEDED;
            }
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_MELEE_ATTACK) {
            DAT_UnitsState::instance.units[unitID].animationSpeed = 2;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
            if (DAT_UnitsState::instance.units[unitID].animationCycleNumber > 50) {
                DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp
                      .field_0x703c[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
            if (DAT_UnitsState::instance.units[unitID].animationCycleNumber == 1
                && DAT_UnitsState::instance.units[unitID].animationCycleNumberHasJustIncremented) {
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    DAT_UnitsState::instance.units[unitID].x, DAT_UnitsState::instance.units[unitID].y,
                    OpenSHC::DE::SHCDE::FX_LION_ATTACK);
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame <= 0) {
                DAT_UnitHasBecomeIdle::instance = 1;
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                          .facingDirectionMapOrientationCorrected
                    + 249 + DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame * 8;
            }
            if (DAT_UnitHasBecomeIdle::instance == 0) {
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate++;
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate > 4) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate = 1;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::resumeMovementIfNoAttackTarget,
                DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance);
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].unknownBool01 = 1000;
            DAT_TribesState::instance.tribes[tribe].unknownCounter01 = 0;
            // "Lions are attacking" at most every 90 seconds
            if (timeGetTime() - DWORD_00ee1058::instance <= 90000) {
                return;
            }
            int const victim = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].attackedUnitID;
            if (victim == 0) {
                return;
            }
            if (DAT_UnitsState::instance.units[victim].owner != DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                return;
            }
            // "General_Warning17.wav"
            MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                s_General_Warning17_wav_005abe40);
            DWORD_00ee1058::instance = timeGetTime();
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_UNKNOWN_204) {
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[unitID].animationSpeed = 2;
            DAT_UnitsState::instance.units[unitID].gfxNumber = 696;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x3c2 = 0;
            DAT_UnitsState::instance.units[unitID].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp
                      .field_0x6ec4[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
            if (DAT_UnitsState::instance.units[unitID].animationFrame <= 0) {
                DAT_UnitsState::instance.units[unitID].gfxNumber
                    += DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected + 32;
                DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
                DAT_UnitHasBecomeIdle::instance = 1;
                return;
            }
            DAT_UnitsState::instance.units[unitID].gfxNumber
                += DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected - 8
                + DAT_UnitsState::instance.units[unitID].animationFrame * 8;
            if (DAT_UnitHasBecomeIdle::instance != 0) {
                DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
                DAT_UnitsState::instance.units[unitID].state.generic
                    = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
            }
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_UNKNOWN_205) {
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[unitID].animationSpeed = 3;
            DAT_UnitsState::instance.units[unitID].gfxNumber = 368;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x3c2 = 0;
            int frame;
            if (DAT_UnitsState::instance.units[unitID].seated == 0) {
                frame = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp
                            .field_0x6ca4[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
            } else {
                frame = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp
                            .field_0x6cec[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
            }
            DAT_UnitsState::instance.units[unitID].animationFrame = frame;
            if (frame <= 0) {
                DAT_UnitsState::instance.units[unitID].gfxNumber += 24;
                DAT_UnitHasBecomeIdle::instance = 1;
            } else {
                DAT_UnitsState::instance.units[unitID].gfxNumber += frame;
            }
            if (DAT_UnitHasBecomeIdle::instance == 0) {
                return;
            }
            DAT_UnitsState::instance.units[unitID].substate++;
            if (DAT_UnitsState::instance.units[unitID].substate > 1) {
                DAT_UnitsState::instance.units[unitID].substate = 0;
            }
            DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
            DAT_UnitsState::instance.units[unitID].seated = 1;
            DAT_UnitsState::instance.units[unitID].state.generic
                = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_UNKNOWN_206) {
            DAT_UnitsState::instance.units[unitID].state.generic
                = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_DEATH_01) {
            DAT_UnitsState::instance.units[unitID].facingDirection = 0;
            DAT_UnitsState::instance.units[unitID].animationSpeed = 2;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.ANIM_Worker_Shared1
                      [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
            if (DAT_UnitsState::instance.units[unitID].animationFrame <= 0) {
                DAT_UnitsState::instance.units[unitID].gfxNumber = 440;
                DAT_UnitsState::instance.units[unitID].state.generic = OpenSHC::Map::Units::States::US_UNKNOWN_117;
                DAT_UnitsState::instance.units[unitID].updateTickTracker = 0;
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame + 416;
            }
            if (DAT_UnitsState::instance.units[unitID].animationCycleNumber == 1
                && DAT_UnitsState::instance.units[unitID].animationCycleNumberHasJustIncremented) {
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].x,
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].y, OpenSHC::DE::SHCDE::FX_LION_DIE);
            }
            return;
        }
        if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::checkIfCitizenUnitIsAliveBasedOnState,
                DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance)) {
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].facingDirection = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSpeed = 2;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.ANIM_Worker_Shared1
                      [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame <= 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber = 416;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = OpenSHC::Map::Units::States::US_UNKNOWN_117;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].updateTickTracker = 0;
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame + 392;
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber == 1
                && DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                    .animationCycleNumberHasJustIncremented) {
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].x,
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].y, OpenSHC::DE::SHCDE::FX_LION_DIE);
            }
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_UNKNOWN_117) {
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[unitID].updateTickTracker++;
            if (DAT_UnitsState::instance.units[unitID].updateTickTracker > 50) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].updateTickTracker = 0;
                DAT_UnitsState::instance.units[unitID].state.generic = OpenSHC::Map::Units::States::US_DISAPPEAR;
            }
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_DISAPPEAR) {
            DAT_UnitsState::instance.units[unitID].disappearFadeAlphaCountdown++;
            if ((char)DAT_UnitsState::instance.units[unitID].disappearFadeAlphaCountdown > 32) {
                DAT_UnitsState::instance.units[unitID].disappearFadeAlphaCountdown = 32;
            }
            DAT_UnitsState::instance.units[unitID].updateTickTracker++;
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
