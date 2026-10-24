#include "../BuildingsState.func.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0040B980
        BOOLEnum BuildingsState::hasHumanPlayerUnitsOnBuilding(int buildingID)
        {
            int const size = this->buildings[buildingID].widthOrHeight;
            for (int yOffset = 0; yOffset < size; ++yOffset) {
                for (int xOffset = 0; xOffset < size; ++xOffset) {
                    int const unitID = (short)DAT_TileMapState::instance
                                           .UnitLayer[DAT_ViewportRenderState::instance
                                                          .translationMatrix[this->buildings[buildingID].y + yOffset]
                                                          .addXgetTile
                                               + this->buildings[buildingID].x + xOffset];
                    if (unitID != 0
                        && DAT_GameSynchronyState::instance
                                .currentPlayerFullIDArray[DAT_UnitsState::instance.units[unitID].owner]
                            != -1) {
                        return TRUE;
                    }
                }
            }
            return FALSE;
        }

    }
}
}
