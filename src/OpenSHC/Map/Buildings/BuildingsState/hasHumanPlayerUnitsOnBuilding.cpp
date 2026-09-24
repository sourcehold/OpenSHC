#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0040B980
        BOOLEnum BuildingsState::hasHumanPlayerUnitsOnBuilding(int buildingID)
        {
            int size = this->buildings[buildingID].widthOrHeight;
            if (size > 0) {
                int x = (short)this->buildings[buildingID].x;
                int y = (short)this->buildings[buildingID].y;
                for (int row = 0; row < size; ++row) {
                    for (int column = 0; column < size; ++column) {
                        int unitID
                            = (short)DAT_TileMapState::instance
                                  .UnitLayer[DAT_ViewportRenderState::instance.translationMatrix[y + row].addXgetTile
                                      + x + column];
                        if (unitID != 0
                            && DAT_GameSynchronyState::instance
                                    .currentPlayerFullIDArray[DAT_UnitsState::instance.units[unitID].owner]
                                != -1) {
                            return TRUE;
                        }
                    }
                }
            }
            return FALSE;
        }

    }
}
}
