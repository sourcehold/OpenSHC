#include "../PathFindingState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Location/Point8ShortXY.hpp"
#include "OpenSHC/Map/LogicHelpers/Logic1.hpp"
#include "OpenSHC/Map/MapConstants.hpp"

#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {
        using OpenSHC::Map::Location::Point8ShortXY;

        // FUNCTION: STRONGHOLDCRUSADER 0x004A0E50
        void PathFindingState::setWalkabilityBorderLogicLayerForSmallerMapSizes()
        {
            this->resultTile = 0;
            this->resultY = 0;
            this->resultX = 0;
            this->searchGeneration += 1;
            if (PFC_SEARCH_GENERATION_LIMIT < this->searchGeneration) {
                this->searchGeneration = 1;
                MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                    sizeof(DAT_TileMapState::instance.WalkLayer), 0, (void*)(DAT_TileMapState::instance.WalkLayer));
            }
            this->searchQueue.readIndex = 0;
            this->searchQueue.writeIndex = 1;
            this->searchQueue.currentDistance = 1;
            this->searchQueue.yQueue[0] = 2;
            this->searchQueue.xQueue[0] = 198;
            int _startTile = DAT_ViewportRenderState::instance.translationMatrix[2].addXgetTile + 198;
            this->searchQueue.tilesQueue[0] = _startTile;
            DAT_TileMapState::instance.CertainPathLayer[_startTile] = this->searchQueue.currentDistance;
            DAT_TileMapState::instance.WalkLayer[this->searchQueue.tilesQueue[0]] = this->searchGeneration;
            while (this->searchQueue.readIndex != this->searchQueue.writeIndex) {
                uint _tile = this->searchQueue.tilesQueue[this->searchQueue.readIndex];
                if (MC_MAP_TILES_COUNT - 1 < _tile) {
                    return;
                }
                int _y = this->searchQueue.yQueue[this->searchQueue.readIndex];
                int _x = this->searchQueue.xQueue[this->searchQueue.readIndex];
                this->searchQueue.currentDistance = DAT_TileMapState::instance.CertainPathLayer[_tile];
                for (int _direction = 0; _direction < PFC_DIRECTIONS; ++_direction) {
                    int _candidateTile = DAT_TileMapState::instance.directionTranslationMatrix[_y][_direction] + _tile;
                    if (DAT_TileMapState::instance.WalkLayer[_candidateTile] != this->searchGeneration
                        && (DAT_TileMapState::instance.LogicLayer[_candidateTile]
                               & (LogicHelpers::L_BORDER | LogicHelpers::L_BORDER_EDGE))
                            == 0) {
                        DAT_TileMapState::instance.CertainPathLayer[_candidateTile]
                            = this->searchQueue.currentDistance + 1;
                        DAT_TileMapState::instance.WalkLayer[_candidateTile] = this->searchGeneration;
                        short _xOffset = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction]
                                             .short_.xOffset;
                        DAT_TileMapState::instance.LogicLayer[_candidateTile] |= LogicHelpers::L_BORDER;
                        this->searchQueue.xQueue[this->searchQueue.writeIndex] = _xOffset + _x;
                        this->searchQueue.yQueue[this->searchQueue.writeIndex]
                            = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction]
                                  .short_.yOffset
                            + _y;
                        this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = _candidateTile;
                        this->searchQueue.writeIndex += 1;
                        if (MC_MAP_TILES_COUNT <= this->searchQueue.writeIndex) {
                            this->searchQueue.writeIndex = 0;
                        }
                    }
                }

                this->searchQueue.readIndex += 1;
                if (MC_MAP_TILES_COUNT <= this->searchQueue.readIndex) {
                    this->searchQueue.readIndex = 0;
                }
            }
        }

    }
}
}
