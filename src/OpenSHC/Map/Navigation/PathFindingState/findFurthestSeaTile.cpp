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
        // FUNCTION: STRONGHOLDCRUSADER 0x0049BBF0
        void PathFindingState::findFurthestSeaTile(int budget, uint x, uint y)
        {
            short* psVar1;
            int (*paiVar2)[8];
            short _x;
            short _y;
            this->ALG_ResultTile = 0;
            this->ALG_ResultY = 0;
            this->ALG_ResultX = 0;
            if (x < 400 && y < 400 && *(char*)(y * 400 + 0x21aec98 + x) != '\0') {
                this->calculations = this->calculations + 1;
                this->searchGeneration = this->searchGeneration + 1;
                if (32000 < this->searchGeneration) {
                    this->searchGeneration = 1;
                    MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                        160800, '\0', (void*)((int)(DAT_TileMapState::instance.WalkLayer)));
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
                    do {
                        this->ALG_ResultTile = this->searchQueue.tilesQueue[this->searchQueue.readIndex];
                        if ((this->ALG_ResultTile < 0) || (0x13a0f < this->ALG_ResultTile))
                            break;
                        _x = this->searchQueue.xQueue[this->searchQueue.readIndex];
                        _y = this->searchQueue.yQueue[this->searchQueue.readIndex];
                        this->searchQueue.currentDistance
                            = (int)DAT_TileMapState::instance.CertainPathLayer[this->ALG_ResultTile];
                        if (budget < this->searchQueue.writeIndex) {
                            this->ALG_ResultY = (int)_y;
                            this->ALG_ResultX = (int)_x;
                            return;
                        }
                        psVar1 = &DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[0].short_.yOffset;
                        paiVar2 = DAT_TileMapState::instance.directionTranslationMatrix + _y;
                        do {
                            /*
                              for each direction, do:
                             */
                            int _candidate = (*paiVar2)[0] + this->ALG_ResultTile;
                            if (DAT_TileMapState::instance.WalkLayer[_candidate] != this->searchGeneration
                                && (DAT_TileMapState::instance.LogicLayer[_candidate] & 1) != 0) {
                                /*
                                  is sea
                                 */
                                DAT_TileMapState::instance.CertainPathLayer[_candidate]
                                    = (short)this->searchQueue.currentDistance + 1;
                                DAT_TileMapState::instance.WalkLayer[_candidate] = (short)this->searchGeneration;
                                this->searchQueue.xQueue[this->searchQueue.writeIndex]
                                    = ((Point8ShortXY*)(psVar1 + -2))->xOffset + _x;
                                this->searchQueue.yQueue[this->searchQueue.writeIndex] = *psVar1 + _y;
                                this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = _candidate;
                                this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                                if (0x13a0f < this->searchQueue.writeIndex) {
                                    this->searchQueue.writeIndex = 0;
                                }
                            }
                            psVar1 = psVar1 + 8;
                            paiVar2 = (int (*)[8])(*paiVar2 + 2);
                        } while ((int)psVar1 < 0xb4908c);
                        this->searchQueue.readIndex = this->searchQueue.readIndex + 1;
                        if (0x13a0f < this->searchQueue.readIndex) {
                            this->searchQueue.readIndex = 0;
                        }
                    } while (this->searchQueue.readIndex != this->searchQueue.writeIndex);
                }
                this->ALG_ResultX = (int)this->searchQueue.yQueue[this->searchQueue.readIndex + 0x13a0f];
                this->ALG_ResultY = (int)this->searchQueue.yQueue[this->searchQueue.readIndex + -1];
                this->ALG_ResultTile = this->searchQueue.tilesQueue[this->searchQueue.readIndex + -1];
            }
            return;
        }

    }
}
}
