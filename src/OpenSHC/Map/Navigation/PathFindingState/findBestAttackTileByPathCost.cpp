#include "../PathFindingState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Entities/EntityType.hpp"

#include "OpenSHC/Globals/DAT_ClimbLogicDefinedData.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        using OpenSHC::Map::Entities::EntityType;

        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
          BFS from (param_1, param_2), scores reachable tiles against a hack values array (indexed by   param_3) and a
          target zone value (param_4). Returns the tile index with the lowest combined path   cost and terrain cost
          weighting. Used to select the optimal attack position for a unit   approaching a target zone.      renamed by:
          Claude Sonnet 4.6
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004A01D0
        dword PathFindingState::findBestAttackTileByPathCost(uint param_1, uint param_2, int param_3, uint param_4)
        {
            int iVar1;
            dword dVar4 = 1000;
            int local_4 = 1000;
            dword local_8 = 0;
            if (param_1 <= 399 && param_2 <= 399 && DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[param_2 * 400 + param_1] != '\0') {
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
                this->searchQueue.yQueue[0] = (short)param_2;
                this->searchQueue.tilesQueue[0]
                    = DAT_ViewportRenderState::instance.translationMatrix[param_2].addXgetTile + param_1;
                DAT_TileMapState::instance.CertainPathLayer[this->searchQueue.tilesQueue[0]] = 1;
                DAT_TileMapState::instance.WalkLayer[this->searchQueue.tilesQueue[0]] = (short)this->searchGeneration;
                dVar4 = local_8;
                if (this->searchQueue.readIndex != this->searchQueue.writeIndex) {
                    do {
                        int iVar3 = this->searchQueue.tilesQueue[this->searchQueue.readIndex];
                        if (iVar3 < 0) {
                            return (dword)(local_8);
                        }
                        if (0x13a0f < iVar3) {
                            return (dword)(local_8);
                        }
                        int sVar2 = (int)this->searchQueue.yQueue[this->searchQueue.readIndex];
                        this->searchQueue.currentDistance = (int)DAT_TileMapState::instance.CertainPathLayer[iVar3];
                        if (0x13a10 < this->searchQueue.currentDistance) {
                            return (dword)(local_8);
                        }
                        int iVar5 = 0;
                        do {
                            if ((DAT_TileMapState::instance.PathLinkageLayer[iVar3]
                                    & DAT_ClimbLogicDefinedData::instance.BitFlagHelperForPathLinkage[iVar5])
                                    != 0
                                && (dVar4 = DAT_TileMapState::instance.directionTranslationMatrix[sVar2][iVar5] + iVar3,
                                    DAT_TileMapState::instance.WalkLayer[dVar4] != this->searchGeneration)) {
                                if (((DAT_TileMapState::instance.EntityLayer[dVar4] == 0)
                                        || (DAT_EntityState::instance
                                                .entityArray[DAT_TileMapState::instance.EntityLayer[dVar4]]
                                                .entityType
                                            != OpenSHC::Map::Entities::ET_FIRE))
                                    && *(byte*)(*(int*)((int)DAT_TroopValueState::instance.attackInfo.hackValuesArray
                                                    + param_3 * 0x177bc + -0x10)
                                               * 0x13a10
                                           + 0x1ee2998 + dVar4)
                                        == param_4) {
                                    if ((10 < this->searchQueue.currentDistance) && (local_8 != 0)) {
                                        return (dword)(local_8);
                                    }
                                    if ((6 < this->searchQueue.currentDistance)
                                        && (iVar1 = this->searchQueue.currentDistance
                                                + (uint)DAT_TileMapState::instance.SEC_TileMap1104[dVar4] * 3,
                                            iVar1 < local_4)) {
                                        local_8 = dVar4;
                                        local_4 = iVar1;
                                    }
                                }
                                DAT_TileMapState::instance.CertainPathLayer[dVar4]
                                    = (short)this->searchQueue.currentDistance + 1;
                                DAT_TileMapState::instance.WalkLayer[dVar4] = (short)this->searchGeneration;
                                this->searchQueue.yQueue[this->searchQueue.writeIndex]
                                    = *(short*)((int)DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix
                                          + iVar5 * 8 + 4)
                                    + sVar2;
                                this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = dVar4;
                                this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                                if (0x13a0f < this->searchQueue.writeIndex) {
                                    this->searchQueue.writeIndex = 0;
                                }
                            }
                            iVar5 = iVar5 + 1;
                        } while (iVar5 < 8);
                        this->searchQueue.readIndex = this->searchQueue.readIndex + 1;
                        if (0x13a0f < this->searchQueue.readIndex) {
                            this->searchQueue.readIndex = 0;
                        }
                        dVar4 = local_8;
                    } while (this->searchQueue.readIndex != this->searchQueue.writeIndex);
                }
            }
            return (dword)(dVar4);
        }

    }
}
}
