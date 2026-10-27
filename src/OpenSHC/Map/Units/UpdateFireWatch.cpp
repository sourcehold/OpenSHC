#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Units.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/DE/SHCDE/eSFX.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/Units/Pathfinding/DestinationNeededEnum.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentUnitSlotID.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_UnitHasBecomeIdle.hpp"
#include "OpenSHC/Globals/DAT_UnitPropertiesDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::DE::SHCDE::eSFX;
    using OpenSHC::Map::Buildings::BuildingLogicalState;
    using OpenSHC::Map::Units::UnitLogicState;
    using OpenSHC::Map::Units::Pathfinding::DestinationNeededEnum;
    using OpenSHC::Map::Units::States::UnitState;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x00543340
    void Units::UpdateFireWatch()
    {
        int unitID = DAT_CurrentUnitSlotID::instance;
        int workplace = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].workplaceBuildingID_1;
        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field295_0x40a = 1;
        UnitStateShort state = DAT_UnitsState::instance.units[unitID].state.generic;
        DAT_BuildingsState::instance.buildings[workplace].workers[DAT_UnitsState::instance.units[unitID].workerIndex]
            = (short)unitID;
        if (state == OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk) {
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[unitID].gfxNumber = 0x18b;
            if (DAT_UnitsState::instance.units[unitID].isDisappearingUnk != 0) {
                DAT_UnitsState::instance.units[unitID].disappearFadeAlphaCountdown -= 1;
                if ((char)DAT_UnitsState::instance.units[unitID].disappearFadeAlphaCountdown < 0) {
                    DAT_UnitsState::instance.units[unitID].disappearFadeAlphaCountdown = 0;
                    DAT_UnitsState::instance.units[unitID].isDisappearingUnk = 0;
                }
                return;
            }
            if (DAT_UnitsState::instance.units[unitID].goToRallyPoint != 0) {
                DAT_UnitsState::instance.units[unitID].goToRallyPoint = 0;
                DAT_UnitsState::instance.units[unitID].state.generic = OpenSHC::Map::Units::States::US_IDLEUnk;
                DAT_UnitsState::instance.units[unitID].destinationNeeded
                    = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_NEEDED;
                DAT_UnitsState::instance.units[unitID].targetedUnitID__OR__engineerMannedSiegeEngineRef = 0;
            }
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_IDLEUnk) {
            // walking to the patrol point
            DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset = 0x81;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0x10;
            DAT_UnitsState::instance.units[unitID].stateBasedSpeed = 1;
            if (DAT_UnitsState::instance.units[unitID].destinationNeeded
                != OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET) {
                if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit, DAT_UnitsState::ptr)(
                        unitID, DAT_UnitsState::instance.units[unitID].targetX_2,
                        DAT_UnitsState::instance.units[unitID].targetY_2, 0)
                    == FALSE) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                        = OpenSHC::Map::Units::States::US_DISAPPEAR;
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].disappearFadeAlphaCountdown = 0;
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].updateTickTracker = 0;
                    return;
                }
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].destinationNeeded
                    = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                    .targetedUnitID__OR__engineerMannedSiegeEngineRef = 0;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::hasUnitReachedDestination, DAT_UnitsState::ptr)(
                    unitID)
                == FALSE) {
                return;
            }
            if (DAT_UnitsState::instance.units[unitID].destinationNeeded
                != OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET) {
                return;
            }
            DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
            int burning
                = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::findClosestReachableAlliedBuilding,
                    DAT_BuildingsState::ptr)(unitID);
            if (burning == 0) {
                if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                        .targetedUnitID__OR__engineerMannedSiegeEngineRef
                    == 0) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic = (UnitState)2;
                    return;
                }
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].destinationNeeded
                    = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_NEEDED;
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic = (UnitState)3;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                .targetedUnitID__OR__engineerMannedSiegeEngineRef = (short)burning;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                .targetedUnitUIDUnk_OR_someAppearTileUnk_OR_buildingUID_OR_pitchDitchUID_OR_entityUID
                = DAT_BuildingsState::instance.buildings[burning].uid;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].destinationNeeded
                = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_NEEDED;
            return;
        }
        if (state == (UnitState)2) {
            // looking out for fires
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset = 1;
            DAT_UnitsState::instance.units[unitID].animationSpeed = 8;
            if (DAT_UnitsState::instance.units[unitID].substate == 0) {
                DAT_UnitsState::instance.units[unitID].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp
                          .field412_0x82f8[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
            } else if (DAT_UnitsState::instance.units[unitID].substate == 1) {
                DAT_UnitsState::instance.units[unitID].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp
                          .field413_0x8320[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
            } else if (DAT_UnitsState::instance.units[unitID].substate == 2) {
                DAT_UnitsState::instance.units[unitID].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp
                          .field414_0x834c[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
            } else {
                DAT_UnitsState::instance.units[unitID].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp
                          .field415_0x837c[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
            }
            if (DAT_UnitsState::instance.units[unitID].animationFrame <= 0) {
                DAT_UnitsState::instance.units[unitID].gfxNumber = 0x18b;
                DAT_UnitHasBecomeIdle::instance = 1;
            } else {
                DAT_UnitsState::instance.units[unitID].gfxNumber
                    = DAT_UnitsState::instance.units[unitID].animationFrame + 0x180;
            }
            if (DAT_UnitHasBecomeIdle::instance == 0) {
                return;
            }
            DAT_UnitsState::instance.units[unitID].substate += 1;
            if (DAT_UnitsState::instance.units[unitID].substate > 3) {
                DAT_UnitsState::instance.units[unitID].substate = 0;
            }
            DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
            int burning
                = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::findClosestReachableAlliedBuilding,
                    DAT_BuildingsState::ptr)(unitID);
            if (burning == 0) {
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic = (UnitState)3;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                .targetedUnitID__OR__engineerMannedSiegeEngineRef = (short)burning;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                .targetedUnitUIDUnk_OR_someAppearTileUnk_OR_buildingUID_OR_pitchDitchUID_OR_entityUID
                = DAT_BuildingsState::instance.buildings[burning].uid;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].destinationNeeded
                = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_NEEDED;
            return;
        }
        if (state == (UnitState)3) {
            // walking to the fire
            DAT_UnitsState::instance.units[unitID].stateBasedSpeed = 0;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0x10;
            DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset = 1;
            if (DAT_UnitsState::instance.units[unitID].destinationNeeded
                != OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET) {
                int target = DAT_UnitsState::instance.units[unitID].targetedUnitID__OR__engineerMannedSiegeEngineRef;
                if (target == 0
                    || DAT_UnitsState::instance.units[unitID]
                            .targetedUnitUIDUnk_OR_someAppearTileUnk_OR_buildingUID_OR_pitchDitchUID_OR_entityUID
                        != DAT_BuildingsState::instance.buildings[target].uid
                    || DAT_BuildingsState::instance.buildings[target].fireDuration == 0
                    || MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit,
                           DAT_UnitsState::ptr)(unitID, DAT_BuildingsState::instance.buildings[target].buildingEntryX,
                           DAT_BuildingsState::instance.buildings[target].buildingEntryY, 0)
                        == FALSE) {
                    int burning = MACRO_CALL_MEMBER(
                        OpenSHC::Map::Buildings::BuildingsState_Func::findClosestReachableAlliedBuilding,
                        DAT_BuildingsState::ptr)(DAT_CurrentUnitSlotID::instance);
                    if (burning == 0) {
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                            = OpenSHC::Map::Units::States::US_IDLEUnk;
                    } else {
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic = (UnitState)3;
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                            .targetedUnitID__OR__engineerMannedSiegeEngineRef = (short)burning;
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                            .targetedUnitUIDUnk_OR_someAppearTileUnk_OR_buildingUID_OR_pitchDitchUID_OR_entityUID
                            = DAT_BuildingsState::instance.buildings[burning].uid;
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].destinationNeeded
                            = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_NEEDED;
                    }
                } else {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].destinationNeeded
                        = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET;
                }
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::hasUnitReachedDestination, DAT_UnitsState::ptr)(
                    unitID)
                    != FALSE
                && DAT_UnitsState::instance.units[unitID].destinationNeeded
                    == OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET) {
                DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
                int target = DAT_UnitsState::instance.units[unitID].targetedUnitID__OR__engineerMannedSiegeEngineRef;
                if (target != 0
                    && DAT_UnitsState::instance.units[unitID]
                            .targetedUnitUIDUnk_OR_someAppearTileUnk_OR_buildingUID_OR_pitchDitchUID_OR_entityUID
                        == DAT_BuildingsState::instance.buildings[target].uid
                    && DAT_BuildingsState::instance.buildings[target].fireDuration != 0) {
                    DAT_UnitsState::instance.units[unitID].state.generic
                        = OpenSHC::Map::Units::States::US_RELOAD_WEAPONUnk;
                    return;
                }
                DAT_UnitsState::instance.units[unitID].destinationNeeded
                    = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_NEEDED;
                return;
            }
            int target = DAT_UnitsState::instance.units[unitID].targetedUnitID__OR__engineerMannedSiegeEngineRef;
            if (target != 0
                && DAT_UnitsState::instance.units[unitID]
                        .targetedUnitUIDUnk_OR_someAppearTileUnk_OR_buildingUID_OR_pitchDitchUID_OR_entityUID
                    == DAT_BuildingsState::instance.buildings[target].uid
                && DAT_BuildingsState::instance.buildings[target].fireDuration != 0) {
                return;
            }
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::makeUnitStopWalkingByClearingPathProgressState,
                DAT_UnitsState::ptr)(unitID);
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_RELOAD_WEAPONUnk) {
            // throwing water
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[unitID].animationSpeed = 3;
            DAT_UnitsState::instance.units[unitID].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp
                      .field411_0x82d0[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
            if (DAT_UnitsState::instance.units[unitID].animationFrame <= 0) {
                DAT_UnitsState::instance.units[unitID].gfxNumber
                    = DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected + 0x101;
                DAT_UnitHasBecomeIdle::instance = 1;
            } else {
                DAT_UnitsState::instance.units[unitID].gfxNumber
                    = DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected + 0xf9
                    + DAT_UnitsState::instance.units[unitID].animationFrame * 8;
            }
            if (DAT_UnitsState::instance.units[unitID].animationCycleNumber == 5
                && DAT_UnitsState::instance.units[unitID].animationCycleNumberHasJustIncremented != FALSE) {
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    DAT_UnitsState::instance.units[unitID].x, DAT_UnitsState::instance.units[unitID].y,
                    OpenSHC::DE::SHCDE::FX_THROW_WATER);
            }
            if (DAT_UnitHasBecomeIdle::instance == 0) {
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                = OpenSHC::Map::Units::States::US_IDLEUnk;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].destinationNeeded
                = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_NEEDED;
            int target = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                             .targetedUnitID__OR__engineerMannedSiegeEngineRef;
            if (target == 0) {
                return;
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                    .targetedUnitUIDUnk_OR_someAppearTileUnk_OR_buildingUID_OR_pitchDitchUID_OR_entityUID
                != DAT_BuildingsState::instance.buildings[target].uid) {
                return;
            }
            MACRO_CALL_MEMBER(
                OpenSHC::Map::Buildings::BuildingsState_Func::extinguishBuildingFire, DAT_BuildingsState::ptr)(target);
            MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                DAT_BuildingsState::instance.buildings[target].x, DAT_BuildingsState::instance.buildings[target].y,
                OpenSHC::DE::SHCDE::FX_FIRE_OUT);
            // buildings placed together (e.g. wall segments) are extinguished together
            int placedUID = DAT_BuildingsState::instance.buildings[target].uidWhenPlaced;
            if (placedUID == 0) {
                return;
            }
            for (int i = 1; i < DAT_BuildingsState::instance.maxBuildingsCount; ++i) {
                if (DAT_BuildingsState::instance.buildings[i].logicalState != 0
                    && DAT_BuildingsState::instance.buildings[i].uidWhenPlaced == placedUID) {
                    MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::extinguishBuildingFire,
                        DAT_BuildingsState::ptr)(i);
                }
            }
            return;
        }
        if (state == (UnitState)0x6c) {
            DAT_UnitsState::instance.units[unitID].stateBasedSpeed = 0;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset = 1;
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
            DAT_UnitsState::instance.units[unitID].updateTickTracker += 1;
            if (DAT_UnitsState::instance.units[unitID].updateTickTracker <= 16) {
                return;
            }
            DAT_UnitsState::instance.units[unitID].updateTickTracker = 0;
            DAT_UnitsState::instance.units[unitID].disappearFadeAlphaCountdown = 0;
            DAT_UnitsState::instance.units[unitID].state.generic = DAT_UnitsState::instance.units[unitID].cachedState;
            if ((char)DAT_UnitsState::instance.units[unitID].engineerManningSiegeStateRef_checkType > 0) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::commitUnitLocation, DAT_UnitsState::ptr)(
                    unitID);
            }
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_DEATH_01) {
            DAT_UnitsState::instance.units[unitID].animationSpeed = 2;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[unitID].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp
                      .field409_0x8234[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
            if (DAT_UnitsState::instance.units[unitID].animationFrame <= 0) {
                DAT_UnitsState::instance.units[unitID].gfxNumber = 0x1ac;
                DAT_UnitsState::instance.units[unitID].logicalState = OpenSHC::Map::Units::ULS_REMOVE;
                DAT_UnitHasBecomeIdle::instance = 1;
                return;
            }
            DAT_UnitsState::instance.units[unitID].gfxNumber
                = DAT_UnitsState::instance.units[unitID].animationFrame + 0x194;
            if (DAT_UnitHasBecomeIdle::instance != 0) {
                DAT_UnitsState::instance.units[unitID].logicalState = OpenSHC::Map::Units::ULS_REMOVE;
            }
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_DEATH_03) {
            DAT_UnitsState::instance.units[unitID].animationSpeed = 2;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[unitID].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp
                      .field409_0x8234[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
            if (DAT_UnitsState::instance.units[unitID].animationFrame <= 0) {
                DAT_UnitsState::instance.units[unitID].gfxNumber = 0x1c4;
                DAT_UnitsState::instance.units[unitID].logicalState = OpenSHC::Map::Units::ULS_REMOVE;
                DAT_UnitHasBecomeIdle::instance = 1;
                return;
            }
            DAT_UnitsState::instance.units[unitID].gfxNumber
                = DAT_UnitsState::instance.units[unitID].animationFrame + 0x1ac;
            if (DAT_UnitHasBecomeIdle::instance != 0) {
                DAT_UnitsState::instance.units[unitID].logicalState = OpenSHC::Map::Units::ULS_REMOVE;
            }
            return;
        }
        if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::checkIfCitizenUnitIsAliveBasedOnState,
                DAT_UnitsState::ptr)(unitID)
            != FALSE) {
            DAT_UnitsState::instance.units[unitID].facingDirection = 0;
            DAT_UnitsState::instance.units[unitID].animationSpeed = 2;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[unitID].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp
                      .field410_0x8284[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
            if (DAT_UnitsState::instance.units[unitID].animationFrame <= 0) {
                DAT_UnitsState::instance.units[unitID].gfxNumber = 0x1dc;
                DAT_UnitsState::instance.units[unitID].logicalState = OpenSHC::Map::Units::ULS_REMOVE;
                DAT_UnitHasBecomeIdle::instance = 1;
                return;
            }
            DAT_UnitsState::instance.units[unitID].gfxNumber
                = DAT_UnitsState::instance.units[unitID].animationFrame + 0x1c4;
            if (DAT_UnitHasBecomeIdle::instance != 0) {
                DAT_UnitsState::instance.units[unitID].logicalState = OpenSHC::Map::Units::ULS_REMOVE;
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
        DAT_UnitsState::instance.units[unitID].state.generic = OpenSHC::Map::Units::States::US_IDLEUnk;
        DAT_UnitsState::instance.units[unitID].destinationNeeded
            = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_NEEDED;
        DAT_UnitsState::instance.units[unitID].targetedUnitID__OR__engineerMannedSiegeEngineRef = 0;
        MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::makeUnitStopWalkingByClearingPathProgressState,
            DAT_UnitsState::ptr)(unitID);
    }

}
}
