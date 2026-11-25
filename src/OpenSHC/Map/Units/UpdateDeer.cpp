#include "../Units.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/DE/SHCDE/eSFX.hpp"
#include "OpenSHC/Map/Units/SomeTribeBehaviorType.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"

#include "OpenSHC/Globals/DAT_CurrentUnitSlotID.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitHasBecomeIdle.hpp"
#include "OpenSHC/Globals/DAT_UnitPropertiesDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x00541DE0
    void Units::UpdateDeer()
    {
        int const unitID = DAT_CurrentUnitSlotID::instance;
        // declared at the top: declaring it in the movement case loses the match
        int frameOffset = 1;
        // read at the top: reading it just before the switch loses the match
        int const tribe = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].tribeID;
        DAT_GameState::instance.mapAndTime.deerCount++;
        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed = 0;
        if (DAT_UnitsState::instance.units[unitID].antelopeBasedRngValue == 0) {
            DAT_UnitsState::instance.units[unitID].movementSpeed = 1;
        } else if (DAT_UnitsState::instance.units[unitID].antelopeBasedRngValue == 1) {
            DAT_UnitsState::instance.units[unitID].movementSpeed = 2;
        } else if (DAT_UnitsState::instance.units[unitID].antelopeBasedRngValue == 2) {
            DAT_UnitsState::instance.units[unitID].movementSpeed = 3;
        }
        if ((char)DAT_UnitsState::instance.units[unitID].disappearFadeAlphaCountdown > 0
            && DAT_UnitsState::instance.units[unitID].state.generic != OpenSHC::Map::Units::States::US_DISAPPEAR) {
            DAT_UnitsState::instance.units[unitID].disappearFadeAlphaCountdown--;
        }
        switch (DAT_UnitsState::instance.units[unitID].state.generic) {
        case OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk:
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
            if (DAT_UnitsState::instance.units[unitID].closestEnemyMicroDistance > 200) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setUnitFacingDirectionTowardsTarget,
                    DAT_UnitsState::ptr)(unitID, DAT_TribesState::instance.tribes[tribe].selectionTargetUnitID);
                if (DAT_TribesState::instance.tribes[tribe].tribeBehaviorType == OpenSHC::Map::Units::STBT_1) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                        = OpenSHC::Map::Units::States::US_UNKNOWN_205;
                    return;
                }
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = OpenSHC::Map::Units::States::US_UNKNOWN_203;
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                = OpenSHC::Map::Units::States::US_UNKNOWN_204;
            DAT_UnitsState::instance.units[unitID].field_0x3f2++;
            if (DAT_UnitsState::instance.units[unitID].field_0x3f2 > 10) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::scatterTribeUnitsRandomly,
                    DAT_TribesState::ptr)(DAT_UnitsState::instance.units[unitID].tribeID);
            }
            return;
        case OpenSHC::Map::Units::States::US_UNKNOWN_209:
            DAT_UnitsState::instance.units[unitID].field_0x3f2 = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 16;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSheetFrameOffset = 1;
            if (((DAT_UnitsState::instance.units[unitID].fixedRng ^ DAT_GameCore::instance.mapTimeInTicks) & 0x7f)
                == 0) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit, DAT_UnitsState::ptr)(
                    unitID, DAT_UnitsState::instance.units[unitID].targetX,
                    DAT_UnitsState::instance.units[unitID].targetY, 0);
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = OpenSHC::Map::Units::States::US_MOVE_TO_DESTINATION;
            }
            return;
        case OpenSHC::Map::Units::States::US_MOVE_TO_DESTINATION:
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x3f2 = 0;
            if (DAT_UnitsState::instance.units[unitID].substate == 100) {
                DAT_UnitsState::instance.units[unitID].movementSpeed = 20;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
                DAT_UnitsState::instance.units[unitID].animationSpeed
                    = (DAT_UnitsState::instance.units[unitID].fixedRng & 7) + 1;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber = 321;
                DAT_UnitsState::instance.units[unitID].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp
                          .field_0x69a8[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
                if (DAT_UnitsState::instance.units[unitID].animationFrame <= 0) {
                    DAT_UnitsState::instance.units[unitID].substate = 0;
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].seated = 0;
                    DAT_UnitsState::instance.units[unitID].gfxNumber
                        += DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected;
                    return;
                }
                DAT_UnitsState::instance.units[unitID].gfxNumber
                    += DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected - 8
                    + DAT_UnitsState::instance.units[unitID].animationFrame * 8;
                return;
            }
            if (DAT_UnitsState::instance.units[unitID].field_0x3c2 != 0) {
                DAT_UnitsState::instance.units[unitID].movementSpeed = 20;
                DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSpeed = 5;
                if (DAT_UnitsState::instance.units[unitID].animationCycleNumberHasJustIncremented) {
                    DAT_UnitsState::instance.units[unitID].animationFrame--;
                }
                if (DAT_UnitsState::instance.units[unitID].animationFrame <= 0) {
                    DAT_UnitsState::instance.units[unitID].substate = 0;
                    DAT_UnitsState::instance.units[unitID].seated = 0;
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                        = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                              .facingDirectionMapOrientationCorrected
                        + 257;
                    DAT_UnitsState::instance.units[unitID].field_0x3c2 = 0;
                    return;
                }
                DAT_UnitsState::instance.units[unitID].gfxNumber
                    = DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected + 249
                    + DAT_UnitsState::instance.units[unitID].animationFrame * 8;
                return;
            }
            if (DAT_TribesState::instance.tribes[tribe].predatorNearby == 0
                || DAT_UnitsState::instance.units[unitID].currentIndexInPathPlan
                    > DAT_UnitsState::instance.units[unitID].totalSizeOfPathPlan - 2) {
                DAT_UnitsState::instance.units[unitID].stateBasedSpeed = 0;
                DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 8;
            } else {
                DAT_UnitsState::instance.units[unitID].stateBasedSpeed = 1;
                DAT_UnitsState::instance.units[unitID].moveInstructionSpeedDelayTracker = 0;
                DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 16;
                frameOffset = 129;
                DAT_UnitsState::instance.units[unitID].movementSpeed = 1;
            }
            DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset = frameOffset;
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::hasUnitReachedDestination, DAT_UnitsState::ptr)(
                    unitID)) {
                // through a pointer, so these two stores stay ahead of the epilogue, as in the original
                Unit* const unit = &DAT_UnitsState::instance.units[unitID];
                unit->animationCycleNumber = 0;
                unit->substate = 0;
                DAT_UnitsState::instance.units[unitID].state.generic
                    = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
            }
            return;
        case OpenSHC::Map::Units::States::US_UNKNOWN_202:
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x3f2 = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSheetFrameOffset = 129;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 16;
            return;
        case OpenSHC::Map::Units::States::US_UNKNOWN_203:
            DAT_UnitsState::instance.units[unitID].field_0x3f2 = 0;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[unitID].animationSpeed = 2;
            DAT_UnitsState::instance.units[unitID].field_0x3c2 = 1;
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate == 0) {
                DAT_UnitsState::instance.units[unitID].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp
                          .field_0x671c[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
            } else if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate == 1) {
                DAT_UnitsState::instance.units[unitID].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp
                          .field_0x6804[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
            } else if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate == 2) {
                DAT_UnitsState::instance.units[unitID].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp
                          .field_0x6784[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
            } else if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate == 3) {
                DAT_UnitsState::instance.units[unitID].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp
                          .field_0x6804[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
            }
            if (DAT_UnitsState::instance.units[unitID].animationFrame <= 0) {
                DAT_UnitsState::instance.units[unitID].gfxNumber
                    = DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected + 257;
                DAT_UnitHasBecomeIdle::instance = 1;
            } else {
                DAT_UnitsState::instance.units[unitID].gfxNumber
                    = DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected + 249
                    + DAT_UnitsState::instance.units[unitID].animationFrame * 8;
            }
            if (DAT_UnitHasBecomeIdle::instance != 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
                DAT_UnitsState::instance.units[unitID].substate++;
                if (DAT_UnitsState::instance.units[unitID].substate > 3) {
                    DAT_UnitsState::instance.units[unitID].substate = 0;
                }
                DAT_UnitsState::instance.units[unitID].state.generic
                    = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
            }
            return;
        case OpenSHC::Map::Units::States::US_UNKNOWN_204:
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSpeed = 2;
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate == 0) {
                DAT_UnitsState::instance.units[unitID].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp
                          .field_0x68a4[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
            } else if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate == 1) {
                DAT_UnitsState::instance.units[unitID].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp
                          .field_0x68f4[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
            } else if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate == 2) {
                DAT_UnitsState::instance.units[unitID].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp
                          .field_0x68a4[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
            } else if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate == 3) {
                DAT_UnitsState::instance.units[unitID].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp
                          .field_0x68f4[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
            }
            if (DAT_UnitsState::instance.units[unitID].animationFrame <= 0) {
                DAT_UnitsState::instance.units[unitID].gfxNumber
                    = DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected + 257;
                DAT_UnitHasBecomeIdle::instance = 1;
            } else {
                DAT_UnitsState::instance.units[unitID].gfxNumber
                    = DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected + 249
                    + DAT_UnitsState::instance.units[unitID].animationFrame * 8;
            }
            if (DAT_UnitHasBecomeIdle::instance != 0) {
                DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
                DAT_UnitsState::instance.units[unitID].substate++;
                if (DAT_UnitsState::instance.units[unitID].substate > 3) {
                    DAT_UnitsState::instance.units[unitID].substate = 0;
                }
                DAT_UnitsState::instance.units[unitID].state.generic
                    = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
            }
            return;
        case OpenSHC::Map::Units::States::US_UNKNOWN_205:
            DAT_UnitsState::instance.units[unitID].field_0x3f2 = 0;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[unitID].animationSpeed = 4;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber = 321;
            if (DAT_UnitsState::instance.units[unitID].seated == 0) {
                DAT_UnitsState::instance.units[unitID].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp
                          .field_0x6984[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
                if (DAT_UnitsState::instance.units[unitID].animationFrame <= 0) {
                    DAT_UnitsState::instance.units[unitID].gfxNumber
                        += DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected + 88;
                    DAT_UnitHasBecomeIdle::instance = 1;
                } else {
                    DAT_UnitsState::instance.units[unitID].gfxNumber
                        += DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected - 8
                        + DAT_UnitsState::instance.units[unitID].animationFrame * 8;
                }
            } else {
                DAT_UnitsState::instance.units[unitID].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp
                          .field_0x69cc[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
                if (DAT_UnitsState::instance.units[unitID].animationFrame <= 0) {
                    DAT_UnitsState::instance.units[unitID].gfxNumber
                        += DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected + 96;
                    DAT_UnitHasBecomeIdle::instance = 1;
                } else {
                    DAT_UnitsState::instance.units[unitID].gfxNumber
                        += DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected - 8
                        + DAT_UnitsState::instance.units[unitID].animationFrame * 8;
                }
            }
            if (DAT_UnitHasBecomeIdle::instance != 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
                DAT_UnitsState::instance.units[unitID].seated = 1;
            }
            return;
        case OpenSHC::Map::Units::States::US_DEATH_01:
            DAT_UnitsState::instance.units[unitID].facingDirection = 0;
            DAT_UnitsState::instance.units[unitID].animationSpeed = 2;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.field_0x6acc
                      [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
            if (DAT_UnitsState::instance.units[unitID].animationCycleNumberHasJustIncremented
                && DAT_UnitsState::instance.units[unitID].animationCycleNumber == 15) {
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    DAT_UnitsState::instance.units[unitID].x, DAT_UnitsState::instance.units[unitID].y,
                    OpenSHC::DE::SHCDE::FX_DEER_FALL);
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame <= 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber = 480;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = OpenSHC::Map::Units::States::US_UNKNOWN_117;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].updateTickTracker = 0;
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame + 460;
            return;
        case OpenSHC::Map::Units::States::US_DEATH_02:
        case OpenSHC::Map::Units::States::US_DEATH_03:
        case OpenSHC::Map::Units::States::US_STONE_DEATH_01:
        case OpenSHC::Map::Units::States::US_STONE_DEATH_02:
        case OpenSHC::Map::Units::States::US_STONE_DEATH_03:
            DAT_UnitsState::instance.units[unitID].facingDirection = 0;
            DAT_UnitsState::instance.units[unitID].animationSpeed = 2;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[unitID].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp
                      .field_0x6b0c[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
            if (DAT_UnitsState::instance.units[unitID].animationFrame <= 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = OpenSHC::Map::Units::States::US_UNKNOWN_117;
                DAT_UnitsState::instance.units[unitID].updateTickTracker = 0;
                return;
            }
            DAT_UnitsState::instance.units[unitID].gfxNumber
                = DAT_UnitsState::instance.units[unitID].animationFrame + 448;
            return;
        case OpenSHC::Map::Units::States::US_UNKNOWN_117:
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[unitID].updateTickTracker++;
            if (DAT_UnitsState::instance.units[unitID].updateTickTracker > 500) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].updateTickTracker = 0;
                DAT_UnitsState::instance.units[unitID].state.generic = OpenSHC::Map::Units::States::US_DISAPPEAR;
            }
            return;
        case OpenSHC::Map::Units::States::US_DISAPPEAR:
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
    }

}
}
