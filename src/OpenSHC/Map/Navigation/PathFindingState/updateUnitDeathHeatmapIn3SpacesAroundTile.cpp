#include "../PathFindingState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"

#include "OpenSHC/Globals/DAT_ClimbLogicDefinedData.hpp"
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
        // FUNCTION: STRONGHOLDCRUSADER 0x0049E0D0
        void PathFindingState::updateUnitDeathHeatmapIn3SpacesAroundTile(uint x, uint y)
        {
            int _candidate1;
            uint _tile;
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
                while (_tile = this->searchQueue.tilesQueue[this->searchQueue.readIndex], _tile < 0x13a10) {
                    int _x = (int)this->searchQueue.xQueue[this->searchQueue.readIndex];
                    int _y = (int)this->searchQueue.yQueue[this->searchQueue.readIndex];
                    int iVar2 = (int)DAT_TileMapState::instance.CertainPathLayer[_tile];
                    if (80400 < iVar2) {
                        this->searchQueue.currentDistance = iVar2;
                        return;
                    }
                    if (3 < iVar2) {
                        this->searchQueue.currentDistance = iVar2;
                        return;
                    }
                    this->searchQueue.currentDistance = iVar2;
                    if (DAT_TileMapState::instance.unitDeathHeatMap[_tile] < 250) {
                        this->searchQueue.currentDistance = (char)DAT_TileMapState::instance.CertainPathLayer[_tile];
                        char cVar1 = DAT_TileMapState::instance.unitDeathHeatMap[_tile]
                            - (char)this->searchQueue.currentDistance;
                        DAT_TileMapState::instance.unitDeathHeatMap[_tile] = cVar1 + 4;
                    }
                    for (int _direction = 0; _direction < 8; _direction = _direction + 4) {
                        if ((DAT_TileMapState::instance.PathLinkageLayer[_tile]
                                & DAT_ClimbLogicDefinedData::instance.BitFlagHelperForPathLinkage[_direction])
                                != 0
                            && (_candidate1
                                = DAT_TileMapState::instance.directionTranslationMatrix[_y][_direction] + _tile,
                                DAT_TileMapState::instance.WalkLayer[_candidate1] != this->searchGeneration)) {
                            /*
                              queue tiles walkable in that direction
                             */
                            DAT_TileMapState::instance.CertainPathLayer[_candidate1]
                                = (short)this->searchQueue.currentDistance + 1;
                            DAT_TileMapState::instance.WalkLayer[_candidate1] = (short)this->searchGeneration;
                            this->searchQueue.xQueue[this->searchQueue.writeIndex]
                                = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction]
                                      .short_.xOffset
                                + _x;
                            this->searchQueue.yQueue[this->searchQueue.writeIndex]
                                = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction]
                                      .short_.yOffset
                                + _y;
                            this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = _candidate1;
                            this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                            if (0x13a10 <= this->searchQueue.writeIndex) {
                                this->searchQueue.writeIndex = 0;
                            }
                        }
                        if ((DAT_TileMapState::instance.PathLinkageLayer[_tile]
                                & DAT_ClimbLogicDefinedData::instance.BitFlagHelperForPathLinkage[_direction + 1])
                                != 0
                            && (iVar2
                                = DAT_TileMapState::instance.directionTranslationMatrix[_y][_direction + 1] + _tile,
                                DAT_TileMapState::instance.WalkLayer[iVar2] != this->searchGeneration)) {
                            DAT_TileMapState::instance.CertainPathLayer[iVar2]
                                = (short)this->searchQueue.currentDistance + 1;
                            DAT_TileMapState::instance.WalkLayer[iVar2] = (short)this->searchGeneration;
                            this->searchQueue.xQueue[this->searchQueue.writeIndex]
                                = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction + 1]
                                      .short_.xOffset
                                + _x;
                            this->searchQueue.yQueue[this->searchQueue.writeIndex]
                                = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction + 1]
                                      .short_.yOffset
                                + _y;
                            this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = iVar2;
                            this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                            if (0x13a10 <= this->searchQueue.writeIndex) {
                                this->searchQueue.writeIndex = 0;
                            }
                        }
                        if ((DAT_TileMapState::instance.PathLinkageLayer[_tile]
                                & DAT_ClimbLogicDefinedData::instance.BitFlagHelperForPathLinkage[_direction + 2])
                                != 0
                            && (iVar2
                                = DAT_TileMapState::instance.directionTranslationMatrix[_y][_direction + 2] + _tile,
                                DAT_TileMapState::instance.WalkLayer[iVar2] != this->searchGeneration)) {
                            DAT_TileMapState::instance.CertainPathLayer[iVar2]
                                = (short)this->searchQueue.currentDistance + 1;
                            DAT_TileMapState::instance.WalkLayer[iVar2] = (short)this->searchGeneration;
                            this->searchQueue.xQueue[this->searchQueue.writeIndex]
                                = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction + 2]
                                      .short_.xOffset
                                + _x;
                            this->searchQueue.yQueue[this->searchQueue.writeIndex]
                                = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction + 2]
                                      .short_.yOffset
                                + _y;
                            this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = iVar2;
                            this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                            if (0x13a10 <= this->searchQueue.writeIndex) {
                                this->searchQueue.writeIndex = 0;
                            }
                        }
                        if ((DAT_TileMapState::instance.PathLinkageLayer[_tile]
                                & DAT_ClimbLogicDefinedData::instance.BitFlagHelperForPathLinkage[_direction + 3])
                                != 0
                            && (iVar2
                                = DAT_TileMapState::instance.directionTranslationMatrix[_y][_direction + 3] + _tile,
                                DAT_TileMapState::instance.WalkLayer[iVar2] != this->searchGeneration)) {
                            DAT_TileMapState::instance.CertainPathLayer[iVar2]
                                = (short)this->searchQueue.currentDistance + 1;
                            DAT_TileMapState::instance.WalkLayer[iVar2] = (short)this->searchGeneration;
                            this->searchQueue.xQueue[this->searchQueue.writeIndex]
                                = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction + 3]
                                      .short_.xOffset
                                + _x;
                            this->searchQueue.yQueue[this->searchQueue.writeIndex]
                                = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction + 3]
                                      .short_.yOffset
                                + _y;
                            this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = iVar2;
                            this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                            if (0x13a10 <= this->searchQueue.writeIndex) {
                                this->searchQueue.writeIndex = 0;
                            }
                        }
                    }
                    this->searchQueue.readIndex = this->searchQueue.readIndex + 1;
                    if (0x13a10 <= this->searchQueue.readIndex) {
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
