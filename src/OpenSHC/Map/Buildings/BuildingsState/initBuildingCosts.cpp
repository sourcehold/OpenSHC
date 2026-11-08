#include "../BuildingsState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x00419780
        void BuildingsState::initBuildingCosts()
        {
            // Copies the building costs to the runtime structure
            for (int i = 0; i < countof(this->buildingCosts); ++i) {
                this->buildingCosts[i].requiredWood = DAT_BuildingDefinedData::instance.BuildingCost[i][0];
                this->buildingCosts[i].requiredStone_0x4 = DAT_BuildingDefinedData::instance.BuildingCost[i][1];
                this->buildingCosts[i].requiredIron_0x8 = DAT_BuildingDefinedData::instance.BuildingCost[i][2];
                this->buildingCosts[i].requiredPitch_0xc = DAT_BuildingDefinedData::instance.BuildingCost[i][3];
                this->buildingCosts[i].requiredGold = DAT_BuildingDefinedData::instance.BuildingCost[i][4];
            }
        }

    }
}
}
