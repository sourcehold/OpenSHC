#include "../Units.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/DE/SHCDE/eSFX.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"
#include "OpenSHC/Map/Units/Pathfinding/DestinationNeededEnum.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentUnitSlotID.hpp"
#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitHasBecomeIdle.hpp"
#include "OpenSHC/Globals/DAT_UnitPropertiesDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x00552F80
    void Units::UpdateHopsFarmer()
    {
        int unitID = DAT_CurrentUnitSlotID::instance;
        int const farm = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].workplaceBuildingID_1;
        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].unitTypeSpecificRestingState = 1;
        UnitStateShort const state = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic;
        if (state == OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk) {
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].isDisappearingUnk != 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].disappearFadeAlphaCountdown--;
                if ((char)DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].disappearFadeAlphaCountdown
                    < 0) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].disappearFadeAlphaCountdown = 0;
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].isDisappearingUnk = 0;
                }
                return;
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].goToRallyPoint != 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].goToRallyPoint = 0;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = OpenSHC::Map::Units::States::US_STATE_2Unk;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].destinationNeeded
                    = OpenSHC::Map::Units::Pathfinding::DNE_UNKNOWN_2;
            }
        } else if (state == OpenSHC::Map::Units::States::US_IDLEUnk) {
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSpeed = 2;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x58 = 1;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x2ac = 1;
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate == 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.field_0x4d3c
                          [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.field_0x4de4
                          [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame <= 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber = 769;
                DAT_UnitHasBecomeIdle::instance = 1;
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame + 768;
            }
            if (MACRO_CALL(OpenSHC::Map::Units_Func::SetStateToFreetimeWalking)(
                    DAT_CurrentUnitSlotID::instance, DAT_UnitHasBecomeIdle::instance, 0)
                || DAT_UnitHasBecomeIdle::instance == 0) {
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
            if (!MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::setNewOnFarmDestination,
                    DAT_BuildingsState::ptr)(farm)) {
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                = DAT_BuildingsState::instance.buildings[farm].farmGrowState;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].destinationYPosition
                = DAT_ViewportRenderState::instance
                      .tileTranslationMatrix_YComponent[DAT_BuildingsState::instance.farmerDestinationTile];
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].destinationXPosition
                = DAT_BuildingsState::instance.farmerDestinationTile
                - DAT_ViewportRenderState::instance
                      .translationMatrix[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                              .destinationYPosition]
                      .addXgetTile;
            if (!MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit, DAT_UnitsState::ptr)(
                    DAT_CurrentUnitSlotID::instance,
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].destinationXPosition
                        + DAT_BuildingsState::instance.hopFarmerDestinationOffsetX,
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].destinationYPosition
                        + DAT_BuildingsState::instance.hopFarmerDestinationOffsetY,
                    0)) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = OpenSHC::Map::Units::States::US_IDLEUnk;
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].destinationTilePosition
                = DAT_BuildingsState::instance.farmerDestinationTile;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetedBuildingTile
                = DAT_BuildingsState::instance.farmerDestinationTile;
        } else if (state == OpenSHC::Map::Units::States::US_STATE_2Unk) {
            MACRO_CALL(OpenSHC::Map::Units_Func::IncrementAndOptionalUpdateAVValueRelated)(
                DAT_CurrentUnitSlotID::instance, FALSE);
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].destinationNeeded
                != OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET) {
                if (MACRO_CALL(OpenSHC::Map::Units_Func::UpdateWorker_ConsiderTakingABreakUnk)(
                        DAT_CurrentUnitSlotID::instance)) {
                    return;
                }
                if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit, DAT_UnitsState::ptr)(
                        unitID, DAT_UnitsState::instance.units[unitID].targetX_2,
                        DAT_UnitsState::instance.units[unitID].targetY_2, 0)) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].destinationNeeded
                        = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET;
                } else {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                        = OpenSHC::Map::Units::States::US_DISAPPEAR;
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].updateTickTracker = 0;
                    return;
                }
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSheetFrameOffset = 1;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 16;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::hasUnitReachedDestination, DAT_UnitsState::ptr)(
                    DAT_CurrentUnitSlotID::instance)) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = OpenSHC::Map::Units::States::US_IDLEUnk;
            }
        } else if (state == OpenSHC::Map::Units::States::US_STATE_3Unk) {
            // walking to a field to plant
            MACRO_CALL(OpenSHC::Map::Units_Func::IncrementAndOptionalUpdateAVValueRelated)(
                DAT_CurrentUnitSlotID::instance, FALSE);
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSheetFrameOffset = 1;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 16;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x58 = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
            if (!MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::hasUnitReachedDestination,
                    DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance)) {
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                = OpenSHC::Map::Units::States::US_RELOAD_WEAPONUnk;
            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::calculateOrientationFromTiles,
                DAT_DirectionAlgorithmState::ptr)(DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].tile,
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].destinationTilePosition);
            if (DAT_DirectionAlgorithmState::instance.orientation == 15) {
                DAT_DirectionAlgorithmState::instance.orientation = 4;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].facingDirection
                = DAT_DirectionAlgorithmState::instance.orientation;
        } else if (state == OpenSHC::Map::Units::States::US_RELOAD_WEAPONUnk) {
            // planting
            MACRO_CALL(OpenSHC::Map::Units_Func::IncrementAndOptionalUpdateAVValueRelated)(
                DAT_CurrentUnitSlotID::instance, FALSE);
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x58 = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x37e = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.field_0x4e30
                      [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame <= 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                            .facingDirectionMapOrientationCorrected
                        / 2
                    + 848;
                DAT_UnitHasBecomeIdle::instance = 1;
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                            .facingDirectionMapOrientationCorrected
                        / 2
                    + 845 + DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame * 4;
            }
            if (DAT_UnitHasBecomeIdle::instance == 0) {
                return;
            }
            DAT_TileMapState::instance
                .DamageLayer[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetedBuildingTile] = 2;
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::setNewOnFarmDestination,
                    DAT_BuildingsState::ptr)(farm)
                && DAT_BuildingsState::instance.buildings[farm].farmGrowState == 3) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].destinationYPosition
                    = DAT_ViewportRenderState::instance
                          .tileTranslationMatrix_YComponent[DAT_BuildingsState::instance.farmerDestinationTile];
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].destinationXPosition
                    = DAT_BuildingsState::instance.farmerDestinationTile
                    - DAT_ViewportRenderState::instance
                          .translationMatrix[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                                  .destinationYPosition]
                          .addXgetTile;
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit, DAT_UnitsState::ptr)(
                    DAT_CurrentUnitSlotID::instance,
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].destinationXPosition
                        + DAT_BuildingsState::instance.hopFarmerDestinationOffsetX,
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].destinationYPosition
                        + DAT_BuildingsState::instance.hopFarmerDestinationOffsetY,
                    0);
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].destinationTilePosition
                    = DAT_BuildingsState::instance.farmerDestinationTile;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetedBuildingTile
                    = DAT_BuildingsState::instance.farmerDestinationTile;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = OpenSHC::Map::Units::States::US_STATE_3Unk;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].resourceToDeposit = 0;
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                = OpenSHC::Map::Units::States::US_STATE_2Unk;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].destinationNeeded
                = OpenSHC::Map::Units::Pathfinding::DNE_UNKNOWN_2;
        } else if (state == OpenSHC::Map::Units::States::US_AIM_WEAPONUnk) {
            // walking to a field to harvest
            MACRO_CALL(OpenSHC::Map::Units_Func::IncrementAndOptionalUpdateAVValueRelated)(
                DAT_CurrentUnitSlotID::instance, FALSE);
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 16;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x58 = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSheetFrameOffset = 1;
            if (!MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::hasUnitReachedDestination,
                    DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance)) {
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
            DAT_UnitHasBecomeIdle::instance = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                = OpenSHC::Map::Units::States::US_FIRE_WEAPONUnk;
            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::calculateOrientationFromTiles,
                DAT_DirectionAlgorithmState::ptr)(DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].tile,
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].destinationTilePosition);
            if (DAT_DirectionAlgorithmState::instance.orientation == 15) {
                DAT_DirectionAlgorithmState::instance.orientation = 4;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].facingDirection
                = DAT_DirectionAlgorithmState::instance.orientation;
        } else if (state == OpenSHC::Map::Units::States::US_FIRE_WEAPONUnk) {
            // harvesting
            MACRO_CALL(OpenSHC::Map::Units_Func::IncrementAndOptionalUpdateAVValueRelated)(
                DAT_CurrentUnitSlotID::instance, FALSE);
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x58 = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x37e = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.field_0x4e68
                      [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame <= 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                            .facingDirectionMapOrientationCorrected
                        / 2
                    + 784;
                DAT_UnitHasBecomeIdle::instance = 1;
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                            .facingDirectionMapOrientationCorrected
                        / 2
                    + 780 + DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame * 4;
            }
            if (DAT_UnitHasBecomeIdle::instance == 0) {
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].resourceToDeposit++;
            DAT_TileMapState::instance
                .DamageLayer[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetedBuildingTile] = 80;
            OpenSHC::WindowsHelper::Enums::BOOLEnum const found = MACRO_CALL_MEMBER(
                OpenSHC::Map::Buildings::BuildingsState_Func::setNewOnFarmDestination, DAT_BuildingsState::ptr)(farm);
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].resourceToDeposit >= 6) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = OpenSHC::Map::Units::States::US_LOOK_AROUNDUnk;
                return;
            }
            if (!found || DAT_BuildingsState::instance.buildings[farm].farmGrowState != 5) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = OpenSHC::Map::Units::States::US_STATE_2Unk;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].destinationNeeded
                    = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_NEEDED;
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                = OpenSHC::Map::Units::States::US_AIM_WEAPONUnk;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].destinationYPosition
                = DAT_ViewportRenderState::instance
                      .tileTranslationMatrix_YComponent[DAT_BuildingsState::instance.farmerDestinationTile];
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].destinationXPosition
                = DAT_BuildingsState::instance.farmerDestinationTile
                - DAT_ViewportRenderState::instance
                      .translationMatrix[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                              .destinationYPosition]
                      .addXgetTile;
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit, DAT_UnitsState::ptr)(
                DAT_CurrentUnitSlotID::instance,
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].destinationXPosition
                    + DAT_BuildingsState::instance.hopFarmerDestinationOffsetX,
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].destinationYPosition
                    + DAT_BuildingsState::instance.hopFarmerDestinationOffsetY,
                0);
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].destinationTilePosition
                = DAT_BuildingsState::instance.farmerDestinationTile;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetedBuildingTile
                = DAT_BuildingsState::instance.farmerDestinationTile;
        } else if (state == OpenSHC::Map::Units::States::US_LOOK_AROUNDUnk) {
            // waiting with the harvest
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSheetFrameOffset = 913;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 16;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x2ac = 1;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].updateTickTracker++;
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].updateTickTracker <= 10) {
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].updateTickTracker = 0;
            int const storage
                = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingThatCanStoreThisResource,
                    DAT_BuildingsState::ptr)(OpenSHC::Game::Resources::RT_HOPS, 1,
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].owner);
            if (storage == 0
                && DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].owner
                    == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                MACRO_CALL(OpenSHC::Map::Units_Func::PlayStockpileIsFullWarning)();
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::buildingIsAccessible,
                    DAT_BuildingsState::ptr)(storage, 1)
                    != 0
                && MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit, DAT_UnitsState::ptr)(
                    DAT_CurrentUnitSlotID::instance, DAT_BuildingsState::instance.buildings[storage].buildingEntryX,
                    DAT_BuildingsState::instance.buildings[storage].buildingEntryY, 0)) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetID_OR_targetBuildingID = storage;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetUID
                    = DAT_BuildingsState::instance.buildings[storage].uid;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = OpenSHC::Map::Units::States::US_STAND_UPUnk;
                if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].resourceToDeposit = MACRO_CALL(
                        OpenSHC::Map::Units_Func::ComputeGoodsProduced)(DAT_CurrentUnitSlotID::instance, 2, TRUE);
                } else {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].resourceToDeposit = MACRO_CALL(
                        OpenSHC::Map::Units_Func::ComputeGoodsProduced)(DAT_CurrentUnitSlotID::instance, 1, TRUE);
                }
            }
        } else if (state == OpenSHC::Map::Units::States::US_STAND_UPUnk) {
            // carrying hops to the stockpile
            MACRO_CALL(OpenSHC::Map::Units_Func::IncrementAndOptionalUpdateAVValueRelated)(
                DAT_CurrentUnitSlotID::instance, FALSE);
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSheetFrameOffset = 913;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 16;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].updateTickTracker++;
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].updateTickTracker < 5) {
                return;
            }
            if (!MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::hasUnitReachedDestination,
                    DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance)) {
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].updateTickTracker = 0;
            if (MACRO_CALL_MEMBER(
                    OpenSHC::Map::Buildings::BuildingsState_Func::canBuildingStoreTheAmount, DAT_BuildingsState::ptr)(
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetID_OR_targetBuildingID,
                    OpenSHC::Game::Resources::RT_HOPS, 16)
                != 0) {
                MACRO_CALL_MEMBER(
                    OpenSHC::Map::Buildings::BuildingsState_Func::addResourceToStockpile, DAT_BuildingsState::ptr)(
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetID_OR_targetBuildingID,
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetUID,
                    OpenSHC::Game::Resources::RT_HOPS, 1, 16, 1);
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].resourceToDeposit--;
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].x,
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].y,
                    OpenSHC::DE::SHCDE::FX_STOCK_HOPS);
            } else {
                // the original reads the slot again here (without this line: quick_diff 0.9971 -> 0.9949)
                unitID = DAT_CurrentUnitSlotID::instance;
                int const storage = MACRO_CALL_MEMBER(
                    OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingThatCanStoreThisResource,
                    DAT_BuildingsState::ptr)(
                    OpenSHC::Game::Resources::RT_HOPS, 1, DAT_UnitsState::instance.units[unitID].owner);
                if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::buildingIsAccessible,
                        DAT_BuildingsState::ptr)(storage, 1)
                    != 0) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetID_OR_targetBuildingID
                        = storage;
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetUID
                        = DAT_BuildingsState::instance.buildings[storage].uid;
                    if (!MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit,
                            DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance,
                            DAT_BuildingsState::instance.buildings[storage].buildingEntryX,
                            DAT_BuildingsState::instance.buildings[storage].buildingEntryY, 0)) {
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].resourceToDeposit = 0;
                    }
                } else {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].resourceToDeposit = 0;
                }
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].resourceToDeposit > 0) {
                return;
            }
            // read again: the original reloads workplaceBuildingID_1 after the calls (reusing farm: 0.9272)
            int const ownFarm = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].workplaceBuildingID_1;
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::setNewOnFarmDestination,
                    DAT_BuildingsState::ptr)(ownFarm)
                && DAT_BuildingsState::instance.buildings[ownFarm].farmGrowState == 5) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = OpenSHC::Map::Units::States::US_AIM_WEAPONUnk;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].destinationYPosition
                    = DAT_ViewportRenderState::instance
                          .tileTranslationMatrix_YComponent[DAT_BuildingsState::instance.farmerDestinationTile];
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].destinationXPosition
                    = DAT_BuildingsState::instance.farmerDestinationTile
                    - DAT_ViewportRenderState::instance
                          .translationMatrix[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                                  .destinationYPosition]
                          .addXgetTile;
                if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit, DAT_UnitsState::ptr)(
                        DAT_CurrentUnitSlotID::instance,
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].destinationXPosition
                            + DAT_BuildingsState::instance.hopFarmerDestinationOffsetX,
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].destinationYPosition
                            + DAT_BuildingsState::instance.hopFarmerDestinationOffsetY,
                        0)) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].destinationTilePosition
                        = DAT_BuildingsState::instance.farmerDestinationTile;
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetedBuildingTile
                        = DAT_BuildingsState::instance.farmerDestinationTile;
                    return;
                }
            }
            MACRO_CALL(OpenSHC::Map::Units_Func::IncrementAndOptionalUpdateAVValueRelated)(
                DAT_CurrentUnitSlotID::instance, TRUE);
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                = OpenSHC::Map::Units::States::US_STATE_2Unk;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].destinationNeeded
                = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_NEEDED;
        } else if (state == OpenSHC::Map::Units::States::US_UNKNOWN_121) {
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSheetFrameOffset = 1;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 16;
            MACRO_CALL(OpenSHC::Map::Units_Func::SetRestingForUnit)(DAT_CurrentUnitSlotID::instance);
        } else if (state == OpenSHC::Map::Units::States::US_UNKNOWN_108) {
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSheetFrameOffset = 1;
        } else if (state == OpenSHC::Map::Units::States::US_DEATH_01) {
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].facingDirection = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSpeed = 2;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.ANIM_Worker_Shared1
                      [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame <= 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber = 1440;
                DAT_UnitHasBecomeIdle::instance = 1;
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame + 1416;
            }
            if (DAT_UnitHasBecomeIdle::instance != 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = OpenSHC::Map::Units::States::US_DISAPPEAR;
            }
        } else if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::checkIfCitizenUnitIsAliveBasedOnState,
                       DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance)) {
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].facingDirection = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSpeed = 2;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp.ANIM_Worker_Shared1
                      [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame <= 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber = 1416;
                DAT_UnitHasBecomeIdle::instance = 1;
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame + 1392;
            }
            if (DAT_UnitHasBecomeIdle::instance != 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = OpenSHC::Map::Units::States::US_DISAPPEAR;
            }
        } else if (state == OpenSHC::Map::Units::States::US_DISAPPEAR) {
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].disappearFadeAlphaCountdown++;
            if ((char)DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].disappearFadeAlphaCountdown
                > 32) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].disappearFadeAlphaCountdown = 32;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].updateTickTracker++;
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].updateTickTracker > 32) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].logicalState
                    = OpenSHC::Map::Units::ULS_REMOVE;
                if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].killedFlagUnk == 0) {
                    MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::setLastEncounteredTroopUnit,
                        DAT_GameState::ptr)(DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].owner,
                        DAT_CurrentUnitSlotID::instance);
                }
            }
            DAT_BuildingsState::instance
                .buildings[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].workplaceBuildingID_1]
                .idleTimerUnk = 4000;
        } else {
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                = OpenSHC::Map::Units::States::US_IDLEUnk;
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::makeUnitStopWalkingByClearingPathProgressState,
                DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance);
        }
    }

}
}
