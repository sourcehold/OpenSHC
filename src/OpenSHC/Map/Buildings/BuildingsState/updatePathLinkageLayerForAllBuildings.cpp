#include "../BuildingsState.func.hpp"

#include "OpenSHC/Map/TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x004197C0
        void BuildingsState::updatePathLinkageLayerForAllBuildings()
        {
            for (int buildingID = 1; buildingID < 2000; ++buildingID) {
                if (DAT_BuildingsState::instance.buildings[buildingID].logicalState != 0) {
                    MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updatePathLinkagesForBuilding,
                        DAT_TileMapState::ptr)(buildingID);
                }
            }
        }

    }
}
}
