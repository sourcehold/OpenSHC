#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"

#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x00417450
        void BuildingsState::removeTetheredUnitFromBuilding(int buildingID, int unitID)
        {
            for (int i = 0; i < 4; ++i) {
                if ((&this->buildings[buildingID].insideUnitID[0])[i] == unitID
                    && (&this->buildings[buildingID].insideUnitUID[0])[i]
                        == DAT_UnitsState::instance.units[unitID].uid) {
                    --this->buildings[buildingID].numberOfAnimals;
                    (&this->buildings[buildingID].insideUnitID[0])[i] = 0;
                    (&this->buildings[buildingID].insideUnitUID[0])[i] = 0;
                }
            }
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::validateBuildingTetheredUnits, this)(
                buildingID);
        }

    }
}
}
