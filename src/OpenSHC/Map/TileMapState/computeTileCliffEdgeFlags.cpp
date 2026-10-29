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
    void TileMapState::computeTileCliffEdgeFlags(int tileUnk, int x, int y)
    {
        int high = this->HeightLayer[tileUnk];
        int lowest = high;
        int highest = high;
        if (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_MULTIPLAYER) {
            return;
        }

        /* the high of each of the eight neighbours, or the own high where there is no river */
        int heights[8];
        for (int i = 0; i < 8; i++) {
            uint neighbourY = y + DAT_TerrainDefinedData::instance.field2345_0x372c[i].y;
            uint neighbourX = x + DAT_TerrainDefinedData::instance.field2345_0x372c[i].x;
            heights[i] = high;
            if (neighbourX <= 399 && neighbourY <= 399
                && DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[neighbourY * 400 + neighbourX] != 0) {
                int neighbour = DAT_ViewportRenderState::instance.translationMatrix[neighbourY].addXgetTile
                    + DAT_TerrainDefinedData::instance.field2345_0x372c[i].x + x;
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

        this->Logic2Layer[tileUnk]
            = this->Logic2Layer[tileUnk] & (OpenSHC::Map::LogicHelpers::L2_BEACH | OpenSHC::Map::LogicHelpers::L2_OASIS_GRASS | OpenSHC::Map::LogicHelpers::L2_PLATEAU_HIGH);
        byte flags = this->Logic2Layer[tileUnk];
        if (lowest < high) {
            /* the bank runs along whichever axis the map is turned to */
            if (this->mapOrientation == 0) {
                if (heights[2] < high && heights[4] < high) {
                    this->Logic2Layer[tileUnk] = flags | 1;
                } else if (heights[4] < high) {
                    this->Logic2Layer[tileUnk] = flags | 2;
                } else if (heights[2] < high) {
                    this->Logic2Layer[tileUnk] = flags | 4;
                }
            } else if (this->mapOrientation == 4) {
                if (heights[0] < high) {
                    if (heights[6] < high) {
                        this->Logic2Layer[tileUnk] = flags | 1;
                    } else {
                        this->Logic2Layer[tileUnk] = flags | 2;
                    }
                } else if (heights[6] < high) {
                    this->Logic2Layer[tileUnk] = flags | 4;
                }
            } else if (this->mapOrientation == 2) {
                if (heights[4] < high && heights[6] < high) {
                    this->Logic2Layer[tileUnk] = flags | 1;
                } else if (heights[6] < high) {
                    this->Logic2Layer[tileUnk] = flags | 2;
                } else if (heights[4] < high) {
                    this->Logic2Layer[tileUnk] = flags | 4;
                }
            } else if (this->mapOrientation == 6) {
                if (heights[0] < high && heights[2] < high) {
                    this->Logic2Layer[tileUnk] = flags | 1;
                } else if (heights[2] < high) {
                    this->Logic2Layer[tileUnk] = flags | 2;
                } else if (heights[0] < high) {
                    this->Logic2Layer[tileUnk] = flags | 4;
                }
            }
        } else if (highest > high) {
            /* a bank all round: low step becomes a beach, a high one a cliff */
            if (highest > high + 0x10) {
                this->Logic2Layer[tileUnk] = flags | 0x40;
            } else {
                this->Logic2Layer[tileUnk] = flags | 0x80;
            }
        }
    }

}
}
