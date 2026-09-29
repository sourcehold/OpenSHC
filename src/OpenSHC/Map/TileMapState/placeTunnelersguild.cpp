
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::Buildings::BuildingType;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00507E00
    void TileMapState::placeTunnelersguild(
        int param_1, int* param_2, uint param_3, undefined4 param_4, uint param_5, int param_6, undefined4 param_7)
    {
        int* piVar1;
        int iVar2;
        int buildingID;
        int iVar3;
        uint y;
        uint x;
        int iVar4;
        int iVar5;
        int local_8;
        piVar1 = param_2;
        iVar5 = DAT_GameCore::instance.uniqueGameObjectTracker;
        iVar4 = 0;
        if (param_6 == 0xf) {
            local_8 = 0;
        } else {
            local_8 = param_6 / 2;
        }
        iVar2 = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::setupBuildingData,
            DAT_BuildingsState::ptr)(param_1, (uint)((int)(param_2)), param_3, (undefined4)((int)(param_7)),
            (BuildingType)((int)((int)(short)param_4)), param_5, param_1, 0xf);
        buildingID = (int)(short)iVar2;
        this->placedBuildingID = buildingID;
        DAT_BuildingsState::instance.buildings[buildingID].uidWhenPlaced = iVar5;
        param_2 = &DAT_BuildingsState::instance.buildings[buildingID].tileRefs[0];
        do {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                iVar4, (int)((int)(param_5)));
            iVar3 = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + param_3].addXgetTile
                + this->buildingX + (int)piVar1;
            *param_2 = iVar3;
            this->HeightLayer[iVar3] = (byte)param_7;
            this->LogicLayer[iVar3] = this->LogicLayer[iVar3] | 1024;
            this->BuildingLayer[iVar3] = (short)iVar2;
            iVar4 = iVar4 + 1;
            param_2 = param_2 + 1;
            this->BuildingWasLayer[iVar3] = (uchar)param_4;
            this->ChangedLayer[iVar3] = 2;
        } while (iVar4 < this->constructionTileCount);
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setMiscDisplayLayer, this)(buildingID);
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updatePathLinkagesForBuilding, this)(buildingID);
        x = (int)piVar1 + DAT_TerrainDefinedData::instance.BuildingPartsOffsets[local_8][1].x;
        y = param_3 + DAT_TerrainDefinedData::instance.BuildingPartsOffsets[local_8][1].y;
        iVar4 = MACRO_CALL_MEMBER(
            OpenSHC::Map::Buildings::BuildingsState_Func::setupBuildingData, DAT_BuildingsState::ptr)(
            param_1, x, y, (undefined4)((int)(param_7)), OpenSHC::Map::Buildings::BT_PARADEGROUND5, 5, param_1, 0xf);
        iVar2 = (int)(short)iVar4;
        DAT_BuildingsState::instance.buildings[iVar2].uidWhenPlaced = iVar5;
        DAT_BuildingsState::instance.buildings[iVar2].quarryStockpileID = (undefined2)this->placedBuildingID;
        param_5 = 0;
        do {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                param_5, (int)((int)(DAT_BuildingsState::instance.buildings[iVar2].widthOrHeight)));
            iVar5 = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + y].addXgetTile
                + this->buildingX + x;
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::resetTileAndClearMoat, this)(iVar5);
            this->HeightLayer[iVar5] = (byte)param_7;
            this->BuildingLayer[iVar5] = (short)iVar4;
            param_5 = param_5 + 1;
            this->BuildingWasLayer[iVar5] = (uchar)param_4;
            this->ChangedLayer[iVar5] = 2;
        } while ((int)param_5 < this->constructionTileCount);
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setMiscDisplayLayer, this)(iVar2);
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updatePathLinkagesForBuilding, this)(iVar2);
        MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updateWalkAndPathLayer,
            DAT_PathFindingState::ptr)(8, x, y);
        MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::setupTunnelersGuildCampgroundPositions,
            DAT_BuildingsState::ptr)(param_1);
        return;
    }

}
}
