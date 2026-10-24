#include "../BuildingsState.func.hpp"

#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x004173D0
        void BuildingsState::validateBuildingTetheredUnits(int buildingID)
        {
            this->buildings[buildingID].randomOutpostField = 0;
            for (int slot = 0; slot < 4; ++slot) {
                int const unitID = this->buildings[buildingID].insideUnitID[slot];
                if (unitID != 0) {
                    if (this->buildings[buildingID].insideUnitUID[slot] == DAT_UnitsState::instance.units[unitID].uid) {
                        ++this->buildings[buildingID].randomOutpostField;
                    } else {
                        this->buildings[buildingID].insideUnitID[slot] = 0;
                        this->buildings[buildingID].insideUnitUID[slot] = 0;
                    }
                }
            }
        }

    }
}
}
