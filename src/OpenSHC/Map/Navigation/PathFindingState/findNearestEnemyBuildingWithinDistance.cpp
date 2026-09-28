#include "../PathFindingState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalStateShort.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        using OpenSHC::Map::Buildings::BuildingLogicalState;
        using OpenSHC::Map::Buildings::BuildingLogicalStateShort;

        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
          BFS from (param_2, param_3) up to distance param_4, checking each visited tile's BuildingLayer.   Returns the
          building ID of the first reachable enemy building (different team to param_1) that is   alive (logicalState !=
          0 and != 3), not on fire, and has a valid fire-related building parameter.   Returns 0 if none found. renamed
          by: Claude Sonnet 4.6
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004A0460
        int PathFindingState::findNearestEnemyBuildingWithinDistance(int param_1, int param_2, int param_3, int param_4)
        {
            BuildingLogicalStateShort BVar2;
            int iVar3;
            int iVar5;
            int (*paiVar6)[8];
            short* psVar7;
            this->searchGeneration = this->searchGeneration + 1;
            this->calculations = this->calculations + 1;
            if (32000 < this->searchGeneration) {
                this->searchGeneration = 1;
                MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                    0x27420, '\0', (void*)((int)(DAT_TileMapState::instance.WalkLayer)));
            }
            this->searchQueue.yQueue[0] = (short)param_3;
            this->searchQueue.readIndex = 0;
            this->searchQueue.writeIndex = 1;
            this->searchQueue.currentDistance = 1;
            this->searchQueue.tilesQueue[0]
                = DAT_ViewportRenderState::instance.translationMatrix[param_3].addXgetTile + param_2;
            DAT_TileMapState::instance.CertainPathLayer[this->searchQueue.tilesQueue[0]] = 1;
            DAT_TileMapState::instance.WalkLayer[this->searchQueue.tilesQueue[0]] = (short)this->searchGeneration;
            if (this->searchQueue.readIndex != this->searchQueue.writeIndex) {
                while ((iVar3 = this->searchQueue.tilesQueue[this->searchQueue.readIndex],
                    -1 < iVar3 && (iVar3 < 0x13a10))) {
                    short sVar1 = this->searchQueue.yQueue[this->searchQueue.readIndex];
                    this->searchQueue.currentDistance = (int)DAT_TileMapState::instance.CertainPathLayer[iVar3];
                    if (0x13a10 < this->searchQueue.currentDistance) {
                        return 0;
                    }
                    if (param_4 < this->searchQueue.currentDistance) {
                        return 0;
                    }
                    for (int _direction = 0; _direction < 8; _direction = _direction + 1) {
                        int iVar4 = DAT_TileMapState::instance.directionTranslationMatrix[sVar1][_direction] + iVar3;
                        if ((DAT_TileMapState::instance.LogicLayer[iVar4] & 0x30) == 0
                            && DAT_TileMapState::instance.WalkLayer[iVar4] != this->searchGeneration) {
                            DAT_TileMapState::instance.CertainPathLayer[iVar4]
                                = (short)this->searchQueue.currentDistance + 1;
                            DAT_TileMapState::instance.WalkLayer[iVar4] = (short)this->searchGeneration;
                            this->searchQueue.yQueue[this->searchQueue.writeIndex] = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction].short_.yOffset + sVar1;
                            this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = iVar4;
                            this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                            if (0x13a0f < this->searchQueue.writeIndex) {
                                this->searchQueue.writeIndex = 0;
                            }
                            iVar4 = (int)DAT_TileMapState::instance.BuildingLayer[iVar4];
                            if (iVar4 != 0
                                && DAT_GameState::instance.mapAndTime.playerTeams[param_1]
                                    != DAT_GameState::instance.mapAndTime
                                        .playerTeams[DAT_BuildingsState::instance.buildings[iVar4].owner]
                                && (BVar2 = DAT_BuildingsState::instance.buildings[iVar4].logicalState,
                                    BVar2 != ((BuildingLogicalState)0))
                                && BVar2 != OpenSHC::Map::Buildings::BLS_REMOVE
                                && DAT_BuildingsState::instance.buildings[iVar4].fireDuration == 0
                                && (iVar5 = MACRO_CALL_MEMBER(
                                        OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingFlammabilityFactor,
                                        DAT_BuildingsState::ptr)(iVar4),
                                    iVar5 != 0 && (iVar5 != 4))) {
                                return iVar4;
                            }
                        }
                    }

                    this->searchQueue.readIndex = this->searchQueue.readIndex + 1;
                    if (0x13a0f < this->searchQueue.readIndex) {
                        this->searchQueue.readIndex = 0;
                    }
                    if (this->searchQueue.readIndex == this->searchQueue.writeIndex) {
                        return 0;
                    }
                }
            }
            return 0;
        }

    }
}
}
