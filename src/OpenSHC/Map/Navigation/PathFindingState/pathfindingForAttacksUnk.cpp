#include "../PathFindingState.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Navigation/Algorithms/XYPair.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_ClimbLogicDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        using OpenSHC::Map::Navigation::Algorithms::XYPair;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004A75B0
        void PathFindingState::pathfindingForAttacksUnk(
            int tribeID, int buildingID, int param_3, dword param_4, int param_5)
        {
            uint uVar5;
            BOOLEnum BVar6;
            XYPair* pXVar8;
            uint uVar9;
            int iVar10;
            int* piVar11;
            int iVar12;
            int iVar13;
            int iVar14;
            int iVar15;
            int tile2;
            int local_28;
            int* local_24;
            int local_20;
            int iVar3 = (int)(short)DAT_BuildingsState::instance.buildings[buildingID].y;
            uint uVar7 = DAT_BuildingsState::instance.buildings[buildingID].widthOrHeight;
            iVar10 = (int)(short)DAT_BuildingsState::instance.buildings[buildingID].x;
            byte bVar1
                = DAT_TileMapState::instance.DefaultHeightLayer[DAT_BuildingsState::instance.buildings[buildingID]
                        .currentTilePositionAdjusted];
            short sVar2 = DAT_TribesState::instance.tribes[tribeID].selectionTargetUnitID;
            local_28 = 0;
            BOOLEnum BVar4 = MACRO_CALL_MEMBER(
                OpenSHC::Map::Units::TribesState_Func::isTribeAllAssassins, DAT_TribesState::ptr)(tribeID);
            param_3 = param_3 * 2;
            if (param_3 < 0x1f5) {
                if (param_3 < 0x32) {
                    param_3 = 0x32;
                }
            } else {
                param_3 = 500;
            }
            iVar14 = DAT_BuildingDefinedData::instance.BuildingAccessibleTilesCount[uVar7];
            local_20 = 0;
            tribeID = 0;
            if (0 < iVar14) {
                local_24 = &this->searchQueue.destinationsArray[0].tile2OrAHelper;
                do {
                    MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::setupBuildingEntrancesOffset,
                        DAT_BuildingsState::ptr)(uVar7, 1, local_20, 0);
                    iVar12 = DAT_ViewportRenderState::instance
                                 .translationMatrix[iVar3 + DAT_BuildingsState::instance.DAT_TempYOffset]
                                 .addXgetTile
                        + DAT_BuildingsState::instance.DAT_TempXOffset;
                    iVar13 = iVar12 + iVar10;
                    uVar5 = (uint)bVar1 - (uint) * (byte*)(iVar12 + 0x1d32c38 + iVar10);
                    uVar9 = (int)uVar5 >> 0x1f;
                    if ((int)((uVar5 ^ uVar9) - uVar9) < 0x20
                        && (((int)(short)DAT_TileMapState::instance.PathConnectionLayer[iVar13] == param_4
                                || (iVar12 = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::
                                                                   calculateCanPlayerUnitsNavigateToAreaFromArea,
                                        this)(param_5, (dword)((int)(param_4)),
                                        (dword)((
                                            int)((int)(short)DAT_TileMapState::instance.PathConnectionLayer[iVar13])),
                                        0),
                                    iVar12 != 0))
                            || ((BVar4 != FALSE
                                && (BVar6 = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::
                                                                  calculateCanReachUsingCachedAreaLogic,
                                        this)(DAT_UnitsState::instance.units[sVar2].tile, iVar13),
                                    BVar6 != FALSE))))
                        && (uVar5 = (int)DAT_BuildingsState::instance.buildings[buildingID].terrainHeightUnk
                                - (uint)DAT_TileMapState::instance.HeightLayer[iVar13],
                            uVar9 = (int)uVar5 >> 0x1f, (int)((uVar5 ^ uVar9) - uVar9) < 0x10)) {
                        ((PathHelper12*)(local_24 + -1))->tile1 = iVar13;
                        *local_24 = 0;
                        pXVar8 = DAT_ClimbLogicDefinedData::instance.CardinalHorizontalFirstSearchOrder;
                        do {
                            iVar12 = DAT_ViewportRenderState::instance
                                         .translationMatrix[pXVar8->y + DAT_BuildingsState::instance.DAT_TempYOffset
                                             + iVar3]
                                         .addXgetTile
                                + pXVar8->x + DAT_BuildingsState::instance.DAT_TempXOffset + iVar10;
                            if ((DAT_TileMapState::instance.LogicLayer[iVar12] & 0xf000000U) == 0
                                && DAT_TileMapState::instance.BuildingLayer[iVar12] == buildingID) {
                                *local_24 = iVar12;
                                break;
                            }
                            pXVar8 = pXVar8 + 1;
                        } while ((int)pXVar8 < 0xb39238);
                        local_24 = local_24 + 3;
                        local_28 = local_28 + 1;
                        if (param_3 <= local_28) {
                            return;
                        }
                    }
                    local_20 = local_20 + 1;
                    if (iVar14 <= local_20) {
                        local_20 = 0;
                    }
                    tribeID = tribeID + 1;
                } while (tribeID < iVar14);
            }
            iVar14 = uVar7 + 1;
            if (iVar14 < 0xe) {
                local_20 = 0x20;
                do {
                    iVar12 = DAT_BuildingDefinedData::instance.BuildingAccessibleTilesCount[iVar14];
                    iVar13 = 0;
                    tribeID = 0;
                    if (0 < iVar12) {
                        piVar11 = &((PathFindingStatePartB*)(this->climbData + 200))
                                       ->destinationsArray[local_28]
                                       .tile2OrAHelper;
                        do {
                            MACRO_CALL_MEMBER(
                                OpenSHC::Map::Buildings::BuildingsState_Func::setupBuildingEntrancesOffset,
                                DAT_BuildingsState::ptr)(iVar14, 1, iVar13, 0);
                            uVar7 = iVar3 + DAT_BuildingsState::instance.DAT_TempYOffset;
                            if ((uint)(DAT_BuildingsState::instance.DAT_TempXOffset + iVar10) < 400 && uVar7 < 400
                                && DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[uVar7 * 400 + DAT_BuildingsState::instance.DAT_TempXOffset
                                       + iVar10]
                                    != '\0') {
                                iVar15 = DAT_ViewportRenderState::instance.translationMatrix[uVar7].addXgetTile
                                    + DAT_BuildingsState::instance.DAT_TempXOffset;
                                tile2 = iVar15 + iVar10;
                                uVar7 = (uint)bVar1 - (uint) * (byte*)(iVar15 + 0x1d32c38 + iVar10);
                                uVar5 = (int)uVar7 >> 0x1f;
                                if ((int)((uVar7 ^ uVar5) - uVar5) < 0x20
                                    && (((int)(short)DAT_TileMapState::instance.PathConnectionLayer[tile2] == param_4
                                            || (iVar15
                                                = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::
                                                                        calculateCanPlayerUnitsNavigateToAreaFromArea,
                                                    this)(param_5, (dword)((int)(param_4)),
                                                    (dword)((int)((
                                                        short)(short)DAT_TileMapState::instance.PathConnectionLayer[tile2])),
                                                    0),
                                                iVar15 != 0))
                                        || ((BVar4 != FALSE
                                            && (BVar6
                                                = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::
                                                                        calculateCanReachUsingCachedAreaLogic,
                                                    this)(DAT_UnitsState::instance.units[sVar2].tile, tile2),
                                                BVar6 != FALSE))))
                                    && (uVar7 = (int)DAT_BuildingsState::instance.buildings[buildingID].terrainHeightUnk
                                            - (uint)DAT_TileMapState::instance.HeightLayer[tile2],
                                        uVar5 = (int)uVar7 >> 0x1f, (int)((uVar7 ^ uVar5) - uVar5) < local_20)) {
                                    local_28 = local_28 + 1;
                                    ((PathHelper12*)(piVar11 + -1))->tile1 = tile2;
                                    *piVar11 = 0;
                                    piVar11 = piVar11 + 3;
                                    if (param_3 <= local_28) {
                                        return;
                                    }
                                }
                                iVar13 = iVar13 + 1;
                                if (iVar12 <= iVar13) {
                                    iVar13 = 0;
                                }
                            }
                            tribeID = tribeID + 1;
                        } while (tribeID < iVar12);
                    }
                    local_20 = local_20 + 0x10;
                    iVar14 = iVar14 + 1;
                } while (iVar14 < 0xe);
            }
            this->searchQueue.destinationsArray[local_28].tile1 = 0;
            ((PathFindingStatePartB*)(this->climbData + 200))->destinationsArray[local_28].tile2OrAHelper = 0;
            return;
        }

    }
}
}
