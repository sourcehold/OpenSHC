#include "../PathFindingState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/LogicHelpers/Logic1.hpp"
#include "OpenSHC/Map/MapConstants.hpp"
#include "OpenSHC/Map/Navigation/Enums/PathFindingConstants.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_ClimbLogicDefinedData.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        /* inlined copy of ViewportRenderState::xyAreValid */
        inline static int xyAreValid(uint ySpace, uint y)
        {
            return ySpace <= MC_MAP_XY_LIMIT_MIN_1 && y <= MC_MAP_XY_LIMIT_MIN_1
                && DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y * MC_MAP_XY_LIMIT + ySpace] != 0;
        }

        // FUNCTION: STRONGHOLDCRUSADER 0x004A19B0
        dword PathFindingState::findOwnedGatehouse(int playerID, uint ySpace, uint y)
        {
            if (!xyAreValid(ySpace, y)) {
                return 0;
            }
            this->calculations += 1;
            this->searchGeneration += 1;
            if (PFC_SEARCH_GENERATION_LIMIT < this->searchGeneration) {
                this->searchGeneration = 1;
                MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                    sizeof(DAT_TileMapState::instance.WalkLayer), 0, &DAT_TileMapState::instance.WalkLayer[0]);
            }
            this->searchQueue.readIndex = 0;
            this->searchQueue.writeIndex = 1;
            this->searchQueue.currentDistance = 1;
            this->searchQueue.yQueue[0] = y;
            this->searchQueue.xQueue[0] = ySpace;
            this->searchQueue.tilesQueue[0]
                = DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + ySpace;
            DAT_TileMapState::instance.CertainPathLayer[this->searchQueue.tilesQueue[0]]
                = this->searchQueue.currentDistance;
            DAT_TileMapState::instance.WalkLayer[this->searchQueue.tilesQueue[0]] = this->searchGeneration;
            while (this->searchQueue.readIndex != this->searchQueue.writeIndex) {
                int _tile = this->searchQueue.tilesQueue[this->searchQueue.readIndex];
                if (_tile < 0) {
                    return 0;
                }
                if (_tile >= MC_MAP_TILES_COUNT) {
                    return 0;
                }
                int _x = this->searchQueue.xQueue[this->searchQueue.readIndex];
                int _y = this->searchQueue.yQueue[this->searchQueue.readIndex];
                this->searchQueue.currentDistance = DAT_TileMapState::instance.CertainPathLayer[_tile];
                if (MC_MAP_TILES_COUNT < this->searchQueue.currentDistance) {
                    return 0;
                }
                char _link = DAT_TileMapState::instance.PathLinkageLayer[_tile];
                for (int _direction = 0; _direction < PFC_DIRECTIONS; ++_direction) {
                    int _candidate = DAT_TileMapState::instance.directionTranslationMatrix[_y][_direction] + _tile;
                    if (DAT_TileMapState::instance.WalkLayer[_candidate] != this->searchGeneration
                        && (DAT_TileMapState::instance.LogicLayer[_candidate]
                               & (LogicHelpers::L_BORDER | LogicHelpers::L_BORDER_EDGE))
                            == 0) {
                        if ((DAT_ClimbLogicDefinedData::instance.BitFlagHelperForPathLinkage[_direction] & _link)
                            == 0) {
                            short _building = DAT_TileMapState::instance.BuildingLayer[_candidate];
                            if (_building != 0) {
                                switch (DAT_BuildingsState::instance.buildings[_building].buildingType) {
                                case OpenSHC::Map::Buildings::BT_GATEHOUSELARGE:
                                case OpenSHC::Map::Buildings::BT_GATEHOUSESMALL:
                                    if (DAT_BuildingsState::instance.buildings[_building].owner == playerID) {
                                        /*
                                          if gate house from player
                                         */
                                        return _tile;
                                    }
                                }
                            }
                        } else {
                            /*
                              queue tiles
                             */
                            DAT_TileMapState::instance.CertainPathLayer[_candidate]
                                = this->searchQueue.currentDistance + 1;
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
                }
                this->searchQueue.readIndex += 1;
                if (MC_MAP_TILES_COUNT <= this->searchQueue.readIndex) {
                    this->searchQueue.readIndex = 0;
                }
            }
            return 0;
        }

    }
}
}
