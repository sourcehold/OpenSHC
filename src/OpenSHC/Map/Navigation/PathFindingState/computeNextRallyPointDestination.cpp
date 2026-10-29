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
            int _cTile;
            int _cX;
            int _cY;
            this->calculations = this->calculations + 1;
            this->ALG_ResultTile = 0;
            this->ALG_ResultY = 0;
            this->ALG_ResultX = 0;
            if ((uint)xPos <= 399 && (uint)yPos <= 399
                && DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[yPos * 400 + xPos] != '\0') {
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
                DAT_TileMapState::instance.CertainPathLayer[this->searchQueue.tilesQueue[0]]
                    = (short)this->searchQueue.currentDistance;
                DAT_TileMapState::instance.WalkLayer[this->searchQueue.tilesQueue[0]] = (short)this->searchGeneration;
                while (this->searchQueue.readIndex != this->searchQueue.writeIndex) {
                    _cTile = this->searchQueue.tilesQueue[this->searchQueue.readIndex];
                    if (_cTile < 0 || _cTile >= 0x13a10) {
                        return;
                    }
                    _cX = this->searchQueue.xQueue[this->searchQueue.readIndex];
                    _cY = this->searchQueue.yQueue[this->searchQueue.readIndex];
                    int _unitID = (short)DAT_TileMapState::instance.UnitLayer[_cTile];
                    if (_unitID == unitID || (DAT_TileMapState::instance.OccupancyLayer[_cTile] == '\0' && _unitID == 0)) {
                        this->ALG_ResultTile = _cTile;
                        this->ALG_ResultY = _cY;
                        this->ALG_ResultX = _cX;
                        return;
                    }
                    this->searchQueue.currentDistance = DAT_TileMapState::instance.CertainPathLayer[_cTile];
                    if (0x13a10 < (int)this->searchQueue.currentDistance) {
                        return;
                    }
                    for (int _direction = 0; _direction < 8; _direction = _direction + 2) {
                        int _cTile2 = DAT_TileMapState::instance.directionTranslationMatrix[_cY][_direction] + _cTile;
                        uint _logic = DAT_TileMapState::instance.LogicLayer[_cTile2];
                        /*
                          0xb1 == test against sea, rocky, and borders
                         */
                        /*
                          0x10001400 == test against building tree keep
                         */
                        if (DAT_TileMapState::instance.WalkLayer[_cTile2] != this->searchGeneration
                            && (_logic & 0xb1U) == 0 && (_logic & 0x10001400U) == 0) {
                            DAT_TileMapState::instance.CertainPathLayer[_cTile2]
                                = (short)this->searchQueue.currentDistance + 1;
                            DAT_TileMapState::instance.WalkLayer[_cTile2] = (short)this->searchGeneration;
                            this->searchQueue.xQueue[this->searchQueue.writeIndex]
                                = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction].short_.xOffset
                                + (short)_cX;
                            this->searchQueue.yQueue[this->searchQueue.writeIndex]
                                = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction].short_.yOffset
                                + (short)_cY;
                            this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = _cTile2;
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
