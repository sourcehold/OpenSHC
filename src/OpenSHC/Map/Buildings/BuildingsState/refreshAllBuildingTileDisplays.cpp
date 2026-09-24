#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        using OpenSHC::Map::Buildings::BuildingLogicalState;

        // FUNCTION: STRONGHOLDCRUSADER 0x0040F4F0
        void BuildingsState::refreshAllBuildingTileDisplays()
        {
            for (int i = 1; i < this->maxBuildingsCount; ++i) {
                if (this->buildings[i].logicalState != 0) {
                    MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::clearBuildingDisplayFlagsAndEntities,
                        DAT_TileMapState::ptr)(i, 0);
                    MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setMiscDisplayLayer, DAT_TileMapState::ptr)(i);
                }
            }
        }

    }
}
}
