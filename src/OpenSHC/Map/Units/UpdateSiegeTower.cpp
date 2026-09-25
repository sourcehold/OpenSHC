#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Units.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Random/RNG.func.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitInstructionType.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_AttackInfoDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentUnitSlotID.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"
#include "OpenSHC/Globals/TIME_LastSiegeTowerWarningMoment.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Commands::MappersEnum;
    using OpenSHC::Game::GameMode;
    using OpenSHC::Map::Units::UnitInstructionType;
    using OpenSHC::Map::Units::UnitLogicState;
    using OpenSHC::Map::Units::UnitType;
    using OpenSHC::Map::Units::States::UnitState;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x00544750
    void Units::UpdateSiegeTower()
    {
        int unitID = DAT_CurrentUnitSlotID::instance;
        int owner = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].owner;
        DAT_GameState::instance.playerDataArray[owner].armySize += 1;
        DAT_GameState::instance.playerDataArray[owner].currentSiegeWeaponCount += 1;
        DAT_UnitsState::instance.units[unitID].isSelectable_OR_matchTime = 1;
        DAT_UnitsState::instance.units[unitID].calculatedOwnerPlayerIndex = 0;
        DAT_UnitsState::instance.units[unitID].displayColorPlayerID = 0;
        DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset = 9;
        UnitStateShort state = DAT_UnitsState::instance.units[unitID].state.generic;
        if (state == OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk) {
            DAT_UnitsState::instance.units[unitID].substate = -1;
            DAT_UnitsState::instance.units[unitID].stateBasedSpeed = 0;
            if (DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected == 0
                || DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected == 6
                || DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected == 7) {
                DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 99;
                DAT_UnitsState::instance.units[unitID].gfxNumber
                    = (DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected + 4) % 8 + 0x49;
                DAT_UnitsState::instance.units[unitID].field59_0x86 = 0;
                DAT_UnitsState::instance.units[unitID].imageIDUnk
                    = DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected + 1;
                DAT_UnitsState::instance.units[unitID].field60_0x88 = 0;
                DAT_UnitsState::instance.units[unitID].imageID2
                    = DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected + 9;
                DAT_UnitsState::instance.units[unitID].drawYOffset = 0x47;
            } else {
                DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0x13;
                DAT_UnitsState::instance.units[unitID].gfxNumber
                    = DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected + 1;
                DAT_UnitsState::instance.units[unitID].field59_0x86 = 0;
                DAT_UnitsState::instance.units[unitID].imageIDUnk
                    = DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected + 9;
                DAT_UnitsState::instance.units[unitID].field60_0x88 = 0x47;
                DAT_UnitsState::instance.units[unitID].imageID2
                    = (DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected + 4) % 8 + 0x49;
                DAT_UnitsState::instance.units[unitID].drawYOffset = 0;
            }
            DAT_UnitsState::instance.units[unitID].state.generic
                = DAT_UnitsState::instance.units[unitID]
                        .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300
                    != 4
                ? OpenSHC::Map::Units::States::US_FIRE_WEAPONUnk
                : OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_FIRE_WEAPONUnk) {
            // waiting for engineers to man the tower
            DAT_UnitsState::instance.units[unitID].field39_0x58 = 0;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            if (DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected == 0
                || DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected == 6
                || DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected == 7) {
                DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 99;
                DAT_UnitsState::instance.units[unitID].gfxNumber
                    = (DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected + 4) % 8 + 0x49;
                DAT_UnitsState::instance.units[unitID].field59_0x86 = 0;
                DAT_UnitsState::instance.units[unitID].imageIDUnk
                    = DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected + 1;
                DAT_UnitsState::instance.units[unitID].field60_0x88 = 0;
                DAT_UnitsState::instance.units[unitID].imageID2
                    = DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected + 9;
                DAT_UnitsState::instance.units[unitID].drawYOffset = 0x47;
                DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
            } else {
                DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0x13;
                DAT_UnitsState::instance.units[unitID].gfxNumber
                    = DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected + 1;
                DAT_UnitsState::instance.units[unitID].field59_0x86 = 0;
                DAT_UnitsState::instance.units[unitID].imageIDUnk
                    = DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected + 9;
                DAT_UnitsState::instance.units[unitID].field60_0x88 = 0x47;
                DAT_UnitsState::instance.units[unitID].imageID2
                    = (DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected + 4) % 8 + 0x49;
                DAT_UnitsState::instance.units[unitID].drawYOffset = 0;
            }
            DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
            if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[DAT_UnitsState::instance.units[unitID].owner]
                    == -1
                && DAT_UnitsState::instance.units[unitID]
                        .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300
                    == 4) {
                // the AI's engineers have been moved away: check whether all are back
                int present = 0;
                for (int i = 0; i < 4; ++i) {
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
                if (present == 4) {
                    for (int i = 0; i < 4; ++i) {
                        int engineer
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
                    DAT_UnitsState::instance.units[unitID].state.generic
                        = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
                }
            }
            if (((DAT_UnitsState::instance.units[unitID].fixedRng
                     ^ DAT_GameState::instance.mapAndTime.totalGameTicksUnk)
                    & 15)
                    != 8
                || DAT_UnitsState::instance.units[unitID].state.generic
                    != OpenSHC::Map::Units::States::US_FIRE_WEAPONUnk) {
                return;
            }
            // look for four engineers of the same player next to the tower
            int crewCount[9] = { 0 };
            int crew[9][4];
            for (int i = 1; i < (int)DAT_UnitsState::instance.maxUnitCount; ++i) {
                if (DAT_UnitsState::instance.units[i].logicalState != OpenSHC::Map::Units::ULS_NORMAL
                    || DAT_UnitsState::instance.units[i].unitType != OpenSHC::Map::Units::UT_E_ENGINEER
                    || DAT_UnitsState::instance.units[i].targetingType != OpenSHC::Map::Units::UIT_MAN_SIEGE_EQUIPMENT
                    || DAT_UnitsState::instance.units[i].dying != 0
                    || DAT_UnitsState::instance.units[i].targetedUnitID__OR__engineerMannedSiegeEngineRef
                        != DAT_CurrentUnitSlotID::instance
                    || abs(DAT_UnitsState::instance.units[i].buildingHeight
                           - DAT_UnitsState::instance.units[unitID].buildingHeight
                           - DAT_UnitsState::instance.units[unitID].terrainOrClimbHeight
                           + DAT_UnitsState::instance.units[i].terrainOrClimbHeight)
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
                if ((dy < dx ? dx : dy) < 30 && crewCount[DAT_UnitsState::instance.units[i].owner] < 4) {
                    crew[DAT_UnitsState::instance.units[i].owner][crewCount[DAT_UnitsState::instance.units[i].owner]]
                        = i;
                    crewCount[DAT_UnitsState::instance.units[i].owner] += 1;
                }
            }
            int crewOwner = DAT_UnitsState::instance.units[unitID].owner;
            if (crewCount[crewOwner] != 4) {
                // the tower is captured by the engineers of another player
                crewOwner = 1;
                while (crewCount[crewOwner] != 4) {
                    crewOwner += 1;
                    if (crewOwner > 8) {
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
            for (int i = 0; i < 4; ++i) {
                int engineer = crew[crewOwner][i];
                DAT_UnitsState::instance.units[engineer].animationCycleNumber = 0;
                DAT_UnitsState::instance.units[engineer].state.generic = OpenSHC::Map::Units::States::US_JESTER_ROAM_TO;
                DAT_UnitsState::instance.units[engineer].disappearFadeAlphaCountdown = 0;
                DAT_UnitsState::instance.units[engineer].engineerManningSiegeStateRef_checkType = 2;
                DAT_UnitsState::instance.units[engineer].cachedState = OpenSHC::Map::Units::States::US_AIM_WEAPONUnk;
                DAT_UnitsState::instance.units[engineer].updateTickTracker = 0;
                DAT_UnitsState::instance.units[engineer].targetingType
                    = OpenSHC::Map::Units::UIT_NO_INSTRUCTION_OR_MOVEUnk;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].manningEngineerRef[i] = (short)engineer;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].manningEngineerUIDRef[i]
                    = DAT_UnitsState::instance.units[engineer].uid;
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::deselectUnit, DAT_UnitsState::ptr)(engineer);
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::clearOrDeselectUnitFromSelection,
                    DAT_UnitsState::ptr)(DAT_UnitsState::instance.units[engineer].owner, engineer, 0);
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300 = 4;
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_MOVE_TO_DESTINATION
            || state == OpenSHC::Map::Units::States::US_IDLEUnk) {
            if (DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected == 0
                || DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected == 6
                || DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected == 7) {
                DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 99;
                DAT_UnitsState::instance.units[unitID].gfxNumber
                    = (DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected + 4) % 8 + 0x49;
                DAT_UnitsState::instance.units[unitID].field59_0x86 = 0;
                DAT_UnitsState::instance.units[unitID].imageIDUnk
                    = DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected + 1;
                DAT_UnitsState::instance.units[unitID].field60_0x88 = 0;
                DAT_UnitsState::instance.units[unitID].drawYOffset = 0x47;
            } else {
                DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0x13;
                DAT_UnitsState::instance.units[unitID].gfxNumber
                    = DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected + 1;
                DAT_UnitsState::instance.units[unitID].field59_0x86 = 0;
                DAT_UnitsState::instance.units[unitID].field60_0x88 = 0x47;
                DAT_UnitsState::instance.units[unitID].imageID2
                    = (DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected + 4) % 8 + 0x49;
                DAT_UnitsState::instance.units[unitID].drawYOffset = 0;
            }
            DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset = 9;
            if (DAT_UnitsState::instance.units[unitID].moveInstructionSpeedDelayTracker == 0) {
                DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset = 9;
                DAT_UnitsState::instance.units[unitID].stateBasedSpeed = 1;
            } else if (DAT_UnitsState::instance.units[unitID].moveInstructionSpeedDelayTracker < 71) {
                DAT_UnitsState::instance.units[unitID].stateBasedSpeed = 0;
            } else {
                DAT_UnitsState::instance.units[unitID].stateBasedSpeed = -1;
                DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            }
            int current = DAT_CurrentUnitSlotID::instance;
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::hasUnitReachedDestination, DAT_UnitsState::ptr)(
                    current)
                == FALSE) {
                // keep looking for a better place at the wall
                if (DAT_UnitsState::instance.units[unitID].targetingType == OpenSHC::Map::Units::UIT_ATTACK_WALL
                    && ((DAT_UnitsState::instance.units[unitID].fixedRng
                            ^ DAT_GameState::instance.mapAndTime.totalGameTicksUnk)
                           & 7)
                        == 0
                    && MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::findFreeTileNearby, DAT_UnitsState::ptr)(
                           current, DAT_UnitsState::instance.units[unitID].targetedBuildingTile)
                        != DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].digTileTarget) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::Map::Units::UnitsState_Func::makeUnitStopWalkingByClearingPathProgressState,
                        DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance);
                }
                return;
            }
            if (DAT_UnitsState::instance.units[unitID].targetingType != OpenSHC::Map::Units::UIT_ATTACK_WALL) {
                DAT_UnitsState::instance.units[unitID].stateBasedSpeed = 0;
                DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
                DAT_UnitsState::instance.units[unitID].state.generic
                    = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
                DAT_UnitsState::instance.units[unitID].field248_0x3bc = 0;
                DAT_UnitsState::instance.units[unitID].targetedBuildingTile = 0;
                return;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::isAtSecondaryDestination, DAT_UnitsState::ptr)(
                    current)
                == FALSE) {
                if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit, DAT_UnitsState::ptr)(
                        current, DAT_UnitsState::instance.units[unitID].destinationX_2Unk,
                        DAT_UnitsState::instance.units[unitID].destinationY_2Unk, 0)
                    != FALSE) {
                    return;
                }
            } else if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::findFreeTileNearby, DAT_UnitsState::ptr)(
                           current, DAT_UnitsState::instance.units[current].targetedBuildingTile)
                == DAT_UnitsState::instance.units[current].digTileTarget) {
                // arrived at the wall
                DAT_UnitsState::instance.units[current].state.generic = OpenSHC::Map::Units::States::US_STAND_UPUnk;
                return;
            }
            int freeTile;
            int wallTile;
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::findAccessibleWallAndNearbyFreeTile,
                    DAT_PathFindingState::ptr)(DAT_CurrentUnitSlotID::instance,
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetedBuildingTile, &freeTile,
                    &wallTile)
                != FALSE) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit, DAT_UnitsState::ptr)(
                    DAT_CurrentUnitSlotID::instance,
                    freeTile
                        - DAT_ViewportRenderState::instance
                            .translationMatrix[DAT_ViewportRenderState::instance
                                    .tileTranslationMatrix_YComponent[freeTile]]
                            .addXgetTile,
                    DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[freeTile], 0);
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetingType
                    = OpenSHC::Map::Units::UIT_ATTACK_WALL;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = OpenSHC::Map::Units::States::US_MOVE_TO_DESTINATION;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetID_OR_targetBuildingID
                    = (short)wallTile;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetedBuildingTile = wallTile;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].digTileTarget = freeTile;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].attackAtTileY
                    = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[wallTile];
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].attackAtTileX = (short)wallTile
                    - (short)DAT_ViewportRenderState::instance
                          .translationMatrix[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                                  .attackAtTileY]
                          .addXgetTile;
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field248_0x3bc = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetingType
                = OpenSHC::Map::Units::UIT_NO_INSTRUCTION_OR_MOVEUnk;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetedBuildingTile = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].digTileTarget = 0;
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_STAND_UPUnk) {
            // docking at the wall
            DAT_UnitsState::instance.units[unitID].animationSpeed = 5;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[unitID].field39_0x58 = 0;
            if (DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected == 0
                || DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected == 6
                || DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected == 7) {
                DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 99;
                DAT_UnitsState::instance.units[unitID].gfxNumber
                    = (DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected + 4) % 8 + 0x49;
                DAT_UnitsState::instance.units[unitID].field59_0x86 = 0;
                DAT_UnitsState::instance.units[unitID].imageIDUnk
                    = DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected + 1;
                DAT_UnitsState::instance.units[unitID].field60_0x88 = 0;
                DAT_UnitsState::instance.units[unitID].imageID2
                    = DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected + 9;
                DAT_UnitsState::instance.units[unitID].drawYOffset = 0x47;
            } else {
                DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0x13;
                DAT_UnitsState::instance.units[unitID].gfxNumber
                    = DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected + 1;
                DAT_UnitsState::instance.units[unitID].field59_0x86 = 0;
                DAT_UnitsState::instance.units[unitID].imageIDUnk
                    = DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected + 9;
                DAT_UnitsState::instance.units[unitID].field60_0x88 = 0x47;
                DAT_UnitsState::instance.units[unitID].imageID2
                    = (DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected + 4) % 8 + 0x49;
                DAT_UnitsState::instance.units[unitID].drawYOffset = 0;
            }
            if (DAT_UnitsState::instance.units[unitID].animationCycleNumberHasJustIncremented == FALSE) {
                return;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setUnitFacingDirectionForTargetXandY,
                    DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance,
                    DAT_UnitsState::instance.units[unitID].attackAtTileX,
                    DAT_UnitsState::instance.units[unitID].attackAtTileY)
                != FALSE) {
                return;
            }
            int current = DAT_CurrentUnitSlotID::instance;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic = (UnitState)9;
            // warn the player whose wall is attacked
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].owner
                    != DAT_GameSynchronyState::instance.currentPlayerSlotID
                && DAT_GameSynchronyState::instance.currentPlayerSlotID
                    == (DAT_TileMapState::instance.WallOwnerLayer
                               [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetedBuildingTile]
                           & 7)
                        + 1
                && timeGetTime() - TIME_LastSiegeTowerWarningMoment::instance > 60000) {
                if (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY
                    || DAT_GameState::instance.mapAndTime
                            .playerTeams[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].owner]
                        != DAT_GameState::instance.mapAndTime
                            .playerTeams[DAT_GameSynchronyState::instance.currentPlayerSlotID]) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                        "General_Warning5.wav");
                }
                TIME_LastSiegeTowerWarningMoment::instance = timeGetTime();
            }
            if (DAT_GameSynchronyState::instance
                    .currentPlayerFullIDArray[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].owner]
                == -1) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::removeUnitFromTribe, DAT_TribesState::ptr)(
                    current, DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].tribeID);
            } else {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::deselectUnit, DAT_UnitsState::ptr)(current);
                MACRO_CALL_MEMBER(
                    OpenSHC::Map::Units::UnitsState_Func::clearOrDeselectUnitFromSelection, DAT_UnitsState::ptr)(
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].owner, current, 0);
                int offsetIndex = SEC_RNG::instance.currentNumber2 % 16;
                MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
                // the engineers leave the tower
                for (int i = 0; i < 4; ++i) {
                    int engineer
                        = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].manningEngineerRef[i];
                    if (DAT_UnitsState::instance.units[engineer].uid
                        != DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].manningEngineerUIDRef[i]) {
                        continue;
                    }
                    DAT_UnitsState::instance.units[engineer].field249_0x3c0 = 0;
                    DAT_UnitsState::instance.units[engineer].field248_0x3bc = 0;
                    DAT_UnitsState::instance.units[engineer].animationCycleNumber = 0;
                    DAT_UnitsState::instance.units[engineer].state.generic
                        = OpenSHC::Map::Units::States::US_JESTER_ROAM_TO;
                    DAT_UnitsState::instance.units[engineer].disappearFadeAlphaCountdown = 32;
                    DAT_UnitsState::instance.units[engineer].engineerManningSiegeStateRef_checkType = 0xfe;
                    DAT_UnitsState::instance.units[engineer].cachedState
                        = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
                    DAT_UnitsState::instance.units[engineer].updateTickTracker = 0;
                    DAT_UnitsState::instance.units[engineer].field39_0x58 = 1;
                    DAT_UnitsState::instance.units[engineer].totalSizeOfPathPlan = 0;
                    DAT_UnitsState::instance.units[engineer].unknownMovementRelated_0x2d2 = 0;
                    int attempts = 0;
                    int tile = 0;
                    int x;
                    int y;
                    while (tile == 0) {
                        int dx = DAT_AttackInfoDefinedData::instance.field10_0xec[offsetIndex][0];
                        int dy = DAT_AttackInfoDefinedData::instance.field10_0xec[offsetIndex][1];
                        offsetIndex = (offsetIndex + 1) % 16;
                        MACRO_CALL_MEMBER(
                            OpenSHC::Map::Navigation::PathFindingState_Func::findWalkableTileThatDoesNotContainUnit,
                            DAT_PathFindingState::ptr)(current,
                            dx + DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].x,
                            dy + DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].y, 1);
                        tile = DAT_PathFindingState::instance.ALG_ResultTile;
                        y = DAT_PathFindingState::instance.ALG_ResultY;
                        x = DAT_PathFindingState::instance.ALG_ResultX;
                        if (tile != 0) {
                            break;
                        }
                        MACRO_CALL_MEMBER(
                            OpenSHC::Map::Navigation::PathFindingState_Func::findWalkableTileThatDoesNotContainUnit,
                            DAT_PathFindingState::ptr)(DAT_CurrentUnitSlotID::instance,
                            DAT_PathFindingState::instance.ALG_ResultX, DAT_PathFindingState::instance.ALG_ResultY, 0);
                        x = DAT_PathFindingState::instance.ALG_ResultX;
                        y = DAT_PathFindingState::instance.ALG_ResultY;
                        tile = DAT_PathFindingState::instance.ALG_ResultTile;
                        if (tile != 0) {
                            break;
                        }
                        attempts += 1;
                        if (attempts == 16) {
                            tile = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].tile;
                            y = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].y;
                            x = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].x;
                        }
                    }
                    DAT_UnitsState::instance.units[engineer].terrainOrClimbHeight
                        = DAT_TileMapState::instance.HeightLayer[tile];
                    DAT_UnitsState::instance.units[engineer].x = (short)x;
                    DAT_UnitsState::instance.units[engineer].mimicCurrentXPosition = (short)x;
                    DAT_UnitsState::instance.units[engineer].tile = tile;
                    DAT_UnitsState::instance.units[engineer].nextTileUnk = tile;
                    DAT_UnitsState::instance.units[engineer].y = (short)y;
                    DAT_UnitsState::instance.units[engineer].mimicCurrentYPosition = (short)y;
                    DAT_UnitsState::instance.units[engineer].microXPosition = (short)(x * 8 + 4);
                    DAT_UnitsState::instance.units[engineer].microYPosition = (short)(y * 8 + 4);
                    MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::updateMicroPosition, DAT_UnitsState::ptr)(
                        engineer);
                    MACRO_CALL_MEMBER(
                        OpenSHC::Map::Units::UnitsState_Func::resetUnitMovementState, DAT_UnitsState::ptr)(engineer);
                    DAT_UnitsState::instance.units[engineer].animationSheetFrameOffset = 1;
                    DAT_UnitsState::instance.units[engineer].field_0x30_animRelated = 0x10;
                }
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                    .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300 = 0;
            }
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::placeBuilding, DAT_TileMapState::ptr)((PlayerID)owner,
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].x - 1,
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].y - 1,
                OpenSHC::Commands::M_MAPPER_SIEGE_TOWER_BASE, 3, 15);
            int towerBase = DAT_TileMapState::instance.placedBuildingID;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].workplaceBuildingID_1 = (short)towerBase;
            DAT_BuildingsState::instance.buildings[towerBase].unitRefID = (short)DAT_CurrentUnitSlotID::instance;
            DAT_BuildingsState::instance.buildings[towerBase].unitRefUID
                = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].uid;
            return;
        }
        if (state == (UnitState)9) {
            // docked
            DAT_UnitsState::instance.units[unitID].field43_0x64 = 2;
            DAT_UnitsState::instance.units[unitID].animationSpeed = 5;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[unitID].field39_0x58 = 0;
            if (DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected == 0
                || DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected == 6
                || DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected == 7) {
                DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 99;
                DAT_UnitsState::instance.units[unitID].gfxNumber
                    = DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected / 2 + 0x51;
                DAT_UnitsState::instance.units[unitID].field59_0x86 = -0x33;
                DAT_UnitsState::instance.units[unitID].imageIDUnk
                    = DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected + 1;
                DAT_UnitsState::instance.units[unitID].field60_0x88 = 0;
                DAT_UnitsState::instance.units[unitID].imageID2
                    = DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected + 9;
                DAT_UnitsState::instance.units[unitID].drawYOffset = 0x47;
            } else {
                DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0x13;
                DAT_UnitsState::instance.units[unitID].gfxNumber
                    = DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected + 1;
                DAT_UnitsState::instance.units[unitID].field59_0x86 = 0;
                DAT_UnitsState::instance.units[unitID].imageIDUnk
                    = DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected + 9;
                DAT_UnitsState::instance.units[unitID].field60_0x88 = 0x47;
                DAT_UnitsState::instance.units[unitID].imageID2
                    = DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected / 2 + 0x51;
                DAT_UnitsState::instance.units[unitID].drawYOffset = -0x33;
            }
            DAT_GameState::instance.playerDataArray[owner].countEntities -= 1;
            DAT_UnitsState::instance.units[unitID].isSelectable_OR_matchTime = 0;
            DAT_GameState::instance.playerDataArray[owner].armySize -= 1;
            DAT_BuildingsState::instance.buildings[DAT_UnitsState::instance.units[unitID].workplaceBuildingID_1]
                .currentHealth = (short)(DAT_BuildingsState::instance
                                             .buildings[DAT_UnitsState::instance.units[unitID].workplaceBuildingID_1]
                                             .maxHealth
                * DAT_UnitsState::instance.units[unitID].health / DAT_UnitsState::instance.units[unitID].maxHealth);
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_DEATH_01 || state == OpenSHC::Map::Units::States::US_DEATH_03
            || state == OpenSHC::Map::Units::States::US_STONE_DEATH_01) {
            DAT_UnitsState::instance.units[unitID].animationSpeed = 10000;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[unitID].gfxNumber = 0x55;
            DAT_UnitsState::instance.units[unitID].field59_0x86 = 0x10;
            DAT_UnitsState::instance.units[unitID].imageIDUnk = 0;
            DAT_UnitsState::instance.units[unitID].imageID2 = 0;
            if (DAT_UnitsState::instance.units[unitID].animationCycleNumber == 0
                && DAT_UnitsState::instance.units[unitID].killedFlagUnk == 0) {
                // the crew dies with the tower
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
            if (DAT_UnitsState::instance.units[unitID].animationCycleNumber <= 20) {
                return;
            }
            DAT_UnitsState::instance.units[unitID].logicalState = OpenSHC::Map::Units::ULS_REMOVE;
            if (DAT_UnitsState::instance.units[unitID].workplaceBuildingID_1 != 0) {
                DAT_TileMapState::instance.showNoRubbleWhenDestroyingBuilding = 1;
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::destroyBuildingAndLinkedDuplicates,
                    DAT_BuildingsState::ptr)(DAT_UnitsState::instance.units[unitID].workplaceBuildingID_1);
            }
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_DISAPPEAR
            || state == OpenSHC::Map::Units::States::US_JESTER_ROAM_TO) {
            DAT_UnitsState::instance.units[unitID].logicalState = OpenSHC::Map::Units::ULS_REMOVE;
            if (DAT_UnitsState::instance.units[unitID].killedFlagUnk == 0
                && DAT_UnitsState::instance.units[unitID]
                        .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300
                    == 4) {
                MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::processUnitLossStatistic,
                    DAT_GameState::ptr)(owner, DAT_CurrentUnitSlotID::instance);
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].workplaceBuildingID_1 != 0) {
                DAT_TileMapState::instance.showNoRubbleWhenDestroyingBuilding = 1;
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::destroyBuildingAndLinkedDuplicates,
                    DAT_BuildingsState::ptr)(
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].workplaceBuildingID_1);
            }
        }
    }

}
}
