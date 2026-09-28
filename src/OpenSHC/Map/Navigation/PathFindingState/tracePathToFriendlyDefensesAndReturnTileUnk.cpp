#include "../PathFindingState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_ClimbLogicDefinedData.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
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
        // FUNCTION: STRONGHOLDCRUSADER 0x004A16C0
        int PathFindingState::tracePathToFriendlyDefensesAndReturnTileUnk(int playerID, uint x, uint y)
        {
            byte bVar1;
            short sVar2;
            short sVar3;
            short sVar4;
            int iVar5;
            int iVar6;
            int (*paiVar7)[8];
            int _candidateTile;
            if (((399 < x) || (399 < y)) || (*(char*)(y * 400 + 0x21aec98 + x) == '\0')) {
                return 0;
            }
            this->calculations = this->calculations + 1;
            this->searchGeneration = this->searchGeneration + 1;
            if (32000 < this->searchGeneration) {
                this->searchGeneration = 1;
                MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                    160800, '\0', (void*)((int)(DAT_TileMapState::instance.WalkLayer)));
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
                    _candidateTile = this->searchQueue.tilesQueue[this->searchQueue.readIndex];
                    if (_candidateTile < 0) {
                        return 0;
                    }
                    if (0x13a0f < _candidateTile) {
                        return 0;
                    }
                    sVar2 = this->searchQueue.xQueue[this->searchQueue.readIndex];
                    sVar3 = this->searchQueue.yQueue[this->searchQueue.readIndex];
                    this->searchQueue.currentDistance
                        = (int)DAT_TileMapState::instance.CertainPathLayer[_candidateTile];
                    if (0x13a10 < this->searchQueue.currentDistance) {
                        return 0;
                    }
                    bVar1 = DAT_TileMapState::instance.PathLinkageLayer[_candidateTile];
                    iVar6 = 0;
                    paiVar7 = DAT_TileMapState::instance.directionTranslationMatrix + sVar3;
                    do {
                        iVar5 = (*paiVar7)[0] + _candidateTile;
                        if ((DAT_TileMapState::instance.WalkLayer[iVar5] != this->searchGeneration)
                            && ((DAT_TileMapState::instance.LogicLayer[iVar5] & 0x30) == 0)) {
                            if ((DAT_ClimbLogicDefinedData::instance.BitFlagHelperForPathLinkage[iVar6] & bVar1) == 0) {
                                sVar4 = DAT_TileMapState::instance.BuildingLayer[iVar5];
                                if (sVar4 != 0) {
                                    switch (DAT_BuildingsState::instance.buildings[sVar4].buildingType) {
                                    case OpenSHC::Map::Buildings::BT_MERCENARYPOST:
                                    case OpenSHC::Map::Buildings::BT_BARRACKS:
                                    case OpenSHC::Map::Buildings::BT_MANORHOUSE:
                                    case OpenSHC::Map::Buildings::BT_STONEKEEP:
                                    case OpenSHC::Map::Buildings::BT_STRONGHOLD:
                                    case OpenSHC::Map::Buildings::BT_KEEPFOUR:
                                    case OpenSHC::Map::Buildings::BT_KEEPFIVE:
                                    case OpenSHC::Map::Buildings::BT_GATEHOUSELARGE:
                                    case OpenSHC::Map::Buildings::BT_GATEHOUSESMALL:
                                    case OpenSHC::Map::Buildings::BT_TOWER1:
                                    case OpenSHC::Map::Buildings::BT_TOWER2:
                                    case OpenSHC::Map::Buildings::BT_TOWER3:
                                    case OpenSHC::Map::Buildings::BT_TOWER4:
                                    case OpenSHC::Map::Buildings::BT_TOWER5:
                                        if (DAT_GameState::instance.mapAndTime
                                                .playerTeams[DAT_BuildingsState::instance.buildings[sVar4].owner]
                                            == DAT_GameState::instance.mapAndTime.playerTeams[playerID]) {
                                            return _candidateTile;
                                        }
                                    }
                                }
                            } else {
                                DAT_TileMapState::instance.CertainPathLayer[iVar5]
                                    = (short)this->searchQueue.currentDistance + 1;
                                DAT_TileMapState::instance.WalkLayer[iVar5] = (short)this->searchGeneration;
                                this->searchQueue.xQueue[this->searchQueue.writeIndex]
                                    = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[iVar6]
                                          .short_.xOffset
                                    + sVar2;
                                this->searchQueue.yQueue[this->searchQueue.writeIndex]
                                    = *(short*)((int)DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix
                                          + iVar6 * 8 + 4)
                                    + sVar3;
                                this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = iVar5;
                                this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                                if (0x13a0f < this->searchQueue.writeIndex) {
                                    this->searchQueue.writeIndex = 0;
                                }
                            }
                        }
                        iVar6 = iVar6 + 1;
                        paiVar7 = (int (*)[8])(*paiVar7 + 1);
                    } while (iVar6 < 8);
                    this->searchQueue.readIndex = this->searchQueue.readIndex + 1;
                    if (0x13a0f < this->searchQueue.readIndex) {
                        this->searchQueue.readIndex = 0;
                    }
                } while (this->searchQueue.readIndex != this->searchQueue.writeIndex);
            }
            return 0;
        }

    }
}
}
