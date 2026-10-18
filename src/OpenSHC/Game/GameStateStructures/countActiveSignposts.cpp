#include "../GameStateStructures.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"

namespace OpenSHC {
namespace Game {

    using Map::Buildings::BuildingType;

    // FUNCTION: STRONGHOLDCRUSADER 0x004568F0
    int GameStateStructures::countActiveSignposts()
    {
        int signpostCount = 0;
        // the eight signpost slots are checked one by one, exactly as the original binary does
        if (this->mapAndTime.signpostIDs[0] > 0
            && DAT_BuildingsState::instance.buildings[this->mapAndTime.signpostIDs[0]].buildingType
                == Map::Buildings::BT_SIGNPOST) {
            signpostCount = 1;
        }
        if (this->mapAndTime.signpostIDs[1] > 0
            && DAT_BuildingsState::instance.buildings[this->mapAndTime.signpostIDs[1]].buildingType
                == Map::Buildings::BT_SIGNPOST) {
            ++signpostCount;
        }
        if (this->mapAndTime.signpostIDs[2] > 0
            && DAT_BuildingsState::instance.buildings[this->mapAndTime.signpostIDs[2]].buildingType
                == Map::Buildings::BT_SIGNPOST) {
            ++signpostCount;
        }
        if (this->mapAndTime.signpostIDs[3] > 0
            && DAT_BuildingsState::instance.buildings[this->mapAndTime.signpostIDs[3]].buildingType
                == Map::Buildings::BT_SIGNPOST) {
            ++signpostCount;
        }
        if (this->mapAndTime.signpostIDs[4] > 0
            && DAT_BuildingsState::instance.buildings[this->mapAndTime.signpostIDs[4]].buildingType
                == Map::Buildings::BT_SIGNPOST) {
            ++signpostCount;
        }
        if (this->mapAndTime.signpostIDs[5] > 0
            && DAT_BuildingsState::instance.buildings[this->mapAndTime.signpostIDs[5]].buildingType
                == Map::Buildings::BT_SIGNPOST) {
            ++signpostCount;
        }
        if (this->mapAndTime.signpostIDs[6] > 0
            && DAT_BuildingsState::instance.buildings[this->mapAndTime.signpostIDs[6]].buildingType
                == Map::Buildings::BT_SIGNPOST) {
            ++signpostCount;
        }
        if (this->mapAndTime.signpostIDs[7] > 0
            && DAT_BuildingsState::instance.buildings[this->mapAndTime.signpostIDs[7]].buildingType
                == Map::Buildings::BT_SIGNPOST) {
            ++signpostCount;
        }
        return signpostCount;
    }

}
}
