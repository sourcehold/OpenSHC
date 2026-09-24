#include "OpenSHC/Map/MapPropertiesState.func.hpp"

#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004BBA20
    int MapPropertiesState::sumInvasionEventUnitCount()
    {
        int sum = 0;
        for (int i = 0; i < 25; ++i) {
            sum += DAT_MapPropertiesState::instance.invasionEventContent.unitCountsPerUnitType[i];
        }
        this->DAT_InvasionEventItemUnitCountSum = sum;
        return sum;
    }

}
}
