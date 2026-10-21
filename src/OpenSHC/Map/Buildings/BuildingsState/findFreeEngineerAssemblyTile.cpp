#include "../BuildingsState.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0040E120
        int BuildingsState::findFreeEngineerAssemblyTile(int playerID, int unitID)
        {
            int const laddermenCount = (short)DAT_GameState::instance.playerDataArray[playerID].someCount28;
            int index = (int)DAT_GameState::instance.playerDataArray[playerID].someCount27 - laddermenCount;
            int isLadderman = 0;
            if (DAT_UnitsState::instance.units[unitID].unitType == Units::UT_E_LADDER) {
                isLadderman = 1;
                index = laddermenCount;
            }
            if (DAT_GameState::instance.playerDataArray[playerID].specialBuildingAssemblyPoints[isLadderman].x != 0) {
                int const assemblyX
                    = DAT_GameState::instance.playerDataArray[playerID].specialBuildingAssemblyPoints[isLadderman].x;
                int const assemblyY
                    = DAT_GameState::instance.playerDataArray[playerID].specialBuildingAssemblyPoints[isLadderman].y;
                for (int i = index; i < 49; ++i) {
                    int const x = DAT_BuildingDefinedData::instance.SearchRelatedXYOffsets_1[i].x + assemblyX;
                    int const y = DAT_BuildingDefinedData::instance.SearchRelatedXYOffsets_1[i].y + assemblyY;
                    int const tile = DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x;
                    int const occupantID = (short)DAT_TileMapState::instance.UnitLayer[tile];
                    if (occupantID != 0 && occupantID != unitID
                        && DAT_UnitsState::instance.units[unitID].movementRelated == 8) {
                        continue;
                    }
                    if (MACRO_CALL_MEMBER(
                            Navigation::PathFindingState_Func::calculateCanPlayerUnitsNavigateToAreaFromArea,
                            DAT_PathFindingState::ptr)(playerID,
                            (short)DAT_TileMapState::instance
                                .PathConnectionLayer[DAT_UnitsState::instance.units[unitID].tile],
                            (short)DAT_TileMapState::instance.PathConnectionLayer[tile], 0)
                        != 0) {
                        this->DAT_TempXOffset = x;
                        this->DAT_TempYOffset = y;
                        if (x == DAT_UnitsState::instance.units[unitID].x
                            && y == DAT_UnitsState::instance.units[unitID].y) {
                            return 0;
                        }
                        return 1;
                    }
                }
                return 0;
            }
            for (int i = index; i < 25; ++i) {
                int x;
                int y;
                if (isLadderman != 0) {
                    x = DAT_GameState::instance.playerDataArray[playerID].engineersParadegroundLocations[24 - i].x;
                    y = DAT_GameState::instance.playerDataArray[playerID].engineersParadegroundLocations[24 - i].y;
                } else {
                    x = DAT_GameState::instance.playerDataArray[playerID].engineersParadegroundLocations[i].x;
                    y = DAT_GameState::instance.playerDataArray[playerID].engineersParadegroundLocations[i].y;
                }
                if ((uint)x > 399 || (uint)y > 399
                    || DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y * 400 + x] == 0) {
                    continue;
                }
                int const occupantID
                    = (short)DAT_TileMapState::instance
                          .UnitLayer[DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x];
                if (occupantID != 0 && occupantID != unitID
                    && DAT_UnitsState::instance.units[unitID].movementRelated == 8) {
                    continue;
                }
                this->DAT_TempXOffset = x;
                this->DAT_TempYOffset = y;
                if (x == DAT_UnitsState::instance.units[unitID].x && y == DAT_UnitsState::instance.units[unitID].y) {
                    return 0;
                }
                return 1;
            }
            return 0;
        }

    }
}
}
