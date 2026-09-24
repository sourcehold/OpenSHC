#include "OpenSHC/Map/MapPropertiesState.func.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004BBA20
    int MapPropertiesState::sumInvasionEventUnitCount()
    {
        this->DAT_InvasionEventItemUnitCountSum = 0;
        for (int i = 0; i < 25; ++i) {
            this->DAT_InvasionEventItemUnitCountSum += this->invasionEventContent.unitCountsPerUnitType[i];
        }
        return this->DAT_InvasionEventItemUnitCountSum;
    }

}
}
