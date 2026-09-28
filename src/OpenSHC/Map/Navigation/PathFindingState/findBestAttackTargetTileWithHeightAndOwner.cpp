#include "../PathFindingState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Navigation.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_ClimbLogicDefinedData.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        using OpenSHC::Game::GameMode;

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
          BFS from (param_2, param_3) up to distance param_1, scoring enemy buildings and walls owned by   player
          param_7. Buildings score higher for defensive structures (0x400 flag), distance, and fire   state. Walls are
          scored by height difference from base terrain. The best-scoring tile coordinates   are written to ALG_TargetX,
          ALG_TargetY, and ALG_TargetTile. Height traversal cost is weighted in   3 tiers based on param_5.      renamed
          by: Claude Sonnet 4.6
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004A6010
        void PathFindingState::findBestAttackTargetTileWithHeightAndOwner(int param_1, uint param_2, uint param_3,
            int param_4, int param_5, int param_6, int param_7, int param_8, int param_9)
        {
            short sVar5;
            int iVar7;
            int iVar9;
            int (*paiVar12)[3];
            int local_20;
            int local_14;
            int local_10;
            uint local_c;
            uint local_8;
            local_14 = -1;
            local_10 = -1;
            local_c = 0xffffffff;
            this->calculations = this->calculations + 1;
            local_20 = 1000000;
            this->ALG_TargetTile = 0;
            this->ALG_TargetY = 0;
            this->ALG_TargetX = 0;
            if (param_2 > 399 || param_3 > 399 || DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[param_3 * 400 + param_2] == '\0') {
                return;
            }
            this->searchGeneration = this->searchGeneration + 1;
            if (32000 < this->searchGeneration) {
                this->searchGeneration = 1;
                MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                    0x27420, '\0', (void*)((int)(DAT_TileMapState::instance.WalkLayer)));
            }
            this->searchQueue.currentDistance = 1;
            this->searchQueue.writeIndex = 1;
            this->searchQueue.readIndex = 0;
            this->searchQueue.yQueue[0] = (short)param_3;
            this->searchQueue.xQueue[0] = (short)param_2;
            int iVar6 = DAT_ViewportRenderState::instance.translationMatrix[param_3].addXgetTile + param_2;
            this->searchQueue.tilesQueue[0] = iVar6;
            DAT_TileMapState::instance.CertainPathLayer[iVar6] = 1;
            DAT_TileMapState::instance.WalkLayer[this->searchQueue.tilesQueue[0]] = (short)this->searchGeneration;
            uint uVar10 = (uint)DAT_TileMapState::instance.HeightLayer[iVar6];
            if (this->searchQueue.readIndex != this->searchQueue.writeIndex) {
                do {
                    uint uVar4 = this->searchQueue.tilesQueue[this->searchQueue.readIndex];
                    if (0x13a0f < uVar4)
                        break;
                    int sVar1 = (int)this->searchQueue.xQueue[this->searchQueue.readIndex];
                    int sVar2 = (int)this->searchQueue.yQueue[this->searchQueue.readIndex];
                    iVar6 = (int)sVar2;
                    uint uVar8 = DAT_TileMapState::instance.LogicLayer[uVar4];
                    uint uVar11 = (uint) * (byte*)(param_7 * 0x13a10 + 0x1ee2998 + uVar4);
                    this->searchQueue.currentDistance = (int)DAT_TileMapState::instance.CertainPathLayer[uVar4];
                    if (this->searchQueue.currentDistance <= param_1) {
                        if ((DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY)
                            && (7 < param_6)) {
                            uVar11 = 1;
                        }
                        if ((uVar8 & 2) == 0) {
                            if ((uVar8 & 0x10100) == 0 || uVar11 == 0 || param_8 <= (int)uVar11) {
                                if ((uVar8 & 0x10000400) != 0 && uVar11 != 0 && (int)uVar11 < param_8
                                    && (iVar9 = (int)DAT_TileMapState::instance.BuildingLayer[uVar4],
                                        iVar9 != 0
                                            && (DAT_BuildingDefinedData::instance.BuildingTypeHasHealth[(
                                                    short)DAT_BuildingsState::instance.buildings[iVar9]
                                                        .buildingType]
                                                != 0))
                                    && DAT_BuildingsState::instance.buildings[iVar9].owner == param_7
                                    && (param_9 == 0
                                        || ((
                                            iVar7 = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::
                                                                          getBuildingFlammabilityFactor,
                                                DAT_BuildingsState::ptr)(iVar9),
                                            iVar7 != 0
                                                && (DAT_BuildingsState::instance.buildings[iVar9].fireDuration
                                                    == 0))))) {
                                    iVar9 = 0x96;
                                    if ((uVar8 & 0x400) == 0) {
                                        iVar9 = 0x4b;
                                    }
                                    if (this->searchQueue.currentDistance < 1) {
                                        iVar9 = 100000;
                                    } else if (this->searchQueue.currentDistance < 0x10) {
                                        iVar9 = (iVar9 + -100) * this->searchQueue.currentDistance + 0x5dc;
                                    } else {
                                        iVar9 = this->searchQueue.currentDistance * iVar9;
                                    }
                                    goto LAB_004a62e3;
                                }
                            } else if ((DAT_TileMapState::instance.WallOwnerLayer[uVar4] & 7) + 1 == param_7
                                && param_9 == 0) {
                                iVar9 = (uint)DAT_TileMapState::instance.HeightLayer[uVar4]
                                    - (uint)DAT_TileMapState::instance.DefaultHeightLayer[uVar4];
                                if (this->searchQueue.currentDistance < 1) {
                                    iVar9 = 100000;
                                } else if (this->searchQueue.currentDistance < 0x10) {
                                    iVar9 = (0x14 - this->searchQueue.currentDistance) * 300 + iVar9;
                                } else {
                                    iVar9 = this->searchQueue.currentDistance * 100 + iVar9;
                                }
                            LAB_004a62e3:
                                if (iVar9 < local_20
                                    && (iVar7
                                        = MACRO_CALL(OpenSHC::Map::Navigation_Func::calcApproxEuclideanDistance)(
                                            param_2, (int)(sVar1), (int)(param_3), iVar6),
                                        iVar7 <= param_1)) {
                                    local_20 = iVar9;
                                    local_14 = (int)sVar1;
                                    local_10 = iVar6;
                                    local_c = uVar4;
                                }
                            }
                        }
                        local_8 = ((int)(char)this->searchQueue.currentDistance & 1U) * 2 | 1;
                        paiVar12 = DAT_ClimbLogicDefinedData::instance.field13_0x13c + param_4;
                        do {
                            iVar9 = (*paiVar12)[0];
                            iVar7 = DAT_TileMapState::instance.directionTranslationMatrix[iVar6][iVar9] + uVar4;
                            uVar8 = DAT_TileMapState::instance.LogicLayer[iVar7];
                            if (DAT_TileMapState::instance.WalkLayer[iVar7] != this->searchGeneration
                                && (uVar8 & 0x30) == 0) {
                                if ((uVar8 & 0x10000400) == 0) {
                                    if ((uVar8 & 0x100) == 0) {
                                        uVar8 = (uint)DAT_TileMapState::instance.HeightLayer[iVar7];
                                        if ((int)uVar8 <= (int)(uVar10 + param_5))
                                            goto LAB_004a63f4;
                                    } else if ((DAT_TileMapState::instance.WallOwnerLayer[iVar7] & 7) + 1
                                        == param_7) {
                                        uVar8 = (uint)DAT_TileMapState::instance.HeightLayer[iVar7];
                                    LAB_004a63f4:
                                        if ((int)((param_5 * 2) / 3 + uVar10) < (int)uVar8) {
                                            sVar5 = 3;
                                        } else {
                                            sVar5 = ((int)(param_5 / 3 + uVar10) < (int)uVar8) + 1;
                                        }
                                        short sVar3 = DAT_TerrainDefinedData::instance
                                                          .clockwiseCardinalTranslationMatrix[iVar9]
                                                          .short_.xOffset;
                                        DAT_TileMapState::instance.CertainPathLayer[iVar7]
                                            = (short)this->searchQueue.currentDistance + sVar5;
                                        DAT_TileMapState::instance.WalkLayer[iVar7] = (short)this->searchGeneration;
                                        this->searchQueue.xQueue[this->searchQueue.writeIndex] = sVar3 + sVar1;
                                        this->searchQueue.yQueue[this->searchQueue.writeIndex]
                                            = *(short*)((int)DAT_TerrainDefinedData::instance
                                                            .clockwiseCardinalTranslationMatrix
                                                  + iVar9 * 8 + 4)
                                            + sVar2;
                                        this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = iVar7;
                                        this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                                        if (0x13a0f < this->searchQueue.writeIndex) {
                                            this->searchQueue.writeIndex = 0;
                                        }
                                    }
                                } else {
                                    int buildingID = (int)DAT_TileMapState::instance.BuildingLayer[iVar7];
                                    if ((buildingID != 0)
                                        && (DAT_BuildingsState::instance.buildings[buildingID].owner == param_7)) {
                                        uVar8 = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::
                                                                      getBuildingHeightForBuildingID,
                                            DAT_BuildingsState::ptr)(buildingID);
                                        goto LAB_004a63f4;
                                    }
                                }
                            }
                            paiVar12 = (int (*)[3])(*paiVar12 + 1);
                            local_8 = local_8 - 1;
                        } while (local_8 != 0);
                    }
                    this->searchQueue.readIndex = this->searchQueue.readIndex + 1;
                    if (0x13a0f < this->searchQueue.readIndex) {
                        this->searchQueue.readIndex = 0;
                    }
                } while (this->searchQueue.readIndex != this->searchQueue.writeIndex);
                if (local_14 != -1) {
                    this->ALG_TargetX = local_14;
                    this->ALG_TargetY = local_10;
                    this->ALG_TargetTile = local_c;
                }
            }
            return;
}

    }
}
}
