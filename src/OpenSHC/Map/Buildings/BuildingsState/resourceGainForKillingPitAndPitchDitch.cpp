#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        using OpenSHC::Map::Buildings::BuildingType;

        // FUNCTION: STRONGHOLDCRUSADER 0x0040C9B0
        void BuildingsState::resourceGainForKillingPitAndPitchDitch(
            BuildingType buildingType, int* ptrRequiredStone, int* ptrRequiredGold)
        {
            *ptrRequiredStone = this->buildingCosts[buildingType].requiredStone_0x4;
            *ptrRequiredGold = this->buildingCosts[buildingType].requiredGold;
            if (buildingType == BT_KILLINGPIT) {
                *ptrRequiredGold = 5;
            } else if (buildingType == BT_PITCHDITCH) {
                *ptrRequiredGold = 2;
            }
        }

    }
}
}
