#include "../Units.func.hpp"

#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Units/Pathfinding/DestinationNeededEnum.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentUnitSlotID.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x00541A30
    void Units::UpdateMerchantHorse()
    {
        int unitID = DAT_CurrentUnitSlotID::instance;
        int const trader = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].traderHorsesTrader;
        if (DAT_UnitsState::instance.units[trader].uid
            != DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].workplaceBuildingUID) {
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].logicalState
                = OpenSHC::Map::Units::ULS_REMOVE;
        }
        DAT_UnitsState::instance.units[unitID].calculatedOwnerPlayerIndex = 0;
        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed = 0;
        UnitStateShort const state = DAT_UnitsState::instance.units[unitID].state.generic;
        if (state == OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk) {
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber = 1;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 16;
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::commitUnitLocation, DAT_UnitsState::ptr)(unitID);
            if (DAT_UnitsState::instance.units[trader].state.generic
                == OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk) {
                return;
            }
            if (DAT_UnitsState::instance.units[trader].state.generic == OpenSHC::Map::Units::States::US_IDLEUnk) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit, DAT_UnitsState::ptr)(
                    unitID, DAT_UnitsState::instance.units[trader].destinationX_2Unk,
                    DAT_UnitsState::instance.units[trader].destinationY_2Unk, 0);
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = OpenSHC::Map::Units::States::US_IDLEUnk;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].moveInstructionSpeedDelayTracker = 20;
                return;
            }
            if (DAT_UnitsState::instance.units[trader].state.generic == OpenSHC::Map::Units::States::US_STATE_3Unk) {
                DAT_UnitsState::instance.units[unitID].destinationNeeded
                    = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_NEEDED;
                DAT_UnitsState::instance.units[unitID].moveInstructionSpeedDelayTracker = 20;
                DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
                DAT_UnitsState::instance.units[unitID].state.generic = OpenSHC::Map::Units::States::US_JESTER_ROAM_TO;
                DAT_UnitsState::instance.units[unitID].disappearFadeAlphaCountdown = 32;
                DAT_UnitsState::instance.units[unitID].engineerManningSiegeStateRef_checkType = -2;
                DAT_UnitsState::instance.units[unitID].cachedState = OpenSHC::Map::Units::States::US_STATE_3Unk;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].updateTickTracker = 0;
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::resetUnitMovementState, DAT_UnitsState::ptr)(
                    unitID);
            }
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_IDLEUnk) {
            MACRO_CALL_MEMBER(
                OpenSHC::Map::Units::UnitsState_Func::clearHiddenFlagAndUpdatePosition, DAT_UnitsState::ptr)(unitID);
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSheetFrameOffset = 1;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 16;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed = 0;
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].moveInstructionSpeedDelayTracker != 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed = -1;
                return;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::hasUnitReachedDestination, DAT_UnitsState::ptr)(
                    DAT_CurrentUnitSlotID::instance)) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = OpenSHC::Map::Units::States::US_JESTER_ROAM_TO;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].disappearFadeAlphaCountdown = 0;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].engineerManningSiegeStateRef_checkType
                    = 2;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].cachedState
                    = OpenSHC::Map::Units::States::US_STATE_2Unk;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].updateTickTracker = 0;
            }
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_STATE_2Unk) {
            DAT_UnitsState::instance.units[unitID].gfxNumber = 1;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 16;
            if (DAT_GameState::instance.mapAndTime.traderRelated2 == 1) {
                DAT_UnitsState::instance.units[unitID].state.generic
                    = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
            }
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_STATE_3Unk) {
            if (DAT_UnitsState::instance.units[unitID].destinationNeeded
                != OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit, DAT_UnitsState::ptr)(
                    DAT_CurrentUnitSlotID::instance, DAT_GameState::instance.mapAndTime.signpostsMapEdge[0][0].x,
                    DAT_GameState::instance.mapAndTime.signpostsMapEdge[0][0].y, 0);
                unitID = DAT_CurrentUnitSlotID::instance;
                DAT_UnitsState::instance.units[unitID].destinationNeeded
                    = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET;
                DAT_UnitsState::instance.units[unitID].stateBasedSpeed = 0;
                DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 16;
                DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset = 1;
            } else {
                DAT_UnitsState::instance.units[unitID].stateBasedSpeed = 0;
                DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 16;
                DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset = 1;
            }
            if (DAT_UnitsState::instance.units[unitID].moveInstructionSpeedDelayTracker != 0) {
                DAT_UnitsState::instance.units[unitID].stateBasedSpeed = -1;
                return;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::hasUnitReachedDestination, DAT_UnitsState::ptr)(
                    unitID)) {
                MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::resetTraderState, DAT_GameState::ptr)();
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].logicalState
                    = OpenSHC::Map::Units::ULS_REMOVE;
            }
            return;
        }
        if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::checkIfCitizenUnitIsAliveBasedOnState,
                DAT_UnitsState::ptr)(unitID)) {
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber = 1;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 16;
            MACRO_CALL_MEMBER(
                OpenSHC::Map::Units::UnitsState_Func::clearHiddenFlagAndUpdatePosition, DAT_UnitsState::ptr)(unitID);
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                = OpenSHC::Map::Units::States::US_DISAPPEAR;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].updateTickTracker = 0;
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
        if (state == OpenSHC::Map::Units::States::US_JESTER_ROAM_TO) {
            DAT_UnitsState::instance.units[unitID].disappearFadeAlphaCountdown
                += DAT_UnitsState::instance.units[unitID].engineerManningSiegeStateRef_checkType;
            if ((char)DAT_UnitsState::instance.units[unitID].disappearFadeAlphaCountdown < 0) {
                DAT_UnitsState::instance.units[unitID].disappearFadeAlphaCountdown = 0;
            } else if ((char)DAT_UnitsState::instance.units[unitID].disappearFadeAlphaCountdown >= 32) {
                DAT_UnitsState::instance.units[unitID].disappearFadeAlphaCountdown = 31;
            }
            DAT_UnitsState::instance.units[unitID].updateTickTracker++;
            if (DAT_UnitsState::instance.units[unitID].updateTickTracker > 16) {
                DAT_UnitsState::instance.units[unitID].updateTickTracker = 0;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].disappearFadeAlphaCountdown = 0;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].cachedState;
                if ((char)DAT_UnitsState::instance.units[unitID].engineerManningSiegeStateRef_checkType > 0) {
                    MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::commitUnitLocation, DAT_UnitsState::ptr)(
                        unitID);
                }
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::updateBuildingSignpostCounter,
                    DAT_BuildingsState::ptr)(DAT_UnitsState::instance.units[unitID].workplaceBuildingID_1, 2);
            }
            return;
        }
        DAT_UnitsState::instance.units[unitID].state.generic = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
        MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::makeUnitStopWalkingByClearingPathProgressState,
            DAT_UnitsState::ptr)(unitID);
    }

}
}
