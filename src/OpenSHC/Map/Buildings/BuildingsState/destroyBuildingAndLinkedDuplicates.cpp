#include "../BuildingsState.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x00421990
        void BuildingsState::destroyBuildingAndLinkedDuplicates(uint param_1)
        {
            this->buildings[param_1].logicalState = BLS_REMOVE;
            if (DAT_TileMapState::instance.showNoRubbleWhenDestroyingBuilding == 0) {
                this->buildings[param_1].noRubble = 1;
            }
            if (this->buildings[param_1].buildingType == BT_SIGNPOST) {
                MACRO_CALL_MEMBER(BuildingsState_Func::destroySignpostData, this)(param_1);
            }
            int const linkedUID = this->buildings[param_1].uidWhenPlaced;
            MACRO_CALL_MEMBER(BuildingsState_Func::deleteBuilding, this)(param_1);
            if (linkedUID == 0) {
                DAT_TileMapState::instance.showNoRubbleWhenDestroyingBuilding = 0;
                return;
            }
            for (int buildingID = 1; buildingID < this->maxBuildingsCount; ++buildingID) {
                if (this->buildings[buildingID].logicalState != 0
                    && this->buildings[buildingID].uidWhenPlaced == linkedUID) {
                    this->buildings[buildingID].logicalState = BLS_REMOVE;
                    if (DAT_TileMapState::instance.showNoRubbleWhenDestroyingBuilding == 0) {
                        this->buildings[buildingID].noRubble = 1;
                    }
                    MACRO_CALL_MEMBER(BuildingsState_Func::deleteBuilding, this)(buildingID);
                }
            }
            DAT_TileMapState::instance.showNoRubbleWhenDestroyingBuilding = 0;
        }

    }
}
}
