#include "../GameStateStructures.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"

namespace OpenSHC {
namespace Game {

    using OpenSHC::Map::Buildings::BuildingType;

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004568F0
    int GameStateStructures::countActiveSignposts()
    {
        int signpostCount = 0;
        /*
          the eight signpost slots are checked one by one, exactly as the original binary does
         */
        if ((this->mapAndTime.signpostIDs[0] > 0)
            && (DAT_BuildingsState::instance.buildings[this->mapAndTime.signpostIDs[0]].buildingType
                == OpenSHC::Map::Buildings::BT_SIGNPOST)) {
            signpostCount = 1;
        }
        if ((this->mapAndTime.signpostIDs[1] > 0)
            && (DAT_BuildingsState::instance.buildings[this->mapAndTime.signpostIDs[1]].buildingType
                == OpenSHC::Map::Buildings::BT_SIGNPOST)) {
            signpostCount = signpostCount + 1;
        }
        if ((this->mapAndTime.signpostIDs[2] > 0)
            && (DAT_BuildingsState::instance.buildings[this->mapAndTime.signpostIDs[2]].buildingType
                == OpenSHC::Map::Buildings::BT_SIGNPOST)) {
            signpostCount = signpostCount + 1;
        }
        if ((this->mapAndTime.signpostIDs[3] > 0)
            && (DAT_BuildingsState::instance.buildings[this->mapAndTime.signpostIDs[3]].buildingType
                == OpenSHC::Map::Buildings::BT_SIGNPOST)) {
            signpostCount = signpostCount + 1;
        }
        if ((this->mapAndTime.signpostIDs[4] > 0)
            && (DAT_BuildingsState::instance.buildings[this->mapAndTime.signpostIDs[4]].buildingType
                == OpenSHC::Map::Buildings::BT_SIGNPOST)) {
            signpostCount = signpostCount + 1;
        }
        if ((this->mapAndTime.signpostIDs[5] > 0)
            && (DAT_BuildingsState::instance.buildings[this->mapAndTime.signpostIDs[5]].buildingType
                == OpenSHC::Map::Buildings::BT_SIGNPOST)) {
            signpostCount = signpostCount + 1;
        }
        if ((this->mapAndTime.signpostIDs[6] > 0)
            && (DAT_BuildingsState::instance.buildings[this->mapAndTime.signpostIDs[6]].buildingType
                == OpenSHC::Map::Buildings::BT_SIGNPOST)) {
            signpostCount = signpostCount + 1;
        }
        if ((this->mapAndTime.signpostIDs[7] > 0)
            && (DAT_BuildingsState::instance.buildings[this->mapAndTime.signpostIDs[7]].buildingType
                == OpenSHC::Map::Buildings::BT_SIGNPOST)) {
            signpostCount = signpostCount + 1;
        }
        return signpostCount;
    }
}
}
