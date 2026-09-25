#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Units.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/DE/SHCDE/eSFX.hpp"
#include "OpenSHC/Game/GameMode.hpp"
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
    using OpenSHC::Game::GameMode;
    using OpenSHC::Game::Resources::ResourceType;
    using OpenSHC::Map::Units::UnitLogicState;
    using OpenSHC::Map::Units::Pathfinding::DestinationNeededEnum;
    using OpenSHC::Map::Units::States::UnitState;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x00557230
    void Units::UpdatePoleTurner()
    {
        int unitID = DAT_CurrentUnitSlotID::instance;
        if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY) {
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].movementSpeed = 2;
        }
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
                DAT_UnitsState::instance.units[unitID].state.generic = OpenSHC::Map::Units::States::US_RELOAD_WEAPONUnk;
            }
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_IDLEUnk) {
            // idling in the workshop
            DAT_UnitsState::instance.units[unitID].animationSpeed = 2;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[unitID].field39_0x58 = 1;
            DAT_UnitsState::instance.units[unitID].resourceToDeposit = 0;
            DAT_UnitsState::instance.units[unitID].field131_0x2ac = 1;
            if (DAT_UnitsState::instance.units[unitID].substate == 0x66) {
                DAT_UnitsState::instance.units[unitID].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp
                          .field278_0x56fc[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
            } else if (DAT_UnitsState::instance.units[unitID].substate == 0x67) {
                DAT_UnitsState::instance.units[unitID].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp
                          .field279_0x5748[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
            } else if (DAT_UnitsState::instance.units[unitID].substate == 0x68) {
                DAT_UnitsState::instance.units[unitID].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp
                          .field280_0x577c[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
            } else {
                DAT_UnitsState::instance.units[unitID].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp
                          .field281_0x57fc[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
            }
            if (DAT_UnitsState::instance.units[unitID].animationFrame <= 0) {
                DAT_UnitsState::instance.units[unitID].gfxNumber = 0x281;
                DAT_UnitHasBecomeIdle::instance = 1;
            } else {
                DAT_UnitsState::instance.units[unitID].gfxNumber
                    = DAT_UnitsState::instance.units[unitID].animationFrame + 0x280;
            }
            DAT_UnitsState::instance.units[unitID].resourceToDeposit = 0;
            int idle = DAT_UnitHasBecomeIdle::instance;
            if (MACRO_CALL(OpenSHC::Map::Units_Func::SetStateToFreetimeWalking)(unitID, idle, 0) != 0) {
                return;
            }
            if (idle == 0) {
                return;
            }
            if (DAT_UnitsState::instance.units[unitID].substate == 0x66) {
                DAT_UnitsState::instance.units[unitID].substate = 0x67;
            } else if (DAT_UnitsState::instance.units[unitID].substate == 0x67) {
                DAT_UnitsState::instance.units[unitID].substate = 0x68;
            } else {
                DAT_UnitsState::instance.units[unitID].substate
                    = DAT_UnitsState::instance.units[unitID].substate != 0x68 ? 0x66 : 0x69;
            }
            DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
            // a pike needs two pieces of wood, a spear one
            DAT_UnitsState::instance.units[unitID].poleturner_spearOrPike
                = (DAT_BuildingsState::instance.buildings[DAT_UnitsState::instance.units[unitID].workplaceBuildingID_1]
                          .producedItemType
                      != OpenSHC::Game::Resources::RT_SPEAR)
                + 1;
            int stockpile = MACRO_CALL_MEMBER(
                OpenSHC::Map::Buildings::BuildingsState_Func::getStorageBuildingForResourceTypeAndAmount,
                DAT_BuildingsState::ptr)(
                OpenSHC::Game::Resources::RT_WOOD, 1, DAT_UnitsState::instance.units[unitID].owner);
            DAT_BuildingsState::instance
                .buildings[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].workplaceBuildingID_1]
                .producedItemTypeNext
                = DAT_BuildingsState::instance
                      .buildings[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].workplaceBuildingID_1]
                      .producedItemType;
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::buildingIsAccessible,
                    DAT_BuildingsState::ptr)(stockpile, 1)
                == 0) {
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetID_OR_targetBuildingID
                = (short)stockpile;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetUID
                = DAT_BuildingsState::instance.buildings[stockpile].uid;
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit, DAT_UnitsState::ptr)(
                    DAT_CurrentUnitSlotID::instance, DAT_BuildingsState::instance.buildings[stockpile].buildingEntryX,
                    DAT_BuildingsState::instance.buildings[stockpile].buildingEntryY, 0)
                != FALSE) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic = (UnitState)2;
            }
            return;
        }
        if (state == (UnitState)2) {
            // taking wood from the stockpile
            MACRO_CALL(OpenSHC::Map::Units_Func::IncrementAndOptionalUpdateAVValueRelated)(unitID, FALSE);
            DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset = 1;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0x10;
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::hasUnitReachedDestination, DAT_UnitsState::ptr)(
                    unitID)
                == FALSE) {
                return;
            }
            DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingResourceAmountByUid,
                    DAT_BuildingsState::ptr)(DAT_UnitsState::instance.units[unitID].targetID_OR_targetBuildingID,
                    DAT_UnitsState::instance.units[unitID].targetUID, OpenSHC::Game::Resources::RT_WOOD)
                > 0) {
                DAT_UnitsState::instance.units[unitID].resourceToDeposit = 1;
                if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setWorkplaceBuildingEntryAsTarget,
                        DAT_UnitsState::ptr)(unitID, 1)
                    == 0) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].logicalState
                        = OpenSHC::Map::Units::ULS_REMOVE;
                    return;
                }
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic = (UnitState)3;
                if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit, DAT_UnitsState::ptr)(
                        DAT_CurrentUnitSlotID::instance,
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetX_2,
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetY_2, 0)
                    == FALSE) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                        = OpenSHC::Map::Units::States::US_DISAPPEAR;
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].updateTickTracker = 0;
                    return;
                }
                MACRO_CALL_MEMBER(
                    OpenSHC::Map::Buildings::BuildingsState_Func::addResourceToStockpile, DAT_BuildingsState::ptr)(
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetID_OR_targetBuildingID,
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetUID,
                    OpenSHC::Game::Resources::RT_WOOD, -1, 48, 1);
                return;
            }
            int stockpile = MACRO_CALL_MEMBER(
                OpenSHC::Map::Buildings::BuildingsState_Func::getStorageBuildingForResourceTypeAndAmount,
                DAT_BuildingsState::ptr)(
                OpenSHC::Game::Resources::RT_WOOD, 1, DAT_UnitsState::instance.units[unitID].owner);
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::buildingIsAccessible,
                    DAT_BuildingsState::ptr)(stockpile, 1)
                == 0) {
                if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setWorkplaceBuildingEntryAsTarget,
                        DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance, 1)
                    != 0) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                        = OpenSHC::Map::Units::States::US_RELOAD_WEAPONUnk;
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].destinationNeeded
                        = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_NEEDED;
                    return;
                }
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].logicalState
                    = OpenSHC::Map::Units::ULS_REMOVE;
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetID_OR_targetBuildingID
                = (short)stockpile;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetUID
                = DAT_BuildingsState::instance.buildings[stockpile].uid;
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit, DAT_UnitsState::ptr)(
                    DAT_CurrentUnitSlotID::instance, DAT_BuildingsState::instance.buildings[stockpile].buildingEntryX,
                    DAT_BuildingsState::instance.buildings[stockpile].buildingEntryY, 0)
                != FALSE) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic = (UnitState)2;
            }
            return;
        }
        if (state == (UnitState)3) {
            // bringing wood to the workshop
            MACRO_CALL(OpenSHC::Map::Units_Func::IncrementAndOptionalUpdateAVValueRelated)(unitID, FALSE);
            DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset = 0x181;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0x10;
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::hasUnitReachedDestination, DAT_UnitsState::ptr)(
                    unitID)
                == FALSE) {
                return;
            }
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::addResourceToStockpile,
                DAT_BuildingsState::ptr)(DAT_UnitsState::instance.units[unitID].workplaceBuildingID_1,
                DAT_BuildingsState::instance.buildings[DAT_UnitsState::instance.units[unitID].workplaceBuildingID_1]
                    .uid,
                OpenSHC::Game::Resources::RT_WOOD, 1, 48, 1);
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].resourceToDeposit = 0;
            if ((char)DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].poleturner_spearOrPike
                <= DAT_BuildingsState::instance
                    .buildings[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].workplaceBuildingID_1]
                    .resources[2]) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = OpenSHC::Map::Units::States::US_JESTER_ROAM_TO;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].disappearFadeAlphaCountdown = 0;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].engineerManningSiegeStateRef_checkType
                    = 2;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].cachedState
                    = OpenSHC::Map::Units::States::US_FIRE_WEAPONUnk;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].updateTickTracker = 0;
                DAT_BuildingsState::instance
                    .buildings[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].workplaceBuildingID_1]
                    .producedItemTypeNext
                    = DAT_BuildingsState::instance
                          .buildings[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                                  .workplaceBuildingID_1]
                          .producedItemType;
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                = OpenSHC::Map::Units::States::US_IDLEUnk;
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_RELOAD_WEAPONUnk) {
            // walking to the workshop
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
                    != FALSE) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].destinationNeeded
                        = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET;
                }
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::hasUnitReachedDestination, DAT_UnitsState::ptr)(
                    unitID)
                != FALSE) {
                DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
                DAT_UnitsState::instance.units[unitID].state.generic = OpenSHC::Map::Units::States::US_IDLEUnk;
            }
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_AIM_WEAPONUnk) {
            // the pole is finished
            MACRO_CALL(OpenSHC::Map::Units_Func::IncrementAndOptionalUpdateAVValueRelated)(unitID, FALSE);
            DAT_UnitsState::instance.units[unitID].field131_0x2ac = 1;
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
                = OpenSHC::Map::Units::States::US_LOOK_AROUNDUnk;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].updateTickTracker = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].resourceToDeposit = (short)MACRO_CALL(
                OpenSHC::Map::Units_Func::ComputeGoodsProduced)(DAT_CurrentUnitSlotID::instance, 1, TRUE);
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field39_0x58 = 1;
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::resetUnitMovementState, DAT_UnitsState::ptr)(
                DAT_CurrentUnitSlotID::instance);
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSheetFrameOffset = 0x101;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0x10;
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_FIRE_WEAPONUnk) {
            // turning the pole
            MACRO_CALL(OpenSHC::Map::Units_Func::IncrementAndOptionalUpdateAVValueRelated)(unitID, FALSE);
            DAT_UnitsState::instance.units[unitID].field131_0x2ac = 1;
            DAT_UnitsState::instance.units[unitID].updateTickTracker += 1;
            int workshop = DAT_UnitsState::instance.units[unitID].workplaceBuildingID_1;
            if (DAT_UnitsState::instance.units[unitID].updateTickTracker < 30) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::updateBuildingSignpostCounter,
                    DAT_BuildingsState::ptr)(workshop, 3);
                return;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingResourceAmountByUid,
                    DAT_BuildingsState::ptr)(
                    workshop, DAT_BuildingsState::instance.buildings[workshop].uid, OpenSHC::Game::Resources::RT_WOOD)
                > 0) {
                DAT_BuildingsState::instance.buildings[workshop].resources[2] = 0;
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::updateBuildingSignpostCounter,
                    DAT_BuildingsState::ptr)(workshop, 2);
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].updateTickTracker = 0;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = OpenSHC::Map::Units::States::US_AIM_WEAPONUnk;
                return;
            }
            DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
            DAT_UnitsState::instance.units[unitID].state.generic = OpenSHC::Map::Units::States::US_IDLEUnk;
            DAT_UnitsState::instance.units[unitID].updateTickTracker = 0;
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::resetUnitMovementState, DAT_UnitsState::ptr)(
                unitID);
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSheetFrameOffset = 0x101;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0x10;
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_LOOK_AROUNDUnk) {
            // leaving the workshop with the weapon
            DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset
                = DAT_BuildingsState::instance.buildings[DAT_UnitsState::instance.units[unitID].workplaceBuildingID_1]
                        .producedItemTypeNext
                    != OpenSHC::Game::Resources::RT_SPEAR
                ? 0x101
                : 0x81;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0x10;
            DAT_UnitsState::instance.units[unitID].field131_0x2ac = 1;
            DAT_UnitsState::instance.units[unitID].updateTickTracker += 1;
            if (DAT_UnitsState::instance.units[unitID].updateTickTracker < 11) {
                return;
            }
            DAT_UnitsState::instance.units[unitID].updateTickTracker = 0;
            int armory = MACRO_CALL_MEMBER(
                OpenSHC::Map::Buildings::BuildingsState_Func::getArmoryWithSpaceLeft, DAT_BuildingsState::ptr)(0,
                DAT_BuildingsState::instance.buildings[DAT_UnitsState::instance.units[unitID].workplaceBuildingID_1]
                    .producedItemTypeNext,
                DAT_UnitsState::instance.units[unitID].owner, DAT_UnitsState::instance.units[unitID].resourceToDeposit);
            if (armory == 0
                && DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].owner
                    == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                MACRO_CALL(OpenSHC::Map::Units_Func::PlayArmoryIsFullWarning)();
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::buildingIsAccessible,
                    DAT_BuildingsState::ptr)(armory, 1)
                == 0) {
                return;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit, DAT_UnitsState::ptr)(
                    DAT_CurrentUnitSlotID::instance, DAT_BuildingsState::instance.buildings[armory].buildingEntryX,
                    DAT_BuildingsState::instance.buildings[armory].buildingEntryY, 0)
                == FALSE) {
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetID_OR_targetBuildingID
                = (short)armory;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetUID
                = DAT_BuildingsState::instance.buildings[armory].uid;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                = OpenSHC::Map::Units::States::US_STAND_UPUnk;
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_STAND_UPUnk) {
            // carrying the weapon to the armory
            MACRO_CALL(OpenSHC::Map::Units_Func::IncrementAndOptionalUpdateAVValueRelated)(unitID, FALSE);
            DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset
                = DAT_BuildingsState::instance.buildings[DAT_UnitsState::instance.units[unitID].workplaceBuildingID_1]
                        .producedItemTypeNext
                    != OpenSHC::Game::Resources::RT_SPEAR
                ? 0x101
                : 0x81;
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
            if (DAT_UnitsState::instance.units[unitID].resourceToDeposit != 0) {
                DAT_UnitsState::instance.units[unitID].updateTickTracker = 0;
                if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getArmoryWithSpaceLeft,
                        DAT_BuildingsState::ptr)(DAT_UnitsState::instance.units[unitID].targetID_OR_targetBuildingID,
                        DAT_BuildingsState::instance
                            .buildings[DAT_UnitsState::instance.units[unitID].workplaceBuildingID_1]
                            .producedItemTypeNext,
                        DAT_UnitsState::instance.units[unitID].owner, 1)
                    == 0) {
                    int armory = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getArmoryWithSpaceLeft,
                        DAT_BuildingsState::ptr)(0,
                        DAT_BuildingsState::instance
                            .buildings[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                                    .workplaceBuildingID_1]
                            .producedItemTypeNext,
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].owner,
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].resourceToDeposit);
                    if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::buildingIsAccessible,
                            DAT_BuildingsState::ptr)(armory, 1)
                        == 0) {
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].resourceToDeposit = 0;
                    } else {
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetID_OR_targetBuildingID
                            = (short)armory;
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetUID
                            = DAT_BuildingsState::instance.buildings[armory].uid;
                        if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit,
                                DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance,
                                DAT_BuildingsState::instance.buildings[armory].buildingEntryX,
                                DAT_BuildingsState::instance.buildings[armory].buildingEntryY, 0)
                            == FALSE) {
                            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].resourceToDeposit = 0;
                        }
                    }
                } else {
                    MACRO_CALL_MEMBER(
                        OpenSHC::Map::Buildings::BuildingsState_Func::addResourceToStockpile, DAT_BuildingsState::ptr)(
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetID_OR_targetBuildingID,
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetUID,
                        (OpenSHC::Game::Resources::ResourceType)DAT_BuildingsState::instance
                            .buildings[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                                    .workplaceBuildingID_1]
                            .producedItemTypeNext,
                        1, 50, 1);
                    DAT_GameSynchronyState::instance.finalResults
                        .finalWeaponsProduced[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].owner]
                        += 1;
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].resourceToDeposit -= 1;
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].x,
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].y,
                        OpenSHC::DE::SHCDE::FX_STOCK_WEAPON);
                }
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].resourceToDeposit > 0) {
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].destinationNeeded
                = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_NEEDED;
            MACRO_CALL(OpenSHC::Map::Units_Func::IncrementAndOptionalUpdateAVValueRelated)(
                DAT_CurrentUnitSlotID::instance, TRUE);
            if (MACRO_CALL(OpenSHC::Map::Units_Func::ConsiderHavingABreakNowUnk)(
                    DAT_CurrentUnitSlotID::instance, OpenSHC::Map::Units::States::US_RELOAD_WEAPONUnk)
                != FALSE) {
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].poleturner_spearOrPike
                = (DAT_BuildingsState::instance
                          .buildings[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                                  .workplaceBuildingID_1]
                          .producedItemType
                      != OpenSHC::Game::Resources::RT_SPEAR)
                + 1;
            int stockpile = MACRO_CALL_MEMBER(
                OpenSHC::Map::Buildings::BuildingsState_Func::getStorageBuildingForResourceTypeAndAmount,
                DAT_BuildingsState::ptr)(OpenSHC::Game::Resources::RT_WOOD, 1,
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].owner);
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::buildingIsAccessible,
                    DAT_BuildingsState::ptr)(stockpile, 1)
                == 0) {
                if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setWorkplaceBuildingEntryAsTarget,
                        DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance, 1)
                    != 0) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                        = OpenSHC::Map::Units::States::US_RELOAD_WEAPONUnk;
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].destinationNeeded
                        = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_NEEDED;
                    return;
                }
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].logicalState
                    = OpenSHC::Map::Units::ULS_REMOVE;
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetID_OR_targetBuildingID
                = (short)stockpile;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetUID
                = DAT_BuildingsState::instance.buildings[stockpile].uid;
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit, DAT_UnitsState::ptr)(
                    DAT_CurrentUnitSlotID::instance, DAT_BuildingsState::instance.buildings[stockpile].buildingEntryX,
                    DAT_BuildingsState::instance.buildings[stockpile].buildingEntryY, 0)
                != FALSE) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic = (UnitState)2;
            }
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
            } else if ((char)DAT_UnitsState::instance.units[unitID].disappearFadeAlphaCountdown > 31) {
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
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::updateBuildingSignpostCounter,
                DAT_BuildingsState::ptr)(DAT_UnitsState::instance.units[unitID].workplaceBuildingID_1, 2);
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_DEATH_01) {
            DAT_UnitsState::instance.units[unitID].facingDirection = 0;
            DAT_UnitsState::instance.units[unitID].animationSpeed = 2;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[unitID].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp
                      .field6_0x6d4[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
            if (DAT_UnitsState::instance.units[unitID].animationFrame <= 0) {
                DAT_UnitsState::instance.units[unitID].gfxNumber = 0x2c0;
                DAT_UnitsState::instance.units[unitID].logicalState = OpenSHC::Map::Units::ULS_REMOVE;
                DAT_UnitHasBecomeIdle::instance = 1;
                return;
            }
            DAT_UnitsState::instance.units[unitID].gfxNumber
                = DAT_UnitsState::instance.units[unitID].animationFrame + 0x2a8;
            if (DAT_UnitHasBecomeIdle::instance != 0) {
                DAT_UnitsState::instance.units[unitID].logicalState = OpenSHC::Map::Units::ULS_REMOVE;
            }
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_DEATH_03) {
            DAT_UnitsState::instance.units[unitID].facingDirection = 0;
            DAT_UnitsState::instance.units[unitID].animationSpeed = 2;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[unitID].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp
                      .field6_0x6d4[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
            if (DAT_UnitsState::instance.units[unitID].animationFrame <= 0) {
                DAT_UnitsState::instance.units[unitID].gfxNumber = 0x2a8;
                DAT_UnitsState::instance.units[unitID].logicalState = OpenSHC::Map::Units::ULS_REMOVE;
                DAT_UnitHasBecomeIdle::instance = 1;
                return;
            }
            DAT_UnitsState::instance.units[unitID].gfxNumber
                = DAT_UnitsState::instance.units[unitID].animationFrame + 0x290;
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
                      .field6_0x6d4[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
            if (DAT_UnitsState::instance.units[unitID].animationFrame <= 0) {
                DAT_UnitsState::instance.units[unitID].gfxNumber = 0x2d8;
                DAT_UnitsState::instance.units[unitID].logicalState = OpenSHC::Map::Units::ULS_REMOVE;
                DAT_UnitHasBecomeIdle::instance = 1;
                return;
            }
            DAT_UnitsState::instance.units[unitID].gfxNumber
                = DAT_UnitsState::instance.units[unitID].animationFrame + 0x2c0;
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
            DAT_BuildingsState::instance.buildings[DAT_UnitsState::instance.units[unitID].workplaceBuildingID_1]
                .idleTimerUnk = 4000;
            return;
        }
        DAT_UnitsState::instance.units[unitID].state.generic = OpenSHC::Map::Units::States::US_IDLEUnk;
        MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::makeUnitStopWalkingByClearingPathProgressState,
            DAT_UnitsState::ptr)(unitID);
    }

}
}
