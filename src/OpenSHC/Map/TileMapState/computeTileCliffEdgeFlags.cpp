#include "OpenSHC/Map/TileMapState.func.hpp"

#include "OpenSHC/Game/GameMode.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_RIVER;

    using OpenSHC::Game::GameMode;

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
    // FUNCTION: STRONGHOLDCRUSADER 0x004FC0B0
    void TileMapState::computeTileCliffEdgeFlags(int tile, int x, int y)
    {
        int height = this->HeightLayer[tile];
        if (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_MULTIPLAYER) {
            return;
        }

        /* the height of each of the eight neighbours, or this tile's own where there is no river */
        int heights[8];
        int lowest = height;
        int highest = height;
        for (int i = 0; i < 8; i++) {
            uint neighbourY = y + DAT_TerrainDefinedData::instance.field2476_0x372c[i].y;
            uint neighbourX = x + DAT_TerrainDefinedData::instance.field2476_0x372c[i].x;
            heights[i] = height;
            if (neighbourX < 400 && neighbourY < 400
                && DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[neighbourY * 400 + neighbourX] != 0) {
                int neighbour = DAT_ViewportRenderState::instance.translationMatrix[neighbourY].addXgetTile
                    + DAT_TerrainDefinedData::instance.field2476_0x372c[i].x + x;
                if ((this->LogicLayer[neighbour] & L_RIVER) != 0) {
                    heights[i] = this->HeightLayer[neighbour];
                    if (heights[i] < lowest) {
                        lowest = heights[i];
                    } else if (heights[i] > highest) {
                        highest = heights[i];
                    }
                }
            }
        }

        this->Logic2Layer[tile]
            = this->Logic2Layer[tile] & (OpenSHC::Map::LogicHelpers::L2_BEACH | OpenSHC::Map::LogicHelpers::L2_OASIS_GRASS | OpenSHC::Map::LogicHelpers::L2_PLATEAU_HIGH);
        byte flags = this->Logic2Layer[tile];
        if (lowest >= height) {
            /* a bank all round: low step becomes a beach, a high one a cliff */
            if (highest > height) {
                if (highest <= height + 0x10) {
                    flags = flags | 0x80;
                } else {
                    flags = flags | 0x40;
                }
            }
        } else if (this->mapOrientation == 4) {
            if (heights[0] >= height) {
                if (heights[6] < height) {
                    flags = flags | 4;
                }
            } else if (heights[6] < height) {
                flags = flags | 1;
            } else {
                flags = flags | 2;
            }
        } else {
            /* the bank runs along whichever axis the map is turned to */
            int along = 0;
            int across = 0;
            bool turned = true;
            if (this->mapOrientation == 0) {
                along = heights[2];
                across = heights[4];
            } else if (this->mapOrientation == 2) {
                along = heights[4];
                across = heights[6];
            } else if (this->mapOrientation == 6) {
                along = heights[0];
                across = heights[2];
            } else {
                turned = false;
            }
            if (turned) {
                if (along < height) {
                    if (across < height) {
                        flags = flags | 1;
                    } else {
                        flags = flags | 4;
                    }
                } else if (across < height) {
                    flags = flags | 2;
                }
            }
        }
        this->Logic2Layer[tile] = flags;
    }

}
}
