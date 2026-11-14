#include "../TileMapState.func.hpp"

#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Map/Enums/MapOrientation.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L2_BEACH;
    using OpenSHC::Map::LogicHelpers::L2_OASIS_GRASS;
    using OpenSHC::Map::LogicHelpers::L2_PLATEAU_HIGH;
    using OpenSHC::Map::LogicHelpers::L2_STONES_OR_DRIVEN_SANDUnk;
    using OpenSHC::Map::LogicHelpers::L2_THICK_SCRUB;
    using OpenSHC::Map::LogicHelpers::L_RIVER;

    // FUNCTION: STRONGHOLDCRUSADER 0x004FC0B0
    void TileMapState::computeTileCliffEdgeFlags(int tile, int x, int y)
    {
        int const height = this->HeightLayer[tile];
        int lowest = height;
        int highest = height;
        if (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_MULTIPLAYER) {
            return;
        }

        // the height of each of the eight neighbours, or the own height where there is no river
        int heights[8];
        for (int i = 0; i < countof(DAT_TerrainDefinedData::instance.field_0x372c); i++) {
            XYPair offset;
            offset.x = DAT_TerrainDefinedData::instance.field_0x372c[i].x;
            offset.y = DAT_TerrainDefinedData::instance.field_0x372c[i].y;
            uint const neighbourY = offset.y + y;
            uint const neighbourX = offset.x + x;
            heights[i] = height;
            if (neighbourX > 399 || neighbourY > 399
                || DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[neighbourY * 400 + neighbourX] == 0) {
                continue;
            }
            int const neighbour
                = DAT_ViewportRenderState::instance.translationMatrix[neighbourY].addXgetTile + offset.x + x;
            if ((this->LogicLayer[neighbour] & L_RIVER) == 0) {
                continue;
            }
            heights[i] = this->HeightLayer[neighbour];
            if (heights[i] < lowest) {
                lowest = heights[i];
            } else if (heights[i] > highest) {
                highest = heights[i];
            }
        }

        this->Logic2Layer[tile] &= (L2_BEACH | L2_OASIS_GRASS | L2_PLATEAU_HIGH);
        byte const flags = this->Logic2Layer[tile];
        if (lowest < height) {
            // the bank runs along whichever axis the map is turned to (Logic2 has no names for edge bits 1, 2, 4)
            if (this->mapOrientation == OpenSHC::Map::Enums::MO_NORTH) {
                if (heights[2] < height && heights[4] < height) {
                    this->Logic2Layer[tile] = flags | 1;
                } else if (heights[4] < height) {
                    this->Logic2Layer[tile] = flags | 2;
                } else if (heights[2] < height) {
                    this->Logic2Layer[tile] = flags | 4;
                }
            } else if (this->mapOrientation == OpenSHC::Map::Enums::MO_SOUTH) {
                if (heights[0] < height && heights[6] < height) {
                    this->Logic2Layer[tile] = flags | 1;
                } else if (heights[0] < height) {
                    this->Logic2Layer[tile] = flags | 2;
                } else if (heights[6] < height) {
                    this->Logic2Layer[tile] = flags | 4;
                }
            } else if (this->mapOrientation == OpenSHC::Map::Enums::MO_EAST) {
                if (heights[4] < height && heights[6] < height) {
                    this->Logic2Layer[tile] = flags | 1;
                } else if (heights[6] < height) {
                    this->Logic2Layer[tile] = flags | 2;
                } else if (heights[4] < height) {
                    this->Logic2Layer[tile] = flags | 4;
                }
            } else if (this->mapOrientation == OpenSHC::Map::Enums::MO_WEST) {
                if (heights[0] < height && heights[2] < height) {
                    this->Logic2Layer[tile] = flags | 1;
                } else if (heights[2] < height) {
                    this->Logic2Layer[tile] = flags | 2;
                } else if (heights[0] < height) {
                    this->Logic2Layer[tile] = flags | 4;
                }
            }
        } else if (highest > height) {
            // a bank all round: low step becomes a beach, a height one a cliff
            if (highest > height + 16) {
                this->Logic2Layer[tile] = flags | L2_STONES_OR_DRIVEN_SANDUnk;
            } else {
                this->Logic2Layer[tile] = flags | L2_THICK_SCRUB;
            }
        }
    }

}
}
