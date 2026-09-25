#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Navigation.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Units.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/DE/SHCDE/eSFX.hpp"
#include "OpenSHC/Map/Units/SomeTribeBehaviorType.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentUnitSlotID.hpp"
#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
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
    using OpenSHC::Map::Units::SomeTribeBehaviorType;
    using OpenSHC::Map::Units::UnitLogicState;
    using OpenSHC::Map::Units::States::UnitState;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x00563910
    void Units::UpdateLadderman()
    {
        int unitID = DAT_CurrentUnitSlotID::instance;
        int owner = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].owner;
        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].unknownV
            = DAT_TextureRenderCoreObject::instance
                  .gmFileHeaderColorpaletteArray[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                          .spriteID]
                  .originY;
        DAT_GameState::instance.playerDataArray[owner].armySize += 1;
        DAT_GameState::instance.playerDataArray[owner].currentLaddermen += 1;
        DAT_UnitsState::instance.units[unitID].calculatedOwnerPlayerIndex = owner;
        if (DAT_UnitsState::instance.units[unitID].isSelectable_OR_matchTime == 0) {
            DAT_UnitsState::instance.units[unitID].isSelectable_OR_matchTime
                = (short)DAT_GameCore::instance.mapTimeInTicks;
        }
        MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::addUnitToNewTribe, DAT_TribesState::ptr)(unitID);
        if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].laddermanIsInPosition != 0
            && DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic != (UnitState)3) {
            MACRO_CALL(OpenSHC::Map::Units_Func::DetachLadderman)(DAT_CurrentUnitSlotID::instance);
        }
        switch (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic) {
        case OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk:
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].unknownV += 0x10;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate = -1;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed = 0;
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].isDisappearingUnk != 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].disappearFadeAlphaCountdown -= 1;
                if ((char)DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].disappearFadeAlphaCountdown
                    < 0) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].disappearFadeAlphaCountdown = 0;
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].isDisappearingUnk = 0;
                }
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
                DAT_GameState::instance.playerDataArray[owner].someCount28 += 1;
                return;
            }
            // cower when enemies are close
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].closestEnemyMicroDistance <= 400) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].closestEnemyMicroDistance > 96
                    ? (UnitState)2
                    : OpenSHC::Map::Units::States::US_IDLEUnk;
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = OpenSHC::Map::Units::States::US_IDLEUnk;
            }
            if (DAT_TribesState::instance
                    .tribes[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].tribeID]
                    .tribeBehaviorType
                == OpenSHC::Map::Units::STBT_0x400) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = OpenSHC::Map::Units::States::US_DISAPPEAR;
            }
            return;
        case 0x69:
            // walking to the engineers guild assembly point
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSheetFrameOffset = 1;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0x10;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].unknownV += 0x20;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].calculatedMovementSpeed
                = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].movementSpeed;
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::hasUnitReachedDestination, DAT_UnitsState::ptr)(
                    DAT_CurrentUnitSlotID::instance)
                != FALSE) {
                if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::findFreeEngineerAssemblyTile,
                        DAT_BuildingsState::ptr)(owner, DAT_CurrentUnitSlotID::instance)
                    == 0) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].facingDirection = 4;
                } else {
                    MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit, DAT_UnitsState::ptr)(
                        DAT_CurrentUnitSlotID::instance, DAT_BuildingsState::instance.DAT_TempXOffset,
                        DAT_BuildingsState::instance.DAT_TempYOffset, 0);
                }
            }
            DAT_GameState::instance.playerDataArray[owner].someCount27 += 1;
            DAT_GameState::instance.playerDataArray[owner].someCount28 += 1;
            return;
        case OpenSHC::Map::Units::States::US_MOVE_TO_DESTINATION:
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].unknownV += 0x20;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0x10;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSheetFrameOffset = 1;
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].moveInstructionSpeedDelayTracker == 0
                && DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].movementRunUpTime == 0
                && DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].isMatchingSpeed == false) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed = 1;
            } else if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].moveInstructionSpeedDelayTracker
                <= 70) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed = 0;
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed = -1;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::hasUnitReachedDestination, DAT_UnitsState::ptr)(
                    DAT_CurrentUnitSlotID::instance)
                != FALSE) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed = 0;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
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
            }
            return;
        case OpenSHC::Map::Units::States::US_APPEAR:
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].unknownV += 0x20;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0x10;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSheetFrameOffset = 1;
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].moveInstructionSpeedDelayTracker == 0
                || DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].moveInstructionSpeedDelayTracker
                    <= 70) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed = 0;
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed = -1;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::hasUnitReachedDestination, DAT_UnitsState::ptr)(
                    DAT_CurrentUnitSlotID::instance)
                != FALSE) {
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
            }
            return;
        case 0x67:
            // walking to the wall with the ladder
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0x10;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].unknownV += 0x20;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSheetFrameOffset = 1;
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].moveInstructionSpeedDelayTracker == 0
                && DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].movementRunUpTime == 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed = 1;
            } else if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].moveInstructionSpeedDelayTracker
                <= 70) {
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
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic = (UnitState)3;
            DAT_DirectionAlgorithmState::instance.orientation
                = MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getOrientationThatIsWallTowerOrGatehouse,
                    DAT_TileMapState::ptr)(DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].x,
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].y);
            if (DAT_DirectionAlgorithmState::instance.orientation == 15) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = OpenSHC::Map::Units::States::US_IDLEUnk;
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].facingDirection
                = (short)DAT_DirectionAlgorithmState::instance.orientation;
            MACRO_CALL(OpenSHC::Map::Navigation_Func::UpdateLadderman_SetClimbData)(DAT_CurrentUnitSlotID::instance);
            MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].x,
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].y, OpenSHC::DE::SHCDE::FX_LADDER_PLACE);
            return;
        case 3:
            // holding the ladder against the wall
            DAT_TroopValueState::instance.attackInfo.field86986_0x20f98 += 1;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].seated = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field43_0x64 = -1;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].facingDirectionMapOrientationCorrected
                + 0xa1;
            return;
        case OpenSHC::Map::Units::States::US_IDLEUnk:
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].unknownV += 0x10;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSpeed = 5;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field131_0x2ac = 10;
            if ((DAT_CurrentUnitSlotID::instance & 1) == 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp
                          .fixme_integerArrayLadderMan[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                                  .animationCycleNumber];
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp
                          .fixme_integerArrayLadderMan2[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                                  .animationCycleNumber];
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame <= 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber = 0x81;
                DAT_UnitHasBecomeIdle::instance = 1;
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame + 0x80;
            }
            if (DAT_UnitHasBecomeIdle::instance != 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::moveToFreeTileNearby, DAT_UnitsState::ptr)(
                    DAT_CurrentUnitSlotID::instance);
            }
            return;
        case 2:
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].unknownV += 0x10;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSpeed = 5;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field131_0x2ac = 10;
            if ((DAT_CurrentUnitSlotID::instance & 1) == 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.field121_0x24a4
                          [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp
                          .fixme_integerArrayLadderMan3[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                                  .animationCycleNumber];
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame <= 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber = 0x91;
                DAT_UnitHasBecomeIdle::instance = 1;
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame + 0x90;
            }
            if (DAT_UnitHasBecomeIdle::instance != 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::moveToFreeTileNearby, DAT_UnitsState::ptr)(
                    DAT_CurrentUnitSlotID::instance);
            }
            return;
        case 0x6c:
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSheetFrameOffset = 1;
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
                    > 0
                && DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].isDisappearingUnk != 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].logicalState
                    = OpenSHC::Map::Units::ULS_TRANSITIONING;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].disappearFadeAlphaCountdown = 32;
            }
            return;
        case OpenSHC::Map::Units::States::US_DEATH_01:
        case OpenSHC::Map::Units::States::US_DEATH_03:
        case OpenSHC::Map::Units::States::US_STONE_DEATH_01:
        case OpenSHC::Map::Units::States::US_STONE_DEATH_02:
        case OpenSHC::Map::Units::States::US_STONE_DEATH_03:
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].facingDirection = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSpeed = 2;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.ANIM_Worker_Shared1
                      [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame <= 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber = 0xf8;
                DAT_UnitHasBecomeIdle::instance = 1;
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame + 0xe0;
            }
            if (DAT_UnitHasBecomeIdle::instance != 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = OpenSHC::Map::Units::States::US_DISAPPEAR;
            }
            return;
        case OpenSHC::Map::Units::States::US_DEATH_02:
            // killed while holding the ladder
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSpeed = 2;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.field123_0x2504
                      [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame <= 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                          .facingDirectionMapOrientationCorrected
                    + 0xd9;
                DAT_UnitHasBecomeIdle::instance = 1;
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                          .facingDirectionMapOrientationCorrected
                    + 0xa1 + DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame * 8;
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumberHasJustIncremented
                    != FALSE
                && DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber == 1) {
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].x,
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].y,
                    OpenSHC::DE::SHCDE::FX_LADDER_BREAK);
            }
            if (DAT_UnitHasBecomeIdle::instance != 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = OpenSHC::Map::Units::States::US_DISAPPEAR;
            }
            return;
        case OpenSHC::Map::Units::States::US_DISAPPEAR:
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].disappearFadeAlphaCountdown += 1;
            if ((char)DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].disappearFadeAlphaCountdown
                > 32) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].disappearFadeAlphaCountdown = 32;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].updateTickTracker += 1;
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].updateTickTracker > 32) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].logicalState
                    = OpenSHC::Map::Units::ULS_REMOVE;
            }
            return;
        }
    }

}
}
