#include "../BuildingsState.func.hpp"

#include "OpenSHC/Map/TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0040F4F0
        void BuildingsState::refreshAllBuildingTileDisplays()
        {
            for (int buildingID = 1; buildingID < this->maxBuildingsCount; ++buildingID) {
                if (this->buildings[buildingID].logicalState != 0) {
                    MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::clearBuildingDisplayFlagsAndEntities,
                        DAT_TileMapState::ptr)(buildingID, 0);
                    MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setMiscDisplayLayer, DAT_TileMapState::ptr)(
                        buildingID);
                }
            }
        }

    }
}
}
