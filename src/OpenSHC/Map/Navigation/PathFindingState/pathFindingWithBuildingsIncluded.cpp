#include "../PathFindingState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_ClimbLogicDefinedData.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          WARNING: Removing unreachable block (ram,0x00498700)
         */
        /*
          WARNING: Removing unreachable block (ram,0x00498713)
         */
        /*
          WARNING: Removing unreachable block (ram,0x0049871e)
         */
        /*
          WARNING: Removing unreachable block (ram,0x0049872d)
         */
        /*
          WARNING: Removing unreachable block (ram,0x00498739)
         */
        /*
          WARNING: Removing unreachable block (ram,0x00498745)
         */
        /*
          WARNING: Removing unreachable block (ram,0x00498749)
         */
        /*
          WARNING: Removing unreachable block (ram,0x00498907)
         */
        /*
          WARNING: Removing unreachable block (ram,0x0049891a)
         */
        /*
          WARNING: Removing unreachable block (ram,0x00498925)
         */
        /*
          WARNING: Removing unreachable block (ram,0x00498934)
         */
        /*
          WARNING: Removing unreachable block (ram,0x00498940)
         */
        /*
          WARNING: Removing unreachable block (ram,0x0049894c)
         */
        /*
          WARNING: Removing unreachable block (ram,0x00498950)
         */
        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00498400
        BOOLEnum PathFindingState::pathFindingWithBuildingsIncluded(
            uint x, uint y, uint x2, uint y2, int maxOptionsToTry, int zeroMeansResetAlgorithm)
        {
            uint uVar1;
            int* piVar2;
            int _nextTileOption;
            uint uVar3;
            uint _tile2;
            short _buildingID;
            uint _currentTile;
            short _currentX;
            short _currentY;
            uint _logical;
            if (399 < x || 399 < y || DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y * 400 + x] == '\0') {
                return FALSE;
            }
            if (x2 == 0xffffffff
                || ((x2 <= 399 && (y2 <= 399))
                    && (DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y2 * 400 + x2] != '\0'))) {
                if (zeroMeansResetAlgorithm == 0) {
                    this->searchGeneration = this->searchGeneration + 1;
                    if (32000 < this->searchGeneration) {
                        this->searchGeneration = 1;
                        MACRO_CALL_MEMBER(
                            OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                            0x27420, '\0', (void*)((int)(DAT_TileMapState::instance.WalkLayer)));
                    }
                    this->searchQueue.writeIndex = 1;
                    this->searchQueue.readIndex = 0;
                    this->searchQueue.currentDistance = 1;
                }
                this->DAT_Ass = this->DAT_Ass + 1;
                this->searchQueue.yQueue[0] = (short)y;
                this->searchQueue.xQueue[0] = (short)x;
                this->searchQueue.tilesQueue[0]
                    = DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x;
                DAT_TileMapState::instance.CertainPathLayer[this->searchQueue.tilesQueue[0]]
                    = (short)this->searchQueue.currentDistance;
                DAT_TileMapState::instance.WalkLayer[this->searchQueue.tilesQueue[0]] = (short)this->searchGeneration;
                if (x2 == 0xffffffff) {
                    _tile2 = 0;
                } else {
                    _tile2 = DAT_ViewportRenderState::instance.translationMatrix[y2].addXgetTile + x2;
                }
                if (this->searchQueue.readIndex != this->searchQueue.writeIndex) {
                    while (true) {
                        _currentTile = this->searchQueue.tilesQueue[this->searchQueue.readIndex];
                        if (_currentTile == _tile2) {
                            return TRUE;
                        }
                        if ((maxOptionsToTry <= this->searchQueue.readIndex) || (80399 < _currentTile))
                            break;
                        _currentX = this->searchQueue.xQueue[this->searchQueue.readIndex];
                        _currentY = this->searchQueue.yQueue[this->searchQueue.readIndex];
                        this->searchQueue.currentDistance
                            = (int)DAT_TileMapState::instance.CertainPathLayer[_currentTile];
                        if (400 < this->searchQueue.currentDistance) {
                            return FALSE;
                        }
                        _buildingID = DAT_TileMapState::instance.BuildingLayer[_currentTile];
                        _logical = DAT_TileMapState::instance.LogicLayer[_currentTile];
                        int _direction = 0;
                        do {
                            _nextTileOption
                                = DAT_TileMapState::instance.directionTranslationMatrix[_currentY][_direction]
                                + _currentTile;
                            /*
                              0x4a5014b1 == check against walkable tiles including keep, walls, and   gatehouses
                             */
                            if (DAT_TileMapState::instance.WalkLayer[_nextTileOption] != this->searchGeneration
                                && ((DAT_TileMapState::instance.PathLinkageLayer[_currentTile]
                                        & DAT_ClimbLogicDefinedData::instance.BitFlagHelperForPathLinkage[_direction])
                                        != 0
                                    || (((((uVar1 = DAT_TileMapState::instance.LogicLayer[_nextTileOption],
                                               (uVar1 & 0x4a5014b1) == 0 && (_buildingID == 0))
                                              && (DAT_TileMapState::instance.BuildingLayer[_nextTileOption] == 0))
                                             && ((uVar3 = _logical & 0x100, uVar3 == 0 || ((uVar1 & 0x100) == 0))))
                                        && ((uVar3 != 0 || ((uVar1 & 0x100) != 0))))))) {
                                DAT_TileMapState::instance.CertainPathLayer[_nextTileOption]
                                    = (short)this->searchQueue.currentDistance + 1;
                                DAT_TileMapState::instance.WalkLayer[_nextTileOption] = (short)this->searchGeneration;
                                this->searchQueue.xQueue[this->searchQueue.writeIndex]
                                    = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction]
                                          .short_.xOffset
                                    + _currentX;
                                this->searchQueue.yQueue[this->searchQueue.writeIndex]
                                    = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction]
                                          .short_.yOffset
                                    + _currentY;
                                this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = _nextTileOption;
                                this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                                if (0x13a10 <= this->searchQueue.writeIndex) {
                                    this->searchQueue.writeIndex = 0;
                                }
                            }
                            _nextTileOption
                                = DAT_TileMapState::instance.directionTranslationMatrix[_currentY][_direction + 1]
                                + _currentTile;
                            if (DAT_TileMapState::instance.WalkLayer[_nextTileOption] != this->searchGeneration
                                && (DAT_TileMapState::instance.PathLinkageLayer[_currentTile]
                                       & DAT_ClimbLogicDefinedData::instance
                                           .BitFlagHelperForPathLinkage[_direction + 1])
                                    != 0) {
                                DAT_TileMapState::instance.CertainPathLayer[_nextTileOption]
                                    = (short)this->searchQueue.currentDistance + 1;
                                DAT_TileMapState::instance.WalkLayer[_nextTileOption] = (short)this->searchGeneration;
                                this->searchQueue.xQueue[this->searchQueue.writeIndex]
                                    = DAT_TerrainDefinedData::instance
                                          .clockwiseCardinalTranslationMatrix[_direction + 1]
                                          .short_.xOffset
                                    + _currentX;
                                this->searchQueue.yQueue[this->searchQueue.writeIndex]
                                    = DAT_TerrainDefinedData::instance
                                          .clockwiseCardinalTranslationMatrix[_direction + 1]
                                          .short_.yOffset
                                    + _currentY;
                                this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = _nextTileOption;
                                this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                                if (0x13a10 <= this->searchQueue.writeIndex) {
                                    this->searchQueue.writeIndex = 0;
                                }
                            }
                            _nextTileOption
                                = DAT_TileMapState::instance.directionTranslationMatrix[_currentY][_direction + 2]
                                + _currentTile;
                            if (DAT_TileMapState::instance.WalkLayer[_nextTileOption] != this->searchGeneration
                                && ((DAT_TileMapState::instance.PathLinkageLayer[_currentTile]
                                        & DAT_ClimbLogicDefinedData::instance
                                            .BitFlagHelperForPathLinkage[_direction + 2])
                                        != 0
                                    || ((((uVar1 = DAT_TileMapState::instance.LogicLayer[_nextTileOption],
                                              (uVar1 & 0x4a5014b1) == 0 && (_buildingID == 0))
                                             && (DAT_TileMapState::instance.BuildingLayer[_nextTileOption] == 0))
                                        && (((uVar3 = _logical & 0x100, uVar3 == 0 || ((uVar1 & 0x100) == 0))
                                            && ((uVar3 != 0 || ((uVar1 & 0x100) != 0))))))))) {
                                DAT_TileMapState::instance.CertainPathLayer[_nextTileOption]
                                    = (short)this->searchQueue.currentDistance + 1;
                                DAT_TileMapState::instance.WalkLayer[_nextTileOption] = (short)this->searchGeneration;
                                this->searchQueue.xQueue[this->searchQueue.writeIndex]
                                    = DAT_TerrainDefinedData::instance
                                          .clockwiseCardinalTranslationMatrix[_direction + 2]
                                          .short_.xOffset
                                    + _currentX;
                                this->searchQueue.yQueue[this->searchQueue.writeIndex]
                                    = DAT_TerrainDefinedData::instance
                                          .clockwiseCardinalTranslationMatrix[_direction + 2]
                                          .short_.yOffset
                                    + _currentY;
                                this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = _nextTileOption;
                                this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                                if (0x13a10 <= this->searchQueue.writeIndex) {
                                    this->searchQueue.writeIndex = 0;
                                }
                            }
                            _nextTileOption
                                = DAT_TileMapState::instance.directionTranslationMatrix[_currentY][_direction + 3]
                                + _currentTile;
                            if (DAT_TileMapState::instance.WalkLayer[_nextTileOption] != this->searchGeneration
                                && (DAT_TileMapState::instance.PathLinkageLayer[_currentTile]
                                       & DAT_ClimbLogicDefinedData::instance
                                           .BitFlagHelperForPathLinkage[_direction + 3])
                                    != 0) {
                                DAT_TileMapState::instance.CertainPathLayer[_nextTileOption]
                                    = (short)this->searchQueue.currentDistance + 1;
                                DAT_TileMapState::instance.WalkLayer[_nextTileOption] = (short)this->searchGeneration;
                                this->searchQueue.xQueue[this->searchQueue.writeIndex]
                                    = DAT_TerrainDefinedData::instance
                                          .clockwiseCardinalTranslationMatrix[_direction + 3]
                                          .short_.xOffset
                                    + _currentX;
                                this->searchQueue.yQueue[this->searchQueue.writeIndex]
                                    = DAT_TerrainDefinedData::instance
                                          .clockwiseCardinalTranslationMatrix[_direction + 3]
                                          .short_.yOffset
                                    + _currentY;
                                this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = _nextTileOption;
                                this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                                if (0x13a10 <= this->searchQueue.writeIndex) {
                                    this->searchQueue.writeIndex = 0;
                                }
                            }
                            _direction = _direction + 4;
                        } while (_direction < 8);
                        this->searchQueue.readIndex = this->searchQueue.readIndex + 1;
                        if (0x13a10 <= this->searchQueue.readIndex) {
                            this->searchQueue.readIndex = 0;
                        }
                        if (this->searchQueue.readIndex == this->searchQueue.writeIndex) {
                            return FALSE;
                        }
                    }
                }
            }
            return FALSE;
        }

    }
}
}
