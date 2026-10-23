#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        using OpenSHC::Map::Buildings::BuildingLogicalState;
        using OpenSHC::Map::Buildings::BuildingType;

        // FUNCTION: STRONGHOLDCRUSADER 0x00421990
        void BuildingsState::destroyBuildingAndLinkedDuplicates(uint param_1)
        {
            // Removes the building and all other parts that were placed together with it
            this->buildings[param_1].logicalState = BLS_REMOVE;
            if (DAT_TileMapState::instance.showNoRubbleWhenDestroyingBuilding == 0) {
                this->buildings[param_1].noRubble = 1;
            }
            if (this->buildings[param_1].buildingType == BT_SIGNPOST) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::destroySignpostData, this)(param_1);
            }
            int placedUID = this->buildings[param_1].uidWhenPlaced;
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::deleteBuilding, this)(param_1);
            if (placedUID != 0) {
                for (int i = 1; i < this->maxBuildingsCount; ++i) {
                    if (this->buildings[i].logicalState != 0 && this->buildings[i].uidWhenPlaced == placedUID) {
                        this->buildings[i].logicalState = BLS_REMOVE;
                        if (DAT_TileMapState::instance.showNoRubbleWhenDestroyingBuilding == 0) {
                            this->buildings[i].noRubble = 1;
                        }
                        MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::deleteBuilding, this)(i);
                    }
                }
            }
            DAT_TileMapState::instance.showNoRubbleWhenDestroyingBuilding = 0;
        }

    }
}
}
