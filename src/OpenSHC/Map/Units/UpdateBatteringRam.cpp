#include "../Units.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/DE/SHCDE/eSFX.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/Enums/HitSoundMaterial.hpp"
#include "OpenSHC/Map/LogicHelpers/Logic1.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitInstructionType.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentUnitSlotID.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitHasBecomeIdle.hpp"
#include "OpenSHC/Globals/DAT_UnitPropertiesDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DWORD_00ee1044.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x005459B0
    void Units::UpdateBatteringRam()
    {
        // counted by the AI check only (declared there, or behind the owner copies, it loses the match)
        int engineersInPlace = 0;
        int const unitID = DAT_CurrentUnitSlotID::instance;
        int const owner = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].owner;
        DAT_GameState::instance.playerDataArray[owner].armySize++;
        DAT_GameState::instance.playerDataArray[owner].currentSiegeWeaponCount++;
        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].isSelectable_OR_matchTime = 1;
        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].calculatedOwnerPlayerIndex
            = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].owner;
        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].displayColorPlayerID
            = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].owner;
        UnitStateShort const state = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic;
        if (state == OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk) {
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate = -1;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].facingDirectionMapOrientationCorrected
                + 1;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].imageIDUnk
                = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].facingDirectionMapOrientationCorrected
                + 145;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].imageID2 = 0;
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                    .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300
                != 4) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = OpenSHC::Map::Units::States::US_FIRE_WEAPONUnk;
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_FIRE_WEAPONUnk) {
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x58 = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].facingDirectionMapOrientationCorrected
                + 1;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].imageIDUnk
                = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].facingDirectionMapOrientationCorrected
                + 145;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].imageID2 = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
            // an AI ram starts moving once its four engineers stand next to it
            if (DAT_GameSynchronyState::instance
                        .currentPlayerFullIDArray[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].owner]
                    == -1
                && DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                        .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300
                    == 4) {
                // three tests, three statements (as one || chain they lose the match)
                for (int i = 0;
                    i < countof(DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].manningEngineerRef);
                    ++i) {
                    int const engineer
                        = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].manningEngineerRef[i];
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
                    int dx;
                    if (DAT_UnitsState::instance.units[engineer].microXPosition
                        > DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].microXPosition) {
                        dx = DAT_UnitsState::instance.units[engineer].microXPosition
                            - DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].microXPosition;
                    } else {
                        dx = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].microXPosition
                            - DAT_UnitsState::instance.units[engineer].microXPosition;
                    }
                    int dy;
                    if (DAT_UnitsState::instance.units[engineer].microYPosition
                        > DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].microYPosition) {
                        dy = DAT_UnitsState::instance.units[engineer].microYPosition
                            - DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].microYPosition;
                    } else {
                        dy = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].microYPosition
                            - DAT_UnitsState::instance.units[engineer].microYPosition;
                    }
                    if (max(dx, dy) < 30) {
                        engineersInPlace++;
                    }
                }
                if (engineersInPlace == 4) {
                    for (int i = 0;
                        i < countof(DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].manningEngineerRef);
                        ++i) {
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
            // an unmanned ram is captured by the first player with four engineers next to it
            if (((DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].fixedRng
                     ^ DAT_GameState::instance.mapAndTime.totalGameTicksUnk ^ 8)
                    & 15)
                != 0) {
                return;
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                != OpenSHC::Map::Units::States::US_FIRE_WEAPONUnk) {
                return;
            }
            int engineerCounts[9];
            int engineerIDs[9][4];
            memset(engineerCounts, 0, sizeof(engineerCounts));
            // createTribe reads units[searched] after the scan
            int searched = 1;
            // six tests, six statements (as one chain they lose the match)
            for (; searched < DAT_UnitsState::instance.maxUnitCount; ++searched) {
                if (DAT_UnitsState::instance.units[searched].logicalState != OpenSHC::Map::Units::ULS_NORMAL) {
                    continue;
                }
                if (DAT_UnitsState::instance.units[searched].dying != 0) {
                    continue;
                }
                if (DAT_UnitsState::instance.units[searched].unitType != OpenSHC::Map::Units::UT_E_ENGINEER) {
                    continue;
                }
                if (DAT_UnitsState::instance.units[searched].targetingType
                    != OpenSHC::Map::Units::UIT_MAN_SIEGE_EQUIPMENT) {
                    continue;
                }
                if (DAT_UnitsState::instance.units[searched].targetedUnitID__OR__engineerMannedSiegeEngineRef
                    != DAT_CurrentUnitSlotID::instance) {
                    continue;
                }
                if (abs(DAT_UnitsState::instance.units[searched].terrainOrClimbHeight
                        - DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].terrainOrClimbHeight
                        - DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].buildingHeight
                        + DAT_UnitsState::instance.units[searched].buildingHeight)
                    > 16) {
                    continue;
                }
                int dx;
                if (DAT_UnitsState::instance.units[searched].microXPosition
                    > DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].microXPosition) {
                    dx = DAT_UnitsState::instance.units[searched].microXPosition
                        - DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].microXPosition;
                } else {
                    dx = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].microXPosition
                        - DAT_UnitsState::instance.units[searched].microXPosition;
                }
                int dy;
                if (DAT_UnitsState::instance.units[searched].microYPosition
                    > DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].microYPosition) {
                    dy = DAT_UnitsState::instance.units[searched].microYPosition
                        - DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].microYPosition;
                } else {
                    dy = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].microYPosition
                        - DAT_UnitsState::instance.units[searched].microYPosition;
                }
                if (max(dx, dy) < 30 && engineerCounts[DAT_UnitsState::instance.units[searched].owner] < 4) {
                    engineerIDs[DAT_UnitsState::instance.units[searched].owner]
                               [engineerCounts[DAT_UnitsState::instance.units[searched].owner]] = searched;
                    engineerCounts[DAT_UnitsState::instance.units[searched].owner]++;
                }
            }
            int crewOwner = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].owner;
            if (engineerCounts[crewOwner] != 4) {
                BOOLEnum found = FALSE;
                int newOwner = 1;
                for (; newOwner < countof(engineerCounts); ++newOwner) {
                    if (engineerCounts[newOwner] == 4) {
                        found = TRUE;
                        break;
                    }
                }
                if (!found) {
                    return;
                }
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::deselectUnit, DAT_UnitsState::ptr)(
                    DAT_CurrentUnitSlotID::instance);
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::clearOrDeselectUnitFromSelection,
                    DAT_UnitsState::ptr)(DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].owner,
                    DAT_CurrentUnitSlotID::instance, OpenSHC::Map::Units::UT_NONE);
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].owner = (short)newOwner;
                if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].calculatedOwnerPlayerIndex != 0) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].calculatedOwnerPlayerIndex
                        = newOwner;
                }
                if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].displayColorPlayerID != 0) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].displayColorPlayerID
                        = (short)newOwner;
                }
                // fixme: the original passes units[searched].owner with searched = maxUnitCount after the scan,
                // not the new owner
                int const newTribe = MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::createTribe,
                    DAT_TribesState::ptr)(DAT_UnitsState::instance.units[searched].owner, 0);
                // fixme: the original passes the tribe as unitID and the ram as tribeID (the parameters are
                // (unitID, tribeID), as main's callers pass them)
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::addUnitToTribe, DAT_TribesState::ptr)(
                    newTribe, DAT_CurrentUnitSlotID::instance);
                crewOwner = newOwner;
            }
            for (int i = 0; i < countof(engineerIDs[crewOwner]); ++i) {
                int const engineer = engineerIDs[crewOwner][i];
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
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::deselectUnit, DAT_UnitsState::ptr)(engineer);
                MACRO_CALL_MEMBER(
                    OpenSHC::Map::Units::UnitsState_Func::clearOrDeselectUnitFromSelection, DAT_UnitsState::ptr)(
                    DAT_UnitsState::instance.units[engineer].owner, engineer, OpenSHC::Map::Units::UT_NONE);
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300 = 4;
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_MOVE_TO_DESTINATION
            || state == OpenSHC::Map::Units::States::US_IDLEUnk) {
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 20;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].facingDirectionMapOrientationCorrected
                + 1;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].imageID2 = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSheetFrameOffset = 145;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed = 0;
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::hasUnitReachedDestination, DAT_UnitsState::ptr)(
                    DAT_CurrentUnitSlotID::instance)) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed = 0;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x3bc = 0;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::stopUnitIfNextToTarget, DAT_UnitsState::ptr)(
                    DAT_CurrentUnitSlotID::instance)
                != 0) {
                // through the copy made at the start (made here, it loses the match): the original keeps the
                // unit's offset in a register across that call
                DAT_UnitsState::instance.units[unitID].state.generic
                    = OpenSHC::Map::Units::States::US_MELEE_ATTACK_WALL;
            }
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_MELEE_ATTACK_WALL) {
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSpeed = 3;
            if (!MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setUnitFacingDirectionForTargetXandY,
                    DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance,
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].attackAtTileX,
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].attackAtTileY)) {
                if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                        .animationCycleNumberHasJustIncremented
                    && DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber == 2) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].x,
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].y,
                        OpenSHC::DE::SHCDE::FX_RAM_SWING);
                }
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                          .facingDirectionMapOrientationCorrected
                    + 1;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].imageIDUnk
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                          .facingDirectionMapOrientationCorrected
                    + 9;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.field_0x83a8
                          [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
                if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame == 0
                    && DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                        .animationCycleNumberHasJustIncremented) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                        = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.field_0x83a8[0];
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber++;
                }
                if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame == 10
                    && DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                        .animationCycleNumberHasJustIncremented) {
                    DAT_UnitHasBecomeIdle::instance = 1;
                }
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].imageID2
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                          .facingDirectionMapOrientationCorrected
                    + 9 + DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame * 8;
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                          .facingDirectionMapOrientationCorrected
                    + 1;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].imageIDUnk
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                          .facingDirectionMapOrientationCorrected
                    + 145;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].imageID2 = 0;
            }
            if (DAT_UnitHasBecomeIdle::instance == 0) {
                return;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingHurtSFXID, DAT_TileMapState::ptr)(
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetedBuildingTile)
                != OpenSHC::Map::Enums::HSM_NONE) {
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].x,
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].y, OpenSHC::DE::SHCDE::FX_RAM_HIT);
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].nextAttackHurtsWall++;
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].nextAttackHurtsWall > 1) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].nextAttackHurtsWall = 0;
            }
            int const building = DAT_TileMapState::instance
                                     .BuildingLayer[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                                             .targetedBuildingTile];
            int const logic
                = DAT_TileMapState::instance
                      .LogicLayer[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetedBuildingTile];
            // "Your gates are under attack" at most every 3 minutes
            if (building != 0 && timeGetTime() - DWORD_00ee1044::instance > 180000
                && DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].owner
                    != DAT_GameSynchronyState::instance.currentPlayerSlotID
                && DAT_BuildingsState::instance.buildings[building].owner
                    == DAT_GameSynchronyState::instance.currentPlayerSlotID
                && DAT_BuildingsState::instance.buildings[building].logicalState != 0
                && DAT_BuildingsState::instance.buildings[building].logicalState != OpenSHC::Map::Buildings::BLS_REMOVE
                && DAT_BuildingsState::instance.buildings[building].currentHealth > 0
                && (DAT_BuildingsState::instance.buildings[building].buildingType
                        == OpenSHC::Map::Buildings::BT_GATEHOUSELARGE
                    || DAT_BuildingsState::instance.buildings[building].buildingType
                        == OpenSHC::Map::Buildings::BT_GATEHOUSESMALL
                    || DAT_BuildingsState::instance.buildings[building].buildingType
                        == OpenSHC::Map::Buildings::BT_WOODGATE1)) {
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                    // "General_Warning6.wav"
                    s_General_Warning6_wav_005abe10);
                DWORD_00ee1044::instance = timeGetTime();
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::processDamageToBuildingThunk, DAT_TileMapState::ptr)(
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetedBuildingTile,
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].attackAtTileX,
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].attackAtTileY, 50, 0,
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].owner, TRUE)
                && ((logic & OpenSHC::Map::LogicHelpers::L_WALL_OR_GATEHOUSE) == 0
                    || !MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationNearTargetedBuilding,
                        DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance, 0))) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetedBuildingTile = 0;
                if (!MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::moveUnitToBehaviorTarget,
                        DAT_TribesState::ptr)(DAT_CurrentUnitSlotID::instance,
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                            .unknownDigMoatOrWallAttackFlag1015)) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                        = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
                }
            }
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_UNKNOWN_108) {
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSheetFrameOffset = 1;
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_DEATH_01 || state == OpenSHC::Map::Units::States::US_DEATH_03
            || state == OpenSHC::Map::Units::States::US_STONE_DEATH_01) {
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSpeed = 10000;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber = 209;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].imageIDUnk = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].imageID2 = 0;
            // the engineers pushing a destroyed ram die with it
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber == 0
                && DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].killedFlagUnk == 0) {
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
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber > 200) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].logicalState
                    = OpenSHC::Map::Units::ULS_REMOVE;
            }
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_DISAPPEAR
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
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].killedFlagUnk == 0
                && DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                        .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300
                    == 4) {
                MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::processUnitLossStatistic,
                    DAT_GameState::ptr)(owner, DAT_CurrentUnitSlotID::instance);
            }
            return;
        }
    }

}
}
