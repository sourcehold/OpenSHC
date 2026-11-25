#include "../Helpers.func.hpp"

#include "OpenSHC/Map/LogicHelpers/Logic1.hpp"
#include "OpenSHC/Map/MapConstants.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_MinimapViewState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace UI {

    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x004347F0
    BOOLEnum Helpers::SomeUnitAndViewportCheck(int unitID)
    {
        // Over a wall, crenel or keep tile, a unit behind that tile does not count.
        if (!DAT_MinimapViewState::instance.minimapClickEnabled
            && DAT_ViewportRenderState::instance.viewportState.mouseAtomRefFloorTile != 0
            && (DAT_TileMapState::instance
                    .LogicLayer[DAT_ViewportRenderState::instance.viewportState.mouseAtomRefFloorTile]
                & (Map::LogicHelpers::L_WALL_OR_GATEHOUSE | Map::LogicHelpers::L_CRENEL
                    | Map::LogicHelpers::L_KEEP_NON_MANOR_HOUSE))) {
            int tileY
                = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[DAT_ViewportRenderState::instance
                        .viewportState.mouseAtomRefFloorTile];
            int tileX = DAT_ViewportRenderState::instance.viewportState.mouseAtomRefFloorTile
                - DAT_ViewportRenderState::instance.translationMatrix[tileY].addXgetTile;
            int unitX = DAT_UnitsState::instance.units[unitID].x;
            int unitY = DAT_UnitsState::instance.units[unitID].y;
            // Turn both positions with the map, so that x + y grows towards the viewer.
            switch (DAT_TileMapState::instance.mapOrientation) {
            case 2: {
                int const oldTileX = tileX;
                tileX = tileY;
                int const oldUnitX = unitX;
                unitX = unitY;
                tileY = Map::MC_MAP_XY_LIMIT - oldTileX;
                unitY = Map::MC_MAP_XY_LIMIT - oldUnitX;
                break;
            }
            case 4:
                tileX = Map::MC_MAP_XY_LIMIT - tileX;
                tileY = Map::MC_MAP_XY_LIMIT - tileY;
                unitX = Map::MC_MAP_XY_LIMIT - unitX;
                unitY = Map::MC_MAP_XY_LIMIT - unitY;
                break;
            case 6: {
                int const oldTileY = tileY;
                tileY = tileX;
                int const oldUnitY = unitY;
                unitY = unitX;
                tileX = Map::MC_MAP_XY_LIMIT - oldTileY;
                unitX = Map::MC_MAP_XY_LIMIT - oldUnitY;
                break;
            }
            }
            if (tileX + tileY > unitX + unitY) {
                return FALSE;
            }
        }
        return TRUE;
    }

}
}
