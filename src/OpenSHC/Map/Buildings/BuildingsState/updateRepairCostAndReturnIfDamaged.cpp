#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00410320
        BOOLEnum BuildingsState::updateRepairCostAndReturnIfDamaged(int buildingIndex)
        {
            if (this->buildings[buildingIndex].currentHealth == this->buildings[buildingIndex].maxHealth) {
                return FALSE;
            }

            // The repair costs are the share of the building costs matching the missing health, at least 1
            int stone = DAT_BuildingsState::instance.buildingCosts[this->buildings[buildingIndex].buildingType]
                            .requiredStone_0x4;
            int wood
                = DAT_BuildingsState::instance.buildingCosts[this->buildings[buildingIndex].buildingType].requiredWood;
            if (wood != 0) {
                this->INT_SelectedBuildingStoneWoodCost
                    = (this->buildings[buildingIndex].maxHealth - this->buildings[buildingIndex].currentHealth) * wood
                            / this->buildings[buildingIndex].maxHealth
                        < 1
                    ? 1
                    : (this->buildings[buildingIndex].maxHealth - this->buildings[buildingIndex].currentHealth) * wood
                        / this->buildings[buildingIndex].maxHealth;
            } else {
                this->INT_SelectedBuildingStoneWoodCost = 0;
            }
            if (stone != 0) {
                this->INT_SelectedBuildingStoneRepairCost
                    = (this->buildings[buildingIndex].maxHealth - this->buildings[buildingIndex].currentHealth) * stone
                            / this->buildings[buildingIndex].maxHealth
                        < 1
                    ? 1
                    : (this->buildings[buildingIndex].maxHealth - this->buildings[buildingIndex].currentHealth) * stone
                        / this->buildings[buildingIndex].maxHealth;
            } else {
                this->INT_SelectedBuildingStoneRepairCost = 0;
            }
            return TRUE;
        }

    }
}
}
