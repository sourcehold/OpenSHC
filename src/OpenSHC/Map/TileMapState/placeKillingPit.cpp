
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/UI/BottomLeftTextDisplayState.func.hpp"
#include "OpenSHC/Map/LogicHelpers/Logic1.hpp"
#include "OpenSHC/Map/LogicHelpers/Logic2.hpp"

#include "OpenSHC/Globals/DAT_BottomLeftTextDisplayState.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
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
    // FUNCTION: STRONGHOLDCRUSADER 0x00514520
    void TileMapState::placeKillingPit(int playerID, uint x, uint y, undefined4 buildingType, uint sizeIndex,
        int buildingState, int height)
    {
        /* the original masks the terrain bits once, before the building is even created */
        int grassOrScrub = this->Logic2Layer[DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x]
            & (OpenSHC::Map::LogicHelpers::L2_OASIS_GRASS | OpenSHC::Map::LogicHelpers::L2_THICK_SCRUB);
        int index = 0;
        int buildingID = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::setupBuildingData, DAT_BuildingsState::ptr)(playerID, x, y, height,
            (BuildingType)(int)(short)buildingType, sizeIndex, playerID, buildingState);
        this->placedBuildingID = buildingID;
        if ((short)buildingType != 0x43) {
            height = height - 4;
            if (height < 0) {
                height = 0;
            }
        }

        do {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(index, sizeIndex);
            int tile = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + y].addXgetTile + this->buildingX + x;
            if (index < 0x24) {
                DAT_BuildingsState::instance.buildings[buildingID].tileRefs[index] = tile;
            }
            this->HeightLayer[tile] = (byte)height;
            this->BuildingLayer[tile] = (short)buildingID;
            this->BuildingWasLayer[tile] = (uchar)(short)buildingType;
            if ((short)buildingType != 0x43) {
                /* bug:fixme: a pit dug in grass comes back as thick scrub, not as the terrain it replaced */
                Logic2 terrain;
                if (grassOrScrub == 0) {
                    terrain = OpenSHC::Map::LogicHelpers::L2_EARTH_AND_STONES;
                } else {
                    terrain = OpenSHC::Map::LogicHelpers::L2_THICK_SCRUB;
                }
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setTerrain, this)(
                    playerID, tile, this->buildingY + y, 3, OpenSHC::Map::LogicHelpers::L_NONE, terrain);
            }
            index++;
            this->ChangedLayer[tile] = 2;
        } while (index < this->constructionTileCount);
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setMiscDisplayLayer, this)(buildingID);
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updatePathLinkagesForBuilding, this)(buildingID);

        if (playerID == DAT_GameSynchronyState::instance.currentPlayerSlotID
            && DAT_GameState::instance.playerDataArray[playerID].availablePeasantsAtFire
                < DAT_BuildingsState::instance.buildings[buildingID].buildingTypeBasedEmployeeCount
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
