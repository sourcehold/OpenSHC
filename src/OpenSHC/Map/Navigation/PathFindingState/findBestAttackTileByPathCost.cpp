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
          target zone value (param_4). Returns the tileUnk index with the lowest combined path   cost and terrain cost
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
            if (param_1 > 399 || param_2 > 399
                || DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[param_2 * 400 + param_1] == '\0') {
                return (dword)(dVar4);
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
            this->searchQueue.yQueue[0] = (short)param_2;
            this->searchQueue.tilesQueue[0]
                = DAT_ViewportRenderState::instance.translationMatrix[param_2].addXgetTile + param_1;
            DAT_TileMapState::instance.CertainPathLayer[this->searchQueue.tilesQueue[0]]
                = (short)this->searchQueue.currentDistance;
            DAT_TileMapState::instance.WalkLayer[this->searchQueue.tilesQueue[0]] = (short)this->searchGeneration;
            while (this->searchQueue.readIndex != this->searchQueue.writeIndex) {
                int iVar3 = this->searchQueue.tilesQueue[this->searchQueue.readIndex];
                if (iVar3 < 0) {
                    return (dword)(local_8);
                }
                if (iVar3 >= 0x13a10) {
                    return (dword)(local_8);
                }
                int sVar2 = (int)this->searchQueue.yQueue[this->searchQueue.readIndex];
                this->searchQueue.currentDistance = (int)DAT_TileMapState::instance.CertainPathLayer[iVar3];
                if (0x13a10 < (int)this->searchQueue.currentDistance) {
                    return (dword)(local_8);
                }
                for (int iVar5 = 0; iVar5 < 8; iVar5 = iVar5 + 1) {
                    if ((DAT_TileMapState::instance.PathLinkageLayer[iVar3]
                            & DAT_ClimbLogicDefinedData::instance.BitFlagHelperForPathLinkage[iVar5])
                        != 0) {
                        dVar4 = DAT_TileMapState::instance.directionTranslationMatrix[sVar2][iVar5] + iVar3;
                        if (DAT_TileMapState::instance.WalkLayer[dVar4] != this->searchGeneration) {
                            int _hackValue = (int)*(byte*)(*(int*)(((int)&DAT_TroopValueState::instance.attackInfo + 0x301d0 /* old hackValuesArray: AttackInfoSubElement of player p at +0x301C0 + p*0x177BC */)
                                                                  + param_3 * 0x177bc + -0x10)
                                    * 0x13a10
                                + 0x1ee2998 + dVar4);
                            int _cost = (int)DAT_TileMapState::instance.SEC_TileMap1104[dVar4];
                            int _entity = (int)DAT_TileMapState::instance.EntityLayer[dVar4];
                            if (((_entity == 0)
                                    || (DAT_EntityState::instance.entityArray[_entity]
                                            .entityType
                                        != OpenSHC::Map::Entities::ET_FIRE))
                                && _hackValue == (int)param_4) {
                                if ((10 < (int)this->searchQueue.currentDistance) && (local_8 != 0)) {
                                    return (dword)(local_8);
                                }
                                if (6 < (int)this->searchQueue.currentDistance) {
                                    iVar1 = this->searchQueue.currentDistance + _cost * 3;
                                    if (iVar1 < local_4) {
                                        local_4 = iVar1;
                                        local_8 = dVar4;
                                    }
                                }
                            }
                            DAT_TileMapState::instance.CertainPathLayer[dVar4]
                                = (short)this->searchQueue.currentDistance + 1;
                            DAT_TileMapState::instance.WalkLayer[dVar4] = (short)this->searchGeneration;
                            this->searchQueue.yQueue[this->searchQueue.writeIndex]
                                = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[iVar5].short_.yOffset
                                + (short)sVar2;
                            this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = dVar4;
                            this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                            if (0x13a10 <= (int)this->searchQueue.writeIndex) {
                                this->searchQueue.writeIndex = 0;
                            }
                        }
                    }
                }
                this->searchQueue.readIndex = this->searchQueue.readIndex + 1;
                if (0x13a10 <= (int)this->searchQueue.readIndex) {
                    this->searchQueue.readIndex = 0;
                }
            }
            return (dword)(local_8);
        }

    }
}
}
