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
        // FUNCTION: STRONGHOLDCRUSADER 0x0049CE40
        void PathFindingState::findPathableTileWithoutUnitWithBuildingAtXY(int unitID, int ySpace, int y)
        {
            int _buildingAtStart;
            int _tile;
            int _x;
            int _y;
            this->calculations = this->calculations + 1;
            this->ALG_ResultTile = 0;
            this->ALG_ResultY = 0;
            this->ALG_ResultX = 0;
            if ((uint)ySpace <= 399 && (uint)y <= 399
                && DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y * 400 + ySpace] != '\0') {
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
                this->searchQueue.xQueue[0] = (short)ySpace;
                this->searchQueue.tilesQueue[0]
                    = DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + ySpace;
                DAT_TileMapState::instance.CertainPathLayer[this->searchQueue.tilesQueue[0]]
                    = (short)this->searchQueue.currentDistance;
                DAT_TileMapState::instance.WalkLayer[this->searchQueue.tilesQueue[0]] = (short)this->searchGeneration;
                _buildingAtStart = DAT_TileMapState::instance.BuildingLayer[this->searchQueue.tilesQueue[0]];
                while (this->searchQueue.readIndex != this->searchQueue.writeIndex) {
                    _tile = this->searchQueue.tilesQueue[this->searchQueue.readIndex];
                    if (_tile < 0 || _tile >= 0x13a10) {
                        return;
                    }
                    _x = this->searchQueue.xQueue[this->searchQueue.readIndex];
                    _y = this->searchQueue.yQueue[this->searchQueue.readIndex];
                    int _unitID = (short)DAT_TileMapState::instance.UnitLayer[_tile];
                    /*
                      the unit itself, or building space without a unit
                     */
                    if (_unitID == unitID
                        || (DAT_TileMapState::instance.OccupancyLayer[_tile] == '\0' && _unitID == 0
                            && _buildingAtStart == DAT_TileMapState::instance.BuildingLayer[_tile])) {
                        this->ALG_ResultTile = _tile;
                        this->ALG_ResultY = _y;
                        this->ALG_ResultX = _x;
                        return;
                    }
                    this->searchQueue.currentDistance = DAT_TileMapState::instance.CertainPathLayer[_tile];
                    if (0x13a10 < (int)this->searchQueue.currentDistance) {
                        return;
                    }
                    if (0x19 < (int)this->searchQueue.currentDistance) {
                        return;
                    }
                    for (int _direction = 0; _direction < 8; _direction = _direction + 2) {
                        /*
                          for each direction, do:
                         */
                        int _candidate = DAT_TileMapState::instance.directionTranslationMatrix[_y][_direction] + _tile;
                        uint _logic = DAT_TileMapState::instance.LogicLayer[_candidate];
                        if (DAT_TileMapState::instance.WalkLayer[_candidate] != this->searchGeneration
                            && (_logic & 0xb1U) == 0 && (_logic & 0x1000U) == 0
                            && (short)DAT_TileMapState::instance.PathConnectionLayer[_candidate] != 0) {
                            /*
                              queue pathable tiles that aren't see nor tree
                             */
                            DAT_TileMapState::instance.CertainPathLayer[_candidate]
                                = (short)this->searchQueue.currentDistance + 1;
                            DAT_TileMapState::instance.WalkLayer[_candidate] = (short)this->searchGeneration;
                            this->searchQueue.xQueue[this->searchQueue.writeIndex]
                                = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction].short_.xOffset
                                + (short)_x;
                            this->searchQueue.yQueue[this->searchQueue.writeIndex]
                                = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction].short_.yOffset
                                + (short)_y;
                            this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = _candidate;
                            this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                            if (0x13a10 <= (int)this->searchQueue.writeIndex) {
                                this->searchQueue.writeIndex = 0;
                            }
                        }
                    }

                    this->searchQueue.readIndex = this->searchQueue.readIndex + 1;
                    if (0x13a10 <= (int)this->searchQueue.readIndex) {
                        this->searchQueue.readIndex = 0;
                    }
                }
            }
            return;
        }

    }
}
}
