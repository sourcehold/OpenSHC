#include "../GameStateStructures.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"

namespace OpenSHC {
namespace Game {

    using OpenSHC::Map::Buildings::BuildingType;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004585B0
    BOOLEnum GameStateStructures::playerHasACampground(int playerID)
    {
        if ((this->playerDataArray[playerID].campground.id > 0)
            && (DAT_BuildingsState::instance.buildings[this->playerDataArray[playerID].campground.id].owner == playerID)
            && (DAT_BuildingsState::instance.buildings[this->playerDataArray[playerID].campground.id].buildingType
                == OpenSHC::Map::Buildings::BT_CAMPGROUND)) {
            return TRUE;
        }
        return FALSE;
    }
}
}
