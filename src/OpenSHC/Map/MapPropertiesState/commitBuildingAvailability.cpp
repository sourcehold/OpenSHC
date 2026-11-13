#include "OpenSHC/Map/MapPropertiesState.func.hpp"

#include "OpenSHC/Globals/DAT_MissionAestheticsDefinedData.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004BAEC0
    void MapPropertiesState::commitBuildingAvailability()
    {
        for (int i = 0; i < 380; ++i) {
            this->buildingAvailabilityRelatedFlags[i] = 1;
        }
        for (int i = 0; i < 10; ++i) {
            this->buildingAvailabilityArray2[i] = 1;
        }
        for (int i = 10; i < 49; ++i) {
            this->buildingAvailabilityArray2[i] = 0;
        }
        int row = 0;
        for (;
            DAT_MissionAestheticsDefinedData::instance.BuildingNameRelatedStructArray[row].nameNumberInTextGroup != -1;
            ++row) {
            int const available = this->buildingAvailability[row] != 0;
            // the three sub entries are read as one list of nine IDs after the name number
            for (int i = 1; i < 10; ++i) {
                int const id
                    = ((int const*)&DAT_MissionAestheticsDefinedData::instance.BuildingNameRelatedStructArray[row])[i];
                if (id > 0) {
                    this->buildingAvailabilityRelatedFlags[id] = available;
                } else if (id < 0) {
                    if (available) {
                        this->buildingAvailabilityArray2[-id] = available;
                    }
                } else {
                    break;
                }
            }
        }
        this->buildingAvailabilityRowCount = row - 2;
        this->buildingAvailabilityArray2[10] = 1;
        this->buildingAvailabilityArray2[20] = 1;
        this->buildingAvailabilityArray2[30] = 1;
        this->buildingAvailabilityArray2[40] = 1;
        this->buildingAvailabilityArray2[25] = 1;
        this->buildingAvailabilityArray2[28] = 1;
    }

}
}
