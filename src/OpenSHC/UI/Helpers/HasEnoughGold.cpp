#include "../Helpers.func.hpp"

#include "OpenSHC/Game/Resources/ResourceType.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace UI {

    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x00465040
    BOOLEnum Helpers::HasEnoughGold(int unitType)
    {
        int goldCost = 0;
        if (unitType == Map::Units::UT_E_ENGINEER) {
            goldCost = 30;
        } else if (unitType == Map::Units::UT_E_LADDER) {
            goldCost = 4;
        } else if (unitType == Map::Units::UT_E_MONK) {
            goldCost = 10;
        }
        return DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                   .currentResources[Game::Resources::RT_GOLD]
            >= goldCost;
    }

}
}
