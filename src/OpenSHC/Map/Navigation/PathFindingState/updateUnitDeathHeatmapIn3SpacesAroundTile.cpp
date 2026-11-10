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

        // FUNCTION: STRONGHOLDCRUSADER 0x0049E0D0
        void PathFindingState::updateUnitDeathHeatmapIn3SpacesAroundTile(uint x, uint y)
        {
            uint _tile;
            if (x > 399 || y > 399) {
                return;
            }
            if (DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y * 400 + x] == '\0') {
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
                while (_tile = this->searchQueue.tilesQueue[this->searchQueue.readIndex], _tile <= 0x13a0f) {
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
                    // queue the tiles reachable in each linked direction
                    for (int _direction = 0; _direction < 8; ++_direction) {
                        if ((DAT_TileMapState::instance.PathLinkageLayer[_tile]
                                & DAT_ClimbLogicDefinedData::instance.BitFlagHelperForPathLinkage[_direction])
                            == 0) {
                            continue;
                        }
                        int const candidate
                            = DAT_TileMapState::instance.directionTranslationMatrix[_y][_direction] + _tile;
                        if (DAT_TileMapState::instance.WalkLayer[candidate] == this->searchGeneration) {
                            continue;
                        }
                        DAT_TileMapState::instance.CertainPathLayer[candidate]
                            = (short)this->searchQueue.currentDistance + 1;
                        DAT_TileMapState::instance.WalkLayer[candidate] = (short)this->searchGeneration;
                        this->searchQueue.xQueue[this->searchQueue.writeIndex]
                            = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction]
                                  .short_.xOffset
                            + _x;
                        this->searchQueue.yQueue[this->searchQueue.writeIndex]
                            = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction]
                                  .short_.yOffset
                            + _y;
                        this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = candidate;
                        this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                        if (0x13a10 <= (int)this->searchQueue.writeIndex) {
                            this->searchQueue.writeIndex = 0;
                        }
                    }
                    this->searchQueue.readIndex = this->searchQueue.readIndex + 1;
                    if (0x13a10 <= (int)this->searchQueue.readIndex) {
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
