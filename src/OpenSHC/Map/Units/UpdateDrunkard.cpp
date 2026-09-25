#include "OpenSHC/Map/Units.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Units/Pathfinding/DestinationNeededEnum.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_CurrentUnitSlotID.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_UnitHasBecomeIdle.hpp"
#include "OpenSHC/Globals/DAT_UnitPropertiesDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::Units::UnitLogicState;
    using OpenSHC::Map::Units::UnitType;
    using OpenSHC::Map::Units::Pathfinding::DestinationNeededEnum;
    using OpenSHC::Map::Units::States::UnitState;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x00567320
    void Units::UpdateDrunkard()
    {
        int unitID = DAT_CurrentUnitSlotID::instance;
        DAT_GameState::instance.playerDataArray[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].owner]
            .field645_0x2174 += 1;
        DAT_UnitsState::instance.units[unitID].calculatedOwnerPlayerIndex = 0;
        if (DAT_UnitsState::instance.units[unitID].field280_0x3f4 > 1) {
            DAT_UnitsState::instance.units[unitID].state.generic = OpenSHC::Map::Units::States::US_DISAPPEAR;
        }
        UnitStateShort state = DAT_UnitsState::instance.units[unitID].state.generic;
        if (state == OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk) {
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_IDLEUnk) {
            DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset = 1;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0x10;
            if (DAT_UnitsState::instance.units[unitID].destinationNeeded
                != OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET) {
                if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::computeLadderClimbPath,
                        DAT_UnitsState::ptr)(unitID, 0, 0, 0)
                    == 0) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                        = OpenSHC::Map::Units::States::US_DISAPPEAR;
                } else {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].destinationNeeded
                        = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET;
                }
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].movementSpeed
                    = (SEC_RNG::instance.currentNumber2 & 3) + 6;
                return;
            }
            if (MACRO_CALL_MEMBER(
                    OpenSHC::Map::Units::UnitsState_Func::hasTunnelerNotFinishedDigging, DAT_UnitsState::ptr)(unitID)
                != FALSE) {
                DAT_UnitsState::instance.units[unitID].state.generic = (UnitState)3;
                DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
            }
            return;
        }
        if (state == (UnitState)3) {
            DAT_UnitsState::instance.units[unitID].animationSpeed = 4;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            if (DAT_UnitsState::instance.units[unitID].substate == 0) {
                DAT_UnitsState::instance.units[unitID].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp
                          .field322_0x634c[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
                if (DAT_UnitsState::instance.units[unitID].animationFrame <= 0) {
                    DAT_UnitHasBecomeIdle::instance = 1;
                } else {
                    DAT_UnitsState::instance.units[unitID].gfxNumber
                        = DAT_UnitsState::instance.units[unitID].animationFrame + 0x100;
                }
            } else {
                if (DAT_UnitsState::instance.units[unitID].substate == 1) {
                    DAT_UnitsState::instance.units[unitID].animationFrame
                        = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp
                              .field323_0x63a0[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
                } else if (DAT_UnitsState::instance.units[unitID].substate == 2) {
                    DAT_UnitsState::instance.units[unitID].animationFrame
                        = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp
                              .field324_0x63d4[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
                }
                if (DAT_UnitsState::instance.units[unitID].animationFrame <= 0) {
                    DAT_UnitHasBecomeIdle::instance = 1;
                } else {
                    DAT_UnitsState::instance.units[unitID].gfxNumber
                        = DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected + 0x79
                        + DAT_UnitsState::instance.units[unitID].animationFrame * 8;
                }
            }
            if (DAT_UnitHasBecomeIdle::instance != 0) {
                DAT_UnitsState::instance.units[unitID].substate += 1;
                if (DAT_UnitsState::instance.units[unitID].substate > 2) {
                    DAT_UnitsState::instance.units[unitID].substate = 0;
                }
                DAT_UnitsState::instance.units[unitID].destinationNeeded
                    = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_NEEDED;
                DAT_UnitsState::instance.units[unitID].resourceToDeposit += 1;
                DAT_UnitsState::instance.units[unitID].state.generic
                    = DAT_UnitsState::instance.units[unitID].resourceToDeposit < 6
                    ? OpenSHC::Map::Units::States::US_IDLEUnk
                    : OpenSHC::Map::Units::States::US_DISAPPEAR;
            }
            return;
        }
        if (state == (UnitState)2) {
            DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset = 1;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0x10;
            DAT_UnitsState::instance.units[unitID].logicalState = OpenSHC::Map::Units::ULS_TRANSITIONING;
            DAT_UnitsState::instance.units[unitID].unitTypeToChangeInto = OpenSHC::Map::Units::UT_PEASANT;
            DAT_UnitsState::instance.units[unitID].state_2 = 0;
            DAT_UnitsState::instance.units[unitID].buildingID = 0;
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_MELEE_ATTACK) {
            DAT_UnitsState::instance.units[unitID].animationSpeed = 3;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[unitID].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp
                      .drunkard[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
            if (DAT_UnitsState::instance.units[unitID].animationFrame <= 0) {
                DAT_UnitsState::instance.units[unitID].gfxNumber
                    = DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected + 1;
                DAT_UnitHasBecomeIdle::instance = 1;
            } else {
                DAT_UnitsState::instance.units[unitID].gfxNumber
                    = DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected - 7
                    + DAT_UnitsState::instance.units[unitID].animationFrame * 8;
            }
            if (DAT_UnitHasBecomeIdle::instance != 0) {
                DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
                MACRO_CALL_MEMBER(
                    OpenSHC::Map::Units::UnitsState_Func::resumeMovementIfNoAttackTarget, DAT_UnitsState::ptr)(unitID);
            }
            return;
        }
        if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::checkIfCitizenUnitIsAliveBasedOnState,
                DAT_UnitsState::ptr)(unitID)
            != FALSE) {
            DAT_UnitsState::instance.units[unitID].state.generic = OpenSHC::Map::Units::States::US_DISAPPEAR;
            DAT_UnitsState::instance.units[unitID].updateTickTracker = 0;
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
            DAT_UnitsState::ptr)(unitID);
    }

}
}
