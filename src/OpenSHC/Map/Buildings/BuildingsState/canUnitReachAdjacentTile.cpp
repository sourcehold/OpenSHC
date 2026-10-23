#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x004105F0
        undefined4 BuildingsState::canUnitReachAdjacentTile(int param_1, int param_2)
        {
            // param_1 is the tile, param_2 the unit
            int height = DAT_TileMapState::instance.HeightLayer[param_1];
            int tileY = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[param_1];
            int unitArea
                = (short)DAT_TileMapState::instance.PathConnectionLayer[DAT_UnitsState::instance.units[param_2].tile];
            if (MACRO_CALL_MEMBER(
                    OpenSHC::Map::Units::UnitsState_Func::selectionContainsOnlyArabAssassins, DAT_UnitsState::ptr)()
                != FALSE) {
                return 0;
            }
            for (int direction = 0; direction < 8; ++direction) {
                int area
                    = (short)DAT_TileMapState::instance
                          .PathConnectionLayer[DAT_TileMapState::instance.directionTranslationMatrix[tileY][direction]
                              + param_1];
                // Note: the original compares the height of the tile with itself instead of the neighbour
                if (abs(height - DAT_TileMapState::instance.HeightLayer[param_1]) < 16 && area != 0
                    && MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::
                                             calculateCanPlayerUnitsNavigateToAreaFromArea,
                           DAT_PathFindingState::ptr)(DAT_UnitsState::instance.units[param_2].owner, unitArea, area,
                           MACRO_CALL_MEMBER(
                               OpenSHC::Map::Units::UnitsState_Func::canAUnitClimb, DAT_UnitsState::ptr)())
                        != 0) {
                    return 1;
                }
            }
            return 0;
        }

    }
}
}
