#include "../Units.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/DE/SHCDE/eSFX.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/IO/Graphics/GmID.hpp"
#include "OpenSHC/Map/Enums/HitSoundMaterial.hpp"
#include "OpenSHC/Map/LogicHelpers/Logic1.hpp"
#include "OpenSHC/Map/Units/SomeTribeBehaviorType.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitInstructionType.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentUnitSlotID.hpp"
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
#include "OpenSHC/Globals/DWORD_00ee1064.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::Units::States::UnitState;

    // FUNCTION: STRONGHOLDCRUSADER 0x005744D0
    void Units::UpdateAssassin()
    {
        int const owner = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].owner;
        DAT_GameState::instance.playerDataArray[owner].armySize++;
        DAT_GameState::instance.playerDataArray[owner].countAssassins++;
        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gmIDUnk
            = OpenSHC::IO::Graphics::GID_ASSASIN_ROPE;
        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].imageIDUnk = 0;
        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].isSelectable_OR_matchTime = 1;
        MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::addUnitToNewTribe, DAT_TribesState::ptr)(
            DAT_CurrentUnitSlotID::instance);
        if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
            != OpenSHC::Map::Units::States::US_MELEE_ATTACK) {
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].imageID2 = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].drawYOffset = 0;
        }
        switch (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic) {
        case OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk:
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate = -1;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x418 = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x413 = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].idleCounterUnk++;
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].isDisappearingUnk != 0) {
                // signed: the original keeps -1 in a register for this decrement
                --(char&)DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].disappearFadeAlphaCountdown;
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
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic = (UnitState)105;
                if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getKeepLocationForAIUnit,
                        DAT_BuildingsState::ptr)(owner, 13, DAT_CurrentUnitSlotID::instance)) {
                    DAT_PathFindingState::instance.allAssassinsUnk = 1;
                    MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit, DAT_UnitsState::ptr)(
                        DAT_CurrentUnitSlotID::instance, DAT_BuildingsState::instance.DAT_TempXOffset,
                        DAT_BuildingsState::instance.DAT_TempYOffset, 0);
                }
                DAT_GameState::instance.playerDataArray[owner].countAssassinsAndArabianSwordsman++;
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                = OpenSHC::Map::Units::States::US_IDLEUnk;
            return;
        case (UnitState)105:
            // gathering at the keep
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x418 = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].SA = 1;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed = 1;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSheetFrameOffset = 1;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 16;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].calculatedMovementSpeed
                = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].movementSpeed;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].idleCounterUnk++;
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::hasUnitReachedDestination, DAT_UnitsState::ptr)(
                    DAT_CurrentUnitSlotID::instance)) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].facingDirection = 4;
                if ((int)(DAT_GameCore::instance.mapTimeInTicks + DAT_CurrentUnitSlotID::instance) % 40 == 0
                    && MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getKeepLocationForAIUnit,
                        DAT_BuildingsState::ptr)(owner, 13, DAT_CurrentUnitSlotID::instance)) {
                    DAT_PathFindingState::instance.allAssassinsUnk = 1;
                    MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit, DAT_UnitsState::ptr)(
                        DAT_CurrentUnitSlotID::instance, DAT_BuildingsState::instance.DAT_TempXOffset,
                        DAT_BuildingsState::instance.DAT_TempYOffset, 0);
                }
            }
            DAT_GameState::instance.playerDataArray[owner].countAssassinsAndArabianSwordsman++;
            break;
        case OpenSHC::Map::Units::States::US_MOVE_TO_DESTINATION:
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x418 = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 16;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSheetFrameOffset = 1;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x413 = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].idleCounterUnk = 0;
            if (DAT_TribesState::instance
                    .tribes[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].tribeID]
                    .isRallyingUnk
                != 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].SA = 1;
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].moveInstructionSpeedDelayTracker != 0) {
                if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].moveInstructionSpeedDelayTracker
                    > 70) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed = -1;
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
                } else {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed = 0;
                }
            } else if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].closestEnemyMicroDistance
                <= 192) {
                // sneaking
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSheetFrameOffset = 129;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed = 0;
            }
            if (!MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::hasUnitReachedDestination,
                    DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance)) {
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
            if (DAT_TribesState::instance
                    .tribes[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].tribeID]
                    .tribeBehaviorType
                == OpenSHC::Map::Units::STBT_0x400) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = OpenSHC::Map::Units::States::US_DISAPPEAR;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::handleUnitMovementWhenTargetingBuildings,
                    DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance)
                <= 0) {
                return;
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].unknownDigMoatOrWallAttackFlag1015
                == 1015) {
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
                        = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetedBuildingTile
                        - DAT_ViewportRenderState::instance
                              .translationMatrix[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                                      .digTileY__OR__countLifeCycleEngineersSentToManSiegeEngine]
                              .addXgetTile;
                    break;
                }
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                = OpenSHC::Map::Units::States::US_MELEE_ATTACK_WALL;
            return;
        case OpenSHC::Map::Units::States::US_APPEAR: {
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 16;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x418 = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].idleCounterUnk = 0;
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].moveInstructionSpeedDelayTracker != 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSheetFrameOffset = 1;
                if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].moveInstructionSpeedDelayTracker
                    > 70) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed = -1;
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
                } else {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed = 0;
                }
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSheetFrameOffset = 1;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed = 0;
            }
            if (!MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::hasUnitReachedDestination,
                    DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance)) {
                return;
            }
            // arrived at the map edge: jump to the actual appear tile
            int const tile = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
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
            break;
        }
        case OpenSHC::Map::Units::States::US_MELEE_ATTACK_WALL: {
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSpeed = 2;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x418 = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].idleCounterUnk = 0;
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setUnitFacingDirectionForTargetXandY,
                DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance,
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].attackAtTileX,
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].attackAtTileY);
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.field_0x2c94
                      [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame <= 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                          .facingDirectionMapOrientationCorrected
                    + 257;
                DAT_UnitHasBecomeIdle::instance = 1;
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                          .facingDirectionMapOrientationCorrected
                    + 249 + DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame * 8;
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumberHasJustIncremented
                && DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber == 6) {
                OpenSHC::Map::Enums::HitSoundMaterialInt const material
                    = MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingHurtSFXID, DAT_TileMapState::ptr)(
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetedBuildingTile);
                if (material == OpenSHC::Map::Enums::HSM_WOOD) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].x,
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].y,
                        OpenSHC::DE::SHCDE::FX_ATTACK_WOOD);
                } else if (material == OpenSHC::Map::Enums::HSM_STONE) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].x,
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].y,
                        OpenSHC::DE::SHCDE::FX_ATTACK_STONE);
                }
            }
            int building = DAT_TileMapState::instance.BuildingLayer
                               [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetedBuildingTile];
            if (building == 0
                && (DAT_TileMapState::instance.LogicLayer
                           [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetedBuildingTile]
                       & OpenSHC::Map::LogicHelpers::L_WALL_OR_GATEHOUSE)
                    == 0) {
                DAT_UnitHasBecomeIdle::instance = 1;
            } else if (DAT_UnitHasBecomeIdle::instance == 0) {
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].nextAttackHurtsWall++;
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].nextAttackHurtsWall > 1) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].nextAttackHurtsWall = 0;
            }
            int const tile = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetedBuildingTile;
            int const isWall
                = DAT_TileMapState::instance.LogicLayer[tile] & OpenSHC::Map::LogicHelpers::L_WALL_OR_GATEHOUSE;
            int damage;
            if (isWall != 0) {
                damage = 10;
            } else {
                building = DAT_TileMapState::instance.BuildingLayer[tile];
                if (building <= 0) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                        = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
                    return;
                }
                if (DAT_BuildingDefinedData::instance
                        .IsGateOrTowerArray[DAT_BuildingsState::instance.buildings[building].buildingType]) {
                    damage = 6;
                } else {
                    damage = 70;
                }
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::processDamageToBuildingThunk, DAT_TileMapState::ptr)(
                    tile, DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].attackAtTileX,
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].attackAtTileY, damage,
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].nextAttackHurtsWall,
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].owner, TRUE)) {
                // the building has been destroyed
                if (isWall != 0
                    && MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationNearTargetedBuilding,
                        DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance, 1)) {
                    return;
                }
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetedBuildingTile = 0;
                if (!MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::moveUnitToBehaviorTarget,
                        DAT_TribesState::ptr)(DAT_CurrentUnitSlotID::instance,
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                            .unknownDigMoatOrWallAttackFlag1015)) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                        = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
                }
            } else {
                int const attacker = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].owner;
                if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[attacker] == -1) {
                    // AI players give up on walls, gates and towers that are too dangerous
                    if (isWall != 0) {
                        if (DAT_TileMapState::instance.SEC_PathfindingCostTileMap1105
                                [DAT_TroopValueState::instance.attackInfo.playerInfo[attacker - 1]
                                        .currentPlayerID_OR_attackedPlayerID_OR_one]
                                [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetedBuildingTile]
                            > DAT_TroopValueState::instance.attackInfo.playerInfo[attacker - 1].someMinimumDistance
                                + 15) {
                            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::moveUnitToBehaviorTarget,
                                    DAT_TribesState::ptr)(DAT_CurrentUnitSlotID::instance,
                                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                                        .unknownDigMoatOrWallAttackFlag1015)) {
                                return;
                            }
                            // then-arm, return in the else: the original jumps from here into the block above; an early
                            // return moves it
                            if (!MACRO_CALL_MEMBER(
                                    OpenSHC::Map::Units::UnitsState_Func::setDestinationNearTargetedBuilding,
                                    DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance, 1)) {
                                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                                    = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
                            } else {
                                return;
                            }
                        }
                    } else if (DAT_BuildingDefinedData::instance
                                   .IsGateOrTowerArray[DAT_BuildingsState::instance.buildings[building].buildingType]
                        && DAT_TileMapState::instance.SEC_PathfindingCostTileMap1105
                                [DAT_TroopValueState::instance.attackInfo.playerInfo[attacker - 1]
                                        .currentPlayerID_OR_attackedPlayerID_OR_one]
                                [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetedBuildingTile]
                            > DAT_TroopValueState::instance.attackInfo.playerInfo[attacker - 1].someMinimumDistance + 10
                        && !MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::moveUnitToBehaviorTarget,
                            DAT_TribesState::ptr)(DAT_CurrentUnitSlotID::instance,
                            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                                .unknownDigMoatOrWallAttackFlag1015)) {
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                            = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
                    }
                }
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
            break;
        }
        case OpenSHC::Map::Units::States::US_ASSASSIN_THROWING_HOOK:
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x413 = 1;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSpeed = 1;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x418 = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].idleCounterUnk = 0;
            // the higher the wall, the higher the throw
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].assassinHeightDifference < 70) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.field_0x2dac
                          [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
            } else if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].assassinHeightDifference < 160) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.field_0x2df4
                          [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.field_0x2e4c
                          [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame <= 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                          .facingDirectionMapOrientationCorrected
                    + 449;
                DAT_UnitHasBecomeIdle::instance = 1;
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                          .facingDirectionMapOrientationCorrected
                    + 441 + DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame * 8;
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber == 1
                && DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                    .animationCycleNumberHasJustIncremented) {
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].x,
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].y, OpenSHC::DE::SHCDE::FX_GH_SWING);
            }
            if (DAT_UnitHasBecomeIdle::instance == 0) {
                return;
            }
            MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].x,
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].y, OpenSHC::DE::SHCDE::FX_GH_CATCH);
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                = OpenSHC::Map::Units::States::US_ASSASSIN_CLIMBING_UP;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x41a = 32;
            // warn the player whose wall is scaled
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].owner
                    != DAT_GameSynchronyState::instance.currentPlayerSlotID
                && DAT_GameSynchronyState::instance.currentPlayerSlotID
                    == (char)DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].ownerOfAssassinScaledObject
                && timeGetTime() - DWORD_00ee1064::instance > 30000) {
                if (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY
                    || DAT_GameState::instance.mapAndTime
                            .playerTeams[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].owner]
                        != DAT_GameState::instance.mapAndTime
                            .playerTeams[DAT_GameSynchronyState::instance.currentPlayerSlotID]) {
                    // "General_Warning18.wav"
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                        s_General_Warning18_wav_005abedc);
                }
                DWORD_00ee1064::instance = timeGetTime();
            }
            break;
        case OpenSHC::Map::Units::States::US_ASSASSIN_START_CLIMBING_DOWN:
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x413 = 1;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSpeed = 1;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].idleCounterUnk = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.field_0x2eb0
                      [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame <= 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                          .facingDirectionMapOrientationCorrected
                    + 449;
                DAT_UnitHasBecomeIdle::instance = 1;
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                          .facingDirectionMapOrientationCorrected
                    + 441 + DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame * 8;
            }
            if (DAT_UnitHasBecomeIdle::instance == 0) {
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                = OpenSHC::Map::Units::States::US_ASSASSIN_CLIMBING_DOWN;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x41a = 32;
            MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].x,
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].y, OpenSHC::DE::SHCDE::FX_ROPE_SLIDE);
            break;
        case OpenSHC::Map::Units::States::US_ASSASSIN_CLIMBING_UP:
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x413 = 1;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSpeed = 2;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].idleCounterUnk = 0;
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x41a > 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x41a -= 2;
            }
            // rope length: an if chain as in the original; a for loop over the thresholds loses the match
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].assassinHeightDifference < 70) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].imageIDUnk = 7;
            } else if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].assassinHeightDifference < 100) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].imageIDUnk = 6;
            } else if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].assassinHeightDifference < 130) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].imageIDUnk = 5;
            } else if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].assassinHeightDifference < 160) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].imageIDUnk = 4;
            } else if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].assassinHeightDifference < 190) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].imageIDUnk = 3;
            } else if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].assassinHeightDifference < 210) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].imageIDUnk = 2;
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].imageIDUnk = 1;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.field_0x2ed8
                      [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame <= 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                          .facingDirectionMapOrientationCorrected
                    + 625;
                DAT_UnitHasBecomeIdle::instance = 1;
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                          .facingDirectionMapOrientationCorrected
                    + 617 + DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame * 8;
            }
            if (DAT_UnitHasBecomeIdle::instance != 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumberHasJustIncremented
                && (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber < 10
                    || DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber > 16)) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x418++;
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x418
                < DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].assassinHeightDifference - 35) {
                return;
            }
            // reached the top
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::commitMimmicLocation, DAT_UnitsState::ptr)(
                DAT_CurrentUnitSlotID::instance);
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                = OpenSHC::Map::Units::States::US_MOVE_TO_DESTINATION;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x418 = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x41a = 32;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x413 = 0;
            break;
        case OpenSHC::Map::Units::States::US_ASSASSIN_CLIMBING_DOWN:
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x413 = 1;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSpeed = 2;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].idleCounterUnk = 0;
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x418 == 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x418
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].assassinHeightDifference;
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::commitMimmicLocation, DAT_UnitsState::ptr)(
                    DAT_CurrentUnitSlotID::instance);
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x41a > 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x41a -= 2;
            }
            // rope length: an if chain as in the original; a for loop over the thresholds loses the match
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].assassinHeightDifference < 70) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].imageIDUnk = 7;
            } else if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].assassinHeightDifference < 100) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].imageIDUnk = 6;
            } else if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].assassinHeightDifference < 130) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].imageIDUnk = 5;
            } else if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].assassinHeightDifference < 160) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].imageIDUnk = 4;
            } else if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].assassinHeightDifference < 190) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].imageIDUnk = 3;
            } else if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].assassinHeightDifference < 210) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].imageIDUnk = 2;
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].imageIDUnk = 1;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                = (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                          .facingDirectionMapOrientationCorrected
                      + 4)
                    % 8
                + 657;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x418 -= 4;
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x418 > 30) {
                return;
            }
            // landed
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                = OpenSHC::Map::Units::States::US_MOVE_TO_DESTINATION;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x418 = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x41a = 32;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x413 = 0;
            MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].x,
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].y, OpenSHC::DE::SHCDE::FX_ASS_LAND);
            break;
        case (UnitState)104:
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].idleCounterUnk = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSheetFrameOffset = 385;
            break;
        case OpenSHC::Map::Units::States::US_UNKNOWN_108:
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].idleCounterUnk = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSheetFrameOffset = 1;
            break;
        case OpenSHC::Map::Units::States::US_JESTER_ROAM_TO:
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x418 = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].idleCounterUnk = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].disappearFadeAlphaCountdown
                += DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                       .engineerManningSiegeStateRef_checkType;
            if ((char)DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].disappearFadeAlphaCountdown < 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].disappearFadeAlphaCountdown = 0;
            } else if ((char)DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].disappearFadeAlphaCountdown
                >= 32) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].disappearFadeAlphaCountdown = 31;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].updateTickTracker++;
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
            break;
        case OpenSHC::Map::Units::States::US_MELEE_ATTACK: {
            int const previousGfx = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x418 = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSpeed = 1;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].idleCounterUnk = 0;
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].attackedUnitID != 0
                && DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                    .animationCycleNumberHasJustIncremented) {
                int const attacked = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].attackedUnitID;
                if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber == 7) {
                    MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::playHurtSFXForUnit, DAT_UnitsState::ptr)(
                        attacked);
                }
                if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber == 5) {
                    int const type = DAT_UnitsState::instance.units[attacked].unitType;
                    if (type == OpenSHC::Map::Units::UT_E_SPEAR || type == OpenSHC::Map::Units::UT_E_PIKE
                        || type == OpenSHC::Map::Units::UT_LORD || type == OpenSHC::Map::Units::UT_E_MACE
                        || type == OpenSHC::Map::Units::UT_E_SWORD || type == OpenSHC::Map::Units::UT_E_KNIGHT
                        || type == OpenSHC::Map::Units::UT_A_ASSASSIN || type == OpenSHC::Map::Units::UT_A_SWORDSMAN) {
                        MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].x,
                            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].y,
                            OpenSHC::DE::SHCDE::FX_STEEL1);
                    }
                }
                if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber == 4) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].x,
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].y,
                        OpenSHC::DE::SHCDE::FX_ASS_SWISH);
                }
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.field_0x2c94
                      [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame <= 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                          .facingDirectionMapOrientationCorrected
                    + 257;
                DAT_UnitHasBecomeIdle::instance = 1;
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                          .facingDirectionMapOrientationCorrected
                    + 249 + DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame * 8;
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber != previousGfx) {
                // motion blur of the previous frames
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].drawYOffset
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].imageID2;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].imageID2 = previousGfx;
            }
            if (DAT_UnitHasBecomeIdle::instance == 0) {
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::resumeMovementIfNoAttackTarget,
                DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance);
            break;
        }
        case OpenSHC::Map::Units::States::US_IDLEUnk: {
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x418 = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSpeed = 5;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x2ac = 10;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].SA = 1;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].idleCounterUnk++;
            int const variant = DAT_CurrentUnitSlotID::instance & 3;
            if (variant == 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp
                          .DAT_AssassinAnimationFrames0[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                                  .animationCycleNumber];
            } else if (variant == 1) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp
                          .DAT_AssassinAnimationFrames1[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                                  .animationCycleNumber];
            } else if (variant == 2) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp
                          .DAT_AssassinAnimationFrames2[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                                  .animationCycleNumber];
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp
                          .DAT_AssassinAnimationFrames4[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                                  .animationCycleNumber];
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame <= 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber = 785;
                DAT_UnitHasBecomeIdle::instance = 1;
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame + 784;
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetingType
                    == OpenSHC::Map::Units::UIT_DIG_MOAT
                || DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetingType
                    == OpenSHC::Map::Units::UIT_FILL_MOAT) {
                DAT_UnitHasBecomeIdle::instance = 1;
            }
            if (DAT_UnitHasBecomeIdle::instance == 0) {
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::moveToFreeTileNearby, DAT_UnitsState::ptr)(
                DAT_CurrentUnitSlotID::instance);
            break;
        }
        case OpenSHC::Map::Units::States::US_DEATH_01:
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x418 >= 8) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x418 -= 8;
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x418 = 0;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].facingDirection = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSpeed = 2;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.field_0x93c
                      [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].idleCounterUnk = 0;
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame <= 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber = 828;
                DAT_UnitHasBecomeIdle::instance = 1;
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame + 804;
            }
            if (DAT_UnitHasBecomeIdle::instance != 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = OpenSHC::Map::Units::States::US_DISAPPEAR;
            }
            break;
        case OpenSHC::Map::Units::States::US_DEATH_03:
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x418 = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].facingDirection = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSpeed = 1;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].idleCounterUnk = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.field_0x93c
                      [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame <= 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber = 874;
                DAT_UnitHasBecomeIdle::instance = 1;
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame + 850;
            }
            if (DAT_UnitHasBecomeIdle::instance != 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = OpenSHC::Map::Units::States::US_DISAPPEAR;
            }
            break;
        case OpenSHC::Map::Units::States::US_STONE_DEATH_01:
        case OpenSHC::Map::Units::States::US_STONE_DEATH_02:
        case OpenSHC::Map::Units::States::US_STONE_DEATH_03:
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x418 = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].facingDirection = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSpeed = 1;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].idleCounterUnk = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.field_0x8e4
                      [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame <= 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber = 850;
                DAT_UnitHasBecomeIdle::instance = 1;
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame + 828;
            }
            if (DAT_UnitHasBecomeIdle::instance != 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = OpenSHC::Map::Units::States::US_DISAPPEAR;
            }
            break;
        case OpenSHC::Map::Units::States::US_DISAPPEAR:
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x418 = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].idleCounterUnk = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].disappearFadeAlphaCountdown++;
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
                DAT_GameState::instance.mapAndTime.hitsDealtToPlayerArray
                    [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].lastEncounteredEnemyPlayerID]++;
                return;
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].lastEncounteredEnemyPlayerID
                == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                DAT_GameState::instance.mapAndTime.emenyHitArray[owner]++;
            }
            break;
        }
    }

}
}
