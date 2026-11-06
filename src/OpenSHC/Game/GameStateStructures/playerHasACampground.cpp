#include "../GameStateStructures.func.hpp"

#include "OpenSHC/Game/Player/Enums/BuildingEntryInfoEnum.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"

namespace OpenSHC {
namespace Game {

    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x004585B0
    BOOLEnum GameStateStructures::playerHasACampground(int playerID)
    {
        if (this->playerDataArray[playerID].buildingEntryInfos[Player::Enums::BEIE_CAMPGROUND].id > 0
            && DAT_BuildingsState::instance
                    .buildings[this->playerDataArray[playerID].buildingEntryInfos[Player::Enums::BEIE_CAMPGROUND].id]
                    .owner
                == playerID
            && DAT_BuildingsState::instance
                    .buildings[this->playerDataArray[playerID].buildingEntryInfos[Player::Enums::BEIE_CAMPGROUND].id]
                    .buildingType
                == Map::Buildings::BT_CAMPGROUND) {
            return TRUE;
        }
        return FALSE;
    }

}
}
