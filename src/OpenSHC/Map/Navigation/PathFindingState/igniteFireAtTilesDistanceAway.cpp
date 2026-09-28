#include "../PathFindingState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Entities.func.hpp"
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
        // FUNCTION: STRONGHOLDCRUSADER 0x004A2DD0
        undefined4 PathFindingState::igniteFireAtTilesDistanceAway(int tile, int maxDistance, int playerID)
        {
            short* psVar3;
            int* piVar4;
            int iVar5;
            int _index2;
            int _index;
            uint _tiles[100];
            uint _tile;
            uint _cTile;
            this->calculations = this->calculations + 1;
            this->searchGeneration = this->searchGeneration + 1;
            _index = 0;
            if (32000 < this->searchGeneration) {
                this->searchGeneration = 1;
                MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                    0x27420, '\0', (void*)((int)(DAT_TileMapState::instance.WalkLayer)));
            }
            this->searchQueue.yQueue[0] = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile];
            this->searchQueue.xQueue[0] = (short)tile
                - (short)DAT_ViewportRenderState::instance.translationMatrix[this->searchQueue.yQueue[0]].addXgetTile;
            this->searchQueue.tilesQueue[0] = tile;
            this->searchQueue.readIndex = 0;
            this->searchQueue.writeIndex = 1;
            this->searchQueue.currentDistance = 1;
            DAT_TileMapState::instance.CertainPathLayer[tile] = 1;
            DAT_TileMapState::instance.WalkLayer[this->searchQueue.tilesQueue[0]] = (short)this->searchGeneration;
            if (this->searchQueue.readIndex != this->searchQueue.writeIndex) {
                while (_tile = this->searchQueue.tilesQueue[this->searchQueue.readIndex], _tile < 0x13a10) {
                    short sVar1 = this->searchQueue.xQueue[this->searchQueue.readIndex];
                    short sVar2 = this->searchQueue.yQueue[this->searchQueue.readIndex];
                    this->searchQueue.currentDistance = (int)DAT_TileMapState::instance.CertainPathLayer[_tile];
                    if ((0x13a10 < this->searchQueue.currentDistance)
                        || (maxDistance < this->searchQueue.currentDistance))
                        break;
                    _tiles[_index] = _tile;
                    _index = _index + 1;
                    piVar4 = DAT_TileMapState::instance.directionTranslationMatrix[sVar2] + 1;
                    psVar3 = &DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[0].short_.yOffset;
                    do {
                        /*
                          For every direction, queue tiles that are not a border tile
                         */
                        iVar5 = (*(int (*)[8])(piVar4 + -1))[0] + _tile;
                        if (DAT_TileMapState::instance.WalkLayer[iVar5] != this->searchGeneration
                            && (DAT_TileMapState::instance.LogicLayer[iVar5] & 0x30) == 0) {
                            DAT_TileMapState::instance.CertainPathLayer[iVar5]
                                = (short)this->searchQueue.currentDistance + 1;
                            DAT_TileMapState::instance.WalkLayer[iVar5] = (short)this->searchGeneration;
                            this->searchQueue.xQueue[this->searchQueue.writeIndex]
                                = ((Point8ShortXY*)(psVar3 + -2))->xOffset + sVar1;
                            this->searchQueue.yQueue[this->searchQueue.writeIndex] = *psVar3 + sVar2;
                            this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = iVar5;
                            this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                            if (0x13a0f < this->searchQueue.writeIndex) {
                                this->searchQueue.writeIndex = 0;
                            }
                        }
                        iVar5 = *piVar4 + _tile;
                        if (DAT_TileMapState::instance.WalkLayer[iVar5] != this->searchGeneration
                            && (DAT_TileMapState::instance.LogicLayer[iVar5] & 0x30) == 0) {
                            DAT_TileMapState::instance.CertainPathLayer[iVar5]
                                = (short)this->searchQueue.currentDistance + 1;
                            DAT_TileMapState::instance.WalkLayer[iVar5] = (short)this->searchGeneration;
                            this->searchQueue.xQueue[this->searchQueue.writeIndex] = psVar3[2] + sVar1;
                            this->searchQueue.yQueue[this->searchQueue.writeIndex] = psVar3[4] + sVar2;
                            this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = iVar5;
                            this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                            if (0x13a0f < this->searchQueue.writeIndex) {
                                this->searchQueue.writeIndex = 0;
                            }
                        }
                        iVar5 = piVar4[1] + _tile;
                        if (DAT_TileMapState::instance.WalkLayer[iVar5] != this->searchGeneration
                            && (DAT_TileMapState::instance.LogicLayer[iVar5] & 0x30) == 0) {
                            DAT_TileMapState::instance.CertainPathLayer[iVar5]
                                = (short)this->searchQueue.currentDistance + 1;
                            DAT_TileMapState::instance.WalkLayer[iVar5] = (short)this->searchGeneration;
                            this->searchQueue.xQueue[this->searchQueue.writeIndex] = psVar3[6] + sVar1;
                            this->searchQueue.yQueue[this->searchQueue.writeIndex] = psVar3[8] + sVar2;
                            this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = iVar5;
                            this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                            if (0x13a0f < this->searchQueue.writeIndex) {
                                this->searchQueue.writeIndex = 0;
                            }
                        }
                        iVar5 = piVar4[2] + _tile;
                        if (DAT_TileMapState::instance.WalkLayer[iVar5] != this->searchGeneration
                            && (DAT_TileMapState::instance.LogicLayer[iVar5] & 0x30) == 0) {
                            DAT_TileMapState::instance.CertainPathLayer[iVar5]
                                = (short)this->searchQueue.currentDistance + 1;
                            DAT_TileMapState::instance.WalkLayer[iVar5] = (short)this->searchGeneration;
                            this->searchQueue.xQueue[this->searchQueue.writeIndex] = psVar3[10] + sVar1;
                            this->searchQueue.yQueue[this->searchQueue.writeIndex] = psVar3[0xc] + sVar2;
                            this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = iVar5;
                            this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                            if (0x13a0f < this->searchQueue.writeIndex) {
                                this->searchQueue.writeIndex = 0;
                            }
                        }
                        piVar4 = piVar4 + 4;
                        psVar3 = psVar3 + 0x10;
                    } while ((int)psVar3 < 0xb4908c);
                    this->searchQueue.readIndex = this->searchQueue.readIndex + 1;
                    if (0x13a0f < this->searchQueue.readIndex) {
                        this->searchQueue.readIndex = 0;
                    }
                    if (this->searchQueue.readIndex == this->searchQueue.writeIndex)
                        break;
                }
            }
            _index2 = 0;
            if (0 < _index) {
                do {
                    _cTile = _tiles[_index2];
                    MACRO_CALL(OpenSHC::Map::Entities_Func::IgniteFireAtMiniTile_Convenience)(playerID,
                        (_cTile
                            - DAT_ViewportRenderState::instance
                                .translationMatrix[DAT_ViewportRenderState::instance
                                        .tileTranslationMatrix_YComponent[_cTile]]
                                .addXgetTile)
                            * 8,
                        (int)(DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[_cTile] * 8),
                        (int)(DAT_TileMapState::instance.HeightLayer[_cTile]), 2);
                    _index2 = _index2 + 1;
                } while (_index2 < _index);
            }
            return (undefined4)(0);
        }

    }
}
}
