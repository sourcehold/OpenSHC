
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
    // FUNCTION: STRONGHOLDCRUSADER 0x00506BD0
    void TileMapState::placeWorkshopOrHovel(
        int playerID, uint x, uint y, BuildingType type, uint size, int orientation, undefined4 averageHeight)
    {
        int buildingID = MACRO_CALL_MEMBER(
            OpenSHC::Map::Buildings::BuildingsState_Func::setupBuildingData, DAT_BuildingsState::ptr)(
            playerID, x, y, averageHeight, (BuildingType)(short)type, size, playerID, orientation);
        /* the original stores only the low half of the int field */
        *(short*)&DAT_BuildingsState::instance.buildings[buildingID].hovelVisualStyle
            = (short)DAT_GameState::instance.playerDataArray[playerID].hovelCountUpToEight;
        this->placedBuildingID = buildingID;
        if (type == OpenSHC::Map::Buildings::BT_HOVEL) {
            DAT_GameState::instance.playerDataArray[playerID].hovelCountUpToEight
                = (DAT_GameState::instance.playerDataArray[playerID].hovelCountUpToEight + 1) % 7;
        }
        int tileIndex = 0;
        do {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(tileIndex, size);
            int tile = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + y].addXgetTile
                + this->buildingX + x;
            if (tileIndex < 36) {
                DAT_BuildingsState::instance.buildings[buildingID].tileRefs[tileIndex] = tile;
            }
            this->HeightLayer[tile] = (byte)averageHeight;
            this->LogicLayer[tile] = this->LogicLayer[tile] | L_BUILDING;
            this->BuildingLayer[tile] = (short)buildingID;
            tileIndex++;
            this->BuildingWasLayer[tile] = (uchar)type;
            this->ChangedLayer[tile] = 2;
        } while (tileIndex < this->constructionTileCount);
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
