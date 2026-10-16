#include "../../../Map.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/Map/Units/Behavior/UnitStanceEnum.hpp"
#include "OpenSHC/Map/Units/UnitInstructionType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using Map::Units::UnitInstructionType;
        using Map::Units::Behavior::UnitStanceEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0051C570
        undefined4 TroopValueState::ifNecessaryThrowOilAutomatically(int param_1)
        {
            short* psVar1;
            short sVar2;
            ushort uVar3;
            ushort uVar4;
            ushort uVar5;
            int iVar6;
            int iVar7;
            int iVar8;
            int iVar9;
            int iVar10;
            int local_c;
            int local_8;
            iVar6 = param_1;
            iVar10 = (int)DAT_UnitsState::instance.units[param_1].tribeID;
            iVar8 = 4;
            if (0x6e < DAT_UnitsState::instance.units[param_1].terrainOrClimbHeight) {
                iVar8 = 5;
            }
            if (((iVar10 < 1) || (0x50 < DAT_UnitsState::instance.units[param_1].closestEnemyMicroDistance))
                || ((iVar9 = (int)DAT_UnitsState::instance.units[param_1].owner,
                    DAT_GameSynchronyState::instance.currentPlayerFullIDArray[iVar9] != -1
                        && (DAT_TribesState::instance.tribes[iVar10].unitStance
                            == Map::Units::Behavior::USE_STAND_GROUND)))) {
                return (undefined4)(0);
            }
            psVar1 = &DAT_UnitsState::instance.units[param_1].updateTickTracker;
            *psVar1 = *psVar1 + 1;
            if (7 < DAT_UnitsState::instance.units[param_1].updateTickTracker) {
                iVar7 = DAT_UnitsState::instance.units[param_1].tile;
                DAT_UnitsState::instance.units[param_1].updateTickTracker = 0;
                MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::computeTotalUnitsWithinDistance,
                    DAT_PathFindingState::ptr)(iVar9, 0, 0, iVar7, iVar8);
                iVar8 = DAT_PathFindingState::instance.field34_0x64;
                if (DAT_TribesState::instance.tribes[iVar10].unitStance
                    == Map::Units::Behavior::USE_AGGRESSIVE) {
                    if (DAT_PathFindingState::instance.ALGO_TotalTroopCount < 1) {
                        return (undefined4)(0);
                    }
                } else if ((DAT_PathFindingState::instance.ALGO_TotalTroopCount < 4)
                    && (DAT_PathFindingState::instance.ALGO_TotalTroopValue < 0x14)) {
                    return (undefined4)(0);
                }
                if (DAT_PathFindingState::instance.field34_0x64) {
                    sVar2 = DAT_TileMapState::instance.BuildingLayer
                                [DAT_UnitsState::instance.units[DAT_PathFindingState::instance.field34_0x64].tile];
                    if (sVar2) {
                        switch (DAT_BuildingsState::instance.buildings[sVar2].buildingType) {
                        case Map::Buildings::BT_CAMPFIRE:
                            param_1 = 4;
                            break;
                        default:
                            goto switchD_0051c693_caseD_34;
                        case Map::Buildings::BT_PARADEGROUND:
                        case Map::Buildings::BT_PARADEGROUND2:
                        case Map::Buildings::BT_PARADEGROUND3:
                        case Map::Buildings::BT_PARADEGROUND4:
                        case Map::Buildings::BT_PARADEGROUND5:
                            param_1 = 5;
                            break;
                        case Map::Buildings::BT_CAMPGROUND:
                            param_1 = 7;
                        }
                        uVar3 = DAT_BuildingsState::instance.buildings[sVar2].x;
                        uVar4 = DAT_BuildingsState::instance.buildings[sVar2].y;
                        iVar10 = 0;
                        local_8 = 0;
                        local_c = 0;
                        do {
                            MACRO_CALL_MEMBER(Map::TileMapState_Func::getBuildingSizeIndexMappingData,
                                DAT_TileMapState::ptr)(iVar10, param_1);
                            uVar5 = DAT_TileMapState::instance.UnitLayer
                                        [DAT_ViewportRenderState::instance
                                                .translationMatrix[DAT_TileMapState::instance.buildingY + (short)uVar4]
                                                .addXgetTile
                                            + DAT_TileMapState::instance.buildingX + (int)(short)uVar3];
                            while (iVar9 = (int)(short)uVar5, iVar9) {
                                if (DAT_UnitsState::instance.units[iVar9].isSelectable_OR_matchTime != 0) {
                                    if (DAT_GameState::instance.mapAndTime
                                            .playerTeams[DAT_UnitsState::instance.units[iVar6].owner]
                                        == DAT_GameState::instance.mapAndTime
                                            .playerTeams[DAT_UnitsState::instance.units[iVar9].owner]) {
                                        iVar7 = MACRO_CALL_MEMBER(
                                            Map::Units::TroopValueState_Func::getValueOfTroopType, this)(
                                            (Map::Units::UnitType)DAT_UnitsState::instance.units[iVar9].unitType);
                                        local_8 = local_8 + iVar7;
                                    } else {
                                        iVar7 = MACRO_CALL_MEMBER(
                                            Map::Units::TroopValueState_Func::getValueOfTroopType, this)(
                                            (Map::Units::UnitType)DAT_UnitsState::instance.units[iVar9].unitType);
                                        local_c = local_c + iVar7;
                                    }
                                }
                                uVar5 = DAT_UnitsState::instance.units[iVar9].nextUnitOnTheSameTile;
                            }
                            iVar10 = iVar10 + 1;
                        } while (iVar10 < DAT_TileMapState::instance.constructionTileCount);
                        if (local_c < local_8) {
                            return (undefined4)(0);
                        }
                    }
                switchD_0051c693_caseD_34:
                    DAT_UnitsState::instance.units[iVar6].targetingType = Map::Units::UIT_THROW_OIL;
                    DAT_UnitsState::instance.units[iVar6].attackAtTileX = DAT_UnitsState::instance.units[iVar8].x;
                    DAT_UnitsState::instance.units[iVar6].attackAtTileY = DAT_UnitsState::instance.units[iVar8].y;
                    DAT_UnitsState::instance.units[iVar6].animationFrame = 4;
                    return (undefined4)(1);
                }
            }
            return (undefined4)(0);
        }

    }
}
}
