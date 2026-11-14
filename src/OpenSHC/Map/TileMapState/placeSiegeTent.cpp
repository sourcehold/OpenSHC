#include "../TileMapState.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/UI/BottomLeftTextDisplayState.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"

#include "OpenSHC/Globals/DAT_BottomLeftTextDisplayState.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_BUILDING;

    // FUNCTION: STRONGHOLDCRUSADER 0x00506E10
    void TileMapState::placeSiegeTent(
        int playerID, uint x, uint y, short buildingType, uint buildingSize, int variation, undefined4 averageHeight)
    {
        int index = 0;
        int buildingID = MACRO_CALL_MEMBER(
            OpenSHC::Map::Buildings::BuildingsState_Func::setupBuildingData, DAT_BuildingsState::ptr)(
            playerID, x, y, averageHeight, (BuildingType)buildingType, buildingSize, playerID, variation);
        this->placedBuildingID = buildingID;
        while (true) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                index, buildingSize);
            int tile = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + y].addXgetTile
                + this->buildingX + x;
            if (index < countof(DAT_BuildingsState::instance.buildings[buildingID].tileRefs)) {
                DAT_BuildingsState::instance.buildings[buildingID].tileRefs[index] = tile;
            }
            this->HeightLayer[tile] = (byte)averageHeight;
            this->LogicLayer[tile] |= L_BUILDING;
            this->BuildingLayer[tile] = (short)buildingID;
            index++;
            this->BuildingWasLayer[tile] = (uchar)buildingType;
            this->ChangedLayer[tile] = 2;
            if (index >= this->constructionTileCount) {
                break;
            }
        }
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setMiscDisplayLayer, this)(buildingID);
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updatePathLinkagesForBuilding, this)(buildingID);
        if (playerID == DAT_GameSynchronyState::instance.currentPlayerSlotID
            && DAT_BuildingsState::instance.buildings[buildingID].buildingTypeBasedEmployeeCount
                > DAT_GameState::instance.playerDataArray[playerID].availablePeasantsAtFire
            && (DAT_GameState::instance.playerDataArray[playerID].populationCap
                    <= DAT_GameState::instance.playerDataArray[playerID].currentPopulation
                || DAT_GameState::instance.playerDataArray[playerID].popularity < 5000)) {
            MACRO_CALL_MEMBER(OpenSHC::UI::BottomLeftTextDisplayState_Func::setBottomLeftTextDisplayText,
                DAT_BottomLeftTextDisplayState::ptr)(1, OpenSHC::DE::SHCDE::TEXT_PANEL_FEEDBACK, 1, 0, 100, 6000);
        }
    }

}
}
