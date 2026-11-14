#include "../TileMapState.func.hpp"

#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_STAIRS;
    using OpenSHC::Map::LogicHelpers::L_STOCKPILEUnk;
    using OpenSHC::Map::LogicHelpers::L_WALL_OR_GATEHOUSE;

    // FUNCTION: STRONGHOLDCRUSADER 0x004FA000
    void TileMapState::determineBuildingPlacementRotation(int x, int y)
    {
        int volatile wallTileCount = 0;
        this->field_0x554944 = 128;
        this->uiBuildingRotation = 8;
        if (this->buildingPlacementFail) {
            return;
        }

        // count, per rotation, how many of its four anchor tiles carry usable wall
        int walls[4];
        for (int rotation = 0; rotation < 4; rotation++) {
            walls[rotation] = 0;
            {
                int const tileY = DAT_TerrainDefinedData::instance.field_0x1e4c[rotation * 8 + 1] + y;
                if ((uint)(DAT_TerrainDefinedData::instance.field_0x1e4c[rotation * 8 + 0] + x) <= 399
                    && (uint)tileY <= 399
                    && DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[tileY * 400
                           + DAT_TerrainDefinedData::instance.field_0x1e4c[rotation * 8 + 0] + x]
                        != 0
                    && (this->LogicLayer[DAT_ViewportRenderState::instance.translationMatrix[tileY].addXgetTile
                            + DAT_TerrainDefinedData::instance.field_0x1e4c[rotation * 8 + 0] + x]
                           & L_WALL_OR_GATEHOUSE)
                        != 0
                    && (this->LogicLayer[DAT_ViewportRenderState::instance.translationMatrix[tileY].addXgetTile
                            + DAT_TerrainDefinedData::instance.field_0x1e4c[rotation * 8 + 0] + x]
                           & (L_STOCKPILEUnk | L_STAIRS))
                        == 0) {
                    wallTileCount++;
                    walls[rotation] = 1;
                }
            }
            {
                int const tileY = DAT_TerrainDefinedData::instance.field_0x1e4c[rotation * 8 + 3] + y;
                if ((uint)(DAT_TerrainDefinedData::instance.field_0x1e4c[rotation * 8 + 2] + x) <= 399
                    && (uint)tileY <= 399
                    && DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[tileY * 400
                           + DAT_TerrainDefinedData::instance.field_0x1e4c[rotation * 8 + 2] + x]
                        != 0
                    && (this->LogicLayer[DAT_ViewportRenderState::instance.translationMatrix[tileY].addXgetTile
                            + DAT_TerrainDefinedData::instance.field_0x1e4c[rotation * 8 + 2] + x]
                           & L_WALL_OR_GATEHOUSE)
                        != 0
                    && (this->LogicLayer[DAT_ViewportRenderState::instance.translationMatrix[tileY].addXgetTile
                            + DAT_TerrainDefinedData::instance.field_0x1e4c[rotation * 8 + 2] + x]
                           & (L_STOCKPILEUnk | L_STAIRS))
                        == 0) {
                    walls[rotation] += 1;
                    wallTileCount++;
                }
            }
            {
                int const tileY = DAT_TerrainDefinedData::instance.field_0x1e4c[rotation * 8 + 5] + y;
                if ((uint)(DAT_TerrainDefinedData::instance.field_0x1e4c[rotation * 8 + 4] + x) <= 399
                    && (uint)tileY <= 399
                    && DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[tileY * 400
                           + DAT_TerrainDefinedData::instance.field_0x1e4c[rotation * 8 + 4] + x]
                        != 0
                    && (this->LogicLayer[DAT_ViewportRenderState::instance.translationMatrix[tileY].addXgetTile
                            + DAT_TerrainDefinedData::instance.field_0x1e4c[rotation * 8 + 4] + x]
                           & L_WALL_OR_GATEHOUSE)
                        != 0
                    && (this->LogicLayer[DAT_ViewportRenderState::instance.translationMatrix[tileY].addXgetTile
                            + DAT_TerrainDefinedData::instance.field_0x1e4c[rotation * 8 + 4] + x]
                           & (L_STOCKPILEUnk | L_STAIRS))
                        == 0) {
                    walls[rotation] += 1;
                    wallTileCount++;
                }
            }
            {
                int const tileY = DAT_TerrainDefinedData::instance.field_0x1e4c[rotation * 8 + 7] + y;
                if ((uint)(DAT_TerrainDefinedData::instance.field_0x1e4c[rotation * 8 + 6] + x) <= 399
                    && (uint)tileY <= 399
                    && DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[tileY * 400
                           + DAT_TerrainDefinedData::instance.field_0x1e4c[rotation * 8 + 6] + x]
                        != 0
                    && (this->LogicLayer[DAT_ViewportRenderState::instance.translationMatrix[tileY].addXgetTile
                            + DAT_TerrainDefinedData::instance.field_0x1e4c[rotation * 8 + 6] + x]
                           & L_WALL_OR_GATEHOUSE)
                        != 0
                    && (this->LogicLayer[DAT_ViewportRenderState::instance.translationMatrix[tileY].addXgetTile
                            + DAT_TerrainDefinedData::instance.field_0x1e4c[rotation * 8 + 6] + x]
                           & (L_STOCKPILEUnk | L_STAIRS))
                        == 0) {
                    walls[rotation] += 1;
                    wallTileCount++;
                }
            }
        }

        this->uiBuildingRotation = 8;
        if (walls[0] == 4 && walls[3] == 4) {
            this->uiBuildingRotation = 7;
        } else if (walls[0] == 4 && walls[1] == 4) {
            this->uiBuildingRotation = 1;
        } else if (walls[2] == 4 && walls[3] == 4) {
            this->uiBuildingRotation = 5;
        } else if (walls[2] == 4 && walls[1] == 4) {
            this->uiBuildingRotation = 3;
        } else if (walls[0] == 4) {
            this->uiBuildingRotation = 0;
        } else if (walls[1] == 4) {
            this->uiBuildingRotation = 2;
        } else if (walls[2] == 4) {
            this->uiBuildingRotation = 4;
        } else if (walls[3] == 4) {
            this->uiBuildingRotation = 6;
        }

        int relative;
        if (this->uiBuildingRotation != 8) {
            relative = this->uiBuildingRotation - this->mapOrientation;
            if (relative < 0) {
                this->field_0x554944 = (relative + 8) * 16;
                return;
            }
        } else {
            relative = 8;
        }
        this->field_0x554944 = relative * 16;
    }

}
}
