#include "../PathFindingState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Location/Point8ShortXY.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        using OpenSHC::Map::Location::Point8ShortXY;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004A4140
        BOOLEnum PathFindingState::pathFindingToAttackCastleIncludingMoat(
            undefined4 playerID, int wallOwnerPlayerID, uint x, uint y, byte* out_successUnk, int* out_x, int* out_y)
        {
            this->calculations = this->calculations + 1;
            MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                0x27420, '\0', (void*)((int)(DAT_TileMapState::instance.CertainPathLayer)));
            *out_y = 0;
            *out_x = 0;
            if (399 < x || 399 < y || DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y * 400 + x] == '\0') {
                return FALSE;
            }
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
            while (this->searchQueue.readIndex != this->searchQueue.writeIndex) {
                int _currentTile = this->searchQueue.tilesQueue[this->searchQueue.readIndex];
                if ((_currentTile < 0) || (0x13a0f < _currentTile)) {
                    return FALSE;
                }
                int _currentX = (int)this->searchQueue.xQueue[this->searchQueue.readIndex];
                int _currentY = (int)this->searchQueue.yQueue[this->searchQueue.readIndex];
                if ((DAT_TileMapState::instance.LogicLayer[_currentTile] & 0x100) != 0
                    && (DAT_TileMapState::instance.LogicLayer[_currentTile] & 2) == 0
                    && wallOwnerPlayerID == (DAT_TileMapState::instance.WallOwnerLayer[_currentTile] & 7) + 1) {
                    *out_successUnk = 1;
                    *out_x = (int)_currentX;
                    *out_y = (int)_currentY;
                    return TRUE;
                }
                this->searchQueue.currentDistance = (int)DAT_TileMapState::instance.CertainPathLayer[_currentTile];
                /*
                  Check all directions for movement
                 */
                for (int _direction = 0; _direction < 8; _direction = _direction + 2) {
                    int _nextTile
                        = DAT_TileMapState::instance.directionTranslationMatrix[_currentY][_direction] + _currentTile;
                    if (DAT_TileMapState::instance.WalkLayer[_nextTile] == this->searchGeneration
                        || (DAT_TileMapState::instance.LogicLayer[_nextTile] & 0x31) != 0
                        || (((DAT_TileMapState::instance.LogicLayer[_nextTile] & 0x100000) != 0)
                            && ((DAT_TileMapState::instance.LogicLayer[_nextTile] & 0x200000) == 0))
                        || (char)DAT_TileMapState::instance.LogicLayer[_nextTile] < 0
                        || (DAT_TileMapState::instance.LogicLayer[_nextTile] & 0x1000) != 0) {
                        continue;
                    }
                    if ((DAT_TileMapState::instance.BuildingLayer[_nextTile] != 0)
                        && (2 < (int)(short)DAT_BuildingsState::instance
                                    .buildings[DAT_TileMapState::instance.BuildingLayer[_nextTile]]
                                    .buildingType
                                - 0x4a)) {
                        continue;
                    }
                    if ((DAT_TileMapState::instance.LogicLayer[_nextTile] & 0x40000000) != 0) {
                        int _moatID = MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::returnMoatIDForPlayerIDs,
                            DAT_TileMapState::ptr)(_nextTile, wallOwnerPlayerID);
                        if (_moatID != 0) {
                            *out_successUnk = 0;
                            *out_y = (int)DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[_nextTile];
                            *out_x = _nextTile
                                - DAT_ViewportRenderState::instance
                                      .translationMatrix[DAT_ViewportRenderState::instance
                                              .tileTranslationMatrix_YComponent[_nextTile]]
                                      .addXgetTile;
                            return TRUE;
                        }
                        continue;
                    }
                    DAT_TileMapState::instance.CertainPathLayer[_nextTile]
                        = (short)this->searchQueue.currentDistance + 1;
                    DAT_TileMapState::instance.WalkLayer[_nextTile] = (short)this->searchGeneration;
                    this->searchQueue.xQueue[this->searchQueue.writeIndex]
                        = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction].short_.xOffset
                        + _currentX;
                    this->searchQueue.yQueue[this->searchQueue.writeIndex]
                        = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction].short_.yOffset
                        + _currentY;
                    this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = _nextTile;
                    this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                    if (0x13a0f < this->searchQueue.writeIndex) {
                        this->searchQueue.writeIndex = 0;
                    }
                }
                this->searchQueue.readIndex = this->searchQueue.readIndex + 1;
                if (0x13a0f < this->searchQueue.readIndex) {
                    this->searchQueue.readIndex = 0;
                }
            }
            return FALSE;
        }

    }
}
}
