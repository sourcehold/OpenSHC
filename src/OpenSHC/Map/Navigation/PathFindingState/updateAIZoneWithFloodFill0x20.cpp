#include "../PathFindingState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"

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
        // FUNCTION: STRONGHOLDCRUSADER 0x0049E9E0
        void PathFindingState::updateAIZoneWithFloodFill0x20(int max, uint x, uint y)
        {
            int _candidate;
            if (x > 399 || y > 399 || DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y * 400 + x] == '\0') {
                return;
            }
            this->searchGeneration = this->searchGeneration + 1;
            if (32000 < this->searchGeneration) {
                this->searchGeneration = 1;
                MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                    0x27420, '\0', (void*)((int)(DAT_TileMapState::instance.WalkLayer)));
            }
            this->searchQueue.readIndex = 0;
            this->searchQueue.writeIndex = 1;
            this->searchQueue.currentDistance = 1;
            this->searchQueue.yQueue[0] = (short)y;
            this->searchQueue.xQueue[0] = (short)x;
            this->searchQueue.tilesQueue[0] = DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x;
            DAT_TileMapState::instance.CertainPathLayer[this->searchQueue.tilesQueue[0]] = 1;
            DAT_TileMapState::instance.WalkLayer[this->searchQueue.tilesQueue[0]] = (short)this->searchGeneration;
            if (this->searchQueue.readIndex != this->searchQueue.writeIndex) {
                do {
                    int _tile = this->searchQueue.tilesQueue[this->searchQueue.readIndex];
                    DAT_TileMapState::instance.AIInfoLayer[_tile]
                        = DAT_TileMapState::instance.AIInfoLayer[_tile] | 0x20;
                    short sVar1 = this->searchQueue.xQueue[this->searchQueue.readIndex];
                    short sVar2 = this->searchQueue.yQueue[this->searchQueue.readIndex];
                    this->searchQueue.currentDistance = (int)DAT_TileMapState::instance.CertainPathLayer[_tile];
                    if (this->searchQueue.currentDistance > max) {
                        return;
                    }
                    int iVar3 = 0;
                    do {
                        /*
                          fixme: why are there nested identical if else statements here?   shouldn't it tested the
                          edge-ness of the candidate !?
                         */
                        if ((DAT_TileMapState::instance.LogicLayer[_tile] & 0x30) == 0) {
                            _candidate = DAT_TileMapState::instance.directionTranslationMatrix[sVar2][iVar3] + _tile;
                            if (DAT_TileMapState::instance.WalkLayer[_candidate] != this->searchGeneration) {
                                DAT_TileMapState::instance.CertainPathLayer[_candidate]
                                    = (short)this->searchQueue.currentDistance + 1;
                                DAT_TileMapState::instance.WalkLayer[_candidate] = (short)this->searchGeneration;
                                this->searchQueue.xQueue[this->searchQueue.writeIndex]
                                    = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[iVar3]
                                          .short_.xOffset
                                    + sVar1;
                                this->searchQueue.yQueue[this->searchQueue.writeIndex]
                                    = *(short*)((int)DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix
                                          + iVar3 * 8 + 4)
                                    + sVar2;
                                this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = _candidate;
                                this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                                if (0x13a0f < this->searchQueue.writeIndex) {
                                    this->searchQueue.writeIndex = 0;
                                }
                            }
                            if ((DAT_TileMapState::instance.LogicLayer[_tile] & 0x30) == 0) {
                                _candidate
                                    = DAT_TileMapState::instance.directionTranslationMatrix[sVar2][iVar3 + 1] + _tile;
                                if (DAT_TileMapState::instance.WalkLayer[_candidate] != this->searchGeneration) {
                                    DAT_TileMapState::instance.CertainPathLayer[_candidate]
                                        = (short)this->searchQueue.currentDistance + 1;
                                    DAT_TileMapState::instance.WalkLayer[_candidate] = (short)this->searchGeneration;
                                    this->searchQueue.xQueue[this->searchQueue.writeIndex]
                                        = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[iVar3 + 1]
                                              .short_.xOffset
                                        + sVar1;
                                    this->searchQueue.yQueue[this->searchQueue.writeIndex]
                                        = *(short*)((int)DAT_TerrainDefinedData::instance
                                                        .clockwiseCardinalTranslationMatrix
                                              + iVar3 * 8 + 0xc)
                                        + sVar2;
                                    this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = _candidate;
                                    this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                                    if (0x13a0f < this->searchQueue.writeIndex) {
                                        this->searchQueue.writeIndex = 0;
                                    }
                                }
                                if ((DAT_TileMapState::instance.LogicLayer[_tile] & 0x30) == 0) {
                                    _candidate = DAT_TileMapState::instance.directionTranslationMatrix[sVar2][iVar3 + 2]
                                        + _tile;
                                    if (DAT_TileMapState::instance.WalkLayer[_candidate] != this->searchGeneration) {
                                        DAT_TileMapState::instance.CertainPathLayer[_candidate]
                                            = (short)this->searchQueue.currentDistance + 1;
                                        DAT_TileMapState::instance.WalkLayer[_candidate]
                                            = (short)this->searchGeneration;
                                        this->searchQueue.xQueue[this->searchQueue.writeIndex]
                                            = DAT_TerrainDefinedData::instance
                                                  .clockwiseCardinalTranslationMatrix[iVar3 + 2]
                                                  .short_.xOffset
                                            + sVar1;
                                        this->searchQueue.yQueue[this->searchQueue.writeIndex]
                                            = *(short*)((int)DAT_TerrainDefinedData::instance
                                                            .clockwiseCardinalTranslationMatrix
                                                  + iVar3 * 8 + 0x14)
                                            + sVar2;
                                        this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = _candidate;
                                        this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                                        if (0x13a0f < this->searchQueue.writeIndex) {
                                            this->searchQueue.writeIndex = 0;
                                        }
                                    }
                                    if ((DAT_TileMapState::instance.LogicLayer[_tile] & 0x30) == 0
                                        && (_candidate
                                            = DAT_TileMapState::instance.directionTranslationMatrix[sVar2][iVar3 + 3]
                                                + _tile,
                                            DAT_TileMapState::instance.WalkLayer[_candidate]
                                                != this->searchGeneration)) {
                                        DAT_TileMapState::instance.CertainPathLayer[_candidate]
                                            = (short)this->searchQueue.currentDistance + 1;
                                        DAT_TileMapState::instance.WalkLayer[_candidate]
                                            = (short)this->searchGeneration;
                                        this->searchQueue.xQueue[this->searchQueue.writeIndex]
                                            = DAT_TerrainDefinedData::instance
                                                  .clockwiseCardinalTranslationMatrix[iVar3 + 3]
                                                  .short_.xOffset
                                            + sVar1;
                                        this->searchQueue.yQueue[this->searchQueue.writeIndex]
                                            = *(short*)((int)DAT_TerrainDefinedData::instance
                                                            .clockwiseCardinalTranslationMatrix
                                                  + iVar3 * 8 + 0x1c)
                                            + sVar2;
                                        this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = _candidate;
                                        this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                                        if (0x13a0f < this->searchQueue.writeIndex) {
                                            this->searchQueue.writeIndex = 0;
                                        }
                                    }
                                }
                            }
                        }
                        iVar3 = iVar3 + 4;
                    } while (iVar3 < 8);
                    this->searchQueue.readIndex = this->searchQueue.readIndex + 1;
                    if (0x13a0f < this->searchQueue.readIndex) {
                        this->searchQueue.readIndex = 0;
                    }
                } while (this->searchQueue.readIndex != this->searchQueue.writeIndex);
            }
            return;
        }

    }
}
}
