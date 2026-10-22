#include "../BuildingsState.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0040E610
        undefined4 BuildingsState::findFreeCathedralAssemblyTile(int playerID, int unitID)
        {
            if (DAT_GameState::instance.playerDataArray[playerID].specialBuildingAssemblyPoints[3].x == 0) {
                return 0;
            }
            int const assemblyX = DAT_GameState::instance.playerDataArray[playerID].specialBuildingAssemblyPoints[3].x;
            int const assemblyY = DAT_GameState::instance.playerDataArray[playerID].specialBuildingAssemblyPoints[3].y;
            for (int i = (short)DAT_GameState::instance.playerDataArray[playerID].someCount30; i < 49; ++i) {
                // The original reads the fixed offset [3] on every iteration instead of offset [i].
                int const x = DAT_BuildingDefinedData::instance.SearchRelatedXYOffsets_1[3].x + assemblyX;
                int const y = DAT_BuildingDefinedData::instance.SearchRelatedXYOffsets_1[3].y + assemblyY;
                int const tile = DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x;
                int const occupantID = (short)DAT_TileMapState::instance.UnitLayer[tile];
                if (occupantID != 0 && occupantID != unitID
                    && DAT_UnitsState::instance.units[unitID].movementRelated == 8) {
                    continue;
                }
                if (MACRO_CALL_MEMBER(Navigation::PathFindingState_Func::calculateCanPlayerUnitsNavigateToAreaFromArea,
                        DAT_PathFindingState::ptr)(playerID,
                        (short)
                            DAT_TileMapState::instance.PathConnectionLayer[DAT_UnitsState::instance.units[unitID].tile],
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

    }
}
}
