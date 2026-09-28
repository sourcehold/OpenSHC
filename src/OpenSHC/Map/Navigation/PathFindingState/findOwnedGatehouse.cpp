#include "../PathFindingState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_ClimbLogicDefinedData.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004A19B0
        dword PathFindingState::findOwnedGatehouse(int playerID, uint x, uint y)
        {
            int (*paiVar3)[8];
            short _building;
            int _link;
            dword _tile;
            if (399 < x || 399 < y || DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y * 400 + x] == '\0') {
                return (dword)(0);
            }
            this->calculations = this->calculations + 1;
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
            this->searchQueue.tilesQueue[0] = DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x;
            DAT_TileMapState::instance.CertainPathLayer[this->searchQueue.tilesQueue[0]] = 1;
            DAT_TileMapState::instance.WalkLayer[this->searchQueue.tilesQueue[0]] = (short)this->searchGeneration;
            if (this->searchQueue.readIndex != this->searchQueue.writeIndex) {
                do {
                    _tile = this->searchQueue.tilesQueue[this->searchQueue.readIndex];
                    if ((int)_tile < 0) {
                        return (dword)(0);
                    }
                    if (0x13a0f < (int)_tile) {
                        return (dword)(0);
                    }
                    short sVar1 = this->searchQueue.xQueue[this->searchQueue.readIndex];
                    short sVar2 = this->searchQueue.yQueue[this->searchQueue.readIndex];
                    this->searchQueue.currentDistance = (int)DAT_TileMapState::instance.CertainPathLayer[_tile];
                    if (0x13a10 < this->searchQueue.currentDistance) {
                        return (dword)(0);
                    }
                    _link = DAT_TileMapState::instance.PathLinkageLayer[_tile];
                    int _direction = 0;
                    paiVar3 = DAT_TileMapState::instance.directionTranslationMatrix + sVar2;
                    do {
                        int _candidate = (*paiVar3)[0] + _tile;
                        if (DAT_TileMapState::instance.WalkLayer[_candidate] != this->searchGeneration
                            && (DAT_TileMapState::instance.LogicLayer[_candidate] & 0x30) == 0) {
                            if ((DAT_ClimbLogicDefinedData::instance.BitFlagHelperForPathLinkage[_direction] & _link)
                                == 0) {
                                _building = DAT_TileMapState::instance.BuildingLayer[_candidate];
                                if (_building != 0
                                    && (int)(short)DAT_BuildingsState::instance.buildings[_building].buildingType - 45
                                        < 2
                                    && DAT_BuildingsState::instance.buildings[_building].owner == playerID) {
                                    /*
                                      if gate house from player
                                     */
                                    return (dword)(_tile);
                                }
                            } else {
                                /*
                                  queue tiles
                                 */
                                DAT_TileMapState::instance.CertainPathLayer[_candidate]
                                    = (short)this->searchQueue.currentDistance + 1;
                                DAT_TileMapState::instance.WalkLayer[_candidate] = (short)this->searchGeneration;
                                this->searchQueue.xQueue[this->searchQueue.writeIndex]
                                    = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction]
                                          .short_.xOffset
                                    + sVar1;
                                this->searchQueue.yQueue[this->searchQueue.writeIndex]
                                    = *(short*)((int)DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix
                                          + _direction * 8 + 4)
                                    + sVar2;
                                this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = _candidate;
                                this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                                if (0x13a0f < this->searchQueue.writeIndex) {
                                    this->searchQueue.writeIndex = 0;
                                }
                            }
                        }
                        _direction = _direction + 1;
                        paiVar3 = (int (*)[8])(*paiVar3 + 1);
                    } while (_direction < 8);
                    this->searchQueue.readIndex = this->searchQueue.readIndex + 1;
                    if (0x13a0f < this->searchQueue.readIndex) {
                        this->searchQueue.readIndex = 0;
                    }
                } while (this->searchQueue.readIndex != this->searchQueue.writeIndex);
            }
            return (dword)(0);
        }

    }
}
}
