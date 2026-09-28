#include "../PathFindingState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Entities/EntityState.func.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Map/Location/Point8ShortXY.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        using OpenSHC::Commands::MappersEnum;
        using OpenSHC::Game::GameMode2;
        using OpenSHC::Map::Location::Point8ShortXY;

        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
          WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
         */
        /*
          WARNING: Enum "DPERRInt": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004A2A90
        undefined4 PathFindingState::spreadAlgorithmForFlagsAndBraziersUnk(
            int playerID, uint x, uint y, int param_4, int param_5)
        {
            int* piVar1;
            int sVar2;
            int tile;
            uint uVar3;
            int iVar4;
            int iVar5;
            short* psVar6;
            int (*paiVar7)[8];
            int iVar8;
            int local_8;
            int local_4;
            uVar3 = y;
            if (399 < x || 399 < y || *(char*)(y * 400 + 0x21aec98 + x) == '\0') {
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
            this->searchQueue.yQueue[0] = (short)uVar3;
            this->searchQueue.xQueue[0] = (short)x;
            this->searchQueue.tilesQueue[0]
                = DAT_ViewportRenderState::instance.translationMatrix[uVar3].addXgetTile + x;
            DAT_TileMapState::instance.CertainPathLayer[this->searchQueue.tilesQueue[0]] = 1;
            DAT_TileMapState::instance.WalkLayer[this->searchQueue.tilesQueue[0]] = (short)this->searchGeneration;
            if (this->searchQueue.readIndex != this->searchQueue.writeIndex) {
                while (
                    (tile = this->searchQueue.tilesQueue[this->searchQueue.readIndex], -1 < tile && (tile < 0x13a10))) {
                    local_4 = (int)this->searchQueue.xQueue[this->searchQueue.readIndex];
                    sVar2 = (int)this->searchQueue.yQueue[this->searchQueue.readIndex];
                    this->searchQueue.currentDistance = (int)DAT_TileMapState::instance.CertainPathLayer[tile];
                    if (0x13a10 < this->searchQueue.currentDistance) {
                        return (undefined4)(0);
                    }
                    if (param_4 < this->searchQueue.currentDistance) {
                        return (undefined4)(0);
                    }
                    iVar8 = 0;
                    iVar5 = (int)DAT_TileMapState::instance.EntityLayer[tile];
                    if (DAT_TileMapState::instance.EntityLayer[tile] != 0) {
                        while (iVar8 = iVar8 + 1, iVar8 < 10) {
                            if (DAT_EntityState::instance.entityArray[iVar5].owner == playerID) {
                                switch (DAT_EntityState::instance.entityArray[iVar5].entityType) {
                                case OpenSHC::Map::Entities::ET_BRAZIER:
                                    if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)
                                        && (DAT_EntityState::instance.entityArray[iVar5].logicalState != 3)) {
                                        if (param_5 == 0) {
                                            return (undefined4)(1);
                                        }
                                        local_8 = 0;
                                        y = 0;
                                        MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingCost,
                                            DAT_BuildingsState::ptr)(
                                            OpenSHC::Commands::M_MAPPER_BRAZIER, &local_8, (int*)&y);
                                        piVar1
                                            = DAT_GameState::instance
                                                  .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                                  .startResources
                                            + 0xf;
                                        *piVar1 = *piVar1 + y;
                                    }
                                case OpenSHC::Map::Entities::ET_FLAG_1:
                                case OpenSHC::Map::Entities::ET_FLAG_4:
                                case OpenSHC::Map::Entities::ET_FLAG_2:
                                case OpenSHC::Map::Entities::ET_FLAG_3:
                                case OpenSHC::Map::Entities::ET_HEADS_ON_SPIKES:
                                    if (param_5 == 0) {
                                        return (undefined4)(1);
                                    }
                                    MACRO_CALL_MEMBER(OpenSHC::Map::Entities::EntityState_Func::destroyEntitiesOnTile,
                                        DAT_EntityState::ptr)(tile);
                                }
                            }
                            iVar4 = (int)DAT_EntityState::instance.entityArray[iVar5].nextEntityOnThisTileByID;
                            if ((iVar5 == iVar4) || (iVar5 = iVar4, iVar4 == 0))
                                break;
                        }
                    }
                    for (int _direction = 0; _direction < 8; _direction = _direction + 2) {
                        iVar5 = DAT_TileMapState::instance.directionTranslationMatrix[sVar2][_direction] + tile;
                        if (DAT_TileMapState::instance.WalkLayer[iVar5] != this->searchGeneration
                            && (DAT_TileMapState::instance.LogicLayer[iVar5] & 0x30) == 0) {
                            DAT_TileMapState::instance.CertainPathLayer[iVar5]
                                = (short)this->searchQueue.currentDistance + 1;
                            DAT_TileMapState::instance.WalkLayer[iVar5] = (short)this->searchGeneration;
                            this->searchQueue.xQueue[this->searchQueue.writeIndex]
                                = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction].short_.xOffset + (short)local_4;
                            this->searchQueue.yQueue[this->searchQueue.writeIndex] = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction].short_.yOffset + sVar2;
                            this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = iVar5;
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
