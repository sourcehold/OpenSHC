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

        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x0049C690
        void PathFindingState::computeTotalUnitsWithinDistance(
            int playerID, int sameTeamUnits, int someLogicalTileProperty, int tile, int distance)
        {
            uint uVar4;
            int iVar5;
            int iVar6;
            int* piVar7;
            this->calculations = this->calculations + 1;
            this->searchGeneration = this->searchGeneration + 1;
            this->ALGO_TotalTroopValue = 0;
            this->ALGO_TotalTroopCount = 0;
            this->field34_0x64 = 0;
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
            DAT_TileMapState::instance.CertainPathLayer[tile] = 1;
            DAT_TileMapState::instance.WalkLayer[this->searchQueue.tilesQueue[0]] = (short)this->searchGeneration;
            if (this->searchQueue.readIndex != this->searchQueue.writeIndex) {
                while (uVar4 = this->searchQueue.tilesQueue[this->searchQueue.readIndex], uVar4 < 0x13a10) {
                    int sVar3 = (int)this->searchQueue.yQueue[this->searchQueue.readIndex];
                    int uVar2 = (short)DAT_TileMapState::instance.UnitLayer[uVar4];
                    while (iVar6 = (int)(short)uVar2, iVar6 != 0) {
                        if (sameTeamUnits == 1) {
                            if (DAT_GameState::instance.mapAndTime.playerTeams[playerID]
                                == DAT_GameState::instance.mapAndTime
                                    .playerTeams[DAT_UnitsState::instance.units[iVar6].owner]) {
                            LAB_0049c7ba:
                                if ((DAT_UnitsState::instance.units[iVar6].owner != 0)
                                    && (DAT_UnitsState::instance.units[iVar6].dying == 0)) {
                                    iVar5 = MACRO_CALL_MEMBER(
                                        OpenSHC::Map::Units::TroopValueState_Func::getValueOfTroopType,
                                        DAT_TroopValueState::ptr)(
                                        (OpenSHC::Map::Units::UnitType)(int)(short)DAT_UnitsState::instance.units[iVar6]
                                            .unitType);
                                    this->ALGO_TotalTroopValue = this->ALGO_TotalTroopValue + iVar5;
                                    this->ALGO_TotalTroopCount = this->ALGO_TotalTroopCount + 1;
                                    if (this->field34_0x64 == 0) {
                                        this->field34_0x64 = iVar6;
                                    }
                                }
                            }
                        } else if ((sameTeamUnits != 0)
                            || (DAT_GameState::instance.mapAndTime.playerTeams[playerID]
                                != DAT_GameState::instance.mapAndTime
                                    .playerTeams[DAT_UnitsState::instance.units[iVar6].owner]))
                            goto LAB_0049c7ba;
                        uVar2 = DAT_UnitsState::instance.units[iVar6].nextUnitOnTheSameTile;
                    }
                    this->searchQueue.currentDistance = (int)DAT_TileMapState::instance.CertainPathLayer[uVar4];
                    if (0x13a10 < this->searchQueue.currentDistance) {
                        return;
                    }
                    if (this->searchQueue.currentDistance > distance) {
                        return;
                    }
                    byte bVar1 = DAT_TileMapState::instance.PathLinkageLayer[uVar4];
                    iVar6 = 0;
                    piVar7 = DAT_TileMapState::instance.directionTranslationMatrix[sVar3] + 1;
                    do {
                        iVar5 = (*(int (*)[8])(piVar7 + -1))[0] + uVar4;
                        if (DAT_TileMapState::instance.WalkLayer[iVar5] != this->searchGeneration) {
                            if (someLogicalTileProperty == 0) {
                                if ((DAT_TileMapState::instance.LogicLayer[iVar5] & 0x30) == 0)
                                    goto LAB_0049c880;
                            } else if ((DAT_ClimbLogicDefinedData::instance.BitFlagHelperForPathLinkage[iVar6] & bVar1)
                                != 0) {
                            LAB_0049c880:
                                DAT_TileMapState::instance.CertainPathLayer[iVar5]
                                    = (short)this->searchQueue.currentDistance + 1;
                                DAT_TileMapState::instance.WalkLayer[iVar5] = (short)this->searchGeneration;
                                this->searchQueue.yQueue[this->searchQueue.writeIndex]
                                    = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[iVar6]
                                          .short_.yOffset
                                    + sVar3;
                                this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = iVar5;
                                this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                                if (80400 < this->searchQueue.writeIndex) {
                                    this->searchQueue.writeIndex = 0;
                                }
                            }
                        }
                        iVar5 = *piVar7 + uVar4;
                        if (DAT_TileMapState::instance.WalkLayer[iVar5] != this->searchGeneration) {
                            if (someLogicalTileProperty == 0) {
                                if ((DAT_TileMapState::instance.LogicLayer[iVar5] & 0x30) == 0)
                                    goto LAB_0049c918;
                            } else if ((DAT_ClimbLogicDefinedData::instance.BitFlagHelperForPathLinkage[iVar6 + 1]
                                           & bVar1)
                                != 0) {
                            LAB_0049c918:
                                DAT_TileMapState::instance.CertainPathLayer[iVar5]
                                    = (short)this->searchQueue.currentDistance + 1;
                                DAT_TileMapState::instance.WalkLayer[iVar5] = (short)this->searchGeneration;
                                this->searchQueue.yQueue[this->searchQueue.writeIndex]
                                    = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[iVar6 + 1]
                                          .short_.yOffset
                                    + sVar3;
                                this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = iVar5;
                                this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                                if (0x13a0f < this->searchQueue.writeIndex) {
                                    this->searchQueue.writeIndex = 0;
                                }
                            }
                        }
                        iVar5 = piVar7[1] + uVar4;
                        if (DAT_TileMapState::instance.WalkLayer[iVar5] != this->searchGeneration) {
                            if (someLogicalTileProperty == 0) {
                                if ((DAT_TileMapState::instance.LogicLayer[iVar5] & 0x30) == 0)
                                    goto LAB_0049c9b1;
                            } else if ((DAT_ClimbLogicDefinedData::instance.BitFlagHelperForPathLinkage[iVar6 + 2]
                                           & bVar1)
                                != 0) {
                            LAB_0049c9b1:
                                DAT_TileMapState::instance.CertainPathLayer[iVar5]
                                    = (short)this->searchQueue.currentDistance + 1;
                                DAT_TileMapState::instance.WalkLayer[iVar5] = (short)this->searchGeneration;
                                this->searchQueue.yQueue[this->searchQueue.writeIndex]
                                    = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[iVar6 + 2]
                                          .short_.yOffset
                                    + sVar3;
                                this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = iVar5;
                                this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                                if (0x13a0f < this->searchQueue.writeIndex) {
                                    this->searchQueue.writeIndex = 0;
                                }
                            }
                        }
                        iVar5 = piVar7[2] + uVar4;
                        if (DAT_TileMapState::instance.WalkLayer[iVar5] != this->searchGeneration) {
                            if (someLogicalTileProperty == 0) {
                                if ((DAT_TileMapState::instance.LogicLayer[iVar5] & 0x30) == 0)
                                    goto LAB_0049ca4a;
                            } else if ((DAT_ClimbLogicDefinedData::instance.BitFlagHelperForPathLinkage[iVar6 + 3]
                                           & bVar1)
                                != 0) {
                            LAB_0049ca4a:
                                DAT_TileMapState::instance.CertainPathLayer[iVar5]
                                    = (short)this->searchQueue.currentDistance + 1;
                                DAT_TileMapState::instance.WalkLayer[iVar5] = (short)this->searchGeneration;
                                this->searchQueue.yQueue[this->searchQueue.writeIndex]
                                    = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[iVar6 + 3]
                                          .short_.yOffset
                                    + sVar3;
                                this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = iVar5;
                                this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                                if (0x13a0f < this->searchQueue.writeIndex) {
                                    this->searchQueue.writeIndex = 0;
                                }
                            }
                        }
                        iVar6 = iVar6 + 4;
                        piVar7 = piVar7 + 4;
                    } while (iVar6 < 8);
                    this->searchQueue.readIndex = this->searchQueue.readIndex + 1;
                    if (0x13a0f < this->searchQueue.readIndex) {
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
