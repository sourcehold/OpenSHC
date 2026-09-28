#include "../PathFindingState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Map/Location/Point8ShortXY.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        using OpenSHC::Game::GameMode;
        using OpenSHC::Map::Location::Point8ShortXY;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
         */
        /*
          WARNING: Enum "DPERRInt": Some values do not have unique names
         */
        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004A1230
        void PathFindingState::aggressiveStanceTargetBuildingAtRange(int unitID, int maxDistance)
        {
            int (*paiVar4)[8];
            uint uVar5;
            short* psVar6;
            uint uVar7;
            int _nextCandidate;
            int _tile;
            short sVar1 = DAT_UnitsState::instance.units[unitID].x;
            uVar5 = (uint)sVar1;
            short sVar2 = DAT_UnitsState::instance.units[unitID].y;
            uVar7 = (uint)sVar2;
            this->calculations = this->calculations + 1;
            this->ALG_ResultTile = 0;
            this->ALG_ResultY = 0;
            this->ALG_ResultX = 0;
            if (uVar5 <= 399 && uVar7 <= 399 && DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[uVar7 * 400 + uVar5] != '\0') {
                this->searchGeneration = this->searchGeneration + 1;
                if (32000 < this->searchGeneration) {
                    this->searchGeneration = 1;
                    MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                        0x27420, '\0', (void*)((int)(DAT_TileMapState::instance.WalkLayer)));
                }
                this->searchQueue.currentDistance = 1;
                this->searchQueue.writeIndex = 1;
                this->searchQueue.readIndex = 0;
                this->searchQueue.tilesQueue[0]
                    = DAT_ViewportRenderState::instance.translationMatrix[uVar7].addXgetTile + uVar5;
                this->searchQueue.yQueue[0] = sVar2;
                this->searchQueue.xQueue[0] = sVar1;
                DAT_TileMapState::instance.CertainPathLayer[this->searchQueue.tilesQueue[0]] = 1;
                DAT_TileMapState::instance.WalkLayer[this->searchQueue.tilesQueue[0]] = (short)this->searchGeneration;
                if ((DAT_TileMapState::instance.LogicLayer[this->searchQueue.tilesQueue[0]] & 0x30) == 0
                    && this->searchQueue.readIndex != this->searchQueue.writeIndex) {
                    while ((_tile = this->searchQueue.tilesQueue[this->searchQueue.readIndex],
                        -1 < _tile && (_tile < 0x13a10))) {
                        sVar1 = this->searchQueue.xQueue[this->searchQueue.readIndex];
                        sVar2 = this->searchQueue.yQueue[this->searchQueue.readIndex];
                        this->searchQueue.currentDistance = (int)DAT_TileMapState::instance.CertainPathLayer[_tile];
                        if (0x13a10 < this->searchQueue.currentDistance) {
                            return;
                        }
                        if (this->searchQueue.currentDistance > maxDistance) {
                            return;
                        }
                        paiVar4 = DAT_TileMapState::instance.directionTranslationMatrix + sVar2;
                        psVar6 = &DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[0].short_.yOffset;
                        do {
                            _nextCandidate = (*paiVar4)[0] + _tile;
                            uVar5 = DAT_TileMapState::instance.LogicLayer[_nextCandidate];
                            if (DAT_TileMapState::instance.WalkLayer[_nextCandidate] != this->searchGeneration) {
                                if (DAT_TileMapState::instance.BuildingLayer[_nextCandidate] == 0) {
                                    /*
                                      Is wall or gatehouseIs wall or gatehouse
                                     */
                                    /*
                                      TODO:FIXME: WallOwnerLayer contains player ids, not necessarily team ids
                                     */
                                    if ((uVar5 & 0x100) != 0
                                        && (DAT_GameSynchronyState::instance.currentGameMode
                                                == OpenSHC::Game::GM_SOLITARY
                                            || (DAT_GameState::instance.mapAndTime.skirmishStrongWalls == 0))
                                        && DAT_GameState::instance.mapAndTime.playerTeams
                                                [(DAT_TileMapState::instance.WallOwnerLayer[_nextCandidate] & 7) + 1]
                                            != DAT_GameState::instance.mapAndTime
                                                .playerTeams[DAT_UnitsState::instance.units[unitID].owner]) {
                                        this->ALG_ResultTile = _nextCandidate;
                                        return;
                                    }
                                } else {
                                    uVar7 = (uint)DAT_TileMapState::instance.BuildingLayer[_nextCandidate];
                                    if (DAT_GameState::instance.mapAndTime
                                            .playerTeams[DAT_UnitsState::instance.units[unitID].owner]
                                        != DAT_GameState::instance.mapAndTime
                                            .playerTeams[DAT_BuildingsState::instance.buildings[uVar7].owner]) {
                                        switch (DAT_BuildingsState::instance.buildings[uVar7].buildingType) {
                                        case OpenSHC::Map::Buildings::BT_STOCKPILE:
                                        case OpenSHC::Map::Buildings::BT_MANORHOUSE:
                                        case OpenSHC::Map::Buildings::BT_STONEKEEP:
                                        case OpenSHC::Map::Buildings::BT_STRONGHOLD:
                                        case OpenSHC::Map::Buildings::BT_CAMPFIRE:
                                        case OpenSHC::Map::Buildings::BT_SIGNPOST:
                                        case OpenSHC::Map::Buildings::BT_PARADEGROUND:
                                        case OpenSHC::Map::Buildings::BT_CAMPGROUND:
                                        case OpenSHC::Map::Buildings::BT_PARADEGROUND2:
                                        case OpenSHC::Map::Buildings::BT_PARADEGROUND3:
                                        case OpenSHC::Map::Buildings::BT_PARADEGROUND4:
                                        case OpenSHC::Map::Buildings::BT_PARADEGROUND5:
                                        case OpenSHC::Map::Buildings::BT_KILLINGPIT:
                                        case OpenSHC::Map::Buildings::BT_KEEPDOOR_LEFT:
                                        case OpenSHC::Map::Buildings::BT_KEEPDOOR_RIGHT:
                                        case OpenSHC::Map::Buildings::BT_KEEPDOOR:
                                            break;
                                        default:
                                            BOOLEnum BVar3
                                                = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::
                                                                        getBuildingHasHealthProperty,
                                                    DAT_BuildingsState::ptr)(uVar7, _nextCandidate);
                                            if (BVar3 != FALSE) {
                                                this->ALG_ResultTile = _nextCandidate;
                                                return;
                                            }
                                        }
                                    }
                                }
                                if ((uVar5 & 0x30) == 0) {
                                    /*
                                      If not the border, enqueue next candidate
                                     */
                                    DAT_TileMapState::instance.CertainPathLayer[_nextCandidate]
                                        = (short)this->searchQueue.currentDistance + 1;
                                    DAT_TileMapState::instance.WalkLayer[_nextCandidate]
                                        = (short)this->searchGeneration;
                                    this->searchQueue.xQueue[this->searchQueue.writeIndex]
                                        = ((Point8ShortXY*)(psVar6 + -2))->xOffset + sVar1;
                                    this->searchQueue.yQueue[this->searchQueue.writeIndex] = *psVar6 + sVar2;
                                    this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = _nextCandidate;
                                    this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                                    if (0x13a0f < this->searchQueue.writeIndex) {
                                        this->searchQueue.writeIndex = 0;
                                    }
                                }
                            }
                            paiVar4 = (int (*)[8])(*paiVar4 + 2);
                            psVar6 = psVar6 + 8;
                        } while ((int)psVar6 < 0xb4908c);
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
