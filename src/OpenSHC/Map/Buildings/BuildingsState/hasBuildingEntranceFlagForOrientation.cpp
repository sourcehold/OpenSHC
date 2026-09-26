#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0040B720
        undefined4 BuildingsState::hasBuildingEntranceFlagForOrientation(int buildingID)
        {
            // padding_0x280 holds one entrance flag per map orientation
            if (DAT_TileMapState::instance.mapOrientation == 0) {
                if (DAT_BuildingsState::instance.buildings[buildingID].padding_0x280[1] != 0) {
                    return 1;
                }
            } else if (DAT_TileMapState::instance.mapOrientation == 2) {
                if (DAT_BuildingsState::instance.buildings[buildingID].padding_0x280[2] != 0) {
                    return 1;
                }
            } else if (DAT_TileMapState::instance.mapOrientation == 4) {
                if (DAT_BuildingsState::instance.buildings[buildingID].padding_0x280[3] != 0) {
                    return 1;
                }
            } else if (DAT_TileMapState::instance.mapOrientation == 6) {
                if (DAT_BuildingsState::instance.buildings[buildingID].padding_0x280[0] != 0) {
                    return 1;
                }
            }
            return 0;
        }

    }
}
}
