
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/UI/BottomLeftTextDisplayState.func.hpp"
#include "OpenSHC/Map/LogicHelpers/Logic1.hpp"
#include "OpenSHC/Map/LogicHelpers/Logic2.hpp"

#include "OpenSHC/Globals/DAT_BottomLeftTextDisplayState.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
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
    // FUNCTION: STRONGHOLDCRUSADER 0x00514F30
    void TileMapState::placeWheatfarm(int playerID, uint x, uint y, undefined4 buildingType, undefined4 param_5,
        int variation, undefined4 averageHeight)
    {
        uint uVar1;
        int buildingID;
        XYPair* pXVar2;
        int iVar3;
        int* piVar4;
        int iVar5;
        uVar1 = x;
        iVar5 = 0;
        buildingID = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::setupBuildingData,
            DAT_BuildingsState::ptr)(playerID, x, y, (undefined4)((int)(averageHeight)),
            (BuildingType)((int)((int)(short)buildingType)), 3, playerID, variation);
        this->placedBuildingID = buildingID;
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::markBuildingFootprintFlag, this)(x, (int)((int)(y)), 9);
        x = 6;
        pXVar2 = DAT_TerrainDefinedData::instance
                     .WheatFarmTiles[DAT_GameState::instance.playerDataArray[playerID].unkWheatFarmOrientation];
        piVar4 = &DAT_BuildingsState::instance.buildings[buildingID].tileRefs[1];
        do {
            piVar4[-1] = DAT_ViewportRenderState::instance.translationMatrix[pXVar2->y + y].addXgetTile + uVar1
                + ((XYPair*)&pXVar2->x)->x;
            *piVar4 = DAT_ViewportRenderState::instance.translationMatrix[pXVar2[1].y + y].addXgetTile + pXVar2[1].x
                + uVar1;
            piVar4[1] = DAT_ViewportRenderState::instance.translationMatrix[pXVar2[2].y + y].addXgetTile + pXVar2[2].x
                + uVar1;
            piVar4[2] = DAT_ViewportRenderState::instance.translationMatrix[pXVar2[3].y + y].addXgetTile + pXVar2[3].x
                + uVar1;
            piVar4[3] = DAT_ViewportRenderState::instance.translationMatrix[pXVar2[4].y + y].addXgetTile + pXVar2[4].x
                + uVar1;
            x = x - 1;
            piVar4[4] = DAT_ViewportRenderState::instance.translationMatrix[pXVar2[5].y + y].addXgetTile + pXVar2[5].x
                + uVar1;
            pXVar2 = pXVar2 + 6;
            piVar4 = piVar4 + 6;
        } while (x != 0);
        iVar3 = DAT_GameState::instance.playerDataArray[playerID].unkWheatFarmOrientation + 1;
        DAT_GameState::instance.playerDataArray[playerID].unkWheatFarmOrientation = iVar3;
        if (1 < iVar3) {
            DAT_GameState::instance.playerDataArray[playerID].unkWheatFarmOrientation = 0;
        }
        do {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(iVar5, 3);
            /*
              fixme: repurposed
             */
            variation._0_2_ = (short)buildingID;
            iVar3 = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + y].addXgetTile + uVar1
                + this->buildingX;
            this->HeightLayer[iVar3] = (byte)averageHeight;
            this->LogicLayer[iVar3] = this->LogicLayer[iVar3] | 1024;
            this->BuildingLayer[iVar3] = (short)variation;
            this->BuildingWasLayer[iVar3] = (uchar)buildingType;
            this->ChangedLayer[iVar3] = 2;
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setTerrain, this)(playerID, iVar3, this->buildingY + y,
                2, OpenSHC::Map::LogicHelpers::L_NONE, OpenSHC::Map::LogicHelpers::L2_THICK_SCRUB);
            iVar5 = iVar5 + 1;
        } while (iVar5 < this->constructionTileCount);
        piVar4 = &DAT_BuildingsState::instance.buildings[buildingID].tileRefs[0];
        iVar5 = 0x24;
        do {
            iVar3 = *piVar4;
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::resetTileAndClearMoat, this)(iVar3);
            this->LogicLayer[iVar3] = this->LogicLayer[iVar3] | 16777216;
            this->BuildingLayer[iVar3] = (short)variation;
            piVar4 = piVar4 + 1;
            iVar5 = iVar5 + -1;
            this->BuildingWasLayer[iVar3] = (uchar)buildingType;
            this->ChangedLayer[iVar3] = 2;
        } while (iVar5 != 0);
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setMiscDisplayLayer, this)(buildingID);
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updatePathLinkagesForBuilding, this)(buildingID);
        if (((playerID == DAT_GameSynchronyState::instance.currentPlayerSlotID)
                && (DAT_GameState::instance.playerDataArray[playerID].availablePeasantsAtFire
                    < (int)DAT_BuildingsState::instance.buildings[buildingID].buildingTypeBasedEmployeeCount))
            && ((DAT_GameState::instance.playerDataArray[playerID].populationCap
                    <= DAT_GameState::instance.playerDataArray[playerID].currentPopulation
                || (DAT_GameState::instance.playerDataArray[playerID].popularity < 5000)))) {
            MACRO_CALL_MEMBER(OpenSHC::UI::BottomLeftTextDisplayState_Func::setBottomLeftTextDisplayText,
                DAT_BottomLeftTextDisplayState::ptr)(1, 0x4d, 1, (TextMessageBLLookupStructUnion)0x0, 100, 6000);
        }
        return;
    }

}
}
