#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        using OpenSHC::Map::Buildings::BuildingLogicalState;

        // FUNCTION: STRONGHOLDCRUSADER 0x004197C0
        void BuildingsState::updatePathLinkageLayerForAllBuildings()
        {
            for (int i = 1; i < 2000; ++i) {
                if (DAT_BuildingsState::instance.buildings[i].logicalState != 0) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::Map::TileMapState_Func::updatePathLinkagesForBuilding, DAT_TileMapState::ptr)(i);
                }
            }
        }

    }
}
}
