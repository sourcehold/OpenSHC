#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/LandscapeState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/UI/BottomLeftTextDisplayState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/LogicHelpers/Logic1.hpp"
#include "OpenSHC/Map/LogicHelpers/Logic2.hpp"

#include "OpenSHC/Globals/DAT_BottomLeftTextDisplayState.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_LandscapeState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::Buildings::BuildingType;
    using OpenSHC::Map::LogicHelpers::L_BUILDING;
    using OpenSHC::Map::LogicHelpers::L_FARM_FIELD_APPLE;
    using OpenSHC::Map::LogicHelpers::L_NONE;
    using OpenSHC::Map::LogicHelpers::L2_THICK_SCRUB;

    /* the header declares the high parameter as int*; it is the plain average high */
    // FUNCTION: STRONGHOLDCRUSADER 0x00515740
    void TileMapState::placeApplefarm(
        int playerID, uint x, uint y, BuildingType buildingType, undefined4 param_5, int variation, int* averageHeight)
    {
        int index = 0;
        int buildingID = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::setupBuildingData,
            DAT_BuildingsState::ptr)(playerID, x, y, (undefined4)averageHeight, (BuildingType)(short)buildingType, 3,
            playerID, variation);
        this->placedBuildingID = buildingID;
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::markBuildingFootprintFlag, this)(x, y, 10);

        /* the 8 apple tree tiles */
        for (int i = 0; i < 8; i++) {
            DAT_BuildingsState::instance.buildings[buildingID].tileRefs[i]
                = DAT_ViewportRenderState::instance
                      .translationMatrix[DAT_TerrainDefinedData::instance.AppleFarmOffsets[i].y + y]
                      .addXgetTile
                + DAT_TerrainDefinedData::instance.AppleFarmOffsets[i].x + x;
        }

        /* the farm house */
        do {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(index, 3);
            int tileUnk = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + y].addXgetTile + x
                + this->buildingX;
            this->HeightLayer[tileUnk] = (byte)(int)averageHeight;
            this->LogicLayer[tileUnk] = this->LogicLayer[tileUnk] | L_BUILDING;
            this->BuildingLayer[tileUnk] = (short)buildingID;
            this->BuildingWasLayer[tileUnk] = (uchar)buildingType;
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setTerrain, this)(
                playerID, tileUnk, this->buildingY + y, 2, L_NONE, L2_THICK_SCRUB);
            index++;
            this->ChangedLayer[tileUnk] = 2;
        } while (index < this->constructionTileCount);

        for (int i = 0; i < 8; i++) {
            int tileUnk = DAT_BuildingsState::instance.buildings[buildingID].tileRefs[i];
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::resetTileAndClearMoat, this)(tileUnk);
            this->LogicLayer[tileUnk] = this->LogicLayer[tileUnk] | L_FARM_FIELD_APPLE;
            this->ChangedLayer[tileUnk] = 2;
            MACRO_CALL_MEMBER(OpenSHC::Map::LandscapeState_Func::placeAppleTree, DAT_LandscapeState::ptr)(buildingID,
                DAT_TerrainDefinedData::instance.AppleFarmOffsets[i].x + x,
                DAT_TerrainDefinedData::instance.AppleFarmOffsets[i].y + y);
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
