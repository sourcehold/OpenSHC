#include "../TroopValueState.func.hpp"

#include "OpenSHC/Map.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Units/Behavior/UnitStanceEnum.hpp"
#include "OpenSHC/Map/Units/UnitInstructionType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using Map::Units::UnitInstructionType;
        using Map::Units::Behavior::UnitStanceEnum;
        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0051C570
        BOOLEnum TroopValueState::ifNecessaryThrowOilAutomatically(int unitID)
        {
            int const tribeID = DAT_UnitsState::instance.units[unitID].tribeID;
            int searchRadius = 4;
            if (DAT_UnitsState::instance.units[unitID].terrainOrClimbHeight > 110) {
                searchRadius = 5;
            }
            if (tribeID <= 0) {
                return FALSE;
            }
            if (DAT_UnitsState::instance.units[unitID].closestEnemyMicroDistance > 80) {
                return FALSE;
            }
            int const playerID = DAT_UnitsState::instance.units[unitID].owner;
            if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[playerID] != -1
                && DAT_TribesState::instance.tribes[tribeID].unitStance == Map::Units::Behavior::USE_STAND_GROUND) {
                return FALSE;
            }
            DAT_UnitsState::instance.units[unitID].updateTickTracker
                = DAT_UnitsState::instance.units[unitID].updateTickTracker + 1;
            if (DAT_UnitsState::instance.units[unitID].updateTickTracker < 8) {
                return FALSE;
            }
            DAT_UnitsState::instance.units[unitID].updateTickTracker = 0;
            MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::computeTotalUnitsWithinDistance,
                DAT_PathFindingState::ptr)(playerID, 0, 0, DAT_UnitsState::instance.units[unitID].tile, searchRadius);
            if (DAT_TribesState::instance.tribes[tribeID].unitStance == Map::Units::Behavior::USE_AGGRESSIVE) {
                if (DAT_PathFindingState::instance.ALGO_TotalTroopCount < 1) {
                    return FALSE;
                }
            } else if (DAT_PathFindingState::instance.ALGO_TotalTroopCount <= 3
                && DAT_PathFindingState::instance.ALGO_TotalTroopValue < 20) {
                return FALSE;
            }
            int const targetUnitID = DAT_PathFindingState::instance.field_0x64;
            if (targetUnitID == 0) {
                return FALSE;
            }
            short const buildingID
                = DAT_TileMapState::instance.BuildingLayer[DAT_UnitsState::instance.units[targetUnitID].tile];
            if (buildingID != 0) {
                int buildingSize = 0;
                switch (DAT_BuildingsState::instance.buildings[buildingID].buildingType) {
                case Map::Buildings::BT_CAMPGROUND:
                    buildingSize = 7;
                    break;
                case Map::Buildings::BT_PARADEGROUND:
                case Map::Buildings::BT_PARADEGROUND2:
                case Map::Buildings::BT_PARADEGROUND3:
                case Map::Buildings::BT_PARADEGROUND4:
                case Map::Buildings::BT_PARADEGROUND5:
                    buildingSize = 5;
                    break;
                case Map::Buildings::BT_CAMPFIRE:
                    buildingSize = 4;
                    break;
                default:
                    break;
                }
                if (buildingSize != 0) {
                    int const buildingX = DAT_BuildingsState::instance.buildings[buildingID].x;
                    int const buildingY = DAT_BuildingsState::instance.buildings[buildingID].y;
                    int tileIndex = 0;
                    int friendlyTroopValue = 0;
                    int enemyTroopValue = 0;
                    do {
                        MACRO_CALL_MEMBER(Map::TileMapState_Func::getBuildingSizeIndexMappingData,
                            DAT_TileMapState::ptr)(tileIndex, buildingSize);
                        for (int tileUnitID = DAT_TileMapState::instance
                                 .UnitLayer[DAT_ViewportRenderState::instance
                                                .translationMatrix[DAT_TileMapState::instance.buildingY + buildingY]
                                                .addXgetTile
                                     + DAT_TileMapState::instance.buildingX + buildingX];
                            tileUnitID != 0;
                            tileUnitID = DAT_UnitsState::instance.units[tileUnitID].nextUnitOnTheSameTile) {
                            if (DAT_UnitsState::instance.units[tileUnitID].isSelectable_OR_matchTime == 0) {
                                continue;
                            }
                            if (DAT_GameState::instance.mapAndTime
                                    .playerTeams[DAT_UnitsState::instance.units[unitID].owner]
                                != DAT_GameState::instance.mapAndTime
                                    .playerTeams[DAT_UnitsState::instance.units[tileUnitID].owner]) {
                                enemyTroopValue += MACRO_CALL_MEMBER(
                                    Map::Units::TroopValueState_Func::getValueOfTroopType, DAT_TroopValueState::ptr)(
                                    (Map::Units::UnitType)DAT_UnitsState::instance.units[tileUnitID].unitType);
                            } else {
                                friendlyTroopValue += MACRO_CALL_MEMBER(
                                    Map::Units::TroopValueState_Func::getValueOfTroopType, DAT_TroopValueState::ptr)(
                                    (Map::Units::UnitType)DAT_UnitsState::instance.units[tileUnitID].unitType);
                            }
                        }
                        tileIndex++;
                    } while (tileIndex < DAT_TileMapState::instance.constructionTileCount);
                    if (friendlyTroopValue > enemyTroopValue) {
                        return FALSE;
                    }
                }
            }
            DAT_UnitsState::instance.units[unitID].targetingType = Map::Units::UIT_THROW_OIL;
            DAT_UnitsState::instance.units[unitID].attackAtTileX = DAT_UnitsState::instance.units[targetUnitID].x;
            DAT_UnitsState::instance.units[unitID].attackAtTileY = DAT_UnitsState::instance.units[targetUnitID].y;
            DAT_UnitsState::instance.units[unitID].animationFrame = 4;
            return TRUE;
        }

    }
}
}
