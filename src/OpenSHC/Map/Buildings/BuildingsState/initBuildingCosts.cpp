#include "../BuildingsState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x00419780
        void BuildingsState::initBuildingCosts()
        {
            for (int buildingType = 0; buildingType < 110; ++buildingType) {
                this->buildingCosts[buildingType].requiredWood
                    = DAT_BuildingDefinedData::instance.BuildingCost[buildingType][0];
                this->buildingCosts[buildingType].requiredStone_0x4
                    = DAT_BuildingDefinedData::instance.BuildingCost[buildingType][1];
                this->buildingCosts[buildingType].requiredIron_0x8
                    = DAT_BuildingDefinedData::instance.BuildingCost[buildingType][2];
                this->buildingCosts[buildingType].requiredPitch_0xc
                    = DAT_BuildingDefinedData::instance.BuildingCost[buildingType][3];
                this->buildingCosts[buildingType].requiredGold
                    = DAT_BuildingDefinedData::instance.BuildingCost[buildingType][4];
            }
        }

    }
}
}
