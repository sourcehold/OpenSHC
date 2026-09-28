#include "../PathFindingState.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Location/Point8IntXY.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {
        using OpenSHC::Map::Location::Point8IntXY;

        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
          Checks all cardinal neighbours of target tile (param_4, param_5) for tiles that are   height-compatible
          (within param_5 height margin) and navigable from (param_2, param_3) via
          calculateCanPlayerUnitsNavigateToAreaFromArea. Uses calcApproxEuclideanDistance to pick the   closest valid
          neighbour. Stores the result in PathFindingState.climbX/climbY. Returns 1 if a   suitable tile was found, 0
          otherwise.      renamed by: Claude Sonnet 4.6
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004A5DA0
        undefined4 PathFindingState::findBestAdjacentClimbTileToTarget(
            int param_1, uint param_2, uint param_3, uint param_4, uint param_5)
        {
            ushort uVar1;
            int iVar2;
            int (*paiVar3)[8];
            uint uVar4;
            int iVar5;
            int iVar6;
            int* piVar7;
            uint local_18;
            int local_10;
            undefined4 local_8;
            if (399 < param_2 || 399 < param_3 || DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[param_3 * 400 + param_2] == '\0') {
                return (undefined4)(0);
            }
            if (param_4 <= 399 && param_5 <= 399 && DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[param_5 * 400 + param_4] != '\0') {
                iVar5 = DAT_ViewportRenderState::instance.translationMatrix[param_5].addXgetTile + param_4;
                local_18 = (uint)DAT_TileMapState::instance.HeightLayer[iVar5];
                uVar1
                    = DAT_TileMapState::instance
                          .PathConnectionLayer[DAT_ViewportRenderState::instance.translationMatrix[param_3].addXgetTile
                              + param_2];
                local_8 = 0;
                local_10 = 1000;
                if (DAT_TileMapState::instance.BuildingLayer[iVar5] != 0) {
                    iVar2 = MACRO_CALL_MEMBER(
                        OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingHeightForBuildingID,
                        DAT_BuildingsState::ptr)((int)DAT_TileMapState::instance.BuildingLayer[iVar5]);
                    local_18 = local_18 + iVar2;
                }
                paiVar3 = DAT_TileMapState::instance.directionTranslationMatrix + param_5;
                piVar7 = &DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[0].int_.yOffset;
                do {
                    iVar6 = (*paiVar3)[0] + iVar5;
                    iVar2 = MACRO_CALL_MEMBER(
                        OpenSHC::Map::Navigation::PathFindingState_Func::calculateCanPlayerUnitsNavigateToAreaFromArea,
                        this)(param_1, (dword)((int)((short)uVar1)),
                        (dword)((int)((short)DAT_TileMapState::instance.PathConnectionLayer[iVar6])), 0);
                    if (iVar2 != 0) {
                        uVar4 = (uint)DAT_TileMapState::instance.HeightLayer[iVar6];
                        if (DAT_TileMapState::instance.BuildingLayer[iVar6] != 0) {
                            iVar2 = MACRO_CALL_MEMBER(
                                OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingHeightForBuildingID,
                                DAT_BuildingsState::ptr)((int)DAT_TileMapState::instance.BuildingLayer[iVar6]);
                            uVar4 = uVar4 + iVar2;
                        }
                        if ((int)local_18 <= (int)(uVar4 + 0x10) && (int)(uVar4 - 0x10) <= (int)local_18
                            && (MACRO_CALL_MEMBER(
                                    OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                                    DAT_DirectionAlgorithmState::ptr)(param_2, (int)(param_3),
                                    (int)(((Point8IntXY*)(piVar7 + -1))->xOffset + param_4), (int)(*piVar7 + param_5)),
                                DAT_DirectionAlgorithmState::instance.distanceHigh < local_10)) {
                            local_10 = DAT_DirectionAlgorithmState::instance.distanceHigh;
                            this->climbX = ((Point8IntXY*)(piVar7 + -1))->xOffset + param_4;
                            this->climbY = *piVar7 + param_5;
                            local_8 = 1;
                        }
                    }
                    paiVar3 = (int (*)[8])(*paiVar3 + 1);
                    piVar7 = piVar7 + 2;
                } while ((int)piVar7 < 0xb4908c);
                return (undefined4)(local_8);
            }
            return (undefined4)(0);
        }

    }
}
}
