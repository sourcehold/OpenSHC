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
        // FUNCTION: STRONGHOLDCRUSADER 0x0049D0E0
        void PathFindingState::findFreeTileOnDefensiveStructure(int unitID, int x, int y)
        {
            short* psVar3;
            int (*paiVar4)[8];
            int iVar5;
            int _tile;
            this->calculations = this->calculations + 1;
            this->ALG_ResultTile = 0;
            this->ALG_ResultY = 0;
            this->ALG_ResultX = 0;
            if ((uint)x < 400 && (uint)y < 400 && *(char*)(y * 400 + 0x21aec98 + x) != '\0') {
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
                this->searchQueue.tilesQueue[0]
                    = DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x;
                DAT_TileMapState::instance.CertainPathLayer[this->searchQueue.tilesQueue[0]] = 1;
                DAT_TileMapState::instance.WalkLayer[this->searchQueue.tilesQueue[0]] = (short)this->searchGeneration;
                if (this->searchQueue.readIndex != this->searchQueue.writeIndex) {
                    while ((_tile = this->searchQueue.tilesQueue[this->searchQueue.readIndex],
                        -1 < _tile && (_tile < 0x13a10))) {
                        short sVar1 = this->searchQueue.xQueue[this->searchQueue.readIndex];
                        short sVar2 = this->searchQueue.yQueue[this->searchQueue.readIndex];
                        iVar5 = (int)sVar2;
                        if ((short)DAT_TileMapState::instance.UnitLayer[_tile] == 0) {
                            this->ALG_ResultX = (int)sVar1;
                            this->ALG_ResultY = iVar5;
                            this->ALG_ResultTile = _tile;
                            return;
                        }
                        if ((short)DAT_TileMapState::instance.UnitLayer[_tile] == unitID) {
                            this->ALG_ResultX = (int)sVar1;
                            this->ALG_ResultY = iVar5;
                            this->ALG_ResultTile = _tile;
                            return;
                        }
                        this->searchQueue.currentDistance = (int)DAT_TileMapState::instance.CertainPathLayer[_tile];
                        if (0x13a10 < this->searchQueue.currentDistance) {
                            return;
                        }
                        psVar3 = &DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[0].short_.yOffset;
                        paiVar4 = DAT_TileMapState::instance.directionTranslationMatrix + iVar5;
                        do {
                            iVar5 = (*paiVar4)[0] + _tile;
                            if (DAT_TileMapState::instance.WalkLayer[iVar5] != this->searchGeneration
                                && (DAT_TileMapState::instance.LogicLayer[iVar5] & 0x10000100U) != 0) {
                                /*
                                  queue tiles that are wall gatehouse tower or keep
                                 */
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
                            psVar3 = psVar3 + 8;
                            paiVar4 = (int (*)[8])(*paiVar4 + 2);
                        } while ((int)psVar3 < 0xb4908c);
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
            return;
        }

    }
}
}
