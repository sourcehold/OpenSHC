#include "../PathFindingState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/LogicHelpers/Logic1.hpp"
#include "OpenSHC/Map/MapConstants.hpp"

#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        // FUNCTION: STRONGHOLDCRUSADER 0x0049A6D0
        void PathFindingState::raiseLand2(uint ySpace, uint y, int maxDistance)
        {
            if (ySpace > MC_MAP_XY_LIMIT_MIN_1 || y > MC_MAP_XY_LIMIT_MIN_1
                || DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y * MC_MAP_XY_LIMIT + ySpace] == 0) {
                return;
            }
            MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                sizeof(DAT_TileMapState::instance.CertainPathLayer), 0,
                (void*)(DAT_TileMapState::instance.CertainPathLayer));
            this->searchQueue.readIndex = 0;
            this->searchQueue.writeIndex = 1;
            this->searchQueue.currentDistance = 1;
            this->searchQueue.yQueue[0] = y;
            this->searchQueue.xQueue[0] = ySpace;
            this->searchQueue.tilesQueue[0]
                = DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + ySpace;
            DAT_TileMapState::instance.CertainPathLayer[this->searchQueue.tilesQueue[0]]
                = this->searchQueue.currentDistance;
            ushort _startArea = DAT_TileMapState::instance.PathConnectionLayer[this->searchQueue.tilesQueue[0]];
            while (this->searchQueue.readIndex != this->searchQueue.writeIndex) {
                uint tileUnk = this->searchQueue.tilesQueue[this->searchQueue.readIndex];
                if (MC_MAP_TILES_COUNT - 1 < tileUnk)
                    break;
                int _x = this->searchQueue.xQueue[this->searchQueue.readIndex];
                int _y = this->searchQueue.yQueue[this->searchQueue.readIndex];
                this->searchQueue.currentDistance = DAT_TileMapState::instance.CertainPathLayer[tileUnk];
                if (this->searchQueue.currentDistance > maxDistance)
                    break;
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::raiseLand, DAT_TileMapState::ptr)(tileUnk, _y, 4, 1);
                for (int _direction = 0; _direction < PFC_DIRECTIONS; ++_direction) {
                    int _candidate = DAT_TileMapState::instance.directionTranslationMatrix[_y][_direction] + tileUnk;
                    if (DAT_TileMapState::instance.CertainPathLayer[_candidate] <= 0
                        && DAT_TileMapState::instance.PathConnectionLayer[_candidate] == _startArea
                        && (DAT_TileMapState::instance.LogicLayer[_candidate]
                               & (LogicHelpers::L_BORDER | LogicHelpers::L_BORDER_EDGE))
                            == 0) {
                        DAT_TileMapState::instance.CertainPathLayer[_candidate] = this->searchQueue.currentDistance + 1;
                        this->searchQueue.xQueue[this->searchQueue.writeIndex]
                            = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction]
                                  .short_.xOffset
                            + _x;
                        this->searchQueue.yQueue[this->searchQueue.writeIndex]
                            = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction]
                                  .short_.yOffset
                            + _y;
                        this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = _candidate;
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
            DAT_TileMapState::instance.forceUpdateLogicalAndMiscDisplayLayers = 1;
            DAT_TileMapState::instance.forceUpdateTextureTilemap = 1;
            DAT_TileMapState::instance.forceUpdateGFXLayers = 1;
        }

    }
}
}
