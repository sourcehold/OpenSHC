#include "../PathFindingState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Units/TroopValueState.func.hpp"

#include "OpenSHC/Globals/DAT_ClimbLogicDefinedData.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        // FUNCTION: STRONGHOLDCRUSADER 0x0049C690
        void PathFindingState::computeTotalUnitsWithinDistance(
            int playerID, int sameTeamUnits, int someLogicalTileProperty, int tile, int distance)
        {
            uint uVar4;
            this->calculations = this->calculations + 1;
            this->searchGeneration = this->searchGeneration + 1;
            this->ALGO_TotalTroopValue = 0;
            this->ALGO_TotalTroopCount = 0;
            this->field_0x64 = 0;
            if (32000 < this->searchGeneration) {
                this->searchGeneration = 1;
                MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                    0x27420, '\0', (void*)((int)(DAT_TileMapState::instance.WalkLayer)));
            }
            this->searchQueue.readIndex = 0;
            this->searchQueue.writeIndex = 1;
            this->searchQueue.currentDistance = 1;
            this->searchQueue.yQueue[0]
                = (short)DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile];
            this->searchQueue.tilesQueue[0] = tile;
            DAT_TileMapState::instance.WalkLayer[this->searchQueue.tilesQueue[0]] = (short)this->searchGeneration;
            DAT_TileMapState::instance.CertainPathLayer[tile] = 1;
            if (this->searchQueue.readIndex != this->searchQueue.writeIndex) {
                while (uVar4 = this->searchQueue.tilesQueue[this->searchQueue.readIndex], uVar4 <= 0x13a0f) {
                    int y = (int)this->searchQueue.yQueue[this->searchQueue.readIndex];
                    for (int unitID = DAT_TileMapState::instance.UnitLayer[uVar4]; unitID != 0;
                        unitID = DAT_UnitsState::instance.units[unitID].nextUnitOnTheSameTile) {
                        // sameTeamUnits 1 counts the player's team, 0 every other team, anything else all units
                        if (sameTeamUnits == 1) {
                            if (DAT_GameState::instance.mapAndTime.playerTeams[playerID]
                                != DAT_GameState::instance.mapAndTime
                                    .playerTeams[DAT_UnitsState::instance.units[unitID].owner]) {
                                continue;
                            }
                        } else if (sameTeamUnits == 0
                            && DAT_GameState::instance.mapAndTime.playerTeams[playerID]
                                == DAT_GameState::instance.mapAndTime
                                    .playerTeams[DAT_UnitsState::instance.units[unitID].owner]) {
                            continue;
                        }
                        if (DAT_UnitsState::instance.units[unitID].owner == 0
                            || DAT_UnitsState::instance.units[unitID].dying != 0) {
                            continue;
                        }
                        int const troopValue = MACRO_CALL_MEMBER(
                            OpenSHC::Map::Units::TroopValueState_Func::getValueOfTroopType, DAT_TroopValueState::ptr)(
                            (OpenSHC::Map::Units::UnitType)(int)(short)DAT_UnitsState::instance.units[unitID].unitType);
                        this->ALGO_TotalTroopValue = this->ALGO_TotalTroopValue + troopValue;
                        this->ALGO_TotalTroopCount = this->ALGO_TotalTroopCount + 1;
                        if (this->field_0x64 == 0) {
                            this->field_0x64 = unitID;
                        }
                    }
                    this->searchQueue.currentDistance = (int)DAT_TileMapState::instance.CertainPathLayer[uVar4];
                    if (0x13a10 < (int)this->searchQueue.currentDistance) {
                        return;
                    }
                    if ((int)this->searchQueue.currentDistance > distance) {
                        return;
                    }
                    byte const pathLinkage = DAT_TileMapState::instance.PathLinkageLayer[uVar4];
                    for (int direction = 0; direction < 8; ++direction) {
                        int const neighbour
                            = DAT_TileMapState::instance.directionTranslationMatrix[y][direction] + uVar4;
                        if (DAT_TileMapState::instance.WalkLayer[neighbour] != this->searchGeneration) {
                            if ((someLogicalTileProperty == 0
                                    && (DAT_TileMapState::instance.LogicLayer[neighbour] & 0x30) == 0)
                                || (someLogicalTileProperty != 0
                                    && (DAT_ClimbLogicDefinedData::instance.BitFlagHelperForPathLinkage[direction]
                                           & pathLinkage)
                                        != 0)) {
                                DAT_TileMapState::instance.CertainPathLayer[neighbour]
                                    = (short)this->searchQueue.currentDistance + 1;
                                DAT_TileMapState::instance.WalkLayer[neighbour] = (short)this->searchGeneration;
                                this->searchQueue.yQueue[this->searchQueue.writeIndex]
                                    = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[direction]
                                          .short_.yOffset
                                    + y;
                                this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = neighbour;
                                this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                                if (0x13a10 <= (int)this->searchQueue.writeIndex) {
                                    this->searchQueue.writeIndex = 0;
                                }
                            }
                        }
                    }
                    this->searchQueue.readIndex = this->searchQueue.readIndex + 1;
                    if (0x13a10 <= (int)this->searchQueue.readIndex) {
                        this->searchQueue.readIndex = 0;
                    }
                    if (this->searchQueue.readIndex == this->searchQueue.writeIndex) {
                        return;
                    }
                }
            }
            return;
        }

    }
}
}
