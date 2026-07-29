#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/AI/AIType.hpp"
#include "OpenSHC/AI/AITypeInt.hpp"
#include "OpenSHC/AI/Tribes/AITribeType.hpp"
#include "OpenSHC/Commands/CommandBuildingType.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/Buildings/BuildingTypeShort.hpp"
#include "OpenSHC/Map/Units/SomeTribeBehaviorType.hpp"
#include "OpenSHC/Map/Units/UnitInstructionType.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_SkirmishDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace AI {

    using OpenSHC::AI::AIType;
    using OpenSHC::AI::AITypeInt;
    using OpenSHC::AI::Tribes::AITribeType;
    using OpenSHC::Commands::CommandBuildingType;
    using OpenSHC::Map::Buildings::BuildingType;
    using OpenSHC::Map::Buildings::BuildingTypeShort;
    using OpenSHC::Map::Units::SomeTribeBehaviorType;
    using OpenSHC::Map::Units::UnitInstructionType;
    using OpenSHC::Map::Units::UnitType;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x004D2000
    void AICState ::aiCreateSiegeUnits(int playerID)
    {
        AITypeInt _aiType = DAT_GameState::instance.playerDataArray[playerID].aiType;
        if (_aiType == OpenSHC::AI::AIT_NULL)
            return;

        int _engineersGuildID = DAT_GameState::instance.playerDataArray[playerID].engineersGuild.id;
        if (!((0 < _engineersGuildID)
                && (DAT_BuildingsState::instance.buildings[_engineersGuildID].buildingType
                    == OpenSHC::Map::Buildings::BT_ENGINEERSGUILD))
            || DAT_GameState::instance.playerDataArray[playerID].canStartSpending == 0)
            return;

        int _siegeInfoIndex = 0;
        int _incrementsBy5 = 0;
        int _mappingOffset = 0;
        int* _pDelay;

        do {
            UnitType _unitType
                = *(UnitType*)((int)&DAT_SkirmishDefinedData::instance.SiegeEngineMetaInfoArray[0].unitType
                    + _mappingOffset);
            int _tribeSize = DAT_GameState::instance.playerDataArray[playerID].aivUnitLocationSlotLocationCount[*(
                int*)((int)&DAT_SkirmishDefinedData::instance.SiegeEngineMetaInfoArray[0].slot + _mappingOffset)];
            int _slotIndex = 0;
            int _nextSlotIndex;

            if (_tribeSize >= 4)
                _tribeSize = 3;

            if (0 < _tribeSize) {
                do {
                    _nextSlotIndex = _slotIndex + 1;
                    int _location = DAT_GameState::instance.playerDataArray[playerID].aivUnitLocationSlots[*(
                        int*)((int)&DAT_SkirmishDefinedData::instance.SiegeEngineMetaInfoArray[0].slot
                        + _mappingOffset)][_slotIndex];

                    if (0 < _location) {
                        int _existingBuildingID = (int)(short)DAT_TileMapState::instance.BuildingLayer[_location];
                        int _engineIndex = _incrementsBy5 + _slotIndex;
                        int _unitID = DAT_GameState::instance.playerDataArray[playerID]
                                          .aiSiegeCreationInformation[0][_engineIndex]
                                          .unitID;
                        int _uid = DAT_GameState::instance.playerDataArray[playerID]
                                       .aiSiegeCreationInformation[0][_engineIndex]
                                       .uid;
                        int _tile = DAT_GameState::instance.playerDataArray[playerID]
                                        .aiSiegeCreationInformation[0][_engineIndex]
                                        .buildingID;

                        if ((_unitID == 0) || (DAT_UnitsState::instance.units[_unitID].uid == _uid)) {
                            if ((_tile == 0) || (DAT_BuildingsState::instance.buildings[_tile].uid == _uid)) {
                                if (_unitID == 0) {
                                    if (_tile == 0) {
                                        bool _doPlace = false;
                                        if (_existingBuildingID == 0) {
                                            if (0x1f < _mappingOffset)
                                                _doPlace = true;
                                        } else if ((_mappingOffset < 0x20)) {
                                            BuildingTypeShort _existingBuildingType
                                                = DAT_BuildingsState::instance.buildings[_existingBuildingID]
                                                      .buildingType;
                                            if (_existingBuildingType == OpenSHC::Map::Buildings::BT_TOWER4
                                                || _existingBuildingType == OpenSHC::Map::Buildings::BT_TOWER5)
                                                _doPlace = true;
                                        } else {
                                            _doPlace = true;
                                        }

                                        if (_doPlace) {
                                            int _requiredGold
                                                = DAT_BuildingsState::instance
                                                      .buildingCosts[*(int*)((int)&DAT_SkirmishDefinedData::instance
                                                                                 .SiegeEngineMetaInfoArray[0]
                                                                                 .buildingType
                                                          + _mappingOffset)]
                                                      .requiredGold;
                                            int _aicOffset = (_aiType + ~OpenSHC::AI::AIT_NULL) * 0x2a4;
                                            _pDelay = &DAT_GameState::instance.playerDataArray[playerID]
                                                           .aiSiegeCreationInformation[0][_engineIndex]
                                                           .delay;
                                            *_pDelay = *_pDelay + 1;
                                            if ((_requiredGold <= DAT_GameState::instance.playerDataArray[playerID]
                                                                      .currentResources[0xf]
                                                        + *(int*)((int)this + _aicOffset + 0x118))
                                                && (*(int*)((int)this + _aicOffset + 0x11c)
                                                    <= DAT_GameState::instance.playerDataArray[playerID]
                                                        .aiSiegeCreationInformation[0][_engineIndex]
                                                        .delay)) {
                                                int _y = (int)DAT_ViewportRenderState::instance
                                                             .DAT_TileTranslationMatrix_YComponent[_location];
                                                int _placeTile = _location
                                                    - DAT_ViewportRenderState::instance.translationMatrix[_y]
                                                          .addXgetTile;
                                                if (_siegeInfoIndex < 2) {
                                                    int _spawnedUnit = MACRO_CALL_MEMBER(
                                                        OpenSHC::Map::Units::UnitsState_Func::spawnUnit,
                                                        DAT_UnitsState::ptr)(playerID, playerID, _placeTile * 8 + 4,
                                                        _y * 8 + 4,
                                                        (int)((int)(DAT_BuildingsState::instance
                                                                .buildings[_existingBuildingID]
                                                                .terrainHeightUnk)),
                                                        _unitType);
                                                    DAT_GameState::instance.playerDataArray[playerID]
                                                        .aiSiegeCreationInformation[_siegeInfoIndex][_slotIndex]
                                                        .unitID = _spawnedUnit;
                                                    DAT_GameState::instance.playerDataArray[playerID]
                                                        .aiSiegeCreationInformation[_siegeInfoIndex][_slotIndex]
                                                        .uid = DAT_UnitsState::instance.units[_spawnedUnit].uid;
                                                    DAT_GameState::instance.playerDataArray[playerID]
                                                        .aiSiegeCreationInformation[_siegeInfoIndex][_slotIndex]
                                                        .buildingID = 0;
                                                    MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::
                                                                          processPlacementResourceLossForBuildingType,
                                                        DAT_BuildingsState::ptr)(playerID,
                                                        (BuildingType)((int)(DAT_SkirmishDefinedData::instance
                                                                .SiegeEngineMetaInfoArray[_siegeInfoIndex]
                                                                .buildingType)),
                                                        0);
                                                } else {
                                                    MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::placeBuilding,
                                                        DAT_TileMapState::ptr)(playerID, _placeTile, _y,
                                                        (CommandBuildingType)((
                                                            int)((uint)(ushort)(short)DAT_SkirmishDefinedData::instance
                                                                .SiegeEngineMetaInfoArray[_siegeInfoIndex]
                                                                .commandBuildingType)),
                                                        3, 0xf);
                                                    if (DAT_TileMapState::instance.buildingPlacementFail == FALSE) {
                                                        int* _pGold = DAT_GameState::instance.playerDataArray[playerID]
                                                                          .currentResources
                                                            + 0xf;
                                                        *_pGold = *_pGold - _requiredGold;
                                                        int _newBuildingID
                                                            = DAT_TileMapState::instance.DAT_PlacedBuildingID;
                                                        int _newUID = DAT_BuildingsState::instance
                                                                          .buildings[DAT_TileMapState::instance
                                                                                  .DAT_PlacedBuildingID]
                                                                          .uid;
                                                        DAT_GameState::instance.playerDataArray[playerID]
                                                            .aiSiegeCreationInformation[_siegeInfoIndex][_slotIndex]
                                                            .unitID = 0;
                                                        DAT_GameState::instance.playerDataArray[playerID]
                                                            .aiSiegeCreationInformation[_siegeInfoIndex][_slotIndex]
                                                            .uid = _newUID;
                                                        DAT_GameState::instance.playerDataArray[playerID]
                                                            .aiSiegeCreationInformation[_siegeInfoIndex][_slotIndex]
                                                            .buildingID = _newBuildingID;
                                                    }
                                                }
                                                *(undefined4*)(playerID * 0x39f4 + 0x115f48c + _slotIndex * 20
                                                    + _siegeInfoIndex * 100) = 0;
                                                return;
                                            }
                                        }
                                    } else {
                                        int _requiredEngineerCount
                                            = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::
                                                                    getRequiredEngineerCountForSiegeBuilding,
                                                DAT_BuildingsState::ptr)(_tile);
                                        if (DAT_BuildingsState::instance.buildings[_tile].currentEmployeeCount
                                            != _requiredEngineerCount) {
                                            if (_requiredEngineerCount
                                                <= DAT_GameState::instance.playerDataArray[playerID]
                                                    .engineerCountRelated) {
                                                int _engineersTribe = MACRO_CALL_MEMBER(
                                                    OpenSHC::AI::AICState_Func::assignRequiredIdleEngineersToNewTribe,
                                                    this)(playerID, _requiredEngineerCount);
                                                DAT_TribesState::instance.tribes[_engineersTribe].tribeType
                                                    = OpenSHC::AI::Tribes::AITT_ENGINEERS;
                                                DAT_TribesState::instance.tribes[_engineersTribe].tribeBehaviorType
                                                    = OpenSHC::Map::Units::STBT_0x410_SIEGE_EQUIPMENT_CONSTRUCTION;
                                                MACRO_CALL_MEMBER(
                                                    OpenSHC::Map::Units::TribesState_Func::giveTribeAnInstruction,
                                                    DAT_TribesState::ptr)(_engineersTribe,
                                                    OpenSHC::Map::Units::
                                                        UIT_CONSTRUCT_SIEGE_EQUIPMENTOIL_DUTYENGINEERRELATED,
                                                    _tile, DAT_BuildingsState::instance.buildings[_tile].uid, 0);
                                                return;
                                            }
                                            DAT_GameState::instance.playerDataArray[playerID].isEngineerRequired = TRUE;
                                        }
                                    }
                                } else {
                                    if (_tile != 0) {
                                        int _requiredEngineerCount2
                                            = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::
                                                                    getRequiredEngineerCountForSiegeBuilding,
                                                DAT_BuildingsState::ptr)(_tile);
                                        if (DAT_BuildingsState::instance.buildings[_tile].currentEmployeeCount
                                            != _requiredEngineerCount2) {
                                            if (_requiredEngineerCount2
                                                <= DAT_GameState::instance.playerDataArray[playerID]
                                                    .engineerCountRelated) {
                                                int _engineersTribe2 = MACRO_CALL_MEMBER(
                                                    OpenSHC::AI::AICState_Func::assignRequiredIdleEngineersToNewTribe,
                                                    this)(playerID, _requiredEngineerCount2);
                                                DAT_TribesState::instance.tribes[_engineersTribe2].tribeType
                                                    = OpenSHC::AI::Tribes::AITT_ENGINEERS;
                                                DAT_TribesState::instance.tribes[_engineersTribe2].tribeBehaviorType
                                                    = OpenSHC::Map::Units::STBT_0x410_SIEGE_EQUIPMENT_CONSTRUCTION;
                                                MACRO_CALL_MEMBER(
                                                    OpenSHC::Map::Units::TribesState_Func::giveTribeAnInstruction,
                                                    DAT_TribesState::ptr)(_engineersTribe2,
                                                    OpenSHC::Map::Units::
                                                        UIT_CONSTRUCT_SIEGE_EQUIPMENTOIL_DUTYENGINEERRELATED,
                                                    _tile, DAT_BuildingsState::instance.buildings[_tile].uid, 0);
                                                return;
                                            }
                                            DAT_GameState::instance.playerDataArray[playerID].isEngineerRequired = TRUE;
                                        }
                                    } else {
                                        int _remainingRequiredEngineers = MACRO_CALL_MEMBER(
                                            OpenSHC::Map::Units::UnitsState_Func::getRemainingRequiredEngineers,
                                            DAT_UnitsState::ptr)(_unitID);
                                        if (0 < _remainingRequiredEngineers) {
                                            if (DAT_GameState::instance.playerDataArray[playerID].engineerCountRelated
                                                < _remainingRequiredEngineers) {
                                                DAT_GameState::instance.playerDataArray[playerID].isEngineerRequired
                                                    = TRUE;
                                            } else {
                                                int _tribeID = MACRO_CALL_MEMBER(
                                                    OpenSHC::AI::AICState_Func::assignRequiredIdleEngineersToNewTribe,
                                                    this)(playerID, _remainingRequiredEngineers);
                                                int _targetUnitID = (int)DAT_TribesState::instance.tribes[_tribeID]
                                                                        .selectionTargetUnitID;
                                                if ((_targetUnitID != 0)
                                                    && (MACRO_CALL_MEMBER(
                                                            OpenSHC::Map::Navigation::PathFindingState_Func::
                                                                calculateCanPlayerUnitsNavigateToAreaFromArea,
                                                            DAT_PathFindingState::ptr)(playerID,
                                                            (dword)((int)((int)(short)DAT_TileMapState::instance
                                                                    .PathConnectionLayer[DAT_UnitsState::instance
                                                                            .units[_unitID]
                                                                            .tile])),
                                                            (dword)((int)((int)(short)DAT_TileMapState::instance
                                                                    .PathConnectionLayer[DAT_UnitsState::instance
                                                                            .units[_targetUnitID]
                                                                            .tile])),
                                                            0)
                                                        != 0)) {
                                                    DAT_TribesState::instance.tribes[_tribeID].tribeType
                                                        = OpenSHC::AI::Tribes::AITT_ENGINEERS;
                                                    DAT_TribesState::instance.tribes[_tribeID].tribeBehaviorType
                                                        = OpenSHC::Map::Units::STBT_0x41c;
                                                    MACRO_CALL_MEMBER(
                                                        OpenSHC::Map::Units::UnitsState_Func::relayTribeInstruction,
                                                        DAT_UnitsState::ptr)(_tribeID,
                                                        OpenSHC::Map::Units::UIT_MAN_SIEGE_EQUIPMENT, _unitID,
                                                        DAT_UnitsState::instance.units[_unitID].uid, 0);
                                                    return;
                                                }
                                            }
                                        }
                                    }
                                }
                            } else {
                                DAT_GameState::instance.playerDataArray[playerID]
                                    .aiSiegeCreationInformation[0][_engineIndex]
                                    .unitID = 0;
                                DAT_GameState::instance.playerDataArray[playerID]
                                    .aiSiegeCreationInformation[0][_engineIndex]
                                    .uid = 0;
                                DAT_GameState::instance.playerDataArray[playerID]
                                    .aiSiegeCreationInformation[0][_engineIndex]
                                    .delay = 0;
                                DAT_GameState::instance.playerDataArray[playerID]
                                    .aiSiegeCreationInformation[0][_engineIndex]
                                    .unknown = 0;
                                DAT_GameState::instance.playerDataArray[playerID]
                                    .aiSiegeCreationInformation[0][_engineIndex]
                                    .buildingID = 0;
                            }
                        } else {
                            DAT_GameState::instance.playerDataArray[playerID]
                                .aiSiegeCreationInformation[0][_engineIndex]
                                .unitID = 0;
                            DAT_GameState::instance.playerDataArray[playerID]
                                .aiSiegeCreationInformation[0][_engineIndex]
                                .uid = 0;
                            DAT_GameState::instance.playerDataArray[playerID]
                                .aiSiegeCreationInformation[0][_engineIndex]
                                .delay = 0;
                            DAT_GameState::instance.playerDataArray[playerID]
                                .aiSiegeCreationInformation[0][_engineIndex]
                                .unknown = 0;
                            DAT_GameState::instance.playerDataArray[playerID]
                                .aiSiegeCreationInformation[0][_engineIndex]
                                .buildingID = 0;
                        }
                    }

                    _slotIndex = _nextSlotIndex;
                } while (_nextSlotIndex < _tribeSize);
            }

            _siegeInfoIndex = _siegeInfoIndex + 1;
            _incrementsBy5 = _incrementsBy5 + 5;
            _mappingOffset = _mappingOffset + 16;
            if (64 < _mappingOffset)
                return;
        } while (true);
    }
}
}
