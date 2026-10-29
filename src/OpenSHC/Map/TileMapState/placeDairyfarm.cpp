#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/UI/BottomLeftTextDisplayState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
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

    using OpenSHC::Map::Buildings::BuildingType;
    using OpenSHC::Map::LogicHelpers::L_BUILDING;
    using OpenSHC::Map::LogicHelpers::L_FARM_FIELD_DAIRY;
    using OpenSHC::Map::LogicHelpers::L_NONE;
    using OpenSHC::Map::LogicHelpers::L2_THICK_SCRUB;

    /* the header declares the variation parameter as int*; it is the plain int variation index */
    // FUNCTION: STRONGHOLDCRUSADER 0x005154D0
    void TileMapState::placeDairyfarm(int playerID, uint x, uint y, undefined4 buildingType, undefined4 param_5,
        int* variation, undefined4 averageHeight)
    {
        int index = 0;
        int buildingID = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::setupBuildingData,
            DAT_BuildingsState::ptr)(playerID, x, y, averageHeight, (BuildingType)(short)buildingType, 3, playerID,
            (int)variation);
        this->placedBuildingID = buildingID;
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::markBuildingFootprintFlag, this)(x, y, 10);

        /* 27 tiles from one of four layouts; tiles 4.. are the field and carry an initial crop stage */
        for (int i = 0; i < 27; i++) {
            DAT_BuildingsState::instance.buildings[buildingID].tileRefs[i]
                = DAT_ViewportRenderState::instance
                      .translationMatrix[DAT_TerrainDefinedData::instance
                                             .field878_0xf5c[DAT_GameState::instance.playerDataArray[playerID]
                                                                     .dairyFarmVariationMod4][i]
                                             .offset.y
                          + y]
                      .addXgetTile
                + DAT_TerrainDefinedData::instance
                      .field878_0xf5c[DAT_GameState::instance.playerDataArray[playerID].dairyFarmVariationMod4][i]
                      .offset.x
                + x;
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::resetTileAndClearMoat, this)(
                DAT_BuildingsState::instance.buildings[buildingID].tileRefs[i]);
            if (i >= 4) {
                this->DamageLayer[DAT_BuildingsState::instance.buildings[buildingID].tileRefs[i]]
                    = (byte)DAT_TerrainDefinedData::instance
                          .field878_0xf5c[DAT_GameState::instance.playerDataArray[playerID].dairyFarmVariationMod4]
                                             [i]
                          .property;
            }
        }
        DAT_GameState::instance.playerDataArray[playerID].dairyFarmVariationMod4++;
        if (DAT_GameState::instance.playerDataArray[playerID].dairyFarmVariationMod4 > 3) {
            DAT_GameState::instance.playerDataArray[playerID].dairyFarmVariationMod4 = 0;
        }

        /* the farm house */
        do {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(index, 3);
            int tileUnk = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + y].addXgetTile
                + this->buildingX + x;
            this->HeightLayer[tileUnk] = (byte)averageHeight;
            this->LogicLayer[tileUnk] = this->LogicLayer[tileUnk] | L_BUILDING;
            this->BuildingLayer[tileUnk] = (short)buildingID;
            this->BuildingWasLayer[tileUnk] = (uchar)buildingType;
            this->ChangedLayer[tileUnk] = 2;
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setTerrain, this)(
                playerID, tileUnk, this->buildingY + y, 2, L_NONE, L2_THICK_SCRUB);
            index++;
        } while (index < this->constructionTileCount);

        for (int i = 4; i < 27; i++) {
            int tileUnk = DAT_BuildingsState::instance.buildings[buildingID].tileRefs[i];
            this->LogicLayer[tileUnk] = this->LogicLayer[tileUnk] | L_FARM_FIELD_DAIRY;
            this->BuildingLayer[tileUnk] = (short)buildingID;
            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updatePathLinkagesInAllEightDirections,
                DAT_PathFindingState::ptr)(DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tileUnk], tileUnk);
            this->BuildingWasLayer[tileUnk] = (uchar)buildingType;
            this->ChangedLayer[tileUnk] = 2;
        }
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setMiscDisplayLayer, this)(buildingID);
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updatePathLinkagesForBuilding, this)(buildingID);

        /* not enough idle peasants for the workers: tell the local player */
        if (playerID == DAT_GameSynchronyState::instance.currentPlayerSlotID
            && DAT_BuildingsState::instance.buildings[buildingID].buildingTypeBasedEmployeeCount
                > DAT_GameState::instance.playerDataArray[playerID].availablePeasantsAtFire
            && (DAT_GameState::instance.playerDataArray[playerID].populationCap
                    <= DAT_GameState::instance.playerDataArray[playerID].currentPopulation
                || DAT_GameState::instance.playerDataArray[playerID].popularity < 5000)) {
            MACRO_CALL_MEMBER(OpenSHC::UI::BottomLeftTextDisplayState_Func::setBottomLeftTextDisplayText,
                DAT_BottomLeftTextDisplayState::ptr)(1, 0x4d, 1, 0, 100, 6000);
        }
    }

}
}
