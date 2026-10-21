#include "../BuildingsState.func.hpp"

#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0040E900
        undefined4 BuildingsState::isEngineerNotAtAssignedWorkTile(int param_1, int param_2, int param_3)
        {
            int tileIndex;
            if (DAT_UnitsState::instance.units[param_2].field252_0x3c4 != 0) {
                tileIndex = 0;
            } else if (DAT_UnitsState::instance.units[param_2].resourceToDeposit != 0) {
                tileIndex = 15 - param_3;
            } else {
                tileIndex = param_3;
            }
            // tileRef1 .. tileRef36 are consecutive fields in the generated header
            int const tile = (&this->buildings[param_1].tileRef1)[tileIndex];
            int const y = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile];
            this->DAT_TempXOffset = tile - DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile;
            this->DAT_TempYOffset = y;
            if (this->DAT_TempXOffset == DAT_UnitsState::instance.units[param_2].x
                && y == DAT_UnitsState::instance.units[param_2].y) {
                return 0;
            }
            return 1;
        }

    }
}
}
