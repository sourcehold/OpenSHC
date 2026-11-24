#include "../Units.func.hpp"

#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Synchrony/Actions.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/DE/SHCDE/eSFX.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Map/Entities/EntityType.hpp"
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
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitPropertiesDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x00569410
    void Units::UpdateTrebuchet()
    {
        // one dx and dy for both engineer loops (a pair per loop loses the match)
        int dx;
        int dy;
        int const unitID = DAT_CurrentUnitSlotID::instance;
        int const owner = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].owner;
        DAT_GameState::instance.playerDataArray[owner].armySize++;
        DAT_GameState::instance.playerDataArray[owner].currentSiegeWeaponCount++;
        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].isSelectable_OR_matchTime = 1;
        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].calculatedOwnerPlayerIndex = owner;
        UnitStateShort const state = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic;
        // counted by the unmanned state only (declared in its block, it loses the match)
        int engineersInPlace = 0;
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
                + 9;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].imageID2
                = (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                          .facingDirectionMapOrientationCorrected
                      + 4)
                    % 8
                + 289;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                    .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300
                != 3) {
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
                if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::harassBuildingsWithSiegeAI,
                        DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance)) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                        = OpenSHC::Map::Units::States::US_STATE_2Unk;
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
                    return;
                }
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x3bc = -40;
            } else {
                if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x3c5
                        == OpenSHC::Map::Units::UIT_ATTACK_LAND
                    || DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x3c5
                        == OpenSHC::Map::Units::UIT_THROW_COW) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetingType
                        = (char)DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x3c5;
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x3c5 = 0;
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
                        == OpenSHC::Map::Units::States::US_MOVE_TO_DESTINATION) {
                        return;
                    }
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                        = OpenSHC::Map::Units::States::US_STAND_UPUnk;
                    return;
                }
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x3bc = -40;
            }
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_FIRE_WEAPONUnk) {
            // waiting for engineers to man the trebuchet
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x58 = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
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
                + 9;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].imageID2 = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
            if (DAT_GameSynchronyState::instance
                        .currentPlayerFullIDArray[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].owner]
                    == -1
                && DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                        .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300
                    == 3) {
                // the AI's engineers have been moved away: check whether all are back
                for (int i = 0; i < 3; ++i) {
                    int const engineer
                        = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].manningEngineerRef[i];
                    if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].manningEngineerUIDRef[i]
                            != DAT_UnitsState::instance.units[engineer].uid
                        || !MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::hasUnitReachedDestination,
                            DAT_UnitsState::ptr)(engineer)
                        || abs(DAT_UnitsState::instance.units[engineer].terrainOrClimbHeight
                               - DAT_UnitsState::instance.units[unitID].terrainOrClimbHeight
                               - DAT_UnitsState::instance.units[unitID].buildingHeight
                               + DAT_UnitsState::instance.units[engineer].buildingHeight)
                            > 16) {
                        break;
                    }
                    short const ownX = DAT_UnitsState::instance.units[unitID].microXPosition;
                    if (DAT_UnitsState::instance.units[engineer].microXPosition > ownX) {
                        dx = DAT_UnitsState::instance.units[engineer].microXPosition - ownX;
                    } else {
                        dx = ownX - DAT_UnitsState::instance.units[engineer].microXPosition;
                    }
                    short const ownY = DAT_UnitsState::instance.units[unitID].microYPosition;
                    if (DAT_UnitsState::instance.units[engineer].microYPosition > ownY) {
                        dy = DAT_UnitsState::instance.units[engineer].microYPosition - ownY;
                    } else {
                        dy = ownY - DAT_UnitsState::instance.units[engineer].microYPosition;
                    }
                    if (max(dx, dy) < 30) {
                        // state 6 keeps `+= 1` on its three counters (as `++` they move the search's registers)
                        engineersInPlace += 1;
                    }
                }
                if (engineersInPlace == 3) {
                    for (int i = 0; i < 3; ++i) {
                        int const engineer = DAT_UnitsState::instance.units[unitID].manningEngineerRef[i];
                        DAT_UnitsState::instance.units[engineer].animationCycleNumber = 0;
                        DAT_UnitsState::instance.units[engineer].state.generic
                            = OpenSHC::Map::Units::States::US_JESTER_ROAM_TO;
                        DAT_UnitsState::instance.units[engineer].disappearFadeAlphaCountdown = 0;
                        DAT_UnitsState::instance.units[engineer].engineerManningSiegeStateRef_checkType = 2;
                        DAT_UnitsState::instance.units[engineer].cachedState
                            = OpenSHC::Map::Units::States::US_AIM_WEAPONUnk;
                        DAT_UnitsState::instance.units[engineer].updateTickTracker = 0;
                    }
                    DAT_UnitsState::instance.units[unitID].state.generic
                        = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
                }
            }
            if (((DAT_UnitsState::instance.units[unitID].fixedRng ^ DAT_GameState::instance.mapAndTime.totalGameTicksUnk
                     ^ 8)
                    & 15)
                != 0) {
                return;
            }
            if (DAT_UnitsState::instance.units[unitID].state.generic
                != OpenSHC::Map::Units::States::US_FIRE_WEAPONUnk) {
                return;
            }
            // look for three engineers of the same player next to the trebuchet
            int crewCount[9] = { 0 };
            int crew[9][3];
            // createTribe reads units[searched] after the search
            int searched = 1;
            for (; searched < DAT_UnitsState::instance.maxUnitCount; ++searched) {
                if (DAT_UnitsState::instance.units[searched].logicalState != OpenSHC::Map::Units::ULS_NORMAL
                    || DAT_UnitsState::instance.units[searched].dying != 0
                    || DAT_UnitsState::instance.units[searched].unitType != OpenSHC::Map::Units::UT_E_ENGINEER
                    || DAT_UnitsState::instance.units[searched].targetingType
                        != OpenSHC::Map::Units::UIT_MAN_SIEGE_EQUIPMENT
                    || DAT_UnitsState::instance.units[searched].targetedUnitID__OR__engineerMannedSiegeEngineRef
                        != unitID
                    || abs(DAT_UnitsState::instance.units[searched].terrainOrClimbHeight
                           - DAT_UnitsState::instance.units[unitID].terrainOrClimbHeight
                           - DAT_UnitsState::instance.units[unitID].buildingHeight
                           + DAT_UnitsState::instance.units[searched].buildingHeight)
                        > 16) {
                    continue;
                }
                if (DAT_UnitsState::instance.units[searched].microXPosition
                    > DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].microXPosition) {
                    dx = DAT_UnitsState::instance.units[searched].microXPosition
                        - DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].microXPosition;
                } else {
                    dx = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].microXPosition
                        - DAT_UnitsState::instance.units[searched].microXPosition;
                }
                if (DAT_UnitsState::instance.units[searched].microYPosition
                    > DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].microYPosition) {
                    dy = DAT_UnitsState::instance.units[searched].microYPosition
                        - DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].microYPosition;
                } else {
                    dy = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].microYPosition
                        - DAT_UnitsState::instance.units[searched].microYPosition;
                }
                if (max(dx, dy) < 30 && crewCount[DAT_UnitsState::instance.units[searched].owner] < 3) {
                    crew[DAT_UnitsState::instance.units[searched].owner]
                        [crewCount[DAT_UnitsState::instance.units[searched].owner]] = searched;
                    crewCount[DAT_UnitsState::instance.units[searched].owner] += 1;
                }
            }
            int crewOwner = DAT_UnitsState::instance.units[unitID].owner;
            if (crewCount[crewOwner] != 3) {
                // the trebuchet is captured by the engineers of another player
                int newOwner = 1;
                // both exit tests in the body, the bound first (in the loop header they lose the match)
                for (;;) {
                    if (newOwner >= 9) {
                        return;
                    }
                    if (crewCount[newOwner] == 3) {
                        break;
                    }
                    newOwner += 1;
                }
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::deselectUnit, DAT_UnitsState::ptr)(
                    DAT_CurrentUnitSlotID::instance);
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::clearOrDeselectUnitFromSelection,
                    DAT_UnitsState::ptr)(DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].owner,
                    DAT_CurrentUnitSlotID::instance, OpenSHC::Map::Units::UT_NONE);
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].owner = newOwner;
                if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].calculatedOwnerPlayerIndex != 0) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].calculatedOwnerPlayerIndex
                        = newOwner;
                }
                if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].displayColorPlayerID != 0) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].displayColorPlayerID = newOwner;
                }
                // fixme: the original passes units[searched].owner with searched = maxUnitCount after the search, not
                // the new owner
                int const tribe = MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::createTribe,
                    DAT_TribesState::ptr)(DAT_UnitsState::instance.units[searched].owner, 0);
                // fixme: the original passes the tribe as unitID and the trebuchet as tribeID (the parameters
                // are (unitID, tribeID), as main's callers pass them)
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::addUnitToTribe, DAT_TribesState::ptr)(
                    tribe, DAT_CurrentUnitSlotID::instance);
                crewOwner = newOwner;
            }
            for (int i = 0; i < countof(crew[crewOwner]); ++i) {
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
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::deselectUnit, DAT_UnitsState::ptr)(engineer);
                MACRO_CALL_MEMBER(
                    OpenSHC::Map::Units::UnitsState_Func::clearOrDeselectUnitFromSelection, DAT_UnitsState::ptr)(
                    DAT_UnitsState::instance.units[engineer].owner, engineer, OpenSHC::Map::Units::UT_NONE);
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300 = 3;
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_STAND_UPUnk) {
            // aiming
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSpeed = 4;
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
                + 9;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].imageID2
                = (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                          .facingDirectionMapOrientationCorrected
                      + 4)
                    % 8
                + 289;
            if (!DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                    .animationCycleNumberHasJustIncremented) {
                return;
            }
            int targetX = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].attackAtTileX;
            int targetY = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].attackAtTileY;
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
            // the two differences written out: as dx and dy locals they take the targets' registers
            if ((targetX - DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].x)
                        * (targetX - DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].x)
                    + (targetY - DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].y)
                        * (targetY - DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].y)
                > 85 * 85) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x3bc = -40;
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
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_STATE_2Unk) {
            // loading
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSpeed = 5;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x58 = 0;
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetingType
                == OpenSHC::Map::Units::UIT_THROW_COW) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setUnitFacingDirectionForTargetXandY,
                    DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance,
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].attackAtTileX,
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].attackAtTileY);
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumberHasJustIncremented
                && DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber == 1) {
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].x,
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].y, OpenSHC::DE::SHCDE::FX_TR_LOAD);
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumberHasJustIncremented
                && DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber == 33) {
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].x,
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].y, OpenSHC::DE::SHCDE::FX_TR_FIRE);
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.field_0x183c
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
                - 7
                + (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.field_0x18a0
                        [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber]
                    * 8;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].imageID2
                = (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                          .facingDirectionMapOrientationCorrected
                      + 4)
                    % 8
                - 7
                + (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.field_0x1904
                        [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber]
                    * 8;
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_RELOAD_WEAPONUnk) {
            // firing
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSpeed = 2;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetingType
                == OpenSHC::Map::Units::UIT_THROW_COW) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setUnitFacingDirectionForTargetXandY,
                    DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance,
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].attackAtTileX,
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].attackAtTileY);
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.field_0x196c
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
                    - 7
                    + (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.field_0x19a8
                            [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber]
                        * 8;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].imageID2
                    = (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                              .facingDirectionMapOrientationCorrected
                          + 4)
                        % 8
                    - 7
                    + (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.field_0x19e4
                            [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber]
                        * 8;
            }
            if (DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.field_0x19a8
                        [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber]
                    == 27
                && DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                    .animationCycleNumberHasJustIncremented) {
                if (DAT_GameSynchronyState::instance
                        .currentPlayerFullIDArray[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].owner]
                    != -1) {
                    MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::prepareProjectileTarget,
                        DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance, -1, 200);
                } else {
                    if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY) {
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x3b0 = 0;
                        if (MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::yieldCowThrow, DAT_AICState::ptr)(
                                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].owner)) {
                            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x3b0 = 1;
                        }
                    }
                }
                if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetingType
                        != OpenSHC::Map::Units::UIT_THROW_COW
                    && DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x3b0 == 0) {
                    if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stoneAmmunition > 0) {
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stoneAmmunition--;
                        MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::shootProjectile, DAT_UnitsState::ptr)(
                            DAT_CurrentUnitSlotID::instance, OpenSHC::Map::Entities::ET_TREBUCHET,
                            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].shootTargetMicroX,
                            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].shootTargetMicroY,
                            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].shootTargetZ);
                    } else if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY
                        && MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::isAIPlayer,
                            DAT_GameSynchronyState::ptr)(owner)) {
                        MACRO_CALL(OpenSHC::Synchrony::Actions_Func::TryAcquireAmmunitionOrPlanToBuyStone)(
                            owner, DAT_CurrentUnitSlotID::instance);
                    }
                } else {
                    // throwing a diseased cow
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x3b0 = 1;
                    if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray
                            [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].owner]
                        != -1) {
                        if (DAT_GameState::instance.playerDataArray[owner].availableCows > 0) {
                            int const cow = MACRO_CALL_MEMBER(
                                OpenSHC::Map::Units::UnitsState_Func::findNearestIdleCowForPlayer, DAT_UnitsState::ptr)(
                                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].owner,
                                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].x,
                                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].y);
                            if (cow != 0) {
                                DAT_UnitsState::instance.units[cow].logicalState = OpenSHC::Map::Units::ULS_REMOVE;
                            }
                            DAT_GameState::instance.playerDataArray[owner].availableCows--;
                        } else {
                            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x3b0 = 0;
                        }
                    }
                    // a flag, so that the shot is written once: written in each arm it loses the match
                    BOOLEnum shoot = TRUE;
                    if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x3b0 == 0) {
                        if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stoneAmmunition > 0) {
                            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stoneAmmunition--;
                        } else if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY
                            && MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::isAIPlayer,
                                DAT_GameSynchronyState::ptr)(owner)) {
                            MACRO_CALL(OpenSHC::Synchrony::Actions_Func::TryAcquireAmmunitionOrPlanToBuyStone)(
                                owner, DAT_CurrentUnitSlotID::instance);
                        } else {
                            shoot = FALSE;
                        }
                    }
                    if (shoot) {
                        MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::shootProjectile, DAT_UnitsState::ptr)(
                            DAT_CurrentUnitSlotID::instance, OpenSHC::Map::Entities::ET_TREBUCHET,
                            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].shootTargetMicroX,
                            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].shootTargetMicroY,
                            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].shootTargetZ);
                    }
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x3b0 = 0;
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x3c5
                        = OpenSHC::Map::Units::UIT_NO_INSTRUCTION_OR_MOVEUnk;
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetingType
                        = OpenSHC::Map::Units::UIT_NO_INSTRUCTION_OR_MOVEUnk;
                }
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame == 0
                && DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                    .animationCycleNumberHasJustIncremented) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame > 0) {
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_MOVE_TO_DESTINATION) {
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSpeed = 2;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
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
                + 9;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].imageID2
                = (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                          .facingDirectionMapOrientationCorrected
                      + 4)
                    % 8
                + 289;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_DEATH_01 || state == OpenSHC::Map::Units::States::US_DEATH_03
            || state == OpenSHC::Map::Units::States::US_STONE_DEATH_01) {
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSpeed = 10000;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].facingDirectionMapOrientationCorrected
                + 569;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].imageIDUnk = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].imageID2 = 0;
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber == 0
                && DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].killedFlagUnk == 0) {
                // the crew dies with the trebuchet
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
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_DISAPPEAR
            || state == OpenSHC::Map::Units::States::US_JESTER_ROAM_TO) {
            DAT_UnitsState::instance.units[unitID].disappearFadeAlphaCountdown++;
            if ((char)DAT_UnitsState::instance.units[unitID].disappearFadeAlphaCountdown > 32) {
                DAT_UnitsState::instance.units[unitID].disappearFadeAlphaCountdown = 32;
            }
            DAT_UnitsState::instance.units[unitID].updateTickTracker++;
            if (DAT_UnitsState::instance.units[unitID].updateTickTracker > 32) {
                DAT_UnitsState::instance.units[unitID].logicalState = OpenSHC::Map::Units::ULS_REMOVE;
            }
            if (DAT_UnitsState::instance.units[unitID].killedFlagUnk != 0) {
                return;
            }
            if (DAT_UnitsState::instance.units[unitID]
                    .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300
                != 3) {
                return;
            }
            MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::processUnitLossStatistic, DAT_GameState::ptr)(
                owner, DAT_CurrentUnitSlotID::instance);
        }
    }

}
}
