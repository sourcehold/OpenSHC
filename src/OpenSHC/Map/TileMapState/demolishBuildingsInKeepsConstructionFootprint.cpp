
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::Buildings::BuildingLogicalState;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004FA760
    void TileMapState::demolishBuildingsInKeepsConstructionFootprint(undefined4 param_1, int x, int y,
        undefined4 buildingType, int sizeIndex, int param_6, int param_7)
    {
        int index = 0;
        do {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(index, sizeIndex);
            int tile = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + y].addXgetTile + this->buildingX + x;
            if (this->BuildingLayer[tile] != 0) {
                this->showNoRubbleWhenDestroyingBuilding = 1;
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::destroyBuilding, DAT_BuildingsState::ptr)(this->BuildingLayer[tile]);
            }
            index++;
        } while (index < this->constructionTileCount);

        /* the keep drags three towers and two outbuildings with it, laid out per keep variant */
        int variant = (short)buildingType - 0x28;
        {
            int tile = DAT_ViewportRenderState::instance.translationMatrix[DAT_TerrainDefinedData::instance.field130_0x264[variant][0].y + y].addXgetTile
                + DAT_TerrainDefinedData::instance.field130_0x264[variant][0].x + x;
            if (this->BuildingLayer[tile] != 0) {
                this->showNoRubbleWhenDestroyingBuilding = 1;
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::destroyBuilding, DAT_BuildingsState::ptr)(this->BuildingLayer[tile]);
            }
        }

        {
            int tile = DAT_ViewportRenderState::instance.translationMatrix[DAT_TerrainDefinedData::instance.field130_0x264[variant][1].y + y].addXgetTile
                + DAT_TerrainDefinedData::instance.field130_0x264[variant][1].x + x;
            if (this->BuildingLayer[tile] != 0) {
                this->showNoRubbleWhenDestroyingBuilding = 1;
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::destroyBuilding, DAT_BuildingsState::ptr)(this->BuildingLayer[tile]);
            }
        }

        {
            int tile = DAT_ViewportRenderState::instance.translationMatrix[DAT_TerrainDefinedData::instance.field130_0x264[variant][2].y + y].addXgetTile
                + DAT_TerrainDefinedData::instance.field130_0x264[variant][2].x + x;
            if (this->BuildingLayer[tile] != 0) {
                this->showNoRubbleWhenDestroyingBuilding = 1;
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::destroyBuilding, DAT_BuildingsState::ptr)(this->BuildingLayer[tile]);
            }
        }

        index = 0;
        do {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(index, 7);
            int tile = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + y + DAT_TerrainDefinedData::instance.keepOutbuildingOffsets_0x384[variant][0].yOffset].addXgetTile + this->buildingX + x
                + DAT_TerrainDefinedData::instance.keepOutbuildingOffsets_0x384[variant][0].xOffset;
            if (this->BuildingLayer[tile] != 0) {
                this->showNoRubbleWhenDestroyingBuilding = 1;
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::destroyBuilding, DAT_BuildingsState::ptr)(this->BuildingLayer[tile]);
            }
            index++;
        } while (index < this->constructionTileCount);

        index = 0;
        do {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(index, 5);
            int tile = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + y + DAT_TerrainDefinedData::instance.keepOutbuildingOffsets_0x3e4[variant][0].yOffset].addXgetTile + this->buildingX + x
                + DAT_TerrainDefinedData::instance.keepOutbuildingOffsets_0x3e4[variant][0].xOffset;
            if (this->BuildingLayer[tile] != 0) {
                this->showNoRubbleWhenDestroyingBuilding = 1;
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::destroyBuilding, DAT_BuildingsState::ptr)(this->BuildingLayer[tile]);
            }
            index++;
        } while (index < this->constructionTileCount);

        for (int buildingID = 1; buildingID < 2000; buildingID++) {
            if (DAT_BuildingsState::instance.buildings[buildingID].logicalState == OpenSHC::Map::Buildings::BLS_REMOVE) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::deleteBuilding, DAT_BuildingsState::ptr)(buildingID);
            }
        }
    }

}
}
