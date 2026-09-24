#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"

#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0040E900
        undefined4 BuildingsState::isEngineerNotAtAssignedWorkTile(int param_1, int param_2, int param_3)
        {
            if (DAT_UnitsState::instance.units[param_2].field252_0x3c4 == 0) {
                if (DAT_UnitsState::instance.units[param_2].resourceToDeposit != 0) {
                    param_3 = 15 - param_3;
                }
            } else {
                param_3 = 0;
            }

            int tile = (&this->buildings[param_1].tileRef1)[param_3];
            this->DAT_TempYOffset = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile];
            this->DAT_TempXOffset
                = tile - DAT_ViewportRenderState::instance.translationMatrix[this->DAT_TempYOffset].addXgetTile;
            if (this->DAT_TempXOffset == DAT_UnitsState::instance.units[param_2].x
                && this->DAT_TempYOffset == DAT_UnitsState::instance.units[param_2].y) {
                return 0;
            }
            return 1;
        }

    }
}
}
