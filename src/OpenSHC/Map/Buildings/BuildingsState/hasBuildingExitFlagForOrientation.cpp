#include "../BuildingsState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0040B7B0
        BOOLEnum BuildingsState::hasBuildingExitFlagForOrientation(int buildingID)
        {
            if (DAT_TileMapState::instance.mapOrientation == 0) {
                if (DAT_BuildingsState::instance.buildings[buildingID].field162_0x280[2]) {
                    return TRUE;
                }
            } else if (DAT_TileMapState::instance.mapOrientation == 2) {
                if (DAT_BuildingsState::instance.buildings[buildingID].field162_0x280[3]) {
                    return TRUE;
                }
            } else if (DAT_TileMapState::instance.mapOrientation == 4) {
                if (DAT_BuildingsState::instance.buildings[buildingID].field162_0x280[0]) {
                    return TRUE;
                }
            } else if (DAT_TileMapState::instance.mapOrientation == 6) {
                if (DAT_BuildingsState::instance.buildings[buildingID].field162_0x280[1]) {
                    return TRUE;
                }
            }
            return FALSE;
        }

    }
}
}
