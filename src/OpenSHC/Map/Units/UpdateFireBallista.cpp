#include "../Units.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/AI/AIUnitBehaviourType.hpp"
#include "OpenSHC/DE/SHCDE/eSFX.hpp"
#include "OpenSHC/Map/Entities/EntityType.hpp"
#include "OpenSHC/Map/Units/Pathfinding/DestinationNeededEnum.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitInstructionType.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentUnitSlotID.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitPropertiesDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x00577CC0
    void Units::UpdateFireBallista()
    {
        int const owner = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].owner;
        // counted in the waiting state only, but zeroed here, where the original zeroes it
        int present = 0;
        DAT_GameState::instance.playerDataArray[owner].armySize++;
        DAT_GameState::instance.playerDataArray[owner].currentSiegeWeaponCount++;
        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].isSelectable_OR_matchTime = 1;
        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].calculatedOwnerPlayerIndex = owner;
        UnitStateShort const state = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic;
        if (state == OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk) {
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate = -1;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                = (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                          .facingDirectionMapOrientationCorrected
                      + 4)
                    % 8
                + 1;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].imageIDUnk
                = (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                          .facingDirectionMapOrientationCorrected
                      + 4)
                    % 8
                + 169;
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                    .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300
                != 2) {
                // not fully manned
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = OpenSHC::Map::Units::States::US_FIRE_WEAPONUnk;
                return;
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x3bc < 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x3bc++;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
                return;
            }
            if (DAT_GameSynchronyState::instance
                    .currentPlayerFullIDArray[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].owner]
                == -1) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetingType
                    = OpenSHC::Map::Units::UIT_NO_INSTRUCTION_OR_MOVEUnk;
                if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].closestEnemyMicroDistance > 680
                    || !MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::acquireShootTarget,
                        DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance)) {
                    // no units in range: attack buildings
                    int const building = MACRO_CALL_MEMBER(
                        OpenSHC::Map::Buildings::BuildingsState_Func::aiFindBuildingToAttack, DAT_BuildingsState::ptr)(
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].owner,
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].x,
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].y, 52);
                    if (building != 0) {
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetingType
                            = OpenSHC::Map::Units::UIT_ATTACK_BUILDING;
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetID_OR_targetBuildingID
                            = building;
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                            .targetedUnitUIDUnk_OR_someAppearTileUnk_OR_buildingUID_OR_pitchDitchUID_OR_entityUID
                            = DAT_BuildingsState::instance.buildings[building].uid;
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].shootTargetedUnit = -1;
                    }
                    if (!MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::harassBuildingsWithSiegeAI,
                            DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance)) {
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x3bc = -60;
                        return;
                    }
                }
                if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    != OpenSHC::Map::Units::States::US_MOVE_TO_DESTINATION) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                        = OpenSHC::Map::Units::States::US_STAND_UPUnk;
                }
                return;
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].closestEnemyMicroDistance > 432
                && DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetingType
                    != OpenSHC::Map::Units::UIT_ATTACK_LAND
                && DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetingType
                    != OpenSHC::Map::Units::UIT_ATTACK_BUILDING) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x3bc = -60;
                return;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::acquireShootTarget, DAT_UnitsState::ptr)(
                    DAT_CurrentUnitSlotID::instance)) {
                if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::checkTargetBuildingPossibilityOrState,
                        DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance)) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].shootBeforeStop = 10;
                } else if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].shootBeforeStop > 0) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].shootBeforeStop--;
                } else if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].shootBeforeStop == 0) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x3bc = -80;
                    return;
                }
                if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    != OpenSHC::Map::Units::States::US_MOVE_TO_DESTINATION) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                        = OpenSHC::Map::Units::States::US_STAND_UPUnk;
                }
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x3bc = -60;
        } else if (state == OpenSHC::Map::Units::States::US_FIRE_WEAPONUnk) {
            // waiting for engineers to man the ballista
            // one index for the state's loops: with an index per loop two registers of the crew's stores differ
            int i;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x58 = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].facingDirectionMapOrientationCorrected
                + 1;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].imageIDUnk = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
            if (DAT_GameSynchronyState::instance
                        .currentPlayerFullIDArray[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].owner]
                    == -1
                && DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                        .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300
                    == 2) {
                // the AI's engineers have been moved away: check whether both are back
                for (i = 0; i < 2; ++i) {
                    int const engineer
                        = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].manningEngineerRef[i];
                    // three ifs, not one ||: with || the zero for the stores behind the loop is set behind it
                    if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].manningEngineerUIDRef[i]
                        != DAT_UnitsState::instance.units[engineer].uid) {
                        break;
                    }
                    if (!MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::hasUnitReachedDestination,
                            DAT_UnitsState::ptr)(engineer)) {
                        break;
                    }
                    if (abs(DAT_UnitsState::instance.units[engineer].terrainOrClimbHeight
                            - DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].terrainOrClimbHeight
                            - DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].buildingHeight
                            + DAT_UnitsState::instance.units[engineer].buildingHeight)
                        > 16) {
                        break;
                    }
                    short const ownX = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].microXPosition;
                    short const otherX = DAT_UnitsState::instance.units[engineer].microXPosition;
                    int dx;
                    if (otherX > ownX) {
                        dx = otherX - ownX;
                    } else {
                        dx = ownX - otherX;
                    }
                    short const ownY = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].microYPosition;
                    short const otherY = DAT_UnitsState::instance.units[engineer].microYPosition;
                    int dy;
                    if (otherY > ownY) {
                        dy = otherY - ownY;
                    } else {
                        dy = ownY - otherY;
                    }
                    int distance = dy;
                    if (dx > dy) {
                        distance = dx;
                    }
                    if (distance < 30) {
                        present++;
                    }
                }
                if (present == 2) {
                    for (i = 0; i < 2; ++i) {
                        int const engineer
                            = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].manningEngineerRef[i];
                        DAT_UnitsState::instance.units[engineer].animationCycleNumber = 0;
                        DAT_UnitsState::instance.units[engineer].state.generic
                            = OpenSHC::Map::Units::States::US_JESTER_ROAM_TO;
                        DAT_UnitsState::instance.units[engineer].disappearFadeAlphaCountdown = 0;
                        DAT_UnitsState::instance.units[engineer].engineerManningSiegeStateRef_checkType = 2;
                        DAT_UnitsState::instance.units[engineer].cachedState
                            = OpenSHC::Map::Units::States::US_AIM_WEAPONUnk;
                        DAT_UnitsState::instance.units[engineer].updateTickTracker = 0;
                    }
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                        = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
                }
            }
            if (((DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].fixedRng
                     ^ DAT_GameState::instance.mapAndTime.totalGameTicksUnk ^ 8)
                    & 15)
                    != 0
                || DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    != OpenSHC::Map::Units::States::US_FIRE_WEAPONUnk) {
                return;
            }
            // look for two engineers of the same player next to the ballista
            int crewCount[9] = { 0 };
            int crew[9][2];
            for (i = 1; i < DAT_UnitsState::instance.maxUnitCount; ++i) {
                if (DAT_UnitsState::instance.units[i].logicalState != OpenSHC::Map::Units::ULS_NORMAL
                    || DAT_UnitsState::instance.units[i].dying != 0
                    || DAT_UnitsState::instance.units[i].unitType != OpenSHC::Map::Units::UT_E_ENGINEER) {
                    continue;
                }
                if ((DAT_GameSynchronyState::instance.currentPlayerFullIDArray
                                [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].owner]
                            != -1
                        || DAT_UnitsState::instance.units[i].aiUnitBehaviourType != OpenSHC::AI::AIUBT_HARASS_SIEGE)
                    && (DAT_UnitsState::instance.units[i].targetingType != OpenSHC::Map::Units::UIT_MAN_SIEGE_EQUIPMENT
                        || DAT_UnitsState::instance.units[i].targetedUnitID__OR__engineerMannedSiegeEngineRef
                            != DAT_CurrentUnitSlotID::instance)) {
                    continue;
                }
                if (abs(DAT_UnitsState::instance.units[i].terrainOrClimbHeight
                        - DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].terrainOrClimbHeight
                        - DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].buildingHeight
                        + DAT_UnitsState::instance.units[i].buildingHeight)
                    > 16) {
                    continue;
                }
                // dx from the fields, dy through two locals: each gives the original's registers
                int dx;
                if (DAT_UnitsState::instance.units[i].microXPosition
                    > DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].microXPosition) {
                    dx = DAT_UnitsState::instance.units[i].microXPosition
                        - DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].microXPosition;
                } else {
                    dx = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].microXPosition
                        - DAT_UnitsState::instance.units[i].microXPosition;
                }
                short const otherY = DAT_UnitsState::instance.units[i].microYPosition;
                short const ownY = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].microYPosition;
                int dy;
                if (otherY > ownY) {
                    dy = otherY - ownY;
                } else {
                    dy = ownY - otherY;
                }
                int distance = dy;
                if (dx > dy) {
                    distance = dx;
                }
                if (distance < 30 && crewCount[DAT_UnitsState::instance.units[i].owner] < 2) {
                    crew[DAT_UnitsState::instance.units[i].owner][crewCount[DAT_UnitsState::instance.units[i].owner]]
                        = i;
                    crewCount[DAT_UnitsState::instance.units[i].owner]++;
                }
            }
            int crewOwner = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].owner;
            if (crewCount[crewOwner] != 2) {
                // the ballista is captured by the engineers of another player
                // the test inside the loop: with it in the header the compiler tests crewOwner twice
                for (crewOwner = 1;; ++crewOwner) {
                    if (crewOwner >= 9) {
                        return;
                    }
                    if (crewCount[crewOwner] == 2) {
                        break;
                    }
                }
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::deselectUnit, DAT_UnitsState::ptr)(
                    DAT_CurrentUnitSlotID::instance);
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::clearOrDeselectUnitFromSelection,
                    DAT_UnitsState::ptr)(DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].owner,
                    DAT_CurrentUnitSlotID::instance, 0);
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].owner = crewOwner;
                if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].calculatedOwnerPlayerIndex != 0) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].calculatedOwnerPlayerIndex
                        = crewOwner;
                }
                if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].displayColorPlayerID != 0) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].displayColorPlayerID = crewOwner;
                }
                // fixme: the original passes the owner of units[i], and i is maxUnitCount here, not crewOwner
                int const tribe = MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::createTribe,
                    DAT_TribesState::ptr)(DAT_UnitsState::instance.units[i].owner, 0);
                // fixme: the original passes the tribe as the unit and the unit as the tribe
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::addUnitToTribe, DAT_TribesState::ptr)(
                    tribe, DAT_CurrentUnitSlotID::instance);
            }
            for (i = 0; i < countof(crew[crewOwner]); ++i) {
                int const engineer = crew[crewOwner][i];
                DAT_UnitsState::instance.units[engineer].animationCycleNumber = 0;
                DAT_UnitsState::instance.units[engineer].disappearFadeAlphaCountdown = 0;
                DAT_UnitsState::instance.units[engineer].updateTickTracker = 0;
                DAT_UnitsState::instance.units[engineer].state.generic = OpenSHC::Map::Units::States::US_JESTER_ROAM_TO;
                DAT_UnitsState::instance.units[engineer].engineerManningSiegeStateRef_checkType = 2;
                DAT_UnitsState::instance.units[engineer].cachedState = OpenSHC::Map::Units::States::US_AIM_WEAPONUnk;
                DAT_UnitsState::instance.units[engineer].targetingType
                    = OpenSHC::Map::Units::UIT_NO_INSTRUCTION_OR_MOVEUnk;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].manningEngineerRef[i] = engineer;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].manningEngineerUIDRef[i]
                    = DAT_UnitsState::instance.units[engineer].uid;
                if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray
                            [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].owner]
                        == -1
                    && DAT_UnitsState::instance.units[engineer].aiUnitBehaviourType
                        == OpenSHC::AI::AIUBT_HARASS_SIEGE) {
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
        } else if (state == OpenSHC::Map::Units::States::US_MOVE_TO_DESTINATION
            || state == OpenSHC::Map::Units::States::US_IDLEUnk) {
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 22;
            // in both arms: the compiler hoists it between the compare and its jump; one store above the if loses it
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].moveInstructionSpeedDelayTracker == 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSheetFrameOffset = 449;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed = 0;
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSheetFrameOffset = 449;
                if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].moveInstructionSpeedDelayTracker
                    > 70) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed = -1;
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
                } else {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed = 0;
                }
            }
            if (!MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::hasUnitReachedDestination,
                    DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance)) {
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x3bc = 0;
        } else if (state == OpenSHC::Map::Units::States::US_STATE_9Unk) {
            // moving towards the enemy
            if (DAT_TileMapState::instance
                    .SEC_PathfindingCostTileMap1105[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                            .siegeTargetPlayerID][DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].tile]
                <= 15) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].destinationNeeded
                    = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 22;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSheetFrameOffset = 449;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed = 0;
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].unknownSiegeTentRelated02 != 3) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x3bc = 0;
                return;
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].destinationNeeded
                != OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET) {
                int tile = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::pathFindingRelated,
                    DAT_PathFindingState::ptr)(5, DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].x,
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].y,
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].siegeTargetPlayerID);
                if (DAT_PathFindingState::instance.field_0x9c <= 2) {
                    tile = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::pathFindingRelated,
                        DAT_PathFindingState::ptr)(10,
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].x,
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].y,
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].siegeTargetPlayerID);
                }
                if (DAT_PathFindingState::instance.field_0x9c <= 2) {
                    tile = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::pathFindingRelated,
                        DAT_PathFindingState::ptr)(20,
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].x,
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].y,
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].siegeTargetPlayerID);
                }
                if (DAT_PathFindingState::instance.field_0x9c <= 2) {
                    tile = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::pathFindingRelated,
                        DAT_PathFindingState::ptr)(60,
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].x,
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].y,
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].siegeTargetPlayerID);
                }
                if (DAT_PathFindingState::instance.field_0x9c <= 2) {
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
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].destinationNeeded
                    = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET;
            }
            int const current = DAT_CurrentUnitSlotID::instance;
            if (!MACRO_CALL_MEMBER(
                    OpenSHC::Map::Units::UnitsState_Func::hasUnitReachedDestination, DAT_UnitsState::ptr)(current)) {
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x3bc = 0;
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::moveToFreeTileNearby, DAT_UnitsState::ptr)(current);
        } else if (state == OpenSHC::Map::Units::States::US_UNKNOWN_108) {
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSheetFrameOffset = 1;
        } else if (state == OpenSHC::Map::Units::States::US_STAND_UPUnk) {
            // aiming
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSpeed = 5;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x58 = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                = (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                          .facingDirectionMapOrientationCorrected
                      + 4)
                    % 8
                + 1;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].imageIDUnk
                = (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                          .facingDirectionMapOrientationCorrected
                      + 4)
                    % 8
                + 169;
            if (!DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                    .animationCycleNumberHasJustIncremented) {
                return;
            }
            int targetX = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].shootTargetMicroX / 8;
            int targetY = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].shootTargetMicroY / 8;
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetingType
                    == OpenSHC::Map::Units::UIT_ATTACK_BUILDING
                && DAT_BuildingsState::instance
                        .buildings[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                                .targetID_OR_targetBuildingID]
                        .uid
                    == DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                        .targetedUnitUIDUnk_OR_someAppearTileUnk_OR_buildingUID_OR_pitchDitchUID_OR_entityUID) {
                int const halfSize = (int)DAT_BuildingsState::instance
                                         .buildings[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                                                 .targetID_OR_targetBuildingID]
                                         .widthOrHeight
                    / 2;
                targetX = DAT_BuildingsState::instance
                              .buildings[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                                      .targetID_OR_targetBuildingID]
                              .x
                    + halfSize;
                targetY = DAT_BuildingsState::instance
                              .buildings[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                                      .targetID_OR_targetBuildingID]
                              .y
                    + halfSize;
            }
            int const dy = targetY - DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].y;
            int const dx = targetX - DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].x;
            if (dx * dx + dy * dy > 2916) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x3bc = -60;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
                return;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setUnitFacingDirectionForTargetXandY,
                    DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance, targetX, targetY)) {
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                = OpenSHC::Map::Units::States::US_STATE_2Unk;
        } else if (state == OpenSHC::Map::Units::States::US_STATE_2Unk) {
            // loading
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSpeed = 5;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x58 = 0;
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumberHasJustIncremented
                && DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber == 1) {
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].x,
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].y,
                    OpenSHC::DE::SHCDE::FX_BALLISTA_LOAD);
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.field_0x35dc
                      [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame <= 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = OpenSHC::Map::Units::States::US_RELOAD_WEAPONUnk;
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                = (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                          .facingDirectionMapOrientationCorrected
                      + 4)
                    % 8
                - 7 + DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame * 8;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].imageIDUnk
                = (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                          .facingDirectionMapOrientationCorrected
                      + 4)
                    % 8
                + 161 + DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame * 8;
        } else if (state == OpenSHC::Map::Units::States::US_RELOAD_WEAPONUnk) {
            // firing
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSpeed = 2;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.field_0x3654
                      [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame > 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                              .facingDirectionMapOrientationCorrected
                          + 4)
                        % 8
                    - 7 + DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame * 8;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].imageIDUnk
                    = (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                              .facingDirectionMapOrientationCorrected
                          + 4)
                        % 8
                    + 161 + DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame * 8;
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumberHasJustIncremented
                && DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame == 12) {
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].x,
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].y,
                    OpenSHC::DE::SHCDE::FX_ARAB_BALLISTA_FIRE);
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame == 13
                && DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                    .animationCycleNumberHasJustIncremented) {
                int heightOffset = 30;
                short const target = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].shootTargetedUnit;
                if (target > 0) {
                    MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::prepareProjectileTarget,
                        DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance, target, 200);
                } else {
                    MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::prepareProjectileTarget,
                        DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance, -1, 200);
                    heightOffset = 0;
                }
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::shootProjectile, DAT_UnitsState::ptr)(
                    DAT_CurrentUnitSlotID::instance, OpenSHC::Map::Entities::ET_FIREBALLISTA,
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].shootTargetMicroX,
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].shootTargetMicroY,
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].shootTargetZ + heightOffset);
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame == 0
                && DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                    .animationCycleNumberHasJustIncremented) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
                return;
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame > 0) {
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
        } else if (state == OpenSHC::Map::Units::States::US_DEATH_01
            || state == OpenSHC::Map::Units::States::US_DEATH_03
            || state == OpenSHC::Map::Units::States::US_STONE_DEATH_01) {
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSpeed = 10000;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].facingDirectionMapOrientationCorrected
                + 593;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].imageIDUnk = 0;
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber == 0
                && DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].killedFlagUnk == 0) {
                // the crew dies with the ballista
                for (int i = 0; i < DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                                    .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300;
                    ++i) {
                    int const engineer
                        = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].manningEngineerRef[i];
                    if (DAT_UnitsState::instance.units[engineer].uid
                        != DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].manningEngineerUIDRef[i]) {
                        continue;
                    }
                    DAT_UnitsState::instance.units[engineer].logicalState = OpenSHC::Map::Units::ULS_REMOVE;
                    if (owner == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                        DAT_GameState::instance.mapAndTime
                            .hitsDealtToPlayerArray[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                                    .lastEncounteredEnemyPlayerID]++;
                    } else if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                                   .lastEncounteredEnemyPlayerID
                        == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                        DAT_GameState::instance.mapAndTime.emenyHitArray[owner]++;
                    }
                }
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber++;
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber <= 200) {
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].logicalState
                = OpenSHC::Map::Units::ULS_REMOVE;
        } else if (state == OpenSHC::Map::Units::States::US_DISAPPEAR
            || state == OpenSHC::Map::Units::States::US_JESTER_ROAM_TO) {
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].disappearFadeAlphaCountdown++;
            if ((char)DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].disappearFadeAlphaCountdown
                > 32) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].disappearFadeAlphaCountdown = 32;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].updateTickTracker++;
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].updateTickTracker > 32) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].logicalState
                    = OpenSHC::Map::Units::ULS_REMOVE;
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].killedFlagUnk != 0) {
                return;
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                    .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300
                != 2) {
                return;
            }
            MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::processUnitLossStatistic, DAT_GameState::ptr)(
                owner, DAT_CurrentUnitSlotID::instance);
        }
    }

}
}
