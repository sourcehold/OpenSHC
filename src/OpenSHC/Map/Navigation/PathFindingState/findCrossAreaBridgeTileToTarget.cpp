#include "../PathFindingState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Location/Point8IntXY.hpp"

#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {
        using OpenSHC::Map::Location::Point8IntXY;

        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
          BFS from unit param_1's current tile, expanding within its own PathConnectionLayer area or   through
          walls/structures. When a tile in a different area is encountered, checks whether that   area connects to the
          target area (param_2, param_3) via   calculateCanPlayerUnitsNavigateToAreaFromArea. Selects the neighbour tile
          with the minimum   Chebyshev distance to the target. Stores the source tile in ALG_TargetTile and the bridge
          tile in   ALG_ResultTile. Returns 1 on success, 0 if no bridge found.      renamed by: Claude Sonnet 4.6
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004A6AB0
        undefined4 PathFindingState::findCrossAreaBridgeTileToTarget(int param_1, uint param_2, uint param_3)
        {
            ushort uVar2;
            int (*paiVar6)[8];
            int iVar7;
            uint uVar8;
            uint uVar9;
            int iVar10;
            uint uVar11;
            int* piVar12;
            int iVar13;
            int local_20;
            uint local_14;
            int local_10;
            local_14 = 0;
            local_10 = 0;
            local_20 = 10000;
            if (param_2 > 399 || param_3 > 399
                || DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[param_3 * 400 + param_2] == '\0') {
                return (undefined4)(0);
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
            ushort uVar1 = DAT_TileMapState::instance.PathConnectionLayer[DAT_UnitsState::instance.units[param_1].tile];
            uVar2 = DAT_TileMapState::instance
                        .PathConnectionLayer[DAT_ViewportRenderState::instance.translationMatrix[param_3].addXgetTile
                            + param_2];
            this->searchQueue.yQueue[0] = DAT_UnitsState::instance.units[param_1].y;
            this->searchQueue.xQueue[0] = DAT_UnitsState::instance.units[param_1].x;
            this->searchQueue.tilesQueue[0] = DAT_UnitsState::instance.units[param_1].tile;
            DAT_TileMapState::instance.CertainPathLayer[this->searchQueue.tilesQueue[0]] = 1;
            DAT_TileMapState::instance.WalkLayer[this->searchQueue.tilesQueue[0]] = (short)this->searchGeneration;
            if (this->searchQueue.readIndex != this->searchQueue.writeIndex) {
                do {
                    uint uVar5 = this->searchQueue.tilesQueue[this->searchQueue.readIndex];
                    if (0x13a0f < uVar5)
                        break;
                    int sVar3 = (int)this->searchQueue.xQueue[this->searchQueue.readIndex];
                    int sVar4 = (int)this->searchQueue.yQueue[this->searchQueue.readIndex];
                    this->searchQueue.currentDistance = (int)DAT_TileMapState::instance.CertainPathLayer[uVar5];
                    if (0x13a10 < this->searchQueue.currentDistance)
                        break;
                    for (int _direction = 0; _direction < 8; _direction = _direction + 2) {
                        iVar13 = DAT_TileMapState::instance.directionTranslationMatrix[sVar4][_direction] + uVar5;
                        if (DAT_TileMapState::instance.WalkLayer[iVar13] != this->searchGeneration
                            && (DAT_TileMapState::instance.LogicLayer[iVar13] & 0x400000U) == 0) {
                            if ((int)(short)DAT_TileMapState::instance.PathConnectionLayer[iVar13] == (int)(short)uVar1
                                || (DAT_TileMapState::instance.LogicLayer[iVar13] & 0x10000100U) != 0) {
                                iVar7 = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction]
                                            .int_.xOffset;
                                DAT_TileMapState::instance.CertainPathLayer[iVar13]
                                    = (short)this->searchQueue.currentDistance + 1;
                                DAT_TileMapState::instance.WalkLayer[iVar13] = (short)this->searchGeneration;
                                this->searchQueue.xQueue[this->searchQueue.writeIndex] = (short)iVar7 + sVar3;
                                this->searchQueue.yQueue[this->searchQueue.writeIndex]
                                    = (short)DAT_TerrainDefinedData::instance
                                          .clockwiseCardinalTranslationMatrix[_direction]
                                          .int_.yOffset
                                    + sVar4;
                                this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = iVar13;
                                this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                                if (0x13a0f < this->searchQueue.writeIndex) {
                                    this->searchQueue.writeIndex = 0;
                                }
                            } else {
                                iVar7 = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::
                                                              calculateCanPlayerUnitsNavigateToAreaFromArea,
                                    this)((int)DAT_UnitsState::instance.units[param_1].owner,
                                    (dword)((int)((int)(short)DAT_TileMapState::instance.PathConnectionLayer[iVar13])),
                                    (dword)((int)((short)uVar2)),
                                    (int)(DAT_UnitsState::instance.units[param_1].unitCanClimb));
                                if (iVar7 != 0) {
                                    uVar8 = (DAT_TerrainDefinedData::instance
                                                    .clockwiseCardinalTranslationMatrix[_direction]
                                                    .int_.yOffset
                                                - param_3)
                                        + (int)sVar4;
                                    uVar11 = (int)uVar8 >> 0x1f;
                                    uVar9 = (DAT_TerrainDefinedData::instance
                                                    .clockwiseCardinalTranslationMatrix[_direction]
                                                    .int_.xOffset
                                                - param_2)
                                        + (int)sVar3;
                                    iVar10 = (uVar8 ^ uVar11) - uVar11;
                                    uVar8 = (int)uVar9 >> 0x1f;
                                    iVar7 = (uVar9 ^ uVar8) - uVar8;
                                    if (iVar7 <= iVar10) {
                                        iVar7 = iVar10;
                                    }
                                    if (iVar7 < local_20) {
                                        local_20 = iVar7;
                                        local_14 = uVar5;
                                        local_10 = iVar13;
                                    }
                                }
                            }
                        }
                    }

                    this->searchQueue.readIndex = this->searchQueue.readIndex + 1;
                    if (0x13a0f < this->searchQueue.readIndex) {
                        this->searchQueue.readIndex = 0;
                    }
                } while (this->searchQueue.readIndex != this->searchQueue.writeIndex);
                if (local_20 < 10000) {
                    this->ALG_TargetTile = local_14;
                    this->ALG_ResultTile = local_10;
                    return (undefined4)(1);
                }
            }
            return (undefined4)(0);
        }

    }
}
}
