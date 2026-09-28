#include "../PathFindingState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Location/Point8ShortXY.hpp"

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
        // FUNCTION: STRONGHOLDCRUSADER 0x0049B5B0
        void PathFindingState::algTunnelerFindTarget(
            int playerID, int targetPlayerID, int distance, int originX, int originY)
        {
            int iVar4;
            uint uVar5;
            short* psVar6;
            int iVar7;
            int (*paiVar8)[8];
            this->calculations = this->calculations + 1;
            MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                0x27420, '\0', (void*)((int)(DAT_TileMapState::instance.CertainPathLayer)));
            this->ALG_TargetTile = 0;
            this->ALG_TargetY = 0;
            this->ALG_TargetX = 0;
            if ((uint)originX < 400 && (uint)originY < 400 && *(char*)(originY * 400 + 0x21aec98 + originX) != '\0') {
                this->searchGeneration = this->searchGeneration + 1;
                if (32000 < this->searchGeneration) {
                    this->searchGeneration = 1;
                    MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                        0x27420, '\0', (void*)((int)(DAT_TileMapState::instance.WalkLayer)));
                }
                this->searchQueue.readIndex = 0;
                this->searchQueue.writeIndex = 1;
                this->searchQueue.currentDistance = 1;
                this->searchQueue.yQueue[0] = (short)originY;
                this->searchQueue.xQueue[0] = (short)originX;
                this->searchQueue.tilesQueue[0]
                    = DAT_ViewportRenderState::instance.translationMatrix[originY].addXgetTile + originX;
                DAT_TileMapState::instance.CertainPathLayer[this->searchQueue.tilesQueue[0]] = 1;
                DAT_TileMapState::instance.WalkLayer[this->searchQueue.tilesQueue[0]] = (short)this->searchGeneration;
                if (this->searchQueue.readIndex != this->searchQueue.writeIndex) {
                    while ((iVar4 = this->searchQueue.tilesQueue[this->searchQueue.readIndex],
                        -1 < iVar4 && (iVar4 < 0x13a10))) {
                        int sVar1 = (int)this->searchQueue.xQueue[this->searchQueue.readIndex];
                        int sVar2 = (int)this->searchQueue.yQueue[this->searchQueue.readIndex];
                        iVar7 = (int)sVar2;
                        if ((DAT_TileMapState::instance.LogicLayer[iVar4] & 0x100U) != 0
                            && (DAT_TileMapState::instance.LogicLayer[iVar4] & 2U) == 0) {
                            uVar5 = DAT_TileMapState::instance.WallOwnerLayer[iVar4] & 7;
                            if (((targetPlayerID == 0) || (targetPlayerID == uVar5 + 1))
                                && DAT_GameState::instance.mapAndTime.playerTeams[playerID]
                                    != DAT_GameState::instance.mapAndTime.playerTeams[uVar5 + 1]) {
                                this->ALG_TargetX = (int)sVar1;
                                this->ALG_TargetY = iVar7;
                                this->ALG_TargetTile = iVar4;
                                return;
                            }
                        }
                        short sVar3 = DAT_TileMapState::instance.BuildingLayer[iVar4];
                        if (sVar3 != 0
                            && (targetPlayerID == 0
                                || (targetPlayerID == DAT_BuildingsState::instance.buildings[sVar3].owner))
                            && DAT_GameState::instance.mapAndTime.playerTeams[playerID]
                                != DAT_GameState::instance.mapAndTime
                                    .playerTeams[DAT_BuildingsState::instance.buildings[sVar3].owner]) {
                            this->ALG_TargetX = (int)sVar1;
                            this->ALG_TargetY = iVar7;
                            this->ALG_TargetTile = iVar4;
                            return;
                        }
                        this->searchQueue.currentDistance = (int)DAT_TileMapState::instance.CertainPathLayer[iVar4];
                        if (distance < this->searchQueue.currentDistance) {
                            return;
                        }
                        paiVar8 = DAT_TileMapState::instance.directionTranslationMatrix + iVar7;
                        psVar6 = &DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[0].short_.yOffset;
                        do {
                            iVar7 = (*paiVar8)[0] + iVar4;
                            uVar5 = DAT_TileMapState::instance.LogicLayer[iVar7];
                            if (DAT_TileMapState::instance.WalkLayer[iVar7] != this->searchGeneration
                                && (uVar5 & 0xb1) == 0 && (uVar5 & 0x301000) == 0
                                && (DAT_TileMapState::instance.BuildingLayer[iVar7] == 0
                                    || ((int)(short)DAT_BuildingsState::instance
                                                .buildings[DAT_TileMapState::instance.BuildingLayer[iVar7]]
                                                .buildingType
                                            - 0x4aU
                                        < 3))
                                && (uVar5 & 0x40000000) == 0) {
                                DAT_TileMapState::instance.CertainPathLayer[iVar7]
                                    = (short)this->searchQueue.currentDistance + 1;
                                DAT_TileMapState::instance.WalkLayer[iVar7] = (short)this->searchGeneration;
                                this->searchQueue.xQueue[this->searchQueue.writeIndex]
                                    = ((Point8ShortXY*)(psVar6 + -2))->xOffset + sVar1;
                                this->searchQueue.yQueue[this->searchQueue.writeIndex] = *psVar6 + sVar2;
                                this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = iVar7;
                                this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                                if (80400 < this->searchQueue.writeIndex) {
                                    this->searchQueue.writeIndex = 0;
                                }
                            }
                            psVar6 = psVar6 + 8;
                            paiVar8 = (int (*)[8])(*paiVar8 + 2);
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
