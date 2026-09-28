#include "../PathFindingState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/Buildings/BuildingTypeShort.hpp"
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

        using OpenSHC::Map::Buildings::BuildingType;
        using OpenSHC::Map::Buildings::BuildingTypeShort;
        using OpenSHC::Map::Location::Point8ShortXY;

        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004A1D30
        undefined4 PathFindingState::findSomeSuitableLocationUnk(int param_1, uint x, uint y, int param_4)
        {
            int iVar5;
            short* psVar6;
            int* piVar7;
            int iVar8;
            if (399 < x || 399 < y || DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y * 400 + x] == '\0') {
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
                while ((iVar5 = this->searchQueue.tilesQueue[this->searchQueue.readIndex],
                    -1 < iVar5 && (iVar5 < 0x13a10))) {
                    int sVar1 = (int)this->searchQueue.xQueue[this->searchQueue.readIndex];
                    int sVar2 = (int)this->searchQueue.yQueue[this->searchQueue.readIndex];
                    this->searchQueue.currentDistance = (int)DAT_TileMapState::instance.CertainPathLayer[iVar5];
                    if (0x13a10 < this->searchQueue.currentDistance) {
                        return (undefined4)(0);
                    }
                    if (param_4 < this->searchQueue.currentDistance) {
                        return (undefined4)(0);
                    }
                    short sVar3 = DAT_TileMapState::instance.BuildingLayer[iVar5];
                    if (sVar3 != 0) {
                        BuildingTypeShort BVar4 = DAT_BuildingsState::instance.buildings[sVar3].buildingType;
                        if (BVar4 != OpenSHC::Map::Buildings::BT_QUARRY
                            && BVar4 != OpenSHC::Map::Buildings::BT_KILLINGPIT
                            && DAT_GameState::instance.mapAndTime
                                    .playerTeams[DAT_BuildingsState::instance.buildings[sVar3].owner]
                                != DAT_GameState::instance.mapAndTime.playerTeams[param_1]) {
                            return (undefined4)(1);
                        }
                    }
                    if ((DAT_TileMapState::instance.LogicLayer[iVar5] & 0x100U) != 0
                        && (DAT_TileMapState::instance.LogicLayer[iVar5] & 2U) == 0
                        && DAT_GameState::instance.mapAndTime
                                .playerTeams[(DAT_TileMapState::instance.WallOwnerLayer[iVar5] & 7) + 1]
                            != DAT_GameState::instance.mapAndTime.playerTeams[param_1]) {
                        return (undefined4)(1);
                    }
                    piVar7 = DAT_TileMapState::instance.directionTranslationMatrix[sVar2] + 1;
                    psVar6 = &DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[0].short_.yOffset;
                    do {
                        iVar8 = (*(int (*)[8])(piVar7 + -1))[0] + iVar5;
                        if (DAT_TileMapState::instance.WalkLayer[iVar8] != this->searchGeneration
                            && (DAT_TileMapState::instance.LogicLayer[iVar8] & 0x30) == 0) {
                            DAT_TileMapState::instance.CertainPathLayer[iVar8]
                                = (short)this->searchQueue.currentDistance + 1;
                            DAT_TileMapState::instance.WalkLayer[iVar8] = (short)this->searchGeneration;
                            this->searchQueue.xQueue[this->searchQueue.writeIndex]
                                = ((Point8ShortXY*)(psVar6 + -2))->xOffset + sVar1;
                            this->searchQueue.yQueue[this->searchQueue.writeIndex] = *psVar6 + sVar2;
                            this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = iVar8;
                            this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                            if (0x13a0f < this->searchQueue.writeIndex) {
                                this->searchQueue.writeIndex = 0;
                            }
                        }
                        iVar8 = *piVar7 + iVar5;
                        if (DAT_TileMapState::instance.WalkLayer[iVar8] != this->searchGeneration
                            && (DAT_TileMapState::instance.LogicLayer[iVar8] & 0x30) == 0) {
                            DAT_TileMapState::instance.CertainPathLayer[iVar8]
                                = (short)this->searchQueue.currentDistance + 1;
                            DAT_TileMapState::instance.WalkLayer[iVar8] = (short)this->searchGeneration;
                            this->searchQueue.xQueue[this->searchQueue.writeIndex] = psVar6[2] + sVar1;
                            this->searchQueue.yQueue[this->searchQueue.writeIndex] = psVar6[4] + sVar2;
                            this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = iVar8;
                            this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                            if (0x13a0f < this->searchQueue.writeIndex) {
                                this->searchQueue.writeIndex = 0;
                            }
                        }
                        iVar8 = piVar7[1] + iVar5;
                        if (DAT_TileMapState::instance.WalkLayer[iVar8] != this->searchGeneration
                            && (DAT_TileMapState::instance.LogicLayer[iVar8] & 0x30) == 0) {
                            DAT_TileMapState::instance.CertainPathLayer[iVar8]
                                = (short)this->searchQueue.currentDistance + 1;
                            DAT_TileMapState::instance.WalkLayer[iVar8] = (short)this->searchGeneration;
                            this->searchQueue.xQueue[this->searchQueue.writeIndex] = psVar6[6] + sVar1;
                            this->searchQueue.yQueue[this->searchQueue.writeIndex] = psVar6[8] + sVar2;
                            this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = iVar8;
                            this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                            if (0x13a0f < this->searchQueue.writeIndex) {
                                this->searchQueue.writeIndex = 0;
                            }
                        }
                        iVar8 = piVar7[2] + iVar5;
                        if (DAT_TileMapState::instance.WalkLayer[iVar8] != this->searchGeneration
                            && (DAT_TileMapState::instance.LogicLayer[iVar8] & 0x30) == 0) {
                            DAT_TileMapState::instance.CertainPathLayer[iVar8]
                                = (short)this->searchQueue.currentDistance + 1;
                            DAT_TileMapState::instance.WalkLayer[iVar8] = (short)this->searchGeneration;
                            this->searchQueue.xQueue[this->searchQueue.writeIndex] = psVar6[10] + sVar1;
                            this->searchQueue.yQueue[this->searchQueue.writeIndex] = psVar6[0xc] + sVar2;
                            this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = iVar8;
                            this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                            if (0x13a0f < this->searchQueue.writeIndex) {
                                this->searchQueue.writeIndex = 0;
                            }
                        }
                        piVar7 = piVar7 + 4;
                        psVar6 = psVar6 + 0x10;
                    } while ((int)psVar6 < 0xb4908c);
                    this->searchQueue.readIndex = this->searchQueue.readIndex + 1;
                    if (0x13a0f < this->searchQueue.readIndex) {
                        this->searchQueue.readIndex = 0;
                    }
                    if (this->searchQueue.readIndex == this->searchQueue.writeIndex) {
                        return (undefined4)(0);
                    }
                }
            }
            return (undefined4)(0);
        }

    }
}
}
