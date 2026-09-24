#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
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
        undefined4 BuildingsState::findFreeCathedralAssemblyTile(int param_1, int param_2)
        {
            // param_1 is the player, param_2 the unit
            short pointX = DAT_GameState::instance.playerDataArray[param_1].cathedralAssemblyPointX;
            if (pointX == 0) {
                return 0;
            }
            int i = DAT_GameState::instance.playerDataArray[param_1].someCount30;
            short pointY = DAT_GameState::instance.playerDataArray[param_1].cathedralAssemblyPointY;
            int x;
            int y;
            for (;; ++i) {
                if (i >= 49) {
                    return 0;
                }
                // Note: the original always uses the same search offset instead of the i-th one
                y = DAT_BuildingDefinedData::instance.SearchRelatedXYOffsets_1[3].y + pointY;
                x = DAT_BuildingDefinedData::instance.SearchRelatedXYOffsets_1[3].x + pointX;
                int tile = DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x;
                int unitOnTile = (short)DAT_TileMapState::instance.UnitLayer[tile];
                if ((unitOnTile == 0 || unitOnTile == param_2
                        || DAT_UnitsState::instance.units[param_2].movementRelated != 8)
                    && MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::
                                             calculateCanPlayerUnitsNavigateToAreaFromArea,
                           DAT_PathFindingState::ptr)(param_1,
                           (short)DAT_TileMapState::instance
                               .PathConnectionLayer[DAT_UnitsState::instance.units[param_2].tile],
                           (short)DAT_TileMapState::instance.PathConnectionLayer[tile], 0)
                        != 0) {
                    break;
                }
            }
            this->DAT_TempXOffset = x;
            this->DAT_TempYOffset = y;
            if (x == DAT_UnitsState::instance.units[param_2].x && y == DAT_UnitsState::instance.units[param_2].y) {
                return 0;
            }
            return 1;
        }

    }
}
}
