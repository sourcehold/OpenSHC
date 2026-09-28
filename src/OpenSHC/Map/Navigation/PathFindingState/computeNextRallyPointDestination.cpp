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
        // FUNCTION: STRONGHOLDCRUSADER 0x0049CB00
        void PathFindingState::computeNextRallyPointDestination(int unitID, int xPos, int yPos)
        {
            short* _pOffsets;
            int _cY_2;
            int (*_cY2)[8];
            int _cTile;
            short _cX;
            short _cY;
            this->calculations = this->calculations + 1;
            this->ALG_ResultTile = 0;
            this->ALG_ResultY = 0;
            this->ALG_ResultX = 0;
            if ((uint)xPos < 400 && (uint)yPos < 400 && *(char*)(yPos * 400 + 0x21aec98 + xPos) != '\0') {
                this->searchGeneration = this->searchGeneration + 1;
                if (32000 < this->searchGeneration) {
                    this->searchGeneration = 1;
                    MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                        0x27420, '\0', (void*)((int)(DAT_TileMapState::instance.WalkLayer)));
                }
                this->searchQueue.readIndex = 0;
                this->searchQueue.writeIndex = 1;
                this->searchQueue.currentDistance = 1;
                this->searchQueue.yQueue[0] = (short)yPos;
                this->searchQueue.xQueue[0] = (short)xPos;
                this->searchQueue.tilesQueue[0]
                    = DAT_ViewportRenderState::instance.translationMatrix[yPos].addXgetTile + xPos;
                DAT_TileMapState::instance.CertainPathLayer[this->searchQueue.tilesQueue[0]] = 1;
                DAT_TileMapState::instance.WalkLayer[this->searchQueue.tilesQueue[0]] = (short)this->searchGeneration;
                if (this->searchQueue.readIndex != this->searchQueue.writeIndex) {
                    while ((_cTile = this->searchQueue.tilesQueue[this->searchQueue.readIndex],
                        -1 < _cTile && (_cTile < 0x13a10))) {
                        _cX = this->searchQueue.xQueue[this->searchQueue.readIndex];
                        _cY = this->searchQueue.yQueue[this->searchQueue.readIndex];
                        _cY_2 = (int)_cY;
                        if ((short)DAT_TileMapState::instance.UnitLayer[_cTile] == unitID) {
                            this->ALG_ResultX = (int)_cX;
                            this->ALG_ResultY = _cY_2;
                            this->ALG_ResultTile = _cTile;
                            return;
                        }
                        if (DAT_TileMapState::instance.OccupancyLayer[_cTile] == '\0'
                            && (short)DAT_TileMapState::instance.UnitLayer[_cTile] == 0) {
                            this->ALG_ResultX = (int)_cX;
                            this->ALG_ResultY = _cY_2;
                            this->ALG_ResultTile = _cTile;
                            return;
                        }
                        this->searchQueue.currentDistance = (int)DAT_TileMapState::instance.CertainPathLayer[_cTile];
                        if (0x13a10 < this->searchQueue.currentDistance) {
                            return;
                        }
                        for (int _direction = 0; _direction < 8; _direction = _direction + 2) {
                            int _cTile2 = DAT_TileMapState::instance.directionTranslationMatrix[_cY_2][_direction] + _cTile;
                            /*
                              0xb1 == test against sea, rocky, and borders
                             */
                            /*
                              0x10001400 == test against building tree keep
                             */
                            if (DAT_TileMapState::instance.WalkLayer[_cTile2] != this->searchGeneration
                                && (DAT_TileMapState::instance.LogicLayer[_cTile2] & 0xb1U) == 0
                                && (DAT_TileMapState::instance.LogicLayer[_cTile2] & 0x10001400U) == 0) {
                                DAT_TileMapState::instance.CertainPathLayer[_cTile2]
                                    = (short)this->searchQueue.currentDistance + 1;
                                DAT_TileMapState::instance.WalkLayer[_cTile2] = (short)this->searchGeneration;
                                this->searchQueue.xQueue[this->searchQueue.writeIndex]
                                    = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction].short_.xOffset + _cX;
                                this->searchQueue.yQueue[this->searchQueue.writeIndex] = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction].short_.yOffset + _cY;
                                this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = _cTile2;
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
