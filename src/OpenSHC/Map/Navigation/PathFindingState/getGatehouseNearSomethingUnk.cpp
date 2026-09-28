#include "../PathFindingState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_ClimbLogicDefinedData.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalStateShort.hpp"
#include "OpenSHC/Map/Buildings/BuildingTypeShort.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        using OpenSHC::Map::Buildings::BuildingLogicalState;
        using OpenSHC::Map::Buildings::BuildingType;
            using OpenSHC::Map::Buildings::BuildingLogicalStateShort;
            using OpenSHC::Map::Buildings::BuildingTypeShort;

        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004A08E0
        int PathFindingState::getGatehouseNearSomethingUnk(int param_1, int param_2, int param_3, int maxDistance)
        {
            short sVar1;
            BuildingLogicalStateShort BVar2;
            BuildingTypeShort BVar3;
            int iVar4;
            int iVar5;
            int iVar6;
            int iVar7;
            int (*paiVar8)[8];
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
                while ((iVar4 = this->searchQueue.tilesQueue[this->searchQueue.readIndex],
                    -1 < iVar4 && (iVar4 < 0x13a10))) {
                    sVar1 = this->searchQueue.yQueue[this->searchQueue.readIndex];
                    this->searchQueue.currentDistance = (int)DAT_TileMapState::instance.CertainPathLayer[iVar4];
                    if (0x13a10 < this->searchQueue.currentDistance) {
                        return 0;
                    }
                    if (maxDistance < this->searchQueue.currentDistance) {
                        return 0;
                    }
                    iVar7 = 0;
                    paiVar8 = DAT_TileMapState::instance.directionTranslationMatrix + sVar1;
                    do {
                        iVar6 = (*paiVar8)[0] + iVar4;
                        iVar5 = (int)DAT_TileMapState::instance.BuildingLayer[iVar6];
                        if (((iVar5 != 0)
                                || ((DAT_TileMapState::instance.PathLinkageLayer[iVar4]
                                        & DAT_ClimbLogicDefinedData::instance.BitFlagHelperForPathLinkage[iVar7])
                                    != 0))
                            && (DAT_TileMapState::instance.WalkLayer[iVar6] != this->searchGeneration)) {
                            DAT_TileMapState::instance.CertainPathLayer[iVar6]
                                = (short)this->searchQueue.currentDistance + 1;
                            DAT_TileMapState::instance.WalkLayer[iVar6] = (short)this->searchGeneration;
                            this->searchQueue.yQueue[this->searchQueue.writeIndex]
                                = *(short*)((int)DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix
                                      + iVar7 * 8 + 4)
                                + sVar1;
                            this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = iVar6;
                            this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                            if (0x13a0f < this->searchQueue.writeIndex) {
                                this->searchQueue.writeIndex = 0;
                            }
                            if (((((iVar5 != 0)
                                      && (DAT_GameState::instance.mapAndTime.playerTeams[param_1]
                                          != DAT_GameState::instance.mapAndTime
                                              .playerTeams[DAT_BuildingsState::instance.buildings[iVar5].owner]))
                                     && ((BVar2 = DAT_BuildingsState::instance.buildings[iVar5].logicalState,
                                         BVar2 != ((BuildingLogicalState)0)
                                             && (BVar2 != OpenSHC::Map::Buildings::BLS_REMOVE))))
                                    && ((BVar3 = DAT_BuildingsState::instance.buildings[iVar5].buildingType,
                                        BVar3 == OpenSHC::Map::Buildings::BT_GATEHOUSELARGE
                                            || (BVar3 == OpenSHC::Map::Buildings::BT_GATEHOUSESMALL))))
                                && (DAT_BuildingsState::instance.buildings[iVar5].fireDuration == 0)) {
                                return iVar5;
                            }
                        }
                        iVar7 = iVar7 + 1;
                        paiVar8 = (int (*)[8])(*paiVar8 + 1);
                    } while (iVar7 < 8);
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
