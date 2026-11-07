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

        // FUNCTION: STRONGHOLDCRUSADER 0x004A2DD0
        BOOLEnum PathFindingState::igniteFireAtTilesDistanceAway(int tileUnk, int maxDistance, int playerID)
        {
            short* psVar3;
            int* piVar4;
            int _candidate;
            int _index2;
            int _index;
            uint _tiles[100];
            uint _cTile;
            _index = 0;
            this->calculations = this->calculations + 1;
            this->searchGeneration = this->searchGeneration + 1;
            if (32000 < this->searchGeneration) {
                this->searchGeneration = 1;
                MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                    sizeof(DAT_TileMapState::instance.WalkLayer), 0, (void*)((int)(DAT_TileMapState::instance.WalkLayer)));
            }
            int _y = (short)DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tileUnk];
            int _x = tileUnk - DAT_ViewportRenderState::instance.translationMatrix[_y].addXgetTile;
            this->searchQueue.yQueue[0] = (short)_y;
            this->searchQueue.tilesQueue[0] = tileUnk;
            this->searchQueue.readIndex = 0;
            this->searchQueue.writeIndex = 1;
            this->searchQueue.xQueue[0] = (short)_x;
            this->searchQueue.currentDistance = 1;
            DAT_TileMapState::instance.CertainPathLayer[tileUnk] = (short)this->searchQueue.currentDistance;
            DAT_TileMapState::instance.WalkLayer[this->searchQueue.tilesQueue[0]] = (short)this->searchGeneration;
            while (this->searchQueue.readIndex != this->searchQueue.writeIndex) {
                tileUnk = this->searchQueue.tilesQueue[this->searchQueue.readIndex];
                if (MC_MAP_TILES_COUNT_MIN_1 < (uint)tileUnk)
                    break;
                int _x = (int)this->searchQueue.xQueue[this->searchQueue.readIndex];
                int _y = (int)this->searchQueue.yQueue[this->searchQueue.readIndex];
                this->searchQueue.currentDistance = (int)DAT_TileMapState::instance.CertainPathLayer[tileUnk];
                if ((MC_MAP_TILES_COUNT < (int)this->searchQueue.currentDistance)
                    || ((int)this->searchQueue.currentDistance > maxDistance))
                    break;
                _tiles[_index] = tileUnk;
                _index = _index + 1;
                // for every direction, queue the tiles that are not a border tile
                for (int _direction = 0; _direction < 8; ++_direction) {
                    _candidate = DAT_TileMapState::instance.directionTranslationMatrix[_y][_direction] + tileUnk;
                    if (DAT_TileMapState::instance.WalkLayer[_candidate] != this->searchGeneration
                        && (DAT_TileMapState::instance.LogicLayer[_candidate] & 0x30) == 0) {
                        DAT_TileMapState::instance.CertainPathLayer[_candidate]
                            = (short)this->searchQueue.currentDistance + 1;
                        DAT_TileMapState::instance.WalkLayer[_candidate] = (short)this->searchGeneration;
                        this->searchQueue.xQueue[this->searchQueue.writeIndex]
                            = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction]
                                  .short_.xOffset
                            + _x;
                        this->searchQueue.yQueue[this->searchQueue.writeIndex]
                            = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction]
                                  .short_.yOffset
                            + _y;
                        this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = _candidate;
                        this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                        if (MC_MAP_TILES_COUNT <= (int)this->searchQueue.writeIndex) {
                            this->searchQueue.writeIndex = 0;
                        }
                    }
                }

                this->searchQueue.readIndex = this->searchQueue.readIndex + 1;
                if (MC_MAP_TILES_COUNT <= (int)this->searchQueue.readIndex) {
                    this->searchQueue.readIndex = 0;
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
                        (int)((short)DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[_cTile] * 8),
                        (int)(DAT_TileMapState::instance.HeightLayer[_cTile]), 2);
                    _index2 = _index2 + 1;
                } while (_index2 < _index);
            }
            return (undefined4)(0);
        }

    }
}
}
