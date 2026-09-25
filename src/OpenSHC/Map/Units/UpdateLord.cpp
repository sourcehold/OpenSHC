#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Units.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/DE/SHCDE/eSFX.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Map/MapType2.hpp"
#include "OpenSHC/Map/Units/Pathfinding/DestinationNeededEnum.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/UI/Enums/BuildingsAndStatusMenuTabType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentUnitSlotID.hpp"
#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_UnitHasBecomeIdle.hpp"
#include "OpenSHC/Globals/DAT_UnitPropertiesDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/DWORD_00ee105c.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::DE::SHCDE::eSFX;
    using OpenSHC::DE::SHCDE::eTextSections;
    using OpenSHC::Game::GameMode;
    using OpenSHC::Game::GameMode2;
    using OpenSHC::Map::MapType2;
    using OpenSHC::Map::Units::UnitLogicState;
    using OpenSHC::Map::Units::UnitType;
    using OpenSHC::Map::Units::Pathfinding::DestinationNeededEnum;
    using OpenSHC::Map::Units::States::UnitState;
    using OpenSHC::UI::Enums::BuildingsAndStatusMenuTabType;
    using OpenSHC::UI::Enums::MenuViewType;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      WARNING: Unable to use type for symbol _matchTime
     */

    // FUNCTION: STRONGHOLDCRUSADER 0x0056C560
    void Units::UpdateLord()
    {
        int matchTime = DAT_GameCore::instance.mapTimeInTicks;
        int unitID = DAT_CurrentUnitSlotID::instance;
        int owner = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].owner;
        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed = 0;
        int spriteOffset = 0;
        if (DAT_UnitsState::instance.units[unitID].isSelectable_OR_matchTime == 0
            && DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY) {
            DAT_UnitsState::instance.units[unitID].isSelectable_OR_matchTime = (short)matchTime;
        } else {
            DAT_UnitsState::instance.units[unitID].isSelectable_OR_matchTime = 1;
        }
        if (DAT_UnitsState::instance.units[unitID].unknownLordTypeBasedMissionSpecificValue_01 == 1) {
            DAT_UnitsState::instance.units[unitID].spriteID = 0xcd;
            spriteOffset = 0x80;
        }
        DAT_GameState::instance.playerDataArray[owner].closestEnemyDistanceToTheLord
            = DAT_UnitsState::instance.units[unitID].closestEnemyMicroDistance;
        if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY
            && DAT_UnitsState::instance.units[unitID].dying == 0) {
            DAT_GameSynchronyState::instance.finalResults.finalTimeAlive[owner] = matchTime;
        }
        UnitStateShort state = DAT_UnitsState::instance.units[unitID].state.generic;
        if (state == OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk) {
            if (DAT_UnitsState::instance.units[unitID].isDisappearingUnk != 0) {
                DAT_UnitsState::instance.units[unitID].disappearFadeAlphaCountdown -= 1;
                if ((char)DAT_UnitsState::instance.units[unitID].disappearFadeAlphaCountdown >= 0) {
                    return;
                }
                DAT_UnitsState::instance.units[unitID].disappearFadeAlphaCountdown = 0;
                DAT_UnitsState::instance.units[unitID].isDisappearingUnk = 0;
                return;
            }
            if (DAT_UnitsState::instance.units[unitID].goToRallyPoint == 0) {
                return;
            }
            DAT_UnitsState::instance.units[unitID].goToRallyPoint = 0;
            DAT_UnitsState::instance.units[unitID].state.generic = OpenSHC::Map::Units::States::US_IDLEUnk;
            DAT_UnitsState::instance.units[unitID].destinationNeeded
                = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_NEEDED;
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_IDLEUnk) {
            // walking to the campfire
            if (DAT_UnitsState::instance.units[unitID].destinationNeeded
                != OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET) {
                if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit, DAT_UnitsState::ptr)(
                        unitID, DAT_UnitsState::instance.units[unitID].targetX_2,
                        DAT_UnitsState::instance.units[unitID].targetY_2, 0)
                    == FALSE) {
                    MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setPositionOfUnit, DAT_UnitsState::ptr)(
                        DAT_CurrentUnitSlotID::instance,
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetX_2,
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetY_2,
                        DAT_TileMapState::instance.HeightLayer[DAT_ViewportRenderState::instance
                                                                   .translationMatrix[DAT_UnitsState::instance
                                                                           .units[DAT_CurrentUnitSlotID::instance]
                                                                           .targetY_2]
                                                                   .addXgetTile
                            + DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetX_2]);
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                        = OpenSHC::Map::Units::States::US_IDLEUnk;
                }
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].destinationNeeded
                    = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSheetFrameOffset
                = 0x81 - spriteOffset;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0x10;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].movementSpeed = 2;
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::hasUnitReachedDestination, DAT_UnitsState::ptr)(
                    DAT_CurrentUnitSlotID::instance)
                == FALSE) {
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                = OpenSHC::Map::Units::States::US_JESTER_ROAM_TO;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].disappearFadeAlphaCountdown = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].engineerManningSiegeStateRef_checkType = 2;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].cachedState = (UnitState)2;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].updateTickTracker = 0;
            return;
        }
        if (state == (UnitState)2) {
            // at the campfire: decide what to do next
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset = 1;
            DAT_UnitsState::instance.units[unitID].updateTickTracker += 1;
            if (DAT_UnitsState::instance.units[unitID].updateTickTracker <= 10) {
                return;
            }
            int random = SEC_RNG::instance.currentNumber2 & 7;
            DAT_UnitsState::instance.units[unitID].updateTickTracker = 0;
            DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
            DAT_UnitsState::instance.units[unitID].substate = 0;
            if (DAT_UnitsState::instance.units[DAT_GameState::instance.playerDataArray[owner].ladyIDUnk].state.generic
                == (UnitState)3) {
                random = 8;
            }
            int unit = MACRO_CALL_MEMBER(
                OpenSHC::Map::Units::UnitsState_Func::findEligibleUnitByTimeAndLocation, DAT_UnitsState::ptr)(unitID,
                owner, DAT_UnitsState::instance.units[unitID].x, DAT_UnitsState::instance.units[unitID].y, 0, 10);
            if (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY
                && DAT_GameState::instance.mapAndTime.field3171_0x27a8 == 0
                && DAT_GameState::instance.mapAndTime.field3172_0x27ac
                        + DAT_GameState::instance.mapAndTime.field3170_0x27a4
                    <= 2
                && DAT_GameState::instance.playerDataArray[owner].totalEnemyUnitsCount <= 0) {
                if (random == 8) {
                    // walk with the lady
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].cachedState = (UnitState)3;
                } else if (random <= 3) {
                    int tower = MACRO_CALL_MEMBER(
                        OpenSHC::Map::Buildings::BuildingsState_Func::canNavigateToDefensiveBuilding,
                        DAT_BuildingsState::ptr)(owner,
                        DAT_GameState::instance.playerDataArray[owner].campground.xEntry,
                        DAT_GameState::instance.playerDataArray[owner].campground.yEntry - 1,
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetID_OR_targetBuildingID);
                    if (tower == 0) {
                        return;
                    }
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].cachedState
                        = OpenSHC::Map::Units::States::US_LOOK_AROUNDUnk;
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetID_OR_targetBuildingID
                        = (short)tower;
                } else if (unit == 0) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].cachedState
                        = OpenSHC::Map::Units::States::US_SIT_DOWNUnk;
                } else {
                    // talk to a unit
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].cachedState
                        = OpenSHC::Map::Units::States::US_AIM_WEAPONUnk;
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                        .targetedUnitID__OR__engineerMannedSiegeEngineRef = (short)unit;
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                        .targetedUnitUIDUnk_OR_someAppearTileUnk_OR_buildingUID_OR_pitchDitchUID_OR_entityUID
                        = DAT_UnitsState::instance.units[unit].uid;
                }
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].cachedState = (UnitState)12;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].resourceToDeposit = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                = OpenSHC::Map::Units::States::US_JESTER_ROAM_TO;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].disappearFadeAlphaCountdown = 32;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].engineerManningSiegeStateRef_checkType
                = 0xfe;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].destinationNeeded
                = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_NEEDED;
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::resetUnitMovementState, DAT_UnitsState::ptr)(
                DAT_CurrentUnitSlotID::instance);
            return;
        }
        if (state == (UnitState)3) {
            // walking with the lady
            int lady = DAT_GameState::instance.playerDataArray[owner].ladyIDUnk;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0x10;
            DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset = 1;
            if (DAT_UnitsState::instance.units[lady].state.generic != (UnitState)3 || lady == 0
                || DAT_GameState::instance.playerDataArray[owner].totalEnemyUnitsCount > 0
                || DAT_GameState::instance.mapAndTime.field3171_0x27a8 != 0
                || DAT_GameState::instance.mapAndTime.field3172_0x27ac
                        + DAT_GameState::instance.mapAndTime.field3170_0x27a4
                    > 2) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::makeUnitStopWalkingByClearingPathProgressState,
                    DAT_UnitsState::ptr)(unitID);
                if (DAT_UnitsState::instance.units[unitID].movementRelated < 8) {
                    return;
                }
                DAT_UnitsState::instance.units[unitID].state.generic = OpenSHC::Map::Units::States::US_IDLEUnk;
                DAT_UnitsState::instance.units[unitID].destinationNeeded
                    = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_NEEDED;
                return;
            }
            DAT_UnitsState::instance.units[unitID].movementSpeed
                = DAT_UnitsState::instance.units[unitID].currentIndexInPathPlan + 2;
            if (DAT_UnitsState::instance.units[unitID].movementSpeed > 4) {
                DAT_UnitsState::instance.units[unitID].movementSpeed = 4;
            }
            if (DAT_UnitsState::instance.units[unitID].destinationNeeded
                != OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit, DAT_UnitsState::ptr)(
                    unitID, DAT_UnitsState::instance.units[lady].x, DAT_UnitsState::instance.units[lady].y, 0);
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::changeDestinationByAmount, DAT_UnitsState::ptr)(
                    DAT_CurrentUnitSlotID::instance, 1);
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].destinationNeeded
                    = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::hasUnitReachedDestination, DAT_UnitsState::ptr)(
                    unitID)
                == FALSE) {
                return;
            }
            DAT_UnitsState::instance.units[unitID].destinationNeeded
                = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_NEEDED;
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_AIM_WEAPONUnk) {
            // walking to the unit to talk to
            DAT_UnitsState::instance.units[unitID].movementSpeed = 2;
            if (DAT_UnitsState::instance.units[unitID].destinationNeeded
                != OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit, DAT_UnitsState::ptr)(
                    unitID,
                    DAT_UnitsState::instance
                        .units[DAT_UnitsState::instance.units[unitID].targetedUnitID__OR__engineerMannedSiegeEngineRef]
                        .x,
                    DAT_UnitsState::instance
                        .units[DAT_UnitsState::instance.units[unitID].targetedUnitID__OR__engineerMannedSiegeEngineRef]
                        .y,
                    0);
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::changeDestinationByAmount, DAT_UnitsState::ptr)(
                    DAT_CurrentUnitSlotID::instance, 1);
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].destinationNeeded
                    = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSheetFrameOffset = 1;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0x10;
            int target = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                             .targetedUnitID__OR__engineerMannedSiegeEngineRef;
            if (target != 0
                && DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                        .targetedUnitUIDUnk_OR_someAppearTileUnk_OR_buildingUID_OR_pitchDitchUID_OR_entityUID
                    == DAT_UnitsState::instance.units[target].uid
                && DAT_GameState::instance.playerDataArray[owner].totalEnemyUnitsCount < 1
                && DAT_GameState::instance.mapAndTime.field3171_0x27a8 == 0
                && DAT_GameState::instance.mapAndTime.field3172_0x27ac
                        + DAT_GameState::instance.mapAndTime.field3170_0x27a4
                    <= 2) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                    DAT_DirectionAlgorithmState::ptr)(DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].x,
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].y,
                    DAT_UnitsState::instance.units[target].x, DAT_UnitsState::instance.units[target].y);
                if (DAT_DirectionAlgorithmState::instance.distanceHigh < 3) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::Map::Units::UnitsState_Func::makeUnitStopWalkingByClearingPathProgressState,
                        DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance);
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                        = OpenSHC::Map::Units::States::US_FIRE_WEAPONUnk;
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
                    return;
                }
                if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::hasUnitReachedDestination,
                        DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance)
                    == FALSE) {
                    return;
                }
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].destinationNeeded
                    = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_NEEDED;
                return;
            }
            // enemies are around: go back to the campfire
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::makeUnitStopWalkingByClearingPathProgressState,
                DAT_UnitsState::ptr)(unitID);
            if (DAT_UnitsState::instance.units[unitID].movementRelated < 8) {
                return;
            }
            DAT_UnitsState::instance.units[unitID].state.generic = OpenSHC::Map::Units::States::US_IDLEUnk;
            DAT_UnitsState::instance.units[unitID].destinationNeeded
                = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_NEEDED;
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_SIT_DOWNUnk) {
            // walking the walls
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0x10;
            DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset = 1;
            if (DAT_UnitsState::instance.units[unitID].destinationNeeded
                != OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET) {
                if (DAT_GameState::instance.playerDataArray[owner].totalEnemyUnitsCount <= 0
                    && DAT_GameState::instance.mapAndTime.field3171_0x27a8 == 0
                    && DAT_GameState::instance.mapAndTime.field3172_0x27ac
                            + DAT_GameState::instance.mapAndTime.field3170_0x27a4
                        < 3) {
                    if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::computeLadderClimbPath,
                            DAT_UnitsState::ptr)(unitID, 2, 1, 1)
                        == 0) {
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                            = OpenSHC::Map::Units::States::US_IDLEUnk;
                        return;
                    }
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].destinationNeeded
                        = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET;
                    return;
                }
                DAT_UnitsState::instance.units[unitID].state.generic = OpenSHC::Map::Units::States::US_IDLEUnk;
                return;
            }
            if (DAT_GameState::instance.playerDataArray[owner].totalEnemyUnitsCount <= 0
                && DAT_GameState::instance.mapAndTime.field3171_0x27a8 == 0
                && DAT_GameState::instance.mapAndTime.field3172_0x27ac
                        + DAT_GameState::instance.mapAndTime.field3170_0x27a4
                    < 3) {
                if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::hasTunnelerNotFinishedDigging,
                        DAT_UnitsState::ptr)(unitID)
                    == FALSE) {
                    return;
                }
                DAT_UnitsState::instance.units[unitID].state.generic = OpenSHC::Map::Units::States::US_IDLEUnk;
                DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
                DAT_UnitsState::instance.units[unitID].destinationNeeded
                    = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_NEEDED;
                return;
            }
            // enemies are around: go back to the campfire
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::makeUnitStopWalkingByClearingPathProgressState,
                DAT_UnitsState::ptr)(unitID);
            if (DAT_UnitsState::instance.units[unitID].movementRelated < 8) {
                return;
            }
            DAT_UnitsState::instance.units[unitID].state.generic = OpenSHC::Map::Units::States::US_IDLEUnk;
            DAT_UnitsState::instance.units[unitID].destinationNeeded
                = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_NEEDED;
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_FIRE_WEAPONUnk) {
            // talking to a unit
            if (DAT_UnitsState::instance.units[unitID].movementRelated < 8) {
                DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset = 1;
                DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0x10;
                return;
            }
            MACRO_CALL_MEMBER(
                OpenSHC::Map::Units::UnitsState_Func::setUnitFacingDirectionTowardsTarget, DAT_UnitsState::ptr)(
                unitID, DAT_UnitsState::instance.units[unitID].targetedUnitID__OR__engineerMannedSiegeEngineRef);
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSpeed = 6;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate == 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.field310_0x5fbc
                          [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
            } else if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate == 1) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.field311_0x5ff4
                          [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
            } else if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate == 2) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.field312_0x603c
                          [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
            } else if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate == 3) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.field313_0x6084
                          [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.field314_0x60dc
                          [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame <= 0) {
                DAT_UnitHasBecomeIdle::instance = 1;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                          .facingDirectionMapOrientationCorrected
                    - spriteOffset + 0x101;
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                          .facingDirectionMapOrientationCorrected
                    + DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame * 8 - spriteOffset
                    + 0xf9;
            }
            if (DAT_UnitHasBecomeIdle::instance == 0) {
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate += 1;
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate > 4) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate = 0;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
            if (DAT_GameState::instance.playerDataArray[owner].totalEnemyUnitsCount <= 0
                && DAT_GameState::instance.mapAndTime.field3171_0x27a8 == 0
                && DAT_GameState::instance.mapAndTime.field3172_0x27ac
                        + DAT_GameState::instance.mapAndTime.field3170_0x27a4
                    <= 2) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].resourceToDeposit += 1;
                if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].resourceToDeposit < 3) {
                    int unit
                        = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::findEligibleUnitByTimeAndLocation,
                            DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance, owner,
                            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].x,
                            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].y, 0, 10);
                    if (unit != 0) {
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                            = OpenSHC::Map::Units::States::US_AIM_WEAPONUnk;
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                            .targetedUnitID__OR__engineerMannedSiegeEngineRef = (short)unit;
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                            .targetedUnitUIDUnk_OR_someAppearTileUnk_OR_buildingUID_OR_pitchDitchUID_OR_entityUID
                            = DAT_UnitsState::instance.units[unit].uid;
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].destinationNeeded
                            = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_NEEDED;
                        return;
                    }
                }
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                = OpenSHC::Map::Units::States::US_IDLEUnk;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].destinationNeeded
                = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_NEEDED;
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_LOOK_AROUNDUnk) {
            // walking to a tower
            DAT_UnitsState::instance.units[unitID].movementSpeed = 2;
            if (DAT_UnitsState::instance.units[unitID].destinationNeeded
                != OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit, DAT_UnitsState::ptr)(
                    unitID,
                    DAT_BuildingsState::instance
                        .buildings[DAT_UnitsState::instance.units[unitID].targetID_OR_targetBuildingID]
                        .someX,
                    DAT_BuildingsState::instance
                        .buildings[DAT_UnitsState::instance.units[unitID].targetID_OR_targetBuildingID]
                        .someY,
                    0);
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].destinationNeeded
                    = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET;
            }
            if (DAT_GameState::instance.playerDataArray[owner].totalEnemyUnitsCount > 0
                || DAT_GameState::instance.mapAndTime.field3171_0x27a8 != 0
                || DAT_GameState::instance.mapAndTime.field3172_0x27ac
                        + DAT_GameState::instance.mapAndTime.field3170_0x27a4
                    > 2) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::makeUnitStopWalkingByClearingPathProgressState,
                    DAT_UnitsState::ptr)(unitID);
                if (DAT_UnitsState::instance.units[unitID].movementRelated > 7) {
                    DAT_UnitsState::instance.units[unitID].state.generic = OpenSHC::Map::Units::States::US_IDLEUnk;
                    DAT_UnitsState::instance.units[unitID].destinationNeeded
                        = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_NEEDED;
                }
            }
            DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset = 1;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0x10;
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
            DAT_UnitsState::instance.units[unitID].state.generic = OpenSHC::Map::Units::States::US_STAND_UPUnk;
            DAT_UnitsState::instance.units[unitID].updateTickTracker = 0;
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_STAND_UPUnk) {
            // looking out from the tower
            DAT_UnitsState::instance.units[unitID].animationSpeed = 2;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[unitID].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp
                      .field308_0x5f6c[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
            if (DAT_UnitsState::instance.units[unitID].animationFrame <= 0) {
                DAT_UnitsState::instance.units[unitID].gfxNumber
                    = DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected + 1;
                DAT_UnitHasBecomeIdle::instance = 1;
            } else {
                DAT_UnitsState::instance.units[unitID].gfxNumber
                    = DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected - 7
                    + DAT_UnitsState::instance.units[unitID].animationFrame * 8;
            }
            if (DAT_UnitHasBecomeIdle::instance == 0) {
                return;
            }
            DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
            DAT_UnitsState::instance.units[unitID].destinationNeeded
                = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_NEEDED;
            DAT_UnitsState::instance.units[unitID].state.generic = OpenSHC::Map::Units::States::US_IDLEUnk;
            if (DAT_GameState::instance.playerDataArray[owner].totalEnemyUnitsCount > 0) {
                return;
            }
            if (DAT_GameState::instance.mapAndTime.field3171_0x27a8 != 0) {
                return;
            }
            if (DAT_GameState::instance.mapAndTime.field3172_0x27ac
                    + DAT_GameState::instance.mapAndTime.field3170_0x27a4
                > 2) {
                return;
            }
            DAT_UnitsState::instance.units[unitID].resourceToDeposit += 1;
            if (DAT_UnitsState::instance.units[unitID].resourceToDeposit > 1) {
                return;
            }
            // visit another tower
            int tower = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::canNavigateToDefensiveBuilding,
                DAT_BuildingsState::ptr)(owner, DAT_UnitsState::instance.units[unitID].x,
                DAT_UnitsState::instance.units[unitID].y,
                DAT_UnitsState::instance.units[unitID].targetID_OR_targetBuildingID);
            if (tower == 0) {
                return;
            }
            if (tower == DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetID_OR_targetBuildingID) {
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                = OpenSHC::Map::Units::States::US_LOOK_AROUNDUnk;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetID_OR_targetBuildingID = (short)tower;
            return;
        }
        if (state == (UnitState)12) {
            // retreating to the keep
            DAT_UnitsState::instance.units[unitID].movementSpeed = 1;
            if (DAT_UnitsState::instance.units[unitID].destinationNeeded
                != OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET) {
                int keep = DAT_GameState::instance.playerDataArray[owner].keep.id;
                if (keep <= 0) {
                    DAT_UnitsState::instance.units[unitID].state.generic = (UnitState)13;
                    return;
                }
                int x = DAT_BuildingsState::instance.buildings[keep].someX + (SEC_RNG::instance.currentNumber2 & 3);
                int y = (DAT_UnitsState::instance.units[unitID].field97_0xd0 + SEC_RNG::instance.currentNumber2 & 3)
                    + DAT_BuildingsState::instance.buildings[keep].someY;
                if (MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::isAIPlayer,
                        DAT_GameSynchronyState::ptr)(DAT_UnitsState::instance.units[unitID].owner)
                        != FALSE
                    && DAT_UnitsState::instance.units[unitID].field97_0xd0 > 10) {
                    if (MACRO_CALL_MEMBER(
                            OpenSHC::Game::GameStateStructures_Func::checkKeepEnclosed, DAT_GameState::ptr)(owner)
                        == FALSE) {
                        if (DAT_GameState::instance.playerDataArray[owner].totalEnemyRangedTroopValue < 100
                            && DAT_GameState::instance.playerDataArray[owner].totalEnemyTroopValue < 200) {
                            x = DAT_GameState::instance.playerDataArray[owner].campground.xEntry;
                            y = DAT_GameState::instance.playerDataArray[owner].campground.yEntry;
                            int enemy = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                                            .lastEncounteredEnemyUnitIDUnk;
                            if (enemy != 0) {
                                MACRO_CALL_MEMBER(
                                    OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                                    DAT_DirectionAlgorithmState::ptr)(DAT_UnitsState::instance.units[enemy].x,
                                    DAT_UnitsState::instance.units[enemy].y, x, y);
                                if (DAT_DirectionAlgorithmState::instance.distanceHigh < 30) {
                                    // fight the enemy close to the campfire
                                    x = DAT_UnitsState::instance.units[enemy].x;
                                    y = DAT_UnitsState::instance.units[enemy].y;
                                }
                            }
                        }
                    } else {
                        x = DAT_GameState::instance.playerDataArray[owner].campground.xEntry;
                        y = DAT_GameState::instance.playerDataArray[owner].campground.yEntry;
                    }
                }
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit, DAT_UnitsState::ptr)(
                    DAT_CurrentUnitSlotID::instance, x, y, 0);
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].destinationNeeded
                    = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSheetFrameOffset = 1;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0x10;
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::hasUnitReachedDestination, DAT_UnitsState::ptr)(
                    DAT_CurrentUnitSlotID::instance)
                == FALSE) {
                return;
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].destinationNeeded
                != OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET) {
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic = (UnitState)13;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].updateTickTracker = 0;
            return;
        }
        if (state == (UnitState)13) {
            // waiting at the keep
            DAT_UnitsState::instance.units[unitID].animationSpeed = 2;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setUnitFacingDirectionForTargetXandY,
                DAT_UnitsState::ptr)(unitID, DAT_GameState::instance.playerDataArray[owner].keep.xEntry,
                DAT_GameState::instance.playerDataArray[owner].keep.yEntry);
            if (DAT_DirectionAlgorithmState::instance.orientation == 15) {
                DAT_DirectionAlgorithmState::instance.orientation = 4;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].facingDirection
                = (short)DAT_DirectionAlgorithmState::instance.orientation;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.field309_0x5fa0
                      [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame <= 0) {
                DAT_UnitHasBecomeIdle::instance = 1;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                          .facingDirectionMapOrientationCorrected
                    - spriteOffset + 0xa9;
            } else {
                int turn;
                if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame == 1) {
                    turn = 0;
                } else if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame == 2) {
                    turn = 1;
                } else if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame == 3) {
                    turn = 2;
                } else if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame == 4) {
                    turn = -1;
                } else {
                    turn = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame == 5 ? -2 : 0;
                }
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                          .facingDirectionMapOrientationCorrected
                    - spriteOffset + 0xa9 + turn;
                if (DAT_UnitHasBecomeIdle::instance == 0) {
                    return;
                }
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
            if (DAT_GameState::instance.playerDataArray[owner].totalEnemyUnitsCount > 0
                || DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY
                || DAT_GameState::instance.mapAndTime.field3171_0x27a8 != 0
                || DAT_GameState::instance.mapAndTime.field3172_0x27ac
                        + DAT_GameState::instance.mapAndTime.field3170_0x27a4
                    > 2) {
                int keep = DAT_GameState::instance.playerDataArray[owner].keep.id;
                if (keep == 0) {
                    return;
                }
                if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field97_0xd0 > 10
                    && MACRO_CALL_MEMBER(
                           OpenSHC::Game::GameStateStructures_Func::checkKeepEnclosed, DAT_GameState::ptr)(owner)
                        != FALSE) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].destinationNeeded
                        = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_NEEDED;
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                        = OpenSHC::Map::Units::States::US_IDLEUnk;
                    return;
                }
                if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field97_0xd0 > 10) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].destinationNeeded
                        = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_NEEDED;
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic = (UnitState)12;
                    return;
                }
                if ((short)DAT_TileMapState::instance
                        .BuildingLayer[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].tile]
                    == keep) {
                    return;
                }
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].destinationNeeded
                = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_NEEDED;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                = OpenSHC::Map::Units::States::US_IDLEUnk;
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_MOVE_TO_DESTINATION || state == (UnitState)120) {
            DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset = 1;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0x10;
            DAT_UnitsState::instance.units[unitID].movementSpeed = 2;
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::hasUnitReachedDestination, DAT_UnitsState::ptr)(
                    unitID)
                != FALSE) {
                DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
                if (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY) {
                    DAT_UnitsState::instance.units[unitID].state.generic = OpenSHC::Map::Units::States::US_IDLEUnk;
                }
                DAT_UnitsState::instance.units[unitID].destinationNeeded
                    = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_NEEDED;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::handleUnitMovementWhenTargetingBuildings,
                    DAT_UnitsState::ptr)(unitID)
                <= 0) {
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                = OpenSHC::Map::Units::States::US_MELEE_ATTACK_WALL;
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_MELEE_ATTACK_WALL) {
            DAT_UnitsState::instance.units[unitID].animationSpeed = 3;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            if (DAT_UnitsState::instance.units[unitID].animationCycleNumberHasJustIncremented != FALSE
                && DAT_UnitsState::instance.units[unitID].animationCycleNumber == 8) {
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    DAT_UnitsState::instance.units[unitID].x, DAT_UnitsState::instance.units[unitID].y,
                    OpenSHC::DE::SHCDE::FX_LORD_SWING);
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumberHasJustIncremented
                    != FALSE
                && DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber == 10) {
                int hurtSFX
                    = MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingHurtSFXID, DAT_TileMapState::ptr)(
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetedBuildingTile);
                if (hurtSFX == 1) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].x,
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].y,
                        OpenSHC::DE::SHCDE::FX_ATTACK_WOOD);
                } else if (hurtSFX == 2) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].x,
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].y,
                        OpenSHC::DE::SHCDE::FX_ATTACK_STONE);
                }
            }
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setUnitFacingDirectionForTargetXandY,
                DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance,
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].attackAtTileX,
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].attackAtTileY);
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate == 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.field315_0x6124
                          [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
            } else if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate == 1
                || DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate == 3) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.field316_0x614c
                          [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
            } else if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate == 2) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.field317_0x6170
                          [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame <= 0) {
                DAT_UnitHasBecomeIdle::instance = 1;
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                          .facingDirectionMapOrientationCorrected
                    + DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame * 8 - spriteOffset
                    + 0x1b9;
            }
            if (DAT_UnitHasBecomeIdle::instance == 0) {
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate += 1;
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate > 3) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate = 0;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].nextAttackHurtsWall += 1;
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].nextAttackHurtsWall > 1) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].nextAttackHurtsWall = 0;
            }
            int tile = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetedBuildingTile;
            int isWall = DAT_TileMapState::instance.LogicLayer[tile] & 0x100;
            int building;
            int damage;
            if (isWall == 0) {
                building = (short)DAT_TileMapState::instance.BuildingLayer[tile];
                if (building <= 0) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                        = DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY
                        ? OpenSHC::Map::Units::States::US_IDLEUnk
                        : OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
                    return;
                }
                damage = DAT_BuildingDefinedData::instance
                             .IsGateOrTowerArray[DAT_BuildingsState::instance.buildings[building].buildingType]
                        != FALSE
                    ? 6
                    : 70;
            } else {
                damage = 10;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::processDamageToBuildingThunk, DAT_TileMapState::ptr)(
                    tile, DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].attackAtTileX,
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].attackAtTileY, damage,
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].nextAttackHurtsWall,
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].owner, TRUE)
                != FALSE) {
                // the building has been destroyed
                if (isWall != 0
                    && MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationNearTargetedBuilding,
                           DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance, 1)
                        != 0) {
                    return;
                }
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetedBuildingTile = 0;
                if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::moveUnitToBehaviorTarget,
                        DAT_TribesState::ptr)(DAT_CurrentUnitSlotID::instance,
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                            .unknownDigMoatOrWallAttackFlag1015)
                    == 0) {
                    if (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY) {
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                            = OpenSHC::Map::Units::States::US_IDLEUnk;
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
                        return;
                    }
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                        = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
                    return;
                }
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
                return;
            }
            int attacker = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].owner;
            if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[attacker] == -1) {
                // AI players give up on walls that are too dangerous
                // TODO: the per player AttackInfo blocks (stride 0x177bc) and the byte tile layers at 0x01EE2998 are
                // not modelled yet
                int danger = *(
                    unsigned char*)(*(int*)((int)&DAT_TroopValueState::instance.attackInfo.unknownPlayerID_0x301c0
                                        + attacker * 0x177bc)
                        * 0x13a10
                    + 0x1ee2998 + DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetedBuildingTile);
                int tolerance = *(
                    int*)((int)&DAT_TroopValueState::instance.attackInfo.unknownDistance_0x34060 + attacker * 0x177bc);
                if (isWall == 0) {
                    if (DAT_BuildingDefinedData::instance
                                .IsGateOrTowerArray[DAT_BuildingsState::instance.buildings[building].buildingType]
                            != FALSE
                        && danger > tolerance + 10
                        && MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::moveUnitToBehaviorTarget,
                               DAT_TribesState::ptr)(DAT_CurrentUnitSlotID::instance,
                               DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                                   .unknownDigMoatOrWallAttackFlag1015)
                            == 0) {
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                            = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
                        return;
                    }
                } else if (danger > tolerance + 15
                    && MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationNearTargetedBuilding,
                           DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance, 1)
                        != 0) {
                    return;
                }
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
            return;
        }
        if (state == (UnitState)0x6c) {
            DAT_UnitsState::instance.units[unitID].stateBasedSpeed = 0;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset = 1;
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_JESTER_ROAM_TO) {
            DAT_UnitsState::instance.units[unitID].updateTickTracker = 0;
            DAT_UnitsState::instance.units[unitID].disappearFadeAlphaCountdown = 0;
            DAT_UnitsState::instance.units[unitID].state.generic = DAT_UnitsState::instance.units[unitID].cachedState;
            return;
        }
        if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::checkIfCitizenUnitIsAliveBasedOnState,
                DAT_UnitsState::ptr)(unitID)
            == FALSE) {
            if (state == OpenSHC::Map::Units::States::US_MELEE_ATTACK) {
                DAT_UnitsState::instance.units[unitID].animationSpeed = 2;
                DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
                if (DAT_UnitsState::instance.units[unitID].substate == 0) {
                    DAT_UnitsState::instance.units[unitID].animationFrame
                        = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp
                              .field315_0x6124[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
                } else if (DAT_UnitsState::instance.units[unitID].substate == 1) {
                    DAT_UnitsState::instance.units[unitID].animationFrame
                        = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp
                              .field316_0x614c[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
                } else if (DAT_UnitsState::instance.units[unitID].substate == 2) {
                    DAT_UnitsState::instance.units[unitID].animationFrame
                        = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp
                              .field317_0x6170[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
                } else if (DAT_UnitsState::instance.units[unitID].substate == 3) {
                    DAT_UnitsState::instance.units[unitID].animationFrame
                        = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp
                              .field316_0x614c[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
                }
                if (DAT_UnitsState::instance.units[unitID].animationFrame <= 0) {
                    DAT_UnitHasBecomeIdle::instance = 1;
                } else {
                    DAT_UnitsState::instance.units[unitID].gfxNumber
                        = DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected
                        + DAT_UnitsState::instance.units[unitID].animationFrame * 8 - spriteOffset + 0x1b9;
                }
                if (DAT_UnitsState::instance.units[unitID].animationCycleNumberHasJustIncremented != FALSE
                    && DAT_UnitsState::instance.units[unitID].animationCycleNumber == 7) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        DAT_UnitsState::instance.units[unitID].x, DAT_UnitsState::instance.units[unitID].y,
                        OpenSHC::DE::SHCDE::FX_LORD_SWING);
                    // warn the player that his lord is fighting
                    if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].owner
                            == DAT_GameSynchronyState::instance.currentPlayerSlotID
                        && timeGetTime() - DWORD_00ee105c::instance > 120000
                        && DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].attackedUnitID != 0
                        && DAT_UnitsState::instance
                                .units[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].attackedUnitID]
                                .isStalked
                            == 0
                        && DAT_UnitsState::instance
                                .units[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].attackedUnitID]
                                .state.generic
                            == OpenSHC::Map::Units::States::US_MELEE_ATTACK) {
                        MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                            "General_Warning12.wav");
                        DWORD_00ee105c::instance = timeGetTime();
                    }
                }
                if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].attackedUnitID != 0
                    && DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                            .animationCycleNumberHasJustIncremented
                        != FALSE) {
                    if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber == 12) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::Map::Units::UnitsState_Func::playHurtSFXForUnit, DAT_UnitsState::ptr)(
                            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].attackedUnitID);
                    }
                    if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber == 10
                        && DAT_UnitsState::instance
                                .units[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].attackedUnitID]
                                .unitType
                            == OpenSHC::Map::Units::UT_LORD) {
                        MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].x,
                            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].y,
                            OpenSHC::DE::SHCDE::FX_STEEL1);
                    }
                }
                if (DAT_UnitHasBecomeIdle::instance == 0) {
                    return;
                }
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate += 1;
                if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate > 3) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate = 0;
                }
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::resumeMovementIfNoAttackTarget,
                    DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance);
                return;
            }
            if (state != OpenSHC::Map::Units::States::US_DISAPPEAR) {
                return;
            }
            DAT_UnitsState::instance.units[unitID].disappearFadeAlphaCountdown += 1;
            if ((char)DAT_UnitsState::instance.units[unitID].disappearFadeAlphaCountdown > 32) {
                DAT_UnitsState::instance.units[unitID].disappearFadeAlphaCountdown = 32;
            }
            DAT_UnitsState::instance.units[unitID].updateTickTracker += 1;
            if (DAT_UnitsState::instance.units[unitID].updateTickTracker <= 32) {
                return;
            }
            DAT_UnitsState::instance.units[unitID].logicalState = OpenSHC::Map::Units::ULS_REMOVE;
            if (DAT_UnitsState::instance.units[unitID].killedFlagUnk == 0) {
                MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::processUnitLossStatistic,
                    DAT_GameState::ptr)(owner, unitID);
                if (owner == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                    DAT_GameState::instance.mapAndTime
                        .ownLossesArray[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                                .lastEncounteredEnemyPlayerID] += 1;
                } else if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].lastEncounteredEnemyPlayerID
                    == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                    DAT_GameState::instance.mapAndTime.emenyHitArray[owner] += 1;
                }
            }
            if (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY) {
                return;
            }
            // the player is defeated
            DAT_GameState::instance.playerDataArray[owner].lordKilledByPlayerID = 1;
            MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocationFullVolume, DAT_SFXState::ptr)(
                DAT_GameState::instance.playerDataArray[owner].keep.xEntry,
                DAT_GameState::instance.playerDataArray[owner].keep.yEntry, 0xf4);
            DAT_GameState::instance.playerDataArray[owner].someKeepRelatedX2
                = (short)DAT_GameState::instance.playerDataArray[owner].keep.xEntry;
            DAT_GameState::instance.playerDataArray[owner].commemorationShrinePlacementCountdown = 5;
            DAT_GameState::instance.playerDataArray[owner].someKeepRelatedY2
                = (short)DAT_GameState::instance.playerDataArray[owner].keep.yEntry;
            MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::destroyPlayerCompletely, DAT_GameState::ptr)(
                owner);
            if (owner != DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                return;
            }
            DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.tabType = OpenSHC::UI::Enums::BASMTT_HUNTERSHUT;
            MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                OpenSHC::UI::Enums::MVT_BUILD_MENU, 0);
            return;
        }
        // the lord is dying
        if (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY) {
            if (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_EDITOR) {
                for (int player = 1; player <= 8; ++player) {
                    if (owner != player && DAT_GameState::instance.playerDataArray[player].playerRelatedFlag == 0) {
                        DAT_GameState::instance.playerDataArray[player].playerRelatedFlag = 1;
                    }
                }
                if (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_BUILDERUnk
                    || DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 != OpenSHC::Map::MT_JUST_BUILD) {
                    DAT_GameState::instance.playerDataArray[owner].lordKilledByPlayerID = 10;
                    if (DAT_UnitsState::instance.units[unitID].lastEncounteredEnemyPlayerID != 0
                        && DAT_UnitsState::instance.units[unitID].lastEncounteredEnemyPlayerID
                            != DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                        DAT_GameState::instance.playerDataArray[owner].lordKilledByPlayerID
                            = DAT_UnitsState::instance.units[unitID].lastEncounteredEnemyPlayerID;
                    }
                }
            }
        } else if (DAT_UnitsState::instance.units[unitID].lordDeathProcessedStatus != 99) {
            DAT_UnitsState::instance.units[unitID].lordDeathProcessedStatus = 99;
            owner = DAT_UnitsState::instance.units[unitID].lastEncounteredEnemyPlayerID;
            int victim = DAT_UnitsState::instance.units[unitID].owner;
            DAT_GameSynchronyState::instance.finalResults.finalDateOfDeathInMonths[victim]
                = DAT_GameState::instance.mapAndTime.month + DAT_GameState::instance.mapAndTime.year * 12;
            if (owner != 0 && DAT_UnitsState::instance.units[unitID].killedFlagUnk == 0) {
                // the killer takes a part of the gold and goods of the victim
                int gold = DAT_GameState::instance.playerDataArray[victim].currentResources[15] * 25 / 100;
                if (gold < 500) {
                    gold = 500;
                } else if (gold > 100000) {
                    gold = 100000;
                }
                DAT_GameSynchronyState::instance.finalResults.finalKilledLords[owner] += 1;
                DAT_GameState::instance.playerDataArray[owner].currentResources[15] += gold;
                int looted = 0;
                for (int i = 0; i < 20; ++i) {
                    int resource = DAT_UnitPropertiesDefinedData::instance.field82_0x11c24[i];
                    int amount = DAT_GameState::instance.playerDataArray[victim].currentResources[resource] * 25 / 100;
                    DAT_GameState::instance.playerDataArray[owner].startResources[resource] += amount;
                    looted += amount;
                }
                if (looted > 0) {
                    DAT_GameState::instance.playerDataArray[owner].someCount47 = 0;
                    DAT_GameState::instance.playerDataArray[owner].someCount45 = 2;
                    DAT_GameState::instance.playerDataArray[owner].textYOffset = 60;
                    DAT_GameState::instance.playerDataArray[owner].someCountdown01 = 160;
                }
                DAT_GameSynchronyState::instance.finalResults.finalGold[owner] += gold;
                DAT_GameCore::instance.countdown = 1;
                if (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_CAMPAIGN_MISSION
                    || !(DAT_GameCore::instance.missionNumber1to20 == 19
                            ? victim == 3
                            : DAT_GameCore::instance.missionNumber1to20 == 17 && victim == 2)) {
                    strcpy(DAT_GameSynchronyState::instance.receivedChatMessage,
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MULTIPLAYER_CONNECTION, 40));
                    MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::addChatMessageToDisplayList,
                        DAT_GameSynchronyState::ptr)(
                        owner, DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].owner);
                    char* suffix = MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MULTIPLAYER_CONNECTION, 42);
                    char* prefix = MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MULTIPLAYER_CONNECTION, 41);
                    MACRO_CALL(OpenSHC::OS_Func::_sprintf)(
                        DAT_GameSynchronyState::instance.receivedChatMessage, "%s %d %s", prefix, gold, suffix);
                    MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::addChatMessageToDisplayList,
                        DAT_GameSynchronyState::ptr)(owner, 0);
                    MACRO_CALL_MEMBER(
                        OpenSHC::AI::AICState_Func::playPlayerKilledBiksFromKilledAndKillerPlayer, DAT_AICState::ptr)(
                        owner, DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].owner);
                }
            }
        }
        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].facingDirection = 0;
        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSpeed = 2;
        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
            = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp
                  .field18_0xb84[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
        if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame <= 0) {
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber = 0x2fc - spriteOffset;
            DAT_UnitHasBecomeIdle::instance = 1;
        } else {
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame - spriteOffset + 0x2e0;
        }
        if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumberHasJustIncremented
                != FALSE
            && DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber == 16) {
            if (owner == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                    "general_warning1.wav");
            } else if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].lastEncounteredEnemyPlayerID
                == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                int victorySpeech = SEC_RNG::instance.currentNumber1 % 3;
                if (victorySpeech == 0) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                        "general_victory3.wav");
                } else if (victorySpeech == 1) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                        "general_victory4.wav");
                } else if (victorySpeech == 2) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                        "general_victory5.wav");
                }
            }
        }
        if (DAT_UnitHasBecomeIdle::instance != 0) {
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                = OpenSHC::Map::Units::States::US_DISAPPEAR;
        }
    }

}
}
