#include "../PathFindingState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Entities/EntityType.hpp"
#include "OpenSHC/Map/MapConstants.hpp"

#include "OpenSHC/Globals/DAT_ClimbLogicDefinedData.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        // FUNCTION: STRONGHOLDCRUSADER 0x004A01D0
        dword PathFindingState::findBestAttackTileByPathCost(uint param_1, uint param_2, int param_3, uint param_4)
        {
            /*
              one slot holds two things, as in the original: the 1000 returned when the search
              cannot start, and then each neighbour tile the search steps onto
             */
            dword _candidate = 1000;
            int _bestScore = 1000;
            dword _bestTile = 0;
            if (param_1 > MC_MAP_XY_LIMIT_MIN_1 || param_2 > MC_MAP_XY_LIMIT_MIN_1
                || DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[param_2 * MC_MAP_XY_LIMIT + param_1]
                    == 0) {
                return _candidate;
            }
            this->calculations += 1;
            this->searchGeneration += 1;
            if (PFC_SEARCH_GENERATION_LIMIT < this->searchGeneration) {
                this->searchGeneration = 1;
                MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                    sizeof(DAT_TileMapState::instance.WalkLayer), 0, (void*)(DAT_TileMapState::instance.WalkLayer));
            }
            this->searchQueue.readIndex = 0;
            this->searchQueue.writeIndex = 1;
            this->searchQueue.currentDistance = 1;
            this->searchQueue.yQueue[0] = param_2;
            this->searchQueue.tilesQueue[0]
                = DAT_ViewportRenderState::instance.translationMatrix[param_2].addXgetTile + param_1;
            DAT_TileMapState::instance.CertainPathLayer[this->searchQueue.tilesQueue[0]]
                = this->searchQueue.currentDistance;
            DAT_TileMapState::instance.WalkLayer[this->searchQueue.tilesQueue[0]] = this->searchGeneration;
            while (this->searchQueue.readIndex != this->searchQueue.writeIndex) {
                int _queuedTile = this->searchQueue.tilesQueue[this->searchQueue.readIndex];
                if (_queuedTile < 0) {
                    return _bestTile;
                }
                if (_queuedTile >= MC_MAP_TILES_COUNT) {
                    return _bestTile;
                }
                int _y = this->searchQueue.yQueue[this->searchQueue.readIndex];
                this->searchQueue.currentDistance = DAT_TileMapState::instance.CertainPathLayer[_queuedTile];
                if (MC_MAP_TILES_COUNT < this->searchQueue.currentDistance) {
                    return _bestTile;
                }
                for (int _direction = 0; _direction < PFC_DIRECTIONS; ++_direction) {
                    if ((DAT_TileMapState::instance.PathLinkageLayer[_queuedTile]
                            & DAT_ClimbLogicDefinedData::instance.BitFlagHelperForPathLinkage[_direction])
                        != 0) {
                        _candidate
                            = DAT_TileMapState::instance.directionTranslationMatrix[_y][_direction] + _queuedTile;
                        if (DAT_TileMapState::instance.WalkLayer[_candidate] != this->searchGeneration) {
                            int _plane = DAT_TroopValueState::instance.attackInfo.playerInfo[param_3 - 1]
                                             .currentPlayerID_OR_attackedPlayerID_OR_one;
                            uint _hackValue
                                = DAT_TileMapState::instance.SEC_PathfindingCostTileMap1105[_plane][_candidate];
                            int _cost = DAT_TileMapState::instance.SEC_TileMap1104[_candidate];
                            int _entity = DAT_TileMapState::instance.EntityLayer[_candidate];
                            if (((_entity == 0)
                                    || (DAT_EntityState::instance.entityArray[_entity].entityType
                                        != OpenSHC::Map::Entities::ET_FIRE))
                                && _hackValue == param_4) {
                                if ((10 < this->searchQueue.currentDistance) && (_bestTile != 0)) {
                                    return _bestTile;
                                }
                                if (6 < this->searchQueue.currentDistance) {
                                    int _score = this->searchQueue.currentDistance + _cost * 3;
                                    if (_score < _bestScore) {
                                        _bestScore = _score;
                                        _bestTile = _candidate;
                                    }
                                }
                            }
                            DAT_TileMapState::instance.CertainPathLayer[_candidate]
                                = this->searchQueue.currentDistance + 1;
                            DAT_TileMapState::instance.WalkLayer[_candidate] = this->searchGeneration;
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
                }
                this->searchQueue.readIndex += 1;
                if (MC_MAP_TILES_COUNT <= this->searchQueue.readIndex) {
                    this->searchQueue.readIndex = 0;
                }
            }
            return _bestTile;
        }

    }
}
}
