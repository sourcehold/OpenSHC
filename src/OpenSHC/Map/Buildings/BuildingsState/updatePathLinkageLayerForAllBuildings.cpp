#include "../BuildingsState.func.hpp"

#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalStateShort.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        using OpenSHC::Map::Buildings::BuildingLogicalState;
        using OpenSHC::Map::Buildings::BuildingLogicalStateShort;

        // FUNCTION: STRONGHOLDCRUSADER 0x004197C0
        void BuildingsState::updatePathLinkageLayerForAllBuildings()
        {
            for (int _buildingID = 1; _buildingID < 2000; _buildingID += 1) {
                if (this->buildings[_buildingID].logicalState != ((BuildingLogicalState)0)) {
                    MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updatePathLinkagesForBuilding,
                        DAT_TileMapState::ptr)(_buildingID);
                }
            }
        }

    }
}
}
