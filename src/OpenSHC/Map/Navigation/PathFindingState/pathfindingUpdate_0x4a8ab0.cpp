#include "../PathFindingState.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Entities/EntityState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/DE/SHCDE/eSFX.hpp"
#include "OpenSHC/Map/Location/Point8IntXY.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        using OpenSHC::DE::SHCDE::eSFX;
        using OpenSHC::Map::Location::Point8IntXY;

        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004A8AB0
        void PathFindingState::pathfindingUpdate_0x4a8ab0(int param_1)
        {
            ushort uVar1;
            ushort uVar2;
            int (*paiVar7)[8];
            int iVar8;
            int iVar9;
            int iVar10;
            int* piVar11;
            short* psVar12;
            bool bVar13;
            int local_24;
            short* local_18;
            short* local_14;
            int* local_10;
            this->searchGeneration = this->searchGeneration + 1;
            this->calculations = this->calculations + 1;
            if (32000 < this->searchGeneration) {
                this->searchGeneration = 1;
                MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                    0x27420, '\0', (void*)((int)(DAT_TileMapState::instance.WalkLayer)));
            }
            this->searchQueue.currentDistance = 1;
            this->searchQueue.readIndex = 0;
            this->searchQueue.writeIndex = 1;
            bVar13 = DAT_GameState::instance.mapAndTime.signpostIDs[0] != 0;
            local_24 = 0x9d08;
            if (bVar13) {
                this->searchQueue.xQueue[0]
                    = DAT_BuildingsState::instance.buildings[DAT_GameState::instance.mapAndTime.signpostIDs[0]].x;
                this->searchQueue.yQueue[0]
                    = DAT_BuildingsState::instance.buildings[DAT_GameState::instance.mapAndTime.signpostIDs[0]].y;
                this->searchQueue.tilesQueue[0]
                    = DAT_ViewportRenderState::instance.translationMatrix[this->searchQueue.yQueue[0]].addXgetTile
                    + (int)this->searchQueue.xQueue[0];
                DAT_TileMapState::instance.CertainPathLayer[this->searchQueue.tilesQueue[0]] = 1;
                DAT_TileMapState::instance.WalkLayer[this->searchQueue.tilesQueue[0]] = (short)this->searchGeneration;
            }
            uint uVar6 = (uint)bVar13;
            if (DAT_GameState::instance.mapAndTime.signpostIDs[1] != 0) {
                uVar1 = DAT_BuildingsState::instance.buildings[DAT_GameState::instance.mapAndTime.signpostIDs[1]].x;
                uVar2 = DAT_BuildingsState::instance.buildings[DAT_GameState::instance.mapAndTime.signpostIDs[1]].y;
                this->searchQueue.yQueue[uVar6] = uVar2;
                this->searchQueue.xQueue[uVar6] = uVar1;
                iVar9
                    = DAT_ViewportRenderState::instance.translationMatrix[(short)uVar2].addXgetTile + (int)(short)uVar1;
                this->searchQueue.tilesQueue[uVar6] = iVar9;
                DAT_TileMapState::instance.CertainPathLayer[iVar9] = (short)this->searchQueue.currentDistance;
                DAT_TileMapState::instance.WalkLayer[this->searchQueue.tilesQueue[uVar6]]
                    = (short)this->searchGeneration;
                uVar6 = uVar6 + 1;
            }
            if (DAT_GameState::instance.mapAndTime.signpostIDs[2] != 0) {
                uVar1 = DAT_BuildingsState::instance.buildings[DAT_GameState::instance.mapAndTime.signpostIDs[2]].x;
                uVar2 = DAT_BuildingsState::instance.buildings[DAT_GameState::instance.mapAndTime.signpostIDs[2]].y;
                this->searchQueue.yQueue[uVar6] = uVar2;
                this->searchQueue.xQueue[uVar6] = uVar1;
                iVar9
                    = DAT_ViewportRenderState::instance.translationMatrix[(short)uVar2].addXgetTile + (int)(short)uVar1;
                this->searchQueue.tilesQueue[uVar6] = iVar9;
                DAT_TileMapState::instance.CertainPathLayer[iVar9] = (short)this->searchQueue.currentDistance;
                DAT_TileMapState::instance.WalkLayer[this->searchQueue.tilesQueue[uVar6]]
                    = (short)this->searchGeneration;
                uVar6 = uVar6 + 1;
            }
            if (DAT_GameState::instance.mapAndTime.signpostIDs[3] != 0) {
                uVar1 = DAT_BuildingsState::instance.buildings[DAT_GameState::instance.mapAndTime.signpostIDs[3]].x;
                uVar2 = DAT_BuildingsState::instance.buildings[DAT_GameState::instance.mapAndTime.signpostIDs[3]].y;
                this->searchQueue.yQueue[uVar6] = uVar2;
                this->searchQueue.xQueue[uVar6] = uVar1;
                iVar9
                    = DAT_ViewportRenderState::instance.translationMatrix[(short)uVar2].addXgetTile + (int)(short)uVar1;
                this->searchQueue.tilesQueue[uVar6] = iVar9;
                DAT_TileMapState::instance.CertainPathLayer[iVar9] = (short)this->searchQueue.currentDistance;
                DAT_TileMapState::instance.WalkLayer[this->searchQueue.tilesQueue[uVar6]]
                    = (short)this->searchGeneration;
                uVar6 = uVar6 + 1;
            }
            if (DAT_GameState::instance.mapAndTime.signpostIDs[4] != 0) {
                uVar1 = DAT_BuildingsState::instance.buildings[DAT_GameState::instance.mapAndTime.signpostIDs[4]].x;
                uVar2 = DAT_BuildingsState::instance.buildings[DAT_GameState::instance.mapAndTime.signpostIDs[4]].y;
                this->searchQueue.yQueue[uVar6] = uVar2;
                this->searchQueue.xQueue[uVar6] = uVar1;
                iVar9
                    = DAT_ViewportRenderState::instance.translationMatrix[(short)uVar2].addXgetTile + (int)(short)uVar1;
                this->searchQueue.tilesQueue[uVar6] = iVar9;
                DAT_TileMapState::instance.CertainPathLayer[iVar9] = (short)this->searchQueue.currentDistance;
                DAT_TileMapState::instance.WalkLayer[this->searchQueue.tilesQueue[uVar6]]
                    = (short)this->searchGeneration;
                uVar6 = uVar6 + 1;
            }
            if (DAT_GameState::instance.mapAndTime.signpostIDs[5] != 0) {
                uVar1 = DAT_BuildingsState::instance.buildings[DAT_GameState::instance.mapAndTime.signpostIDs[5]].x;
                uVar2 = DAT_BuildingsState::instance.buildings[DAT_GameState::instance.mapAndTime.signpostIDs[5]].y;
                this->searchQueue.yQueue[uVar6] = uVar2;
                this->searchQueue.xQueue[uVar6] = uVar1;
                iVar9
                    = DAT_ViewportRenderState::instance.translationMatrix[(short)uVar2].addXgetTile + (int)(short)uVar1;
                this->searchQueue.tilesQueue[uVar6] = iVar9;
                DAT_TileMapState::instance.CertainPathLayer[iVar9] = (short)this->searchQueue.currentDistance;
                DAT_TileMapState::instance.WalkLayer[this->searchQueue.tilesQueue[uVar6]]
                    = (short)this->searchGeneration;
                uVar6 = uVar6 + 1;
            }
            if (DAT_GameState::instance.mapAndTime.signpostIDs[6] != 0) {
                uVar1 = DAT_BuildingsState::instance.buildings[DAT_GameState::instance.mapAndTime.signpostIDs[6]].x;
                uVar2 = DAT_BuildingsState::instance.buildings[DAT_GameState::instance.mapAndTime.signpostIDs[6]].y;
                this->searchQueue.yQueue[uVar6] = uVar2;
                this->searchQueue.xQueue[uVar6] = uVar1;
                iVar9
                    = (int)(short)uVar1 + DAT_ViewportRenderState::instance.translationMatrix[(short)uVar2].addXgetTile;
                this->searchQueue.tilesQueue[uVar6] = iVar9;
                DAT_TileMapState::instance.CertainPathLayer[iVar9] = (short)this->searchQueue.currentDistance;
                DAT_TileMapState::instance.WalkLayer[this->searchQueue.tilesQueue[uVar6]]
                    = (short)this->searchGeneration;
                uVar6 = uVar6 + 1;
            }
            if (DAT_GameState::instance.mapAndTime.signpostIDs[7] != 0) {
                uVar1 = DAT_BuildingsState::instance.buildings[DAT_GameState::instance.mapAndTime.signpostIDs[7]].x;
                uVar2 = DAT_BuildingsState::instance.buildings[DAT_GameState::instance.mapAndTime.signpostIDs[7]].y;
                this->searchQueue.yQueue[uVar6] = uVar2;
                this->searchQueue.xQueue[uVar6] = uVar1;
                iVar9
                    = DAT_ViewportRenderState::instance.translationMatrix[(short)uVar2].addXgetTile + (int)(short)uVar1;
                this->searchQueue.tilesQueue[uVar6] = iVar9;
                DAT_TileMapState::instance.CertainPathLayer[iVar9] = (short)this->searchQueue.currentDistance;
                DAT_TileMapState::instance.WalkLayer[this->searchQueue.tilesQueue[uVar6]]
                    = (short)this->searchGeneration;
            }
            if (this->searchQueue.readIndex != this->searchQueue.writeIndex) {
                while (uVar6 = this->searchQueue.tilesQueue[this->searchQueue.readIndex], uVar6 < 0x13a10) {
                    int sVar3 = (int)this->searchQueue.xQueue[this->searchQueue.readIndex];
                    int sVar4 = (int)this->searchQueue.yQueue[this->searchQueue.readIndex];
                    this->searchQueue.currentDistance = (int)DAT_TileMapState::instance.CertainPathLayer[uVar6];
                    if ((0x13a10 < this->searchQueue.currentDistance) || (this->searchQueue.currentDistance > param_1))
                        break;
                    local_10 = this->searchQueue.tilesQueue + local_24;
                    local_14 = this->searchQueue.yQueue + local_24;
                    local_18 = this->searchQueue.xQueue + local_24;
                    paiVar7 = DAT_TileMapState::instance.directionTranslationMatrix + sVar4;
                    piVar11 = &DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[0].int_.yOffset;
                    do {
                        iVar9 = (*paiVar7)[0] + uVar6;
                        uint uVar5 = DAT_TileMapState::instance.LogicLayer[iVar9];
                        if (DAT_TileMapState::instance.WalkLayer[iVar9] != this->searchGeneration
                            && (uVar5 & 0x30) == 0) {
                            DAT_TileMapState::instance.CertainPathLayer[iVar9]
                                = (short)this->searchQueue.currentDistance + 1;
                            iVar8 = ((Point8IntXY*)(piVar11 + -1))->xOffset;
                            DAT_TileMapState::instance.WalkLayer[iVar9] = (short)this->searchGeneration;
                            this->searchQueue.xQueue[this->searchQueue.writeIndex] = (short)iVar8 + sVar3;
                            this->searchQueue.yQueue[this->searchQueue.writeIndex] = (short)*piVar11 + sVar4;
                            this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = iVar9;
                            if (DAT_TileMapState::instance.BuildingLayer[iVar9] != 0) {
                                iVar8 = (int)DAT_TileMapState::instance.BuildingLayer[iVar9];
                                iVar10 = (int)(short)DAT_BuildingsState::instance.buildings[iVar8].buildingType;
                                switch (iVar10) {
                                case 10:
                                case 0xb:
                                case 0x13:
                                case 0x24:
                                case 0x25:
                                case 0x26:
                                case 0x28:
                                case 0x29:
                                case 0x2a:
                                case 0x34:
                                case 0x37:
                                case 0x47:
                                case 0x48:
                                case 0x49:
                                    break;
                                default:
                                    DAT_TileMapState::instance.showNoRubbleWhenDestroyingBuilding
                                        = (int)(DAT_BuildingDefinedData::instance
                                                    .BuildingShowRubbleWhenDestroyed[iVar10]
                                            == 0);
                                    MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::destroyBuilding,
                                        DAT_BuildingsState::ptr)(iVar8);
                                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation,
                                        DAT_SFXState::ptr)((int)(short)DAT_BuildingsState::instance.buildings[iVar8].x,
                                        (int)((short)DAT_BuildingsState::instance.buildings[iVar8].y),
                                        OpenSHC::DE::SHCDE::FX_BUILDING_SMASH);
                                }
                            }
                            if ((uVar5 & 0x100) != 0 && (uVar5 & 2) == 0) {
                                MACRO_CALL_MEMBER(OpenSHC::Map::Entities::EntityState_Func::destroyEntitiesOnTile,
                                    DAT_EntityState::ptr)(iVar9);
                                DAT_TileMapState::instance.LogicLayer[iVar9]
                                    = DAT_TileMapState::instance.LogicLayer[iVar9] & 0xffbef4ff;
                                iVar8 = ((Point8IntXY*)(piVar11 + -1))->xOffset;
                                local_24 = local_24 + 1;
                                DAT_TileMapState::instance.HeightLayer[iVar9]
                                    = DAT_TileMapState::instance.DefaultHeightLayer[iVar9];
                                DAT_TileMapState::instance.DamageLayer[iVar9] = 0;
                                this->toggleUpdateSeparateAreaTileMap = 1;
                                DAT_TileMapState::instance.field204_0x554a30 = 1;
                                *local_18 = (short)iVar8 + sVar3;
                                *local_14 = (short)*piVar11 + sVar4;
                                local_14 = local_14 + 1;
                                local_18 = local_18 + 1;
                                *local_10 = iVar9;
                                local_10 = local_10 + 1;
                            }
                            if ((uVar5 & 0x40000000) != 0) {
                                MACRO_CALL_MEMBER(
                                    OpenSHC::Map::TileMapState_Func::clearMoatDataAtTile, DAT_TileMapState::ptr)(
                                    ((Point8IntXY*)(piVar11 + -1))->xOffset + (int)sVar3, (int)(*piVar11 + sVar4));
                                iVar8 = ((Point8IntXY*)(piVar11 + -1))->xOffset;
                                local_24 = local_24 + 1;
                                DAT_TileMapState::instance.HeightLayer[iVar9] = 8;
                                DAT_TileMapState::instance.LogicLayer[iVar9]
                                    = DAT_TileMapState::instance.LogicLayer[iVar9] & 0xbfffbfff;
                                *local_18 = (short)iVar8 + sVar3;
                                *local_14 = (short)*piVar11 + sVar4;
                                local_18 = local_18 + 1;
                                *local_10 = iVar9;
                                local_10 = local_10 + 1;
                                local_14 = local_14 + 1;
                            }
                            if ((uVar5 & 8) != 0) {
                                DAT_TileMapState::instance.LogicLayer[iVar9]
                                    = DAT_TileMapState::instance.LogicLayer[iVar9] & 0xfffffff7;
                            }
                            this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                            if (0x13a0f < this->searchQueue.writeIndex) {
                                this->searchQueue.writeIndex = 0;
                            }
                        }
                        paiVar7 = (int (*)[8])(*paiVar7 + 1);
                        piVar11 = piVar11 + 2;
                    } while ((int)piVar11 < 0xb4908c);
                    this->searchQueue.readIndex = this->searchQueue.readIndex + 1;
                    if (0x13a0f < this->searchQueue.readIndex) {
                        this->searchQueue.readIndex = 0;
                    }
                    if (this->searchQueue.readIndex == this->searchQueue.writeIndex)
                        break;
                }
            }
            if (0x9d08 < local_24) {
                psVar12 = this->searchQueue.yQueue + 0x9d08;
                piVar11 = this->searchQueue.tilesQueue + 0x9d08;
                local_24 = local_24 + -0x9d08;
                do {
                    MACRO_CALL_MEMBER(
                        OpenSHC::Map::Navigation::PathFindingState_Func::updatePathLinkagesInAllEightDirections, this)(
                        (int)*psVar12, (int)(*piVar11));
                    MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updateWalkAndPathLayer, this)(
                        7, (uint)(psVar12[0x13a10]), (uint)((int)*psVar12));
                    piVar11 = piVar11 + 1;
                    psVar12 = psVar12 + 1;
                    local_24 = local_24 + -1;
                } while (local_24 != 0);
            }
            return;
        }

    }
}
}
