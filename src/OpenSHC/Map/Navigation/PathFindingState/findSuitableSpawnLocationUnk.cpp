#include "../PathFindingState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"

#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
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
        // FUNCTION: STRONGHOLDCRUSADER 0x00497B80
        undefined4 PathFindingState::findSuitableSpawnLocationUnk(
            int x, int y, int x2, int y2, int param_5, int param_6)
        {
            int iVar5 = x2;
            int iVar6 = y;
            if ((uint)x < 400 && (uint)y < 400
                && DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y * 400 + x] != '\0') {
                if (x2 != -1
                    && ((399 < (uint)x2 || (399 < (uint)y2))
                        || (DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y2 * 400 + x2] == '\0'))
                    && 500 < param_5) {
                    param_5 = 500;
                }
                if (param_6 == 0) {
                    this->searchGeneration = this->searchGeneration + 1;
                    if (32000 < this->searchGeneration) {
                        this->searchGeneration = 1;
                        MACRO_CALL_MEMBER(
                            OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                            0x27420, '\0', (void*)((int)(DAT_TileMapState::instance.WalkLayer)));
                    }
                    this->searchQueue.writeIndex = 1;
                    this->searchQueue.readIndex = 0;
                    this->searchQueue.depth = 0;
                }
                int iVar4 = this->searchGeneration;
                y = this->searchQueue.writeIndex;
                this->searchQueue.yQueue[0] = (short)iVar6;
                x2 = this->searchQueue.readIndex;
                this->searchQueue.tilesQueue[0]
                    = DAT_ViewportRenderState::instance.translationMatrix[iVar6].addXgetTile + x;
                DAT_TileMapState::instance.CertainPathLayer[this->searchQueue.tilesQueue[0]] = 1;
                param_6 = this->searchQueue.depth;
                DAT_TileMapState::instance.WalkLayer[this->searchQueue.tilesQueue[0]] = (short)this->searchGeneration;
                if (iVar5 == -1) {
                    x = 0;
                } else {
                    x = DAT_ViewportRenderState::instance.translationMatrix[y2].addXgetTile + iVar5;
                }
                while (true) {
                    if (x2 == y) {
                        this->searchQueue.readIndex = x2;
                        this->searchQueue.writeIndex = y;
                        this->searchQueue.depth = param_6;
                        return (undefined4)(0);
                    }
                    if (param_5 <= param_6)
                        break;
                    param_6 = param_6 + 1;
                    iVar6 = this->searchQueue.tilesQueue[x2];
                    if (iVar6 == x) {
                        this->searchQueue.writeIndex = y;
                        this->searchQueue.readIndex = x2;
                        this->searchQueue.depth = param_6;
                        return (undefined4)(1);
                    }
                    short sVar2 = DAT_TileMapState::instance.CertainPathLayer[iVar6];
                    short sVar7 = sVar2 + 1;
                    int uVar3 = (int)this->searchQueue.yQueue[x2];
                    int bVar1 = DAT_TileMapState::instance.PathLinkageLayer[iVar6];
                    int local_20 = (short)iVar4;
                    if (DAT_TileMapState::instance.CertainPathLayer[iVar6 + 0x13a0f] != local_20 && (bVar1 & 0x40) != 0
                        && DAT_TileMapState::instance.PathLinkageLayer[iVar6 + 0x13a0f] == '\0') {
                        DAT_TileMapState::instance.CertainPathLayer[iVar6 + -1] = sVar7;
                        DAT_TileMapState::instance.CertainPathLayer[iVar6 + 0x13a0f] = local_20;
                        this->searchQueue.tilesQueue[y] = iVar6 + -1;
                        this->searchQueue.yQueue[y] = uVar3;
                        y = y + 1;
                    }
                    if (DAT_TileMapState::instance.WalkLayer[iVar6 + 1] != local_20 && (bVar1 & 4) != 0
                        && DAT_TileMapState::instance.OccupancyLayer[iVar6 + 1] == '\0') {
                        DAT_TileMapState::instance.CertainPathLayer[iVar6 + 1] = sVar7;
                        DAT_TileMapState::instance.WalkLayer[iVar6 + 1] = local_20;
                        this->searchQueue.tilesQueue[y] = iVar6 + 1;
                        this->searchQueue.yQueue[y] = uVar3;
                        y = y + 1;
                    }
                    iVar5 = iVar6 + DAT_TileMapState::instance.directionTranslationMatrix[uVar3][0];
                    if (DAT_TileMapState::instance.WalkLayer[iVar5] != local_20 && (bVar1 & 1) != 0
                        && DAT_TileMapState::instance.OccupancyLayer[iVar5] == '\0') {
                        DAT_TileMapState::instance.CertainPathLayer[iVar5] = sVar7;
                        DAT_TileMapState::instance.WalkLayer[iVar5] = local_20;
                        this->searchQueue.tilesQueue[y] = iVar5;
                        this->searchQueue.yQueue[y] = uVar3 - 1;
                        y = y + 1;
                    }
                    if (DAT_TileMapState::instance.CertainPathLayer[iVar5 + 0x13a0f] != local_20 && (bVar1 & 0x80) != 0
                        && DAT_TileMapState::instance.PathLinkageLayer[iVar5 + 0x13a0f] == '\0') {
                        DAT_TileMapState::instance.CertainPathLayer[iVar5 + -1] = sVar2 + 2;
                        DAT_TileMapState::instance.CertainPathLayer[iVar5 + 0x13a0f] = local_20;
                        this->searchQueue.tilesQueue[y] = iVar5 + -1;
                        this->searchQueue.yQueue[y] = uVar3 - 1;
                        y = y + 1;
                    }
                    if (DAT_TileMapState::instance.WalkLayer[iVar5 + 1] != local_20 && (bVar1 & 2) != 0
                        && DAT_TileMapState::instance.OccupancyLayer[iVar5 + 1] == '\0') {
                        DAT_TileMapState::instance.CertainPathLayer[iVar5 + 1] = sVar2 + 2;
                        DAT_TileMapState::instance.WalkLayer[iVar5 + 1] = local_20;
                        this->searchQueue.tilesQueue[y] = iVar5 + 1;
                        this->searchQueue.yQueue[y] = uVar3 - 1;
                        y = y + 1;
                    }
                    iVar6 = iVar6 + DAT_TileMapState::instance.directionTranslationMatrix[uVar3][4];
                    if (DAT_TileMapState::instance.WalkLayer[iVar6] != local_20 && (bVar1 & 0x10) != 0
                        && DAT_TileMapState::instance.OccupancyLayer[iVar6] == '\0') {
                        DAT_TileMapState::instance.CertainPathLayer[iVar6] = sVar7;
                        DAT_TileMapState::instance.WalkLayer[iVar6] = local_20;
                        this->searchQueue.tilesQueue[y] = iVar6;
                        this->searchQueue.yQueue[y] = uVar3 + 1;
                        y = y + 1;
                    }
                    if (DAT_TileMapState::instance.CertainPathLayer[iVar6 + 0x13a0f] != local_20 && (bVar1 & 0x20) != 0
                        && DAT_TileMapState::instance.PathLinkageLayer[iVar6 + 0x13a0f] == '\0') {
                        DAT_TileMapState::instance.CertainPathLayer[iVar6 + -1] = sVar2 + 2;
                        DAT_TileMapState::instance.CertainPathLayer[iVar6 + 0x13a0f] = local_20;
                        this->searchQueue.tilesQueue[y] = iVar6 + -1;
                        this->searchQueue.yQueue[y] = uVar3 + 1;
                        y = y + 1;
                    }
                    if (DAT_TileMapState::instance.WalkLayer[iVar6 + 1] != local_20 && (bVar1 & 8) != 0
                        && DAT_TileMapState::instance.OccupancyLayer[iVar6 + 1] == '\0') {
                        DAT_TileMapState::instance.CertainPathLayer[iVar6 + 1] = sVar2 + 2;
                        DAT_TileMapState::instance.WalkLayer[iVar6 + 1] = local_20;
                        this->searchQueue.tilesQueue[y] = iVar6 + 1;
                        this->searchQueue.yQueue[y] = uVar3 + 1;
                        y = y + 1;
                    }
                    x2 = x2 + 1;
                }
                this->searchQueue.readIndex = x2;
                this->searchQueue.writeIndex = y;
                this->searchQueue.depth = param_6;
                return (undefined4)(0);
            }
            return (undefined4)(0);
        }

    }
}
}
