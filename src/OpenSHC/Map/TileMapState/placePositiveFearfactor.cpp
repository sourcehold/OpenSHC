
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/UI/BottomLeftTextDisplayState.func.hpp"

#include "OpenSHC/Globals/DAT_BottomLeftTextDisplayState.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_BUILDING;

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
    // FUNCTION: STRONGHOLDCRUSADER 0x00506F40
    void TileMapState::placePositiveFearfactor(int playerID, uint x, uint y, undefined4 buildingType,
        undefined4 variation, uint buildingSize, undefined4 param_7, undefined4 height)
    {
        int buildingID = MACRO_CALL_MEMBER(
            OpenSHC::Map::Buildings::BuildingsState_Func::setupBuildingData, DAT_BuildingsState::ptr)(
            playerID, x, y, height, (BuildingType)(short)buildingType, buildingSize, playerID, (short)variation);
        this->placedBuildingID = buildingID;
        int buildingSizeTileIndex = 0;
        do {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                buildingSizeTileIndex, buildingSize);
            int tile = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + y].addXgetTile
                + this->buildingX + x;
            if (buildingSizeTileIndex < 36) {
                DAT_BuildingsState::instance.buildings[buildingID].tileRefs[buildingSizeTileIndex] = tile;
            }
            this->HeightLayer[tile] = (byte)height;
            this->LogicLayer[tile] = this->LogicLayer[tile] | L_BUILDING;
            this->BuildingLayer[tile] = (short)buildingID;
            buildingSizeTileIndex++;
            this->ChangedLayer[tile] = 2;
        } while (buildingSizeTileIndex < this->constructionTileCount);
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setMiscDisplayLayer, this)(buildingID);
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updatePathLinkagesForBuilding, this)(buildingID);
        if (playerID == DAT_GameSynchronyState::instance.currentPlayerSlotID
            && DAT_GameState::instance.playerDataArray[playerID].availablePeasantsAtFire
                < (int)DAT_BuildingsState::instance.buildings[buildingID].buildingTypeBasedEmployeeCount
            && (DAT_GameState::instance.playerDataArray[playerID].populationCap
                    <= DAT_GameState::instance.playerDataArray[playerID].currentPopulation
                || DAT_GameState::instance.playerDataArray[playerID].popularity < 5000)) {
            MACRO_CALL_MEMBER(OpenSHC::UI::BottomLeftTextDisplayState_Func::setBottomLeftTextDisplayText,
                DAT_BottomLeftTextDisplayState::ptr)(
                1, 0x4d, 1, OpenSHC::UI::TextMessageBLLookupStructUnion(), 100, 6000);
        }
    }

}
}
