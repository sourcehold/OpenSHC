#include "../PathFindingState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_ClimbLogicDefinedData.hpp"
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
        // FUNCTION: STRONGHOLDCRUSADER 0x00498A40
        undefined4 PathFindingState::calculatePathKeepAndWallsGatesNotAllowed(
            int x1, int y1, int x2, int y2, int maxTries)
        {
            uint uVar4;
            int* piVar5;
            int iVar6;
            uint _tile;
            if (399 < (uint)x1 || 399 < (uint)y1 || *(char*)(y1 * 400 + 0x21aec98 + x1) == '\0') {
                return (undefined4)(0);
            }
            if (x2 == -1 || (((uint)x2 < 400 && ((uint)y2 < 400)) && (*(char*)(y2 * 400 + 0x21aec98 + x2) != '\0'))) {
                this->searchGeneration = this->searchGeneration + 1;
                if (32000 < this->searchGeneration) {
                    this->searchGeneration = 1;
                    MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                        0x27420, '\0', (void*)((int)(DAT_TileMapState::instance.WalkLayer)));
                }
                this->searchQueue.yQueue[0] = (short)y1;
                this->searchQueue.writeIndex = 1;
                this->searchQueue.readIndex = 0;
                this->searchQueue.currentDistance = 1;
                this->searchQueue.xQueue[0] = (short)x1;
                this->searchQueue.tilesQueue[0]
                    = DAT_ViewportRenderState::instance.translationMatrix[y1].addXgetTile + x1;
                DAT_TileMapState::instance.CertainPathLayer[this->searchQueue.tilesQueue[0]] = 1;
                DAT_TileMapState::instance.WalkLayer[this->searchQueue.tilesQueue[0]] = (short)this->searchGeneration;
                if (x2 == -1) {
                    uVar4 = 0;
                } else {
                    uVar4 = DAT_ViewportRenderState::instance.translationMatrix[y2].addXgetTile + x2;
                }
                if (this->searchQueue.readIndex != this->searchQueue.writeIndex) {
                    while (true) {
                        _tile = this->searchQueue.tilesQueue[this->searchQueue.readIndex];
                        if (_tile == uVar4) {
                            return (undefined4)(1);
                        }
                        if ((maxTries <= this->searchQueue.readIndex) || (80399 < _tile))
                            break;
                        short sVar1 = this->searchQueue.yQueue[this->searchQueue.readIndex];
                        this->searchQueue.currentDistance = (int)DAT_TileMapState::instance.CertainPathLayer[_tile];
                        short sVar2 = this->searchQueue.xQueue[this->searchQueue.readIndex];
                        int iVar3 = 0;
                        piVar5 = DAT_TileMapState::instance.directionTranslationMatrix[sVar1] + 1;
                        do {
                            iVar6 = (*(int (*)[8])(piVar5 + -1))[0] + _tile;
                            if (DAT_TileMapState::instance.WalkLayer[iVar6] != this->searchGeneration
                                && (DAT_TileMapState::instance.PathLinkageLayer[_tile]
                                       & DAT_ClimbLogicDefinedData::instance.BitFlagHelperForPathLinkage[iVar3])
                                    != 0
                                && (((DAT_TileMapState::instance.LogicLayer[iVar6] & 2U) != 0
                                        || ((DAT_TileMapState::instance.LogicLayer[iVar6] & 0x10000100U) == 0))
                                    || ((DAT_TileMapState::instance.BuildingLayer[iVar6] != 0
                                        && (DAT_BuildingDefinedData::instance
                                                .BuildingIsGateHouseArray[(short)DAT_BuildingsState::instance
                                                        .buildings[DAT_TileMapState::instance.BuildingLayer[iVar6]]
                                                        .buildingType]
                                            != 0))))) {
                                DAT_TileMapState::instance.CertainPathLayer[iVar6]
                                    = (short)this->searchQueue.currentDistance + 1;
                                DAT_TileMapState::instance.WalkLayer[iVar6] = (short)this->searchGeneration;
                                this->searchQueue.xQueue[this->searchQueue.writeIndex]
                                    = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[iVar3]
                                          .short_.xOffset
                                    + sVar2;
                                this->searchQueue.yQueue[this->searchQueue.writeIndex]
                                    = *(short*)((int)DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix
                                          + iVar3 * 8 + 4)
                                    + sVar1;
                                this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = iVar6;
                                this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                                if (0x13a0f < this->searchQueue.writeIndex) {
                                    this->searchQueue.writeIndex = 0;
                                }
                            }
                            iVar6 = *piVar5 + _tile;
                            if (DAT_TileMapState::instance.WalkLayer[iVar6] != this->searchGeneration
                                && (DAT_TileMapState::instance.PathLinkageLayer[_tile]
                                       & DAT_ClimbLogicDefinedData::instance.BitFlagHelperForPathLinkage[iVar3 + 1])
                                    != 0
                                && (((DAT_TileMapState::instance.LogicLayer[iVar6] & 2U) != 0
                                        || ((DAT_TileMapState::instance.LogicLayer[iVar6] & 0x10000100U) == 0))
                                    || ((DAT_TileMapState::instance.BuildingLayer[iVar6] != 0
                                        && (DAT_BuildingDefinedData::instance
                                                .BuildingIsGateHouseArray[(short)DAT_BuildingsState::instance
                                                        .buildings[DAT_TileMapState::instance.BuildingLayer[iVar6]]
                                                        .buildingType]
                                            != 0))))) {
                                DAT_TileMapState::instance.CertainPathLayer[iVar6]
                                    = (short)this->searchQueue.currentDistance + 1;
                                DAT_TileMapState::instance.WalkLayer[iVar6] = (short)this->searchGeneration;
                                this->searchQueue.xQueue[this->searchQueue.writeIndex]
                                    = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[iVar3 + 1]
                                          .short_.xOffset
                                    + sVar2;
                                this->searchQueue.yQueue[this->searchQueue.writeIndex]
                                    = *(short*)((int)DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix
                                          + iVar3 * 8 + 0xc)
                                    + sVar1;
                                this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = iVar6;
                                this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                                if (0x13a0f < this->searchQueue.writeIndex) {
                                    this->searchQueue.writeIndex = 0;
                                }
                            }
                            iVar6 = piVar5[1] + _tile;
                            if (DAT_TileMapState::instance.WalkLayer[iVar6] != this->searchGeneration
                                && (DAT_TileMapState::instance.PathLinkageLayer[_tile]
                                       & DAT_ClimbLogicDefinedData::instance.BitFlagHelperForPathLinkage[iVar3 + 2])
                                    != 0
                                && (((DAT_TileMapState::instance.LogicLayer[iVar6] & 2U) != 0
                                        || ((DAT_TileMapState::instance.LogicLayer[iVar6] & 0x10000100U) == 0))
                                    || ((DAT_TileMapState::instance.BuildingLayer[iVar6] != 0
                                        && (DAT_BuildingDefinedData::instance
                                                .BuildingIsGateHouseArray[(short)DAT_BuildingsState::instance
                                                        .buildings[DAT_TileMapState::instance.BuildingLayer[iVar6]]
                                                        .buildingType]
                                            != 0))))) {
                                DAT_TileMapState::instance.CertainPathLayer[iVar6]
                                    = (short)this->searchQueue.currentDistance + 1;
                                DAT_TileMapState::instance.WalkLayer[iVar6] = (short)this->searchGeneration;
                                this->searchQueue.xQueue[this->searchQueue.writeIndex]
                                    = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[iVar3 + 2]
                                          .short_.xOffset
                                    + sVar2;
                                this->searchQueue.yQueue[this->searchQueue.writeIndex]
                                    = *(short*)((int)DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix
                                          + iVar3 * 8 + 0x14)
                                    + sVar1;
                                this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = iVar6;
                                this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                                if (0x13a0f < this->searchQueue.writeIndex) {
                                    this->searchQueue.writeIndex = 0;
                                }
                            }
                            iVar6 = piVar5[2] + _tile;
                            if (DAT_TileMapState::instance.WalkLayer[iVar6] != this->searchGeneration
                                && (DAT_TileMapState::instance.PathLinkageLayer[_tile]
                                       & DAT_ClimbLogicDefinedData::instance.BitFlagHelperForPathLinkage[iVar3 + 3])
                                    != 0
                                && (((DAT_TileMapState::instance.LogicLayer[iVar6] & 2U) != 0
                                        || ((DAT_TileMapState::instance.LogicLayer[iVar6] & 0x10000100U) == 0))
                                    || ((DAT_TileMapState::instance.BuildingLayer[iVar6] != 0
                                        && (DAT_BuildingDefinedData::instance
                                                .BuildingIsGateHouseArray[(short)DAT_BuildingsState::instance
                                                        .buildings[DAT_TileMapState::instance.BuildingLayer[iVar6]]
                                                        .buildingType]
                                            != 0))))) {
                                DAT_TileMapState::instance.CertainPathLayer[iVar6]
                                    = (short)this->searchQueue.currentDistance + 1;
                                DAT_TileMapState::instance.WalkLayer[iVar6] = (short)this->searchGeneration;
                                this->searchQueue.xQueue[this->searchQueue.writeIndex]
                                    = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[iVar3 + 3]
                                          .short_.xOffset
                                    + sVar2;
                                this->searchQueue.yQueue[this->searchQueue.writeIndex]
                                    = *(short*)((int)DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix
                                          + iVar3 * 8 + 0x1c)
                                    + sVar1;
                                this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = iVar6;
                                this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                                if (0x13a0f < this->searchQueue.writeIndex) {
                                    this->searchQueue.writeIndex = 0;
                                }
                            }
                            iVar3 = iVar3 + 4;
                            piVar5 = piVar5 + 4;
                        } while (iVar3 < 8);
                        this->searchQueue.readIndex = this->searchQueue.readIndex + 1;
                        if (80400 < this->searchQueue.readIndex) {
                            this->searchQueue.readIndex = 0;
                        }
                        if (this->searchQueue.readIndex == this->searchQueue.writeIndex) {
                            return (undefined4)(0);
                        }
                    }
                }
            }
            return (undefined4)(0);
        }

    }
}
}
