#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

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
            int stone = this->buildingCosts[this->buildings[buildingIndex].buildingType].requiredStone_0x4;
            int wood = this->buildingCosts[this->buildings[buildingIndex].buildingType].requiredWood;
            if (wood == 0) {
                this->INT_SelectedBuildingStoneWoodCost = 0;
            } else if ((this->buildings[buildingIndex].maxHealth - this->buildings[buildingIndex].currentHealth) * wood
                    / this->buildings[buildingIndex].maxHealth
                < 1) {
                this->INT_SelectedBuildingStoneWoodCost = 1;
            } else {
                this->INT_SelectedBuildingStoneWoodCost
                    = (this->buildings[buildingIndex].maxHealth - this->buildings[buildingIndex].currentHealth) * wood
                    / this->buildings[buildingIndex].maxHealth;
            }
            if (stone == 0) {
                this->INT_SelectedBuildingStoneRepairCost = 0;
                return TRUE;
            }
            if ((this->buildings[buildingIndex].maxHealth - this->buildings[buildingIndex].currentHealth) * stone
                    / this->buildings[buildingIndex].maxHealth
                < 1) {
                this->INT_SelectedBuildingStoneRepairCost = 1;
                return TRUE;
            }
            this->INT_SelectedBuildingStoneRepairCost
                = (this->buildings[buildingIndex].maxHealth - this->buildings[buildingIndex].currentHealth) * stone
                / this->buildings[buildingIndex].maxHealth;
            return TRUE;
        }

    }
}
}
