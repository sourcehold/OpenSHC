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
        // FUNCTION: STRONGHOLDCRUSADER 0x0049E510
        void PathFindingState::recomputeALGPathFindingTileMapUnk(int someMax, uint x, uint y, undefined4 param_4)
        {
            uint uVar3;
            int iVar4;
            if (x < 400 && y < 400 && *(char*)(y * 400 + 0x21aec98 + x) != '\0') {
                this->searchGeneration = this->searchGeneration + 1;
                if (32000 < this->searchGeneration) {
                    this->searchGeneration = 1;
                    MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                        160800, '\0', (void*)((int)(DAT_TileMapState::instance.WalkLayer)));
                }
                this->searchQueue.currentDistance = 1;
                this->searchQueue.readIndex = 0;
                this->searchQueue.writeIndex = 1;
                this->searchQueue.yQueue[0] = (short)y;
                this->searchQueue.xQueue[0] = (short)x;
                this->searchQueue.tilesQueue[0]
                    = DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x;
                if ((DAT_TileMapState::instance.AIInfoLayer[this->searchQueue.tilesQueue[0]] & 0xf) == 0) {
                    DAT_TileMapState::instance.CertainPathLayer[this->searchQueue.tilesQueue[0]] = 1;
                    DAT_TileMapState::instance.WalkLayer[this->searchQueue.tilesQueue[0]]
                        = (short)this->searchGeneration;
                    if (this->searchQueue.readIndex != this->searchQueue.writeIndex) {
                        while (uVar3 = this->searchQueue.tilesQueue[this->searchQueue.readIndex], uVar3 < 0x13a10) {
                            DAT_TileMapState::instance.AIInfoLayer[uVar3]
                                = DAT_TileMapState::instance.AIInfoLayer[uVar3] | (byte)param_4;
                            int sVar1 = (int)this->searchQueue.xQueue[this->searchQueue.readIndex];
                            int sVar2 = (int)this->searchQueue.yQueue[this->searchQueue.readIndex];
                            this->searchQueue.currentDistance = (int)DAT_TileMapState::instance.CertainPathLayer[uVar3];
                            if (0x13a10 < this->searchQueue.currentDistance) {
                                return;
                            }
                            if (someMax < this->searchQueue.currentDistance) {
                                return;
                            }
                            int _direction = 0;
                            do {
                                if ((DAT_TileMapState::instance.LogicLayer[uVar3] & 0x30U) == 0
                                    && ((byte)param_4 != 8
                                        || ((DAT_TileMapState::instance.LogicLayer[uVar3] & 0x6a5014b1U) == 0))
                                    && (iVar4 = DAT_TileMapState::instance.directionTranslationMatrix[sVar2][_direction]
                                            + uVar3,
                                        DAT_TileMapState::instance.WalkLayer[iVar4] != this->searchGeneration)
                                    && ((byte)param_4 == 0x80
                                        || (DAT_TileMapState::instance.AIInfoLayer[iVar4] == '\0'))) {
                                    DAT_TileMapState::instance.CertainPathLayer[iVar4]
                                        = (short)this->searchQueue.currentDistance + 1;
                                    DAT_TileMapState::instance.WalkLayer[iVar4] = (short)this->searchGeneration;
                                    this->searchQueue.xQueue[this->searchQueue.writeIndex]
                                        = DAT_TerrainDefinedData::instance
                                              .clockwiseCardinalTranslationMatrix[_direction]
                                              .short_.xOffset
                                        + sVar1;
                                    this->searchQueue.yQueue[this->searchQueue.writeIndex]
                                        = *(short*)((int)DAT_TerrainDefinedData::instance
                                                        .clockwiseCardinalTranslationMatrix
                                              + _direction * 8 + 4)
                                        + sVar2;
                                    this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = iVar4;
                                    this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                                    if (0x13a0f < this->searchQueue.writeIndex) {
                                        this->searchQueue.writeIndex = 0;
                                    }
                                }
                                if ((DAT_TileMapState::instance.LogicLayer[uVar3] & 0x30U) == 0
                                    && ((byte)param_4 != 8
                                        || ((DAT_TileMapState::instance.LogicLayer[uVar3] & 0x6a5014b1U) == 0))
                                    && (iVar4
                                        = DAT_TileMapState::instance.directionTranslationMatrix[sVar2][_direction + 1]
                                            + uVar3,
                                        DAT_TileMapState::instance.WalkLayer[iVar4] != this->searchGeneration)
                                    && ((byte)param_4 == 0x80
                                        || (DAT_TileMapState::instance.AIInfoLayer[iVar4] == '\0'))) {
                                    DAT_TileMapState::instance.CertainPathLayer[iVar4]
                                        = (short)this->searchQueue.currentDistance + 1;
                                    DAT_TileMapState::instance.WalkLayer[iVar4] = (short)this->searchGeneration;
                                    this->searchQueue.xQueue[this->searchQueue.writeIndex]
                                        = DAT_TerrainDefinedData::instance
                                              .clockwiseCardinalTranslationMatrix[_direction + 1]
                                              .short_.xOffset
                                        + sVar1;
                                    this->searchQueue.yQueue[this->searchQueue.writeIndex]
                                        = *(short*)((int)DAT_TerrainDefinedData::instance
                                                        .clockwiseCardinalTranslationMatrix
                                              + _direction * 8 + 0xc)
                                        + sVar2;
                                    this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = iVar4;
                                    this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                                    if (0x13a0f < this->searchQueue.writeIndex) {
                                        this->searchQueue.writeIndex = 0;
                                    }
                                }
                                if ((DAT_TileMapState::instance.LogicLayer[uVar3] & 0x30U) == 0
                                    && ((byte)param_4 != 8
                                        || ((DAT_TileMapState::instance.LogicLayer[uVar3] & 0x6a5014b1U) == 0))
                                    && (iVar4
                                        = DAT_TileMapState::instance.directionTranslationMatrix[sVar2][_direction + 2]
                                            + uVar3,
                                        DAT_TileMapState::instance.WalkLayer[iVar4] != this->searchGeneration
                                            && (((byte)param_4 == 0x80
                                                || (DAT_TileMapState::instance.AIInfoLayer[iVar4] == '\0'))))) {
                                    DAT_TileMapState::instance.CertainPathLayer[iVar4]
                                        = (short)this->searchQueue.currentDistance + 1;
                                    DAT_TileMapState::instance.WalkLayer[iVar4] = (short)this->searchGeneration;
                                    this->searchQueue.xQueue[this->searchQueue.writeIndex]
                                        = DAT_TerrainDefinedData::instance
                                              .clockwiseCardinalTranslationMatrix[_direction + 2]
                                              .short_.xOffset
                                        + sVar1;
                                    this->searchQueue.yQueue[this->searchQueue.writeIndex]
                                        = *(short*)((int)DAT_TerrainDefinedData::instance
                                                        .clockwiseCardinalTranslationMatrix
                                              + _direction * 8 + 0x14)
                                        + sVar2;
                                    this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = iVar4;
                                    this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                                    if (0x13a0f < this->searchQueue.writeIndex) {
                                        this->searchQueue.writeIndex = 0;
                                    }
                                }
                                if ((DAT_TileMapState::instance.LogicLayer[uVar3] & 0x30U) == 0
                                    && ((byte)param_4 != 8
                                        || ((DAT_TileMapState::instance.LogicLayer[uVar3] & 0x6a5014b1U) == 0))
                                    && (iVar4
                                        = DAT_TileMapState::instance.directionTranslationMatrix[sVar2][_direction + 3]
                                            + uVar3,
                                        DAT_TileMapState::instance.WalkLayer[iVar4] != this->searchGeneration)
                                    && ((byte)param_4 == 0x80
                                        || (DAT_TileMapState::instance.AIInfoLayer[iVar4] == '\0'))) {
                                    DAT_TileMapState::instance.CertainPathLayer[iVar4]
                                        = (short)this->searchQueue.currentDistance + 1;
                                    DAT_TileMapState::instance.WalkLayer[iVar4] = (short)this->searchGeneration;
                                    this->searchQueue.xQueue[this->searchQueue.writeIndex]
                                        = DAT_TerrainDefinedData::instance
                                              .clockwiseCardinalTranslationMatrix[_direction + 3]
                                              .short_.xOffset
                                        + sVar1;
                                    this->searchQueue.yQueue[this->searchQueue.writeIndex]
                                        = *(short*)((int)DAT_TerrainDefinedData::instance
                                                        .clockwiseCardinalTranslationMatrix
                                              + _direction * 8 + 0x1c)
                                        + sVar2;
                                    this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = iVar4;
                                    this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                                    if (0x13a0f < this->searchQueue.writeIndex) {
                                        this->searchQueue.writeIndex = 0;
                                    }
                                }
                                _direction = _direction + 4;
                            } while (_direction < 8);
                            this->searchQueue.readIndex = this->searchQueue.readIndex + 1;
                            if (0x13a0f < this->searchQueue.readIndex) {
                                this->searchQueue.readIndex = 0;
                            }
                            if (this->searchQueue.readIndex == this->searchQueue.writeIndex) {
                                return;
                            }
                        }
                    }
                }
            }
            return;
        }

    }
}
}
