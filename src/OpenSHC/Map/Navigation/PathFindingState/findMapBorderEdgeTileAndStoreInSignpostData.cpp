#include "../PathFindingState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"

#include "OpenSHC/Globals/DAT_ClimbLogicDefinedData.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x0049B940
        void PathFindingState::findMapBorderEdgeTileAndStoreInSignpostData(
            int signpostID, int maxDistance, uint x, uint y)
        {
            int (*paiVar1)[8];
            int _candidate;
            int _offset;
            int _index;
            uint _tile;
            int _x;
            int _y;
            DAT_GameState::instance.mapAndTime.signpostsMapEdgeDataCounter = 0;
            this->calculations = this->calculations + 1;
            this->resultTile = 0;
            this->resultY = 0;
            this->resultX = 0;
            if (x > 399 || y > 399 || DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y * 400 + x] == '\0') {
                return;
            }
            this->searchGeneration = this->searchGeneration + 1;
            if (32000 < this->searchGeneration) {
                this->searchGeneration = 1;
                MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                    0x27420, '\0', (void*)((int)(DAT_TileMapState::instance.WalkLayer)));
            }
            this->searchQueue.currentDistance = 1;
            this->searchQueue.writeIndex = 1;
            this->searchQueue.readIndex = 0;
            this->searchQueue.yQueue[0] = (short)y;
            this->searchQueue.xQueue[0] = (short)x;
            this->searchQueue.tilesQueue[0] = DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x;
            DAT_TileMapState::instance.CertainPathLayer[this->searchQueue.tilesQueue[0]] = 1;
            DAT_TileMapState::instance.WalkLayer[this->searchQueue.tilesQueue[0]] = (short)this->searchGeneration;
            if (this->searchQueue.readIndex != this->searchQueue.writeIndex) {
                while (_tile = this->searchQueue.tilesQueue[this->searchQueue.readIndex], _tile < 80399) {
                    _x = (int)this->searchQueue.xQueue[this->searchQueue.readIndex];
                    _y = (int)this->searchQueue.yQueue[this->searchQueue.readIndex];
                    this->searchQueue.currentDistance = (int)DAT_TileMapState::instance.CertainPathLayer[_tile];
                    if (this->searchQueue.currentDistance > maxDistance) {
                        return;
                    }
                    _index = 0;
                    paiVar1 = DAT_TileMapState::instance.directionTranslationMatrix + _y;
                    do {
                        /*
                          for each direction, do
                         */
                        _candidate = (*paiVar1)[0] + _tile;
                        if (DAT_TileMapState::instance.WalkLayer[_candidate] != this->searchGeneration) {
                            /*
                              reached map border edge?
                             */
                            if ((DAT_TileMapState::instance.LogicLayer[_candidate] & 0x30) != 0) {
                                this->resultX = (int)_x;
                                this->resultY = (int)_y;
                                this->resultTile = _tile;
                                DAT_GameState::instance.mapAndTime
                                    .signpostsMapEdge[signpostID]
                                                     [DAT_GameState::instance.mapAndTime.signpostsMapEdgeDataCounter]
                                    .x = (int)_x;
                                DAT_GameState::instance.mapAndTime
                                    .signpostsMapEdge[signpostID]
                                                     [DAT_GameState::instance.mapAndTime.signpostsMapEdgeDataCounter]
                                    .y = this->resultY;
                                DAT_GameState::instance.mapAndTime
                                    .signpostsMapEdge[signpostID]
                                                     [DAT_GameState::instance.mapAndTime.signpostsMapEdgeDataCounter]
                                    .tile = this->resultTile;
                                DAT_GameState::instance.mapAndTime.signpostsMapEdgeDataCounter
                                    = DAT_GameState::instance.mapAndTime.signpostsMapEdgeDataCounter + 1;
                                if (50 < DAT_GameState::instance.mapAndTime.signpostsMapEdgeDataCounter) {
                                    return;
                                }
                                break;
                            }
                            if ((DAT_TileMapState::instance.PathLinkageLayer[_tile]
                                    & DAT_ClimbLogicDefinedData::instance.BitFlagHelperForPathLinkage[_index])
                                != 0) {
                                /*
                                  this direction can be walked to? add to queue
                                 */
                                DAT_TileMapState::instance.CertainPathLayer[_candidate]
                                    = (short)this->searchQueue.currentDistance + 1;
                                DAT_TileMapState::instance.WalkLayer[_candidate] = (short)this->searchGeneration;
                                this->searchQueue.xQueue[this->searchQueue.writeIndex]
                                    = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_index]
                                          .short_.xOffset
                                    + _x;
                                this->searchQueue.yQueue[this->searchQueue.writeIndex]
                                    = *(short*)((int)DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix
                                          + _index * 8 + 4)
                                    + _y;
                                this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = _candidate;
                                this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                                if (0x13a0f < this->searchQueue.writeIndex) {
                                    this->searchQueue.writeIndex = 0;
                                }
                            }
                        }
                        _index = _index + 2;
                        paiVar1 = (int (*)[8])(*paiVar1 + 2);
                    } while (_index < 8);
                    this->searchQueue.readIndex = this->searchQueue.readIndex + 1;
                    if (0x13a0f < this->searchQueue.readIndex) {
                        this->searchQueue.readIndex = 0;
                    }
                    if (this->searchQueue.readIndex == this->searchQueue.writeIndex) {
                        return;
                    }
                }
            }
            return;
        }

    }
}
}
