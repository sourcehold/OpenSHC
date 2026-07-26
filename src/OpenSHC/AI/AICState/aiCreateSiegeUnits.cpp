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

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000 */

    // FUNCTION: STRONGHOLDCRUSADER 0x004D2000
    void AICState ::aiCreateSiegeUnits(int playerID)

    {

        int _existingBuildingID;

        int _spawnedUnit;

        int _requiredEngineerCount;

        int _remainingRequiredEngineers;

        int _tribeID;

        int _targetUnitID;

        int _area;

        int _engineersTribe;

        int _aicOffset;

        int _y;

        int _slotIndex;

        int _nextSlotIndex;

        int _tile;

        int _mappingOffset;

        int _incrementsBy5;

        int _siegeInfoIndex;

        int _tribeSize;

        int _requiredGold;

        int _engineersGuildID;

        int _newUID;

        int _newBuildingID;

        int* _pGold;

        int _engineIndex;

        int _uid;

        int _unitID;

        int _location;

        AITypeInt _aiType;

        BuildingTypeShort _existingBuildingType;

        int* _pDelay;

        UnitType _unitType;

        _aiType = DAT_GameState::instance.playerDataArray[playerID].aiType;

        if (_aiType != OpenSHC::AI::AIT_NULL) {

            _engineersGuildID = DAT_GameState::instance.playerDataArray[playerID].engineersGuild.id;

            if (((0 < _engineersGuildID)
                    && (DAT_BuildingsState::instance.buildings[_engineersGuildID].buildingType
                        == OpenSHC::Map::Buildings::BT_ENGINEERSGUILD))
                && (DAT_GameState::instance.playerDataArray[playerID].canStartSpending != 0)) {

                _siegeInfoIndex = 0;

                _incrementsBy5 = 0;

                _mappingOffset = 0;

                do {

                    _unitType
                        = *(UnitType*)((int)&DAT_SkirmishDefinedData::instance.DAT_SiegeEngineMetaInfoArray[0].unitType
                            + _mappingOffset);

                    _tribeSize = DAT_GameState::instance.playerDataArray[playerID].aivUnitLocationSlotLocationCount[*(
                        int*)((int)&DAT_SkirmishDefinedData::instance.DAT_SiegeEngineMetaInfoArray[0].slot
                        + _mappingOffset)];

                    _slotIndex = 0;

                    if (_tribeSize < 4) {

                        if (0 < _tribeSize)
                            goto LAB_004d20c0;

                    }

                    else {

                        _tribeSize = 3;

                    LAB_004d20c0:
                        do {

                            _nextSlotIndex = _slotIndex + 1;

                            _location = DAT_GameState::instance.playerDataArray[playerID].aivUnitLocationSlots[*(
                                int*)((int)&DAT_SkirmishDefinedData::instance.DAT_SiegeEngineMetaInfoArray[0].slot
                                + _mappingOffset)][_slotIndex];

                            if (0 < _location) {

                                _existingBuildingID = (int)(short)DAT_TileMapState::instance.BuildingLayer[_location];

                                _engineIndex = _incrementsBy5 + _slotIndex;

                                _unitID = DAT_GameState::instance.playerDataArray[playerID]
                                              .aiSiegeCreationInformation[0][_engineIndex]
                                              .unitID;

                                _uid = DAT_GameState::instance.playerDataArray[playerID]
                                           .aiSiegeCreationInformation[0][_engineIndex]
                                           .uid;

                                _tile = DAT_GameState::instance.playerDataArray[playerID]
                                            .aiSiegeCreationInformation[0][_engineIndex]
                                            .buildingID;

                                if ((_unitID == 0) || (DAT_UnitsState::instance.units[_unitID].uid == _uid)) {

                                    if ((_tile == 0) || (DAT_BuildingsState::instance.buildings[_tile].uid == _uid)) {

                                        if (_unitID == 0) {

                                            if (_tile == 0) {

                                                if (_existingBuildingID == 0) {

                                                    if (0x1f < _mappingOffset)
                                                        goto LAB_004d21d4;

                                                }

                                                else if ((_mappingOffset < 0x20)
                                                    && ((_existingBuildingType
                                                        = DAT_BuildingsState::instance.buildings[_existingBuildingID]
                                                            .buildingType,
                                                        _existingBuildingType == OpenSHC::Map::Buildings::BT_TOWER4
                                                            || (_existingBuildingType
                                                                == OpenSHC::Map::Buildings::BT_TOWER5)))) {

                                                LAB_004d21d4:
                                                    _requiredGold
                                                        = DAT_BuildingsState::instance
                                                              .buildingCosts[*(
                                                                  int*)((int)&DAT_SkirmishDefinedData::instance
                                                                            .DAT_SiegeEngineMetaInfoArray[0]
                                                                            .buildingType
                                                                  + _mappingOffset)]
                                                              .requiredGold;

                                                    _aicOffset = (_aiType + ~OpenSHC::AI::AIT_NULL) * 0x2a4;

                                                    /*
                                                                              defSiegeEngineGoldThreshold */

                                                    /*
                                                                              defSiegeEngineBuildDelay */

                                                    if ((_requiredGold
                                                            <= DAT_GameState::instance.playerDataArray[playerID]
                                                                    .currentResources[0xf]
                                                                + *(int*)((int)this + _aicOffset + 0x118))
                                                        && (_pDelay = &DAT_GameState::instance.playerDataArray[playerID]
                                                                .aiSiegeCreationInformation[0][_engineIndex]
                                                                .delay,
                                                            *_pDelay = *_pDelay + 1,
                                                            *(int*)((int)this + _aicOffset + 0x11c)
                                                                <= DAT_GameState::instance.playerDataArray[playerID]
                                                                    .aiSiegeCreationInformation[0][_engineIndex]
                                                                    .delay)) {

                                                        _y = (int)DAT_ViewportRenderState::instance
                                                                 .DAT_TileTranslationMatrix_YComponent[_location];

                                                        _tile = _location
                                                            - DAT_ViewportRenderState::instance.translationMatrix[_y]
                                                                  .addXgetTile;

                                                        if (_siegeInfoIndex < 2) {

                                                            _spawnedUnit = MACRO_CALL_MEMBER(
                                                                OpenSHC::Map::Units::UnitsState_Func::spawnUnit,
                                                                DAT_UnitsState::ptr)(playerID, playerID, _tile * 8 + 4,
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

                                                            MACRO_CALL_MEMBER(
                                                                OpenSHC::Map::Buildings::BuildingsState_Func::
                                                                    processPlacementResourceLossForBuildingType,
                                                                DAT_BuildingsState::ptr)(playerID,
                                                                (BuildingType)((int)(DAT_SkirmishDefinedData::instance
                                                                        .DAT_SiegeEngineMetaInfoArray[_siegeInfoIndex]
                                                                        .buildingType)),
                                                                0);

                                                        }

                                                        else {

                                                            MACRO_CALL_MEMBER(
                                                                OpenSHC::Map::TileMapState_Func::placeBuilding,
                                                                DAT_TileMapState::ptr)(playerID, _tile, _y,
                                                                (CommandBuildingType)((int)((uint)(ushort)(short)
                                                                        DAT_SkirmishDefinedData::instance
                                                                            .DAT_SiegeEngineMetaInfoArray
                                                                                [_siegeInfoIndex]
                                                                            .commandBuildingType)),
                                                                3, 0xf);

                                                            if (DAT_TileMapState::instance.buildingPlacementFail
                                                                == FALSE) {

                                                                _pGold
                                                                    = DAT_GameState::instance.playerDataArray[playerID]
                                                                          .currentResources
                                                                    + 0xf;

                                                                *_pGold = *_pGold - _requiredGold;

                                                                _newBuildingID
                                                                    = DAT_TileMapState::instance.DAT_PlacedBuildingID;

                                                                _newUID = DAT_BuildingsState::instance
                                                                              .buildings[DAT_TileMapState::instance
                                                                                      .DAT_PlacedBuildingID]
                                                                              .uid;

                                                                DAT_GameState::instance.playerDataArray[playerID]
                                                                    .aiSiegeCreationInformation[_siegeInfoIndex]
                                                                                               [_slotIndex]
                                                                    .unitID = 0;

                                                                DAT_GameState::instance.playerDataArray[playerID]
                                                                    .aiSiegeCreationInformation[_siegeInfoIndex]
                                                                                               [_slotIndex]
                                                                    .uid = _newUID;

                                                                DAT_GameState::instance.playerDataArray[playerID]
                                                                    .aiSiegeCreationInformation[_siegeInfoIndex]
                                                                                               [_slotIndex]
                                                                    .buildingID = _newBuildingID;
                                                            }
                                                        }

                                                        /*
                                                                                    delay = 0 */

                                                        *(undefined4*)(playerID * 0x39f4 + 0x115f48c + _slotIndex * 20
                                                            + _siegeInfoIndex * 100) = 0;

                                                        return;
                                                    }
                                                }

                                            }

                                            else {

                                            LAB_004d22d3:
                                                _requiredEngineerCount
                                                    = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::
                                                                            getRequiredEngineerCountForSiegeBuilding,
                                                        DAT_BuildingsState::ptr)(_tile);

                                                if (DAT_BuildingsState::instance.buildings[_tile].currentEmployeeCount
                                                    != _requiredEngineerCount) {

                                                    if (_requiredEngineerCount
                                                        <= DAT_GameState::instance.playerDataArray[playerID]
                                                            .engineerCountRelated) {

                                                        _engineersTribe = MACRO_CALL_MEMBER(
                                                            OpenSHC::AI::AICState_Func::
                                                                assignRequiredIdleEngineersToNewTribe,
                                                            this)(playerID, _requiredEngineerCount);

                                                        DAT_TribesState::instance.tribes[_engineersTribe].tribeType
                                                            = OpenSHC::AI::Tribes::AITT_ENGINEERS;

                                                        DAT_TribesState::instance.tribes[_engineersTribe]
                                                            .tribeBehaviorType = OpenSHC::Map::Units::
                                                            STBT_0x410_SIEGE_EQUIPMENT_CONSTRUCTION;

                                                        MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::
                                                                              giveTribeAnInstruction,
                                                            DAT_TribesState::ptr)(_engineersTribe,
                                                            OpenSHC::Map::Units::
                                                                UIT_CONSTRUCT_SIEGE_EQUIPMENTOIL_DUTYENGINEERRELATED,
                                                            _tile, DAT_BuildingsState::instance.buildings[_tile].uid,
                                                            0);

                                                        return;
                                                    }

                                                    DAT_GameState::instance.playerDataArray[playerID].isEngineerRequired
                                                        = TRUE;
                                                }
                                            }

                                        }

                                        else {

                                            if (_tile != 0)
                                                goto LAB_004d22d3;

                                            _remainingRequiredEngineers = MACRO_CALL_MEMBER(
                                                OpenSHC::Map::Units::UnitsState_Func::getRemainingRequiredEngineers,
                                                DAT_UnitsState::ptr)(_unitID);

                                            if (0 < _remainingRequiredEngineers) {

                                                if (DAT_GameState::instance.playerDataArray[playerID]
                                                        .engineerCountRelated
                                                    < _remainingRequiredEngineers) {

                                                    DAT_GameState::instance.playerDataArray[playerID].isEngineerRequired
                                                        = TRUE;

                                                }

                                                else {

                                                    _tribeID
                                                        = MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::
                                                                                assignRequiredIdleEngineersToNewTribe,
                                                            this)(playerID, _remainingRequiredEngineers);

                                                    _targetUnitID = (int)DAT_TribesState::instance.tribes[_tribeID]
                                                                        .selectionTargetUnitID;

                                                    if ((_targetUnitID != 0)
                                                        && (_area = MACRO_CALL_MEMBER(
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
                                                                0),
                                                            _area != 0)) {

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

                                    else {

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

                                else {

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

                    if (64 < _mappingOffset) {

                        return;
                    }

                } while (true);
            }
        }

        return;
    }

}
}
