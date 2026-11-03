#include "../BuildingsState.func.hpp"

#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x00417450
        void BuildingsState::removeTetheredUnitFromBuilding(int buildingID, int unitID)
        {
            for (int slot = 0; slot < 4; ++slot) {
                if (this->buildings[buildingID].insideUnitID[slot] == unitID
                    && this->buildings[buildingID].insideUnitUID[slot] == DAT_UnitsState::instance.units[unitID].uid) {
                    this->buildings[buildingID].numberOfAnimals -= 1;
                    this->buildings[buildingID].insideUnitID[slot] = 0;
                    this->buildings[buildingID].insideUnitUID[slot] = 0;
                }
            }
            MACRO_CALL_MEMBER(BuildingsState_Func::validateBuildingTetheredUnits, this)(buildingID);
        }

    }
}
}
