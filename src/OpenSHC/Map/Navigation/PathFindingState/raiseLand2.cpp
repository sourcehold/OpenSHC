#include "../PathFindingState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Location/Point8ShortXY.hpp"

#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {
        using OpenSHC::Map::Location::Point8ShortXY;

        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x0049A6D0
        void PathFindingState::raiseLand2(uint x, uint y, int maxDistance)
        {
            short* psVar4;
            int iVar5;
            int* piVar6;
            if (x > 399 || y > 399 || DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y * 400 + x] == '\0') {
                return;
            }
            MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                160800, '\0', (void*)((int)(DAT_TileMapState::instance.CertainPathLayer)));
            this->searchQueue.readIndex = 0;
            this->searchQueue.writeIndex = 1;
            this->searchQueue.currentDistance = 1;
            this->searchQueue.yQueue[0] = (short)y;
            this->searchQueue.xQueue[0] = (short)x;
            this->searchQueue.tilesQueue[0] = DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x;
            DAT_TileMapState::instance.CertainPathLayer[this->searchQueue.tilesQueue[0]] = 1;
            ushort uVar1 = DAT_TileMapState::instance.PathConnectionLayer[this->searchQueue.tilesQueue[0]];
            if (this->searchQueue.readIndex != this->searchQueue.writeIndex) {
                do {
                    uint tile = this->searchQueue.tilesQueue[this->searchQueue.readIndex];
                    if (0x13a0f < tile)
                        break;
                    int sVar2 = (int)this->searchQueue.xQueue[this->searchQueue.readIndex];
                    int sVar3 = (int)this->searchQueue.yQueue[this->searchQueue.readIndex];
                    this->searchQueue.currentDistance = (int)DAT_TileMapState::instance.CertainPathLayer[tile];
                    if (this->searchQueue.currentDistance > maxDistance)
                        break;
                    MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::raiseLand, DAT_TileMapState::ptr)(
                        tile, (uint)(sVar3), 4, 1);
                    psVar4 = &DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[0].short_.yOffset;
                    piVar6 = DAT_TileMapState::instance.directionTranslationMatrix[sVar3] + 1;
                    do {
                        iVar5 = (*(int (*)[8])(piVar6 + -1))[0] + tile;
                        if (DAT_TileMapState::instance.CertainPathLayer[iVar5] < 1
                            && (short)DAT_TileMapState::instance.PathConnectionLayer[iVar5] == uVar1
                            && (DAT_TileMapState::instance.LogicLayer[iVar5] & 0x30) == 0) {
                            DAT_TileMapState::instance.CertainPathLayer[iVar5]
                                = (short)this->searchQueue.currentDistance + 1;
                            this->searchQueue.xQueue[this->searchQueue.writeIndex]
                                = ((Point8ShortXY*)(psVar4 + -2))->xOffset + sVar2;
                            this->searchQueue.yQueue[this->searchQueue.writeIndex] = *psVar4 + sVar3;
                            this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = iVar5;
                            this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                            if (0x13a0f < this->searchQueue.writeIndex) {
                                this->searchQueue.writeIndex = 0;
                            }
                        }
                        iVar5 = *piVar6 + tile;
                        if (DAT_TileMapState::instance.CertainPathLayer[iVar5] < 1
                            && (short)DAT_TileMapState::instance.PathConnectionLayer[iVar5] == uVar1
                            && (DAT_TileMapState::instance.LogicLayer[iVar5] & 0x30) == 0) {
                            DAT_TileMapState::instance.CertainPathLayer[iVar5]
                                = (short)this->searchQueue.currentDistance + 1;
                            this->searchQueue.xQueue[this->searchQueue.writeIndex] = psVar4[2] + sVar2;
                            this->searchQueue.yQueue[this->searchQueue.writeIndex] = psVar4[4] + sVar3;
                            this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = iVar5;
                            this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                            if (0x13a0f < this->searchQueue.writeIndex) {
                                this->searchQueue.writeIndex = 0;
                            }
                        }
                        iVar5 = piVar6[1] + tile;
                        if (DAT_TileMapState::instance.CertainPathLayer[iVar5] < 1
                            && (short)DAT_TileMapState::instance.PathConnectionLayer[iVar5] == uVar1
                            && (DAT_TileMapState::instance.LogicLayer[iVar5] & 0x30) == 0) {
                            DAT_TileMapState::instance.CertainPathLayer[iVar5]
                                = (short)this->searchQueue.currentDistance + 1;
                            this->searchQueue.xQueue[this->searchQueue.writeIndex] = psVar4[6] + sVar2;
                            this->searchQueue.yQueue[this->searchQueue.writeIndex] = psVar4[8] + sVar3;
                            this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = iVar5;
                            this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                            if (0x13a0f < this->searchQueue.writeIndex) {
                                this->searchQueue.writeIndex = 0;
                            }
                        }
                        iVar5 = piVar6[2] + tile;
                        if (DAT_TileMapState::instance.CertainPathLayer[iVar5] < 1
                            && (short)DAT_TileMapState::instance.PathConnectionLayer[iVar5] == uVar1
                            && (DAT_TileMapState::instance.LogicLayer[iVar5] & 0x30) == 0) {
                            DAT_TileMapState::instance.CertainPathLayer[iVar5]
                                = (short)this->searchQueue.currentDistance + 1;
                            this->searchQueue.xQueue[this->searchQueue.writeIndex] = psVar4[10] + sVar2;
                            this->searchQueue.yQueue[this->searchQueue.writeIndex] = psVar4[0xc] + sVar3;
                            this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = iVar5;
                            this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                            if (0x13a0f < this->searchQueue.writeIndex) {
                                this->searchQueue.writeIndex = 0;
                            }
                        }
                        psVar4 = psVar4 + 0x10;
                        piVar6 = piVar6 + 4;
                    } while ((int)psVar4 < 0xb4908c);
                    this->searchQueue.readIndex = this->searchQueue.readIndex + 1;
                    if (0x13a0f < this->searchQueue.readIndex) {
                        this->searchQueue.readIndex = 0;
                    }
                } while (this->searchQueue.readIndex != this->searchQueue.writeIndex);
            }
            DAT_TileMapState::instance.forceUpdateLogicalAndMiscDisplayLayers = 1;
            DAT_TileMapState::instance.forceUpdateTextureTilemap = 1;
            DAT_TileMapState::instance.forceUpdateGFXLayers = 1;
            return;
        }

    }
}
}
