#include "../../../Map.func.hpp"

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
            int bVar1;
            undefined2 uVar3;
            undefined* puVar4;
            undefined* puVar5;
            int _buildingID_2;
            int _buildingHeight_GHL;
            int _buildingHeight_GHS;
            int _buildingHeight_else;
            BOOLEnum _teamsDifferent;
            uint _height1;
            int iVar6;
            uint uVar7;
            uint _heightTown;
            int _buildingID_3;
            short* psVar8;
            dword _toArea;
            int (*paiVar9)[8];
            int sVar10;
            int iVar11;
            uint uVar12;
            int _tile;
            int _offset;
            int iVar13;
            char* _pTranslated;
            int* piVar14;
            int _direction;
            int _isSolitary;
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
            if (_isSolitary) {
                DAT_TroopValueState::instance.attackInfo.someDistanceLimit
                    = ((2999 < DAT_TroopValueState::instance.attackInfo.zoneSize) - 1 & 6) + 4;
            } else {
                DAT_TroopValueState::instance.attackInfo.someDistanceLimit = 4;
            }
            MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                16000, '\0', (void*)((int)(DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].hackValuesArray)));
            MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(16000, '\0',
                (void*)((int)(DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].scaleValuesArray)));
            MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                16000, '\0', (void*)((int)(DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].townValuesArray)));
            MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                16000, '\0', (void*)((int)(DAT_TroopValueState::instance.attackInfo.peopleValuesArray)));
            MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                16000, '\0', (void*)((int)(DAT_TroopValueState::instance.attackInfo.lordValuesArray)));
            MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                16000, '\0', (void*)((int)(DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].gateValuesArray)));
            MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                16000, '\0', (void*)((int)(DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].wideValuesArray)));
            MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                16000, '\0', (void*)((int)(DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].moatValuesArray)));
            MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                16000, '\0', (void*)((int)(DAT_TroopValueState::instance.attackInfo.high2ValuesArray)));
            MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                16000, '\0', (void*)((int)(DAT_TroopValueState::instance.attackInfo.arch2ValuesArray)));
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
                            if (DAT_TileMapState::instance.SEC_PathfindingCostTileMap1105[attackedPlayerID][_tile] == '\0')
                                goto LAB_0051f320__next_tile;
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
                                iVar13 = 0;
                                do {
                                    if (DAT_TileMapState::instance.specialAreasArray[iVar13] == _startCon) {
                                        if ((999 < DAT_TroopValueState::instance.attackInfo.people2)
                                            || (_teamsDifferent = MACRO_CALL_MEMBER(
                                                    Map::Units::TroopValueState_Func::getTileInTargetedBuildingTiles,
                                                    this)(_tile),
                                                _teamsDifferent))
                                            break;
                                        _height1 = MACRO_CALL_MEMBER(
                                            Map::TileMapState_Func::getTotalHeightAtTile, DAT_TileMapState::ptr)(
                                            DAT_TileMapState::instance
                                                .directionTranslationMatrix[DAT_TileMapState::instance.DAT_SomeY]
                                                                           [iVar13]
                                            + _tile);
                                        _y = DAT_TileMapState::instance.DAT_SomeY;
                                        if ((int)_defaultHeight <= (int)(_height1 + 0x10)
                                            && (int)(_height1 - 0x10) <= (int)_defaultHeight) {
                                            DAT_TroopValueState::instance.attackInfo
                                                .peopleValuesArray[DAT_TroopValueState::instance.attackInfo.people2]
                                                .tile = _tile;
                                            DAT_TroopValueState::instance.attackInfo
                                                .peopleValuesArray[DAT_TroopValueState::instance.attackInfo.people2]
                                                .tile2
                                                = DAT_TileMapState::instance.directionTranslationMatrix[_y][iVar13]
                                                + _tile;
                                            DAT_TroopValueState::instance.attackInfo.people2
                                                = DAT_TroopValueState::instance.attackInfo.people2 + 1;
                                        }
                                    }
                                    iVar13 = iVar13 + 2;
                                } while (iVar13 < 8);
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
                                    iVar11 = 0;
                                    paiVar9 = DAT_TileMapState::instance.directionTranslationMatrix
                                        + DAT_TileMapState::instance.DAT_SomeY;
                                    iVar13 = DAT_TroopValueState::instance.attackInfo.lord3;
                                    do {
                                        iVar6 = (*paiVar9)[0] + _tile;
                                        if (DAT_TileMapState::instance.PathConnectionLayer[iVar6] != 0) {
                                            if (999 < iVar13)
                                                break;
                                            DAT_TroopValueState::instance.attackInfo.lordValuesArray[iVar13].tile
                                                = _tile;
                                            DAT_TroopValueState::instance.attackInfo
                                                .lordValuesArray[DAT_TroopValueState::instance.attackInfo.lord3]
                                                .tile2 = iVar6;
                                            iVar13 = DAT_TroopValueState::instance.attackInfo.lord3 + 1;
                                            DAT_TroopValueState::instance.attackInfo.lord3 = iVar13;
                                        }
                                        iVar11 = iVar11 + 1;
                                        paiVar9 = (int (*)[8])(*paiVar9 + 1);
                                    } while (iVar11 < 8);
                                }
                            }
                        }
                    }
                    puVar5 = (undefined*)(DAT_TileMapState::instance.ptr_SpecialAreasArray);
                    puVar4 = (undefined*)(DAT_TileMapState::instance.ptr_PathConnectionLayer);
                    if ((!_buildingID)
                        || (DAT_BuildingsState::instance.buildings[(short)_buildingID].owner != attackedPlayerID)) {
                        if (!(_logic & 0x300) || (_logic & 2)) {
                            if ((_logic & 0x40000000)
                                && DAT_TileMapState::instance.SEC_PathfindingCostTileMap1105[attackedPlayerID][_tile] != '\0') {
                                bVar1 = DAT_TileMapState::instance.DefaultHeightLayer[_tile];
                                piVar14 = (int*)((
                                    undefined*)((int*)((int)DAT_TroopValueState::instance.attackInfo.moatValuesArray
                                    + _offset + -0xc)));
                                *piVar14 = (int)((undefined*)(*piVar14 + 1));
                                puVar5 = (undefined*)(DAT_TileMapState::instance.ptr_SpecialAreasArray);
                                puVar4 = (undefined*)(DAT_TileMapState::instance.ptr_PathConnectionLayer);
                                DAT_TileMapState::instance.DAT_SomeY
                                    = (int)DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[_tile];
                                piVar14
                                    = (int*)(((char*)DAT_TileMapState::instance.ptr_MovementDirectionTranslationMatrix)
                                        + DAT_TileMapState::instance.DAT_SomeY * 0x20);
                                uVar3 = *(undefined2*)(((char*)DAT_TileMapState::instance.ptr_PathConnectionLayer)
                                    + _tile * 2 + -2);
                                DAT_TileMapState::instance.DAT_SomeTile = _tile;
                                *(undefined2*)(((char*)DAT_TileMapState::instance.ptr_SpecialAreasArray) + 4)
                                    = *(undefined2*)(((char*)DAT_TileMapState::instance.ptr_PathConnectionLayer)
                                        + _tile * 2 + 2);
                                *(undefined2*)(puVar5 + 0xc) = uVar3;
                                uVar3 = *(undefined2*)(puVar4 + piVar14[4] * 2 + _tile * 2);
                                *(undefined2*)puVar5 = *(undefined2*)(puVar4 + *piVar14 * 2 + _tile * 2);
                                *(undefined2*)(puVar5 + 8) = uVar3;
                                iVar13 = 0;
                                do {
                                    iVar11 = MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::
                                                                   calculateCanPlayerUnitsNavigateToAreaFromArea,
                                        DAT_PathFindingState::ptr)(playerID,
                                        (dword)((int)(DAT_TroopValueState::instance.attackInfo.startCon)),
                                        (dword)((int)(DAT_TileMapState::instance.specialAreasArray[iVar13])), 0);
                                    if (iVar11) {
                                        if (999 < DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].moat2
                                            || (_teamsDifferent = MACRO_CALL_MEMBER(
                                                    Map::Units::TroopValueState_Func::getTileInTargetedBuildingTiles,
                                                    this)(_tile),
                                                _teamsDifferent))
                                            break;
                                        iVar11 = DAT_TileMapState::instance
                                                     .directionTranslationMatrix[DAT_TileMapState::instance.DAT_SomeY]
                                                                                [iVar13]
                                            + _tile;
                                        if (!(DAT_TileMapState::instance.LogicLayer[iVar11] & 0x10000100U)
                                            && (uVar12 = MACRO_CALL_MEMBER(Map::TileMapState_Func::getTotalHeightAtTile,
                                                    DAT_TileMapState::ptr)(iVar11),
                                                _someY = DAT_TileMapState::instance.DAT_SomeY,
                                                bVar1 <= (int)(uVar12 + 0x10)
                                                    && ((int)(uVar12 - 0x10) <= bVar1))) {
                                            DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].moatValuesArray[DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].moat2].tile = _tile;
                                            DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].moatValuesArray[DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].moat2].tile2
                                                = DAT_TileMapState::instance.directionTranslationMatrix[_someY][iVar13]
                                                + _tile;
                                            DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].moat2
                                                = DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].moat2 + 1;
                                            if (DAT_TileMapState::instance.AIZoneLayer[_tile] != 0) {
                                                iVar13 = DAT_ViewportRenderState::instance.translationMatrix[_someY]
                                                             .addXgetTile;
                                                _someLimit = 1;
                                                goto LAB_0051f316;
                                            }
                                            break;
                                        }
                                    }
                                    iVar13 = iVar13 + 2;
                                } while (iVar13 < 8);
                            }
                        } else if (DAT_TileMapState::instance.SEC_PathfindingCostTileMap1105[attackedPlayerID][_tile] != '\0'
                            && (DAT_TileMapState::instance.WallOwnerLayer[_tile] & 7) + 1 == attackedPlayerID
                            && (uVar12 = (uint)DAT_TileMapState::instance.DefaultHeightLayer[_tile],
                                0x14 < (int)(DAT_TileMapState::instance.HeightLayer[_tile] - uVar12))
                            && !_buildingID) {
                            DAT_TileMapState::instance.DAT_SomeY
                                = (int)DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[_tile];
                            piVar14 = (int*)(((char*)DAT_TileMapState::instance.ptr_MovementDirectionTranslationMatrix)
                                + DAT_TileMapState::instance.DAT_SomeY * 0x20);
                            uVar3 = *(undefined2*)(((char*)DAT_TileMapState::instance.ptr_PathConnectionLayer)
                                + _tile * 2 + -2);
                            DAT_TileMapState::instance.DAT_SomeTile = _tile;
                            *(undefined2*)(((char*)DAT_TileMapState::instance.ptr_SpecialAreasArray) + 4)
                                = *(undefined2*)(((char*)DAT_TileMapState::instance.ptr_PathConnectionLayer) + _tile * 2
                                    + 2);
                            *(undefined2*)(puVar5 + 0xc) = uVar3;
                            uVar3 = *(undefined2*)(puVar4 + piVar14[4] * 2 + _tile * 2);
                            *(undefined2*)puVar5
                                = (undefined2)((undefined*)(*(undefined2*)(puVar4 + *piVar14 * 2 + _tile * 2)));
                            *(undefined2*)(puVar5 + 8) = (undefined2)((undefined*)(uVar3));
                            puVar5 = (undefined*)(DAT_TileMapState::instance.ptr_SpecialAreasArray);
                            puVar4 = (undefined*)(DAT_TileMapState::instance.ptr_PathConnectionLayer);
                            iVar11 = DAT_TileMapState::instance.DAT_SomeTile;
                            piVar14 = (int*)(((char*)DAT_TileMapState::instance.ptr_MovementDirectionTranslationMatrix)
                                + DAT_TileMapState::instance.DAT_SomeY * 0x20);
                            iVar13 = *piVar14 * 2 + DAT_TileMapState::instance.DAT_SomeTile * 2;
                            uVar3 = *(
                                undefined2*)(((char*)DAT_TileMapState::instance.ptr_PathConnectionLayer) + iVar13 + -2);
                            *(undefined2*)(((char*)DAT_TileMapState::instance.ptr_SpecialAreasArray) + 2) = *(
                                undefined2*)(((char*)DAT_TileMapState::instance.ptr_PathConnectionLayer) + iVar13 + 2);
                            *(undefined2*)(puVar5 + 0xe) = uVar3;
                            iVar13 = piVar14[4] * 2 + iVar11 * 2;
                            uVar3 = *(undefined2*)(puVar4 + iVar13 + -2);
                            *(undefined2*)(puVar5 + 6) = *(undefined2*)(puVar4 + iVar13 + 2);
                            *(undefined2*)(puVar5 + 10) = uVar3;
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
                                    iVar13 = MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::
                                                                   calculateCanPlayerUnitsNavigateToAreaFromArea,
                                        DAT_PathFindingState::ptr)(playerID,
                                        (dword)((int)(DAT_TroopValueState::instance.attackInfo.startCon)),
                                        (dword)((
                                            int)((int)DAT_TileMapState::instance.specialAreasArray[_direction + 1])),
                                        0);
                                    if (iVar13
                                        && (iVar13
                                            = MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::
                                                                    calculateCanPlayerUnitsNavigateToAreaFromArea,
                                                DAT_PathFindingState::ptr)(playerID,
                                                (dword)((int)(DAT_TroopValueState::instance.attackInfo.startCon)),
                                                (dword)((
                                                    int)(DAT_TileMapState::instance.specialAreasArray[_directionMin1])),
                                                0),
                                            iVar13 != 0)
                                        && !(DAT_TileMapState::instance.AIInfoLayer[_tile] & 0x20)) {
                                        if (999 < DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].wide2
                                            || (_teamsDifferent = MACRO_CALL_MEMBER(
                                                    Map::Units::TroopValueState_Func::getTileInTargetedBuildingTiles,
                                                    this)(_tile),
                                                _teamsDifferent))
                                            break;
                                        iVar13 = DAT_TileMapState::instance
                                                     .directionTranslationMatrix[DAT_TileMapState::instance.DAT_SomeY]
                                                                                [_direction]
                                            + _tile;
                                        if (!(DAT_TileMapState::instance.LogicLayer[iVar13] & 0x10000100U)
                                            && (uVar7 = MACRO_CALL_MEMBER(Map::TileMapState_Func::getTotalHeightAtTile,
                                                    DAT_TileMapState::ptr)(iVar13),
                                                (int)uVar12 <= (int)(uVar7 + 0x10)
                                                    && ((int)(uVar7 - 0x10) <= (int)uVar12))) {
                                            DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].wideValuesArray[DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].wide2].tile = _tile;
                                            iVar13 = DAT_TileMapState::instance.DAT_SomeY;
                                            DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].wideValuesArray[DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].wide2].tile2
                                                = DAT_TileMapState::instance
                                                      .directionTranslationMatrix[DAT_TileMapState::instance.DAT_SomeY]
                                                                                 [_direction]
                                                + _tile;
                                            DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].wide2
                                                = DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].wide2 + 1;
                                            DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].wide1
                                                = DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].wide1 + 1;
                                            DAT_TileMapState::instance.DAT_SomeX = _tile
                                                - DAT_ViewportRenderState::instance.translationMatrix[iVar13]
                                                      .addXgetTile;
                                            MACRO_CALL_MEMBER(
                                                Map::Navigation::PathFindingState_Func::updateAIZoneWithFloodFill0x20,
                                                DAT_PathFindingState::ptr)(
                                                4, (uint)(DAT_TileMapState::instance.DAT_SomeX), (uint)(iVar13));
                                            goto LAB_0051f320__next_tile;
                                        }
                                    }
                                }
                            }
                            DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].stone1 = DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].stone1 + 1;
                            iVar13 = 0;
                            do {
                                iVar11 = MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::
                                                               calculateCanPlayerUnitsNavigateToAreaFromArea,
                                    DAT_PathFindingState::ptr)(playerID,
                                    (dword)((int)(DAT_TroopValueState::instance.attackInfo.startCon)),
                                    (dword)((int)(DAT_TileMapState::instance.specialAreasArray[iVar13])), 0);
                                if (iVar11) {
                                    if (999 < DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].hack2
                                        || (_teamsDifferent = MACRO_CALL_MEMBER(
                                                Map::Units::TroopValueState_Func::getTileInTargetedBuildingTiles, this)(
                                                _tile),
                                            _teamsDifferent))
                                        break;
                                    iVar11
                                        = DAT_TileMapState::instance
                                              .directionTranslationMatrix[DAT_TileMapState::instance.DAT_SomeY][iVar13]
                                        + _tile;
                                    if (!(DAT_TileMapState::instance.LogicLayer[iVar11] & 0x10000100U)
                                        && (uVar7 = MACRO_CALL_MEMBER(Map::TileMapState_Func::getTotalHeightAtTile,
                                                DAT_TileMapState::ptr)(iVar11),
                                            iVar11 = DAT_TileMapState::instance.DAT_SomeY,
                                            (int)uVar12 <= (int)(uVar7 + 0x10)
                                                && ((int)(uVar7 - 0x10) <= (int)uVar12))) {
                                        DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].hackValuesArray[DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].hack2].tile = _tile;
                                        DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].hackValuesArray[DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].hack2].tile2
                                            = DAT_TileMapState::instance.directionTranslationMatrix[iVar11][iVar13]
                                            + _tile;
                                        iVar13 = DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].hack2;
                                        DAT_TileMapState::instance
                                            .AIZoneLayer[DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].hackValuesArray[iVar13].tile2] = 10;
                                        bVar1 = DAT_TileMapState::instance.AIZoneLayer[_tile];
                                        DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].hack2 = iVar13 + 1;
                                        if (bVar1) {
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
                                iVar13 = iVar13 + 2;
                            } while (iVar13 < 8);
                            DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].hack1 = DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].hack1 + 1;
                            if (!(_logic & 0x400000)) {
                                iVar13 = (int)(char)DAT_TileMapState::instance.AIZoneLayer[_tile];
                                DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].scale1 = DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].scale1 + 1;
                                if ((iVar13) && (iVar13 < DAT_TroopValueState::instance.attackInfo.scaleZone)) {
                                    DAT_TroopValueState::instance.attackInfo.scaleZone = iVar13;
                                }
                                iVar13 = 0;
                                do {
                                    iVar11 = MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::
                                                                   calculateCanPlayerUnitsNavigateToAreaFromArea,
                                        DAT_PathFindingState::ptr)(playerID,
                                        (dword)((int)(DAT_TroopValueState::instance.attackInfo.startCon)),
                                        (dword)((int)(DAT_TileMapState::instance.specialAreasArray[iVar13])), 0);
                                    if (iVar11) {
                                        if (999 < DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].scale2
                                            || (_teamsDifferent = MACRO_CALL_MEMBER(
                                                    Map::Units::TroopValueState_Func::getTileInTargetedBuildingTiles,
                                                    this)(_tile),
                                                _teamsDifferent))
                                            break;
                                        iVar11 = DAT_TileMapState::instance
                                                     .directionTranslationMatrix[DAT_TileMapState::instance.DAT_SomeY]
                                                                                [iVar13]
                                            + _tile;
                                        if (!(DAT_TileMapState::instance.LogicLayer[iVar11] & 0x10000100U)
                                            && (uVar7 = MACRO_CALL_MEMBER(Map::TileMapState_Func::getTotalHeightAtTile,
                                                    DAT_TileMapState::ptr)(iVar11),
                                                (int)uVar12 <= (int)(uVar7 + 0x10)
                                                    && ((int)(uVar7 - 0x10) <= (int)uVar12))) {
                                            DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].scaleValuesArray[DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].scale2].tile = _tile;
                                            _someY = DAT_TileMapState::instance.DAT_SomeY;
                                            DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].scaleValuesArray[DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].scale2].tile2
                                                = DAT_TileMapState::instance
                                                      .directionTranslationMatrix[DAT_TileMapState::instance.DAT_SomeY]
                                                                                 [iVar13]
                                                + _tile;
                                            DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].scale2
                                                = DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].scale2 + 1;
                                            goto LAB_0051e94c;
                                        }
                                    }
                                    iVar13 = iVar13 + 2;
                                } while (iVar13 < 8);
                            }
                        }
                    } else {
                        int BVar2
                            = (int)(short)DAT_BuildingsState::instance.buildings[(short)_buildingID].buildingType;
                        uVar12 = (uint)DAT_TileMapState::instance.DefaultHeightLayer[_tile];
                        if (DAT_BuildingDefinedData::instance.IsGateOrTowerArray[BVar2]) {
                            if (DAT_TileMapState::instance.SEC_PathfindingCostTileMap1105[attackedPlayerID][_tile] != '\0') {
                                piVar14 = (int*)((undefined*)((
                                    int*)((int)DAT_TroopValueState::instance.attackInfo.gateValuesArray + _offset + -0xc)));
                                *piVar14 = (int)((undefined*)(*piVar14 + 1));
                                puVar5 = (undefined*)(DAT_TileMapState::instance.ptr_SpecialAreasArray);
                                puVar4 = (undefined*)(DAT_TileMapState::instance.ptr_PathConnectionLayer);
                                DAT_TileMapState::instance.DAT_SomeY
                                    = (int)DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[_tile];
                                DAT_TileMapState::instance.DAT_SomeX = _tile
                                    - DAT_ViewportRenderState::instance
                                          .translationMatrix[DAT_TileMapState::instance.DAT_SomeY]
                                          .addXgetTile;
                                piVar14 = (int*)(((char*)DAT_TileMapState::instance.ptr_MovementDirectionTranslationMatrix)
                                    + DAT_TileMapState::instance.DAT_SomeY * 0x20);
                                uVar3 = *(undefined2*)(((char*)DAT_TileMapState::instance.ptr_PathConnectionLayer)
                                    + _tile * 2 + -2);
                                DAT_TileMapState::instance.DAT_SomeTile = _tile;
                                *(undefined2*)(((char*)DAT_TileMapState::instance.ptr_SpecialAreasArray) + 4)
                                    = *(undefined2*)(((char*)DAT_TileMapState::instance.ptr_PathConnectionLayer) + _tile * 2
                                        + 2);
                                *(undefined2*)(puVar5 + 0xc) = uVar3;
                                uVar3 = *(undefined2*)(puVar4 + piVar14[4] * 2 + _tile * 2);
                                *(undefined2*)puVar5 = *(undefined2*)(puVar4 + *piVar14 * 2 + _tile * 2);
                                *(undefined2*)(puVar5 + 8) = uVar3;
                                iVar13 = 0;
                            LAB_0051e890:
                                if (DAT_TileMapState::instance.specialAreasArray[iVar13]
                                    != DAT_TroopValueState::instance.attackInfo.startCon)
                                    break;
                                if (DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].some1000ArrayIndex_2
                                        < 1000
                                    && (_teamsDifferent = MACRO_CALL_MEMBER(
                                            Map::Units::TroopValueState_Func::getTileInTargetedBuildingTiles, this)(_tile),
                                        !_teamsDifferent)) {
                                    iVar11 = DAT_TileMapState::instance
                                                 .directionTranslationMatrix[DAT_TileMapState::instance.DAT_SomeY][iVar13]
                                        + _tile;
                                    if ((DAT_TileMapState::instance.LogicLayer[iVar11] & 0x10000100U)
                                        || (uVar7 = MACRO_CALL_MEMBER(Map::TileMapState_Func::getTotalHeightAtTile,
                                                DAT_TileMapState::ptr)(iVar11),
                                            (int)(uVar7 + 0x10) < (int)uVar12 || ((int)uVar12 < (int)(uVar7 - 0x10))))
                                        break;
                                    DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].gateValuesArray[DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].some1000ArrayIndex_2].tile = _tile;
                                    _someY = DAT_TileMapState::instance.DAT_SomeY;
                                    DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].gateValuesArray[DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].some1000ArrayIndex_2].tile2
                                        = DAT_TileMapState::instance
                                              .directionTranslationMatrix[DAT_TileMapState::instance.DAT_SomeY][iVar13]
                                        + _tile;
                                    DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].some1000ArrayIndex_2 = DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].some1000ArrayIndex_2 + 1;
                                LAB_0051e94c:
                                    if (DAT_TileMapState::instance.AIZoneLayer[_tile] != 0) {
                                        iVar13 = DAT_ViewportRenderState::instance.translationMatrix[_someY].addXgetTile;
                                        _someLimit = DAT_TroopValueState::instance.attackInfo.someDistanceLimit;
                                    LAB_0051f316:
                                        DAT_TileMapState::instance.DAT_SomeX = _tile - iVar13;
                                        MACRO_CALL_MEMBER(
                                            Map::Navigation::PathFindingState_Func::recomputeALGPathFindingTileMapUnk,
                                            DAT_PathFindingState::ptr)(
                                            _someLimit, (uint)(DAT_TileMapState::instance.DAT_SomeX), (uint)(_someY), 1);
                                    }
                                }
                            }
                        } else {
                            if (DAT_BuildingDefinedData::instance.BuildingTypeHasHealth[BVar2] != 0) {
                                if (!(DAT_TileMapState::instance.LogicLayer[_tile] & 0xf000000U)) {
                                    DAT_TileMapState::instance.DAT_SomeY
                                        = (int)DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[_tile];
                                    piVar14 = (int*)((
                                        undefined*)((int*)((int)DAT_TroopValueState::instance.attackInfo.townValuesArray
                                        + _offset + -0xc)));
                                    *piVar14 = (int)((undefined*)(*piVar14 + 1));
                                    puVar5 = (undefined*)(DAT_TileMapState::instance.ptr_SpecialAreasArray);
                                    puVar4 = (undefined*)(DAT_TileMapState::instance.ptr_PathConnectionLayer);
                                    piVar14
                                        = (int*)(((char*)DAT_TileMapState::instance.ptr_MovementDirectionTranslationMatrix)
                                            + DAT_TileMapState::instance.DAT_SomeY * 0x20);
                                    uVar3 = *(undefined2*)(((char*)DAT_TileMapState::instance.ptr_PathConnectionLayer)
                                        + _tile * 2 + -2);
                                    DAT_TileMapState::instance.DAT_SomeTile = _tile;
                                    *(undefined2*)(((char*)DAT_TileMapState::instance.ptr_SpecialAreasArray) + 4)
                                        = *(undefined2*)(((char*)DAT_TileMapState::instance.ptr_PathConnectionLayer)
                                            + _tile * 2 + 2);
                                    *(undefined2*)(puVar5 + 0xc) = uVar3;
                                    uVar3 = *(undefined2*)(puVar4 + piVar14[4] * 2 + _tile * 2);
                                    *(undefined2*)puVar5 = *(undefined2*)(puVar4 + *piVar14 * 2 + _tile * 2);
                                    *(undefined2*)(puVar5 + 8) = uVar3;
                                    iVar13 = 0;
                                    do {
                                        if (DAT_TileMapState::instance.specialAreasArray[iVar13]
                                            == DAT_TroopValueState::instance.attackInfo.startCon) {
                                            if (999 < DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].town2
                                                || (_teamsDifferent = MACRO_CALL_MEMBER(
                                                        Map::Units::TroopValueState_Func::getTileInTargetedBuildingTiles,
                                                        this)(_tile),
                                                    _teamsDifferent))
                                                break;
                                            _heightTown = MACRO_CALL_MEMBER(
                                                Map::TileMapState_Func::getTotalHeightAtTile, DAT_TileMapState::ptr)(
                                                DAT_TileMapState::instance
                                                    .directionTranslationMatrix[DAT_TileMapState::instance.DAT_SomeY]
                                                                               [iVar13]
                                                + _tile);
                                            iVar11 = DAT_TileMapState::instance.DAT_SomeY;
                                            if ((int)uVar12 <= (int)(_heightTown + 0x10)
                                                && (int)(_heightTown - 0x10) <= (int)uVar12) {
                                                DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].townValuesArray[DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].town2].tile = _tile;
                                                DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].townValuesArray[DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].town2].tile2
                                                    = DAT_TileMapState::instance.directionTranslationMatrix[iVar11][iVar13]
                                                    + _tile;
                                                DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].town2
                                                    = DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].town2 + 1;
                                                break;
                                            }
                                        }
                                        iVar13 = iVar13 + 2;
                                    } while (iVar13 < 8);
                                }
                            } else {
                                if ((_logic & 0x10000000)) {
                                    _area = DAT_TileMapState::instance.PathConnectionLayer[_tile];
                                    if (DAT_TileMapState::instance.SEC_PathfindingCostTileMap1105[attackedPlayerID][_tile] != '\0') {
                                        _buildingID_3 = (int)DAT_TileMapState::instance.BuildingLayer[_tile];
                                        _teamsDifferent = MACRO_CALL_MEMBER(
                                            Map::Units::TroopValueState_Func::attackInfoHasHigh2Building, this)(
                                            _buildingID_3);
                                        if ((!_teamsDifferent)
                                            && (_teamsDifferent = MACRO_CALL_MEMBER(
                                                    Map::Units::TroopValueState_Func::attackInfoHasArch2Building, this)(
                                                    _buildingID_3),
                                                puVar5 = (undefined*)DAT_TileMapState::instance.ptr_SpecialAreasArray,
                                                puVar4 = (undefined*)DAT_TileMapState::instance.ptr_AIZoneLayer,
                                                !_teamsDifferent)) {
                                            DAT_TileMapState::instance.DAT_SomeY
                                                = (int)DAT_ViewportRenderState::instance
                                                      .tileTranslationMatrix_YComponent[_tile];
                                            piVar14 = (int*)((char*)DAT_TileMapState::instance
                                                                 .ptr_MovementDirectionTranslationMatrix
                                                + DAT_TileMapState::instance.DAT_SomeY * 0x10);
                                            uVar3 = *(undefined2*)(((char*)DAT_TileMapState::instance.ptr_AIZoneLayer)
                                                + _tile + -1);
                                            DAT_TileMapState::instance.DAT_SomeTile = _tile;
                                            *(undefined2*)(((char*)DAT_TileMapState::instance.ptr_SpecialAreasArray)
                                                + 2)
                                                = *(undefined2*)(((char*)DAT_TileMapState::instance.ptr_AIZoneLayer)
                                                    + _tile + 1);
                                            *(undefined2*)(puVar5 + 6) = uVar3;
                                            uVar3 = *(undefined2*)(puVar4 + piVar14[4] + _tile);
                                            *(undefined2*)puVar5 = *(undefined2*)(puVar4 + *piVar14 + _tile);
                                            *(undefined2*)(puVar5 + 4) = uVar3;
                                            sVar10 = 0;
                                            psVar8 = DAT_TileMapState::instance.specialAreasArray;
                                            do {
                                                if (*psVar8 != 0) {
                                                    sVar10 = (int)*psVar8;
                                                }
                                                psVar8 = psVar8 + 2;
                                            } while (psVar8 < &DAT_TileMapState::instance.specialAreasArray[8]);
                                            if (0 < sVar10) {
                                                DAT_BuildingsState::instance.buildings[_buildingID_3]
                                                    .unknownCounterTo10000_0x2b4 = (short)sVar10;
                                                _teamsDifferent = MACRO_CALL_MEMBER(
                                                    Map::Buildings::BuildingsState_Func::hasHumanPlayerUnitsOnBuilding,
                                                    DAT_BuildingsState::ptr)(_buildingID_3);
                                                if (_teamsDifferent) {
                                                    DAT_TroopValueState::instance.attackInfo.high1
                                                        = DAT_TroopValueState::instance.attackInfo.high1 + 1;
                                                    if (DAT_TroopValueState::instance.attackInfo.high2 < 1000
                                                        && (iVar13 = MACRO_CALL_MEMBER(
                                                                Map::Navigation::PathFindingState_Func::
                                                                    calculateCanPlayerUnitsNavigateToAreaFromArea,
                                                                DAT_PathFindingState::ptr)(playerID,
                                                                (dword)((int)(DAT_TroopValueState::instance.attackInfo
                                                                        .startCon)),
                                                                (dword)((int)((short)_area)), 0),
                                                            iVar13 != 0)) {
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
                                                        && (iVar13 = MACRO_CALL_MEMBER(
                                                                Map::Navigation::PathFindingState_Func::
                                                                    calculateCanPlayerUnitsNavigateToAreaFromArea,
                                                                DAT_PathFindingState::ptr)(playerID,
                                                                (dword)((int)(DAT_TroopValueState::instance.attackInfo
                                                                        .startCon)),
                                                                (dword)((int)((short)_area)), 0),
                                                            iVar13 != 0)) {
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
            LAB_0051f320__next_tile:
                _tile = _tile + 1;
                if (0x13a0f < _tile) {
                    return;
                }
            } while (true);
            iVar13 = iVar13 + 2;
            if (7 < iVar13)
                goto LAB_0051f320__next_tile;
            goto LAB_0051e890;
        }

    }
}
}
