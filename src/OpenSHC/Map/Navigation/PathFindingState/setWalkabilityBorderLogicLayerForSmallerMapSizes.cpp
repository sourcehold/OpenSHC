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
            while (this->searchQueue.readIndex != this->searchQueue.writeIndex) {
                uint uVar4 = this->searchQueue.tilesQueue[this->searchQueue.readIndex];
                if (0x13a0f < uVar4) {
                    return;
                }
                int sVar1 = (int)this->searchQueue.yQueue[this->searchQueue.readIndex];
                int sVar2 = (int)this->searchQueue.xQueue[this->searchQueue.readIndex];
                this->searchQueue.currentDistance = (int)DAT_TileMapState::instance.CertainPathLayer[uVar4];
                for (int _direction = 0; _direction < 8; _direction = _direction + 4) {
                    _candidateTile = DAT_TileMapState::instance.directionTranslationMatrix[sVar1][_direction] + uVar4;
                    if (DAT_TileMapState::instance.WalkLayer[_candidateTile] != this->searchGeneration
                        && (DAT_TileMapState::instance.LogicLayer[_candidateTile] & 0x30) == 0) {
                        DAT_TileMapState::instance.CertainPathLayer[_candidateTile]
                            = (short)this->searchQueue.currentDistance + 1;
                        DAT_TileMapState::instance.WalkLayer[_candidateTile] = (short)this->searchGeneration;
                        sVar3 = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction]
                                    .short_.xOffset;
                        DAT_TileMapState::instance.LogicLayer[_candidateTile]
                            = DAT_TileMapState::instance.LogicLayer[_candidateTile] | 0x10;
                        this->searchQueue.xQueue[this->searchQueue.writeIndex] = sVar3 + sVar2;
                        this->searchQueue.yQueue[this->searchQueue.writeIndex]
                            = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction]
                                  .short_.yOffset
                            + sVar1;
                        this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = _candidateTile;
                        this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                        if (0x13a0f < this->searchQueue.writeIndex) {
                            this->searchQueue.writeIndex = 0;
                        }
                    }
                    _candidateTile
                        = DAT_TileMapState::instance.directionTranslationMatrix[sVar1][_direction + 1] + uVar4;
                    if (DAT_TileMapState::instance.WalkLayer[_candidateTile] != this->searchGeneration
                        && (DAT_TileMapState::instance.LogicLayer[_candidateTile] & 0x30) == 0) {
                        DAT_TileMapState::instance.CertainPathLayer[_candidateTile]
                            = (short)this->searchQueue.currentDistance + 1;
                        DAT_TileMapState::instance.WalkLayer[_candidateTile] = (short)this->searchGeneration;
                        sVar3 = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction + 1]
                                    .short_.xOffset;
                        DAT_TileMapState::instance.LogicLayer[_candidateTile]
                            = DAT_TileMapState::instance.LogicLayer[_candidateTile] | 0x10;
                        this->searchQueue.xQueue[this->searchQueue.writeIndex] = sVar3 + sVar2;
                        this->searchQueue.yQueue[this->searchQueue.writeIndex]
                            = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction + 1]
                                  .short_.yOffset
                            + sVar1;
                        this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = _candidateTile;
                        this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                        if (0x13a0f < this->searchQueue.writeIndex) {
                            this->searchQueue.writeIndex = 0;
                        }
                    }
                    _candidateTile
                        = DAT_TileMapState::instance.directionTranslationMatrix[sVar1][_direction + 2] + uVar4;
                    if (DAT_TileMapState::instance.WalkLayer[_candidateTile] != this->searchGeneration
                        && (DAT_TileMapState::instance.LogicLayer[_candidateTile] & 0x30) == 0) {
                        DAT_TileMapState::instance.CertainPathLayer[_candidateTile]
                            = (short)this->searchQueue.currentDistance + 1;
                        DAT_TileMapState::instance.WalkLayer[_candidateTile] = (short)this->searchGeneration;
                        sVar3 = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction + 2]
                                    .short_.xOffset;
                        DAT_TileMapState::instance.LogicLayer[_candidateTile]
                            = DAT_TileMapState::instance.LogicLayer[_candidateTile] | 0x10;
                        this->searchQueue.xQueue[this->searchQueue.writeIndex] = sVar3 + sVar2;
                        this->searchQueue.yQueue[this->searchQueue.writeIndex]
                            = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction + 2]
                                  .short_.yOffset
                            + sVar1;
                        this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = _candidateTile;
                        this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                        if (0x13a0f < this->searchQueue.writeIndex) {
                            this->searchQueue.writeIndex = 0;
                        }
                    }
                    _candidateTile
                        = DAT_TileMapState::instance.directionTranslationMatrix[sVar1][_direction + 3] + uVar4;
                    if (DAT_TileMapState::instance.WalkLayer[_candidateTile] != this->searchGeneration
                        && (DAT_TileMapState::instance.LogicLayer[_candidateTile] & 0x30) == 0) {
                        DAT_TileMapState::instance.CertainPathLayer[_candidateTile]
                            = (short)this->searchQueue.currentDistance + 1;
                        DAT_TileMapState::instance.WalkLayer[_candidateTile] = (short)this->searchGeneration;
                        sVar3 = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction + 3]
                                    .short_.xOffset;
                        DAT_TileMapState::instance.LogicLayer[_candidateTile]
                            = DAT_TileMapState::instance.LogicLayer[_candidateTile] | 0x10;
                        this->searchQueue.xQueue[this->searchQueue.writeIndex] = sVar3 + sVar2;
                        this->searchQueue.yQueue[this->searchQueue.writeIndex]
                            = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction + 3]
                                  .short_.yOffset
                            + sVar1;
                        this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = _candidateTile;
                        this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                        if (0x13a0f < this->searchQueue.writeIndex) {
                            this->searchQueue.writeIndex = 0;
                        }
                    }
                }

                this->searchQueue.readIndex = this->searchQueue.readIndex + 1;
                if (0x13a0f < this->searchQueue.readIndex) {
                    this->searchQueue.readIndex = 0;
                }
            }
            return;
        }

    }
}
}
