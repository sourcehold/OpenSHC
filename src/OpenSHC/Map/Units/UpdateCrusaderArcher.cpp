#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Entities/EntityState.func.hpp"
#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Units.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"
#include "OpenSHC/DE/SHCDE/eSFX.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Map/Entities/EntityType.hpp"
#include "OpenSHC/Map/Units/Behavior/UnitStanceEnum.hpp"
#include "OpenSHC/Map/Units/SomeTribeBehaviorType.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitInstructionType.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentUnitSlotID.hpp"
#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_UnitHasBecomeIdle.hpp"
#include "OpenSHC/Globals/DAT_UnitPropertiesDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::DE::SHCDE::eSFX;
    using OpenSHC::Game::GameMode;
    using OpenSHC::Game::GameMode2;
    using OpenSHC::Map::Entities::EntityType;
    using OpenSHC::Map::Units::SomeTribeBehaviorType;
    using OpenSHC::Map::Units::UnitInstructionType;
    using OpenSHC::Map::Units::UnitLogicState;
    using OpenSHC::Map::Units::Behavior::UnitStanceEnum;
    using OpenSHC::Map::Units::States::UnitState;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x0055A800
    void Units::UpdateCrusaderArcher()
    {
        int unitID = DAT_CurrentUnitSlotID::instance;
        int owner = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].owner;
        DAT_GameState::instance.playerDataArray[owner].armySize += 1;
        DAT_GameState::instance.playerDataArray[owner].currentArchers += 1;
        if (DAT_UnitsState::instance.units[unitID].isSelectable_OR_matchTime == 0) {
            DAT_UnitsState::instance.units[unitID].isSelectable_OR_matchTime
                = (short)DAT_GameCore::instance.mapTimeInTicks;
        }
        DAT_UnitsState::instance.units[unitID].field316_0x430 = 1;
        MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::addUnitToNewTribe, DAT_TribesState::ptr)(unitID);
        if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetingType
                == OpenSHC::Map::Units::UIT_LIGHT_PITCH
            && DAT_TileMapState::instance
                    .pitchDitches[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                            .targetID_OR_targetBuildingID]
                    .state
                > 1) {
            // the pitch is already burning
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetingType
                = OpenSHC::Map::Units::UIT_NO_INSTRUCTION_OR_MOVEUnk;
        }
        switch (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic) {
        case OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk:
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate = -1;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed = 0;
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].isDisappearingUnk != 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].disappearFadeAlphaCountdown -= 1;
                if ((char)DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].disappearFadeAlphaCountdown
                    >= 0) {
                    return;
                }
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].disappearFadeAlphaCountdown = 0;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].isDisappearingUnk = 0;
                return;
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].goToRallyPoint != 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].goToRallyPoint = 0;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic = (UnitState)0x69;
                if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::isSpaceAvailableAtUnitRallyPoint,
                        DAT_BuildingsState::ptr)(owner, 0, DAT_CurrentUnitSlotID::instance)
                    != 0) {
                    MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit, DAT_UnitsState::ptr)(
                        DAT_CurrentUnitSlotID::instance, DAT_BuildingsState::instance.DAT_TempXOffset,
                        DAT_BuildingsState::instance.DAT_TempYOffset, 0);
                }
                DAT_GameState::instance.playerDataArray[owner].rallySearchOffsetsUnk[0] += 1;
                return;
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetingType
                == OpenSHC::Map::Units::UIT_DIG_MOAT) {
                int moat = MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::findNearestFriendlyMoatTileForDigging,
                    DAT_TileMapState::ptr)(owner, DAT_CurrentUnitSlotID::instance, 1);
                if (moat > -1) {
                    MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setXYBasedOnMoatID, DAT_TileMapState::ptr)(moat,
                        1, DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].x,
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].y);
                    DAT_PathFindingState::instance.climbIsIllegal = 1;
                    if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit,
                            DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance,
                            DAT_TileMapState::instance.ALG_MoatXResult, DAT_TileMapState::instance.ALG_MoatYResult, 0)
                        != FALSE) {
                        MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::changeDestinationByAmount,
                            DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance, 1);
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                            .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300
                            = (short)DAT_TileMapState::instance.ALG_MoatXResult;
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                            .digTileY__OR__countLifeCycleEngineersSentToManSiegeEngine
                            = (short)DAT_TileMapState::instance.ALG_MoatYResult;
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].digTileTarget = moat;
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic = (UnitState)124;
                        return;
                    }
                    DAT_TileMapState::instance.moats[moat].someCountDown -= 20;
                }
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetingType
                    = OpenSHC::Map::Units::UIT_NO_INSTRUCTION_OR_MOVEUnk;
            } else if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetingType
                == OpenSHC::Map::Units::UIT_FILL_MOAT) {
                int moat = MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::findNearestFriendlyMoatTileForDigging,
                    DAT_TileMapState::ptr)(owner, DAT_CurrentUnitSlotID::instance, 2);
                if (moat > -1) {
                    MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setXYBasedOnMoatID, DAT_TileMapState::ptr)(moat,
                        1, DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].x,
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].y);
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                        .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300
                        = (short)DAT_TileMapState::instance.ALG_MoatXResult;
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                        .digTileY__OR__countLifeCycleEngineersSentToManSiegeEngine
                        = (short)DAT_TileMapState::instance.ALG_MoatYResult;
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].digTileTarget = moat;
                    if (MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setXYBasedOnMoatID, DAT_TileMapState::ptr)(
                            moat, 2, DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].x,
                            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].y)
                        != 0) {
                        if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit,
                                DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance,
                                DAT_TileMapState::instance.ALG_MoatXResult, DAT_TileMapState::instance.ALG_MoatYResult,
                                0)
                            != FALSE) {
                            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
                            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                                = OpenSHC::Map::Units::States::US_DIG;
                            return;
                        }
                        DAT_TileMapState::instance.moats[moat].someCountDown -= 20;
                    } else {
                        DAT_TileMapState::instance.moats[moat].someCountDown -= 20;
                    }
                }
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetingType
                    = OpenSHC::Map::Units::UIT_NO_INSTRUCTION_OR_MOVEUnk;
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetingType
                        != OpenSHC::Map::Units::UIT_UNIT_ATTACK_UNIT
                    && DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetingType
                        != OpenSHC::Map::Units::UIT_ATTACK_BUILDING
                    && DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetingType
                        != OpenSHC::Map::Units::UIT_LIGHT_PITCH
                    && DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetingType
                        != OpenSHC::Map::Units::UIT_ATTACK_LAND
                || MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::acquireShootTarget, DAT_UnitsState::ptr)(
                       DAT_CurrentUnitSlotID::instance)
                    == FALSE) {
                if (DAT_GameState::instance.playerDataArray[owner].aiControlStatusRelated > 0
                    && (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].closestEnemyMicroDistance > 400
                        || DAT_GameState::instance.playerDataArray[owner].aiControlStatusRelated == 100000)) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                        = OpenSHC::Map::Units::States::US_LOOK_AROUNDUnk;
                    return;
                }
                if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].closestEnemyMicroDistance > 400) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                        = OpenSHC::Map::Units::States::US_SIT_DOWNUnk;
                    return;
                }
                if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].closestEnemyMicroDistance > 432
                    || MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::acquireShootTarget, DAT_UnitsState::ptr)(
                           DAT_CurrentUnitSlotID::instance)
                        == FALSE) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                        = OpenSHC::Map::Units::States::US_STAND_UPUnk;
                    return;
                }
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                == OpenSHC::Map::Units::States::US_MOVE_TO_DESTINATION) {
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                = OpenSHC::Map::Units::States::US_RELOAD_WEAPONUnk;
            MACRO_CALL_MEMBER(
                OpenSHC::Map::Units::UnitsState_Func::ifOnADefensiveStructureSetDestinationInDirectionOfTarget,
                DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance);
            return;
        case (UnitState)0x69:
            // gathering at the rally point
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSheetFrameOffset = 1;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0x10;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].calculatedMovementSpeed
                = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].movementSpeed;
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::hasUnitReachedDestination, DAT_UnitsState::ptr)(
                    DAT_CurrentUnitSlotID::instance)
                != FALSE) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].facingDirection = 4;
                if ((DAT_GameCore::instance.mapTimeInTicks + DAT_CurrentUnitSlotID::instance) % 40 == 0) {
                    if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].closestEnemyMicroDistance < 433
                        && MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::acquireShootTarget,
                               DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance)
                            != FALSE) {
                        DAT_GameState::instance.playerDataArray[owner].rallySearchOffsetsUnk[0] += 1;
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                            = OpenSHC::Map::Units::States::US_RELOAD_WEAPONUnk;
                        return;
                    }
                    if (MACRO_CALL_MEMBER(
                            OpenSHC::Map::Buildings::BuildingsState_Func::isSpaceAvailableAtUnitRallyPoint,
                            DAT_BuildingsState::ptr)(owner, 0, DAT_CurrentUnitSlotID::instance)
                        != 0) {
                        MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit,
                            DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance,
                            DAT_BuildingsState::instance.DAT_TempXOffset, DAT_BuildingsState::instance.DAT_TempYOffset,
                            0);
                    }
                }
            }
            DAT_GameState::instance.playerDataArray[owner].rallySearchOffsetsUnk[0] += 1;
            return;
        case (UnitState)2:
        case OpenSHC::Map::Units::States::US_MOVE_TO_DESTINATION:
        case (UnitState)123:
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0x10;
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].moveInstructionSpeedDelayTracker == 0) {
                if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].movementRunUpTime != 0) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSheetFrameOffset = 1;
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed = 0;
                } else if (DAT_TribesState::instance
                               .tribes[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].tribeID]
                               .isRallyingUnk
                    != 0) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSheetFrameOffset = 1;
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed = 0;
                } else if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].isMatchingSpeed != false) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSheetFrameOffset = 1;
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed = 0;
                } else {
                    // running
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSheetFrameOffset = 0x81;
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed = 1;
                }
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSheetFrameOffset = 1;
                if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].moveInstructionSpeedDelayTracker
                    < 71) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed = 0;
                } else {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed = -1;
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
                }
            }
            if ((DAT_TribesState::instance
                            .tribes[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].tribeID]
                            .isRallyingUnk
                        != 0
                    || DAT_GameSynchronyState::instance.currentPlayerFullIDArray[owner] == -1)
                && DAT_TribesState::instance
                        .tribes[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].tribeID]
                        .unitStance
                    != OpenSHC::Map::Units::Behavior::USE_STAND_GROUND
                && DAT_CurrentUnitSlotID::instance
                    == DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].selectionTargetUnitID
                && ((DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].fixedRng
                        ^ DAT_GameState::instance.mapAndTime.totalGameTicksUnk)
                       & 31)
                    == 0
                && MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::acquireShootTarget, DAT_UnitsState::ptr)(
                       DAT_CurrentUnitSlotID::instance)
                    != FALSE
                && DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].shootTargetedUnit > 0) {
                // the leader of a moving group shoots at an enemy: the whole group shoots
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::giveTribeAnInstruction, DAT_TribesState::ptr)(
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].tribeID,
                    OpenSHC::Map::Units::UIT_SHOOT_TARGETUnk,
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].shootTargetedUnit,
                    DAT_UnitsState::instance
                        .units[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].shootTargetedUnit]
                        .uid,
                    0);
                return;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::hasUnitReachedDestination, DAT_UnitsState::ptr)(
                    DAT_CurrentUnitSlotID::instance)
                != FALSE) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed = 0;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
                if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field143_0x2c4 == 123) {
                    MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::moveToFreeTileNearby, DAT_UnitsState::ptr)(
                        DAT_CurrentUnitSlotID::instance);
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                        = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                            != OpenSHC::Map::Units::States::US_MOVE_TO_DESTINATION
                        ? OpenSHC::Map::Units::States::US_RELOAD_WEAPONUnk
                        : (UnitState)123;
                }
                if (DAT_TribesState::instance
                        .tribes[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].tribeID]
                        .tribeBehaviorType
                    == OpenSHC::Map::Units::STBT_0x400) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                        = OpenSHC::Map::Units::States::US_DISAPPEAR;
                }
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::handleUnitMovementWhenTargetingBuildings,
                    DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance)
                <= 0) {
                return;
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].unknownDigMoatOrWallAttackFlag1015
                != 0x3f7) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = OpenSHC::Map::Units::States::US_MELEE_ATTACK_WALL;
                return;
            }
            // arrived at a moat to fill
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].digTileTarget
                = MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::returnOwnedMoatAtTile, DAT_TileMapState::ptr)(
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetedBuildingTile);
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].digTileTarget != 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = OpenSHC::Map::Units::States::US_DIG;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                    .digTileY__OR__countLifeCycleEngineersSentToManSiegeEngine
                    = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent
                          [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetedBuildingTile];
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                    .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300
                    = (short)DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetedBuildingTile
                    - (short)DAT_ViewportRenderState::instance
                          .translationMatrix[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                                  .digTileY__OR__countLifeCycleEngineersSentToManSiegeEngine]
                          .addXgetTile;
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
            return;
        case OpenSHC::Map::Units::States::US_APPEAR: {
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0x10;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSheetFrameOffset = 1;
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].moveInstructionSpeedDelayTracker == 0
                || DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].moveInstructionSpeedDelayTracker
                    < 71) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed = 0;
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed = -1;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::hasUnitReachedDestination, DAT_UnitsState::ptr)(
                    DAT_CurrentUnitSlotID::instance)
                == FALSE) {
                return;
            }
            // arrived at the map edge: jump to the actual appear tile
            int tile = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                           .targetedUnitUIDUnk_OR_someAppearTileUnk_OR_buildingUID_OR_pitchDitchUID_OR_entityUID;
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setPositionOfUnit, DAT_UnitsState::ptr)(
                DAT_CurrentUnitSlotID::instance,
                tile
                    - DAT_ViewportRenderState::instance
                        .translationMatrix[DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile]]
                        .addXgetTile,
                DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile],
                DAT_TileMapState::instance.HeightLayer[tile]);
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit, DAT_UnitsState::ptr)(
                DAT_CurrentUnitSlotID::instance,
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].plannedDestinationX,
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].plannedDestinationY, 0);
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                = OpenSHC::Map::Units::States::US_MOVE_TO_DESTINATION;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].fadeType = 1;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].fadeCounter = 0;
            return;
        }
        case OpenSHC::Map::Units::States::US_MELEE_ATTACK_WALL: {
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSpeed = 3;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setUnitFacingDirectionForTargetXandY,
                DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance,
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].attackAtTileX,
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].attackAtTileY);
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.field31_0xf84
                      [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame <= 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                          .facingDirectionMapOrientationCorrected
                    + 0x319;
                DAT_UnitHasBecomeIdle::instance = 1;
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                          .facingDirectionMapOrientationCorrected
                    + 0x311 + DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame * 8;
            }
            if (DAT_UnitHasBecomeIdle::instance == 0) {
                return;
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
                        = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
                    return;
                }
                damage = DAT_BuildingDefinedData::instance
                             .IsGateOrTowerArray[DAT_BuildingsState::instance.buildings[building].buildingType]
                        != FALSE
                    ? 1
                    : 4;
            } else {
                damage = 2;
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
        case (UnitState)12:
        case (UnitState)124: {
            // digging a moat
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic = (UnitState)124;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0x10;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSheetFrameOffset = 1;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed = 0;
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::hasUnitReachedDestination, DAT_UnitsState::ptr)(
                    DAT_CurrentUnitSlotID::instance)
                == FALSE) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
                return;
            }
            if (MACRO_CALL_MEMBER(
                    OpenSHC::Rendering::ViewportRenderState_Func::xyAreValid, DAT_ViewportRenderState::ptr)(
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                        .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300,
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                        .digTileY__OR__countLifeCycleEngineersSentToManSiegeEngine)
                == FALSE) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
                return;
            }
            int tile = DAT_ViewportRenderState::instance
                           .translationMatrix[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                                   .digTileY__OR__countLifeCycleEngineersSentToManSiegeEngine]
                           .addXgetTile
                + DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                      .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSpeed = 3;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::calculateOrientation,
                DAT_DirectionAlgorithmState::ptr)(DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].x,
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].y,
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                    .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300,
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                    .digTileY__OR__countLifeCycleEngineersSentToManSiegeEngine);
            if (DAT_DirectionAlgorithmState::instance.orientation != 15) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].facingDirection
                    = (short)DAT_DirectionAlgorithmState::instance.orientation;
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber == 5
                && DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                        .animationCycleNumberHasJustIncremented
                    != FALSE) {
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].x,
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].y, OpenSHC::DE::SHCDE::FX_MOAT_DIG);
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.field100_0x1dd0
                      [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame <= 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                          .facingDirectionMapOrientationCorrected
                    + 0x419;
                DAT_UnitHasBecomeIdle::instance = 1;
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                          .facingDirectionMapOrientationCorrected
                    + 0x411 + DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame * 8;
            }
            if ((DAT_TileMapState::instance.LogicLayer[tile] & 0x40000000) != 0
                || ((short)DAT_TileMapState::instance.UnitLayer[tile] != 0
                    && DAT_UnitsState::instance.units[(short)DAT_TileMapState::instance.UnitLayer[tile]].someUnitStat4
                        == 0)) {
                // the tile is already dug or occupied
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
                return;
            }
            if (DAT_UnitHasBecomeIdle::instance == 0) {
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
            if (MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::advanceMoatDigProgress, DAT_TileMapState::ptr)(
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].digTileTarget)
                == 1) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
            }
            return;
        }
        case (UnitState)13:
        case OpenSHC::Map::Units::States::US_DIG: {
            // filling a moat
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                = OpenSHC::Map::Units::States::US_DIG;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0x10;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSheetFrameOffset = 1;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed = 0;
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::hasUnitReachedDestination, DAT_UnitsState::ptr)(
                    DAT_CurrentUnitSlotID::instance)
                == FALSE) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
                return;
            }
            if (MACRO_CALL_MEMBER(
                    OpenSHC::Rendering::ViewportRenderState_Func::xyAreValid, DAT_ViewportRenderState::ptr)(
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                        .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300,
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                        .digTileY__OR__countLifeCycleEngineersSentToManSiegeEngine)
                == FALSE) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
                return;
            }
            int tile = DAT_ViewportRenderState::instance
                           .translationMatrix[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                                   .digTileY__OR__countLifeCycleEngineersSentToManSiegeEngine]
                           .addXgetTile
                + DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                      .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSpeed = 3;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::calculateOrientation,
                DAT_DirectionAlgorithmState::ptr)(DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].x,
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].y,
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                    .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300,
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                    .digTileY__OR__countLifeCycleEngineersSentToManSiegeEngine);
            if (DAT_DirectionAlgorithmState::instance.orientation != 15) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].facingDirection
                    = (short)DAT_DirectionAlgorithmState::instance.orientation;
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber == 5
                && DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                        .animationCycleNumberHasJustIncremented
                    != FALSE) {
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].x,
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].y, OpenSHC::DE::SHCDE::FX_MOAT_DIG);
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.field101_0x1df8
                      [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame <= 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                          .facingDirectionMapOrientationCorrected
                    + 0x419;
                DAT_UnitHasBecomeIdle::instance = 1;
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                          .facingDirectionMapOrientationCorrected
                    + 0x411 + DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame * 8;
            }
            if ((DAT_TileMapState::instance.LogicLayer[tile] & 0x40000000) == 0) {
                // the moat is already filled
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetedBuildingTile = 0;
                if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::moveUnitToBehaviorTarget,
                        DAT_TribesState::ptr)(DAT_CurrentUnitSlotID::instance,
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                            .unknownDigMoatOrWallAttackFlag1015)
                    == 0) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                        = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
                }
                return;
            }
            if (DAT_UnitHasBecomeIdle::instance == 0) {
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
            if (MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::removeMoat, DAT_TileMapState::ptr)(
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].digTileTarget)
                != 1) {
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetedBuildingTile = 0;
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::moveUnitToBehaviorTarget,
                    DAT_TribesState::ptr)(DAT_CurrentUnitSlotID::instance,
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].unknownDigMoatOrWallAttackFlag1015)
                == 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
            }
            return;
        }
        case (UnitState)0x68:
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSheetFrameOffset = 0x379;
            return;
        case (UnitState)0x6c:
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSheetFrameOffset = 1;
            return;
        case OpenSHC::Map::Units::States::US_RELOAD_WEAPONUnk:
            // drawing an arrow
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSpeed = 2;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field39_0x58 = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.field19_0xbf4
                      [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame <= 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = OpenSHC::Map::Units::States::US_AIM_WEAPONUnk;
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].facingDirectionMapOrientationCorrected
                + 0xf9 + DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame * 8;
            return;
        case OpenSHC::Map::Units::States::US_AIM_WEAPONUnk: {
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSpeed = 2;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetingType
                == OpenSHC::Map::Units::UIT_ATTACK_BUILDING) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setUnitFacingDirectionForTargetXandY,
                    DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance,
                    DAT_BuildingsState::instance
                        .buildings[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                                .targetID_OR_targetBuildingID]
                        .x,
                    DAT_BuildingsState::instance
                        .buildings[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                                .targetID_OR_targetBuildingID]
                        .y);
            } else if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetingType
                == OpenSHC::Map::Units::UIT_LIGHT_PITCH) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setUnitFacingDirectionForTargetXandY,
                    DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance,
                    DAT_TileMapState::instance
                        .pitchDitches[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                                .targetID_OR_targetBuildingID]
                        .x,
                    DAT_TileMapState::instance
                        .pitchDitches[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                                .targetID_OR_targetBuildingID]
                        .y);
            } else if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetingType
                    == OpenSHC::Map::Units::UIT_ATTACK_LAND
                || DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].shootTargetedUnit == -2) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setUnitFacingDirectionForTargetXandY,
                    DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance,
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].shootTargetMicroX / 8,
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].shootTargetMicroY / 8);
            } else {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setUnitFacingDirectionTowardsTarget,
                    DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance,
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].shootTargetedUnit);
            }
            // aim level, up or down
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].jugglerCount == 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.field20_0xc1c
                          [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
                if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame > 0) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                        = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                              .facingDirectionMapOrientationCorrected
                        + 0x139 + DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame * 8;
                }
            } else if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].jugglerCount == 1) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.field21_0xc34
                          [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
                if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame > 0) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                        = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                              .facingDirectionMapOrientationCorrected
                        + 0x1b9 + DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame * 8;
                }
            } else if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].jugglerCount == -1) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.field22_0xc54
                          [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
                if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame > 0) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                        = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                              .facingDirectionMapOrientationCorrected
                        + 0x219 + DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame * 8;
                }
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame > 0) {
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
            int target = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].shootTargetedUnit;
            if (target > -1) {
                if (DAT_UnitsState::instance.units[target].logicalState != OpenSHC::Map::Units::ULS_NORMAL
                    || DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetUID
                        != DAT_UnitsState::instance.units[target].uid
                    || DAT_UnitsState::instance.units[target].dying != 0) {
                    if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::acquireShootTarget,
                            DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance)
                        != FALSE) {
                        return;
                    }
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                        = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
                    return;
                }
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].shootTargetMicroX
                    = DAT_UnitsState::instance.units[target].microXPosition;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].shootTargetMicroY
                    = DAT_UnitsState::instance.units[target].microYPosition;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].shootTargetZ
                    = DAT_UnitsState::instance.units[target].buildingHeight
                    + DAT_UnitsState::instance.units[target].terrainOrClimbHeight;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                = OpenSHC::Map::Units::States::US_FIRE_WEAPONUnk;
            return;
        }
        case OpenSHC::Map::Units::States::US_FIRE_WEAPONUnk:
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSpeed = 2;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].jugglerCount == 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.field23_0xc74
                          [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
                if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame > 0) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                        = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                              .facingDirectionMapOrientationCorrected
                        + 0x179 + DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame * 8;
                }
            } else if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].jugglerCount == 1) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.field23_0xc74
                          [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
                if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame > 0) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                        = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                              .facingDirectionMapOrientationCorrected
                        + 0x1d9 + DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame * 8;
                }
            } else if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].jugglerCount == -1) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.field23_0xc74
                          [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
                if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame > 0) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                        = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                              .facingDirectionMapOrientationCorrected
                        + 0x239 + DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame * 8;
                }
            }
            if ((DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame == 6
                    && DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                            .animationCycleNumberHasJustIncremented
                        != FALSE)
                || DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field298_0x40e != false) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field298_0x40e = false;
                int target = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].shootTargetedUnit;
                if (target < 0) {
                    int targetZ;
                    if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetingType
                        == OpenSHC::Map::Units::UIT_LIGHT_PITCH) {
                        targetZ = DAT_TileMapState::instance.HeightLayer[DAT_TileMapState::instance
                                          .pitchDitches[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                                                  .targetID_OR_targetBuildingID]
                                          .tile]
                            + 4;
                    } else {
                        MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::prepareProjectileTarget,
                            DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance, -1, 200);
                        targetZ = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].shootTargetZ + 30;
                    }
                    OpenSHC::Map::Entities::EntityType projectile = (OpenSHC::Map::Entities::EntityType)24;
                    if (MACRO_CALL_MEMBER(OpenSHC::Map::Entities::EntityState_Func::isBrazierNearby,
                            DAT_EntityState::ptr)(DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].x,
                            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].y,
                            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].buildingHeight
                                + DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].terrainOrClimbHeight)
                        != 0) {
                        // light the arrow at the brazier
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field297_0x40d = true;
                        projectile = (OpenSHC::Map::Entities::EntityType)0x5c;
                        if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetingType
                            == OpenSHC::Map::Units::UIT_LIGHT_PITCH) {
                            projectile = (OpenSHC::Map::Entities::EntityType)0x5d;
                        }
                    }
                    MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::shootProjectile, DAT_UnitsState::ptr)(
                        DAT_CurrentUnitSlotID::instance, projectile,
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].shootTargetMicroX,
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].shootTargetMicroY, targetZ);
                    if (projectile == (OpenSHC::Map::Entities::EntityType)0x5c
                        || projectile == (OpenSHC::Map::Entities::EntityType)0x5d) {
                        MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].x,
                            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].y,
                            OpenSHC::DE::SHCDE::FX_FLAME_ARROW);
                    } else {
                        MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].x,
                            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].y,
                            OpenSHC::DE::SHCDE::FX_ARROW_FIRE);
                    }
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field283_0x3f8 = 0;
                } else {
                    int flightTime = MACRO_CALL_MEMBER(
                        OpenSHC::Map::Entities::EntityState_Func::arrowShootingRelated, DAT_EntityState::ptr)(
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].microXPosition,
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].microYPosition,
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].buildingHeight + 30
                            + DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].terrainOrClimbHeight,
                        DAT_UnitsState::instance.units[target].microXPosition,
                        DAT_UnitsState::instance.units[target].microYPosition,
                        DAT_UnitsState::instance.units[target].buildingHeight + 26
                            + DAT_UnitsState::instance.units[target].terrainOrClimbHeight);
                    int heightOffset = 30;
                    OpenSHC::Map::Entities::EntityType projectile = OpenSHC::Map::Entities::ET_ARROW_AND_DEFAULT;
                    if (MACRO_CALL_MEMBER(OpenSHC::Map::Entities::EntityState_Func::isBrazierNearby,
                            DAT_EntityState::ptr)(DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].x,
                            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].y,
                            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].buildingHeight
                                + DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].terrainOrClimbHeight)
                        != 0) {
                        // light the arrow at the brazier
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field297_0x40d = true;
                        projectile = (OpenSHC::Map::Entities::EntityType)0x5b;
                        if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetingType
                            == OpenSHC::Map::Units::UIT_ATTACK_BUILDING) {
                            heightOffset = 0;
                        }
                        if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetingType
                            == OpenSHC::Map::Units::UIT_LIGHT_PITCH) {
                            projectile = (OpenSHC::Map::Entities::EntityType)0x5d;
                            heightOffset = 0;
                        }
                    }
                    if (flightTime <= 0
                        || DAT_UnitsState::instance.units[target].uid
                            != DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetUID
                        || DAT_UnitsState::instance.units[target].logicalState != OpenSHC::Map::Units::ULS_NORMAL
                        || DAT_UnitsState::instance.units[target].dying != 0) {
                        if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::acquireShootTarget,
                                DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance)
                            == FALSE) {
                            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                                = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
                        } else if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                            != OpenSHC::Map::Units::States::US_MOVE_TO_DESTINATION) {
                            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                                = OpenSHC::Map::Units::States::US_AIM_WEAPONUnk;
                        }
                    } else {
                        MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::prepareProjectileTarget,
                            DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance, target, flightTime);
                        MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::shootProjectile, DAT_UnitsState::ptr)(
                            DAT_CurrentUnitSlotID::instance, projectile,
                            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].shootTargetMicroX,
                            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].shootTargetMicroY,
                            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].shootTargetZ
                                + heightOffset);
                        if (projectile == (OpenSHC::Map::Entities::EntityType)0x5b
                            || projectile == (OpenSHC::Map::Entities::EntityType)0x5d) {
                            MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].x,
                                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].y,
                                OpenSHC::DE::SHCDE::FX_FLAME_ARROW);
                        } else {
                            MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].x,
                                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].y,
                                OpenSHC::DE::SHCDE::FX_ARROW_FIRE);
                        }
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field283_0x3f8 = 0;
                    }
                }
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame > 0) {
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
            return;
        case OpenSHC::Map::Units::States::US_LOOK_AROUNDUnk:
            // cheering
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSpeed = 2;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field283_0x3f8 == 0
                && (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetingType
                        == OpenSHC::Map::Units::UIT_UNIT_ATTACK_UNIT
                    || DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetingType
                        == OpenSHC::Map::Units::UIT_ATTACK_BUILDING
                    || DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetingType
                        == OpenSHC::Map::Units::UIT_LIGHT_PITCH
                    || DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetingType
                        == OpenSHC::Map::Units::UIT_ATTACK_LAND)) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field283_0x3f8 = 1;
                DAT_UnitHasBecomeIdle::instance = 1;
            }
            if (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_SKIRMISH_AND_MULTIPLAYER) {
                MACRO_CALL_MEMBER(
                    OpenSHC::Map::Units::UnitsState_Func::setUnitFacingDirectionBasedOnBuilding, DAT_UnitsState::ptr)(
                    DAT_CurrentUnitSlotID::instance, DAT_GameState::instance.mapAndTime.signpostIDs[0]);
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.field30_0xe74
                      [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber]
                * 4;
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame <= 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                            .facingDirectionMapOrientationCorrected
                        / 2
                    + 0x281;
                DAT_UnitHasBecomeIdle::instance = 1;
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                            .facingDirectionMapOrientationCorrected
                        / 2
                    + 0x280 + DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame;
            }
            if (DAT_UnitHasBecomeIdle::instance == 0) {
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate += 1;
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate > 5) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate = 0;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
            return;
        case OpenSHC::Map::Units::States::US_STAND_UPUnk:
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSpeed = 5;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field283_0x3f8 == 0
                && (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetingType
                        == OpenSHC::Map::Units::UIT_UNIT_ATTACK_UNIT
                    || DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetingType
                        == OpenSHC::Map::Units::UIT_ATTACK_BUILDING
                    || DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetingType
                        == OpenSHC::Map::Units::UIT_LIGHT_PITCH
                    || DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetingType
                        == OpenSHC::Map::Units::UIT_ATTACK_LAND)) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field283_0x3f8 = 1;
                DAT_UnitHasBecomeIdle::instance = 1;
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].seated == 0) {
                if ((DAT_CurrentUnitSlotID::instance & 1) == 0) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                        = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.field25_0xce0
                              [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
                } else {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                        = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.field24_0xca0
                              [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
                }
                if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame <= 0) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber = 0x2b1;
                    DAT_UnitHasBecomeIdle::instance = 1;
                } else {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                        = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame + 0x2b0;
                }
            } else {
                // standing up
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field39_0x58 = 1;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp
                          .ANIM_Archer_CrusaderAndArabian1
                              [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
                if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame <= 0) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate = 0x66;
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].seated = 0;
                    DAT_UnitHasBecomeIdle::instance = 1;
                } else {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                        = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame + 0x2c0;
                }
            }
            if (DAT_UnitHasBecomeIdle::instance == 0) {
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::moveToFreeTileNearby, DAT_UnitsState::ptr)(
                DAT_CurrentUnitSlotID::instance);
            return;
        case OpenSHC::Map::Units::States::US_SIT_DOWNUnk: {
            // idling, sitting down now and then
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].seated = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSpeed = 2;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field131_0x2ac = 10;
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate == -1) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber
                    = DAT_CurrentUnitSlotID::instance & 15;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate = 0x66;
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].closestEnemyMicroDistance < 400
                || DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field283_0x3f8 == 0
                    && (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetingType
                            == OpenSHC::Map::Units::UIT_UNIT_ATTACK_UNIT
                        || DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetingType
                            == OpenSHC::Map::Units::UIT_ATTACK_BUILDING
                        || DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetingType
                            == OpenSHC::Map::Units::UIT_LIGHT_PITCH
                        || DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetingType
                            == OpenSHC::Map::Units::UIT_ATTACK_LAND)) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field283_0x3f8 = 1;
                DAT_UnitHasBecomeIdle::instance = 1;
            }
            OpenSHC::Game::GameModeInt gameMode = DAT_GameSynchronyState::instance.currentGameMode;
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate == 0x65
                || DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate == 0x6a
                || DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate == 0x6b) {
                if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate == 0x65) {
                    // sitting down
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                        = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.field26_0xd18
                              [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
                    if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame <= 0) {
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate = 0x6a;
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].seated = 1;
                        DAT_UnitHasBecomeIdle::instance = 1;
                    } else {
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                            = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame + 0x2c0;
                    }
                } else if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate == 0x6a) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].seated = 1;
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                        = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.field27_0xd40
                              [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
                    if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame > 0) {
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                            = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame + 0x2c0;
                    } else {
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate = 0x6b;
                        DAT_UnitHasBecomeIdle::instance = 1;
                    }
                } else {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].seated = 1;
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                        = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.field28_0xd7c
                              [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
                    if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame > 0) {
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                            = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame + 0x2c0;
                    } else {
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate = 0x6a;
                        DAT_UnitHasBecomeIdle::instance = 1;
                    }
                }
                // a selected archer in a single player game stops idling
                if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].isSelected != 0
                    && gameMode == OpenSHC::Game::GM_SOLITARY) {
                    DAT_UnitHasBecomeIdle::instance = 1;
                } else if (DAT_UnitHasBecomeIdle::instance == 0) {
                    return;
                }
            } else if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate == 100) {
                // standing up
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field39_0x58 = 1;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp
                          .ANIM_Archer_CrusaderAndArabian1
                              [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
                if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame <= 0) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate = 0x66;
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].seated = 0;
                    DAT_UnitHasBecomeIdle::instance = 1;
                } else {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                        = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame + 0x2c0;
                    if (DAT_UnitHasBecomeIdle::instance == 0) {
                        return;
                    }
                }
            } else {
                // standing
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].seated = 0;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSheetFrameOffset = 1;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0x10;
                if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber
                    > (int)((DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].fixedRng & 31) * 4 + 2)) {
                    DAT_UnitHasBecomeIdle::instance = 1;
                } else if (DAT_UnitHasBecomeIdle::instance == 0) {
                    return;
                }
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].closestEnemyMicroDistance < 401
                || DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetingType
                    == OpenSHC::Map::Units::UIT_UNIT_ATTACK_UNIT
                || DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetingType
                    == OpenSHC::Map::Units::UIT_ATTACK_BUILDING
                || DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetingType
                    == OpenSHC::Map::Units::UIT_LIGHT_PITCH
                || DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetingType
                    == OpenSHC::Map::Units::UIT_ATTACK_LAND) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
                return;
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].isSelected == 0
                || gameMode != OpenSHC::Game::GM_SOLITARY) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::moveToFreeTileNearby, DAT_UnitsState::ptr)(
                    DAT_CurrentUnitSlotID::instance);
                if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].seated == 0
                    && (DAT_TileMapState::instance
                               .LogicLayer[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].tile]
                           & 0x10000100)
                        == 0) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate = 0x65;
                    return;
                }
                if ((DAT_TileMapState::instance
                            .LogicLayer[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].tile]
                        & 0x10000100)
                        != 0
                    && DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].seated != 0) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate = 100;
                }
                return;
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].seated != 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate = 100;
                return;
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate == 0x65) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate = 0x66;
            }
            return;
        }
        case OpenSHC::Map::Units::States::US_JESTER_ROAM_TO:
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].disappearFadeAlphaCountdown
                += DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                       .engineerManningSiegeStateRef_checkType;
            if ((char)DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].disappearFadeAlphaCountdown < 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].disappearFadeAlphaCountdown = 0;
            } else if ((char)DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].disappearFadeAlphaCountdown
                > 31) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].disappearFadeAlphaCountdown = 31;
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
                if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].isDisappearingUnk != 0) {
                    MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::prepareCampgroundCoords,
                        DAT_BuildingsState::ptr)(owner);
                    MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit, DAT_UnitsState::ptr)(
                        DAT_CurrentUnitSlotID::instance, DAT_BuildingsState::instance.DAT_TempXOffset,
                        DAT_BuildingsState::instance.DAT_TempYOffset, 0);
                }
                return;
            }
            if ((char)DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                        .engineerManningSiegeStateRef_checkType
                    > 0
                && DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].isDisappearingUnk != 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].logicalState
                    = OpenSHC::Map::Units::ULS_TRANSITIONING;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].disappearFadeAlphaCountdown = 32;
            }
            return;
        case OpenSHC::Map::Units::States::US_DEATH_02: {
            // falling off a wall
            int direction
                = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].facingDirectionMapOrientationCorrected
                + 4;
            int groundHeight = DAT_TileMapState::instance
                                   .HeightLayer[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].tile];
            if (direction > 7) {
                direction = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                                .facingDirectionMapOrientationCorrected
                    - 4;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSpeed = 1;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.field1_0x14
                      [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame <= 0) {
                DAT_UnitHasBecomeIdle::instance = 1;
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber = direction + 0x3d0
                    + DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame * 8;
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber > 3) {
                int drop = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber - 3;
                if (drop + groundHeight
                    < DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].terrainOrClimbHeight) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].terrainOrClimbHeight -= (short)drop;
                } else {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].terrainOrClimbHeight
                        = (short)groundHeight;
                }
            }
            if (DAT_UnitHasBecomeIdle::instance != 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = OpenSHC::Map::Units::States::US_DISAPPEAR;
            }
            return;
        }
        case OpenSHC::Map::Units::States::US_DEATH_01:
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].facingDirection = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSpeed = 2;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.ANIM_Frames_UnitDeath
                      [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame <= 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber = 0x2e8;
                DAT_UnitHasBecomeIdle::instance = 1;
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame + 0x2d0;
            }
            if (DAT_UnitHasBecomeIdle::instance != 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = OpenSHC::Map::Units::States::US_DISAPPEAR;
            }
            return;
        case OpenSHC::Map::Units::States::US_DEATH_03:
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].facingDirection = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSpeed = 2;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.ANIM_Frames_UnitDeath
                      [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame <= 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber = 0x300;
                DAT_UnitHasBecomeIdle::instance = 1;
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame + 0x2e8;
            }
            if (DAT_UnitHasBecomeIdle::instance != 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = OpenSHC::Map::Units::States::US_DISAPPEAR;
            }
            return;
        case OpenSHC::Map::Units::States::US_STONE_DEATH_01:
        case OpenSHC::Map::Units::States::US_STONE_DEATH_02:
        case OpenSHC::Map::Units::States::US_STONE_DEATH_03:
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].facingDirection = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSpeed = 2;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.ANIM_Frames_UnitDeath
                      [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame <= 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber = 0x318;
                DAT_UnitHasBecomeIdle::instance = 1;
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame + 0x300;
            }
            if (DAT_UnitHasBecomeIdle::instance != 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = OpenSHC::Map::Units::States::US_DISAPPEAR;
            }
            return;
        case OpenSHC::Map::Units::States::US_MELEE_ATTACK:
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSpeed = 3;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].attackedUnitID != 0
                && DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                        .animationCycleNumberHasJustIncremented
                    != FALSE
                && DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber == 4) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::playHurtSFXForUnit, DAT_UnitsState::ptr)(
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].attackedUnitID);
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate == 0
                || DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate != 1) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.field31_0xf84
                          [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.field32_0xfc8
                          [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame <= 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                          .facingDirectionMapOrientationCorrected
                    + 0x319;
                DAT_UnitHasBecomeIdle::instance = 1;
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                          .facingDirectionMapOrientationCorrected
                    + 0x311 + DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame * 8;
            }
            if (DAT_UnitHasBecomeIdle::instance == 0) {
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate += 1;
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate > 2) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate = 0;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::resumeMovementIfNoAttackTarget,
                DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance);
            return;
        case OpenSHC::Map::Units::States::US_DISAPPEAR:
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].disappearFadeAlphaCountdown += 1;
            if ((char)DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].disappearFadeAlphaCountdown
                <= 32) {
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].disappearFadeAlphaCountdown = 32;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].logicalState
                = OpenSHC::Map::Units::ULS_REMOVE;
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].killedFlagUnk != 0) {
                return;
            }
            MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::processUnitLossStatistic, DAT_GameState::ptr)(
                owner, DAT_CurrentUnitSlotID::instance);
            if (owner == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                DAT_GameState::instance.mapAndTime.ownLossesArray
                    [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].lastEncounteredEnemyPlayerID] += 1;
                return;
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].lastEncounteredEnemyPlayerID
                == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                DAT_GameState::instance.mapAndTime.emenyHitArray[owner] += 1;
            }
            return;
        }
    }

}
}
