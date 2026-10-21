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
        for (int slot = 0; slot < 8; ++slot) {
            if (this->mapAndTime.signpostIDs[slot] > 0
                && DAT_BuildingsState::instance.buildings[this->mapAndTime.signpostIDs[slot]].buildingType
                    == Map::Buildings::BT_SIGNPOST) {
                ++signpostCount;
            }
        }
        return signpostCount;
    }

}
}
