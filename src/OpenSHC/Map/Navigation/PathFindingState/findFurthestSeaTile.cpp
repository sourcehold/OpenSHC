#include "../PathFindingState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/MapConstants.hpp"

#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        // FUNCTION: STRONGHOLDCRUSADER 0x0049BBF0
        void PathFindingState::findFurthestSeaTile(int budget, uint ySpace, uint y)
        {
            this->ALG_ResultTile = 0;
            this->ALG_ResultY = 0;
            this->ALG_ResultX = 0;
            if (ySpace > MC_MAP_XY_LIMIT_MIN_1 || y > MC_MAP_XY_LIMIT_MIN_1
                || DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y * MC_MAP_XY_LIMIT + ySpace] == 0) {
                return;
            }
            this->calculations += 1;
            this->searchGeneration += 1;
            if (PFC_SEARCH_GENERATION_LIMIT < this->searchGeneration) {
                this->searchGeneration = 1;
                MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                    sizeof(DAT_TileMapState::instance.WalkLayer), 0, &DAT_TileMapState::instance.WalkLayer[0]);
            }
            this->searchQueue.readIndex = 0;
            this->searchQueue.writeIndex = 1;
            this->searchQueue.currentDistance = 1;
            this->searchQueue.yQueue[0] = y;
            this->searchQueue.xQueue[0] = ySpace;
            this->searchQueue.tilesQueue[0]
                = DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + ySpace;
            DAT_TileMapState::instance.CertainPathLayer[this->searchQueue.tilesQueue[0]]
                = this->searchQueue.currentDistance;
            DAT_TileMapState::instance.WalkLayer[this->searchQueue.tilesQueue[0]] = this->searchGeneration;
            while (this->searchQueue.readIndex != this->searchQueue.writeIndex) {
                int _tile = this->searchQueue.tilesQueue[this->searchQueue.readIndex];
                if (_tile < 0 || _tile >= MC_MAP_TILES_COUNT) {
                    break;
                }
                int _x = this->searchQueue.xQueue[this->searchQueue.readIndex];
                int _y = this->searchQueue.yQueue[this->searchQueue.readIndex];
                this->searchQueue.currentDistance = DAT_TileMapState::instance.CertainPathLayer[_tile];
                if (this->searchQueue.writeIndex > budget) {
                    this->ALG_ResultTile = _tile;
                    this->ALG_ResultY = _y;
                    this->ALG_ResultX = _x;
                    return;
                }
                for (int _direction = 0; _direction < PFC_DIRECTIONS; _direction = _direction + 2) {
                    /*
                      for each direction, do:
                     */
                    int _candidate = DAT_TileMapState::instance.directionTranslationMatrix[_y][_direction] + _tile;
                    if (DAT_TileMapState::instance.WalkLayer[_candidate] != this->searchGeneration
                        && (DAT_TileMapState::instance.LogicLayer[_candidate] & L_SEA) != 0) {
                        DAT_TileMapState::instance.CertainPathLayer[_candidate] = this->searchQueue.currentDistance + 1;
                        DAT_TileMapState::instance.WalkLayer[_candidate] = this->searchGeneration;
                        this->searchQueue.xQueue[this->searchQueue.writeIndex]
                            = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction]
                                  .short_.xOffset
                            + _x;
                        this->searchQueue.yQueue[this->searchQueue.writeIndex]
                            = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction]
                                  .short_.yOffset
                            + _y;
                        this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = _candidate;
                        this->searchQueue.writeIndex += 1;
                        if (MC_MAP_TILES_COUNT <= this->searchQueue.writeIndex) {
                            this->searchQueue.writeIndex = 0;
                        }
                    }
                }

                this->searchQueue.readIndex += 1;
                if (MC_MAP_TILES_COUNT <= this->searchQueue.readIndex) {
                    this->searchQueue.readIndex = 0;
                }
            }
            this->ALG_ResultX = this->searchQueue.xQueue[this->searchQueue.readIndex - 1];
            this->ALG_ResultY = this->searchQueue.yQueue[this->searchQueue.readIndex - 1];
            this->ALG_ResultTile = this->searchQueue.tilesQueue[this->searchQueue.readIndex - 1];
        }

    }
}
}
