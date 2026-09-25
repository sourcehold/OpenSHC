#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Units.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentUnitSlotID.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitHasBecomeIdle.hpp"
#include "OpenSHC/Globals/DAT_UnitPropertiesDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::Units::UnitLogicState;
    using OpenSHC::Map::Units::States::UnitState;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x0053EAA0
    void Units::UpdatePeasant()
    {
        int owner = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].owner;
        int campfire = DAT_GameState::instance.playerDataArray[owner].campground.id;
        DAT_GameState::instance.playerDataArray[owner].availablePeasantsOrHousedPeasants += 1;
        MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::clearHiddenFlagAndUpdatePosition, DAT_UnitsState::ptr)(
            DAT_CurrentUnitSlotID::instance);
        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].calculatedOwnerPlayerIndex
            = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].fixedRng & 7;
        UnitStateShort state = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic;
        if (state == OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk) {
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].facingDirection = 4;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].tribeID = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSpeed = 2;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
            DAT_GameState::instance.playerDataArray[owner].availablePeasantsAtFire += 1;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].facingDirectionMapOrientationCorrected
                    / 2
                + 0x81;
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].isDisappearingUnk != 0) {
                // appearing at the campfire
                DAT_GameState::instance.playerDataArray[owner].count += 1;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = OpenSHC::Map::Units::States::US_JESTER_ROAM_TO;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].disappearFadeAlphaCountdown = 32;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].engineerManningSiegeStateRef_checkType
                    = 0xff;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].cachedState
                    = OpenSHC::Map::Units::States::US_RELOAD_WEAPONUnk;
                return;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::moveUnitAroundCampfire, DAT_GameState::ptr)(
                    DAT_CurrentUnitSlotID::instance,
                    DAT_GameState::instance.playerDataArray[owner].availablePeasantsOrHousedPeasants)
                == -1) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].logicalState
                    = OpenSHC::Map::Units::ULS_REMOVE;
                return;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::moveUnitAroundCampfire, DAT_GameState::ptr)(
                    DAT_CurrentUnitSlotID::instance,
                    DAT_GameState::instance.playerDataArray[owner].availablePeasantsOrHousedPeasants)
                > 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].idInTribe
                    = (short)DAT_GameState::instance.playerDataArray[owner].availablePeasantsOrHousedPeasants;
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit, DAT_UnitsState::ptr)(
                    DAT_CurrentUnitSlotID::instance,
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetX_2,
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetY_2, 0);
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = OpenSHC::Map::Units::States::US_LOOK_AROUNDUnk;
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                = OpenSHC::Map::Units::States::US_STAND_UPUnk;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate = -1;
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_RELOAD_WEAPONUnk) {
            // walking to the campfire
            DAT_GameState::instance.playerDataArray[owner].count += 1;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0x10;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSheetFrameOffset = 1;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed = 0;
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::hasUnitReachedDestination, DAT_UnitsState::ptr)(
                    DAT_CurrentUnitSlotID::instance)
                == FALSE) {
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].isDisappearingUnk = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                = OpenSHC::Map::Units::States::US_AIM_WEAPONUnk;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].facingDirection = 0;
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_AIM_WEAPONUnk) {
            // warming up at the campfire
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSpeed = 2;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].seated = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp
                      .useWeapon[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
            DAT_GameState::instance.playerDataArray[owner].count += 1;
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame <= 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
                DAT_UnitHasBecomeIdle::instance = 1;
                return;
            }
            int direction;
            if (DAT_BuildingsState::instance.buildings[campfire].orientation == 4) {
                direction = (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                                    .facingDirectionMapOrientationCorrected
                                + 4)
                    % 8;
            } else if (DAT_BuildingsState::instance.buildings[campfire].orientation == 2) {
                direction = (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                                    .facingDirectionMapOrientationCorrected
                                + 6)
                    % 8;
            } else if (DAT_BuildingsState::instance.buildings[campfire].orientation == 6) {
                direction = (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                                    .facingDirectionMapOrientationCorrected
                                + 2)
                    % 8;
            } else {
                direction = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                                .facingDirectionMapOrientationCorrected
                    % 8;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber = direction / 2 + 0x155
                + DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame * 4;
            if (DAT_UnitHasBecomeIdle::instance == 0) {
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_MOVE_TO_DESTINATION) {
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0x10;
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].moveInstructionSpeedDelayTracker == 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSheetFrameOffset = 1;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed = 0;
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSheetFrameOffset = 1;
                if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].moveInstructionSpeedDelayTracker
                    > 70) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed = -1;
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
                } else {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed = 0;
                }
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::hasUnitReachedDestination, DAT_UnitsState::ptr)(
                    DAT_CurrentUnitSlotID::instance)
                == FALSE) {
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].cachedState;
            return;
        }
        if (state == (UnitState)0x6c) {
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSheetFrameOffset = 1;
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_JESTER_ROAM_TO) {
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].disappearFadeAlphaCountdown
                += DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                       .engineerManningSiegeStateRef_checkType;
            if ((char)DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].disappearFadeAlphaCountdown < 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].disappearFadeAlphaCountdown = 0;
            } else if ((char)DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].disappearFadeAlphaCountdown
                > 31) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].disappearFadeAlphaCountdown = 31;
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].cachedState
                == OpenSHC::Map::Units::States::US_RELOAD_WEAPONUnk) {
                DAT_GameState::instance.playerDataArray[owner].count += 1;
            }
            if ((char)DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                        .engineerManningSiegeStateRef_checkType
                    > 0
                && DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].isDisappearingUnk != 0) {
                // turning into a military unit
                switch (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].unitTypeToChangeInto) {
                case OpenSHC::Map::Units::UT_TUNNELER:
                case OpenSHC::Map::Units::UT_E_ARCHER:
                case OpenSHC::Map::Units::UT_E_XBOW:
                case OpenSHC::Map::Units::UT_E_SPEAR:
                case OpenSHC::Map::Units::UT_E_PIKE:
                case OpenSHC::Map::Units::UT_E_MACE:
                case OpenSHC::Map::Units::UT_E_SWORD:
                case OpenSHC::Map::Units::UT_E_KNIGHT:
                case OpenSHC::Map::Units::UT_E_LADDER:
                case OpenSHC::Map::Units::UT_E_ENGINEER:
                case OpenSHC::Map::Units::UT_E_MONK:
                case OpenSHC::Map::Units::UT_S_CATAPULT:
                case OpenSHC::Map::Units::UT_S_TOWER:
                case OpenSHC::Map::Units::UT_S_BATTERINGRAM:
                case OpenSHC::Map::Units::UT_S_SHIELD:
                case OpenSHC::Map::Units::UT_S_BALLISTA:
                case OpenSHC::Map::Units::UT_A_ARCHER:
                case OpenSHC::Map::Units::UT_A_SLAVE:
                case OpenSHC::Map::Units::UT_A_SLINGER:
                case OpenSHC::Map::Units::UT_A_ASSASSIN:
                case OpenSHC::Map::Units::UT_A_HARCHER:
                case OpenSHC::Map::Units::UT_A_SWORDSMAN:
                case OpenSHC::Map::Units::UT_A_FIRETHROWER:
                case OpenSHC::Map::Units::UT_S_FBALLISTA:
                    DAT_GameState::instance.playerDataArray[owner].count_2 += 1;
                    break;
                }
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].updateTickTracker += 1;
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].updateTickTracker <= 32) {
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].updateTickTracker = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].disappearFadeAlphaCountdown = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].cachedState;
            if ((char)DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                    .engineerManningSiegeStateRef_checkType
                < 0) {
                if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].isDisappearingUnk == 0) {
                    return;
                }
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::prepareCampgroundCoords,
                    DAT_BuildingsState::ptr)(owner);
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit, DAT_UnitsState::ptr)(
                    DAT_CurrentUnitSlotID::instance, DAT_BuildingsState::instance.DAT_TempXOffset,
                    DAT_BuildingsState::instance.DAT_TempYOffset, 0);
                return;
            }
            if ((char)DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                    .engineerManningSiegeStateRef_checkType
                <= 0) {
                return;
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].isDisappearingUnk == 0) {
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].logicalState
                = OpenSHC::Map::Units::ULS_TRANSITIONING;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].disappearFadeAlphaCountdown = 32;
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_DISAPPEAR) {
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].disappearFadeAlphaCountdown += 1;
            if ((char)DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].disappearFadeAlphaCountdown
                > 32) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].disappearFadeAlphaCountdown = 32;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].updateTickTracker += 1;
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].updateTickTracker <= 32) {
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].logicalState
                = OpenSHC::Map::Units::ULS_REMOVE;
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_DEATH_01) {
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].facingDirection = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSpeed = 2;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.ANIM_Frames_UnitDeath
                      [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame <= 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber = 0x1a0;
                DAT_UnitHasBecomeIdle::instance = 1;
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame + 0x188;
            }
            if (DAT_UnitHasBecomeIdle::instance != 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = OpenSHC::Map::Units::States::US_DISAPPEAR;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].updateTickTracker = 0;
            }
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_DEATH_03) {
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].facingDirection = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSpeed = 2;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.ANIM_Frames_UnitDeath
                      [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame <= 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber = 0x1b8;
                DAT_UnitHasBecomeIdle::instance = 1;
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame + 0x1a0;
            }
            if (DAT_UnitHasBecomeIdle::instance != 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = OpenSHC::Map::Units::States::US_DISAPPEAR;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].updateTickTracker = 0;
            }
            return;
        }
        if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::checkIfCitizenUnitIsAliveBasedOnState,
                DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance)
            != FALSE) {
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].facingDirection = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSpeed = 2;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.ANIM_Frames_UnitDeath
                      [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame <= 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber = 0x1d0;
                DAT_UnitHasBecomeIdle::instance = 1;
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame + 0x1b8;
            }
            if (DAT_UnitHasBecomeIdle::instance != 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = OpenSHC::Map::Units::States::US_DISAPPEAR;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].updateTickTracker = 0;
            }
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_LOOK_AROUNDUnk) {
            // walking to a free place at the campfire
            DAT_BuildingsState::instance.buildings[campfire].field196_0x272 += 1;
            DAT_GameState::instance.playerDataArray[owner].idlePeasantsCount += 1;
            DAT_GameState::instance.playerDataArray[owner].availablePeasantsAtFire += 1;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSheetFrameOffset = 1;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0x10;
            if (MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::moveUnitAroundCampfire, DAT_GameState::ptr)(
                    DAT_CurrentUnitSlotID::instance,
                    DAT_GameState::instance.playerDataArray[owner].availablePeasantsOrHousedPeasants)
                == -1) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].logicalState
                    = OpenSHC::Map::Units::ULS_REMOVE;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::getDestination2EqualsGivenCoordinates,
                    DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance,
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetX_2,
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetY_2)
                != FALSE) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].idInTribe
                    = (short)DAT_GameState::instance.playerDataArray[owner].availablePeasantsOrHousedPeasants;
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit, DAT_UnitsState::ptr)(
                    DAT_CurrentUnitSlotID::instance,
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetX_2,
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetY_2, 0);
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::hasUnitReachedDestination, DAT_UnitsState::ptr)(
                    DAT_CurrentUnitSlotID::instance)
                == FALSE) {
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                = OpenSHC::Map::Units::States::US_STAND_UPUnk;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate = -1;
            return;
        }
        if (state != OpenSHC::Map::Units::States::US_STAND_UPUnk) {
            return;
        }
        // idling at the campfire
        DAT_GameState::instance.playerDataArray[owner].idlePeasantsCount += 1;
        DAT_GameState::instance.playerDataArray[owner].availablePeasantsAtFire += 1;
        DAT_BuildingsState::instance.buildings[campfire].field195_0x270 += 1;
        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].facingDirection
            = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field38_0x56;
        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSpeed = 2;
        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
        if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate == -1) {
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate = 0x66;
        }
        if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate == 0x66) {
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].seated = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.field233_0x451c
                      [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame <= 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                            .facingDirectionMapOrientationCorrected
                        / 2
                    + 0x81;
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                            .facingDirectionMapOrientationCorrected
                        / 2
                    + 0x7d + DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame * 4;
                if (DAT_UnitHasBecomeIdle::instance == 0) {
                    return;
                }
            }
        } else if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate == 0x67) {
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].seated = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.field234_0x45ac
                      [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame <= 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                            .facingDirectionMapOrientationCorrected
                        / 2
                    + 0x81;
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                            .facingDirectionMapOrientationCorrected
                        / 2
                    + 0x7d + DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame * 4;
                if (DAT_UnitHasBecomeIdle::instance == 0) {
                    return;
                }
            }
        } else if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate == 0x65) {
            // sitting down
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.field235_0x4610
                      [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame <= 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                            .facingDirectionMapOrientationCorrected
                        / 2
                    + 0xad;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].seated = 1;
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                            .facingDirectionMapOrientationCorrected
                        / 2
                    + 0x7d + DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame * 4;
                if (DAT_UnitHasBecomeIdle::instance == 0) {
                    return;
                }
            }
        } else if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate == 100) {
            // standing up
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.field236_0x4638
                      [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame <= 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                            .facingDirectionMapOrientationCorrected
                        / 2
                    + 0x81;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].seated = 0;
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                            .facingDirectionMapOrientationCorrected
                        / 2
                    + 0x7d + DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame * 4;
                if (DAT_UnitHasBecomeIdle::instance == 0) {
                    return;
                }
            }
        } else if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate == 0x6a) {
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].seated = 1;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.field237_0x466c
                      [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame <= 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                            .facingDirectionMapOrientationCorrected
                        / 2
                    + 0xad;
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                            .facingDirectionMapOrientationCorrected
                        / 2
                    + 0x7d + DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame * 4;
                if (DAT_UnitHasBecomeIdle::instance == 0) {
                    return;
                }
            }
        } else if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate == 0x6b) {
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].seated = 1;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.field238_0x46c4
                      [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame <= 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                            .facingDirectionMapOrientationCorrected
                        / 2
                    + 0xad;
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                            .facingDirectionMapOrientationCorrected
                        / 2
                    + 0x7d + DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame * 4;
                if (DAT_UnitHasBecomeIdle::instance == 0) {
                    return;
                }
            }
        } else if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate == 0x6e) {
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].seated = 1;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.field239_0x4724
                      [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame <= 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                            .facingDirectionMapOrientationCorrected
                        / 2
                    + 0xad;
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                            .facingDirectionMapOrientationCorrected
                        / 2
                    + 0x7d + DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame * 4;
                if (DAT_UnitHasBecomeIdle::instance == 0) {
                    return;
                }
            }
        } else if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate == 0x6f) {
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].seated = 1;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.field240_0x4794
                      [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame <= 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                            .facingDirectionMapOrientationCorrected
                        / 2
                    + 0xad;
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                            .facingDirectionMapOrientationCorrected
                        / 2
                    + 0x7d + DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame * 4;
                if (DAT_UnitHasBecomeIdle::instance == 0) {
                    return;
                }
            }
        } else if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate == 0x72) {
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].seated = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.field241_0x4804
                      [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame <= 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                            .facingDirectionMapOrientationCorrected
                        / 2
                    + 0xb5;
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                            .facingDirectionMapOrientationCorrected
                        / 2
                    + 0xb1 + DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame * 4;
                if (DAT_UnitHasBecomeIdle::instance == 0) {
                    return;
                }
            }
        } else if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate == 0x73) {
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].seated = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.field242_0x485c
                      [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame <= 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                            .facingDirectionMapOrientationCorrected
                        / 2
                    + 0xb5;
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                            .facingDirectionMapOrientationCorrected
                        / 2
                    + 0xb1 + DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame * 4;
                if (DAT_UnitHasBecomeIdle::instance == 0) {
                    return;
                }
            }
        } else if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate == 0x74) {
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].seated = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.field243_0x489c
                      [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame <= 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                            .facingDirectionMapOrientationCorrected
                        / 2
                    + 0xb5;
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                            .facingDirectionMapOrientationCorrected
                        / 2
                    + 0xb1 + DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame * 4;
                if (DAT_UnitHasBecomeIdle::instance == 0) {
                    return;
                }
            }
        } else if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate == 0x75) {
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].seated = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.field244_0x4904
                      [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame <= 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                            .facingDirectionMapOrientationCorrected
                        / 2
                    + 0xb5;
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                            .facingDirectionMapOrientationCorrected
                        / 2
                    + 0xb1 + DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame * 4;
                if (DAT_UnitHasBecomeIdle::instance == 0) {
                    return;
                }
            }
        } else if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate == 0x76) {
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].seated = 0;
            int direction
                = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].facingDirectionMapOrientationCorrected
                / 2;
            if ((DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].fixedRng & 1) != 0) {
                direction += 1;
            }
            if (direction > 3) {
                direction = 0;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.field245_0x498c
                      [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame <= 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber = direction + 0x141;
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber = direction + 0x13d
                    + DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame * 4;
                if (DAT_UnitHasBecomeIdle::instance == 0) {
                    return;
                }
            }
        } else if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate == 0x77) {
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].seated = 0;
            int direction
                = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].facingDirectionMapOrientationCorrected
                / 2;
            int nextDirection = direction + 1;
            if (nextDirection > 3) {
                nextDirection = 0;
            }
            if ((DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].fixedRng & 1) == 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber = nextDirection + 0x155;
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber = direction + 0x155;
            }
            if (DAT_UnitHasBecomeIdle::instance == 0) {
                return;
            }
        } else if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate == 0x78) {
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].seated = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.field246_0x49c4
                      [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame <= 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                            .facingDirectionMapOrientationCorrected
                        / 2
                    + 0xf1;
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                            .facingDirectionMapOrientationCorrected
                        / 2
                    + 0xed + DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame * 4;
                if (DAT_UnitHasBecomeIdle::instance == 0) {
                    return;
                }
            }
        } else if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber < 17) {
            if (DAT_UnitHasBecomeIdle::instance == 0) {
                return;
            }
        }
        // the animation has finished: choose the next one
        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
        DAT_UnitHasBecomeIdle::instance = 0;
        if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].workplaceBuildingUID
            != DAT_BuildingsState::instance.buildings[campfire].uid) {
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
        }
        if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].idInTribe
            != DAT_GameState::instance.playerDataArray[owner].availablePeasantsOrHousedPeasants) {
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
        }
        if (DAT_BuildingsState::instance.buildings[campfire].field197_0x274 == 1) {
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate = 0x66;
        } else if (DAT_BuildingsState::instance.buildings[campfire].field197_0x274 == 2) {
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].seated == 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate == 0x66 ? 0x67 : 0x66;
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate = 100;
            }
        } else if (DAT_BuildingsState::instance.buildings[campfire].field197_0x274 == 4) {
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate
                = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].seated != 0 ? 100 : 0x78;
        } else if (DAT_BuildingsState::instance.buildings[campfire].field197_0x274 == 3) {
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].seated == 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate = 0x65;
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate == 0x6a ? 0x6b : 0x6a;
            }
        } else if (DAT_BuildingsState::instance.buildings[campfire].field197_0x274 == 5
            || DAT_BuildingsState::instance.buildings[campfire].field197_0x274 == 6) {
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].peasantAlwaysZero == 0) {
                if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].seated == 0) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate = 0x65;
                } else if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate == 0x6a) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate = 0x6e;
                } else {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate
                        = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate != 0x6e ? 0x6a
                                                                                                           : 0x6f;
                }
            } else if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].seated != 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate = 100;
            } else if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate == 0x72) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate = 0x73;
            } else if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate == 0x73) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate = 0x74;
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate != 0x74 ? 0x72 : 0x75;
            }
        }
        if (DAT_TileMapState::instance
                .PathConnectionLayer[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].tile]
            != 0) {
            return;
        }
        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
            = OpenSHC::Map::Units::States::US_DISAPPEAR;
        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].disappearFadeAlphaCountdown = 0;
        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].updateTickTracker = 0;
    }

}
}
