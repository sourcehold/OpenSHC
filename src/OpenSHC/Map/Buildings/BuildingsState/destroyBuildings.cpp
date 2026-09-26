#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        using OpenSHC::Map::Buildings::BuildingLogicalState;

        // FUNCTION: STRONGHOLDCRUSADER 0x0041A860
        void BuildingsState::destroyBuildings(int playerID)
        {
            for (int i = 1; i < this->maxBuildingsCount; ++i) {
                if (this->buildings[i].logicalState != 0 && this->buildings[i].owner == playerID) {
                    DAT_TileMapState::instance.showNoRubbleWhenDestroyingBuilding
                        = DAT_BuildingDefinedData::instance
                              .BuildingShowRubbleWhenDestroyed[this->buildings[i].buildingType]
                        == 0;
                    MACRO_CALL_MEMBER(
                        OpenSHC::Map::Buildings::BuildingsState_Func::destroyBuilding, DAT_BuildingsState::ptr)(i);
                }
            }
        }

    }
}
}
