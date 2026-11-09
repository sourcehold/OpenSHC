#include "../PathFindingState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Entities.func.hpp"
#include "OpenSHC/Map/LogicHelpers/Logic1.hpp"
#include "OpenSHC/Map/MapConstants.hpp"
#include "OpenSHC/Map/Navigation/Enums/PathFindingConstants.hpp"

#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        // FUNCTION: STRONGHOLDCRUSADER 0x004A2DD0
        BOOLEnum PathFindingState::igniteFireAtTilesDistanceAway(int tileUnk, int maxDistance, int playerID)
        {
            uint _tiles[100];
            int _index = 0;
            this->calculations += 1;
            this->searchGeneration += 1;
            if (PFC_SEARCH_GENERATION_LIMIT < this->searchGeneration) {
                this->searchGeneration = 1;
                MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                    sizeof(DAT_TileMapState::instance.WalkLayer), 0, &DAT_TileMapState::instance.WalkLayer[0]);
            }
            int _y = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tileUnk];
            int _x = tileUnk - DAT_ViewportRenderState::instance.translationMatrix[_y].addXgetTile;
            this->searchQueue.yQueue[0] = _y;
            this->searchQueue.tilesQueue[0] = tileUnk;
            this->searchQueue.readIndex = 0;
            this->searchQueue.writeIndex = 1;
            this->searchQueue.xQueue[0] = _x;
            this->searchQueue.currentDistance = 1;
            DAT_TileMapState::instance.CertainPathLayer[tileUnk] = this->searchQueue.currentDistance;
            DAT_TileMapState::instance.WalkLayer[this->searchQueue.tilesQueue[0]] = this->searchGeneration;
            while (this->searchQueue.readIndex != this->searchQueue.writeIndex) {
                tileUnk = this->searchQueue.tilesQueue[this->searchQueue.readIndex];
                // one unsigned compare rejects a negative tile and one past the last tile at once
                if (tileUnk < 1 || tileUnk > MC_MAP_TILES_COUNT)
                    break;
                int _x = this->searchQueue.xQueue[this->searchQueue.readIndex];
                int _y = this->searchQueue.yQueue[this->searchQueue.readIndex];
                this->searchQueue.currentDistance = DAT_TileMapState::instance.CertainPathLayer[tileUnk];
                if ((MC_MAP_TILES_COUNT < this->searchQueue.currentDistance)
                    || (this->searchQueue.currentDistance > maxDistance))
                    break;
                _tiles[_index] = tileUnk;
                _index += 1;
                // for every direction, queue the tiles that are not a border tile
                for (int _direction = 0; _direction < PFC_DIRECTIONS; ++_direction) {
                    int _candidate = DAT_TileMapState::instance.directionTranslationMatrix[_y][_direction] + tileUnk;
                    if (DAT_TileMapState::instance.WalkLayer[_candidate] != this->searchGeneration
                        && (DAT_TileMapState::instance.LogicLayer[_candidate]
                               & (LogicHelpers::L_BORDER | LogicHelpers::L_BORDER_EDGE))
                            == 0) {
                        DAT_TileMapState::instance.CertainPathLayer[_candidate] = this->searchQueue.currentDistance + 1;
                        DAT_TileMapState::instance.WalkLayer[_candidate] = this->searchGeneration;
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
            for (int _index2 = 0; _index2 < _index; ++_index2) {
                uint _cTile = _tiles[_index2];
                MACRO_CALL(OpenSHC::Map::Entities_Func::IgniteFireAtMiniTile_Convenience)(playerID,
                    (_cTile
                        - DAT_ViewportRenderState::instance
                            .translationMatrix[DAT_ViewportRenderState::instance
                                    .tileTranslationMatrix_YComponent[_cTile]]
                            .addXgetTile)
                        * 8,
                    DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[_cTile] * 8,
                    DAT_TileMapState::instance.HeightLayer[_cTile], 2);
            }
            return FALSE;
        }

    }
}
}
