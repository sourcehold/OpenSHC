
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/UI/BottomLeftTextDisplayState.func.hpp"
#include "OpenSHC/Map/LogicHelpers/Logic1.hpp"
#include "OpenSHC/Map/LogicHelpers/Logic2.hpp"

#include "OpenSHC/Globals/DAT_BottomLeftTextDisplayState.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::Logic1;
    using OpenSHC::Map::LogicHelpers::Logic2;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
     */
    /*
      WARNING: Enum "DPERRInt": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x005151C0
    void TileMapState::placeHopfarm(
        int param_1, uint param_2, uint param_3, undefined4 param_4, undefined4 param_5, int param_6, int param_7)
    {
        undefined1* puVar1;
        uint uVar2;
        int buildingID;
        XYPair* pXVar3;
        int iVar4;
        int* piVar5;
        int buildingSizeTileIndex;
        uVar2 = param_2;
        buildingSizeTileIndex = 0;
        buildingID = MACRO_CALL_MEMBER(
            OpenSHC::Map::Buildings::BuildingsState_Func::setupBuildingData, DAT_BuildingsState::ptr)(param_1, param_2,
            param_3, (undefined4)((int)(param_7)), (BuildingType)((int)((int)(short)param_4)), 3, param_1, param_6);
        this->placedBuildingID = buildingID;
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::markBuildingFootprintFlag, this)(
            param_2, (int)((int)(param_3)), 9);
        iVar4 = *(int*)&DAT_GameState::instance.playerDataArray[param_1].unkHopFarmVariation;
        param_2 = 4;
        pXVar3 = DAT_TerrainDefinedData::instance.HopFarmProperty1[iVar4];
        piVar5 = &DAT_BuildingsState::instance.buildings[buildingID].tileRefs[1];
        do {
            piVar5[-1] = DAT_ViewportRenderState::instance.translationMatrix[pXVar3->y + param_3].addXgetTile
                + ((XYPair*)&pXVar3->x)->x + uVar2;
            *piVar5 = DAT_ViewportRenderState::instance.translationMatrix[pXVar3[1].y + param_3].addXgetTile
                + pXVar3[1].x + uVar2;
            piVar5[1] = DAT_ViewportRenderState::instance.translationMatrix[pXVar3[2].y + param_3].addXgetTile
                + pXVar3[2].x + uVar2;
            piVar5[2] = DAT_ViewportRenderState::instance.translationMatrix[pXVar3[3].y + param_3].addXgetTile
                + pXVar3[3].x + uVar2;
            piVar5[3] = DAT_ViewportRenderState::instance.translationMatrix[pXVar3[4].y + param_3].addXgetTile
                + pXVar3[4].x + uVar2;
            param_2 = param_2 - 1;
            piVar5[4] = DAT_ViewportRenderState::instance.translationMatrix[pXVar3[5].y + param_3].addXgetTile
                + pXVar3[5].x + uVar2;
            pXVar3 = pXVar3 + 6;
            piVar5 = piVar5 + 6;
        } while (param_2 != 0);
        *(ushort*)&DAT_BuildingsState::instance.buildings[buildingID].field_0x26e
            = (-(ushort)(iVar4 != 0) & 0xffb6) + 0x51;
        do {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                buildingSizeTileIndex, 3);
            param_6._0_2_ = (short)buildingID;
            iVar4 = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + param_3].addXgetTile
                + this->buildingX + uVar2;
            this->HeightLayer[iVar4] = (byte)param_7;
            this->LogicLayer[iVar4] = this->LogicLayer[iVar4] | 1024;
            this->BuildingLayer[iVar4] = (short)param_6;
            this->BuildingWasLayer[iVar4] = (uchar)param_4;
            this->ChangedLayer[iVar4] = 2;
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setTerrain, this)(param_1, iVar4,
                this->buildingY + param_3, 2, OpenSHC::Map::LogicHelpers::L_NONE,
                OpenSHC::Map::LogicHelpers::L2_THICK_SCRUB);
            buildingSizeTileIndex = buildingSizeTileIndex + 1;
        } while (buildingSizeTileIndex < this->constructionTileCount);
        param_7 = 0;
        do {
            iVar4 = *(int*)&DAT_GameState::instance.playerDataArray[param_1].unkHopFarmVariation;
            iVar4
                = DAT_ViewportRenderState::instance
                      .translationMatrix[DAT_TerrainDefinedData::instance.HopFarmProperty1[iVar4][param_7].y + param_3]
                      .addXgetTile
                + DAT_TerrainDefinedData::instance.HopFarmProperty1[iVar4][param_7].x + uVar2;
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::resetTileAndClearMoat, this)(iVar4);
            this->LogicLayer[iVar4] = this->LogicLayer[iVar4] | 33554432;
            this->BuildingLayer[iVar4] = (short)param_6;
            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updatePathLinkagesInAllEightDirections,
                DAT_PathFindingState::ptr)(
                DAT_TerrainDefinedData::instance
                        .HopFarmProperty1[*(int*)&DAT_GameState::instance.playerDataArray[param_1].unkHopFarmVariation]
                                         [param_7]
                        .y
                    + param_3,
                iVar4);
            param_7 = param_7 + 1;
            this->BuildingWasLayer[iVar4] = (uchar)param_4;
            this->ChangedLayer[iVar4] = 2;
        } while (param_7 < 0x18);
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setMiscDisplayLayer, this)(buildingID);
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updatePathLinkagesForBuilding, this)(buildingID);
        puVar1 = &DAT_GameState::instance.playerDataArray[param_1].unkHopFarmVariation;
        *(int*)puVar1 = *(int*)puVar1 + 1;
        if (1 < *(int*)&DAT_GameState::instance.playerDataArray[param_1].unkHopFarmVariation) {
            *(undefined4*)&DAT_GameState::instance.playerDataArray[param_1].unkHopFarmVariation = 0;
        }
        if (((param_1 == DAT_GameSynchronyState::instance.currentPlayerSlotID)
                && (DAT_GameState::instance.playerDataArray[param_1].availablePeasantsAtFire
                    < (int)DAT_BuildingsState::instance.buildings[buildingID].buildingTypeBasedEmployeeCount))
            && ((DAT_GameState::instance.playerDataArray[param_1].populationCap
                    <= DAT_GameState::instance.playerDataArray[param_1].currentPopulation
                || (DAT_GameState::instance.playerDataArray[param_1].popularity < 5000)))) {
            MACRO_CALL_MEMBER(OpenSHC::UI::BottomLeftTextDisplayState_Func::setBottomLeftTextDisplayText,
                DAT_BottomLeftTextDisplayState::ptr)(1, 0x4d, 1, (TextMessageBLLookupStructUnion)0x0, 100, 6000);
        }
        return;
    }

}
}
