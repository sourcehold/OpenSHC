#include "../BuildingsState.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"

#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

#include <stdlib.h>

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x004105F0
        undefined4 BuildingsState::canUnitReachAdjacentTile(int param_1, int param_2)
        {
            int const unitArea
                = (short)DAT_TileMapState::instance.PathConnectionLayer[DAT_UnitsState::instance.units[param_2].tile];
            int const height = DAT_TileMapState::instance.HeightLayer[param_1];
            int const row = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[param_1];
            if (MACRO_CALL_MEMBER(Units::UnitsState_Func::selectionContainsOnlyArabAssassins, DAT_UnitsState::ptr)()
                != FALSE) {
                return 0;
            }
            for (int direction = 0; direction < 8; ++direction) {
                int const area
                    = (short)DAT_TileMapState::instance
                          .PathConnectionLayer[DAT_TileMapState::instance.directionTranslationMatrix[row][direction]
                              + param_1];
                // The original compares the height of param_1 with itself, not with the neighbouring tile.
                if (abs(height - DAT_TileMapState::instance.HeightLayer[param_1]) < 16 && area != 0
                    && MACRO_CALL_MEMBER(
                           Navigation::PathFindingState_Func::calculateCanPlayerUnitsNavigateToAreaFromArea,
                           DAT_PathFindingState::ptr)(DAT_UnitsState::instance.units[param_2].owner, unitArea, area,
                           MACRO_CALL_MEMBER(Units::UnitsState_Func::canAUnitClimb, DAT_UnitsState::ptr)())
                        != 0) {
                    return 1;
                }
            }
            return 0;
        }

    }
}
}
