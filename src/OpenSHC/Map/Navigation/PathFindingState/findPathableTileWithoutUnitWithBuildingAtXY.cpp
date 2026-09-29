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
        void PathFindingState::findPathableTileWithoutUnitWithBuildingAtXY(int unitID, int x, int y)
        {
            short* psVar1;
            int iVar2;
            int (*paiVar3)[8];
            short _buildingAtStart;
            int _tile;
            int _x;
            int _y;
            this->calculations = this->calculations + 1;
            this->ALG_ResultTile = 0;
            this->ALG_ResultY = 0;
            this->ALG_ResultX = 0;
            if ((uint)x <= 399 && (uint)y <= 399
                && DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y * 400 + x] != '\0') {
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
                this->searchQueue.tilesQueue[0]
                    = DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x;
                DAT_TileMapState::instance.CertainPathLayer[this->searchQueue.tilesQueue[0]] = 1;
                DAT_TileMapState::instance.WalkLayer[this->searchQueue.tilesQueue[0]] = (short)this->searchGeneration;
                _buildingAtStart = DAT_TileMapState::instance.BuildingLayer[this->searchQueue.tilesQueue[0]];
                if (this->searchQueue.readIndex != this->searchQueue.writeIndex) {
                    while ((_tile = this->searchQueue.tilesQueue[this->searchQueue.readIndex],
                        -1 < _tile && (_tile < 0x13a10))) {
                        _x = (int)this->searchQueue.xQueue[this->searchQueue.readIndex];
                        _y = (int)this->searchQueue.yQueue[this->searchQueue.readIndex];
                        iVar2 = (int)_y;
                        int _unitID = (int)(short)DAT_TileMapState::instance.UnitLayer[_tile];
                        if (_unitID == unitID) {
                            this->ALG_ResultX = (int)_x;
                            this->ALG_ResultY = iVar2;
                            this->ALG_ResultTile = _tile;
                            return;
                        }
                        /*
                          find building space without unit
                         */
                        if (DAT_TileMapState::instance.OccupancyLayer[_tile] == '\0' && _unitID == 0
                            && _buildingAtStart == DAT_TileMapState::instance.BuildingLayer[_tile]) {
                            this->ALG_ResultX = (int)_x;
                            this->ALG_ResultY = iVar2;
                            this->ALG_ResultTile = _tile;
                            return;
                        }
                        this->searchQueue.currentDistance = (int)DAT_TileMapState::instance.CertainPathLayer[_tile];
                        if (0x13a10 < this->searchQueue.currentDistance) {
                            return;
                        }
                        if (0x19 < this->searchQueue.currentDistance) {
                            return;
                        }
                        for (int _direction = 0; _direction < 8; _direction = _direction + 2) {
                            /*
                              for each direction, do:
                             */
                            int _candidate
                                = DAT_TileMapState::instance.directionTranslationMatrix[iVar2][_direction] + _tile;
                            if (DAT_TileMapState::instance.WalkLayer[_candidate] != this->searchGeneration
                                && (DAT_TileMapState::instance.LogicLayer[_candidate] & 0xb1U) == 0
                                && (DAT_TileMapState::instance.LogicLayer[_candidate] & 0x1000U) == 0
                                && (short)DAT_TileMapState::instance.PathConnectionLayer[_candidate] != 0) {
                                /*
                                  queue pathable tiles that aren't see nor tree
                                 */
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
                                if (0x13a0f < this->searchQueue.writeIndex) {
                                    this->searchQueue.writeIndex = 0;
                                }
                            }
                        }

                        this->searchQueue.readIndex = this->searchQueue.readIndex + 1;
                        if (0x13a0f < this->searchQueue.readIndex) {
                            this->searchQueue.readIndex = 0;
                        }
                        if (this->searchQueue.readIndex == this->searchQueue.writeIndex) {
                            return;
                        }
                    }
                }
            }
            return;
        }

    }
}
}
