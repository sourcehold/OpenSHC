#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Units.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Synchrony/Actions.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/DE/SHCDE/eSFX.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Map/Entities/EntityType.hpp"
#include "OpenSHC/Map/Units/Pathfinding/DestinationNeededEnum.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitInstructionType.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentUnitSlotID.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitPropertiesDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::DE::SHCDE::eSFX;
    using OpenSHC::Game::GameMode;
    using OpenSHC::Map::Entities::EntityType;
    using OpenSHC::Map::Units::UnitInstructionType;
    using OpenSHC::Map::Units::UnitLogicState;
    using OpenSHC::Map::Units::UnitType;
    using OpenSHC::Map::Units::Pathfinding::DestinationNeededEnum;
    using OpenSHC::Map::Units::States::UnitState;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      digTileX reused as number of engineers currently manning the siege engine
     */

    // FUNCTION: STRONGHOLDCRUSADER 0x00568320
    void Units::UpdateCatapult()
    {
        int unitID = DAT_CurrentUnitSlotID::instance;
        int owner = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].owner;
        DAT_GameState::instance.playerDataArray[owner].armySize += 1;
        DAT_GameState::instance.playerDataArray[owner].currentSiegeWeaponCount += 1;
        DAT_UnitsState::instance.units[unitID].isSelectable_OR_matchTime = 1;
        DAT_UnitsState::instance.units[unitID].calculatedOwnerPlayerIndex = owner;
        UnitStateShort state = DAT_UnitsState::instance.units[unitID].state.generic;
        if (state == OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk) {
            DAT_UnitsState::instance.units[unitID].substate = -1;
            DAT_UnitsState::instance.units[unitID].stateBasedSpeed = 0;
            DAT_UnitsState::instance.units[unitID].gfxNumber
                = DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected + 1;
            DAT_UnitsState::instance.units[unitID].imageIDUnk
                = DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected + 0xe1;
            if (DAT_UnitsState::instance.units[unitID]
                    .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300
                != 2) {
                // not fully manned
                DAT_UnitsState::instance.units[unitID].state.generic = OpenSHC::Map::Units::States::US_FIRE_WEAPONUnk;
                return;
            }
            if (DAT_UnitsState::instance.units[unitID].field248_0x3bc < 0) {
                DAT_UnitsState::instance.units[unitID].field248_0x3bc += 1;
                DAT_UnitsState::instance.units[unitID].state.generic
                    = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
                return;
            }
            if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[DAT_UnitsState::instance.units[unitID].owner]
                == -1) {
                if (MACRO_CALL_MEMBER(
                        OpenSHC::Map::Units::UnitsState_Func::harassBuildingsWithSiegeAI, DAT_UnitsState::ptr)(unitID)
                    != 0) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic = (UnitState)2;
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
                    return;
                }
            } else {
                if (DAT_UnitsState::instance.units[unitID].field253_0x3c5 == 5
                    || DAT_UnitsState::instance.units[unitID].field253_0x3c5 == 0x16) {
                    DAT_UnitsState::instance.units[unitID].targetingType
                        = (char)DAT_UnitsState::instance.units[unitID].field253_0x3c5;
                    DAT_UnitsState::instance.units[unitID].field253_0x3c5 = 0;
                }
                if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::acquireShootTarget, DAT_UnitsState::ptr)(
                        unitID)
                    != FALSE) {
                    if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::checkTargetBuildingPossibilityOrState,
                            DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance)
                        != FALSE) {
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].shootBeforeStop = 10;
                    } else if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].shootBeforeStop > 0) {
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].shootBeforeStop -= 1;
                    } else if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].shootBeforeStop == 0) {
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field248_0x3bc = -80;
                        return;
                    }
                    if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                        == OpenSHC::Map::Units::States::US_MOVE_TO_DESTINATION) {
                        return;
                    }
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                        = OpenSHC::Map::Units::States::US_STAND_UPUnk;
                    return;
                }
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field248_0x3bc = -40;
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_FIRE_WEAPONUnk) {
            // waiting for engineers to man the catapult
            DAT_UnitsState::instance.units[unitID].field39_0x58 = 0;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[unitID].gfxNumber
                = DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected + 1;
            DAT_UnitsState::instance.units[unitID].imageIDUnk = 0;
            DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
            if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[DAT_UnitsState::instance.units[unitID].owner]
                    == -1
                && DAT_UnitsState::instance.units[unitID]
                        .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300
                    == 2) {
                // the AI's engineers have been moved away: check whether both are back
                int present = 0;
                for (int i = 0; i < 2; ++i) {
                    int engineer = DAT_UnitsState::instance.units[unitID].manningEngineerRef[i];
                    if (DAT_UnitsState::instance.units[unitID].manningEngineerUIDRef[i]
                            != DAT_UnitsState::instance.units[engineer].uid
                        || MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::hasUnitReachedDestination,
                               DAT_UnitsState::ptr)(engineer)
                            == FALSE
                        || abs(DAT_UnitsState::instance.units[engineer].buildingHeight
                               - DAT_UnitsState::instance.units[unitID].buildingHeight
                               - DAT_UnitsState::instance.units[unitID].terrainOrClimbHeight
                               + DAT_UnitsState::instance.units[engineer].terrainOrClimbHeight)
                            > 16) {
                        break;
                    }
                    int dx = DAT_UnitsState::instance.units[unitID].microXPosition
                            < DAT_UnitsState::instance.units[engineer].microXPosition
                        ? DAT_UnitsState::instance.units[engineer].microXPosition
                            - DAT_UnitsState::instance.units[unitID].microXPosition
                        : DAT_UnitsState::instance.units[unitID].microXPosition
                            - DAT_UnitsState::instance.units[engineer].microXPosition;
                    int dy = DAT_UnitsState::instance.units[unitID].microYPosition
                            < DAT_UnitsState::instance.units[engineer].microYPosition
                        ? DAT_UnitsState::instance.units[engineer].microYPosition
                            - DAT_UnitsState::instance.units[unitID].microYPosition
                        : DAT_UnitsState::instance.units[unitID].microYPosition
                            - DAT_UnitsState::instance.units[engineer].microYPosition;
                    if ((dy < dx ? dx : dy) < 30) {
                        present += 1;
                    }
                }
                if (present == 2) {
                    int first = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].manningEngineerRef[0];
                    DAT_UnitsState::instance.units[first].animationCycleNumber = 0;
                    DAT_UnitsState::instance.units[first].disappearFadeAlphaCountdown = 0;
                    DAT_UnitsState::instance.units[first].engineerManningSiegeStateRef_checkType = 2;
                    DAT_UnitsState::instance.units[first].updateTickTracker = 0;
                    DAT_UnitsState::instance.units[first].state.generic
                        = OpenSHC::Map::Units::States::US_JESTER_ROAM_TO;
                    DAT_UnitsState::instance.units[first].cachedState = OpenSHC::Map::Units::States::US_AIM_WEAPONUnk;
                    int second = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].manningEngineerRef[1];
                    DAT_UnitsState::instance.units[second].animationCycleNumber = 0;
                    DAT_UnitsState::instance.units[second].state.generic
                        = OpenSHC::Map::Units::States::US_JESTER_ROAM_TO;
                    DAT_UnitsState::instance.units[second].disappearFadeAlphaCountdown = 0;
                    DAT_UnitsState::instance.units[second].engineerManningSiegeStateRef_checkType = 2;
                    DAT_UnitsState::instance.units[second].cachedState = OpenSHC::Map::Units::States::US_AIM_WEAPONUnk;
                    DAT_UnitsState::instance.units[second].updateTickTracker = 0;
                    DAT_UnitsState::instance.units[unitID].state.generic
                        = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
                }
            }
            if (((DAT_UnitsState::instance.units[unitID].fixedRng
                     ^ DAT_GameState::instance.mapAndTime.totalGameTicksUnk)
                    & 15)
                != 8) {
                return;
            }
            if (DAT_UnitsState::instance.units[unitID].state.generic
                != OpenSHC::Map::Units::States::US_FIRE_WEAPONUnk) {
                return;
            }
            // look for two engineers of the same player next to the catapult
            int crewCount[9] = { 0 };
            int crew[9][2];
            for (int i = 1; i < (int)DAT_UnitsState::instance.maxUnitCount; ++i) {
                if (DAT_UnitsState::instance.units[i].logicalState != OpenSHC::Map::Units::ULS_NORMAL
                    || DAT_UnitsState::instance.units[i].dying != 0
                    || DAT_UnitsState::instance.units[i].unitType != OpenSHC::Map::Units::UT_E_ENGINEER) {
                    continue;
                }
                if ((DAT_GameSynchronyState::instance
                                .currentPlayerFullIDArray[DAT_UnitsState::instance.units[unitID].owner]
                            != -1
                        || DAT_UnitsState::instance.units[i].aiUnitBehaviourType != 0x16)
                    && (DAT_UnitsState::instance.units[i].targetingType != OpenSHC::Map::Units::UIT_MAN_SIEGE_EQUIPMENT
                        || DAT_UnitsState::instance.units[i].targetedUnitID__OR__engineerMannedSiegeEngineRef
                            != DAT_CurrentUnitSlotID::instance)) {
                    continue;
                }
                if (abs(DAT_UnitsState::instance.units[i].terrainOrClimbHeight
                        - DAT_UnitsState::instance.units[unitID].buildingHeight
                        - DAT_UnitsState::instance.units[unitID].terrainOrClimbHeight
                        + DAT_UnitsState::instance.units[i].buildingHeight)
                    > 16) {
                    continue;
                }
                int dx = DAT_UnitsState::instance.units[unitID].microXPosition
                        < DAT_UnitsState::instance.units[i].microXPosition
                    ? DAT_UnitsState::instance.units[i].microXPosition
                        - DAT_UnitsState::instance.units[unitID].microXPosition
                    : DAT_UnitsState::instance.units[unitID].microXPosition
                        - DAT_UnitsState::instance.units[i].microXPosition;
                int dy = DAT_UnitsState::instance.units[unitID].microYPosition
                        < DAT_UnitsState::instance.units[i].microYPosition
                    ? DAT_UnitsState::instance.units[i].microYPosition
                        - DAT_UnitsState::instance.units[unitID].microYPosition
                    : DAT_UnitsState::instance.units[unitID].microYPosition
                        - DAT_UnitsState::instance.units[i].microYPosition;
                if ((dy < dx ? dx : dy) < 30 && crewCount[DAT_UnitsState::instance.units[i].owner] < 2) {
                    crew[DAT_UnitsState::instance.units[i].owner][crewCount[DAT_UnitsState::instance.units[i].owner]]
                        = i;
                    crewCount[DAT_UnitsState::instance.units[i].owner] += 1;
                }
            }
            int crewOwner = DAT_UnitsState::instance.units[unitID].owner;
            if (crewCount[crewOwner] != 2) {
                // the catapult is captured by the engineers of another player
                crewOwner = 1;
                while (crewCount[crewOwner] != 2) {
                    crewOwner += 1;
                    if (crewOwner >= 9) {
                        return;
                    }
                }
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::deselectUnit, DAT_UnitsState::ptr)(
                    DAT_CurrentUnitSlotID::instance);
                MACRO_CALL_MEMBER(
                    OpenSHC::Map::Units::UnitsState_Func::clearOrDeselectUnitFromSelection, DAT_UnitsState::ptr)(
                    DAT_UnitsState::instance.units[unitID].owner, DAT_CurrentUnitSlotID::instance, 0);
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].owner = (short)crewOwner;
                if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].calculatedOwnerPlayerIndex != 0) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].calculatedOwnerPlayerIndex
                        = crewOwner;
                }
                if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].displayColorPlayerID != 0) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].displayColorPlayerID
                        = (short)crewOwner;
                }
                int tribe = MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::createTribe, DAT_TribesState::ptr)(
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].owner, 0);
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::addUnitToTribe, DAT_TribesState::ptr)(
                    tribe, DAT_CurrentUnitSlotID::instance);
            }
            for (int i = 0; i < 2; ++i) {
                int engineer = crew[crewOwner][i];
                DAT_UnitsState::instance.units[engineer].animationCycleNumber = 0;
                DAT_UnitsState::instance.units[engineer].disappearFadeAlphaCountdown = 0;
                DAT_UnitsState::instance.units[engineer].updateTickTracker = 0;
                DAT_UnitsState::instance.units[engineer].state.generic = OpenSHC::Map::Units::States::US_JESTER_ROAM_TO;
                DAT_UnitsState::instance.units[engineer].engineerManningSiegeStateRef_checkType = 2;
                DAT_UnitsState::instance.units[engineer].cachedState = OpenSHC::Map::Units::States::US_AIM_WEAPONUnk;
                DAT_UnitsState::instance.units[engineer].targetingType
                    = OpenSHC::Map::Units::UIT_NO_INSTRUCTION_OR_MOVEUnk;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].manningEngineerRef[i] = (short)engineer;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].manningEngineerUIDRef[i]
                    = DAT_UnitsState::instance.units[engineer].uid;
                if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray
                            [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].owner]
                        == -1
                    && DAT_UnitsState::instance.units[engineer].aiUnitBehaviourType == 0x16) {
                    MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::removeUnitFromTribe, DAT_TribesState::ptr)(
                        engineer, DAT_UnitsState::instance.units[engineer].tribeID);
                }
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::deselectUnit, DAT_UnitsState::ptr)(engineer);
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::clearOrDeselectUnitFromSelection,
                    DAT_UnitsState::ptr)(DAT_UnitsState::instance.units[engineer].owner, engineer, 0);
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300 = 2;
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_MOVE_TO_DESTINATION
            || state == OpenSHC::Map::Units::States::US_IDLEUnk) {
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0x15;
            if (DAT_UnitsState::instance.units[unitID].moveInstructionSpeedDelayTracker == 0) {
                DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset = 0x1c1;
                if (DAT_UnitsState::instance.units[unitID].isMatchingSpeed != false) {
                    DAT_UnitsState::instance.units[unitID].stateBasedSpeed = 0;
                } else {
                    DAT_UnitsState::instance.units[unitID].stateBasedSpeed = 1;
                }
            } else {
                DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset = 0x1c1;
                if (DAT_UnitsState::instance.units[unitID].moveInstructionSpeedDelayTracker < 70) {
                    DAT_UnitsState::instance.units[unitID].stateBasedSpeed = 0;
                } else {
                    DAT_UnitsState::instance.units[unitID].stateBasedSpeed = -1;
                    DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
                }
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::hasUnitReachedDestination, DAT_UnitsState::ptr)(
                    unitID)
                == FALSE) {
                return;
            }
            DAT_UnitsState::instance.units[unitID].stateBasedSpeed = 0;
            DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
            DAT_UnitsState::instance.units[unitID].state.generic
                = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
            DAT_UnitsState::instance.units[unitID].field248_0x3bc = 0;
            return;
        }
        if (state == (UnitState)9) {
            // moving towards the enemy
            // TODO: the byte tile layers at 0x01EE2998 are not modelled yet
            if (*(unsigned char*)(DAT_UnitsState::instance.units[unitID].siegeTargetPlayerID * 0x13a10 + 0x1ee2998
                    + DAT_UnitsState::instance.units[unitID].tile)
                <= 15) {
                DAT_UnitsState::instance.units[unitID].destinationNeeded
                    = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET;
            }
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0x15;
            DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset = 0x1c1;
            DAT_UnitsState::instance.units[unitID].stateBasedSpeed = 0;
            if (DAT_UnitsState::instance.units[unitID].unknownSiegeTentRelated02 != 3) {
                DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
                DAT_UnitsState::instance.units[unitID].state.generic
                    = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
                DAT_UnitsState::instance.units[unitID].field248_0x3bc = 0;
                return;
            }
            if (DAT_UnitsState::instance.units[unitID].destinationNeeded
                != OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET) {
                int tile = MACRO_CALL_MEMBER(
                    OpenSHC::Map::Navigation::PathFindingState_Func::pathFindingRelated, DAT_PathFindingState::ptr)(5,
                    DAT_UnitsState::instance.units[unitID].x, DAT_UnitsState::instance.units[unitID].y,
                    DAT_UnitsState::instance.units[unitID].siegeTargetPlayerID);
                if (DAT_PathFindingState::instance.field51_0x9c < 3) {
                    tile = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::pathFindingRelated,
                        DAT_PathFindingState::ptr)(10,
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].x,
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].y,
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].siegeTargetPlayerID);
                }
                if (DAT_PathFindingState::instance.field51_0x9c < 3) {
                    tile = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::pathFindingRelated,
                        DAT_PathFindingState::ptr)(20,
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].x,
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].y,
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].siegeTargetPlayerID);
                }
                if (DAT_PathFindingState::instance.field51_0x9c < 3) {
                    tile = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::pathFindingRelated,
                        DAT_PathFindingState::ptr)(60,
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].x,
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].y,
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].siegeTargetPlayerID);
                }
                if (DAT_PathFindingState::instance.field51_0x9c < 3) {
                    tile = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::pathFindingRelated,
                        DAT_PathFindingState::ptr)(120,
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].x,
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].y,
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].siegeTargetPlayerID);
                }
                if (tile > 0) {
                    MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit, DAT_UnitsState::ptr)(
                        DAT_CurrentUnitSlotID::instance,
                        tile
                            - DAT_ViewportRenderState::instance
                                .translationMatrix[DAT_ViewportRenderState::instance
                                        .tileTranslationMatrix_YComponent[tile]]
                                .addXgetTile,
                        DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile], 0);
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].attackFacingDirection = 0;
                }
                DAT_UnitsState::instance.units[unitID].destinationNeeded
                    = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::hasUnitReachedDestination, DAT_UnitsState::ptr)(
                    unitID)
                == FALSE) {
                return;
            }
            DAT_UnitsState::instance.units[unitID].stateBasedSpeed = 0;
            DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
            DAT_UnitsState::instance.units[unitID].state.generic
                = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
            DAT_UnitsState::instance.units[unitID].field248_0x3bc = 0;
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::moveToFreeTileNearby, DAT_UnitsState::ptr)(unitID);
            return;
        }
        if (state == (UnitState)0x6c) {
            DAT_UnitsState::instance.units[unitID].stateBasedSpeed = 0;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset = 1;
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_STAND_UPUnk) {
            // aiming
            DAT_UnitsState::instance.units[unitID].animationSpeed = 5;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[unitID].field39_0x58 = 0;
            DAT_UnitsState::instance.units[unitID].gfxNumber
                = DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected + 1;
            DAT_UnitsState::instance.units[unitID].imageIDUnk
                = DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected + 0xe1;
            if (DAT_UnitsState::instance.units[unitID].animationCycleNumberHasJustIncremented == FALSE) {
                return;
            }
            int targetX = DAT_UnitsState::instance.units[unitID].attackAtTileX;
            int targetY = DAT_UnitsState::instance.units[unitID].attackAtTileY;
            if (DAT_UnitsState::instance.units[unitID].targetingType == OpenSHC::Map::Units::UIT_ATTACK_BUILDING
                && DAT_BuildingsState::instance
                        .buildings[DAT_UnitsState::instance.units[unitID].targetID_OR_targetBuildingID]
                        .uid
                    == DAT_UnitsState::instance.units[unitID]
                        .targetedUnitUIDUnk_OR_someAppearTileUnk_OR_buildingUID_OR_pitchDitchUID_OR_entityUID) {
                int halfSize = DAT_BuildingsState::instance
                                   .buildings[DAT_UnitsState::instance.units[unitID].targetID_OR_targetBuildingID]
                                   .widthOrHeight
                    / 2;
                targetX = DAT_BuildingsState::instance
                              .buildings[DAT_UnitsState::instance.units[unitID].targetID_OR_targetBuildingID]
                              .x
                    + halfSize;
                targetY = DAT_BuildingsState::instance
                              .buildings[DAT_UnitsState::instance.units[unitID].targetID_OR_targetBuildingID]
                              .y
                    + halfSize;
            }
            int dy = targetY - DAT_UnitsState::instance.units[unitID].y;
            int dx = targetX - DAT_UnitsState::instance.units[unitID].x;
            if (dx * dx + dy * dy > 5625) {
                DAT_UnitsState::instance.units[unitID].field248_0x3bc = -40;
                DAT_UnitsState::instance.units[unitID].state.generic
                    = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
                return;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setUnitFacingDirectionForTargetXandY,
                    DAT_UnitsState::ptr)(unitID, targetX, targetY)
                != FALSE) {
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic = (UnitState)2;
            return;
        }
        if (state == (UnitState)2) {
            // loading
            DAT_UnitsState::instance.units[unitID].animationSpeed = 5;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[unitID].field39_0x58 = 0;
            if (DAT_UnitsState::instance.units[unitID].animationCycleNumberHasJustIncremented != FALSE
                && DAT_UnitsState::instance.units[unitID].animationCycleNumber == 1) {
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    DAT_UnitsState::instance.units[unitID].x, DAT_UnitsState::instance.units[unitID].y,
                    OpenSHC::DE::SHCDE::FX_CA_LOAD);
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetingType
                == OpenSHC::Map::Units::UIT_THROW_COW) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setUnitFacingDirectionForTargetXandY,
                    DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance,
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].attackAtTileX,
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].attackAtTileY);
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.field73_0x1784
                      [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame <= 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = OpenSHC::Map::Units::States::US_RELOAD_WEAPONUnk;
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].facingDirectionMapOrientationCorrected
                - 7 + DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame * 8;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].imageIDUnk
                = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].facingDirectionMapOrientationCorrected
                - 7
                + (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.field74_0x17ac
                        [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber]
                    * 8;
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_RELOAD_WEAPONUnk) {
            // firing
            DAT_UnitsState::instance.units[unitID].animationSpeed = 2;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            if (DAT_UnitsState::instance.units[unitID].targetingType == OpenSHC::Map::Units::UIT_THROW_COW) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setUnitFacingDirectionForTargetXandY,
                    DAT_UnitsState::ptr)(unitID, DAT_UnitsState::instance.units[unitID].attackAtTileX,
                    DAT_UnitsState::instance.units[unitID].attackAtTileY);
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumberHasJustIncremented
                    != FALSE
                && DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber == 2) {
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].x,
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].y, OpenSHC::DE::SHCDE::FX_CA_FIRE);
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.field75_0x17d4
                      [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame > 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                          .facingDirectionMapOrientationCorrected
                    - 7 + DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame * 8;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].imageIDUnk
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                          .facingDirectionMapOrientationCorrected
                    - 7
                    + (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.field76_0x17fc
                            [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber]
                        * 8;
            }
            if (DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.field75_0x17d4
                        [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber]
                    == 23
                && DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                        .animationCycleNumberHasJustIncremented
                    != FALSE) {
                if (DAT_GameSynchronyState::instance
                        .currentPlayerFullIDArray[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].owner]
                    == -1) {
                    if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY) {
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field243_0x3b0 = 0;
                        if (MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::yieldCowThrow, DAT_AICState::ptr)(
                                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].owner)
                            != FALSE) {
                            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field243_0x3b0 = 1;
                        }
                    }
                } else {
                    MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::prepareProjectileTarget,
                        DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance, -1, 200);
                }
                if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetingType
                        != OpenSHC::Map::Units::UIT_THROW_COW
                    && DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field243_0x3b0 == 0) {
                    if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stoneAmmunition > 0) {
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stoneAmmunition -= 1;
                        MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::shootProjectile, DAT_UnitsState::ptr)(
                            DAT_CurrentUnitSlotID::instance, OpenSHC::Map::Entities::ET_CATAPULT,
                            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].shootTargetMicroX,
                            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].shootTargetMicroY,
                            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].shootTargetZ);
                    } else if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY
                        && MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::isAIPlayer,
                               DAT_GameSynchronyState::ptr)(owner)
                            != FALSE) {
                        MACRO_CALL(OpenSHC::Synchrony::Actions_Func::TryAcquireAmmunitionOrPlanToBuyStone)(
                            owner, DAT_CurrentUnitSlotID::instance);
                    }
                } else {
                    // throwing a diseased cow
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field243_0x3b0 = 1;
                    if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray
                            [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].owner]
                        != -1) {
                        if (DAT_GameState::instance.playerDataArray[owner].counter <= 0) {
                            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field243_0x3b0 = 0;
                        } else {
                            int cow = MACRO_CALL_MEMBER(
                                OpenSHC::Map::Units::UnitsState_Func::findNearestIdleCowForPlayer, DAT_UnitsState::ptr)(
                                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].owner,
                                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].x,
                                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].y);
                            if (cow != 0) {
                                DAT_UnitsState::instance.units[cow].logicalState = OpenSHC::Map::Units::ULS_REMOVE;
                            }
                            DAT_GameState::instance.playerDataArray[owner].counter -= 1;
                        }
                    }
                    if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field243_0x3b0 != 0) {
                        MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::shootProjectile, DAT_UnitsState::ptr)(
                            DAT_CurrentUnitSlotID::instance, OpenSHC::Map::Entities::ET_CATAPULT,
                            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].shootTargetMicroX,
                            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].shootTargetMicroY,
                            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].shootTargetZ);
                    } else if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stoneAmmunition > 0) {
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stoneAmmunition -= 1;
                        MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::shootProjectile, DAT_UnitsState::ptr)(
                            DAT_CurrentUnitSlotID::instance, OpenSHC::Map::Entities::ET_CATAPULT,
                            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].shootTargetMicroX,
                            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].shootTargetMicroY,
                            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].shootTargetZ);
                    } else if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY
                        && MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::isAIPlayer,
                               DAT_GameSynchronyState::ptr)(owner)
                            != FALSE) {
                        MACRO_CALL(OpenSHC::Synchrony::Actions_Func::TryAcquireAmmunitionOrPlanToBuyStone)(
                            owner, DAT_CurrentUnitSlotID::instance);
                        MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::shootProjectile, DAT_UnitsState::ptr)(
                            DAT_CurrentUnitSlotID::instance, OpenSHC::Map::Entities::ET_CATAPULT,
                            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].shootTargetMicroX,
                            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].shootTargetMicroY,
                            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].shootTargetZ);
                    }
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field243_0x3b0 = 0;
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field253_0x3c5 = 3;
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetingType
                        = OpenSHC::Map::Units::UIT_NO_INSTRUCTION_OR_MOVEUnk;
                }
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame == 0
                && DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                        .animationCycleNumberHasJustIncremented
                    != FALSE) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
            } else {
                if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame > 0) {
                    return;
                }
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
            }
            // AI catapults hitting their own troops move somewhere else
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field98_0xd2 < 6
                && DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].friendlyFireCounterUnk <= 4) {
                return;
            }
            if (DAT_GameSynchronyState::instance
                    .currentPlayerFullIDArray[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].owner]
                != -1) {
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic = (UnitState)9;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].destinationNeeded
                = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_NEEDED;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field98_0xd2 = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].friendlyFireCounterUnk = 0;
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_DEATH_01 || state == OpenSHC::Map::Units::States::US_DEATH_03
            || state == OpenSHC::Map::Units::States::US_STONE_DEATH_01) {
            DAT_UnitsState::instance.units[unitID].animationSpeed = 10000;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[unitID].gfxNumber
                = DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected + 0x2c1;
            DAT_UnitsState::instance.units[unitID].imageIDUnk = 0;
            if (DAT_UnitsState::instance.units[unitID].animationCycleNumber == 0
                && DAT_UnitsState::instance.units[unitID].killedFlagUnk == 0) {
                // the crew dies with the catapult
                for (int i = 0; i < DAT_UnitsState::instance.units[unitID]
                                    .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300;
                    ++i) {
                    if (DAT_UnitsState::instance.units[DAT_UnitsState::instance.units[unitID].manningEngineerRef[i]].uid
                        != DAT_UnitsState::instance.units[unitID].manningEngineerUIDRef[i]) {
                        continue;
                    }
                    DAT_UnitsState::instance.units[DAT_UnitsState::instance.units[unitID].manningEngineerRef[i]]
                        .logicalState = OpenSHC::Map::Units::ULS_REMOVE;
                    if (owner == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                        DAT_GameState::instance.mapAndTime
                            .ownLossesArray[DAT_UnitsState::instance.units[unitID].lastEncounteredEnemyPlayerID] += 1;
                    } else if (DAT_UnitsState::instance.units[unitID].lastEncounteredEnemyPlayerID
                        == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                        DAT_GameState::instance.mapAndTime.emenyHitArray[owner] += 1;
                    }
                }
            }
            DAT_UnitsState::instance.units[unitID].animationCycleNumber += 1;
            if (DAT_UnitsState::instance.units[unitID].animationCycleNumber <= 200) {
                return;
            }
            DAT_UnitsState::instance.units[unitID].logicalState = OpenSHC::Map::Units::ULS_REMOVE;
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_DISAPPEAR
            || state == OpenSHC::Map::Units::States::US_JESTER_ROAM_TO) {
            DAT_UnitsState::instance.units[unitID].disappearFadeAlphaCountdown += 1;
            if ((char)DAT_UnitsState::instance.units[unitID].disappearFadeAlphaCountdown > 32) {
                DAT_UnitsState::instance.units[unitID].disappearFadeAlphaCountdown = 32;
            }
            DAT_UnitsState::instance.units[unitID].updateTickTracker += 1;
            if (DAT_UnitsState::instance.units[unitID].updateTickTracker > 32) {
                DAT_UnitsState::instance.units[unitID].logicalState = OpenSHC::Map::Units::ULS_REMOVE;
            }
            if (DAT_UnitsState::instance.units[unitID].killedFlagUnk != 0) {
                return;
            }
            if (DAT_UnitsState::instance.units[unitID]
                    .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300
                != 2) {
                return;
            }
            MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::processUnitLossStatistic, DAT_GameState::ptr)(
                owner, unitID);
        }
    }

}
}
