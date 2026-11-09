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

        // FUNCTION: STRONGHOLDCRUSADER 0x0049CB00
        void PathFindingState::computeNextRallyPointDestination(int unitID, uint xPos, uint yPos)
        {
            this->calculations += 1;
            this->ALG_ResultTile = 0;
            this->ALG_ResultY = 0;
            this->ALG_ResultX = 0;
            if (xPos <= MC_MAP_XY_LIMIT_MIN_1 && yPos <= MC_MAP_XY_LIMIT_MIN_1
                && DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[yPos * MC_MAP_XY_LIMIT + xPos] != 0) {
                this->searchGeneration += 1;
                if (PFC_SEARCH_GENERATION_LIMIT < this->searchGeneration) {
                    this->searchGeneration = 1;
                    MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                        sizeof(DAT_TileMapState::instance.WalkLayer), 0, &DAT_TileMapState::instance.WalkLayer[0]);
                }
                this->searchQueue.readIndex = 0;
                this->searchQueue.writeIndex = 1;
                this->searchQueue.currentDistance = 1;
                this->searchQueue.yQueue[0] = yPos;
                this->searchQueue.xQueue[0] = xPos;
                this->searchQueue.tilesQueue[0]
                    = DAT_ViewportRenderState::instance.translationMatrix[yPos].addXgetTile + xPos;
                DAT_TileMapState::instance.CertainPathLayer[this->searchQueue.tilesQueue[0]]
                    = this->searchQueue.currentDistance;
                DAT_TileMapState::instance.WalkLayer[this->searchQueue.tilesQueue[0]] = this->searchGeneration;
                while (this->searchQueue.readIndex != this->searchQueue.writeIndex) {
                    int _cTile = this->searchQueue.tilesQueue[this->searchQueue.readIndex];
                    if (_cTile < 0 || _cTile >= MC_MAP_TILES_COUNT) {
                        return;
                    }
                    int _cX = this->searchQueue.xQueue[this->searchQueue.readIndex];
                    int _cY = this->searchQueue.yQueue[this->searchQueue.readIndex];
                    int _unitID = DAT_TileMapState::instance.UnitLayer[_cTile];
                    if (_unitID == unitID || (DAT_TileMapState::instance.OccupancyLayer[_cTile] == 0 && _unitID == 0)) {
                        this->ALG_ResultTile = _cTile;
                        this->ALG_ResultY = _cY;
                        this->ALG_ResultX = _cX;
                        return;
                    }
                    this->searchQueue.currentDistance = DAT_TileMapState::instance.CertainPathLayer[_cTile];
                    if (MC_MAP_TILES_COUNT < this->searchQueue.currentDistance) {
                        return;
                    }
                    for (int _direction = 0; _direction < PFC_DIRECTIONS; _direction = _direction + 2) {
                        int _cTile2 = DAT_TileMapState::instance.directionTranslationMatrix[_cY][_direction] + _cTile;
                        uint _logic = DAT_TileMapState::instance.LogicLayer[_cTile2];
                        if (DAT_TileMapState::instance.WalkLayer[_cTile2] != this->searchGeneration
                            && (_logic
                                   & (LogicHelpers::L_SEA | LogicHelpers::L_BORDER | LogicHelpers::L_BORDER_EDGE
                                       | LogicHelpers::L_ROCKY))
                                == 0
                            && (_logic
                                   & (LogicHelpers::L_BUILDING | LogicHelpers::L_TREE
                                       | LogicHelpers::L_KEEP_NON_MANOR_HOUSE))
                                == 0) {
                            DAT_TileMapState::instance.CertainPathLayer[_cTile2]
                                = this->searchQueue.currentDistance + 1;
                            DAT_TileMapState::instance.WalkLayer[_cTile2] = this->searchGeneration;
                            this->searchQueue.xQueue[this->searchQueue.writeIndex]
                                = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction]
                                      .short_.xOffset
                                + _cX;
                            this->searchQueue.yQueue[this->searchQueue.writeIndex]
                                = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction]
                                      .short_.yOffset
                                + _cY;
                            this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = _cTile2;
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
