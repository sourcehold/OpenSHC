#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_STAIRS;
    using OpenSHC::Map::LogicHelpers::L_STOCKPILEUnk;
    using OpenSHC::Map::LogicHelpers::L_WALL_OR_GATEHOUSE;

    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004FA000
    void TileMapState::determineBuildingPlacementRotation(int x, int y)
    {
        if (this->buildingPlacementFail != FALSE) {
            this->uiBuildingRotation = 8;
            this->field127_0x554944 = 0x80;
            return;
        }

        /* count, per rotation, how many of its four anchor tiles carry usable wall */
        int walls[4];
        for (int rotation = 0; rotation < 4; rotation++) {
            walls[rotation] = 0;
            if ((uint)(DAT_TerrainDefinedData::instance.field2465_0x1e4c[rotation * 8 + 0] + x) <= 399
                && (uint)(DAT_TerrainDefinedData::instance.field2465_0x1e4c[rotation * 8 + 1] + y) <= 399
                && DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[(DAT_TerrainDefinedData::instance.field2465_0x1e4c[rotation * 8 + 1] + y) * 400
                    + DAT_TerrainDefinedData::instance.field2465_0x1e4c[rotation * 8 + 0] + x]
                    != 0
                && (this->LogicLayer[DAT_ViewportRenderState::instance
                                         .translationMatrix[DAT_TerrainDefinedData::instance.field2465_0x1e4c[rotation * 8 + 1] + y]
                                         .addXgetTile
                       + DAT_TerrainDefinedData::instance.field2465_0x1e4c[rotation * 8 + 0] + x]
                       & L_WALL_OR_GATEHOUSE)
                    != 0
                && (this->LogicLayer[DAT_ViewportRenderState::instance
                                         .translationMatrix[DAT_TerrainDefinedData::instance.field2465_0x1e4c[rotation * 8 + 1] + y]
                                         .addXgetTile
                       + DAT_TerrainDefinedData::instance.field2465_0x1e4c[rotation * 8 + 0] + x]
                       & (L_STOCKPILEUnk | L_STAIRS))
                    == 0) {
                walls[rotation] = 1;
            }
            if ((uint)(DAT_TerrainDefinedData::instance.field2465_0x1e4c[rotation * 8 + 2] + x) <= 399
                && (uint)(DAT_TerrainDefinedData::instance.field2465_0x1e4c[rotation * 8 + 3] + y) <= 399
                && DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[(DAT_TerrainDefinedData::instance.field2465_0x1e4c[rotation * 8 + 3] + y) * 400
                    + DAT_TerrainDefinedData::instance.field2465_0x1e4c[rotation * 8 + 2] + x]
                    != 0
                && (this->LogicLayer[DAT_ViewportRenderState::instance
                                         .translationMatrix[DAT_TerrainDefinedData::instance.field2465_0x1e4c[rotation * 8 + 3] + y]
                                         .addXgetTile
                       + DAT_TerrainDefinedData::instance.field2465_0x1e4c[rotation * 8 + 2] + x]
                       & L_WALL_OR_GATEHOUSE)
                    != 0
                && (this->LogicLayer[DAT_ViewportRenderState::instance
                                         .translationMatrix[DAT_TerrainDefinedData::instance.field2465_0x1e4c[rotation * 8 + 3] + y]
                                         .addXgetTile
                       + DAT_TerrainDefinedData::instance.field2465_0x1e4c[rotation * 8 + 2] + x]
                       & (L_STOCKPILEUnk | L_STAIRS))
                    == 0) {
                walls[rotation] = walls[rotation] + 1;
            }
            if ((uint)(DAT_TerrainDefinedData::instance.field2465_0x1e4c[rotation * 8 + 4] + x) <= 399
                && (uint)(DAT_TerrainDefinedData::instance.field2465_0x1e4c[rotation * 8 + 5] + y) <= 399
                && DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[(DAT_TerrainDefinedData::instance.field2465_0x1e4c[rotation * 8 + 5] + y) * 400
                    + DAT_TerrainDefinedData::instance.field2465_0x1e4c[rotation * 8 + 4] + x]
                    != 0
                && (this->LogicLayer[DAT_ViewportRenderState::instance
                                         .translationMatrix[DAT_TerrainDefinedData::instance.field2465_0x1e4c[rotation * 8 + 5] + y]
                                         .addXgetTile
                       + DAT_TerrainDefinedData::instance.field2465_0x1e4c[rotation * 8 + 4] + x]
                       & L_WALL_OR_GATEHOUSE)
                    != 0
                && (this->LogicLayer[DAT_ViewportRenderState::instance
                                         .translationMatrix[DAT_TerrainDefinedData::instance.field2465_0x1e4c[rotation * 8 + 5] + y]
                                         .addXgetTile
                       + DAT_TerrainDefinedData::instance.field2465_0x1e4c[rotation * 8 + 4] + x]
                       & (L_STOCKPILEUnk | L_STAIRS))
                    == 0) {
                walls[rotation] = walls[rotation] + 1;
            }
            if ((uint)(DAT_TerrainDefinedData::instance.field2465_0x1e4c[rotation * 8 + 6] + x) <= 399
                && (uint)(DAT_TerrainDefinedData::instance.field2465_0x1e4c[rotation * 8 + 7] + y) <= 399
                && DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[(DAT_TerrainDefinedData::instance.field2465_0x1e4c[rotation * 8 + 7] + y) * 400
                    + DAT_TerrainDefinedData::instance.field2465_0x1e4c[rotation * 8 + 6] + x]
                    != 0
                && (this->LogicLayer[DAT_ViewportRenderState::instance
                                         .translationMatrix[DAT_TerrainDefinedData::instance.field2465_0x1e4c[rotation * 8 + 7] + y]
                                         .addXgetTile
                       + DAT_TerrainDefinedData::instance.field2465_0x1e4c[rotation * 8 + 6] + x]
                       & L_WALL_OR_GATEHOUSE)
                    != 0
                && (this->LogicLayer[DAT_ViewportRenderState::instance
                                         .translationMatrix[DAT_TerrainDefinedData::instance.field2465_0x1e4c[rotation * 8 + 7] + y]
                                         .addXgetTile
                       + DAT_TerrainDefinedData::instance.field2465_0x1e4c[rotation * 8 + 6] + x]
                       & (L_STOCKPILEUnk | L_STAIRS))
                    == 0) {
                walls[rotation] = walls[rotation] + 1;
            }
        }

        bool decided = false;
        if (walls[0] == 4) {
            if (walls[3] == 4) {
                this->uiBuildingRotation = 7;
                decided = true;
            } else if (walls[1] == 4) {
                this->uiBuildingRotation = 1;
                decided = true;
            }
        }
        if (!decided && walls[2] == 4) {
            if (walls[3] == 4) {
                this->uiBuildingRotation = 5;
                decided = true;
            } else if (walls[1] == 4) {
                this->uiBuildingRotation = 3;
                decided = true;
            }
        }
        if (!decided) {
            if (walls[0] == 4) {
                this->uiBuildingRotation = 0;
            } else if (walls[1] == 4) {
                this->uiBuildingRotation = 2;
            } else if (walls[2] == 4) {
                this->uiBuildingRotation = 4;
            } else if (walls[3] == 4) {
                this->uiBuildingRotation = 6;
            } else {
                this->uiBuildingRotation = 8;
            }
        }

        int relative;
        if (this->uiBuildingRotation == 8) {
            relative = 8;
        } else {
            relative = this->uiBuildingRotation - this->mapOrientation;
            if (relative < 0) {
                this->field127_0x554944 = (relative + 8) * 0x10;
                return;
            }
        }
        this->field127_0x554944 = relative << 4;
    }

}
}
