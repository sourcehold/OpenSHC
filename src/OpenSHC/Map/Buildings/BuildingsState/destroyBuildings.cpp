#include "../BuildingsState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0041A860
        void BuildingsState::destroyBuildings(int playerID)
        {
            for (int buildingID = 1; buildingID < this->maxBuildingsCount; ++buildingID) {
                if (this->buildings[buildingID].logicalState != 0 && this->buildings[buildingID].owner == playerID) {
                    DAT_TileMapState::instance.showNoRubbleWhenDestroyingBuilding
                        = DAT_BuildingDefinedData::instance
                              .BuildingShowRubbleWhenDestroyed[this->buildings[buildingID].buildingType]
                        == 0;
                    MACRO_CALL_MEMBER(BuildingsState_Func::destroyBuilding, DAT_BuildingsState::ptr)(buildingID);
                }
            }
        }

    }
}
}
