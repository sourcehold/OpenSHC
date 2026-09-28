#include "../PathFindingState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Location/Point8ShortXY.hpp"

#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

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
        // FUNCTION: STRONGHOLDCRUSADER 0x0049D880
        undefined4 PathFindingState::findClosestFreeTileNearUnitOnBuilding(
            int buildingID, int unitID, int x, int y, int* pX, int* pY)
        {
            short* psVar2;
            uint uVar3;
            int (*paiVar4)[8];
            int iVar5;
            int _lowestDist;
            uint _tile;
            ushort _unitArea;
            short _x;
            short _y;
            this->searchGeneration = this->searchGeneration + 1;
            this->calculations = this->calculations + 1;
            _lowestDist = 10000;
            if (32000 < this->searchGeneration) {
                this->searchGeneration = 1;
                MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                    0x27420, '\0', (void*)((int)(DAT_TileMapState::instance.WalkLayer)));
            }
            this->searchQueue.currentDistance = 1;
            this->searchQueue.readIndex = 0;
            this->searchQueue.writeIndex = 1;
            _unitArea = DAT_TileMapState::instance.PathConnectionLayer[DAT_UnitsState::instance.units[unitID].tile];
            *pX = (int)DAT_UnitsState::instance.units[unitID].x;
            *pY = (int)DAT_UnitsState::instance.units[unitID].y;
            this->searchQueue.yQueue[0] = DAT_UnitsState::instance.units[unitID].y;
            this->searchQueue.xQueue[0] = DAT_UnitsState::instance.units[unitID].x;
            this->searchQueue.tilesQueue[0] = DAT_UnitsState::instance.units[unitID].tile;
            DAT_TileMapState::instance.CertainPathLayer[this->searchQueue.tilesQueue[0]]
                = (short)this->searchQueue.currentDistance;
            DAT_TileMapState::instance.WalkLayer[this->searchQueue.tilesQueue[0]] = (short)this->searchGeneration;
            if (this->searchQueue.readIndex == this->searchQueue.writeIndex) {
                return (undefined4)(1);
            }
            while (true) {
                _tile = this->searchQueue.tilesQueue[this->searchQueue.readIndex];
                if (0x13a0f < _tile) {
                    return (undefined4)(1);
                }
                _x = this->searchQueue.xQueue[this->searchQueue.readIndex];
                _y = this->searchQueue.yQueue[this->searchQueue.readIndex];
                iVar5 = (int)_y;
                uint uVar1 = _x - x;
                uVar3 = (int)uVar1 >> 0x1f;
                int _absDistX = (uVar1 ^ uVar3) - uVar3;
                uVar1 = iVar5 - y >> 0x1f;
                int _absDistY = (iVar5 - y ^ uVar1) - uVar1;
                if (_absDistY < _absDistX) {
                    _absDistY = _absDistX;
                }
                if (_absDistY < _lowestDist) {
                    /*
                      lowest manhatten distance
                     */
                    *pX = (int)_x;
                    *pY = iVar5;
                    _lowestDist = _absDistY;
                }
                this->searchQueue.currentDistance = (int)DAT_TileMapState::instance.CertainPathLayer[_tile];
                if (0x13a10 < this->searchQueue.currentDistance)
                    break;
                for (int _direction = 0; _direction < 8; _direction = _direction + 2) {
                    int _candidate = DAT_TileMapState::instance.directionTranslationMatrix[iVar5][_direction] + _tile;
                    if (DAT_TileMapState::instance.WalkLayer[_candidate] != this->searchGeneration
                        && DAT_TileMapState::instance.PathConnectionLayer[_candidate] == _unitArea
                        && DAT_TileMapState::instance.BuildingLayer[_candidate] == buildingID
                        && DAT_TileMapState::instance.UnitLayer[_candidate] == 0) {
                        /*
                          queue free spaces in the same area as the unit on the same building as the   unit
                         */
                        DAT_TileMapState::instance.CertainPathLayer[_candidate]
                            = (short)this->searchQueue.currentDistance + 1;
                        DAT_TileMapState::instance.WalkLayer[_candidate] = (short)this->searchGeneration;
                        this->searchQueue.xQueue[this->searchQueue.writeIndex]
                            = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction].short_.xOffset + _x;
                        this->searchQueue.yQueue[this->searchQueue.writeIndex] = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction].short_.yOffset + _y;
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
                    return (undefined4)(1);
                }
            }
            return (undefined4)(1);
        }

    }
}
}
