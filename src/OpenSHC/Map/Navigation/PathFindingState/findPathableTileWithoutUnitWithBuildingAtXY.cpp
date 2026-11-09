#include "../PathFindingState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
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

        // FUNCTION: STRONGHOLDCRUSADER 0x0049CE40
        void PathFindingState::findPathableTileWithoutUnitWithBuildingAtXY(int unitID, int ySpace, int y)
        {
            this->calculations += 1;
            this->ALG_ResultTile = 0;
            this->ALG_ResultY = 0;
            this->ALG_ResultX = 0;
            if ((uint)ySpace <= MC_MAP_XY_LIMIT_MIN_1 && (uint)y <= MC_MAP_XY_LIMIT_MIN_1
                && DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y * MC_MAP_XY_LIMIT + ySpace] != 0) {
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
                int _buildingAtStart = DAT_TileMapState::instance.BuildingLayer[this->searchQueue.tilesQueue[0]];
                while (this->searchQueue.readIndex != this->searchQueue.writeIndex) {
                    int _tile = this->searchQueue.tilesQueue[this->searchQueue.readIndex];
                    if (_tile < 0 || _tile >= MC_MAP_TILES_COUNT) {
                        return;
                    }
                    int _x = this->searchQueue.xQueue[this->searchQueue.readIndex];
                    int _y = this->searchQueue.yQueue[this->searchQueue.readIndex];
                    int _unitID = DAT_TileMapState::instance.UnitLayer[_tile];
                    /*
                      the unit itself, or building space without a unit
                     */
                    if (_unitID == unitID
                        || (DAT_TileMapState::instance.OccupancyLayer[_tile] == 0 && _unitID == 0
                            && _buildingAtStart == DAT_TileMapState::instance.BuildingLayer[_tile])) {
                        this->ALG_ResultTile = _tile;
                        this->ALG_ResultY = _y;
                        this->ALG_ResultX = _x;
                        return;
                    }
                    this->searchQueue.currentDistance = DAT_TileMapState::instance.CertainPathLayer[_tile];
                    if (MC_MAP_TILES_COUNT < this->searchQueue.currentDistance) {
                        return;
                    }
                    if (25 < this->searchQueue.currentDistance) {
                        return;
                    }
                    for (int _direction = 0; _direction < PFC_DIRECTIONS; _direction = _direction + 2) {
                        /*
                          for each direction, do:
                         */
                        int _candidate = DAT_TileMapState::instance.directionTranslationMatrix[_y][_direction] + _tile;
                        uint _logic = DAT_TileMapState::instance.LogicLayer[_candidate];
                        if (DAT_TileMapState::instance.WalkLayer[_candidate] != this->searchGeneration
                            && (_logic
                                   & (LogicHelpers::L_SEA | LogicHelpers::L_BORDER | LogicHelpers::L_BORDER_EDGE
                                       | LogicHelpers::L_ROCKY))
                                == 0
                            && (_logic & LogicHelpers::L_TREE) == 0
                            && DAT_TileMapState::instance.PathConnectionLayer[_candidate] != 0) {
                            /*
                              queue pathable tiles that aren't see nor tree
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

                    this->searchQueue.readIndex += 1;
                    if (MC_MAP_TILES_COUNT <= this->searchQueue.readIndex) {
                        this->searchQueue.readIndex = 0;
                    }
                }
            }
        }

    }
}
}
