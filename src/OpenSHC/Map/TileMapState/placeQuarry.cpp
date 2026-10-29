
#include "OpenSHC/AI/AIVState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/UI/BottomLeftTextDisplayState.func.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_AIVState.hpp"
#include "OpenSHC/Globals/DAT_BottomLeftTextDisplayState.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_BUILDING;

    using OpenSHC::Commands::MappersEnum;
    using OpenSHC::Map::Buildings::BuildingType;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      WARNING: Enum "MappersEnumShort": Some values do not have unique names
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
    // FUNCTION: STRONGHOLDCRUSADER 0x00508250
    void TileMapState::placeQuarry(int playerID, uint x, uint y, undefined4 buildingType, uint buildingSize,
        int buildingOrientation, uint high)
    {
        int index = 0;
        int uid = DAT_GameCore::instance.uniqueGameObjectTracker;
        int quarryID = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::setupBuildingData, DAT_BuildingsState::ptr)(playerID, x, y, high,
            (BuildingType)(int)(short)buildingType, buildingSize, playerID, buildingOrientation);
        this->placedBuildingID = quarryID;
        DAT_BuildingsState::instance.buildings[quarryID].uidWhenPlaced = uid;

        do {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(index, buildingSize);
            int tileUnk = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + y].addXgetTile + x + this->buildingX;
            index++;
            this->HeightLayer[tileUnk] = (byte)high;
            this->LogicLayer[tileUnk] = this->LogicLayer[tileUnk] | L_BUILDING;
            this->BuildingLayer[tileUnk] = (short)quarryID;
            this->BuildingWasLayer[tileUnk] = (uchar)buildingType;
            this->ChangedLayer[tileUnk] = 2;
        } while (index < this->constructionTileCount);
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setMiscDisplayLayer, this)(quarryID);
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updatePathLinkagesForBuilding, this)(quarryID);

        /* nine attempts at a pile location, moving further from the quarry each time */
        int attempt = 1;
        do {
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::findQuarryPileLocation, DAT_BuildingsState::ptr)(
                playerID, x, y, buildingSize, 2, attempt, OpenSHC::Commands::M_MAPPER_QUARRYPILE);
            if (this->buildingPlacementFail == FALSE) {
                break;
            }
            attempt++;
        } while (attempt < 10);
        if (this->buildingPlacementFail != FALSE) {
            return;
        }

        /* x/y now name the pile corner */
        x = x + DAT_BuildingsState::instance.DAT_TempXOffset;
        y = y + DAT_BuildingsState::instance.DAT_TempYOffset;
        int tileIndex = 0;
        int lowest = 1000;
        int highest = 0;
        do {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(tileIndex, 2);
            int tileHeight = this->HeightLayer[DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + y].addXgetTile
                + x + this->buildingX];
            if (tileHeight > highest) {
                highest = tileHeight;
            }
            if (tileHeight < lowest) {
                lowest = tileHeight;
            }
            tileIndex++;
        } while (tileIndex < this->constructionTileCount);
        high = (highest - lowest) / 2 + lowest;

        tileIndex = 0;
        int pileID = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::setupBuildingData, DAT_BuildingsState::ptr)(playerID, x, y,
            high, OpenSHC::Map::Buildings::BT_QUARRYSTOCKPILE, 2, playerID, buildingOrientation);
        MACRO_CALL_MEMBER(OpenSHC::AI::AIVState_Func::incrementStructureHeatMapTile, DAT_AIVState::ptr)(x, y);
        DAT_BuildingsState::instance.buildings[pileID].uidWhenPlaced = uid;
        DAT_BuildingsState::instance.buildings[quarryID].quarryStockpileID = (short)pileID;
        do {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(tileIndex, 2);
            int tileUnk = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + y].addXgetTile + x + this->buildingX;
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::resetTileAndClearMoat, this)(tileUnk);
            this->HeightLayer[tileUnk] = (byte)high;
            this->LogicLayer[tileUnk] = this->LogicLayer[tileUnk] | L_BUILDING;
            this->BuildingLayer[tileUnk] = (short)pileID;
            tileIndex++;
            this->BuildingWasLayer[tileUnk] = (uchar)buildingType;
            this->ChangedLayer[tileUnk] = 2;
        } while (tileIndex < this->constructionTileCount);
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setMiscDisplayLayer, this)(pileID);
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updatePathLinkagesForBuilding, this)(pileID);

        if (playerID == DAT_GameSynchronyState::instance.currentPlayerSlotID
            && DAT_BuildingsState::instance.buildings[pileID].buildingTypeBasedEmployeeCount
                > DAT_GameState::instance.playerDataArray[playerID].availablePeasantsAtFire
            && (DAT_GameState::instance.playerDataArray[playerID].populationCap
                    <= DAT_GameState::instance.playerDataArray[playerID].currentPopulation
                || DAT_GameState::instance.playerDataArray[playerID].popularity < 5000)) {
            /* "Not enough workers available to run this building." */
            MACRO_CALL_MEMBER(OpenSHC::UI::BottomLeftTextDisplayState_Func::setBottomLeftTextDisplayText,
                DAT_BottomLeftTextDisplayState::ptr)(
                1, 0x4d, 1, 0, 100, 6000);
        }
    }

}
}
