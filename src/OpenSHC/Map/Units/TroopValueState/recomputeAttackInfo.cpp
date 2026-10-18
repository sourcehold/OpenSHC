#include "OpenSHC/Map.func.hpp"

#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/Buildings/BuildingTypeShort.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using Game::GameMode;
        using Map::Buildings::BuildingType;
        using Map::Buildings::BuildingTypeShort;
        using Map::Units::UnitType;
        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0051E300
        void TroopValueState::recomputeAttackInfo(int playerID, int attackedPlayerID)
        {
            int _tileDefaultHeight;
            undefined2 _pathConnectionValue;
            undefined* _pSpecialAreasBase;
            undefined* _pPathConnectionBase;
            int _buildingID_2;
            int _buildingHeight_GHL;
            int _buildingHeight_GHS;
            int _buildingHeight_else;
            BOOLEnum _teamsDifferent;
            uint _height1;
            int _neighbourTile;
            uint _neighbourTotalHeight;
            uint _heightTown;
            int _buildingID_3;
            short* _pSpecialArea;
            dword _toArea;
            int (*_pDirectionRow)[8];
            int _specialArea;
            int _candidateTile;
            uint _totalHeight;
            int _tile;
            int _offset;
            int _directionStep;
            char* _pTranslated;
            int* _pValueCount;
            int _direction;
            BOOLEnum _isSolitary;
            uint _defaultHeight;
            int _directionMin1;
            BuildingTypeShort _buildingType;
            undefined* _pSpecialAreas;
            undefined* _pConnectionLayer;
            ushort _areaTile1;
            ushort _area2;
            int _y;
            ushort _unitID;
            uint _logic;
            ushort _buildingID;
            int _someY;
            int _someLimit;
            ushort _area;
            int _startCon;
            _offset = playerID * 96188;
            _isSolitary = DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SOLITARY;
            DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].hack1 = 0;
            DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].scale1 = 0;
            DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].hack2 = 0;
            DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].scale2 = 0;
            DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].stone1 = 0;
            DAT_TroopValueState::instance.attackInfo.high1 = 0;
            DAT_TroopValueState::instance.attackInfo.arch1 = 0;
            DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].gate1 = 0;
            DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].wide1 = 0;
            DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].town1 = 0;
            DAT_TroopValueState::instance.attackInfo.people1 = 0;
            DAT_TroopValueState::instance.attackInfo.lord1 = 0;
            DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].some1000ArrayIndex_2 = 0;
            DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].wide2 = 0;
            DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].town2 = 0;
            DAT_TroopValueState::instance.attackInfo.people2 = 0;
            DAT_TroopValueState::instance.attackInfo.lord3 = 0;
            DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].moat1 = 0;
            DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].moat2 = 0;
            DAT_TroopValueState::instance.attackInfo.high2 = 0;
            DAT_TroopValueState::instance.attackInfo.arch2 = 0;
            DAT_TroopValueState::instance.attackInfo.scaleZone = 1000;
            DAT_TroopValueState::instance.attackInfo.someArea = 0;
            DAT_TroopValueState::instance.attackInfo.field127541_0x2c85c = 0;
            if (!_isSolitary) {
                DAT_TroopValueState::instance.attackInfo.someDistanceLimit = 4;
            } else {
                DAT_TroopValueState::instance.attackInfo.someDistanceLimit
                    = ((3000 <= DAT_TroopValueState::instance.attackInfo.zoneSize) - 1 & 6) + 4;
            }
            MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                sizeof(DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].hackValuesArray), '\0',
                (void*)((int)(DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].hackValuesArray)));
            // FIXME:: this clears 16000 bytes where the member is 16016, so sizeof would change the clear;
            // the constant stays until the header is corrected.
            MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(16000, '\0',
                (void*)((int)(DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].scaleValuesArray)));
            // FIXME:: this clears 16000 bytes where the member is 16016, so sizeof would change the clear;
            // the constant stays until the header is corrected.
            MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(16000, '\0',
                (void*)((int)(DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].townValuesArray)));
            // FIXME:: this clears 16000 bytes where the member is 4992, so sizeof would change the clear;
            // the constant stays until the header is corrected.
            MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                16000, '\0', (void*)((int)(DAT_TroopValueState::instance.attackInfo.peopleValuesArray)));
            // FIXME:: this clears 16000 bytes where the member is 14672, so sizeof would change the clear;
            // the constant stays until the header is corrected.
            MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                16000, '\0', (void*)((int)(DAT_TroopValueState::instance.attackInfo.lordValuesArray)));
            // FIXME:: this clears 16000 bytes where the member is 16016, so sizeof would change the clear;
            // the constant stays until the header is corrected.
            MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(16000, '\0',
                (void*)((int)(DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].gateValuesArray)));
            // FIXME:: this clears 16000 bytes where the member is 10992, so sizeof would change the clear;
            // the constant stays until the header is corrected.
            MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(16000, '\0',
                (void*)((int)(DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].wideValuesArray)));
            // FIXME:: this clears 16000 bytes where the member is 8992, so sizeof would change the clear;
            // the constant stays until the header is corrected.
            MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(16000, '\0',
                (void*)((int)(DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].moatValuesArray)));
            MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                sizeof(DAT_TroopValueState::instance.attackInfo.high2ValuesArray), '\0',
                (void*)((int)(DAT_TroopValueState::instance.attackInfo.high2ValuesArray)));
            MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                sizeof(DAT_TroopValueState::instance.attackInfo.arch2ValuesArray), '\0',
                (void*)((int)(DAT_TroopValueState::instance.attackInfo.arch2ValuesArray)));
            _startCon = DAT_TroopValueState::instance.attackInfo.startCon;
            _tile = 0;
            do {
                _unitID = DAT_TileMapState::instance.UnitLayer[_tile];
                _logic = DAT_TileMapState::instance.LogicLayer[_tile];
                if (_unitID || (_logic & 0x50000700)) {
                    _buildingID = DAT_TileMapState::instance.BuildingLayer[_tile];
                    if (_buildingID) {
                        _buildingID_2 = (int)(short)_buildingID;
                        _buildingType = DAT_BuildingsState::instance.buildings[_buildingID_2].buildingType;
                        if (_buildingType == Map::Buildings::BT_GATEHOUSELARGE) {
                            _buildingHeight_GHL
                                = MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::getBuildingHeightForBuildingID,
                                    DAT_BuildingsState::ptr)(_buildingID_2);
                            _defaultHeight
                                = _buildingHeight_GHL + (uint)DAT_TileMapState::instance.DefaultHeightLayer[_tile];
                        } else if (_buildingType == Map::Buildings::BT_GATEHOUSESMALL) {
                            _buildingHeight_GHS
                                = MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::getBuildingHeightForBuildingID,
                                    DAT_BuildingsState::ptr)(_buildingID_2);
                            _defaultHeight
                                = _buildingHeight_GHS + (uint)DAT_TileMapState::instance.DefaultHeightLayer[_tile];
                        } else {
                            _buildingHeight_else
                                = MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::getBuildingHeightForBuildingID,
                                    DAT_BuildingsState::ptr)(_buildingID_2);
                            _defaultHeight = _buildingHeight_else + (uint)DAT_TileMapState::instance.HeightLayer[_tile];
                        }
                    } else {
                        _defaultHeight = (uint)DAT_TileMapState::instance.HeightLayer[_tile];
                    }
                    if (_unitID) {
                        _teamsDifferent = MACRO_CALL_MEMBER(Game::GameStateStructures_Func::getTeamsDifferent,
                            DAT_GameState::ptr)((int)DAT_UnitsState::instance.units[(short)_unitID].owner, playerID);
                        _pSpecialAreas = (undefined*)(DAT_TileMapState::instance.ptr_SpecialAreasArray);
                        _pConnectionLayer = (undefined*)(DAT_TileMapState::instance.ptr_PathConnectionLayer);
                        if (_teamsDifferent) {
                            /*
                              path cost is zero
                             */
                            if (DAT_TileMapState::instance.SEC_PathfindingCostTileMap1105[attackedPlayerID][_tile]
                                == '\0') {
                                continue;
                            }
                            if ((short)DAT_TileMapState::instance.PathConnectionLayer[_tile] == _startCon
                                && DAT_UnitsState::instance.units[(short)_unitID].isStalked == 0
                                && DAT_UnitsState::instance.units[(short)_unitID].isSelectable_OR_matchTime != 0) {
                                DAT_TileMapState::instance.DAT_SomeY
                                    = (int)DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[_tile];
                                DAT_TroopValueState::instance.attackInfo.people1
                                    = DAT_TroopValueState::instance.attackInfo.people1 + 1;
                                _pTranslated
                                    = (char*)(((char*)DAT_TileMapState::instance.ptr_MovementDirectionTranslationMatrix)
                                        + DAT_TileMapState::instance.DAT_SomeY * 0x20);
                                _areaTile1 = *(ushort*)(((char*)DAT_TileMapState::instance.ptr_PathConnectionLayer)
                                    + _tile * 2 + -2);
                                DAT_TileMapState::instance.DAT_SomeTile = _tile;
                                *(undefined2*)(((char*)DAT_TileMapState::instance.ptr_SpecialAreasArray) + 4)
                                    = *(undefined2*)(((char*)DAT_TileMapState::instance.ptr_PathConnectionLayer)
                                        + _tile * 2 + 2);
                                *(ushort*)(_pSpecialAreas + 0xc) = _areaTile1;
                                _area2 = *(ushort*)(_pConnectionLayer + *(int*)(_pTranslated + 0x10) * 2 + _tile * 2);
                                *(undefined2*)_pSpecialAreas
                                    = *(undefined2*)(_pConnectionLayer + *(int*)_pTranslated * 2 + _tile * 2);
                                *(ushort*)(_pSpecialAreas + 8) = _area2;
                                _directionStep = 0;
                                do {
                                    if (DAT_TileMapState::instance.specialAreasArray[_directionStep] == _startCon) {
                                        if ((999 < DAT_TroopValueState::instance.attackInfo.people2)
                                            || (_teamsDifferent = MACRO_CALL_MEMBER(
                                                    Map::Units::TroopValueState_Func::getTileInTargetedBuildingTiles,
                                                    this)(_tile),
                                                _teamsDifferent)) {
                                            break;
                                        }
                                        _height1 = MACRO_CALL_MEMBER(
                                            Map::TileMapState_Func::getTotalHeightAtTile, DAT_TileMapState::ptr)(
                                            DAT_TileMapState::instance
                                                .directionTranslationMatrix[DAT_TileMapState::instance.DAT_SomeY]
                                                                           [_directionStep]
                                            + _tile);
                                        _y = DAT_TileMapState::instance.DAT_SomeY;
                                        if ((int)_defaultHeight <= (int)(_height1 + 0x10)
                                            && (int)(_height1 - 0x10) <= (int)_defaultHeight) {
                                            DAT_TroopValueState::instance.attackInfo
                                                .peopleValuesArray[DAT_TroopValueState::instance.attackInfo.people2]
                                                .tile = _tile;
                                            DAT_TroopValueState::instance.attackInfo
                                                .peopleValuesArray[DAT_TroopValueState::instance.attackInfo.people2]
                                                .tile2 = DAT_TileMapState::instance
                                                             .directionTranslationMatrix[_y][_directionStep]
                                                + _tile;
                                            DAT_TroopValueState::instance.attackInfo.people2
                                                = DAT_TroopValueState::instance.attackInfo.people2 + 1;
                                        }
                                    }
                                    _directionStep = _directionStep + 2;
                                } while (_directionStep < 8);
                            }
                            if (DAT_UnitsState::instance.units[(short)_unitID].unitType == Map::Units::UT_LORD) {
                                DAT_TroopValueState::instance.attackInfo.someArea
                                    = (int)(short)DAT_TileMapState::instance.PathConnectionLayer[_tile];
                                DAT_TroopValueState::instance.attackInfo.lord1
                                    = DAT_TroopValueState::instance.attackInfo.lord1 + 1;
                                if (DAT_TroopValueState::instance.attackInfo.someArea
                                    == DAT_TroopValueState::instance.attackInfo.startCon) {
                                    DAT_TileMapState::instance.DAT_SomeY
                                        = (int)
                                              DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[_tile];
                                    _candidateTile = 0;
                                    _pDirectionRow = DAT_TileMapState::instance.directionTranslationMatrix
                                        + DAT_TileMapState::instance.DAT_SomeY;
                                    _directionStep = DAT_TroopValueState::instance.attackInfo.lord3;
                                    do {
                                        _neighbourTile = (*_pDirectionRow)[0] + _tile;
                                        if (DAT_TileMapState::instance.PathConnectionLayer[_neighbourTile] != 0) {
                                            if (999 < _directionStep) {
                                                break;
                                            }
                                            DAT_TroopValueState::instance.attackInfo.lordValuesArray[_directionStep]
                                                .tile = _tile;
                                            DAT_TroopValueState::instance.attackInfo
                                                .lordValuesArray[DAT_TroopValueState::instance.attackInfo.lord3]
                                                .tile2 = _neighbourTile;
                                            _directionStep = DAT_TroopValueState::instance.attackInfo.lord3 + 1;
                                            DAT_TroopValueState::instance.attackInfo.lord3 = _directionStep;
                                        }
                                        _candidateTile = _candidateTile + 1;
                                        _pDirectionRow = (int (*)[8])(*_pDirectionRow + 1);
                                    } while (_candidateTile < 8);
                                }
                            }
                        }
                    }
                    _pPathConnectionBase = (undefined*)(DAT_TileMapState::instance.ptr_SpecialAreasArray);
                    _pSpecialAreasBase = (undefined*)(DAT_TileMapState::instance.ptr_PathConnectionLayer);
                    if ((!_buildingID)
                        || (DAT_BuildingsState::instance.buildings[(short)_buildingID].owner != attackedPlayerID)) {
                        if (!(_logic & 0x300) || (_logic & 2)) {
                            if ((_logic & 0x40000000)
                                && DAT_TileMapState::instance.SEC_PathfindingCostTileMap1105[attackedPlayerID][_tile]
                                    != '\0') {
                                _tileDefaultHeight = DAT_TileMapState::instance.DefaultHeightLayer[_tile];
                                _pValueCount = (int*)((
                                    undefined*)((int*)((int)DAT_TroopValueState::instance.attackInfo.moatValuesArray
                                    + _offset + -0xc)));
                                *_pValueCount = (int)((undefined*)(*_pValueCount + 1));
                                _pPathConnectionBase = (undefined*)(DAT_TileMapState::instance.ptr_SpecialAreasArray);
                                _pSpecialAreasBase = (undefined*)(DAT_TileMapState::instance.ptr_PathConnectionLayer);
                                DAT_TileMapState::instance.DAT_SomeY
                                    = (int)DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[_tile];
                                _pValueCount
                                    = (int*)(((char*)DAT_TileMapState::instance.ptr_MovementDirectionTranslationMatrix)
                                        + DAT_TileMapState::instance.DAT_SomeY * 0x20);
                                _pathConnectionValue
                                    = *(undefined2*)(((char*)DAT_TileMapState::instance.ptr_PathConnectionLayer)
                                        + _tile * 2 + -2);
                                DAT_TileMapState::instance.DAT_SomeTile = _tile;
                                *(undefined2*)(((char*)DAT_TileMapState::instance.ptr_SpecialAreasArray) + 4)
                                    = *(undefined2*)(((char*)DAT_TileMapState::instance.ptr_PathConnectionLayer)
                                        + _tile * 2 + 2);
                                *(undefined2*)(_pPathConnectionBase + 0xc) = _pathConnectionValue;
                                _pathConnectionValue
                                    = *(undefined2*)(_pSpecialAreasBase + _pValueCount[4] * 2 + _tile * 2);
                                *(undefined2*)_pPathConnectionBase
                                    = *(undefined2*)(_pSpecialAreasBase + *_pValueCount * 2 + _tile * 2);
                                *(undefined2*)(_pPathConnectionBase + 8) = _pathConnectionValue;
                                _directionStep = 0;
                                do {
                                    _candidateTile = MACRO_CALL_MEMBER(
                                        Map::Navigation::PathFindingState_Func::
                                            calculateCanPlayerUnitsNavigateToAreaFromArea,
                                        DAT_PathFindingState::ptr)(playerID,
                                        (dword)((int)(DAT_TroopValueState::instance.attackInfo.startCon)),
                                        (dword)((int)(DAT_TileMapState::instance.specialAreasArray[_directionStep])),
                                        0);
                                    if (_candidateTile) {
                                        if (999 < DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1]
                                                    .moat2
                                            || (_teamsDifferent = MACRO_CALL_MEMBER(
                                                    Map::Units::TroopValueState_Func::getTileInTargetedBuildingTiles,
                                                    this)(_tile),
                                                _teamsDifferent)) {
                                            break;
                                        }
                                        _candidateTile
                                            = DAT_TileMapState::instance
                                                  .directionTranslationMatrix[DAT_TileMapState::instance.DAT_SomeY]
                                                                             [_directionStep]
                                            + _tile;
                                        if (!(DAT_TileMapState::instance.LogicLayer[_candidateTile] & 0x10000100U)
                                            && (_totalHeight
                                                = MACRO_CALL_MEMBER(Map::TileMapState_Func::getTotalHeightAtTile,
                                                    DAT_TileMapState::ptr)(_candidateTile),
                                                _someY = DAT_TileMapState::instance.DAT_SomeY,
                                                _tileDefaultHeight <= (int)(_totalHeight + 0x10)
                                                    && ((int)(_totalHeight - 0x10) <= _tileDefaultHeight))) {
                                            DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1]
                                                .moatValuesArray[DAT_TroopValueState::instance.attackInfo
                                                        .playerInfo[playerID - 1]
                                                        .moat2]
                                                .tile = _tile;
                                            DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1]
                                                .moatValuesArray[DAT_TroopValueState::instance.attackInfo
                                                        .playerInfo[playerID - 1]
                                                        .moat2]
                                                .tile2 = DAT_TileMapState::instance
                                                             .directionTranslationMatrix[_someY][_directionStep]
                                                + _tile;
                                            DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].moat2
                                                = DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1]
                                                      .moat2
                                                + 1;
                                            if (DAT_TileMapState::instance.AIZoneLayer[_tile] != 0) {
                                                _directionStep
                                                    = DAT_ViewportRenderState::instance.translationMatrix[_someY]
                                                          .addXgetTile;
                                                _someLimit = 1;
                                                // Duplicated from the gate scan; _someLimit is 1 here rather than
                                                // someDistanceLimit.
                                                DAT_TileMapState::instance.DAT_SomeX = _tile - _directionStep;
                                                MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::
                                                                      recomputeALGPathFindingTileMapUnk,
                                                    DAT_PathFindingState::ptr)(_someLimit,
                                                    (uint)(DAT_TileMapState::instance.DAT_SomeX), (uint)(_someY), 1);
                                            }
                                            break;
                                        }
                                    }
                                    _directionStep = _directionStep + 2;
                                } while (_directionStep < 8);
                            }
                        } else if (DAT_TileMapState::instance.SEC_PathfindingCostTileMap1105[attackedPlayerID][_tile]
                                != '\0'
                            && (DAT_TileMapState::instance.WallOwnerLayer[_tile] & 7) + 1 == attackedPlayerID
                            && (_totalHeight = (uint)DAT_TileMapState::instance.DefaultHeightLayer[_tile],
                                0x14 < (int)(DAT_TileMapState::instance.HeightLayer[_tile] - _totalHeight))
                            && !_buildingID) {
                            DAT_TileMapState::instance.DAT_SomeY
                                = (int)DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[_tile];
                            _pValueCount
                                = (int*)(((char*)DAT_TileMapState::instance.ptr_MovementDirectionTranslationMatrix)
                                    + DAT_TileMapState::instance.DAT_SomeY * 0x20);
                            _pathConnectionValue
                                = *(undefined2*)(((char*)DAT_TileMapState::instance.ptr_PathConnectionLayer) + _tile * 2
                                    + -2);
                            DAT_TileMapState::instance.DAT_SomeTile = _tile;
                            *(undefined2*)(((char*)DAT_TileMapState::instance.ptr_SpecialAreasArray) + 4)
                                = *(undefined2*)(((char*)DAT_TileMapState::instance.ptr_PathConnectionLayer) + _tile * 2
                                    + 2);
                            *(undefined2*)(_pPathConnectionBase + 0xc) = _pathConnectionValue;
                            _pathConnectionValue = *(undefined2*)(_pSpecialAreasBase + _pValueCount[4] * 2 + _tile * 2);
                            *(undefined2*)_pPathConnectionBase = (undefined2)((
                                undefined*)(*(undefined2*)(_pSpecialAreasBase + *_pValueCount * 2 + _tile * 2)));
                            *(undefined2*)(_pPathConnectionBase + 8) = (undefined2)((undefined*)(_pathConnectionValue));
                            _pPathConnectionBase = (undefined*)(DAT_TileMapState::instance.ptr_SpecialAreasArray);
                            _pSpecialAreasBase = (undefined*)(DAT_TileMapState::instance.ptr_PathConnectionLayer);
                            _candidateTile = DAT_TileMapState::instance.DAT_SomeTile;
                            _pValueCount
                                = (int*)(((char*)DAT_TileMapState::instance.ptr_MovementDirectionTranslationMatrix)
                                    + DAT_TileMapState::instance.DAT_SomeY * 0x20);
                            _directionStep = *_pValueCount * 2 + DAT_TileMapState::instance.DAT_SomeTile * 2;
                            _pathConnectionValue
                                = *(undefined2*)(((char*)DAT_TileMapState::instance.ptr_PathConnectionLayer)
                                    + _directionStep + -2);
                            *(undefined2*)(((char*)DAT_TileMapState::instance.ptr_SpecialAreasArray) + 2)
                                = *(undefined2*)(((char*)DAT_TileMapState::instance.ptr_PathConnectionLayer)
                                    + _directionStep + 2);
                            *(undefined2*)(_pPathConnectionBase + 0xe) = _pathConnectionValue;
                            _directionStep = _pValueCount[4] * 2 + _candidateTile * 2;
                            _pathConnectionValue = *(undefined2*)(_pSpecialAreasBase + _directionStep + -2);
                            *(undefined2*)(_pPathConnectionBase + 6)
                                = *(undefined2*)(_pSpecialAreasBase + _directionStep + 2);
                            *(undefined2*)(_pPathConnectionBase + 10) = _pathConnectionValue;
                            for (_direction = 0; _direction < 8; _direction += 2) {
                                _toArea = MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::
                                                                calculateCanPlayerUnitsNavigateToAreaFromArea,
                                    DAT_PathFindingState::ptr)(playerID,
                                    (dword)((int)(DAT_TroopValueState::instance.attackInfo.startCon)),
                                    (dword)((int)(DAT_TileMapState::instance.specialAreasArray[_direction])), 0);
                                if (_toArea) {
                                    _directionMin1 = _direction + -1;
                                    if (_directionMin1 < 0) {
                                        _directionMin1 = 7;
                                    }
                                    _directionStep = MACRO_CALL_MEMBER(
                                        Map::Navigation::PathFindingState_Func::
                                            calculateCanPlayerUnitsNavigateToAreaFromArea,
                                        DAT_PathFindingState::ptr)(playerID,
                                        (dword)((int)(DAT_TroopValueState::instance.attackInfo.startCon)),
                                        (dword)((
                                            int)((int)DAT_TileMapState::instance.specialAreasArray[_direction + 1])),
                                        0);
                                    if (_directionStep
                                        && (_directionStep
                                            = MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::
                                                                    calculateCanPlayerUnitsNavigateToAreaFromArea,
                                                DAT_PathFindingState::ptr)(playerID,
                                                (dword)((int)(DAT_TroopValueState::instance.attackInfo.startCon)),
                                                (dword)((
                                                    int)(DAT_TileMapState::instance.specialAreasArray[_directionMin1])),
                                                0),
                                            _directionStep != 0)
                                        && !(DAT_TileMapState::instance.AIInfoLayer[_tile] & 0x20)) {
                                        if (999 < DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1]
                                                    .wide2
                                            || (_teamsDifferent = MACRO_CALL_MEMBER(
                                                    Map::Units::TroopValueState_Func::getTileInTargetedBuildingTiles,
                                                    this)(_tile),
                                                _teamsDifferent)) {
                                            break;
                                        }
                                        _directionStep
                                            = DAT_TileMapState::instance
                                                  .directionTranslationMatrix[DAT_TileMapState::instance.DAT_SomeY]
                                                                             [_direction]
                                            + _tile;
                                        if (!(DAT_TileMapState::instance.LogicLayer[_directionStep] & 0x10000100U)
                                            && (_neighbourTotalHeight
                                                = MACRO_CALL_MEMBER(Map::TileMapState_Func::getTotalHeightAtTile,
                                                    DAT_TileMapState::ptr)(_directionStep),
                                                (int)_totalHeight <= (int)(_neighbourTotalHeight + 0x10)
                                                    && ((int)(_neighbourTotalHeight - 0x10) <= (int)_totalHeight))) {
                                            DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1]
                                                .wideValuesArray[DAT_TroopValueState::instance.attackInfo
                                                        .playerInfo[playerID - 1]
                                                        .wide2]
                                                .tile = _tile;
                                            _directionStep = DAT_TileMapState::instance.DAT_SomeY;
                                            DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1]
                                                .wideValuesArray[DAT_TroopValueState::instance.attackInfo
                                                        .playerInfo[playerID - 1]
                                                        .wide2]
                                                .tile2
                                                = DAT_TileMapState::instance
                                                      .directionTranslationMatrix[DAT_TileMapState::instance.DAT_SomeY]
                                                                                 [_direction]
                                                + _tile;
                                            DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].wide2
                                                = DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1]
                                                      .wide2
                                                + 1;
                                            DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].wide1
                                                = DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1]
                                                      .wide1
                                                + 1;
                                            DAT_TileMapState::instance.DAT_SomeX = _tile
                                                - DAT_ViewportRenderState::instance.translationMatrix[_directionStep]
                                                      .addXgetTile;
                                            MACRO_CALL_MEMBER(
                                                Map::Navigation::PathFindingState_Func::updateAIZoneWithFloodFill0x20,
                                                DAT_PathFindingState::ptr)(4,
                                                (uint)(DAT_TileMapState::instance.DAT_SomeX), (uint)(_directionStep));
                                            continue;
                                        }
                                    }
                                }
                            }
                            DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].stone1
                                = DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].stone1 + 1;
                            _directionStep = 0;
                            do {
                                _candidateTile = MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::
                                                                       calculateCanPlayerUnitsNavigateToAreaFromArea,
                                    DAT_PathFindingState::ptr)(playerID,
                                    (dword)((int)(DAT_TroopValueState::instance.attackInfo.startCon)),
                                    (dword)((int)(DAT_TileMapState::instance.specialAreasArray[_directionStep])), 0);
                                if (_candidateTile) {
                                    if (999 < DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].hack2
                                        || (_teamsDifferent = MACRO_CALL_MEMBER(
                                                Map::Units::TroopValueState_Func::getTileInTargetedBuildingTiles, this)(
                                                _tile),
                                            _teamsDifferent)) {
                                        break;
                                    }
                                    _candidateTile
                                        = DAT_TileMapState::instance
                                              .directionTranslationMatrix[DAT_TileMapState::instance.DAT_SomeY]
                                                                         [_directionStep]
                                        + _tile;
                                    if (!(DAT_TileMapState::instance.LogicLayer[_candidateTile] & 0x10000100U)
                                        && (_neighbourTotalHeight
                                            = MACRO_CALL_MEMBER(Map::TileMapState_Func::getTotalHeightAtTile,
                                                DAT_TileMapState::ptr)(_candidateTile),
                                            _candidateTile = DAT_TileMapState::instance.DAT_SomeY,
                                            (int)_totalHeight <= (int)(_neighbourTotalHeight + 0x10)
                                                && ((int)(_neighbourTotalHeight - 0x10) <= (int)_totalHeight))) {
                                        DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1]
                                            .hackValuesArray[DAT_TroopValueState::instance.attackInfo
                                                    .playerInfo[playerID - 1]
                                                    .hack2]
                                            .tile = _tile;
                                        DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1]
                                            .hackValuesArray[DAT_TroopValueState::instance.attackInfo
                                                    .playerInfo[playerID - 1]
                                                    .hack2]
                                            .tile2 = DAT_TileMapState::instance
                                                         .directionTranslationMatrix[_candidateTile][_directionStep]
                                            + _tile;
                                        _directionStep
                                            = DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].hack2;
                                        DAT_TileMapState::instance.AIZoneLayer[DAT_TroopValueState::instance.attackInfo
                                                .playerInfo[playerID - 1]
                                                .hackValuesArray[_directionStep]
                                                .tile2] = 10;
                                        _tileDefaultHeight = DAT_TileMapState::instance.AIZoneLayer[_tile];
                                        DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].hack2
                                            = _directionStep + 1;
                                        if (_tileDefaultHeight) {
                                            DAT_TileMapState::instance.DAT_SomeX = _tile
                                                - DAT_ViewportRenderState::instance
                                                      .translationMatrix[DAT_TileMapState::instance.DAT_SomeY]
                                                      .addXgetTile;
                                            MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::
                                                                  recomputeALGPathFindingTileMapUnk,
                                                DAT_PathFindingState::ptr)(
                                                DAT_TroopValueState::instance.attackInfo.someDistanceLimit,
                                                (uint)(DAT_TileMapState::instance.DAT_SomeX),
                                                (uint)(DAT_TileMapState::instance.DAT_SomeY), 1);
                                        }
                                        break;
                                    }
                                }
                                _directionStep = _directionStep + 2;
                            } while (_directionStep < 8);
                            DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].hack1
                                = DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].hack1 + 1;
                            if (!(_logic & 0x400000)) {
                                _directionStep = (int)(char)DAT_TileMapState::instance.AIZoneLayer[_tile];
                                DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].scale1
                                    = DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].scale1 + 1;
                                if ((_directionStep)
                                    && (_directionStep < DAT_TroopValueState::instance.attackInfo.scaleZone)) {
                                    DAT_TroopValueState::instance.attackInfo.scaleZone = _directionStep;
                                }
                                _directionStep = 0;
                                do {
                                    _candidateTile = MACRO_CALL_MEMBER(
                                        Map::Navigation::PathFindingState_Func::
                                            calculateCanPlayerUnitsNavigateToAreaFromArea,
                                        DAT_PathFindingState::ptr)(playerID,
                                        (dword)((int)(DAT_TroopValueState::instance.attackInfo.startCon)),
                                        (dword)((int)(DAT_TileMapState::instance.specialAreasArray[_directionStep])),
                                        0);
                                    if (_candidateTile) {
                                        if (999 < DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1]
                                                    .scale2
                                            || (_teamsDifferent = MACRO_CALL_MEMBER(
                                                    Map::Units::TroopValueState_Func::getTileInTargetedBuildingTiles,
                                                    this)(_tile),
                                                _teamsDifferent)) {
                                            break;
                                        }
                                        _candidateTile
                                            = DAT_TileMapState::instance
                                                  .directionTranslationMatrix[DAT_TileMapState::instance.DAT_SomeY]
                                                                             [_directionStep]
                                            + _tile;
                                        if (!(DAT_TileMapState::instance.LogicLayer[_candidateTile] & 0x10000100U)
                                            && (_neighbourTotalHeight
                                                = MACRO_CALL_MEMBER(Map::TileMapState_Func::getTotalHeightAtTile,
                                                    DAT_TileMapState::ptr)(_candidateTile),
                                                (int)_totalHeight <= (int)(_neighbourTotalHeight + 0x10)
                                                    && ((int)(_neighbourTotalHeight - 0x10) <= (int)_totalHeight))) {
                                            DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1]
                                                .scaleValuesArray[DAT_TroopValueState::instance.attackInfo
                                                        .playerInfo[playerID - 1]
                                                        .scale2]
                                                .tile = _tile;
                                            _someY = DAT_TileMapState::instance.DAT_SomeY;
                                            DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1]
                                                .scaleValuesArray[DAT_TroopValueState::instance.attackInfo
                                                        .playerInfo[playerID - 1]
                                                        .scale2]
                                                .tile2
                                                = DAT_TileMapState::instance
                                                      .directionTranslationMatrix[DAT_TileMapState::instance.DAT_SomeY]
                                                                                 [_directionStep]
                                                + _tile;
                                            DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].scale2
                                                = DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1]
                                                      .scale2
                                                + 1;
                                            // Duplicated from the gate scan: the original shared one tail block between
                                            // the two scans.
                                            if (DAT_TileMapState::instance.AIZoneLayer[_tile] != 0) {
                                                _directionStep
                                                    = DAT_ViewportRenderState::instance.translationMatrix[_someY]
                                                          .addXgetTile;
                                                _someLimit = DAT_TroopValueState::instance.attackInfo.someDistanceLimit;
                                                DAT_TileMapState::instance.DAT_SomeX = _tile - _directionStep;
                                                MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::
                                                                      recomputeALGPathFindingTileMapUnk,
                                                    DAT_PathFindingState::ptr)(_someLimit,
                                                    (uint)(DAT_TileMapState::instance.DAT_SomeX), (uint)(_someY), 1);
                                            }
                                            break;
                                        }
                                    }
                                    _directionStep = _directionStep + 2;
                                } while (_directionStep < 8);
                            }
                        }
                    } else {
                        int _buildingTypeInt
                            = (int)(short)DAT_BuildingsState::instance.buildings[(short)_buildingID].buildingType;
                        _totalHeight = (uint)DAT_TileMapState::instance.DefaultHeightLayer[_tile];
                        if (DAT_BuildingDefinedData::instance.IsGateOrTowerArray[_buildingTypeInt]) {
                            if (DAT_TileMapState::instance.SEC_PathfindingCostTileMap1105[attackedPlayerID][_tile]
                                != '\0') {
                                _pValueCount = (int*)((
                                    undefined*)((int*)((int)DAT_TroopValueState::instance.attackInfo.gateValuesArray
                                    + _offset + -0xc)));
                                *_pValueCount = (int)((undefined*)(*_pValueCount + 1));
                                _pPathConnectionBase = (undefined*)(DAT_TileMapState::instance.ptr_SpecialAreasArray);
                                _pSpecialAreasBase = (undefined*)(DAT_TileMapState::instance.ptr_PathConnectionLayer);
                                DAT_TileMapState::instance.DAT_SomeY
                                    = (int)DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[_tile];
                                DAT_TileMapState::instance.DAT_SomeX = _tile
                                    - DAT_ViewportRenderState::instance
                                          .translationMatrix[DAT_TileMapState::instance.DAT_SomeY]
                                          .addXgetTile;
                                _pValueCount
                                    = (int*)(((char*)DAT_TileMapState::instance.ptr_MovementDirectionTranslationMatrix)
                                        + DAT_TileMapState::instance.DAT_SomeY * 0x20);
                                _pathConnectionValue
                                    = *(undefined2*)(((char*)DAT_TileMapState::instance.ptr_PathConnectionLayer)
                                        + _tile * 2 + -2);
                                DAT_TileMapState::instance.DAT_SomeTile = _tile;
                                *(undefined2*)(((char*)DAT_TileMapState::instance.ptr_SpecialAreasArray) + 4)
                                    = *(undefined2*)(((char*)DAT_TileMapState::instance.ptr_PathConnectionLayer)
                                        + _tile * 2 + 2);
                                *(undefined2*)(_pPathConnectionBase + 0xc) = _pathConnectionValue;
                                _pathConnectionValue
                                    = *(undefined2*)(_pSpecialAreasBase + _pValueCount[4] * 2 + _tile * 2);
                                *(undefined2*)_pPathConnectionBase
                                    = *(undefined2*)(_pSpecialAreasBase + *_pValueCount * 2 + _tile * 2);
                                *(undefined2*)(_pPathConnectionBase + 8) = _pathConnectionValue;
                                _directionStep = 0;
                                // The decompiler encoded this scan as a label plus a fragment after the tile
                                // loop: its "break" was the back edge and falling off the end left the scan.
                                for (_directionStep = 0; _directionStep < 8; _directionStep = _directionStep + 2) {
                                    if (DAT_TileMapState::instance.specialAreasArray[_directionStep]
                                        != DAT_TroopValueState::instance.attackInfo.startCon) {
                                        continue;
                                    }
                                    if (DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1]
                                                .some1000ArrayIndex_2
                                            < 1000
                                        && (_teamsDifferent = MACRO_CALL_MEMBER(
                                                Map::Units::TroopValueState_Func::getTileInTargetedBuildingTiles, this)(
                                                _tile),
                                            !_teamsDifferent)) {
                                        _candidateTile
                                            = DAT_TileMapState::instance
                                                  .directionTranslationMatrix[DAT_TileMapState::instance.DAT_SomeY]
                                                                             [_directionStep]
                                            + _tile;
                                        if ((DAT_TileMapState::instance.LogicLayer[_candidateTile] & 0x10000100U)
                                            || (_neighbourTotalHeight
                                                = MACRO_CALL_MEMBER(Map::TileMapState_Func::getTotalHeightAtTile,
                                                    DAT_TileMapState::ptr)(_candidateTile),
                                                (int)(_neighbourTotalHeight + 0x10) < (int)_totalHeight
                                                    || ((int)_totalHeight < (int)(_neighbourTotalHeight - 0x10)))) {
                                            continue;
                                        }
                                        DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1]
                                            .gateValuesArray[DAT_TroopValueState::instance.attackInfo
                                                    .playerInfo[playerID - 1]
                                                    .some1000ArrayIndex_2]
                                            .tile = _tile;
                                        _someY = DAT_TileMapState::instance.DAT_SomeY;
                                        DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1]
                                            .gateValuesArray[DAT_TroopValueState::instance.attackInfo
                                                    .playerInfo[playerID - 1]
                                                    .some1000ArrayIndex_2]
                                            .tile2
                                            = DAT_TileMapState::instance
                                                  .directionTranslationMatrix[DAT_TileMapState::instance.DAT_SomeY]
                                                                             [_directionStep]
                                            + _tile;
                                        DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1]
                                            .some1000ArrayIndex_2
                                            = DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1]
                                                  .some1000ArrayIndex_2
                                            + 1;
                                        if (DAT_TileMapState::instance.AIZoneLayer[_tile] != 0) {
                                            _directionStep = DAT_ViewportRenderState::instance.translationMatrix[_someY]
                                                                 .addXgetTile;
                                            _someLimit = DAT_TroopValueState::instance.attackInfo.someDistanceLimit;
                                            DAT_TileMapState::instance.DAT_SomeX = _tile - _directionStep;
                                            MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::
                                                                  recomputeALGPathFindingTileMapUnk,
                                                DAT_PathFindingState::ptr)(_someLimit,
                                                (uint)(DAT_TileMapState::instance.DAT_SomeX), (uint)(_someY), 1);
                                        }
                                    }
                                    break;
                                }
                            }
                        } else {
                            if (DAT_BuildingDefinedData::instance.BuildingTypeHasHealth[_buildingTypeInt] != 0) {
                                if (!(DAT_TileMapState::instance.LogicLayer[_tile] & 0xf000000U)) {
                                    DAT_TileMapState::instance.DAT_SomeY
                                        = (int)
                                              DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[_tile];
                                    _pValueCount = (int*)((
                                        undefined*)((int*)((int)DAT_TroopValueState::instance.attackInfo.townValuesArray
                                        + _offset + -0xc)));
                                    *_pValueCount = (int)((undefined*)(*_pValueCount + 1));
                                    _pPathConnectionBase
                                        = (undefined*)(DAT_TileMapState::instance.ptr_SpecialAreasArray);
                                    _pSpecialAreasBase
                                        = (undefined*)(DAT_TileMapState::instance.ptr_PathConnectionLayer);
                                    _pValueCount = (int*)(((char*)DAT_TileMapState::instance
                                                                  .ptr_MovementDirectionTranslationMatrix)
                                        + DAT_TileMapState::instance.DAT_SomeY * 0x20);
                                    _pathConnectionValue
                                        = *(undefined2*)(((char*)DAT_TileMapState::instance.ptr_PathConnectionLayer)
                                            + _tile * 2 + -2);
                                    DAT_TileMapState::instance.DAT_SomeTile = _tile;
                                    *(undefined2*)(((char*)DAT_TileMapState::instance.ptr_SpecialAreasArray) + 4)
                                        = *(undefined2*)(((char*)DAT_TileMapState::instance.ptr_PathConnectionLayer)
                                            + _tile * 2 + 2);
                                    *(undefined2*)(_pPathConnectionBase + 0xc) = _pathConnectionValue;
                                    _pathConnectionValue
                                        = *(undefined2*)(_pSpecialAreasBase + _pValueCount[4] * 2 + _tile * 2);
                                    *(undefined2*)_pPathConnectionBase
                                        = *(undefined2*)(_pSpecialAreasBase + *_pValueCount * 2 + _tile * 2);
                                    *(undefined2*)(_pPathConnectionBase + 8) = _pathConnectionValue;
                                    _directionStep = 0;
                                    do {
                                        if (DAT_TileMapState::instance.specialAreasArray[_directionStep]
                                            == DAT_TroopValueState::instance.attackInfo.startCon) {
                                            if (999 < DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1]
                                                        .town2
                                                || (_teamsDifferent
                                                    = MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::
                                                                            getTileInTargetedBuildingTiles,
                                                        this)(_tile),
                                                    _teamsDifferent)) {
                                                break;
                                            }
                                            _heightTown = MACRO_CALL_MEMBER(
                                                Map::TileMapState_Func::getTotalHeightAtTile, DAT_TileMapState::ptr)(
                                                DAT_TileMapState::instance
                                                    .directionTranslationMatrix[DAT_TileMapState::instance.DAT_SomeY]
                                                                               [_directionStep]
                                                + _tile);
                                            _candidateTile = DAT_TileMapState::instance.DAT_SomeY;
                                            if ((int)_totalHeight <= (int)(_heightTown + 0x10)
                                                && (int)(_heightTown - 0x10) <= (int)_totalHeight) {
                                                DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1]
                                                    .townValuesArray[DAT_TroopValueState::instance.attackInfo
                                                            .playerInfo[playerID - 1]
                                                            .town2]
                                                    .tile = _tile;
                                                DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1]
                                                    .townValuesArray[DAT_TroopValueState::instance.attackInfo
                                                            .playerInfo[playerID - 1]
                                                            .town2]
                                                    .tile2
                                                    = DAT_TileMapState::instance
                                                          .directionTranslationMatrix[_candidateTile][_directionStep]
                                                    + _tile;
                                                DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].town2
                                                    = DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1]
                                                          .town2
                                                    + 1;
                                                break;
                                            }
                                        }
                                        _directionStep = _directionStep + 2;
                                    } while (_directionStep < 8);
                                }
                            } else {
                                if ((_logic & 0x10000000)) {
                                    _area = DAT_TileMapState::instance.PathConnectionLayer[_tile];
                                    if (DAT_TileMapState::instance
                                            .SEC_PathfindingCostTileMap1105[attackedPlayerID][_tile]
                                        != '\0') {
                                        _buildingID_3 = (int)DAT_TileMapState::instance.BuildingLayer[_tile];
                                        _teamsDifferent = MACRO_CALL_MEMBER(
                                            Map::Units::TroopValueState_Func::attackInfoHasHigh2Building, this)(
                                            _buildingID_3);
                                        if ((!_teamsDifferent)
                                            && (_teamsDifferent = MACRO_CALL_MEMBER(
                                                    Map::Units::TroopValueState_Func::attackInfoHasArch2Building, this)(
                                                    _buildingID_3),
                                                _pPathConnectionBase
                                                = (undefined*)DAT_TileMapState::instance.ptr_SpecialAreasArray,
                                                _pSpecialAreasBase
                                                = (undefined*)DAT_TileMapState::instance.ptr_AIZoneLayer,
                                                !_teamsDifferent)) {
                                            DAT_TileMapState::instance.DAT_SomeY
                                                = (int)DAT_ViewportRenderState::instance
                                                      .tileTranslationMatrix_YComponent[_tile];
                                            _pValueCount = (int*)((char*)DAT_TileMapState::instance
                                                                      .ptr_MovementDirectionTranslationMatrix
                                                + DAT_TileMapState::instance.DAT_SomeY * 0x10);
                                            _pathConnectionValue
                                                = *(undefined2*)(((char*)DAT_TileMapState::instance.ptr_AIZoneLayer)
                                                    + _tile + -1);
                                            DAT_TileMapState::instance.DAT_SomeTile = _tile;
                                            *(undefined2*)(((char*)DAT_TileMapState::instance.ptr_SpecialAreasArray)
                                                + 2)
                                                = *(undefined2*)(((char*)DAT_TileMapState::instance.ptr_AIZoneLayer)
                                                    + _tile + 1);
                                            *(undefined2*)(_pPathConnectionBase + 6) = _pathConnectionValue;
                                            _pathConnectionValue
                                                = *(undefined2*)(_pSpecialAreasBase + _pValueCount[4] + _tile);
                                            *(undefined2*)_pPathConnectionBase
                                                = *(undefined2*)(_pSpecialAreasBase + *_pValueCount + _tile);
                                            *(undefined2*)(_pPathConnectionBase + 4) = _pathConnectionValue;
                                            _specialArea = 0;
                                            _pSpecialArea = DAT_TileMapState::instance.specialAreasArray;
                                            do {
                                                if (*_pSpecialArea != 0) {
                                                    _specialArea = (int)*_pSpecialArea;
                                                }
                                                _pSpecialArea = _pSpecialArea + 2;
                                            } while ((int)_pSpecialArea
                                                < (int)&DAT_TileMapState::instance.specialAreasArray[8]);
                                            if (0 < _specialArea) {
                                                DAT_BuildingsState::instance.buildings[_buildingID_3]
                                                    .unknownCounterTo10000_0x2b4 = (short)_specialArea;
                                                _teamsDifferent = MACRO_CALL_MEMBER(
                                                    Map::Buildings::BuildingsState_Func::hasHumanPlayerUnitsOnBuilding,
                                                    DAT_BuildingsState::ptr)(_buildingID_3);
                                                if (_teamsDifferent) {
                                                    DAT_TroopValueState::instance.attackInfo.high1
                                                        = DAT_TroopValueState::instance.attackInfo.high1 + 1;
                                                    if (DAT_TroopValueState::instance.attackInfo.high2 < 1000
                                                        && (_directionStep = MACRO_CALL_MEMBER(
                                                                Map::Navigation::PathFindingState_Func::
                                                                    calculateCanPlayerUnitsNavigateToAreaFromArea,
                                                                DAT_PathFindingState::ptr)(playerID,
                                                                (dword)((int)(DAT_TroopValueState::instance.attackInfo
                                                                        .startCon)),
                                                                (dword)((int)((short)_area)), 0),
                                                            _directionStep != 0)) {
                                                        DAT_TroopValueState::instance.attackInfo
                                                            .high2ValuesArray[DAT_TroopValueState::instance.attackInfo
                                                                    .high2]
                                                            .buildingID = _buildingID_3;
                                                        DAT_TroopValueState::instance.attackInfo
                                                            .high2ValuesArray[DAT_TroopValueState::instance.attackInfo
                                                                    .high2]
                                                            .tile2 = _tile;
                                                        DAT_TroopValueState::instance.attackInfo
                                                            .high2ValuesArray[DAT_TroopValueState::instance.attackInfo
                                                                    .high2]
                                                            .tile = _tile;
                                                        DAT_TroopValueState::instance.attackInfo.high2
                                                            = DAT_TroopValueState::instance.attackInfo.high2 + 1;
                                                    }
                                                } else {
                                                    DAT_TroopValueState::instance.attackInfo.arch1
                                                        = DAT_TroopValueState::instance.attackInfo.arch1 + 1;
                                                    if (DAT_TroopValueState::instance.attackInfo.arch2 < 1000
                                                        && (_directionStep = MACRO_CALL_MEMBER(
                                                                Map::Navigation::PathFindingState_Func::
                                                                    calculateCanPlayerUnitsNavigateToAreaFromArea,
                                                                DAT_PathFindingState::ptr)(playerID,
                                                                (dword)((int)(DAT_TroopValueState::instance.attackInfo
                                                                        .startCon)),
                                                                (dword)((int)((short)_area)), 0),
                                                            _directionStep != 0)) {
                                                        DAT_TroopValueState::instance.attackInfo
                                                            .arch2ValuesArray[DAT_TroopValueState::instance.attackInfo
                                                                    .arch2]
                                                            .buildingID = _buildingID_3;
                                                        DAT_TroopValueState::instance.attackInfo
                                                            .arch2ValuesArray[DAT_TroopValueState::instance.attackInfo
                                                                    .arch2]
                                                            .tile2 = _tile;
                                                        DAT_TroopValueState::instance.attackInfo
                                                            .arch2ValuesArray[DAT_TroopValueState::instance.attackInfo
                                                                    .arch2]
                                                            .tile = _tile;
                                                        DAT_TroopValueState::instance.attackInfo.arch2
                                                            = DAT_TroopValueState::instance.attackInfo.arch2 + 1;
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                _tile = _tile + 1;
                if (0x13a0f < _tile) {
                    return;
                }
            } while (true);
        }

    }
}
}
