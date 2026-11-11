#include "../TileMapState.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/UI/BottomLeftTextDisplayState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

#include "OpenSHC/Globals/DAT_BottomLeftTextDisplayState.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x005076A0
    void TileMapState::placeBarracks(int playerID, uint xPosition, uint yPosition, undefined4 buildingType,
        uint buildingSize, int buildingOrientation, undefined4 param_7)
    {
        int _buildingID;
        int iVar2;
        int iVar3;
        uint uVar4;
        int iVar5;
        uint uVar6;
        int iVar7;
        int local_c;
        uint const y = yPosition;
        iVar7 = DAT_GameCore::instance.uniqueGameObjectTracker;
        iVar5 = 0;
        if (buildingOrientation == 0xf) {
            local_c = 0;
        } else {
            local_c = buildingOrientation / 2;
        }
        _buildingID = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::setupBuildingData,
            DAT_BuildingsState::ptr)(playerID, xPosition, y, (undefined4)((int)(param_7)),
            (BuildingType)((int)((short)buildingType)), buildingSize, playerID, 0xf);
        iVar2 = (int)(short)_buildingID;
        this->placedBuildingID = iVar2;
        DAT_BuildingsState::instance.buildings[iVar2].uidWhenPlaced = iVar7;
        // fixme: the original walks the tile references with a pointer held in the dead y parameter, and
        // only reusing the parameter reproduces that slot (a separate int* local costs 10 points)
        yPosition = (uint)&DAT_BuildingsState::instance.buildings[iVar2].tileRefs[0];
        do {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                iVar5, (int)(buildingSize));
            iVar3 = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + y].addXgetTile
                + this->buildingX + xPosition;
            *(int*)yPosition = iVar3;
            this->HeightLayer[iVar3] = (byte)param_7;
            this->LogicLayer[iVar3] |= 0x400;
            this->BuildingLayer[iVar3] = (short)_buildingID;
            iVar5 += 1;
            yPosition += sizeof(int);
            this->BuildingWasLayer[iVar3] = (uchar)buildingType;
            this->ChangedLayer[iVar3] = 2;
        } while (iVar5 < this->constructionTileCount);
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setMiscDisplayLayer, this)(iVar2);
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updatePathLinkagesForBuilding, this)(iVar2);
        uVar6 = y + DAT_TerrainDefinedData::instance.BuildingPartsOffsets[local_c][0].y;
        uVar4 = xPosition + DAT_TerrainDefinedData::instance.BuildingPartsOffsets[local_c][0].x;
        iVar5 = MACRO_CALL_MEMBER(
            OpenSHC::Map::Buildings::BuildingsState_Func::setupBuildingData, DAT_BuildingsState::ptr)(playerID, uVar4,
            uVar6, (undefined4)((int)(param_7)), OpenSHC::Map::Buildings::BT_PARADEGROUND3, 5, playerID, 0xf);
        _buildingID = (int)(short)iVar5;
        DAT_BuildingsState::instance.buildings[_buildingID].uidWhenPlaced = iVar7;
        DAT_BuildingsState::instance.buildings[_buildingID].quarryStockpileID = (undefined2)this->placedBuildingID;
        buildingSize = 0;
        do {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                buildingSize, (int)(DAT_BuildingsState::instance.buildings[_buildingID].widthOrHeight));
            iVar2 = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + uVar6].addXgetTile
                + this->buildingX + uVar4;
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::resetTileAndClearMoat, this)(iVar2);
            this->HeightLayer[iVar2] = (byte)param_7;
            if ((this->buildingX == 2) && (this->buildingY == 2)) {
                this->LogicLayer[iVar2] |= 0x400;
            }
            this->BuildingLayer[iVar2] = (short)iVar5;
            buildingSize += 1;
            this->BuildingWasLayer[iVar2] = (uchar)buildingType;
            this->ChangedLayer[iVar2] = 2;
        } while ((int)buildingSize < this->constructionTileCount);
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setMiscDisplayLayer, this)(_buildingID);
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updatePathLinkagesForBuilding, this)(_buildingID);
        MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updateWalkAndPathLayer,
            DAT_PathFindingState::ptr)(8, uVar4, uVar6);
        uVar6 = DAT_TerrainDefinedData::instance.BuildingPartsOffsets[local_c][1].y + y;
        uVar4 = DAT_TerrainDefinedData::instance.BuildingPartsOffsets[local_c][1].x + xPosition;
        iVar5 = MACRO_CALL_MEMBER(
            OpenSHC::Map::Buildings::BuildingsState_Func::setupBuildingData, DAT_BuildingsState::ptr)(playerID, uVar4,
            uVar6, (undefined4)((int)(param_7)), OpenSHC::Map::Buildings::BT_PARADEGROUND4, 5, playerID, 0xf);
        _buildingID = (int)(short)iVar5;
        DAT_BuildingsState::instance.buildings[_buildingID].uidWhenPlaced = iVar7;
        DAT_BuildingsState::instance.buildings[_buildingID].quarryStockpileID = (undefined2)this->placedBuildingID;
        buildingSize = 0;
        do {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                buildingSize, (int)(DAT_BuildingsState::instance.buildings[_buildingID].widthOrHeight));
            iVar2 = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + uVar6].addXgetTile
                + this->buildingX + uVar4;
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::resetTileAndClearMoat, this)(iVar2);
            this->HeightLayer[iVar2] = (byte)param_7;
            if ((this->buildingX == 2) && (this->buildingY == 2)) {
                this->LogicLayer[iVar2] |= 0x400;
            }
            this->BuildingLayer[iVar2] = (short)iVar5;
            buildingSize += 1;
            this->BuildingWasLayer[iVar2] = (uchar)buildingType;
            this->ChangedLayer[iVar2] = 2;
        } while ((int)buildingSize < this->constructionTileCount);
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setMiscDisplayLayer, this)(_buildingID);
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updatePathLinkagesForBuilding, this)(_buildingID);
        MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updateWalkAndPathLayer,
            DAT_PathFindingState::ptr)(8, uVar4, uVar6);
        uVar6 = DAT_TerrainDefinedData::instance.BuildingPartsOffsets[local_c][2].y + y;
        uVar4 = DAT_TerrainDefinedData::instance.BuildingPartsOffsets[local_c][2].x + xPosition;
        iVar5 = MACRO_CALL_MEMBER(
            OpenSHC::Map::Buildings::BuildingsState_Func::setupBuildingData, DAT_BuildingsState::ptr)(playerID, uVar4,
            uVar6, (undefined4)((int)(param_7)), OpenSHC::Map::Buildings::BT_PARADEGROUND2, 5, playerID, 0xf);
        _buildingID = (int)(short)iVar5;
        DAT_BuildingsState::instance.buildings[_buildingID].uidWhenPlaced = iVar7;
        DAT_BuildingsState::instance.buildings[_buildingID].quarryStockpileID = (undefined2)this->placedBuildingID;
        buildingSize = 0;
        do {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                buildingSize, (int)(DAT_BuildingsState::instance.buildings[_buildingID].widthOrHeight));
            iVar7 = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + uVar6].addXgetTile
                + this->buildingX + uVar4;
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::resetTileAndClearMoat, this)(iVar7);
            this->HeightLayer[iVar7] = (byte)param_7;
            if ((this->buildingX == 2) && (this->buildingY == 2)) {
                this->LogicLayer[iVar7] |= 0x400;
            }
            this->BuildingLayer[iVar7] = (short)iVar5;
            this->BuildingWasLayer[iVar7] = (uchar)buildingType;
            buildingSize += 1;
            this->ChangedLayer[iVar7] = 2;
        } while ((int)buildingSize < this->constructionTileCount);
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setMiscDisplayLayer, this)(_buildingID);
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updatePathLinkagesForBuilding, this)(_buildingID);
        MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updateWalkAndPathLayer,
            DAT_PathFindingState::ptr)(8, uVar4, uVar6);
        if ((short)buildingType == 8) {
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::setupMercenaryPostCampgroundPositions,
                DAT_BuildingsState::ptr)(playerID);
        } else {
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::setupBarracksCampgroundPositions,
                DAT_BuildingsState::ptr)(playerID);
        }
        if (playerID == DAT_GameSynchronyState::instance.currentPlayerSlotID
            && DAT_GameState::instance.playerDataArray[playerID].availablePeasantsAtFire
                < (int)DAT_BuildingsState::instance.buildings[_buildingID].buildingTypeBasedEmployeeCount
            && (DAT_GameState::instance.playerDataArray[playerID].populationCap
                    <= DAT_GameState::instance.playerDataArray[playerID].currentPopulation
                || (DAT_GameState::instance.playerDataArray[playerID].popularity < 5000))) {
            MACRO_CALL_MEMBER(OpenSHC::UI::BottomLeftTextDisplayState_Func::setBottomLeftTextDisplayText,
                DAT_BottomLeftTextDisplayState::ptr)(1, 0x4d, 1, 0, 100, 6000);
        }
        return;
    }

}
}
