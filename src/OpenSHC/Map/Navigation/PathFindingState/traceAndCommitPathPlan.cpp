#include "../PathFindingState.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_ClimbLogicDefinedData.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
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
        void PathFindingState::traceAndCommitPathPlan(uint ySpace, uint y, uint x2, uint y2, int param_5)
        {
            if (ySpace <= 399 && y <= 399 && DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y * 400 + ySpace] != '\0'
                && x2 <= 399 && y2 <= 399
                && DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y2 * 400 + x2] != '\0') {
                int tileUnk = DAT_ViewportRenderState::instance.translationMatrix[y2].addXgetTile + x2;
                int distance = DAT_TileMapState::instance.CertainPathLayer[tileUnk];
                int generation = DAT_TileMapState::instance.WalkLayer[tileUnk];
                int start = DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + ySpace;
                int next = 0;
                int curY = y2;
                DAT_PathFindingState::instance.field49_0x94 = 0;
                if (tileUnk != start) {
                    do {
                        uint logic = DAT_TileMapState::instance.LogicLayer[tileUnk];
                        uint isWalkableArea = logic & 0x100;
                        uint isClimbable = logic & 0x40000000;
                        int best = 8;
                        for (int dir = 0; dir < 8; dir++) {
                            if (param_5 == 1) {
                                if ((DAT_TileMapState::instance.PathLinkageLayer[tileUnk]
                                        & DAT_ClimbLogicDefinedData::instance.BitFlagHelperForPathLinkage[dir])
                                    == 0)
                                    continue;
                            } else if (param_5 == 2) {
                                if ((DAT_TileMapState::instance.PathLinkageLayer[tileUnk]
                                        & DAT_ClimbLogicDefinedData::instance.BitFlagHelperForPathLinkage[dir])
                                    == 0) {
                                    int n = DAT_TileMapState::instance.directionTranslationMatrix[curY][dir] + tileUnk;
                                    if (isClimbable != 0) {
                                        if ((DAT_TileMapState::instance.LogicLayer[n] & 0xa5014b1) != 0)
                                            continue;
                                        int heightN = DAT_TileMapState::instance.HeightLayer[n];
                                        int high = DAT_TileMapState::instance.HeightLayer[tileUnk];
                                        if (high > heightN + 0x10)
                                            continue;
                                        if (high < heightN - 0x10)
                                            continue;
                                    } else if ((DAT_TileMapState::instance.LogicLayer[n] & 0x40000000) == 0) {
                                        continue;
                                    }
                                }
                            } else if (param_5 == 3) {
                                if ((DAT_TileMapState::instance.PathLinkageLayer[tileUnk]
                                        & DAT_ClimbLogicDefinedData::instance.BitFlagHelperForPathLinkage[dir])
                                    == 0) {
                                    if ((dir & 1) != 0)
                                        continue;
                                    int n = DAT_TileMapState::instance.directionTranslationMatrix[curY][dir] + tileUnk;
                                    if (DAT_TileMapState::instance.BuildingLayer[tileUnk] != 0)
                                        continue;
                                    if (DAT_TileMapState::instance.BuildingLayer[n] != 0)
                                        continue;
                                    if (isWalkableArea == 0) {
                                        if ((DAT_TileMapState::instance.LogicLayer[n] & 0x100) == 0)
                                            continue;
                                    } else if ((DAT_TileMapState::instance.LogicLayer[n] & 0x100) != 0) {
                                        continue;
                                    }
                                }
                            }
                            int n = DAT_TileMapState::instance.directionTranslationMatrix[curY][dir] + tileUnk;
                            if (DAT_TileMapState::instance.WalkLayer[n] == generation) {
                                int d = DAT_TileMapState::instance.CertainPathLayer[n];
                                if (d >= distance - 2 && d < distance) {
                                    next = n;
                                    distance = d;
                                    best = dir;
                                }
                            }
                        }
                        if (best == 8) {
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
                                this)(tileUnk, curY);
                            return;
                        }
                        tileUnk = next;
                        curY = curY + DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[best].int_.yOffset;
                        if ((DAT_TileMapState::instance.LogicLayer[tileUnk] & 0x10000100) != 0
                            && (DAT_TileMapState::instance.LogicLayer[tileUnk] & 2) == 0
                            && (DAT_TileMapState::instance.BuildingLayer[tileUnk] == 0
                                || DAT_BuildingDefinedData::instance
                                        .BuildingIsGateHouseArray[(short)DAT_BuildingsState::instance
                                                .buildings[DAT_TileMapState::instance.BuildingLayer[tileUnk]]
                                                .buildingType]
                                    == 0)) {
                            DAT_PathFindingState::instance.field49_0x94
                                = DAT_PathFindingState::instance.field49_0x94 + 1;
                        }
                        best = best + 4;
                        if (best > 7) {
                            best = best - 8;
                        }
                        /*
                          commit path plan
                         */
                        if ((this->searchQueue.pathPlanIndex & 1) == 0) {
                            this->searchQueue.ptrPathPlan[(int)this->searchQueue.pathPlanIndex / 2] = (byte)best;
                        } else {
                            this->searchQueue.ptrPathPlan[(int)this->searchQueue.pathPlanIndex / 2]
                                = this->searchQueue.ptrPathPlan[(int)this->searchQueue.pathPlanIndex / 2] & 0xf;
                            this->searchQueue.ptrPathPlan[(int)this->searchQueue.pathPlanIndex / 2]
                                = this->searchQueue.ptrPathPlan[(int)this->searchQueue.pathPlanIndex / 2]
                                + (byte)best * '\x10';
                        }
                        this->searchQueue.pathPlanIndex = this->searchQueue.pathPlanIndex + 1;
                    } while ((int)this->searchQueue.pathPlanIndex < 800 && tileUnk != start);
                }
                MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::reverseCurrentPathPlan, this)();
            }
            return;
        }

    }
}
}
