#include "../BuildingsState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x00410320
        BOOLEnum BuildingsState::updateRepairCostAndReturnIfDamaged(int buildingID)
        {
            if (this->buildings[buildingID].currentHealth == this->buildings[buildingID].maxHealth) {
                return FALSE;
            }
            int const type = this->buildings[buildingID].buildingType;
            int const wood = DAT_BuildingsState::instance.buildingCosts[type].requiredWood;
            int const stone = DAT_BuildingsState::instance.buildingCosts[type].requiredStone_0x4;
            if (wood != 0) {
                if ((this->buildings[buildingID].maxHealth - this->buildings[buildingID].currentHealth) * wood
                        / this->buildings[buildingID].maxHealth
                    < 1) {
                    this->INT_SelectedBuildingStoneWoodCost = 1;
                } else {
                    this->INT_SelectedBuildingStoneWoodCost
                        = (this->buildings[buildingID].maxHealth - this->buildings[buildingID].currentHealth) * wood
                        / this->buildings[buildingID].maxHealth;
                }
            } else {
                this->INT_SelectedBuildingStoneWoodCost = 0;
            }
            if (stone != 0) {
                if ((this->buildings[buildingID].maxHealth - this->buildings[buildingID].currentHealth) * stone
                        / this->buildings[buildingID].maxHealth
                    < 1) {
                    this->INT_SelectedBuildingStoneRepairCost = 1;
                } else {
                    this->INT_SelectedBuildingStoneRepairCost
                        = (this->buildings[buildingID].maxHealth - this->buildings[buildingID].currentHealth) * stone
                        / this->buildings[buildingID].maxHealth;
                }
            } else {
                this->INT_SelectedBuildingStoneRepairCost = 0;
            }
            return TRUE;
        }

    }
}
}
