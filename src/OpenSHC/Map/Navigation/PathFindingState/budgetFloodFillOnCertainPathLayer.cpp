#include "../PathFindingState.func.hpp"

#include "OpenSHC/Map/Location/Point8IntXY.hpp"

#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {
        using OpenSHC::Map::Location::Point8IntXY;

        // FUNCTION: STRONGHOLDCRUSADER 0x0049DDC0
        void PathFindingState::budgetFloodFillOnCertainPathLayer(uint x, uint y, int marker, int budget)
        {
            int readIndex = 0;
            int writeIndex = 1;
            if (x > 399 || y > 399 || DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y * 400 + x] == 0) {
                return;
            }
            this->DAT_Mini_spreads = this->DAT_Mini_spreads + 1;
            uint ys[1000];
            uint xs[1000];
            uint tilesQueue[1000];
            ys[0] = y;
            xs[0] = x;
            tilesQueue[0] = DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x;
            do {
                uint const tile = tilesQueue[readIndex];
                if (tile > 0x13a0f) {
                    return;
                }
                if (writeIndex >= budget) {
                    return;
                }
                if (writeIndex >= 999) {
                    return;
                }
                x = xs[readIndex];
                y = ys[readIndex];
                DAT_TileMapState::instance.CertainPathLayer[tile] = (short)marker;
                for (int direction = 0; direction < 8; ++direction) {
                    uint const candidate = DAT_TileMapState::instance.directionTranslationMatrix[y][direction] + tile;
                    if (DAT_TileMapState::instance.WalkLayer[candidate] != this->searchGeneration) {
                        budget = budget - 1;
                        continue;
                    }
                    short const certainPath = DAT_TileMapState::instance.CertainPathLayer[candidate];
                    if (certainPath == marker) {
                        budget = budget - 1;
                    } else if (certainPath > 0) {
                        tilesQueue[writeIndex] = candidate;
                        xs[writeIndex] = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[direction]
                                             .int_.xOffset
                            + x;
                        ys[writeIndex] = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[direction]
                                             .int_.yOffset
                            + y;
                        writeIndex = writeIndex + 1;
                        DAT_TileMapState::instance.CertainPathLayer[candidate] = (short)marker;
                        if (writeIndex >= 1000) {
                            writeIndex = 0;
                        }
                    }
                }
                readIndex = readIndex + 1;
                if (readIndex >= 1000) {
                    readIndex = 0;
                }
            } while (readIndex != writeIndex);
        }

    }
}
}
