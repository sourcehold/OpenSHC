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
          Executes a flood file with logic layer 0x10 to indicate impenetrable land   decompilerscript: committed:
          2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004A0E50
        void PathFindingState::setWalkabilityBorderLogicLayerForSmallerMapSizes()
        {
            short sVar3;
            short* psVar5;
            int* piVar6;
            int _candidateTile;
            this->searchGeneration = this->searchGeneration + 1;
            this->resultTile = 0;
            this->resultY = 0;
            this->resultX = 0;
            if (32000 < this->searchGeneration) {
                this->searchGeneration = 1;
                MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                    160800, '\0', (void*)((int)(DAT_TileMapState::instance.WalkLayer)));
            }
            this->searchQueue.readIndex = 0;
            this->searchQueue.writeIndex = 1;
            this->searchQueue.currentDistance = 1;
            this->searchQueue.yQueue[0] = 2;
            this->searchQueue.xQueue[0] = 198;
            this->searchQueue.tilesQueue[0] = DAT_ViewportRenderState::instance.translationMatrix[2].addXgetTile + 0xc6;
            DAT_TileMapState::instance
                .CertainPathLayer[DAT_ViewportRenderState::instance.translationMatrix[2].addXgetTile + 0xc6] = 1;
            DAT_TileMapState::instance.WalkLayer[this->searchQueue.tilesQueue[0]] = (short)this->searchGeneration;
            if (this->searchQueue.readIndex != this->searchQueue.writeIndex) {
                do {
                    uint uVar4 = this->searchQueue.tilesQueue[this->searchQueue.readIndex];
                    if (0x13a0f < uVar4) {
                        return;
                    }
                    int sVar1 = (int)this->searchQueue.yQueue[this->searchQueue.readIndex];
                    int sVar2 = (int)this->searchQueue.xQueue[this->searchQueue.readIndex];
                    this->searchQueue.currentDistance = (int)DAT_TileMapState::instance.CertainPathLayer[uVar4];
                    piVar6 = DAT_TileMapState::instance.directionTranslationMatrix[sVar1] + 1;
                    psVar5 = &DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[0].short_.yOffset;
                    do {
                        _candidateTile = (*(int (*)[8])(piVar6 + -1))[0] + uVar4;
                        if (DAT_TileMapState::instance.WalkLayer[_candidateTile] != this->searchGeneration
                            && (DAT_TileMapState::instance.LogicLayer[_candidateTile] & 0x30) == 0) {
                            DAT_TileMapState::instance.CertainPathLayer[_candidateTile]
                                = (short)this->searchQueue.currentDistance + 1;
                            DAT_TileMapState::instance.WalkLayer[_candidateTile] = (short)this->searchGeneration;
                            sVar3 = ((Point8ShortXY*)(psVar5 + -2))->xOffset;
                            DAT_TileMapState::instance.LogicLayer[_candidateTile]
                                = DAT_TileMapState::instance.LogicLayer[_candidateTile] | 0x10;
                            this->searchQueue.xQueue[this->searchQueue.writeIndex] = sVar3 + sVar2;
                            this->searchQueue.yQueue[this->searchQueue.writeIndex] = *psVar5 + sVar1;
                            this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = _candidateTile;
                            this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                            if (0x13a0f < this->searchQueue.writeIndex) {
                                this->searchQueue.writeIndex = 0;
                            }
                        }
                        _candidateTile = *piVar6 + uVar4;
                        if (DAT_TileMapState::instance.WalkLayer[_candidateTile] != this->searchGeneration
                            && (DAT_TileMapState::instance.LogicLayer[_candidateTile] & 0x30) == 0) {
                            DAT_TileMapState::instance.CertainPathLayer[_candidateTile]
                                = (short)this->searchQueue.currentDistance + 1;
                            DAT_TileMapState::instance.WalkLayer[_candidateTile] = (short)this->searchGeneration;
                            sVar3 = psVar5[2];
                            DAT_TileMapState::instance.LogicLayer[_candidateTile]
                                = DAT_TileMapState::instance.LogicLayer[_candidateTile] | 0x10;
                            this->searchQueue.xQueue[this->searchQueue.writeIndex] = sVar3 + sVar2;
                            this->searchQueue.yQueue[this->searchQueue.writeIndex] = psVar5[4] + sVar1;
                            this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = _candidateTile;
                            this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                            if (0x13a0f < this->searchQueue.writeIndex) {
                                this->searchQueue.writeIndex = 0;
                            }
                        }
                        _candidateTile = piVar6[1] + uVar4;
                        if (DAT_TileMapState::instance.WalkLayer[_candidateTile] != this->searchGeneration
                            && (DAT_TileMapState::instance.LogicLayer[_candidateTile] & 0x30) == 0) {
                            DAT_TileMapState::instance.CertainPathLayer[_candidateTile]
                                = (short)this->searchQueue.currentDistance + 1;
                            DAT_TileMapState::instance.WalkLayer[_candidateTile] = (short)this->searchGeneration;
                            sVar3 = psVar5[6];
                            DAT_TileMapState::instance.LogicLayer[_candidateTile]
                                = DAT_TileMapState::instance.LogicLayer[_candidateTile] | 0x10;
                            this->searchQueue.xQueue[this->searchQueue.writeIndex] = sVar3 + sVar2;
                            this->searchQueue.yQueue[this->searchQueue.writeIndex] = psVar5[8] + sVar1;
                            this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = _candidateTile;
                            this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                            if (0x13a0f < this->searchQueue.writeIndex) {
                                this->searchQueue.writeIndex = 0;
                            }
                        }
                        _candidateTile = piVar6[2] + uVar4;
                        if (DAT_TileMapState::instance.WalkLayer[_candidateTile] != this->searchGeneration
                            && (DAT_TileMapState::instance.LogicLayer[_candidateTile] & 0x30) == 0) {
                            DAT_TileMapState::instance.CertainPathLayer[_candidateTile]
                                = (short)this->searchQueue.currentDistance + 1;
                            DAT_TileMapState::instance.WalkLayer[_candidateTile] = (short)this->searchGeneration;
                            sVar3 = psVar5[10];
                            DAT_TileMapState::instance.LogicLayer[_candidateTile]
                                = DAT_TileMapState::instance.LogicLayer[_candidateTile] | 0x10;
                            this->searchQueue.xQueue[this->searchQueue.writeIndex] = sVar3 + sVar2;
                            this->searchQueue.yQueue[this->searchQueue.writeIndex] = psVar5[0xc] + sVar1;
                            this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = _candidateTile;
                            this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                            if (0x13a0f < this->searchQueue.writeIndex) {
                                this->searchQueue.writeIndex = 0;
                            }
                        }
                        piVar6 = piVar6 + 4;
                        psVar5 = psVar5 + 0x10;
                    } while ((int)psVar5 < 0xb4908c);
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
