#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Map/Units.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/DE/SHCDE/eSFX.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"
#include "OpenSHC/Map/Units/Pathfinding/DestinationNeededEnum.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/States/UnitState_OxState.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentUnitSlotID.hpp"
#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
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
    using OpenSHC::Map::Units::States::UnitState_OxState;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x0053F940
    void Units::UpdateOx()
    {
        int unitID = DAT_CurrentUnitSlotID::instance;
        int workplace = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].workplaceBuildingID_1;
        int owner = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].owner;
        if (workplace == 0
            || DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].workplaceBuildingUID
                != DAT_BuildingsState::instance.buildings[workplace].uid) {
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                = OpenSHC::Map::Units::States::US_DISAPPEAR;
        }
        if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY) {
            DAT_UnitsState::instance.units[unitID].movementSpeed = 1;
        }
        DAT_GameState::instance.playerDataArray[owner].nonInteractiveCitizenCountUnk += 1;
        DAT_UnitsState::instance.units[unitID].calculatedOwnerPlayerIndex = 0;
        short state = DAT_UnitsState::instance.units[unitID].state.ox;
        if (state == OpenSHC::Map::Units::States::USOS_RESET) {
            DAT_UnitsState::instance.units[unitID].animationSpeed = 4;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            if (DAT_UnitsState::instance.units[unitID].resourceToDeposit < 8) {
                DAT_UnitsState::instance.units[unitID].destinationNeeded
                    = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_NEEDED;
                DAT_UnitsState::instance.units[unitID].state.ox = OpenSHC::Map::Units::States::USOS_GOING_TO_WORKPLACE;
                return;
            }
            int storage
                = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingThatCanStoreThisResource,
                    DAT_BuildingsState::ptr)(
                    OpenSHC::Game::Resources::RT_STONE, 1, DAT_UnitsState::instance.units[unitID].owner);
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::buildingIsAccessible,
                    DAT_BuildingsState::ptr)(storage, 1)
                == 0) {
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetID_OR_targetBuildingID
                = (short)storage;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetUID
                = DAT_BuildingsState::instance.buildings[storage].uid;
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit, DAT_UnitsState::ptr)(
                    DAT_CurrentUnitSlotID::instance, DAT_BuildingsState::instance.buildings[storage].buildingEntryX,
                    DAT_BuildingsState::instance.buildings[storage].buildingEntryY, 0)
                == FALSE) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].destinationNeeded
                    = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_NEEDED;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.ox
                    = OpenSHC::Map::Units::States::USOS_GOING_TO_WORKPLACE;
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.ox
                = OpenSHC::Map::Units::States::USOS_TAKING_GOODS_TO_STORE;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].moveInstructionSpeedDelayTracker = 80;
            return;
        }
        if (state == OpenSHC::Map::Units::States::USOS_EATING_GRASS) {
            DAT_UnitsState::instance.units[unitID].animationSpeed = 4;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::calculateOrientation,
                DAT_DirectionAlgorithmState::ptr)(DAT_UnitsState::instance.units[unitID].x,
                DAT_UnitsState::instance.units[unitID].y, DAT_BuildingsState::instance.buildings[workplace].x,
                DAT_BuildingsState::instance.buildings[workplace].y);
            if (DAT_DirectionAlgorithmState::instance.orientation == 15) {
                DAT_DirectionAlgorithmState::instance.orientation = 4;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].facingDirection
                = (short)DAT_DirectionAlgorithmState::instance.orientation;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.field250_0x4b1c
                      [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame <= 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                          .facingDirectionMapOrientationCorrected
                    + 0x101;
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                          .facingDirectionMapOrientationCorrected
                    + 0xf9 + DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame * 8;
                if (DAT_UnitHasBecomeIdle::instance == 0) {
                    if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].resourceToDeposit < 8
                        || DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field279_0x3f2 != 0) {
                        return;
                    }
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.ox
                        = OpenSHC::Map::Units::States::USOS_RESET;
                    DAT_UnitHasBecomeIdle::instance = 0;
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field279_0x3f2 = 1;
                    return;
                }
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
            DAT_UnitHasBecomeIdle::instance = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.ox
                = OpenSHC::Map::Units::States::USOS_RESET;
            return;
        }
        if (state == OpenSHC::Map::Units::States::USOS_TAKING_GOODS_TO_STORE) {
            DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset = 0x81;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0x10;
            DAT_UnitsState::instance.units[unitID].movementSpeed = 3;
            if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY) {
                DAT_UnitsState::instance.units[unitID].movementSpeed = 1;
            }
            DAT_UnitsState::instance.units[unitID].stateBasedSpeed = 0;
            if (DAT_UnitsState::instance.units[unitID].moveInstructionSpeedDelayTracker != 0) {
                DAT_UnitsState::instance.units[unitID].moveInstructionSpeedDelayTracker -= 1;
                DAT_UnitsState::instance.units[unitID].stateBasedSpeed = -1;
                DAT_UnitsState::instance.units[unitID].movementSpeed += 5;
                DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
                return;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::hasUnitReachedDestination, DAT_UnitsState::ptr)(
                    DAT_CurrentUnitSlotID::instance)
                != FALSE) {
                DAT_UnitsState::instance.units[unitID].updateTickTracker = 0;
                DAT_UnitsState::instance.units[unitID].state.ox = OpenSHC::Map::Units::States::USOS_WAITING;
            }
            return;
        }
        if (state == OpenSHC::Map::Units::States::USOS_WAITING) {
            DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset = 1;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0x10;
            DAT_UnitsState::instance.units[unitID].field279_0x3f2 = 0;
            if (DAT_UnitsState::instance.units[unitID].resourceToDeposit <= 0) {
                if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setWorkplaceBuildingEntryAsTarget,
                        DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance, 1)
                    == 0) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].logicalState
                        = OpenSHC::Map::Units::ULS_REMOVE;
                    return;
                }
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.ox
                    = OpenSHC::Map::Units::States::USOS_GOING_TO_WORKPLACE;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].destinationNeeded
                    = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_NEEDED;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSheetFrameOffset = 1;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].moveInstructionSpeedDelayTracker = 2;
                return;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::canBuildingStoreTheAmount,
                    DAT_BuildingsState::ptr)(DAT_UnitsState::instance.units[unitID].targetID_OR_targetBuildingID,
                    OpenSHC::Game::Resources::RT_STONE, 48)
                != 0) {
                MACRO_CALL_MEMBER(
                    OpenSHC::Map::Buildings::BuildingsState_Func::addResourceToStockpile, DAT_BuildingsState::ptr)(
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetID_OR_targetBuildingID,
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetUID,
                    OpenSHC::Game::Resources::RT_STONE, 1, 48, 1);
                DAT_GameSynchronyState::instance.finalResults
                    .finalStoneProduced[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].owner] += 1;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].resourceToDeposit -= 1;
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].x,
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].y,
                    OpenSHC::DE::SHCDE::FX_STOCK_STONE);
                return;
            }
            int storage
                = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingThatCanStoreThisResource,
                    DAT_BuildingsState::ptr)(OpenSHC::Game::Resources::RT_STONE, 1,
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].owner);
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::buildingIsAccessible,
                    DAT_BuildingsState::ptr)(storage, 1)
                == 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].resourceToDeposit = 0;
                return;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit, DAT_UnitsState::ptr)(
                    DAT_CurrentUnitSlotID::instance, DAT_BuildingsState::instance.buildings[storage].buildingEntryX,
                    DAT_BuildingsState::instance.buildings[storage].buildingEntryY, 0)
                == FALSE) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].resourceToDeposit = 0;
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetID_OR_targetBuildingID
                = (short)storage;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetUID
                = DAT_BuildingsState::instance.buildings[storage].uid;
            return;
        }
        if (state == OpenSHC::Map::Units::States::USOS_GOING_TO_WORKPLACE) {
            DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset = 1;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0x10;
            DAT_UnitsState::instance.units[unitID].movementSpeed = 3;
            if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY) {
                DAT_UnitsState::instance.units[unitID].movementSpeed = 1;
            }
            DAT_UnitsState::instance.units[unitID].stateBasedSpeed = 0;
            if (DAT_UnitsState::instance.units[unitID].destinationNeeded
                == OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_NEEDED) {
                if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit, DAT_UnitsState::ptr)(
                        DAT_CurrentUnitSlotID::instance, DAT_UnitsState::instance.units[unitID].targetX_2,
                        DAT_UnitsState::instance.units[unitID].targetY_2, 0)
                    == FALSE) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].destinationNeeded
                        = OpenSHC::Map::Units::Pathfinding::DNE_OX_SPECIFIC_COUNTDOWN;
                } else {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].destinationNeeded
                        = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET;
                }
            } else if (DAT_UnitsState::instance.units[unitID].destinationNeeded > 1) {
                DAT_UnitsState::instance.units[unitID].destinationNeeded -= 1;
            }
            if (DAT_UnitsState::instance.units[unitID].destinationNeeded
                != OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET) {
                return;
            }
            if (DAT_UnitsState::instance.units[unitID].moveInstructionSpeedDelayTracker != 0) {
                DAT_UnitsState::instance.units[unitID].moveInstructionSpeedDelayTracker -= 1;
                DAT_UnitsState::instance.units[unitID].stateBasedSpeed = -1;
                DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
                return;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::hasUnitReachedDestination, DAT_UnitsState::ptr)(
                    DAT_CurrentUnitSlotID::instance)
                != FALSE) {
                DAT_UnitsState::instance.units[unitID].updateTickTracker = 0;
                DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
                DAT_UnitsState::instance.units[unitID].state.ox = OpenSHC::Map::Units::States::USOS_EATING_GRASS;
            }
            return;
        }
        if (state == (UnitState)0x6c) {
            DAT_UnitsState::instance.units[unitID].stateBasedSpeed = 0;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0x10;
            DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset = 1;
            return;
        }
        if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::checkIfCitizenUnitIsAliveBasedOnState,
                DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance)
            != FALSE) {
            DAT_UnitsState::instance.units[unitID].facingDirection = 0;
            DAT_UnitsState::instance.units[unitID].animationSpeed = 4;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[unitID].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp
                      .field251_0x4bc4[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
            if (DAT_UnitsState::instance.units[unitID].animationCycleNumber == 1
                && DAT_UnitsState::instance.units[unitID].animationCycleNumberHasJustIncremented != FALSE) {
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    DAT_UnitsState::instance.units[unitID].x, DAT_UnitsState::instance.units[unitID].y,
                    OpenSHC::DE::SHCDE::FX_OX_DIE);
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame <= 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber = 0x14c;
                DAT_UnitHasBecomeIdle::instance = 1;
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame + 0x140;
            }
            // loaded oxen use the frames with stone
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].resourceToDeposit != 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber += 12;
            }
            if (DAT_UnitHasBecomeIdle::instance != 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = OpenSHC::Map::Units::States::US_DISAPPEAR;
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
        DAT_UnitsState::instance.units[unitID].state.ox = OpenSHC::Map::Units::States::USOS_RESET;
        MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::makeUnitStopWalkingByClearingPathProgressState,
            DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance);
    }

}
}
