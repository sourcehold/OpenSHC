#include "../TileMapState.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/UI/BottomLeftTextDisplayState.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Map/LogicHelpers/Logic1.hpp"
#include "OpenSHC/Map/LogicHelpers/Logic2.hpp"

#include "OpenSHC/Globals/DAT_BottomLeftTextDisplayState.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x00514520
    void TileMapState::placeKillingPit(
        int playerID, uint x, uint y, short buildingType, uint buildingSize, int variation, int averageHeight)
    {
        /* the original masks the terrain bits once, before the building is even created */
        int grassOrScrub = this->Logic2Layer[DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x]
            & (OpenSHC::Map::LogicHelpers::L2_OASIS_GRASS | OpenSHC::Map::LogicHelpers::L2_THICK_SCRUB);
        int index = 0;
        int buildingID = MACRO_CALL_MEMBER(
            OpenSHC::Map::Buildings::BuildingsState_Func::setupBuildingData, DAT_BuildingsState::ptr)(
            playerID, x, y, averageHeight, (BuildingType)buildingType, buildingSize, playerID, variation);
        this->placedBuildingID = buildingID;
        if (buildingType != OpenSHC::Map::Buildings::BT_KILLINGPIT) {
            averageHeight -= 4;
            if (averageHeight < 0) {
                averageHeight = 0;
            }
        }

        while (true) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                index, buildingSize);
            int tile = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + y].addXgetTile
                + this->buildingX + x;
            if (index < countof(DAT_BuildingsState::instance.buildings[buildingID].tileRefs)) {
                DAT_BuildingsState::instance.buildings[buildingID].tileRefs[index] = tile;
            }
            this->HeightLayer[tile] = (byte)averageHeight;
            this->BuildingLayer[tile] = (short)buildingID;
            this->BuildingWasLayer[tile] = (uchar)buildingType;
            if (buildingType != OpenSHC::Map::Buildings::BT_KILLINGPIT) {
                /* bug:fixme: a pit dug in grass comes back as thick scrub, not as the terrain it replaced */
                if (grassOrScrub != 0) {
                    MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setTerrain, this)(playerID, tile,
                        this->buildingY + y, 3, OpenSHC::Map::LogicHelpers::L_NONE,
                        OpenSHC::Map::LogicHelpers::L2_THICK_SCRUB);
                } else {
                    MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setTerrain, this)(playerID, tile,
                        this->buildingY + y, 3, OpenSHC::Map::LogicHelpers::L_NONE,
                        OpenSHC::Map::LogicHelpers::L2_EARTH_AND_STONES);
                }
            }
            index++;
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
