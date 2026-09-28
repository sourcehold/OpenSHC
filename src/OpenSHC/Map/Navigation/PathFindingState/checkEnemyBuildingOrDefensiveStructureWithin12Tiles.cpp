#include "../PathFindingState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Map/Buildings/BuildingTypeShort.hpp"
#include "OpenSHC/Map/Location/Point8ShortXY.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        using OpenSHC::Map::Buildings::BuildingType;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;
            using OpenSHC::Map::Buildings::BuildingTypeShort;
            using OpenSHC::Map::Location::Point8ShortXY;

        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x0049DB30
        BOOLEnum PathFindingState::checkEnemyBuildingOrDefensiveStructureWithin12Tiles(int playerID, uint x, uint y)
        {
            int _candidate;
            short* psVar1;
            int (*paiVar2)[8];
            bool bVar3;
            short _building;
            BuildingTypeShort _buildingType;
            int _tile;
            short _x;
            short _y;
            if (((399 < x) || (399 < y)) || (*(char*)(y * 400 + 0x21aec98 + x) == '\0')) {
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
            bVar3 = this->searchQueue.readIndex == this->searchQueue.writeIndex;
            while (true) {
                if (bVar3) {
                    return FALSE;
                }
                _tile = this->searchQueue.tilesQueue[this->searchQueue.readIndex];
                if (_tile < 0) {
                    return FALSE;
                }
                if (0x13a0f < _tile) {
                    return FALSE;
                }
                _x = this->searchQueue.xQueue[this->searchQueue.readIndex];
                _y = this->searchQueue.yQueue[this->searchQueue.readIndex];
                _building = DAT_TileMapState::instance.BuildingLayer[_tile];
                if (_building != 0) {
                    _buildingType = DAT_BuildingsState::instance.buildings[_building].buildingType;
                    /*
                      find enemy building
                     */
                    if (((_buildingType != OpenSHC::Map::Buildings::BT_PITCHDITCH)
                            && (_buildingType != OpenSHC::Map::Buildings::BT_KILLINGPIT))
                        && (DAT_GameState::instance.mapAndTime
                                .playerTeams[DAT_BuildingsState::instance.buildings[_building].owner]
                            != DAT_GameState::instance.mapAndTime.playerTeams[playerID])) {
                        return TRUE;
                    }
                }
                /*
                  find enemy wall tower or gatehouse
                 */
                if (((DAT_TileMapState::instance.LogicLayer[_tile] & 0x100U) != 0)
                    && (DAT_GameState::instance.mapAndTime
                            .playerTeams[(DAT_TileMapState::instance.WallOwnerLayer[_tile] & 7) + 1]
                        != DAT_GameState::instance.mapAndTime.playerTeams[playerID])) {
                    return TRUE;
                }
                this->searchQueue.currentDistance = (int)DAT_TileMapState::instance.CertainPathLayer[_tile];
                if (0x13a10 < this->searchQueue.currentDistance) {
                    return FALSE;
                }
                if (12 < this->searchQueue.currentDistance)
                    break;
                psVar1 = &DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[0].short_.yOffset;
                paiVar2 = DAT_TileMapState::instance.directionTranslationMatrix + _y;
                do {
                    _candidate = (*paiVar2)[0] + _tile;
                    if (DAT_TileMapState::instance.WalkLayer[_candidate] != this->searchGeneration) {
                        DAT_TileMapState::instance.CertainPathLayer[_candidate]
                            = (short)this->searchQueue.currentDistance + 1;
                        DAT_TileMapState::instance.WalkLayer[_candidate] = (short)this->searchGeneration;
                        this->searchQueue.xQueue[this->searchQueue.writeIndex]
                            = ((Point8ShortXY*)(psVar1 + -2))->xOffset + _x;
                        this->searchQueue.yQueue[this->searchQueue.writeIndex] = *psVar1 + _y;
                        this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = _candidate;
                        this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                        if (0x13a0f < this->searchQueue.writeIndex) {
                            this->searchQueue.writeIndex = 0;
                        }
                    }
                    psVar1 = psVar1 + 8;
                    paiVar2 = (int (*)[8])(*paiVar2 + 2);
                } while ((int)psVar1 < 0xb4908c);
                this->searchQueue.readIndex = this->searchQueue.readIndex + 1;
                if (0x13a0f < this->searchQueue.readIndex) {
                    this->searchQueue.readIndex = 0;
                }
                bVar3 = this->searchQueue.readIndex == this->searchQueue.writeIndex;
            }
            return FALSE;
        }

    }
}
}
