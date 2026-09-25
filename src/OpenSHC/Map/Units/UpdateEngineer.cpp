#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Units.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/DE/SHCDE/eSFX.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/Entities/EntityType.hpp"
#include "OpenSHC/Map/Units/Pathfinding/DestinationNeededEnum.hpp"
#include "OpenSHC/Map/Units/SomeTribeBehaviorType.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitInstructionType.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentUnitSlotID.hpp"
#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
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
    using OpenSHC::Game::Resources::ResourceType;
    using OpenSHC::Map::Buildings::BuildingLogicalState;
    using OpenSHC::Map::Entities::EntityType;
    using OpenSHC::Map::Units::SomeTribeBehaviorType;
    using OpenSHC::Map::Units::UnitInstructionType;
    using OpenSHC::Map::Units::UnitLogicState;
    using OpenSHC::Map::Units::Pathfinding::DestinationNeededEnum;
    using OpenSHC::Map::Units::States::UnitState;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x00564250
    void Units::UpdateEngineer()
    {
        int owner = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].owner;
        int target = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetID_OR_targetBuildingID;
        if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY
            && DAT_GameSynchronyState::instance.currentPlayerFullIDArray[owner] == -1
            && DAT_GameSynchronyState::instance.currentAIArray[owner] != 0
            && DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].aiUnitBehaviourType == 10) {
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].movementSpeed = 2;
        }
        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].isSelectable_OR_matchTime = 1;
        MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::addUnitToNewTribe, DAT_TribesState::ptr)(
            DAT_CurrentUnitSlotID::instance);
        DAT_GameState::instance.playerDataArray[owner].armySize += 1;
        if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].dying == 0) {
            DAT_GameState::instance.playerDataArray[owner].field852_0x2b58 += 1;
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].aiUnitBehaviourType != 10
                && DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].aiUnitBehaviourType == 0x16) {
                DAT_GameState::instance.playerDataArray[owner].unknownHarrassingSiegeRelated += 1;
                if (DAT_GameState::instance.playerDataArray[owner].unknownHarrassingSiegeRelated > 20) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].logicalState
                        = OpenSHC::Map::Units::ULS_REMOVE;
                }
            }
        }
        DAT_GameState::instance.playerDataArray[owner].currentEngineers += 1;
        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].calculatedOwnerPlayerIndex = owner;
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
                if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::findFreeEngineerAssemblyTile,
                        DAT_BuildingsState::ptr)(owner, DAT_CurrentUnitSlotID::instance)
                    != 0) {
                    MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit, DAT_UnitsState::ptr)(
                        DAT_CurrentUnitSlotID::instance, DAT_BuildingsState::instance.DAT_TempXOffset,
                        DAT_BuildingsState::instance.DAT_TempYOffset, 0);
                }
                DAT_GameState::instance.playerDataArray[owner].someCount27 += 1;
                return;
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetingType
                == OpenSHC::Map::Units::UIT_DIG_MOAT) {
                int moat = MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::findNearestFriendlyMoatTileForDigging,
                    DAT_TileMapState::ptr)(owner, DAT_CurrentUnitSlotID::instance, 1);
                if (moat >= 0) {
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
                if (moat < 0) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetingType
                        = OpenSHC::Map::Units::UIT_NO_INSTRUCTION_OR_MOVEUnk;
                } else {
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
                            != 0
                        && MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit,
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
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetingType
                        = OpenSHC::Map::Units::UIT_NO_INSTRUCTION_OR_MOVEUnk;
                }
            } else if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].resourceToDeposit == 0) {
                if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].closestEnemyMicroDistance <= 400) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic = (UnitState)2;
                } else {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                        = OpenSHC::Map::Units::States::US_IDLEUnk;
                }
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = OpenSHC::Map::Units::States::US_SIT_DOWNUnk;
            }
            if (DAT_TribesState::instance
                    .tribes[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].tribeID]
                    .tribeBehaviorType
                == OpenSHC::Map::Units::STBT_0x400) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = OpenSHC::Map::Units::States::US_DISAPPEAR;
            }
            return;
        case (UnitState)0x69:
            // gathering at the assembly point
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSheetFrameOffset = 1;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0x10;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].calculatedMovementSpeed
                = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].movementSpeed;
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].aiUnitBehaviourType != 0x16
                && DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].aiUnitBehaviourType != 10
                && DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].engineerRelatedUnk == 0) {
                DAT_GameState::instance.playerDataArray[owner].engineerCountRelated += 1;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::hasUnitReachedDestination, DAT_UnitsState::ptr)(
                    DAT_CurrentUnitSlotID::instance)
                != FALSE) {
                if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::findFreeEngineerAssemblyTile,
                        DAT_BuildingsState::ptr)(owner, DAT_CurrentUnitSlotID::instance)
                    != 0) {
                    MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit, DAT_UnitsState::ptr)(
                        DAT_CurrentUnitSlotID::instance, DAT_BuildingsState::instance.DAT_TempXOffset,
                        DAT_BuildingsState::instance.DAT_TempYOffset, 0);
                    DAT_GameState::instance.playerDataArray[owner].someCount27 += 1;
                    return;
                }
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].facingDirection = 4;
            }
            DAT_GameState::instance.playerDataArray[owner].someCount27 += 1;
            return;
        case OpenSHC::Map::Units::States::US_MOVE_TO_DESTINATION:
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0x10;
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::clearHiddenFlagAndUpdatePosition,
                DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance);
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].aiUnitBehaviourType != 0x16
                && DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].aiUnitBehaviourType != 10
                && DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].engineerRelatedUnk == 0) {
                DAT_GameState::instance.playerDataArray[owner].engineerCountRelated += 1;
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].moveInstructionSpeedDelayTracker != 0) {
                if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].moveInstructionSpeedDelayTracker
                    < 71) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed = 0;
                } else {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed = -1;
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
                }
            }
            // carrying oil
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSheetFrameOffset
                = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].resourceToDeposit != 0 ? 501 : 1;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].movementSpeed
                = (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].resourceToDeposit != 0) + 1;
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::hasUnitReachedDestination, DAT_UnitsState::ptr)(
                    DAT_CurrentUnitSlotID::instance)
                != FALSE) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed = 0;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].seated = 0;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
                if (DAT_TribesState::instance
                        .tribes[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].tribeID]
                        .tribeBehaviorType
                    == OpenSHC::Map::Units::STBT_0x400) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].disappearFadeAlphaCountdown = 4;
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                        = OpenSHC::Map::Units::States::US_DISAPPEAR;
                }
                if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::handleUnitMovementWhenTargetingBuildings,
                        DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance)
                    > 0) {
                    if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                            .unknownDigMoatOrWallAttackFlag1015
                        == 1015) {
                        // arrived at a moat to fill
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].digTileTarget
                            = MACRO_CALL_MEMBER(
                                OpenSHC::Map::TileMapState_Func::returnOwnedMoatAtTile, DAT_TileMapState::ptr)(
                                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetedBuildingTile);
                        if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].digTileTarget == 0) {
                            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                                = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
                        } else {
                            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                                = OpenSHC::Map::Units::States::US_DIG;
                            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                                .digTileY__OR__countLifeCycleEngineersSentToManSiegeEngine
                                = DAT_ViewportRenderState::instance
                                      .tileTranslationMatrix_YComponent[DAT_UnitsState::instance
                                              .units[DAT_CurrentUnitSlotID::instance]
                                              .targetedBuildingTile];
                            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                                .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300
                                = (short)DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                                      .targetedBuildingTile
                                - (short)DAT_ViewportRenderState::instance
                                      .translationMatrix[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                                              .digTileY__OR__countLifeCycleEngineersSentToManSiegeEngine]
                                      .addXgetTile;
                        }
                    } else {
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                            = OpenSHC::Map::Units::States::US_MELEE_ATTACK_WALL;
                    }
                }
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].resourceToDeposit != 0
                && DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetingType
                    == OpenSHC::Map::Units::UIT_THROW_OIL) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::makeUnitStopWalkingByClearingPathProgressState,
                    DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance);
                if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].movementRelated > 7) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetingType
                        = OpenSHC::Map::Units::UIT_NO_INSTRUCTION_OR_MOVEUnk;
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic = (UnitState)10;
                }
            }
            return;
        case OpenSHC::Map::Units::States::US_APPEAR: {
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0x10;
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].moveInstructionSpeedDelayTracker != 0) {
                if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].moveInstructionSpeedDelayTracker
                    < 71) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed = 0;
                } else {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed = -1;
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
                }
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSheetFrameOffset
                = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].resourceToDeposit != 0 ? 501 : 1;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].movementSpeed
                = (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].resourceToDeposit != 0) + 1;
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
        case (UnitState)0x68:
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSheetFrameOffset = 0x181;
            return;
        case (UnitState)0x6c:
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSheetFrameOffset = 1;
            return;
        case (UnitState)3:
        case (UnitState)124: {
            // digging a moat
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic = (UnitState)124;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0x10;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSheetFrameOffset = 1;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed = 0;
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::clearHiddenFlagAndUpdatePosition,
                DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance);
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
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSpeed = 3;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
            int tile = DAT_ViewportRenderState::instance
                           .translationMatrix[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                                   .digTileY__OR__countLifeCycleEngineersSentToManSiegeEngine]
                           .addXgetTile
                + DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                      .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300;
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
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.field100_0x1dd0
                      [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame <= 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                          .facingDirectionMapOrientationCorrected
                    + 0x101;
                DAT_UnitHasBecomeIdle::instance = 1;
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                          .facingDirectionMapOrientationCorrected
                    + 0xf9 + DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame * 8;
            }
            if ((DAT_TileMapState::instance.LogicLayer[tile] & 0x40000000) != 0
                || ((short)DAT_TileMapState::instance.UnitLayer[tile] != 0
                    && DAT_UnitsState::instance.units[(short)DAT_TileMapState::instance.UnitLayer[tile]].someUnitStat4
                        == 0)) {
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
        case OpenSHC::Map::Units::States::US_RELOAD_WEAPONUnk:
        case OpenSHC::Map::Units::States::US_DIG: {
            // filling a moat
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                = OpenSHC::Map::Units::States::US_DIG;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0x10;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSheetFrameOffset = 1;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed = 0;
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::clearHiddenFlagAndUpdatePosition,
                DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance);
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
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSpeed = 3;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
            int tile = DAT_ViewportRenderState::instance
                           .translationMatrix[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                                   .digTileY__OR__countLifeCycleEngineersSentToManSiegeEngine]
                           .addXgetTile
                + DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                      .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300;
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
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.field101_0x1df8
                      [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame <= 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                          .facingDirectionMapOrientationCorrected
                    + 0x101;
                DAT_UnitHasBecomeIdle::instance = 1;
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                          .facingDirectionMapOrientationCorrected
                    + 0xf9 + DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame * 8;
            }
            if ((DAT_TileMapState::instance.LogicLayer[tile] & 0x40000000) == 0) {
                // the moat is gone already
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
        case (UnitState)2:
            // standing idle close to enemies
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSpeed = 3;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].aiUnitBehaviourType != 0x16
                && DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].aiUnitBehaviourType != 10
                && DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].engineerRelatedUnk == 0) {
                DAT_GameState::instance.playerDataArray[owner].engineerCountRelated += 1;
            }
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::clearHiddenFlagAndUpdatePosition,
                DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance);
            if ((DAT_CurrentUnitSlotID::instance & 1) == 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.field185_0x3754
                          [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.field184_0x36cc
                          [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame <= 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber = 0x179;
                DAT_UnitHasBecomeIdle::instance = 1;
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame + 0x178;
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetingType
                    == OpenSHC::Map::Units::UIT_DIG_MOAT
                || DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetingType
                    == OpenSHC::Map::Units::UIT_FILL_MOAT) {
                DAT_UnitHasBecomeIdle::instance = 1;
            } else if (DAT_UnitHasBecomeIdle::instance == 0) {
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::moveToFreeTileNearby, DAT_UnitsState::ptr)(
                DAT_CurrentUnitSlotID::instance);
            if (MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::isAIPlayer, DAT_GameSynchronyState::ptr)(
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].owner)
                == FALSE) {
                return;
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].engineerRelatedUnk != 0) {
                return;
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetingType
                    == OpenSHC::Map::Units::UIT_MAN_SIEGE_EQUIPMENT
                && DAT_UnitsState::instance
                        .units[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                                .targetedUnitID__OR__engineerMannedSiegeEngineRef]
                        .state.generic
                    == OpenSHC::Map::Units::States::US_FIRE_WEAPONUnk) {
                return;
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].aiUnitBehaviourType == 10
                && DAT_GameState::instance.playerDataArray[owner].aiPlayerState <= 4) {
                return;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::findFreeEngineerAssemblyTile,
                    DAT_BuildingsState::ptr)(owner, DAT_CurrentUnitSlotID::instance)
                == 0) {
                return;
            }
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit, DAT_UnitsState::ptr)(
                DAT_CurrentUnitSlotID::instance, DAT_BuildingsState::instance.DAT_TempXOffset,
                DAT_BuildingsState::instance.DAT_TempYOffset, 0);
            DAT_GameState::instance.playerDataArray[owner].someCount27 += 1;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic = (UnitState)0x69;
            return;
        case OpenSHC::Map::Units::States::US_IDLEUnk:
            // sitting around
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSpeed = 5;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field131_0x2ac = 10;
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].aiUnitBehaviourType != 0x16
                && DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].aiUnitBehaviourType != 10
                && DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].engineerRelatedUnk == 0) {
                DAT_GameState::instance.playerDataArray[owner].engineerCountRelated += 1;
            }
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::clearHiddenFlagAndUpdatePosition,
                DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance);
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].resourceToDeposit == 0) {
                if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate == -1) {
                    MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::sitDownIfStanding, DAT_UnitsState::ptr)(
                        DAT_CurrentUnitSlotID::instance);
                }
                if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate == 100) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                        = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.field187_0x37d4
                              [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
                } else if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate == 0x65) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                        = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.field186_0x37b0
                              [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
                } else if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate == 0x6a) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                        = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.field188_0x37f8
                              [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
                } else if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate == 0x6b) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                        = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.field190_0x383c
                              [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
                } else if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate == 0x6c) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                        = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.field194_0x38e0
                              [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
                } else if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate == 0x6d) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                        = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.field190_0x383c
                              [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
                } else if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate == 0x6e) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                        = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.field189_0x381c
                              [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
                } else if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate == 0x6f) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                        = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.field191_0x3858
                              [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
                } else if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate == 0x70) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                        = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.field193_0x38a8
                              [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
                } else if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate == 0x71) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                        = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.field192_0x387c
                              [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
                }
                if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame <= 0) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber = 0x196;
                    DAT_UnitHasBecomeIdle::instance = 1;
                } else {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                        = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame + 0x188;
                }
                if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetingType
                        == OpenSHC::Map::Units::UIT_DIG_MOAT
                    || DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetingType
                        == OpenSHC::Map::Units::UIT_FILL_MOAT) {
                    DAT_UnitHasBecomeIdle::instance = 1;
                } else if (DAT_UnitHasBecomeIdle::instance == 0) {
                    return;
                }
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
                if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate == 0x65) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate
                        = (DAT_CurrentUnitSlotID::instance & 3) + 0x6a;
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].seated = 1;
                } else if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate == 100) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate = 0x6a;
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].seated = 0;
                } else {
                    if ((DAT_GameCore::instance.mapTimeInTicks & 1) == 0) {
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate += 2;
                    } else {
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate += 1;
                    }
                    if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate > 0x71) {
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate = 0x6a;
                    }
                }
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::moveToFreeTileNearby, DAT_UnitsState::ptr)(
                    DAT_CurrentUnitSlotID::instance);
                if (MACRO_CALL_MEMBER(
                        OpenSHC::Synchrony::GameSynchronyState_Func::isAIPlayer, DAT_GameSynchronyState::ptr)(
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].owner)
                        != FALSE
                    && DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].engineerRelatedUnk == 0
                    && DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].aiUnitBehaviourType != 0x16) {
                    if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetingType
                            == OpenSHC::Map::Units::UIT_MAN_SIEGE_EQUIPMENT
                        && DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                                .targetedUnitID__OR__engineerMannedSiegeEngineRef
                            != 0
                        && DAT_UnitsState::instance
                                .units[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                                        .targetedUnitID__OR__engineerMannedSiegeEngineRef]
                                .state.generic
                            == OpenSHC::Map::Units::States::US_FIRE_WEAPONUnk) {
                        return;
                    }
                    if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].aiUnitBehaviourType == 10
                        && DAT_GameState::instance.playerDataArray[owner].aiPlayerState < 5) {
                        return;
                    }
                    if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::findFreeEngineerAssemblyTile,
                            DAT_BuildingsState::ptr)(owner, DAT_CurrentUnitSlotID::instance)
                        != 0) {
                        MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit,
                            DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance,
                            DAT_BuildingsState::instance.DAT_TempXOffset, DAT_BuildingsState::instance.DAT_TempYOffset,
                            0);
                        DAT_GameState::instance.playerDataArray[owner].someCount27 += 1;
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic = (UnitState)0x69;
                    }
                }
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber = 0x1f5;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed = 0;
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetingType
                    == OpenSHC::Map::Units::UIT_DIG_MOAT
                || DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetingType
                    == OpenSHC::Map::Units::UIT_FILL_MOAT) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
            }
            return;
        case OpenSHC::Map::Units::States::US_FIRE_WEAPONUnk:
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
            return;
        case OpenSHC::Map::Units::States::US_STAND_UPUnk: {
            // walking to a siege building to man it
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0x10;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSheetFrameOffset = 1;
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].aiUnitBehaviourType != 0x16
                && DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].aiUnitBehaviourType != 10
                && DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].engineerRelatedUnk == 0) {
                DAT_GameState::instance.playerDataArray[owner].engineerCountRelated += 1;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::hasUnitReachedDestination, DAT_UnitsState::ptr)(
                    DAT_CurrentUnitSlotID::instance)
                == FALSE) {
                return;
            }
            if (DAT_BuildingsState::instance.buildings[target].uid
                    == DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetUID
                && DAT_BuildingsState::instance.buildings[target].logicalState == OpenSHC::Map::Buildings::BLS_NORMAL) {
                int count = DAT_BuildingsState::instance.buildings[target].currentEmployeeCount;
                if (count < MACRO_CALL_MEMBER(
                        OpenSHC::Map::Buildings::BuildingsState_Func::getRequiredEngineerCountForSiegeBuilding,
                        DAT_BuildingsState::ptr)(target)
                    && abs(DAT_BuildingsState::instance.buildings[target].buildingEntryX
                           - DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].x)
                        < 2
                    && abs(DAT_BuildingsState::instance.buildings[target].buildingEntryY
                           - DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].y)
                        < 2) {
                    DAT_BuildingsState::instance.buildings[target].workerID[count]
                        = (short)DAT_CurrentUnitSlotID::instance;
                    DAT_BuildingsState::instance.buildings[target]
                        .workerUID[DAT_BuildingsState::instance.buildings[target].currentEmployeeCount]
                        = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].uid;
                    DAT_BuildingsState::instance.buildings[target].currentEmployeeCount += 1;
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                        = OpenSHC::Map::Units::States::US_JESTER_ROAM_TO;
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].disappearFadeAlphaCountdown = 0;
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                        .engineerManningSiegeStateRef_checkType = 2;
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].cachedState
                        = OpenSHC::Map::Units::States::US_LOOK_AROUNDUnk;
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].updateTickTracker = 0;
                    MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::deselectUnit, DAT_UnitsState::ptr)(
                        DAT_CurrentUnitSlotID::instance);
                    MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::clearOrDeselectUnitFromSelection,
                        DAT_UnitsState::ptr)(DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].owner,
                        DAT_CurrentUnitSlotID::instance, 0);
                    return;
                }
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
            return;
        }
        case OpenSHC::Map::Units::States::US_LOOK_AROUNDUnk:
            // inside the siege building
            if (DAT_BuildingsState::instance.buildings[target].uid
                == DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetUID) {
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                = OpenSHC::Map::Units::States::US_JESTER_ROAM_TO;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].disappearFadeAlphaCountdown = 32;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].engineerManningSiegeStateRef_checkType
                = 0xfe;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].cachedState = (UnitState)0x69;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].updateTickTracker = 0;
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::resetUnitMovementState, DAT_UnitsState::ptr)(
                DAT_CurrentUnitSlotID::instance);
            return;
        case (UnitState)9: {
            // working at the oil pot
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0x10;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSpeed = 8;
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].resourceToDeposit == 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSheetFrameOffset = 0x81;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed = 1;
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSheetFrameOffset = 0x1f5;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed = 0;
            }
            DAT_BuildingsState::instance.buildings[target].currentEmployeeCount += 1;
            short slot = DAT_BuildingsState::instance.buildings[target].currentEmployeeCount;
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::hasUnitReachedDestination, DAT_UnitsState::ptr)(
                    DAT_CurrentUnitSlotID::instance)
                == FALSE) {
                return;
            }
            if (DAT_BuildingsState::instance.buildings[target].uid
                    != DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetUID
                || DAT_BuildingsState::instance.buildings[target].logicalState != OpenSHC::Map::Buildings::BLS_NORMAL) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = OpenSHC::Map::Units::States::US_IDLEUnk;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate = -1;
                return;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::isEngineerNotAtAssignedWorkTile,
                    DAT_BuildingsState::ptr)((short)DAT_BuildingsState::instance.buildings[target].quarryStockpileID,
                    DAT_CurrentUnitSlotID::instance, slot)
                != 0) {
                if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit, DAT_UnitsState::ptr)(
                        DAT_CurrentUnitSlotID::instance, DAT_BuildingsState::instance.DAT_TempXOffset,
                        DAT_BuildingsState::instance.DAT_TempYOffset, 0)
                    != FALSE) {
                    return;
                }
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = OpenSHC::Map::Units::States::US_IDLEUnk;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate = -1;
                return;
            }
            uint activeEngineer = MACRO_CALL_MEMBER(
                OpenSHC::Map::Buildings::BuildingsState_Func::getActiveEngineerForBuilding, DAT_BuildingsState::ptr)(
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].workplaceBuildingID_1);
            if (activeEngineer == 0 || activeEngineer == DAT_CurrentUnitSlotID::instance) {
                // heating the oil
                if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber > 8) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
                }
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field252_0x3c4 = 1;
                DAT_BuildingsState::instance.buildings[target].workerUID[0]
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].uid;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.field195_0x3920
                          [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
                DAT_BuildingsState::instance.buildings[target].workerID[0] = (short)DAT_CurrentUnitSlotID::instance;
                if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame <= 0) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
                    if (DAT_BuildingsState::instance.buildings[target].uid
                        == DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetUID) {
                        if (DAT_BuildingsState::instance.buildings[target].resources[7] <= 0
                            || (DAT_BuildingsState::instance.buildings[target].waitingEngineerIDUnk == 0
                                && DAT_BuildingsState::instance.buildings[target].resources[7] < 9)) {
                            // fetch more pitch
                            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                                = (UnitState)12;
                            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].destinationNeeded
                                = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_NEEDED;
                        } else if (DAT_BuildingsState::instance.buildings[target].waitingEngineerIDUnk != 0) {
                            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].resourceToDeposit = 0;
                            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                                = OpenSHC::Map::Units::States::US_JESTER_ROAM_TO;
                            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].disappearFadeAlphaCountdown
                                = 0;
                            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                                .engineerManningSiegeStateRef_checkType = 2;
                            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].cachedState = (UnitState)15;
                            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].updateTickTracker = 0;
                            DAT_BuildingsState::instance.buildings[target].state = 6;
                            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
                        }
                    }
                } else {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                        = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame + 0x178;
                }
                DAT_BuildingsState::instance.buildings[target].waitingEngineerIDUnk = 0;
            } else {
                // waiting for oil
                if (DAT_BuildingsState::instance.buildings[target].waitingEngineerIDUnk <= 0
                    && DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].resourceToDeposit == 0) {
                    DAT_BuildingsState::instance.buildings[target].waitingEngineerIDUnk
                        = (short)DAT_CurrentUnitSlotID::instance;
                }
                if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber > 4) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
                }
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field252_0x3c4 = 0;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.field196_0x3940
                          [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
                if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame <= 0) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
                } else if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].resourceToDeposit == 0) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                        = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                              .facingDirectionMapOrientationCorrected
                        + 0x2a5;
                } else {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                        = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                              .facingDirectionMapOrientationCorrected
                        + 0x1f5;
                }
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic == (UnitState)9
                && DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].resourceToDeposit != 0
                && DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetingType
                    == (UnitInstructionType)0x19) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit, DAT_UnitsState::ptr)(
                    DAT_CurrentUnitSlotID::instance,
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].attackAtTileX,
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].attackAtTileY, 0);
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = OpenSHC::Map::Units::States::US_MOVE_TO_DESTINATION;
            }
            return;
        }
        case (UnitState)12:
            // fetching pitch from the stockpile
            DAT_BuildingsState::instance.buildings[target].currentEmployeeCount += 1;
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].destinationNeeded
                != OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].destinationNeeded
                    = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame = MACRO_CALL_MEMBER(
                    OpenSHC::Map::Buildings::BuildingsState_Func::getStorageBuildingForResourceTypeAndAmount,
                    DAT_BuildingsState::ptr)(OpenSHC::Game::Resources::RT_PITCH, 1,
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].owner);
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].horseOriginStablesBuildingIndexUnk
                    = (short)DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame;
                if (MACRO_CALL_MEMBER(
                        OpenSHC::Map::Buildings::BuildingsState_Func::buildingIsAccessible, DAT_BuildingsState::ptr)(
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame, 1)
                    == 0) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic = (UnitState)9;
                    return;
                }
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit, DAT_UnitsState::ptr)(
                    DAT_CurrentUnitSlotID::instance,
                    DAT_BuildingsState::instance
                        .buildings[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame]
                        .buildingEntryX,
                    DAT_BuildingsState::instance
                        .buildings[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame]
                        .buildingEntryY,
                    0);
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].horseOriginStableIDUnk
                    = DAT_BuildingsState::instance
                          .buildings[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame]
                          .uid;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSheetFrameOffset = 0x81;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0x10;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed = 1;
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::hasUnitReachedDestination, DAT_UnitsState::ptr)(
                    DAT_CurrentUnitSlotID::instance)
                == FALSE) {
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingResourceAmountByUid,
                    DAT_BuildingsState::ptr)(
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].horseOriginStablesBuildingIndexUnk,
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].horseOriginStableIDUnk,
                    OpenSHC::Game::Resources::RT_PITCH)
                <= 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].destinationNeeded
                    = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_NEEDED;
                return;
            }
            MACRO_CALL_MEMBER(
                OpenSHC::Map::Buildings::BuildingsState_Func::addResourceToStockpile, DAT_BuildingsState::ptr)(
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].horseOriginStablesBuildingIndexUnk,
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].horseOriginStableIDUnk,
                OpenSHC::Game::Resources::RT_PITCH, -1, 0x30, 1);
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].resourceToDeposit = 1;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].destinationNeeded
                = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_NEEDED;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic = (UnitState)13;
            return;
        case (UnitState)13:
            // bringing the pitch back to the oil pot
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].destinationNeeded
                != OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].destinationNeeded
                    = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET;
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::isEngineerNotAtAssignedWorkTile,
                    DAT_BuildingsState::ptr)((short)DAT_BuildingsState::instance.buildings[target].quarryStockpileID,
                    DAT_CurrentUnitSlotID::instance,
                    DAT_BuildingsState::instance.buildings[target].currentEmployeeCount);
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit, DAT_UnitsState::ptr)(
                    DAT_CurrentUnitSlotID::instance, DAT_BuildingsState::instance.DAT_TempXOffset,
                    DAT_BuildingsState::instance.DAT_TempYOffset, 0);
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSheetFrameOffset = 0x2bd;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0x10;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed = 0;
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::hasUnitReachedDestination, DAT_UnitsState::ptr)(
                    DAT_CurrentUnitSlotID::instance)
                == FALSE) {
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].resourceToDeposit = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                = OpenSHC::Map::Units::States::US_JESTER_ROAM_TO;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].disappearFadeAlphaCountdown = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].engineerManningSiegeStateRef_checkType = 2;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].cachedState = (UnitState)14;
            DAT_BuildingsState::instance.buildings[target].state = 2;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].updateTickTracker = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
            return;
        case (UnitState)14:
            DAT_BuildingsState::instance.buildings[target].workers[0] = (short)DAT_CurrentUnitSlotID::instance;
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::updateBuildingSignpostCounter,
                    DAT_BuildingsState::ptr)(target, 1)
                == 0) {
                return;
            }
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::updateBuildingSignpostCounter,
                DAT_BuildingsState::ptr)(target, 3);
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                = OpenSHC::Map::Units::States::US_JESTER_ROAM_TO;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].disappearFadeAlphaCountdown = 32;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].engineerManningSiegeStateRef_checkType
                = 0xfe;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].cachedState = (UnitState)9;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].updateTickTracker = 0;
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::resetUnitMovementState, DAT_UnitsState::ptr)(
                DAT_CurrentUnitSlotID::instance);
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSheetFrameOffset = 1;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0x10;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
            return;
        case (UnitState)15:
            DAT_BuildingsState::instance.buildings[target].workers[0] = (short)DAT_CurrentUnitSlotID::instance;
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::updateBuildingSignpostCounter,
                    DAT_BuildingsState::ptr)(target, 1)
                == 0) {
                return;
            }
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::updateBuildingSignpostCounter,
                DAT_BuildingsState::ptr)(target, 3);
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                = OpenSHC::Map::Units::States::US_JESTER_ROAM_TO;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].disappearFadeAlphaCountdown = 32;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].engineerManningSiegeStateRef_checkType
                = 0xfe;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].cachedState = (UnitState)9;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].updateTickTracker = 0;
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::resetUnitMovementState, DAT_UnitsState::ptr)(
                DAT_CurrentUnitSlotID::instance);
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSheetFrameOffset = 1;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0x10;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
            return;
        case OpenSHC::Map::Units::States::US_SIT_DOWNUnk:
            // holding oil, waiting for an order
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::TroopValueState_Func::ifNecessaryThrowOilAutomatically,
                DAT_TroopValueState::ptr)(DAT_CurrentUnitSlotID::instance);
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetingType
                == OpenSHC::Map::Units::UIT_THROW_OIL) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetingType
                    = (UnitInstructionType)0x19;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic = (UnitState)10;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].updateTickTracker = 0;
            }
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::clearHiddenFlagAndUpdatePosition,
                DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance);
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSpeed = 3;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.field196_0x3940
                      [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame > 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                          .facingDirectionMapOrientationCorrected
                    + 0x275;
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
            return;
        case (UnitState)10:
            // throwing oil
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setUnitFacingDirectionForTargetXandY,
                DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance,
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].attackAtTileX,
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].attackAtTileY);
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSpeed = 5;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.field197_0x395c
                      [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame <= 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic = (UnitState)9;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].attackAtTileX
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].x;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].attackAtTileY
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].y;
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                          .facingDirectionMapOrientationCorrected
                    + 0x26d + DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame * 8;
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame != 7
                || DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                        .animationCycleNumberHasJustIncremented
                    == FALSE) {
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].resourceToDeposit = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].shootTargetMicroX
                = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].attackAtTileX * 8;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].shootTargetMicroY
                = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].attackAtTileY * 8;
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::shootProjectile, DAT_UnitsState::ptr)(
                DAT_CurrentUnitSlotID::instance, (EntityType)8,
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].shootTargetMicroX,
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].shootTargetMicroY,
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].shootTargetZ + 10);
            MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].x,
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].y, OpenSHC::DE::SHCDE::FX_OIL_DUMP);
            return;
        case (UnitState)16:
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::disbandUnit, DAT_UnitsState::ptr)(
                DAT_CurrentUnitSlotID::instance);
            return;
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
                <= 0) {
                return;
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].isDisappearingUnk == 0) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::commitUnitLocation, DAT_UnitsState::ptr)(
                    DAT_CurrentUnitSlotID::instance);
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].logicalState
                = OpenSHC::Map::Units::ULS_TRANSITIONING;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].disappearFadeAlphaCountdown = 32;
            return;
        case OpenSHC::Map::Units::States::US_DEATH_01:
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].facingDirection = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSpeed = 1;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.ANIM_Frames_UnitDeath
                      [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame <= 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber = 0x1c4;
                DAT_UnitHasBecomeIdle::instance = 1;
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame + 0x1ac;
            }
            if (DAT_UnitHasBecomeIdle::instance != 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = OpenSHC::Map::Units::States::US_DISAPPEAR;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].disappearFadeAlphaCountdown = 0;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].updateTickTracker = 0;
            }
            return;
        case OpenSHC::Map::Units::States::US_DEATH_03:
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].facingDirection = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSpeed = 1;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.field5_0x66c
                      [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame <= 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber = 500;
                DAT_UnitHasBecomeIdle::instance = 1;
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame + 0x1dc;
            }
            if (DAT_UnitHasBecomeIdle::instance != 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = OpenSHC::Map::Units::States::US_DISAPPEAR;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].disappearFadeAlphaCountdown = 0;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].updateTickTracker = 0;
            }
            return;
        case OpenSHC::Map::Units::States::US_DEATH_02:
        case OpenSHC::Map::Units::States::US_STONE_DEATH_01:
        case OpenSHC::Map::Units::States::US_STONE_DEATH_02:
        case OpenSHC::Map::Units::States::US_STONE_DEATH_03:
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].facingDirection = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSpeed = 1;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.field5_0x66c
                      [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame <= 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber = 0x1dc;
                DAT_UnitHasBecomeIdle::instance = 1;
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame + 0x1c4;
            }
            if (DAT_UnitHasBecomeIdle::instance != 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = OpenSHC::Map::Units::States::US_DISAPPEAR;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].disappearFadeAlphaCountdown = 0;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].updateTickTracker = 0;
            }
            return;
        case OpenSHC::Map::Units::States::US_DISAPPEAR:
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
