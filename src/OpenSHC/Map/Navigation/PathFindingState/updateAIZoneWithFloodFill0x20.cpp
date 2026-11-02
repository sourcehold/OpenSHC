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
        // FUNCTION: STRONGHOLDCRUSADER 0x0049E9E0
        void PathFindingState::updateAIZoneWithFloodFill0x20(int max, uint ySpace, uint y)
        {
            if (ySpace > 399 || y > 399
                || DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y * 400 + ySpace] == '\0') {
                return;
            }
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
            this->searchQueue.xQueue[0] = (short)ySpace;
            this->searchQueue.tilesQueue[0]
                = DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + ySpace;
            DAT_TileMapState::instance.CertainPathLayer[this->searchQueue.tilesQueue[0]]
                = (short)this->searchQueue.currentDistance;
            DAT_TileMapState::instance.WalkLayer[this->searchQueue.tilesQueue[0]] = (short)this->searchGeneration;
            while (this->searchQueue.readIndex != this->searchQueue.writeIndex) {
                int _tile = this->searchQueue.tilesQueue[this->searchQueue.readIndex];
                DAT_TileMapState::instance.AIInfoLayer[_tile] = DAT_TileMapState::instance.AIInfoLayer[_tile] | 0x20;
                int const _x = this->searchQueue.xQueue[this->searchQueue.readIndex];
                int const _y = this->searchQueue.yQueue[this->searchQueue.readIndex];
                this->searchQueue.currentDistance = (int)DAT_TileMapState::instance.CertainPathLayer[_tile];
                if ((int)this->searchQueue.currentDistance > max) {
                    return;
                }
                for (int _direction = 0; _direction < 8; ++_direction) {
                    /*
                      fixme: the edge test is done on the current tile, not on the candidate
                     */
                    if ((DAT_TileMapState::instance.LogicLayer[_tile] & 0x30) != 0) {
                        continue;
                    }
                    int const _candidate
                        = DAT_TileMapState::instance.directionTranslationMatrix[_y][_direction] + _tile;
                    if (DAT_TileMapState::instance.WalkLayer[_candidate] == this->searchGeneration) {
                        continue;
                    }
                    DAT_TileMapState::instance.CertainPathLayer[_candidate]
                        = (short)this->searchQueue.currentDistance + 1;
                    DAT_TileMapState::instance.WalkLayer[_candidate] = (short)this->searchGeneration;
                    this->searchQueue.xQueue[this->searchQueue.writeIndex]
                        = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction].short_.xOffset
                        + _x;
                    this->searchQueue.yQueue[this->searchQueue.writeIndex]
                        = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction].short_.yOffset
                        + _y;
                    this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = _candidate;
                    this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                    if (80400 <= (int)this->searchQueue.writeIndex) {
                        this->searchQueue.writeIndex = 0;
                    }
                }
                this->searchQueue.readIndex = this->searchQueue.readIndex + 1;
                if (80400 <= (int)this->searchQueue.readIndex) {
                    this->searchQueue.readIndex = 0;
                }
            }
        }

    }
}
}
