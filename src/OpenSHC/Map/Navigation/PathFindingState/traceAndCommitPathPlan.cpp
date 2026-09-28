#include "../PathFindingState.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_ClimbLogicDefinedData.hpp"
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
        // FUNCTION: STRONGHOLDCRUSADER 0x004A97D0
        void PathFindingState::traceAndCommitPathPlan(uint x, uint y, uint x2, uint y2, int param_5)
        {
            uint uVar3;
            int iVar4;
            uint uVar5;
            if (x < 400 && y < 400 && DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y * 400 + x] != '\0' && x2 < 400 && y2 < 400
                && DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y2 * 400 + x2] != '\0') {
                uint tile = DAT_ViewportRenderState::instance.translationMatrix[y2].addXgetTile + x2;
                int iVar2 = DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile;
                short sVar1 = DAT_TileMapState::instance.WalkLayer[tile];
                x2 = 0;
                this->field49_0x94 = 0;
                y = (int)DAT_TileMapState::instance.CertainPathLayer[tile];
                do {
                    if (tile == iVar2 + x)
                        break;
                    uint _theDirection = 8;
                    uint _direction = 0;
                    do {
                        if (param_5 == 1) {
                            if ((DAT_ClimbLogicDefinedData::instance.BitFlagHelperForPathLinkage[_direction]
                                    & DAT_TileMapState::instance.PathLinkageLayer[tile])
                                == 0)
                                goto LAB_004a99f7;
                        LAB_004a99b6:
                            uint uVar3 = DAT_TileMapState::instance.directionTranslationMatrix[y2][_direction] + tile;
                            if (DAT_TileMapState::instance.WalkLayer[uVar3] == sVar1
                                && (uVar5 = (uint)DAT_TileMapState::instance.CertainPathLayer[uVar3],
                                    (int)(y - 2) <= (int)uVar5)
                                && (int)uVar5 < (int)y) {
                                _theDirection = _direction;
                                y = uVar5;
                                x2 = uVar3;
                            }
                        } else {
                            if (param_5 != 2) {
                                if (param_5 == 3
                                    && (DAT_ClimbLogicDefinedData::instance.BitFlagHelperForPathLinkage[_direction]
                                           & DAT_TileMapState::instance.PathLinkageLayer[tile])
                                        == 0) {
                                    if ((_direction & 1) == 0
                                        && (iVar4
                                            = DAT_TileMapState::instance.directionTranslationMatrix[y2][_direction]
                                                + tile,
                                            DAT_TileMapState::instance.BuildingLayer[tile] == 0
                                                && (DAT_TileMapState::instance.BuildingLayer[iVar4] == 0))) {
                                        if ((DAT_TileMapState::instance.LogicLayer[tile] & 0x100U) == 0) {
                                            uVar3 = DAT_TileMapState::instance.LogicLayer[iVar4] & 0x100;
                                            goto joined_r0x004a99a9;
                                        }
                                        if ((DAT_TileMapState::instance.LogicLayer[iVar4] & 0x100U) == 0)
                                            goto LAB_004a99b6;
                                    }
                                    goto LAB_004a99f7;
                                }
                                goto LAB_004a99b6;
                            }
                            if ((DAT_ClimbLogicDefinedData::instance.BitFlagHelperForPathLinkage[_direction]
                                    & DAT_TileMapState::instance.PathLinkageLayer[tile])
                                != 0)
                                goto LAB_004a99b6;
                            iVar4 = DAT_TileMapState::instance.directionTranslationMatrix[y2][_direction] + tile;
                            if ((DAT_TileMapState::instance.LogicLayer[tile] & 0x40000000U) == 0) {
                                uVar3 = DAT_TileMapState::instance.LogicLayer[iVar4] & 0x40000000;
                            joined_r0x004a99a9:
                                if (uVar3 != 0)
                                    goto LAB_004a99b6;
                            } else if ((DAT_TileMapState::instance.LogicLayer[iVar4] & 0xa5014b1U) == 0) {
                                if ((uint)DAT_TileMapState::instance.HeightLayer[tile]
                                        <= DAT_TileMapState::instance.HeightLayer[iVar4] + 0x10
                                    && (int)(DAT_TileMapState::instance.HeightLayer[iVar4] - 0x10)
                                        <= (int)(uint)DAT_TileMapState::instance.HeightLayer[tile])
                                    goto LAB_004a99b6;
                            }
                        }
                    LAB_004a99f7:
                        _direction = _direction + 1;
                    } while ((int)_direction < 8);
                    if (_theDirection == 8) {
                        /*
                          I guess this increment means "total recomputes of the path linkage layer"
                         */
                        this->DAT_lWys = this->DAT_lWys + 1;
                        this->searchQueue.pathPlanIndex = 0;
                        MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::
                                              updatePathLinkageLayerForEachBuildingAtEachTile,
                            this)();
                        MACRO_CALL_MEMBER(
                            OpenSHC::Map::Navigation::PathFindingState_Func::updateSeparateAreaTileMap, this)(1);
                        MACRO_CALL_MEMBER(
                            OpenSHC::Map::Buildings::BuildingsState_Func::updatePathLinkageLayerForAllBuildings,
                            DAT_BuildingsState::ptr)();
                        MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::
                                              updatePathLinkageLayerAtTileForSomeLogicalReason,
                            this)(tile, (int)(y2));
                        return;
                    }
                    y2 = y2
                        + *(int*)((int)DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix
                            + _theDirection * 8 + 4);
                    if ((DAT_TileMapState::instance.LogicLayer[x2] & 0x10000100U) != 0
                        && (DAT_TileMapState::instance.LogicLayer[x2] & 2U) == 0
                        && (DAT_TileMapState::instance.BuildingLayer[x2] == 0
                            || (DAT_BuildingDefinedData::instance
                                    .BuildingIsGateHouseArray[(short)DAT_BuildingsState::instance
                                            .buildings[DAT_TileMapState::instance.BuildingLayer[x2]]
                                            .buildingType]
                                == 0))) {
                        this->field49_0x94 = this->field49_0x94 + 1;
                    }
                    iVar4 = _theDirection + 4;
                    if (7 < iVar4) {
                        iVar4 = _theDirection - 4;
                    }
                    /*
                      commit path plan
                     */
                    if ((this->searchQueue.pathPlanIndex & 1) == 0) {
                        this->searchQueue.ptrPathPlan[(int)this->searchQueue.pathPlanIndex / 2] = (byte)iVar4;
                    } else {
                        this->searchQueue.ptrPathPlan[(int)this->searchQueue.pathPlanIndex / 2]
                            = this->searchQueue.ptrPathPlan[(int)this->searchQueue.pathPlanIndex / 2] & 0xf;
                        this->searchQueue.ptrPathPlan[(int)this->searchQueue.pathPlanIndex / 2]
                            = this->searchQueue.ptrPathPlan[(int)this->searchQueue.pathPlanIndex / 2]
                            + (byte)iVar4 * '\x10';
                    }
                    this->searchQueue.pathPlanIndex = this->searchQueue.pathPlanIndex + 1;
                    tile = x2;
                } while ((int)this->searchQueue.pathPlanIndex < 800);
                MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::reverseCurrentPathPlan, this)();
            }
            return;
        }

    }
}
}
