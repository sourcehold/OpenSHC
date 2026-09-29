
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
    // FUNCTION: STRONGHOLDCRUSADER 0x005154D0
    void TileMapState::placeDairyfarm(int param_1, uint param_2, uint param_3, undefined4 param_4, undefined4 param_5,
        int* param_6, undefined4 param_7)
    {
        int iVar1;
        uint uVar2;
        int buildingID;
        int iVar3;
        int* piVar4;
        int iVar5;
        uVar2 = param_3;
        iVar3 = 0;
        buildingID = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::setupBuildingData,
            DAT_BuildingsState::ptr)(param_1, param_2, param_3, (undefined4)((int)(param_7)),
            (BuildingType)((int)((int)(short)param_4)), 3, param_1, (int)((int)(param_6)));
        this->placedBuildingID = buildingID;
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::markBuildingFootprintFlag, this)(
            param_2, (int)((int)(param_3)), 10);
        iVar5 = 0;
        param_6 = &DAT_BuildingsState::instance.buildings[buildingID].tileRefs[0];
        do {
            iVar1 = DAT_GameState::instance.playerDataArray[param_1].dairyFarmVariationMod4;
            /*
              0 to 3*27 + 26 = 107
             */
            iVar1 = DAT_ViewportRenderState::instance
                        .translationMatrix[DAT_TerrainDefinedData::instance.field1009_0xf5c[iVar1][iVar5].offset.y
                            + param_3]
                        .addXgetTile
                + DAT_TerrainDefinedData::instance.field1009_0xf5c[iVar1][iVar5].offset.x + param_2;
            *param_6 = iVar1;
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::resetTileAndClearMoat, this)(iVar1);
            if (3 < iVar5) {
                this->DamageLayer[*param_6]
                    = (byte)DAT_TerrainDefinedData::instance
                          .field1009_0xf5c[DAT_GameState::instance.playerDataArray[param_1].dairyFarmVariationMod4]
                                          [iVar5]
                          .property;
            }
            param_6 = param_6 + 1;
            iVar5 = iVar5 + 1;
        } while (iVar5 < 27);
        piVar4 = &DAT_GameState::instance.playerDataArray[param_1].dairyFarmVariationMod4;
        *piVar4 = *piVar4 + 1;
        if (3 < DAT_GameState::instance.playerDataArray[param_1].dairyFarmVariationMod4) {
            DAT_GameState::instance.playerDataArray[param_1].dairyFarmVariationMod4 = 0;
        }
        do {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(iVar3, 3);
            param_3._0_2_ = (short)buildingID;
            iVar5 = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + uVar2].addXgetTile
                + this->buildingX + param_2;
            this->HeightLayer[iVar5] = (byte)param_7;
            this->LogicLayer[iVar5] = this->LogicLayer[iVar5] | 0x400;
            this->BuildingLayer[iVar5] = (short)param_3;
            this->BuildingWasLayer[iVar5] = (uchar)param_4;
            this->ChangedLayer[iVar5] = 2;
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setTerrain, this)(param_1, iVar5,
                this->buildingY + uVar2, 2, OpenSHC::Map::LogicHelpers::L_NONE,
                OpenSHC::Map::LogicHelpers::L2_THICK_SCRUB);
            iVar3 = iVar3 + 1;
        } while (iVar3 < this->constructionTileCount);
        piVar4 = &DAT_BuildingsState::instance.buildings[buildingID].tileRefs[4];
        iVar3 = 23;
        do {
            iVar5 = *piVar4;
            this->LogicLayer[iVar5] = this->LogicLayer[iVar5] | 0x8000000;
            this->BuildingLayer[iVar5] = (short)param_3;
            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updatePathLinkagesInAllEightDirections,
                DAT_PathFindingState::ptr)(
                (int)DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[iVar5], iVar5);
            piVar4 = piVar4 + 1;
            iVar3 = iVar3 + -1;
            this->BuildingWasLayer[iVar5] = (uchar)param_4;
            this->ChangedLayer[iVar5] = 2;
        } while (iVar3 != 0);
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setMiscDisplayLayer, this)(buildingID);
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updatePathLinkagesForBuilding, this)(buildingID);
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
