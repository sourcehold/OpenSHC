#include "../PathFindingState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Location/Point8IntXY.hpp"

#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {
        using OpenSHC::Map::Location::Point8IntXY;

        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
          Computes the distance to reach x and y, has a shortcut to basically return distance 1 if the area   of the
          destination is the same as the current area was   decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x0049B1D0
        void PathFindingState::pathFindingDeerAndLionsUnk(int originArea, uint destinationX, uint destinationY)
        {
            Point8IntXY* _cardinalXYOffset;
            int* _cardinalTileOffset;
            int _neswTile1;
            int _neswTile2;
            int _neswTile3;
            int _neswTile4;
            int _currentTile;
            int _currentX;
            int _currentY;
            if (destinationX <= 399 && destinationY <= 399
                && DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[destinationY * 400 + destinationX] != '\0') {
                this->calculations = this->calculations + 1;
                this->searchGeneration = this->searchGeneration + 1;
                this->climbX = destinationX;
                this->climbY = destinationY;
                if (32000 < this->searchGeneration) {
                    this->searchGeneration = 1;
                    MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                        0x27420, '\0', (void*)((int)(DAT_TileMapState::instance.WalkLayer)));
                }
                this->searchQueue.readIndex = 0;
                this->searchQueue.writeIndex = 1;
                this->searchQueue.xQueue[0] = (short)destinationX;
                this->searchQueue.currentDistance = 1;
                this->searchQueue.yQueue[0] = (short)destinationY;
                this->searchQueue.tilesQueue[0]
                    = destinationX + DAT_ViewportRenderState::instance.translationMatrix[destinationY].addXgetTile;
                DAT_TileMapState::instance.CertainPathLayer[this->searchQueue.tilesQueue[0]] = 1;
                DAT_TileMapState::instance.WalkLayer[this->searchQueue.tilesQueue[0]] = (short)this->searchGeneration;
                if (this->searchQueue.readIndex != this->searchQueue.writeIndex) {
                    while ((_currentTile = this->searchQueue.tilesQueue[this->searchQueue.readIndex],
                        -1 < _currentTile && (_currentTile < 80400))) {
                        _currentX = (int)this->searchQueue.xQueue[this->searchQueue.readIndex];
                        _currentY = (int)this->searchQueue.yQueue[this->searchQueue.readIndex];
                        if ((short)DAT_TileMapState::instance.PathConnectionLayer[_currentTile] == originArea) {
                            this->climbX = (int)_currentX;
                            this->climbY = (int)_currentY;
                            return;
                        }
                        this->searchQueue.currentDistance
                            = (int)DAT_TileMapState::instance.CertainPathLayer[_currentTile];
                        if (6 < this->searchQueue.currentDistance) {
                            return;
                        }
                        _cardinalTileOffset = DAT_TileMapState::instance.directionTranslationMatrix[_currentY] + 1;
                        _cardinalXYOffset
                            = &DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[0].int_;
                        do {
                            _neswTile1 = (*(int (*)[8])(_cardinalTileOffset + -1))[0] + _currentTile;
                            if ((DAT_TileMapState::instance.LogicLayer[_neswTile1] & 0x30) == 0) {
                                DAT_TileMapState::instance.CertainPathLayer[_neswTile1]
                                    = (short)this->searchQueue.currentDistance + 1;
                                DAT_TileMapState::instance.WalkLayer[_neswTile1] = (short)this->searchGeneration;
                                this->searchQueue.xQueue[this->searchQueue.writeIndex]
                                    = (short)_cardinalXYOffset->xOffset + _currentX;
                                this->searchQueue.yQueue[this->searchQueue.writeIndex]
                                    = (short)_cardinalXYOffset->yOffset + _currentY;
                                this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = _neswTile1;
                                this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                                if (0x13a0f < this->searchQueue.writeIndex) {
                                    this->searchQueue.writeIndex = 0;
                                }
                            }
                            _neswTile2 = *_cardinalTileOffset + _currentTile;
                            if ((DAT_TileMapState::instance.LogicLayer[_neswTile2] & 0x30) == 0) {
                                DAT_TileMapState::instance.CertainPathLayer[_neswTile2]
                                    = (short)this->searchQueue.currentDistance + 1;
                                DAT_TileMapState::instance.WalkLayer[_neswTile2] = (short)this->searchGeneration;
                                this->searchQueue.xQueue[this->searchQueue.writeIndex]
                                    = *(short*)(_cardinalXYOffset + 1) + _currentX;
                                this->searchQueue.yQueue[this->searchQueue.writeIndex]
                                    = *(short*)(_cardinalXYOffset + 2) + _currentY;
                                this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = _neswTile2;
                                this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                                if (80400 < this->searchQueue.writeIndex) {
                                    this->searchQueue.writeIndex = 0;
                                }
                            }
                            _neswTile3 = _cardinalTileOffset[1] + _currentTile;
                            if ((DAT_TileMapState::instance.LogicLayer[_neswTile3] & 0x30) == 0) {
                                DAT_TileMapState::instance.CertainPathLayer[_neswTile3]
                                    = (short)this->searchQueue.currentDistance + 1;
                                DAT_TileMapState::instance.WalkLayer[_neswTile3] = (short)this->searchGeneration;
                                this->searchQueue.xQueue[this->searchQueue.writeIndex]
                                    = *(short*)(_cardinalXYOffset + 3) + _currentX;
                                this->searchQueue.yQueue[this->searchQueue.writeIndex]
                                    = *(short*)(_cardinalXYOffset + 4) + _currentY;
                                this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = _neswTile3;
                                this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                                if (80400 < this->searchQueue.writeIndex) {
                                    this->searchQueue.writeIndex = 0;
                                }
                            }
                            _neswTile4 = _cardinalTileOffset[2] + _currentTile;
                            if ((DAT_TileMapState::instance.LogicLayer[_neswTile4] & 0x30) == 0) {
                                DAT_TileMapState::instance.CertainPathLayer[_neswTile4]
                                    = (short)this->searchQueue.currentDistance + 1;
                                DAT_TileMapState::instance.WalkLayer[_neswTile4] = (short)this->searchGeneration;
                                this->searchQueue.xQueue[this->searchQueue.writeIndex]
                                    = *(short*)(_cardinalXYOffset + 5) + _currentX;
                                this->searchQueue.yQueue[this->searchQueue.writeIndex]
                                    = *(short*)(_cardinalXYOffset + 6) + _currentY;
                                this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = _neswTile4;
                                this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                                if (80400 < this->searchQueue.writeIndex) {
                                    this->searchQueue.writeIndex = 0;
                                }
                            }
                            _cardinalTileOffset = _cardinalTileOffset + 4;
                            _cardinalXYOffset = _cardinalXYOffset + 8;
                        } while ((int)_cardinalXYOffset < 0xb4908c);
                        this->searchQueue.readIndex = this->searchQueue.readIndex + 1;
                        if (80400 < this->searchQueue.readIndex) {
                            this->searchQueue.readIndex = 0;
                        }
                        /*
                          the right hand side stops incrementing if no valid tiles are found, so the   left hand side
                          catches up breaking when finished. Very elegant
                         */
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
