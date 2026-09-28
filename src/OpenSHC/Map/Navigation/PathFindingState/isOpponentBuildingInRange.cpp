#include "../PathFindingState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Location/Point8ShortXY.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
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
        // FUNCTION: STRONGHOLDCRUSADER 0x004A9200
        undefined4 PathFindingState::isOpponentBuildingInRange(
            int playerID, int x, int y, int range, int param_5, int param_6, int keepRange)
        {
            int iVar1;
            short* psVar2;
            int (*paiVar3)[8];
            int _tile;
            short _buildingID;
            int _x;
            int _y;
            if (399 < (uint)x || 399 < (uint)y || DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y * 400 + x] == '\0') {
                return (undefined4)(0);
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
                while ((
                    _tile = this->searchQueue.tilesQueue[this->searchQueue.readIndex], -1 < _tile && (_tile < 80400))) {
                    _x = (int)this->searchQueue.xQueue[this->searchQueue.readIndex];
                    _y = (int)this->searchQueue.yQueue[this->searchQueue.readIndex];
                    this->searchQueue.currentDistance = (int)DAT_TileMapState::instance.CertainPathLayer[_tile];
                    if ((80400 < this->searchQueue.currentDistance) || (this->searchQueue.currentDistance > range))
                        break;
                    _buildingID = DAT_TileMapState::instance.BuildingLayer[_tile];
                    if (_buildingID != 0
                        && DAT_BuildingDefinedData::instance.BuildingTypeOwnable
                                [(short)DAT_BuildingsState::instance.buildings[_buildingID].buildingType]
                            != 0
                        && DAT_GameState::instance.mapAndTime
                                .playerTeams[DAT_BuildingsState::instance.buildings[_buildingID].owner]
                            != DAT_GameState::instance.mapAndTime.playerTeams[playerID]) {
                        return (undefined4)(1);
                    }
                    if ((DAT_TileMapState::instance.LogicLayer[_tile] & 0x100U) != 0
                        && (DAT_TileMapState::instance.LogicLayer[_tile] & 2U) == 0
                        && DAT_GameState::instance.mapAndTime
                                .playerTeams[(DAT_TileMapState::instance.WallOwnerLayer[_tile] & 7) + 1]
                            != DAT_GameState::instance.mapAndTime.playerTeams[playerID]) {
                        return (undefined4)(1);
                    }
                    paiVar3 = DAT_TileMapState::instance.directionTranslationMatrix + _y;
                    psVar2 = &DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[0].short_.yOffset;
                    do {
                        int _newTile = (*paiVar3)[0] + _tile;
                        if (DAT_TileMapState::instance.WalkLayer[_newTile] != this->searchGeneration
                            && (DAT_TileMapState::instance.LogicLayer[_newTile] & 0x30) == 0) {
                            DAT_TileMapState::instance.CertainPathLayer[_newTile]
                                = (short)this->searchQueue.currentDistance + 1;
                            DAT_TileMapState::instance.WalkLayer[_newTile] = (short)this->searchGeneration;
                            this->searchQueue.xQueue[this->searchQueue.writeIndex]
                                = ((Point8ShortXY*)(psVar2 + -2))->xOffset + _x;
                            this->searchQueue.yQueue[this->searchQueue.writeIndex] = *psVar2 + _y;
                            this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = _newTile;
                            this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                            if (80400 < this->searchQueue.writeIndex) {
                                this->searchQueue.writeIndex = 0;
                            }
                        }
                        psVar2 = psVar2 + 8;
                        paiVar3 = (int (*)[8])(*paiVar3 + 2);
                    } while ((int)psVar2 < 0xb4908c);
                    this->searchQueue.readIndex = this->searchQueue.readIndex + 1;
                    if (80400 < this->searchQueue.readIndex) {
                        this->searchQueue.readIndex = 0;
                    }
                    if (this->searchQueue.readIndex == this->searchQueue.writeIndex)
                        break;
                }
            }
            if (keepRange != -1
                && (iVar1 = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::isTileInRangeOfKeepRange,
                        this)(playerID, (uint)(x), (uint)(y), keepRange),
                    iVar1 != 0)) {
                return (undefined4)(1);
            }
            return (undefined4)(0);
        }

    }
}
}
