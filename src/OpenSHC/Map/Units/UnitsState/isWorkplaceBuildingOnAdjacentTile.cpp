#include "../UnitsState.func.hpp"

#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00534380
        BOOLEnum UnitsState::isWorkplaceBuildingOnAdjacentTile(int unitID)
        {
            int _workplaceBuildingID = this->units[unitID].workplaceBuildingID_1;
            if (_workplaceBuildingID == 0) {
                return FALSE;
            }
            for (int direction = 0; direction < 8; ++direction) {
                if ((short)DAT_TileMapState::instance.BuildingLayer
                        [DAT_TileMapState::instance.directionTranslationMatrix[this->units[unitID].y][direction]
                            + this->units[unitID].tile]
                    == _workplaceBuildingID) {
                    return TRUE;
                }
            }
            return FALSE;
        }

    }
}
}
