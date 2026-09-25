#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Units.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/DE/SHCDE/eSFX.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"
#include "OpenSHC/Map/Units/Pathfinding/DestinationNeededEnum.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentUnitSlotID.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_UnitHasBecomeIdle.hpp"
#include "OpenSHC/Globals/DAT_UnitPropertiesDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::DE::SHCDE::eSFX;
    using OpenSHC::Game::Resources::ResourceType;
    using OpenSHC::Map::Units::UnitLogicState;
    using OpenSHC::Map::Units::Pathfinding::DestinationNeededEnum;
    using OpenSHC::Map::Units::States::UnitState;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x00555880
    void Units::UpdateBaker()
    {
        int unitID = DAT_CurrentUnitSlotID::instance;
        int bakery = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].workplaceBuildingID_1;
        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field39_0x58 = 0;
        DAT_UnitsState::instance.units[unitID].unitTypeSpecificRestingState = 1;
        UnitStateShort state = DAT_UnitsState::instance.units[unitID].state.generic;
        if (state == OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk) {
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
                DAT_UnitsState::instance.units[unitID].destinationNeeded = (DestinationNeededEnum)2;
                DAT_UnitsState::instance.units[unitID].state.generic = (UnitState)2;
            }
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_IDLEUnk) {
            // idling in the bakery
            DAT_UnitsState::instance.units[unitID].animationSpeed = 2;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[unitID].field39_0x58 = 1;
            DAT_UnitsState::instance.units[unitID].resourceToDeposit = 0;
            DAT_UnitsState::instance.units[unitID].field131_0x2ac = 1;
            if (DAT_UnitsState::instance.units[unitID].substate == -1) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::sitDownIfStanding, DAT_UnitsState::ptr)(unitID);
            }
            if (MACRO_CALL(OpenSHC::Map::Units_Func::CheckUnitProductionPaused)(unitID) == FALSE) {
                if (DAT_UnitsState::instance.units[unitID].substate == 100) {
                    DAT_UnitsState::instance.units[unitID].animationFrame
                        = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp
                              .field263_0x5150[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
                } else if (DAT_UnitsState::instance.units[unitID].substate == 0x65) {
                    DAT_UnitsState::instance.units[unitID].animationFrame
                        = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp
                              .field264_0x5160[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
                } else if (DAT_UnitsState::instance.units[unitID].substate == 0x6a) {
                    DAT_UnitsState::instance.units[unitID].animationFrame
                        = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp
                              .field266_0x51ec[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
                } else if (DAT_UnitsState::instance.units[unitID].substate == 0x6b) {
                    DAT_UnitsState::instance.units[unitID].animationFrame
                        = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp
                              .field267_0x52b4[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
                } else if (DAT_UnitsState::instance.units[unitID].substate == 0x6c) {
                    DAT_UnitsState::instance.units[unitID].animationFrame
                        = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp
                              .field268_0x5324[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
                } else if (DAT_UnitsState::instance.units[unitID].substate == 0x6d) {
                    DAT_UnitsState::instance.units[unitID].animationFrame
                        = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp
                              .field269_0x53dc[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
                } else {
                    DAT_UnitsState::instance.units[unitID].animationFrame = 0;
                }
            } else {
                DAT_UnitsState::instance.units[unitID].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp
                          .field265_0x5174[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
            }
            if (DAT_UnitsState::instance.units[unitID].animationFrame <= 0) {
                DAT_UnitsState::instance.units[unitID].gfxNumber = 0x10c;
                DAT_UnitHasBecomeIdle::instance = 1;
            } else {
                DAT_UnitsState::instance.units[unitID].gfxNumber
                    = DAT_UnitsState::instance.units[unitID].animationFrame + 0x100;
            }
            int idle = DAT_UnitHasBecomeIdle::instance;
            if (MACRO_CALL(OpenSHC::Map::Units_Func::SetStateToFreetimeWalking)(unitID, idle, 0) != 0) {
                DAT_UnitsState::instance.units[unitID].seated = 0;
                return;
            }
            if (idle == 0) {
                return;
            }
            if (DAT_UnitsState::instance.units[unitID].substate == 0x65) {
                DAT_UnitsState::instance.units[unitID].substate = 0x6a;
                DAT_UnitsState::instance.units[unitID].seated = 1;
            } else if (DAT_UnitsState::instance.units[unitID].substate == 100) {
                DAT_UnitsState::instance.units[unitID].substate = 0x6a;
                DAT_UnitsState::instance.units[unitID].seated = 0;
            } else {
                DAT_UnitsState::instance.units[unitID].substate += 1;
                if (DAT_UnitsState::instance.units[unitID].substate > 0x6d) {
                    DAT_UnitsState::instance.units[unitID].substate = 0x6a;
                }
            }
            DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
            int stockpile = MACRO_CALL_MEMBER(
                OpenSHC::Map::Buildings::BuildingsState_Func::getStorageBuildingForResourceTypeAndAmount,
                DAT_BuildingsState::ptr)(
                OpenSHC::Game::Resources::RT_FLOUR, 1, DAT_UnitsState::instance.units[unitID].owner);
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::buildingIsAccessible,
                    DAT_BuildingsState::ptr)(stockpile, 1)
                    != 0
                && MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::standUpIfSeated, DAT_UnitsState::ptr)(
                       DAT_CurrentUnitSlotID::instance)
                    == 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetID_OR_targetBuildingID
                    = (short)stockpile;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetUID
                    = DAT_BuildingsState::instance.buildings[stockpile].uid;
                if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit, DAT_UnitsState::ptr)(
                        DAT_CurrentUnitSlotID::instance,
                        DAT_BuildingsState::instance.buildings[stockpile].buildingEntryX,
                        DAT_BuildingsState::instance.buildings[stockpile].buildingEntryY, 0)
                    != FALSE) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                        = OpenSHC::Map::Units::States::US_LOOK_AROUNDUnk;
                }
            }
            return;
        }
        if (state == (UnitState)2) {
            // walking to the bakery
            MACRO_CALL(OpenSHC::Map::Units_Func::IncrementAndOptionalUpdateAVValueRelated)(unitID, FALSE);
            DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset = 1;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0x10;
            if (DAT_UnitsState::instance.units[unitID].destinationNeeded
                != OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET) {
                if (MACRO_CALL(OpenSHC::Map::Units_Func::UpdateWorker_ConsiderTakingABreakUnk)(unitID) != FALSE) {
                    return;
                }
                if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit, DAT_UnitsState::ptr)(
                        unitID, DAT_UnitsState::instance.units[unitID].targetX_2,
                        DAT_UnitsState::instance.units[unitID].targetY_2, 0)
                    == FALSE) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                        = OpenSHC::Map::Units::States::US_DISAPPEAR;
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].updateTickTracker = 0;
                    return;
                }
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].destinationNeeded
                    = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::hasUnitReachedDestination, DAT_UnitsState::ptr)(
                    unitID)
                != FALSE) {
                DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
                DAT_UnitsState::instance.units[unitID].state.generic = OpenSHC::Map::Units::States::US_IDLEUnk;
                DAT_UnitsState::instance.units[unitID].substate = -1;
            }
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_LOOK_AROUNDUnk) {
            // fetching flour from the stockpile
            MACRO_CALL(OpenSHC::Map::Units_Func::IncrementAndOptionalUpdateAVValueRelated)(unitID, FALSE);
            DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset = 1;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0x10;
            DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::hasUnitReachedDestination, DAT_UnitsState::ptr)(
                    unitID)
                == FALSE) {
                return;
            }
            DAT_UnitsState::instance.units[unitID].stateBasedSpeed = 0;
            int stockpileUID = DAT_UnitsState::instance.units[unitID].targetUID;
            int stockpile = DAT_UnitsState::instance.units[unitID].targetID_OR_targetBuildingID;
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingResourceAmountByUid,
                    DAT_BuildingsState::ptr)(stockpile, stockpileUID, OpenSHC::Game::Resources::RT_FLOUR)
                <= 0) {
                stockpile = MACRO_CALL_MEMBER(
                    OpenSHC::Map::Buildings::BuildingsState_Func::getStorageBuildingForResourceTypeAndAmount,
                    DAT_BuildingsState::ptr)(
                    OpenSHC::Game::Resources::RT_FLOUR, 1, DAT_UnitsState::instance.units[unitID].owner);
                if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::buildingIsAccessible,
                        DAT_BuildingsState::ptr)(stockpile, 1)
                    != 0) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetID_OR_targetBuildingID
                        = (short)stockpile;
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetUID
                        = DAT_BuildingsState::instance.buildings[stockpile].uid;
                    // the original removes the baker when the next stockpile is reachable
                    if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit,
                            DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance,
                            DAT_BuildingsState::instance.buildings[stockpile].buildingEntryX,
                            DAT_BuildingsState::instance.buildings[stockpile].buildingEntryY, 0)
                        != FALSE) {
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].logicalState
                            = OpenSHC::Map::Units::ULS_REMOVE;
                        return;
                    }
                } else if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setWorkplaceBuildingEntryAsTarget,
                               DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance, 1)
                    == 0) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].logicalState
                        = OpenSHC::Map::Units::ULS_REMOVE;
                    return;
                }
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic = (UnitState)2;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].destinationNeeded
                    = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_NEEDED;
                return;
            }
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::addResourceToStockpile,
                DAT_BuildingsState::ptr)(stockpile, stockpileUID, OpenSHC::Game::Resources::RT_FLOUR, -1, 32, 1);
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].resourceToDeposit = (short)MACRO_CALL(
                OpenSHC::Map::Units_Func::ComputeGoodsProduced)(DAT_CurrentUnitSlotID::instance, 0, TRUE);
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setWorkplaceBuildingEntryAsTarget,
                    DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance, 1)
                == 0) {
                return;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit, DAT_UnitsState::ptr)(
                    DAT_CurrentUnitSlotID::instance,
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetX_2,
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetY_2, 0)
                == FALSE) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].logicalState
                    = OpenSHC::Map::Units::ULS_REMOVE;
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                = OpenSHC::Map::Units::States::US_STAND_UPUnk;
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_STAND_UPUnk) {
            // carrying flour to the bakery
            MACRO_CALL(OpenSHC::Map::Units_Func::IncrementAndOptionalUpdateAVValueRelated)(unitID, FALSE);
            DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset = 0x146;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0x10;
            if (DAT_UnitsState::instance.units[unitID].destinationNeeded
                != OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET) {
                if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit, DAT_UnitsState::ptr)(
                        unitID, DAT_UnitsState::instance.units[unitID].targetX_2,
                        DAT_UnitsState::instance.units[unitID].targetY_2, 0)
                    == FALSE) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].logicalState
                        = OpenSHC::Map::Units::ULS_REMOVE;
                }
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].destinationNeeded
                    = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::hasUnitReachedDestination, DAT_UnitsState::ptr)(
                    unitID)
                != FALSE) {
                DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
                DAT_UnitsState::instance.units[unitID].state.generic = OpenSHC::Map::Units::States::US_JESTER_ROAM_TO;
                DAT_UnitsState::instance.units[unitID].disappearFadeAlphaCountdown = 0;
                DAT_UnitsState::instance.units[unitID].engineerManningSiegeStateRef_checkType = 2;
                DAT_UnitsState::instance.units[unitID].cachedState = OpenSHC::Map::Units::States::US_RELOAD_WEAPONUnk;
                DAT_UnitsState::instance.units[unitID].updateTickTracker = 0;
            }
            return;
        }
        if (state == (UnitState)3) {
            // baking
            MACRO_CALL(OpenSHC::Map::Units_Func::IncrementAndOptionalUpdateAVValueRelated)(unitID, FALSE);
            DAT_BuildingsState::instance.buildings[bakery].workers[0] = (short)unitID;
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::updateBuildingSignpostCounter,
                    DAT_BuildingsState::ptr)(DAT_UnitsState::instance.units[unitID].workplaceBuildingID_1, 1)
                == 0) {
                return;
            }
            MACRO_CALL_MEMBER(
                OpenSHC::Map::Buildings::BuildingsState_Func::updateBuildingSignpostCounter, DAT_BuildingsState::ptr)(
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].workplaceBuildingID_1, 0);
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                = OpenSHC::Map::Units::States::US_JESTER_ROAM_TO;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].disappearFadeAlphaCountdown = 32;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].engineerManningSiegeStateRef_checkType
                = 0xfe;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].cachedState
                = OpenSHC::Map::Units::States::US_AIM_WEAPONUnk;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].updateTickTracker = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].resourceToDeposit = (short)MACRO_CALL(
                OpenSHC::Map::Units_Func::ComputeGoodsProduced)(DAT_CurrentUnitSlotID::instance, 8, FALSE);
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field39_0x58 = 1;
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::resetUnitMovementState, DAT_UnitsState::ptr)(
                DAT_CurrentUnitSlotID::instance);
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSheetFrameOffset = 0x81;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0x10;
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_RELOAD_WEAPONUnk) {
            // putting the flour into the oven
            MACRO_CALL(OpenSHC::Map::Units_Func::IncrementAndOptionalUpdateAVValueRelated)(unitID, FALSE);
            DAT_BuildingsState::instance.buildings[bakery].workers[0] = (short)unitID;
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::updateBuildingSignpostCounter,
                DAT_BuildingsState::ptr)(DAT_UnitsState::instance.units[unitID].workplaceBuildingID_1, 2);
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].updateTickTracker = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic = (UnitState)3;
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_AIM_WEAPONUnk) {
            // leaving the bakery with bread
            DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset = 0x81;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0x10;
            DAT_UnitsState::instance.units[unitID].field131_0x2ac = 1;
            DAT_UnitsState::instance.units[unitID].updateTickTracker += 1;
            if (DAT_UnitsState::instance.units[unitID].updateTickTracker <= 10) {
                return;
            }
            DAT_UnitsState::instance.units[unitID].updateTickTracker = 0;
            int granary
                = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingThatCanStoreThisResource,
                    DAT_BuildingsState::ptr)(
                    OpenSHC::Game::Resources::RT_BREAD, 1, DAT_UnitsState::instance.units[unitID].owner);
            if (granary == 0
                && DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].owner
                    == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                MACRO_CALL(OpenSHC::Map::Units_Func::WarnIfPlayersGranaryIsFull)();
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::buildingIsAccessible,
                    DAT_BuildingsState::ptr)(granary, 1)
                    != 0
                && MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit, DAT_UnitsState::ptr)(
                       DAT_CurrentUnitSlotID::instance, DAT_BuildingsState::instance.buildings[granary].buildingEntryX,
                       DAT_BuildingsState::instance.buildings[granary].buildingEntryY, 0)
                    != FALSE) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetID_OR_targetBuildingID
                    = (short)granary;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetUID
                    = DAT_BuildingsState::instance.buildings[granary].uid;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = OpenSHC::Map::Units::States::US_FIRE_WEAPONUnk;
            }
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_FIRE_WEAPONUnk) {
            // carrying bread to the granary
            MACRO_CALL(OpenSHC::Map::Units_Func::IncrementAndOptionalUpdateAVValueRelated)(unitID, FALSE);
            DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset = 0x81;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0x10;
            DAT_UnitsState::instance.units[unitID].updateTickTracker += 1;
            if (DAT_UnitsState::instance.units[unitID].updateTickTracker < 5) {
                return;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::hasUnitReachedDestination, DAT_UnitsState::ptr)(
                    unitID)
                == FALSE) {
                return;
            }
            DAT_UnitsState::instance.units[unitID].updateTickTracker = 0;
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getResourceCountThatCanBeDeposited,
                    DAT_BuildingsState::ptr)(DAT_UnitsState::instance.units[unitID].targetID_OR_targetBuildingID,
                    OpenSHC::Game::Resources::RT_BREAD, 250)
                == 0) {
                int granary = MACRO_CALL_MEMBER(
                    OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingThatCanStoreThisResource,
                    DAT_BuildingsState::ptr)(OpenSHC::Game::Resources::RT_BREAD, 1,
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].owner);
                if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::buildingIsAccessible,
                        DAT_BuildingsState::ptr)(granary, 1)
                    == 0) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].resourceToDeposit = 0;
                } else {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetID_OR_targetBuildingID
                        = (short)granary;
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetUID
                        = DAT_BuildingsState::instance.buildings[granary].uid;
                    if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit,
                            DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance,
                            DAT_BuildingsState::instance.buildings[granary].buildingEntryX,
                            DAT_BuildingsState::instance.buildings[granary].buildingEntryY, 0)
                        != FALSE) {
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].updateTickTracker = -30;
                    }
                }
            } else {
                MACRO_CALL_MEMBER(
                    OpenSHC::Map::Buildings::BuildingsState_Func::addResourceToStockpile, DAT_BuildingsState::ptr)(
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetID_OR_targetBuildingID,
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetUID,
                    OpenSHC::Game::Resources::RT_BREAD, 1, 250, 1);
                DAT_GameSynchronyState::instance.finalResults
                    .finalFoodProduced[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].owner] += 1;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].resourceToDeposit -= 1;
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].x,
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].y,
                    OpenSHC::DE::SHCDE::FX_STOCK_FOOD);
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].resourceToDeposit > 0) {
                return;
            }
            MACRO_CALL(OpenSHC::Map::Units_Func::IncrementAndOptionalUpdateAVValueRelated)(
                DAT_CurrentUnitSlotID::instance, TRUE);
            int stockpile = MACRO_CALL_MEMBER(
                OpenSHC::Map::Buildings::BuildingsState_Func::getStorageBuildingForResourceTypeAndAmount,
                DAT_BuildingsState::ptr)(OpenSHC::Game::Resources::RT_FLOUR, 1,
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].owner);
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::buildingIsAccessible,
                    DAT_BuildingsState::ptr)(stockpile, 1)
                == 0) {
                if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setWorkplaceBuildingEntryAsTarget,
                        DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance, 1)
                    == 0) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].logicalState
                        = OpenSHC::Map::Units::ULS_REMOVE;
                    return;
                }
            } else {
                if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit, DAT_UnitsState::ptr)(
                        DAT_CurrentUnitSlotID::instance,
                        DAT_BuildingsState::instance.buildings[stockpile].buildingEntryX,
                        DAT_BuildingsState::instance.buildings[stockpile].buildingEntryY, 0)
                    != FALSE) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                        = OpenSHC::Map::Units::States::US_LOOK_AROUNDUnk;
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetID_OR_targetBuildingID
                        = (short)stockpile;
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetUID
                        = DAT_BuildingsState::instance.buildings[stockpile].uid;
                    return;
                }
                if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setWorkplaceBuildingEntryAsTarget,
                        DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance, 1)
                    == 0) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].logicalState
                        = OpenSHC::Map::Units::ULS_REMOVE;
                    return;
                }
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic = (UnitState)2;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate = -1;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].seated = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].destinationNeeded
                = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_NEEDED;
            return;
        }
        if (state == (UnitState)121) {
            DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset = 1;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0x10;
            MACRO_CALL(OpenSHC::Map::Units_Func::SetRestingForUnit)(unitID);
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
            if (DAT_UnitsState::instance.units[unitID].updateTickTracker > 16) {
                DAT_UnitsState::instance.units[unitID].updateTickTracker = 0;
                DAT_UnitsState::instance.units[unitID].disappearFadeAlphaCountdown = 0;
                DAT_UnitsState::instance.units[unitID].state.generic
                    = DAT_UnitsState::instance.units[unitID].cachedState;
                if ((char)DAT_UnitsState::instance.units[unitID].engineerManningSiegeStateRef_checkType > 0) {
                    MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::commitUnitLocation, DAT_UnitsState::ptr)(
                        unitID);
                }
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::updateBuildingSignpostCounter,
                    DAT_BuildingsState::ptr)(DAT_UnitsState::instance.units[unitID].workplaceBuildingID_1, 2);
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
            DAT_BuildingsState::instance.buildings[DAT_UnitsState::instance.units[unitID].workplaceBuildingID_1]
                .idleTimerUnk = 4000;
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_DEATH_01) {
            DAT_UnitsState::instance.units[unitID].facingDirection = 0;
            DAT_UnitsState::instance.units[unitID].animationSpeed = 2;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[unitID].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp
                      .ANIM_Frames_UnitDeath[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
            if (DAT_UnitsState::instance.units[unitID].animationFrame <= 0) {
                DAT_UnitsState::instance.units[unitID].gfxNumber = 0x12d;
                DAT_UnitHasBecomeIdle::instance = 1;
            } else {
                DAT_UnitsState::instance.units[unitID].gfxNumber
                    = DAT_UnitsState::instance.units[unitID].animationFrame + 0x115;
            }
            if (DAT_UnitHasBecomeIdle::instance != 0) {
                DAT_UnitsState::instance.units[unitID].state.generic = OpenSHC::Map::Units::States::US_DISAPPEAR;
                DAT_UnitsState::instance.units[unitID].updateTickTracker = 0;
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
                      .ANIM_Frames_UnitDeath[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
            if (DAT_UnitsState::instance.units[unitID].animationFrame <= 0) {
                DAT_UnitsState::instance.units[unitID].gfxNumber = 0x145;
                DAT_UnitHasBecomeIdle::instance = 1;
            } else {
                DAT_UnitsState::instance.units[unitID].gfxNumber
                    = DAT_UnitsState::instance.units[unitID].animationFrame + 0x12d;
            }
            if (DAT_UnitHasBecomeIdle::instance != 0) {
                DAT_UnitsState::instance.units[unitID].state.generic = OpenSHC::Map::Units::States::US_DISAPPEAR;
                DAT_UnitsState::instance.units[unitID].updateTickTracker = 0;
            }
            return;
        }
        DAT_UnitsState::instance.units[unitID].state.generic = OpenSHC::Map::Units::States::US_IDLEUnk;
        MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::makeUnitStopWalkingByClearingPathProgressState,
            DAT_UnitsState::ptr)(unitID);
    }

}
}
