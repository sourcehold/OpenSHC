#include "../PathFindingState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Location/Point8ShortXY.hpp"

#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
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
        // FUNCTION: STRONGHOLDCRUSADER 0x0049D340
        void PathFindingState::findWalkableTileThatDoesNotContainUnit(int unitID, uint x, uint y, int considerUnits)
        {
            uint _tHeight;
            short* psVar2;
            uint _absHeight;
            int (*paiVar3)[8];
            ushort _area;
            uint _heightDiff;
            short _buildingHeight;
            short _terrainHeight;
            int _tile;
            short _x;
            short _y;
            _buildingHeight = DAT_UnitsState::instance.units[unitID].buildingHeight;
            _terrainHeight = DAT_UnitsState::instance.units[unitID].terrainOrClimbHeight;
            this->calculations = this->calculations + 1;
            this->ALG_ResultTile = 0;
            this->ALG_ResultY = 0;
            this->ALG_ResultX = 0;
            if (x < 400 && y < 400 && *(char*)(y * 400 + 0x21aec98 + x) != '\0') {
                this->searchGeneration = this->searchGeneration + 1;
                if (32000 < this->searchGeneration) {
                    this->searchGeneration = 1;
                    MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                        0x27420, '\0', (void*)((int)(DAT_TileMapState::instance.WalkLayer)));
                }
                this->searchQueue.currentDistance = 1;
                this->searchQueue.writeIndex = 1;
                this->searchQueue.readIndex = 0;
                _area = DAT_TileMapState::instance.PathConnectionLayer[DAT_UnitsState::instance.units[unitID].tile];
                this->searchQueue.yQueue[0] = (short)y;
                this->searchQueue.xQueue[0] = (short)x;
                this->searchQueue.tilesQueue[0]
                    = DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x;
                DAT_TileMapState::instance.CertainPathLayer[this->searchQueue.tilesQueue[0]] = 1;
                DAT_TileMapState::instance.WalkLayer[this->searchQueue.tilesQueue[0]] = (short)this->searchGeneration;
                if ((DAT_TileMapState::instance.LogicLayer[this->searchQueue.tilesQueue[0]] & 0x30) == 0
                    && this->searchQueue.readIndex != this->searchQueue.writeIndex) {
                    while ((_tile = this->searchQueue.tilesQueue[this->searchQueue.readIndex],
                        -1 < _tile && (_tile < 0x13a10))) {
                        _x = this->searchQueue.xQueue[this->searchQueue.readIndex];
                        _y = this->searchQueue.yQueue[this->searchQueue.readIndex];
                        if ((((short)DAT_TileMapState::instance.UnitLayer[_tile] == 0) || (considerUnits == 0))
                            && (short)DAT_TileMapState::instance.UnitLayer[_tile] != unitID
                            && _area == DAT_TileMapState::instance.PathConnectionLayer[_tile]
                            && (_tHeight = MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getTotalHeightAtTile,
                                    DAT_TileMapState::ptr)(_tile),
                                _heightDiff = ((int)_buildingHeight + (int)_terrainHeight) - _tHeight,
                                _absHeight = (int)_heightDiff >> 0x1f,
                                (int)((_heightDiff ^ _absHeight) - _absHeight) < 16)) {
                            this->ALG_ResultX = (int)_x;
                            this->ALG_ResultY = (int)_y;
                            this->ALG_ResultTile = _tile;
                            return;
                        }
                        this->searchQueue.currentDistance = (int)DAT_TileMapState::instance.CertainPathLayer[_tile];
                        if (0x13a10 < this->searchQueue.currentDistance) {
                            return;
                        }
                        for (int _direction = 0; _direction < 8; _direction = _direction + 2) {
                            int iVar1 = DAT_TileMapState::instance.directionTranslationMatrix[_y][_direction] + _tile;
                            if (DAT_TileMapState::instance.WalkLayer[iVar1] != this->searchGeneration
                                && (DAT_TileMapState::instance.LogicLayer[iVar1] & 0xb1U) == 0
                                && (DAT_TileMapState::instance.LogicLayer[iVar1] & 0x1400U) == 0
                                && DAT_TileMapState::instance.PathConnectionLayer[iVar1] == _area) {
                                DAT_TileMapState::instance.CertainPathLayer[iVar1]
                                    = (short)this->searchQueue.currentDistance + 1;
                                DAT_TileMapState::instance.WalkLayer[iVar1] = (short)this->searchGeneration;
                                this->searchQueue.xQueue[this->searchQueue.writeIndex]
                                    = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction].short_.xOffset + _x;
                                this->searchQueue.yQueue[this->searchQueue.writeIndex] = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction].short_.yOffset + _y;
                                this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = iVar1;
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
