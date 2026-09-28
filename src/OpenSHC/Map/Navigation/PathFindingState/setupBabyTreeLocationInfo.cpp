#include "../PathFindingState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Location/Point8ShortXY.hpp"
#include "OpenSHC/Map/Trees/TreeType.hpp"
#include "OpenSHC/Map/Trees/TreeTypeShort.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_LandscapeState.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        using OpenSHC::Map::Location::Point8ShortXY;
        using OpenSHC::Map::Trees::TreeType;
        using OpenSHC::Map::Trees::TreeTypeShort;

        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x0049C020
        undefined4 PathFindingState::setupBabyTreeLocationInfo(int param_1, int treeType, uint x, uint y)
        {
            int iVar4;
            short* psVar7;
            int (*paiVar8)[8];
            this->ALG_ResultTile = 0;
            this->ALG_ResultY = 0;
            this->ALG_ResultX = 0;
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
                while ((iVar4 = this->searchQueue.tilesQueue[this->searchQueue.readIndex],
                    -1 < iVar4 && (iVar4 < 0x13a10))) {
                    this->searchQueue.currentDistance = (int)DAT_TileMapState::instance.CertainPathLayer[iVar4];
                    if (0x13a10 < this->searchQueue.currentDistance) {
                        return (undefined4)(0);
                    }
                    if (param_1 < this->searchQueue.currentDistance) {
                        return (undefined4)(1);
                    }
                    int sVar1 = (int)this->searchQueue.yQueue[this->searchQueue.readIndex];
                    int sVar2 = (int)this->searchQueue.xQueue[this->searchQueue.readIndex];
                    for (int _direction = 0; _direction < 8; _direction = _direction + 1) {
                        int iVar5 = DAT_TileMapState::instance.directionTranslationMatrix[sVar1][_direction] + iVar4;
                        if (DAT_TileMapState::instance.WalkLayer[iVar5] != this->searchGeneration) {
                            int iVar6 = (int)DAT_TileMapState::instance.OrganismLayer[iVar5];
                            if ((iVar6 == 0) || (1999 < iVar6)) {
                                if (DAT_TileMapState::instance.BuildingLayer[iVar5] != 0) {
                                    switch (DAT_BuildingsState::instance
                                            .buildings[DAT_TileMapState::instance.BuildingLayer[iVar5]]
                                            .buildingType) {
                                    case OpenSHC::Map::Buildings::BT_WOODCUTTERSHUT:
                                    case OpenSHC::Map::Buildings::BT_QUARRY:
                                    case OpenSHC::Map::Buildings::BT_WHEATFARM:
                                    case OpenSHC::Map::Buildings::BT_HOPFARM:
                                    case OpenSHC::Map::Buildings::BT_APPLEFARM:
                                    case OpenSHC::Map::Buildings::BT_DAIRYFARM:
                                    case OpenSHC::Map::Buildings::BT_SIGNPOST:
                                    case OpenSHC::Map::Buildings::BT_POND:
                                        break;
                                    default:
                                        goto switchD_0049c1f0_caseD_4;
                                    }
                                }
                                if ((DAT_TileMapState::instance.LogicLayer[iVar5] & 0x703e25b5U) == 0) {
                                    if (treeType == 1) {
                                        if ((DAT_TileMapState::instance.Logic2Layer[iVar5] & 0x90) == 0) {
                                        LAB_0049c26a:
                                            DAT_TileMapState::instance.CertainPathLayer[iVar5]
                                                = (short)this->searchQueue.currentDistance + 1;
                                            DAT_TileMapState::instance.WalkLayer[iVar5] = (short)this->searchGeneration;
                                            this->searchQueue.xQueue[this->searchQueue.writeIndex]
                                                = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction].short_.xOffset + sVar2;
                                            this->searchQueue.yQueue[this->searchQueue.writeIndex] = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction].short_.yOffset + sVar1;
                                            this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = iVar5;
                                            this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                                            if (0x13a0f < this->searchQueue.writeIndex) {
                                                this->searchQueue.writeIndex = 0;
                                            }
                                        }
                                    } else if ((DAT_TileMapState::instance.Logic2Layer[iVar5] & 0x90) != 0)
                                        goto LAB_0049c26a;
                                }
                            } else {
                                TreeTypeShort TVar3 = DAT_LandscapeState::instance.trees[iVar6].treeType;
                                if (TVar3 == (TreeType)1) {
                                    return (undefined4)(0);
                                }
                                if (TVar3 == (TreeType)2) {
                                    return (undefined4)(0);
                                }
                                if (TVar3 == (TreeType)3) {
                                    return (undefined4)(0);
                                }
                                if (TVar3 == (TreeType)4) {
                                    return (undefined4)(0);
                                }
                            }
                        }
                    }

                    this->searchQueue.readIndex = this->searchQueue.readIndex + 1;
                    if (0x13a0f < this->searchQueue.readIndex) {
                        this->searchQueue.readIndex = 0;
                    }
                    if (this->searchQueue.readIndex == this->searchQueue.writeIndex) {
                        return (undefined4)(0);
                    }
                }
            }
        switchD_0049c1f0_caseD_4:
            return (undefined4)(0);
        }

    }
}
}
