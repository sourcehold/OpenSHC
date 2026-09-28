#include "../PathFindingState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
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
        // FUNCTION: STRONGHOLDCRUSADER 0x0049AAD0
        void PathFindingState::updateWalkAndPathLayer(int param_1, uint xPosition, uint yPosition)
        {
            short* psVar6;
            int* piVar7;
            int iVar8;
            if (xPosition < 400 && yPosition < 400 && DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[yPosition * 400 + xPosition] != '\0') {
                this->searchGeneration = this->searchGeneration + 1;
                if (32000 < this->searchGeneration) {
                    this->searchGeneration = 1;
                    MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                        160800, '\0', (void*)((int)(DAT_TileMapState::instance.WalkLayer)));
                }
                this->searchQueue.readIndex = 0;
                this->searchQueue.writeIndex = 1;
                this->searchQueue.currentDistance = 1;
                this->searchQueue.yQueue[0] = (short)yPosition;
                this->searchQueue.xQueue[0] = (short)xPosition;
                this->searchQueue.tilesQueue[0]
                    = DAT_ViewportRenderState::instance.translationMatrix[yPosition].addXgetTile + xPosition;
                DAT_TileMapState::instance.CertainPathLayer[this->searchQueue.tilesQueue[0]] = 1;
                DAT_TileMapState::instance.WalkLayer[this->searchQueue.tilesQueue[0]] = (short)this->searchGeneration;
                if (this->searchQueue.readIndex != this->searchQueue.writeIndex) {
                    do {
                        uint uVar3 = this->searchQueue.tilesQueue[this->searchQueue.readIndex];
                        if (0x13a0f < uVar3)
                            break;
                        int sVar1 = (int)this->searchQueue.yQueue[this->searchQueue.readIndex];
                        iVar8 = (int)sVar1;
                        int sVar2 = (int)this->searchQueue.xQueue[this->searchQueue.readIndex];
                        if (iVar8 < this->mappingYRelated) {
                            this->mappingYRelated = iVar8;
                        }
                        if (this->yLimit < iVar8) {
                            this->yLimit = iVar8;
                        }
                        int iVar4 = (int)sVar2 / 10;
                        int iVar5 = iVar8 / 10;
                        *(undefined1*)(iVar4 + 0x1f93438 + iVar5 * 0x28) = 2;
                        if (iVar4 < DAT_TileMapState::instance.someYLike) {
                            DAT_TileMapState::instance.someYLike = iVar4;
                        }
                        if (DAT_TileMapState::instance.someYLikeLimit < iVar4) {
                            DAT_TileMapState::instance.someYLikeLimit = iVar4;
                        }
                        if (iVar5 < DAT_TileMapState::instance.someIndex) {
                            DAT_TileMapState::instance.someIndex = iVar5;
                        }
                        if (DAT_TileMapState::instance.someLimit < iVar5) {
                            DAT_TileMapState::instance.someLimit = iVar5;
                        }
                        this->searchQueue.currentDistance = (int)DAT_TileMapState::instance.CertainPathLayer[uVar3];
                        if (param_1 < this->searchQueue.currentDistance)
                            break;
                        piVar7 = DAT_TileMapState::instance.directionTranslationMatrix[iVar8] + 1;
                        DAT_TileMapState::instance.ChangedLayer[uVar3] = 2;
                        psVar6 = &DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[0].short_.yOffset;
                        do {
                            iVar8 = (*(int (*)[8])(piVar7 + -1))[0] + uVar3;
                            if (DAT_TileMapState::instance.WalkLayer[iVar8] != this->searchGeneration
                                && (DAT_TileMapState::instance.LogicLayer[iVar8] & 0x30) == 0) {
                                DAT_TileMapState::instance.CertainPathLayer[iVar8]
                                    = (short)this->searchQueue.currentDistance + 1;
                                DAT_TileMapState::instance.WalkLayer[iVar8] = (short)this->searchGeneration;
                                this->searchQueue.xQueue[this->searchQueue.writeIndex]
                                    = ((Point8ShortXY*)(psVar6 + -2))->xOffset + sVar2;
                                this->searchQueue.yQueue[this->searchQueue.writeIndex] = *psVar6 + sVar1;
                                this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = iVar8;
                                this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                                if (80400 < this->searchQueue.writeIndex) {
                                    this->searchQueue.writeIndex = 0;
                                }
                            }
                            iVar8 = *piVar7 + uVar3;
                            if (DAT_TileMapState::instance.WalkLayer[iVar8] != this->searchGeneration
                                && (DAT_TileMapState::instance.LogicLayer[iVar8] & 0x30) == 0) {
                                DAT_TileMapState::instance.CertainPathLayer[iVar8]
                                    = (short)this->searchQueue.currentDistance + 1;
                                DAT_TileMapState::instance.WalkLayer[iVar8] = (short)this->searchGeneration;
                                this->searchQueue.xQueue[this->searchQueue.writeIndex] = psVar6[2] + sVar2;
                                this->searchQueue.yQueue[this->searchQueue.writeIndex] = psVar6[4] + sVar1;
                                this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = iVar8;
                                this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                                if (0x13a0f < this->searchQueue.writeIndex) {
                                    this->searchQueue.writeIndex = 0;
                                }
                            }
                            iVar8 = piVar7[1] + uVar3;
                            if (DAT_TileMapState::instance.WalkLayer[iVar8] != this->searchGeneration
                                && (DAT_TileMapState::instance.LogicLayer[iVar8] & 0x30) == 0) {
                                DAT_TileMapState::instance.CertainPathLayer[iVar8]
                                    = (short)this->searchQueue.currentDistance + 1;
                                DAT_TileMapState::instance.WalkLayer[iVar8] = (short)this->searchGeneration;
                                this->searchQueue.xQueue[this->searchQueue.writeIndex] = psVar6[6] + sVar2;
                                this->searchQueue.yQueue[this->searchQueue.writeIndex] = psVar6[8] + sVar1;
                                this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = iVar8;
                                this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                                if (0x13a0f < this->searchQueue.writeIndex) {
                                    this->searchQueue.writeIndex = 0;
                                }
                            }
                            iVar8 = piVar7[2] + uVar3;
                            if (DAT_TileMapState::instance.WalkLayer[iVar8] != this->searchGeneration
                                && (DAT_TileMapState::instance.LogicLayer[iVar8] & 0x30) == 0) {
                                DAT_TileMapState::instance.CertainPathLayer[iVar8]
                                    = (short)this->searchQueue.currentDistance + 1;
                                DAT_TileMapState::instance.WalkLayer[iVar8] = (short)this->searchGeneration;
                                this->searchQueue.xQueue[this->searchQueue.writeIndex] = psVar6[10] + sVar2;
                                this->searchQueue.yQueue[this->searchQueue.writeIndex] = psVar6[0xc] + sVar1;
                                this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = iVar8;
                                this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                                if (0x13a0f < this->searchQueue.writeIndex) {
                                    this->searchQueue.writeIndex = 0;
                                }
                            }
                            piVar7 = piVar7 + 4;
                            psVar6 = psVar6 + 0x10;
                        } while ((int)psVar6 < 0xb4908c);
                        this->searchQueue.readIndex = this->searchQueue.readIndex + 1;
                        if (0x13a0f < this->searchQueue.readIndex) {
                            this->searchQueue.readIndex = 0;
                        }
                    } while (this->searchQueue.readIndex != this->searchQueue.writeIndex);
                }
                DAT_TileMapState::instance.forceUpdateLogicalAndMiscDisplayLayers = 1;
                DAT_TileMapState::instance.forceUpdateTextureTilemap = 1;
                DAT_TileMapState::instance.forceUpdateGFXLayers = 1;
            }
            return;
        }

    }
}
}
