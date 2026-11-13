#include "OpenSHC/Map/MapPropertiesState.func.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004B7FA0
    int MapPropertiesState::sumUnitPoints()
    {
        // the siege unit counts are summed as one array of 20 ints
        int const* const unitCounts = (int const*)&this->SEC_SiegeInformation;
        int sum = 0;
        for (int i = 0; i < 20; ++i) {
            sum += unitCounts[i];
        }
        sum += this->SEC_Section1067.siegeEngineCounts[5] + this->SEC_Section1067.siegeEngineCounts[4]
            + this->SEC_Section1067.siegeEngineCounts[3] + this->SEC_Section1067.siegeEngineCounts[2]
            + this->SEC_Section1067.siegeEngineCounts[1] + this->SEC_Section1067.siegeEngineCounts[0];
        this->DAT_MapEditorUnitPointsSum = sum;
        return sum;
    }

}
}
