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

        // FUNCTION: STRONGHOLDCRUSADER 0x0040E410
        undefined4 BuildingsState::findFreeTunnelerAssemblyTile(int param_1, int param_2)
        {
            // param_1 is the player, param_2 the unit
            short pointX = DAT_GameState::instance.playerDataArray[param_1].tunnelersGuildAssemblyPointX;
            int start = DAT_GameState::instance.playerDataArray[param_1].someCount29;
            if (pointX != 0) {
                // Search around the assembly point
                short pointY = DAT_GameState::instance.playerDataArray[param_1].tunnelersGuildAssemblyPointY;
                for (int i = start; i < 49; ++i) {
                    int y = DAT_BuildingDefinedData::instance.SearchRelatedXYOffsets_1[i].y + pointY;
                    int x = DAT_BuildingDefinedData::instance.SearchRelatedXYOffsets_1[i].x + pointX;
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
                        this->DAT_TempXOffset = x;
                        this->DAT_TempYOffset = y;
                        if (x == DAT_UnitsState::instance.units[param_2].x
                            && y == DAT_UnitsState::instance.units[param_2].y) {
                            return 0;
                        }
                        return 1;
                    }
                }
                return 0;
            }

            // Otherwise use the parade ground of the tunnelers guild
            for (int i = start; i < 25; ++i) {
                uint x = DAT_GameState::instance.playerDataArray[param_1].tunnelersGuildParadegroundLocations[i].x;
                uint y = DAT_GameState::instance.playerDataArray[param_1].tunnelersGuildParadegroundLocations[i].y;
                if (x <= 399 && y <= 399 && DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y * 400 + x] != 0
                    && ((short)DAT_TileMapState::instance
                                .UnitLayer[DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x]
                            == 0
                        || (short)DAT_TileMapState::instance
                                .UnitLayer[DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x]
                            == param_2
                        || DAT_UnitsState::instance.units[param_2].movementRelated != 8)) {
                    this->DAT_TempXOffset = x;
                    this->DAT_TempYOffset = y;
                    if (x == DAT_UnitsState::instance.units[param_2].x
                        && y == DAT_UnitsState::instance.units[param_2].y) {
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
