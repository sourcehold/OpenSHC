#include "../PathFindingState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"

#include "OpenSHC/Globals/DAT_ClimbLogicDefinedData.hpp"
#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
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
        // FUNCTION: STRONGHOLDCRUSADER 0x0049FC00
        dword PathFindingState::pathFindingRelated(int param_1, uint param_2, uint param_3, int param_4)
        {
            uint uVar5;
            int iVar8;
            dword dVar6 = 1000;
            uint local_1c = 1000;
            dword local_14 = 0;
            int local_18 = 10000;
            if (param_2 > 399 || param_3 > 399 || DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[param_3 * 400 + param_2] == '\0') {
                return (dword)(dVar6);
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
            this->searchQueue.yQueue[0] = (short)param_3;
            this->searchQueue.xQueue[0] = (short)param_2;
            this->searchQueue.tilesQueue[0]
                = DAT_ViewportRenderState::instance.translationMatrix[param_3].addXgetTile + param_2;
            int bVar1 = *(byte*)(param_4 * 0x13a10 + 0x1ee2998 + this->searchQueue.tilesQueue[0]);
            DAT_TileMapState::instance.CertainPathLayer[this->searchQueue.tilesQueue[0]] = 1;
            DAT_TileMapState::instance.WalkLayer[this->searchQueue.tilesQueue[0]] = (short)this->searchGeneration;
            if (this->searchQueue.readIndex != this->searchQueue.writeIndex) {
                while (uVar5 = this->searchQueue.tilesQueue[this->searchQueue.readIndex], uVar5 < 0x13a10) {
                    short sVar2 = this->searchQueue.xQueue[this->searchQueue.readIndex];
                    this->searchQueue.currentDistance = (int)DAT_TileMapState::instance.CertainPathLayer[uVar5];
                    short sVar3 = this->searchQueue.yQueue[this->searchQueue.readIndex];
                    int iVar7 = (int)sVar3;
                    if ((0x13a10 < this->searchQueue.currentDistance)
                        || (this->searchQueue.currentDistance > param_1))
                        break;
                    for (int iVar10 = 0; iVar10 < 8; iVar10 = iVar10 + 1) {
                        if ((DAT_TileMapState::instance.PathLinkageLayer[uVar5]
                            & DAT_ClimbLogicDefinedData::instance.BitFlagHelperForPathLinkage[iVar10])
                            != 0
                        && (dVar6
                            = DAT_TileMapState::instance.directionTranslationMatrix[iVar7][iVar10] + uVar5,
                            DAT_TileMapState::instance.WalkLayer[dVar6] != this->searchGeneration)) {
                        uint uVar9 = (uint) * (byte*)(param_4 * 0x13a10 + 0x1ee2998 + dVar6);
                        if (uVar9 < 4) {
                            uVar9 = 0;
                        LAB_0049fdba:
                            if (uVar9 == local_1c
                                && (iVar8
                                    = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::
                                                            setAxisBasedDistanceResult,
                                        DAT_DirectionAlgorithmState::ptr)(param_2, (int)(param_3),
                                        (int)(DAT_TerrainDefinedData::instance
                                                  .clockwiseCardinalTranslationMatrix[iVar10]
                                                  .int_.xOffset
                                            + sVar2),
                                        *(int*)((int)DAT_TerrainDefinedData::instance
                                                    .clockwiseCardinalTranslationMatrix
                                            + iVar10 * 8 + 4)
                                            + iVar7),
                                    iVar8 < local_18))
                                goto LAB_0049fdee;
                        } else {
                            if ((uVar9 == 0) || (local_1c <= uVar9))
                                goto LAB_0049fdba;
                            iVar8 = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::
                                                          setAxisBasedDistanceResult,
                                DAT_DirectionAlgorithmState::ptr)(param_2, (int)(param_3),
                                (int)(DAT_TerrainDefinedData::instance
                                          .clockwiseCardinalTranslationMatrix[iVar10]
                                          .int_.xOffset
                                    + sVar2),
                                *(int*)((int)DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix
                                    + iVar10 * 8 + 4)
                                    + iVar7);
                        LAB_0049fdee:
                            local_1c = uVar9;
                            local_18 = iVar8;
                            local_14 = dVar6;
                        }
                        DAT_TileMapState::instance.CertainPathLayer[dVar6]
                            = (short)this->searchQueue.currentDistance + 1;
                        short sVar4
                            = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[iVar10]
                                  .short_.xOffset;
                        DAT_TileMapState::instance.WalkLayer[dVar6] = (short)this->searchGeneration;
                        this->searchQueue.xQueue[this->searchQueue.writeIndex] = sVar4 + sVar2;
                        this->searchQueue.yQueue[this->searchQueue.writeIndex]
                            = *(short*)((int)DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix
                                  + iVar10 * 8 + 4)
                            + sVar3;
                        this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = dVar6;
                        this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                        if (0x13a0f < this->searchQueue.writeIndex) {
                            this->searchQueue.writeIndex = 0;
                        }
                        }
                    }
                    this->searchQueue.readIndex = this->searchQueue.readIndex + 1;
                    if (0x13a0f < this->searchQueue.readIndex) {
                        this->searchQueue.readIndex = 0;
                    }
                    if (this->searchQueue.readIndex == this->searchQueue.writeIndex)
                        break;
                }
            }
            this->field51_0x9c = bVar1 - local_1c;
            dVar6 = local_14;
            return (dword)(dVar6);
}

    }
}
}
