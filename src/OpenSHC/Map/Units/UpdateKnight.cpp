#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Units.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/DE/SHCDE/eSFX.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Map/Units/SomeTribeBehaviorType.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentUnitSlotID.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
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
    using OpenSHC::Game::GameMode2;
    using OpenSHC::Map::Units::SomeTribeBehaviorType;
    using OpenSHC::Map::Units::UnitLogicState;
    using OpenSHC::Map::Units::UnitType;
    using OpenSHC::Map::Units::States::UnitState;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x00562AA0
    void Units::UpdateKnight()
    {
        int unitID = DAT_CurrentUnitSlotID::instance;
        int owner = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].owner;
        if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].imageIDUnk == 0) {
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].imageIDUnk = 1;
        }
        DAT_GameState::instance.playerDataArray[owner].armySize += 1;
        DAT_GameState::instance.playerDataArray[owner].currentKnights += 1;
        DAT_UnitsState::instance.units[unitID].gmIDUnk = 0x6e;
        DAT_UnitsState::instance.units[unitID].isSelectable_OR_matchTime = 1;
        MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::addUnitToNewTribe, DAT_TribesState::ptr)(unitID);
        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].displayColorPlayerID = (short)owner;
        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].calculatedOwnerPlayerIndex = owner;
        switch (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic) {
        case OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk:
            DAT_UnitsState::instance.units[unitID].stateBasedSpeed = 0;
            if (DAT_UnitsState::instance.units[unitID].isDisappearingUnk != 0) {
                DAT_UnitsState::instance.units[unitID].disappearFadeAlphaCountdown -= 1;
                if ((char)DAT_UnitsState::instance.units[unitID].disappearFadeAlphaCountdown >= 0) {
                    return;
                }
                DAT_UnitsState::instance.units[unitID].disappearFadeAlphaCountdown = 0;
                DAT_UnitsState::instance.units[unitID].isDisappearingUnk = 0;
                return;
            }
            if (DAT_UnitsState::instance.units[unitID].goToRallyPoint != 0) {
                DAT_UnitsState::instance.units[unitID].goToRallyPoint = 0;
                DAT_UnitsState::instance.units[unitID].state.generic = (UnitState)0x69;
                if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::isSpaceAvailableAtUnitRallyPoint,
                        DAT_BuildingsState::ptr)(owner, 6, unitID)
                    != 0) {
                    MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit, DAT_UnitsState::ptr)(
                        DAT_CurrentUnitSlotID::instance, DAT_BuildingsState::instance.DAT_TempXOffset,
                        DAT_BuildingsState::instance.DAT_TempYOffset, 0);
                }
                DAT_GameState::instance.playerDataArray[owner].rallySearchOffsetsUnk[5] += 1;
                DAT_GameState::instance.playerDataArray[owner].rallySearchOffset += 1;
                return;
            }
            if (DAT_GameState::instance.playerDataArray[owner].aiControlStatusRelated > 0
                && (DAT_UnitsState::instance.units[unitID].closestEnemyMicroDistance > 400
                    || DAT_GameState::instance.playerDataArray[owner].aiControlStatusRelated == 100000)) {
                DAT_UnitsState::instance.units[unitID].state.generic = (UnitState)3;
                return;
            }
            DAT_UnitsState::instance.units[unitID].state.generic = OpenSHC::Map::Units::States::US_IDLEUnk;
            return;
        case (UnitState)0x69:
            // gathering at the rally point
            DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset = 1;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0x10;
            DAT_UnitsState::instance.units[unitID].SA = 1;
            DAT_UnitsState::instance.units[unitID].calculatedMovementSpeed
                = DAT_UnitsState::instance.units[unitID].movementSpeed;
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::hasUnitReachedDestination, DAT_UnitsState::ptr)(
                    unitID)
                != FALSE) {
                DAT_UnitsState::instance.units[unitID].facingDirection = 4;
                if ((DAT_GameCore::instance.mapTimeInTicks + unitID) % 40 == 0
                    && MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::isSpaceAvailableAtUnitRallyPoint,
                           DAT_BuildingsState::ptr)(owner, 6, unitID)
                        != 0) {
                    MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit, DAT_UnitsState::ptr)(
                        DAT_CurrentUnitSlotID::instance, DAT_BuildingsState::instance.DAT_TempXOffset,
                        DAT_BuildingsState::instance.DAT_TempYOffset, 0);
                }
            }
            DAT_GameState::instance.playerDataArray[owner].rallySearchOffsetsUnk[5] += 1;
            DAT_GameState::instance.playerDataArray[owner].rallySearchOffset += 1;
            return;
        case OpenSHC::Map::Units::States::US_MOVE_TO_DESTINATION:
            DAT_UnitsState::instance.units[unitID].stateBasedSpeed = 0;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0x10;
            if (DAT_TribesState::instance.tribes[DAT_UnitsState::instance.units[unitID].tribeID].isRallyingUnk != 0) {
                DAT_UnitsState::instance.units[unitID].SA = 1;
            }
            if (DAT_UnitsState::instance.units[unitID].moveInstructionSpeedDelayTracker == 0) {
                if (DAT_UnitsState::instance.units[unitID].movementRunUpTime != 0) {
                    DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset = 1;
                    DAT_UnitsState::instance.units[unitID].stateBasedSpeed = 0;
                } else if (DAT_UnitsState::instance.units[unitID].isMatchingSpeed != false) {
                    DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset = 1;
                    DAT_UnitsState::instance.units[unitID].stateBasedSpeed = 0;
                } else {
                    // charging
                    DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset = 0x81;
                    DAT_UnitsState::instance.units[unitID].stateBasedSpeed = 2;
                }
            } else {
                DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset = 1;
                if (DAT_UnitsState::instance.units[unitID].moveInstructionSpeedDelayTracker < 71) {
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
            if (DAT_TribesState::instance.tribes[DAT_UnitsState::instance.units[unitID].tribeID].tribeBehaviorType
                == OpenSHC::Map::Units::STBT_0x400) {
                DAT_UnitsState::instance.units[unitID].state.generic = OpenSHC::Map::Units::States::US_DISAPPEAR;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::handleUnitMovementWhenTargetingBuildings,
                    DAT_UnitsState::ptr)(unitID)
                > 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = OpenSHC::Map::Units::States::US_MELEE_ATTACK_WALL;
            }
            return;
        case OpenSHC::Map::Units::States::US_APPEAR: {
            DAT_UnitsState::instance.units[unitID].stateBasedSpeed = 0;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0x10;
            if (DAT_UnitsState::instance.units[unitID].moveInstructionSpeedDelayTracker == 0) {
                DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset = 0x81;
                DAT_UnitsState::instance.units[unitID].stateBasedSpeed = 0;
            } else {
                DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset = 1;
                if (DAT_UnitsState::instance.units[unitID].moveInstructionSpeedDelayTracker < 71) {
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
            // arrived at the map edge: jump to the actual appear tile
            int tile = DAT_UnitsState::instance.units[unitID]
                           .targetedUnitUIDUnk_OR_someAppearTileUnk_OR_buildingUID_OR_pitchDitchUID_OR_entityUID;
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setPositionOfUnit, DAT_UnitsState::ptr)(unitID,
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
            DAT_UnitsState::instance.units[unitID].animationSpeed = 3;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setUnitFacingDirectionForTargetXandY,
                DAT_UnitsState::ptr)(unitID, DAT_UnitsState::instance.units[unitID].attackAtTileX,
                DAT_UnitsState::instance.units[unitID].attackAtTileY);
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.field117_0x2290
                      [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame <= 0) {
                DAT_UnitHasBecomeIdle::instance = 1;
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].imageIDUnk
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                          .facingDirectionMapOrientationCorrected
                    + 0x1d9 + DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame * 8;
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumberHasJustIncremented
                    != FALSE
                && DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber == 15) {
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
                    ? 6
                    : 70;
            } else {
                damage = 10;
                building = 0;
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
        case OpenSHC::Map::Units::States::US_MELEE_ATTACK:
            DAT_UnitsState::instance.units[unitID].animationSpeed = 3;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            if (DAT_UnitsState::instance.units[unitID].attackedUnitID != 0
                && DAT_UnitsState::instance.units[unitID].animationCycleNumberHasJustIncremented != FALSE) {
                if (DAT_UnitsState::instance.units[unitID].animationCycleNumber == 7
                    || DAT_UnitsState::instance.units[unitID].animationCycleNumber == 16) {
                    MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::playHurtSFXForUnit, DAT_UnitsState::ptr)(
                        DAT_UnitsState::instance.units[unitID].attackedUnitID);
                }
                if ((DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber == 5
                        || DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber == 14)
                    && (DAT_UnitsState::instance
                                .units[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].attackedUnitID]
                                .unitType
                            == OpenSHC::Map::Units::UT_E_SPEAR
                        || DAT_UnitsState::instance
                                .units[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].attackedUnitID]
                                .unitType
                            == OpenSHC::Map::Units::UT_E_PIKE
                        || DAT_UnitsState::instance
                                .units[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].attackedUnitID]
                                .unitType
                            == OpenSHC::Map::Units::UT_LORD
                        || DAT_UnitsState::instance
                                .units[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].attackedUnitID]
                                .unitType
                            == OpenSHC::Map::Units::UT_E_MACE
                        || DAT_UnitsState::instance
                                .units[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].attackedUnitID]
                                .unitType
                            == OpenSHC::Map::Units::UT_E_SWORD
                        || DAT_UnitsState::instance
                                .units[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].attackedUnitID]
                                .unitType
                            == OpenSHC::Map::Units::UT_E_KNIGHT
                        || DAT_UnitsState::instance
                                .units[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].attackedUnitID]
                                .unitType
                            == OpenSHC::Map::Units::UT_A_ASSASSIN
                        || DAT_UnitsState::instance
                                .units[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].attackedUnitID]
                                .unitType
                            == OpenSHC::Map::Units::UT_A_SWORDSMAN)) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].x,
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].y,
                        OpenSHC::DE::SHCDE::FX_STEEL1);
                }
                if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber == 4
                    || DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber == 13) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].x,
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].y,
                        OpenSHC::DE::SHCDE::FX_SWISH);
                }
            }
            // horse
            if ((unitID & 1) == 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.field117_0x2290
                          [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
                if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame <= 0) {
                    DAT_UnitHasBecomeIdle::instance = 1;
                } else {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].imageIDUnk
                        = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                              .facingDirectionMapOrientationCorrected
                        + 0x1d9 + DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame * 8;
                }
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.field116_0x2264
                          [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
                if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame <= 0) {
                    DAT_UnitHasBecomeIdle::instance = 1;
                } else {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].imageIDUnk
                        = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                              .facingDirectionMapOrientationCorrected
                        + 0x371 + DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame * 8;
                }
            }
            // rider
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.field118_0x22dc
                      [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame <= 0) {
                DAT_UnitHasBecomeIdle::instance = 1;
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                          .facingDirectionMapOrientationCorrected
                    + 0xf9 + DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame * 8;
            }
            if (DAT_UnitHasBecomeIdle::instance == 0) {
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate
                = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate == 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::resumeMovementIfNoAttackTarget,
                DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance);
            return;
        case (UnitState)3:
            // cheering
            DAT_UnitsState::instance.units[unitID].animationSpeed = 8;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[unitID].field131_0x2ac = 10;
            DAT_UnitsState::instance.units[unitID].SA = 1;
            if (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_SKIRMISH_AND_MULTIPLAYER) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setUnitFacingDirectionBasedOnBuilding,
                    DAT_UnitsState::ptr)(unitID, DAT_GameState::instance.mapAndTime.signpostIDs[0]);
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.field114_0x2210
                      [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame <= 0) {
                DAT_UnitHasBecomeIdle::instance = 1;
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].imageIDUnk
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                          .facingDirectionMapOrientationCorrected
                    + 0x1d9 + DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame * 8;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.field115_0x223c
                      [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame <= 0) {
                DAT_UnitHasBecomeIdle::instance = 1;
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                          .facingDirectionMapOrientationCorrected
                    + 0xf9 + DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame * 8;
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
        case OpenSHC::Map::Units::States::US_IDLEUnk:
            DAT_UnitsState::instance.units[unitID].animationSpeed = 5;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[unitID].field131_0x2ac = 10;
            DAT_UnitsState::instance.units[unitID].SA = 1;
            // horse
            if ((unitID & 1) == 0) {
                DAT_UnitsState::instance.units[unitID].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp
                          .field111_0x2084[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
                if (DAT_UnitsState::instance.units[unitID].animationFrame <= 0) {
                    DAT_UnitHasBecomeIdle::instance = 1;
                } else {
                    DAT_UnitsState::instance.units[unitID].imageIDUnk
                        = DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected + 0x179
                        + DAT_UnitsState::instance.units[unitID].animationFrame * 8;
                }
            } else {
                DAT_UnitsState::instance.units[unitID].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp
                          .field112_0x2104[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
                if (DAT_UnitsState::instance.units[unitID].animationFrame <= 0) {
                    DAT_UnitHasBecomeIdle::instance = 1;
                } else {
                    DAT_UnitsState::instance.units[unitID].imageIDUnk
                        = DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected + 0x369
                        + DAT_UnitsState::instance.units[unitID].animationFrame * 8;
                }
            }
            // rider
            DAT_UnitsState::instance.units[unitID].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp
                      .field113_0x2184[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
            if (DAT_UnitsState::instance.units[unitID].animationFrame <= 0) {
                DAT_UnitHasBecomeIdle::instance = 1;
            } else {
                DAT_UnitsState::instance.units[unitID].gfxNumber
                    = DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected + 0xf9
                    + DAT_UnitsState::instance.units[unitID].animationFrame * 8;
            }
            if (DAT_UnitHasBecomeIdle::instance == 0) {
                return;
            }
            DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
            DAT_UnitsState::instance.units[unitID].state.generic
                = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::moveToFreeTileNearby, DAT_UnitsState::ptr)(unitID);
            return;
        case (UnitState)0x6c:
            DAT_UnitsState::instance.units[unitID].stateBasedSpeed = 0;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset = 1;
            return;
        case OpenSHC::Map::Units::States::US_JESTER_ROAM_TO:
            DAT_UnitsState::instance.units[unitID].disappearFadeAlphaCountdown
                += DAT_UnitsState::instance.units[unitID].engineerManningSiegeStateRef_checkType;
            if ((char)DAT_UnitsState::instance.units[unitID].disappearFadeAlphaCountdown < 0) {
                DAT_UnitsState::instance.units[unitID].disappearFadeAlphaCountdown = 0;
            } else if ((char)DAT_UnitsState::instance.units[unitID].disappearFadeAlphaCountdown > 31) {
                DAT_UnitsState::instance.units[unitID].disappearFadeAlphaCountdown = 31;
            }
            DAT_UnitsState::instance.units[unitID].updateTickTracker += 1;
            if (DAT_UnitsState::instance.units[unitID].updateTickTracker <= 32) {
                return;
            }
            DAT_UnitsState::instance.units[unitID].updateTickTracker = 0;
            DAT_UnitsState::instance.units[unitID].disappearFadeAlphaCountdown = 0;
            DAT_UnitsState::instance.units[unitID].state.generic = DAT_UnitsState::instance.units[unitID].cachedState;
            if ((char)DAT_UnitsState::instance.units[unitID].engineerManningSiegeStateRef_checkType < 0) {
                if (DAT_UnitsState::instance.units[unitID].isDisappearingUnk != 0) {
                    MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::prepareCampgroundCoords,
                        DAT_BuildingsState::ptr)(owner);
                    MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit, DAT_UnitsState::ptr)(
                        DAT_CurrentUnitSlotID::instance, DAT_BuildingsState::instance.DAT_TempXOffset,
                        DAT_BuildingsState::instance.DAT_TempYOffset, 0);
                }
                return;
            }
            if ((char)DAT_UnitsState::instance.units[unitID].engineerManningSiegeStateRef_checkType > 0
                && DAT_UnitsState::instance.units[unitID].isDisappearingUnk != 0) {
                DAT_UnitsState::instance.units[unitID].logicalState = OpenSHC::Map::Units::ULS_TRANSITIONING;
                DAT_UnitsState::instance.units[unitID].disappearFadeAlphaCountdown = 32;
            }
            return;
        case OpenSHC::Map::Units::States::US_DEATH_01:
            DAT_UnitsState::instance.units[unitID].facingDirection = 0;
            DAT_UnitsState::instance.units[unitID].animationSpeed = 2;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[unitID].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp
                      .ANIM_Worker_Shared1[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
            if (DAT_UnitsState::instance.units[unitID].animationFrame <= 0) {
                DAT_UnitsState::instance.units[unitID].gfxNumber = 0x178;
                DAT_UnitHasBecomeIdle::instance = 1;
            } else {
                DAT_UnitsState::instance.units[unitID].gfxNumber
                    = DAT_UnitsState::instance.units[unitID].animationFrame + 0x160;
            }
            if (DAT_UnitsState::instance.units[unitID].animationFrame <= 0) {
                DAT_UnitsState::instance.units[unitID].imageIDUnk = 0x270;
                DAT_UnitHasBecomeIdle::instance = 1;
            } else {
                DAT_UnitsState::instance.units[unitID].imageIDUnk
                    = DAT_UnitsState::instance.units[unitID].animationFrame + 600;
            }
            if (DAT_UnitHasBecomeIdle::instance != 0) {
                DAT_UnitsState::instance.units[unitID].state.generic = OpenSHC::Map::Units::States::US_DISAPPEAR;
            }
            if (DAT_UnitsState::instance.units[unitID].animationCycleNumberHasJustIncremented == FALSE) {
                return;
            }
            if (DAT_UnitsState::instance.units[unitID].animationCycleNumber == 1) {
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    DAT_UnitsState::instance.units[unitID].x, DAT_UnitsState::instance.units[unitID].y,
                    OpenSHC::DE::SHCDE::FX_HORSE_DIE);
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber == 15) {
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].x,
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].y,
                    OpenSHC::DE::SHCDE::FX_HORSE_FALL);
            }
            return;
        case OpenSHC::Map::Units::States::US_DEATH_02:
        case OpenSHC::Map::Units::States::US_DEATH_03:
        case OpenSHC::Map::Units::States::US_STONE_DEATH_01:
        case OpenSHC::Map::Units::States::US_STONE_DEATH_02:
        case OpenSHC::Map::Units::States::US_STONE_DEATH_03:
            DAT_UnitsState::instance.units[unitID].facingDirection = 0;
            DAT_UnitsState::instance.units[unitID].animationSpeed = 2;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[unitID].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp
                      .ANIM_Worker_Shared1[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
            if (DAT_UnitsState::instance.units[unitID].animationFrame <= 0) {
                DAT_UnitsState::instance.units[unitID].gfxNumber = 0x160;
                DAT_UnitHasBecomeIdle::instance = 1;
            } else {
                DAT_UnitsState::instance.units[unitID].gfxNumber
                    = DAT_UnitsState::instance.units[unitID].animationFrame + 0x148;
            }
            if (DAT_UnitsState::instance.units[unitID].animationFrame <= 0) {
                DAT_UnitsState::instance.units[unitID].imageIDUnk = 600;
                DAT_UnitHasBecomeIdle::instance = 1;
            } else {
                DAT_UnitsState::instance.units[unitID].imageIDUnk
                    = DAT_UnitsState::instance.units[unitID].animationFrame + 0x240;
            }
            if (DAT_UnitHasBecomeIdle::instance != 0) {
                DAT_UnitsState::instance.units[unitID].state.generic = OpenSHC::Map::Units::States::US_DISAPPEAR;
            }
            if (DAT_UnitsState::instance.units[unitID].animationCycleNumberHasJustIncremented == FALSE) {
                return;
            }
            if (DAT_UnitsState::instance.units[unitID].animationCycleNumber == 1) {
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    DAT_UnitsState::instance.units[unitID].x, DAT_UnitsState::instance.units[unitID].y,
                    OpenSHC::DE::SHCDE::FX_HORSE_DIE);
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber == 15) {
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].x,
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].y,
                    OpenSHC::DE::SHCDE::FX_HORSE_FALL);
            }
            return;
        case OpenSHC::Map::Units::States::US_DISAPPEAR:
            DAT_UnitsState::instance.units[unitID].disappearFadeAlphaCountdown += 1;
            if ((char)DAT_UnitsState::instance.units[unitID].disappearFadeAlphaCountdown <= 32) {
                return;
            }
            DAT_UnitsState::instance.units[unitID].disappearFadeAlphaCountdown = 32;
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
            // free the horse's place in the stables
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].horseOriginStablesBuildingIndexUnk != 0
                && DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].horseOriginStableIDUnk
                    == DAT_BuildingsState::instance
                        .buildings[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                                .horseOriginStablesBuildingIndexUnk]
                        .uid) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::removeTetheredUnitFromBuilding,
                    DAT_BuildingsState::ptr)(
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].horseOriginStablesBuildingIndexUnk,
                    unitID);
            }
            return;
        }
    }

}
}
