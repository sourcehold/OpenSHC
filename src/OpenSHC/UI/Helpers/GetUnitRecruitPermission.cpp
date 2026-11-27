#include "../Helpers.func.hpp"

#include "OpenSHC/Game/Resources/ResourceType.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TroopDefinedData.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::Map::Units::EuroRecruitableState;
    using OpenSHC::Map::Units::UnitType;

    // FUNCTION: STRONGHOLDCRUSADER 0x00464E80
    EuroRecruitableState Helpers::GetUnitRecruitPermission(UnitType unitType)
    {
        if (!DAT_GameState::instance.mapAndTime.mercRecruitable[unitType - Map::Units::UT_A_ARCHER]) {
            return Map::Units::ERS_NOT_ALLOWED_TO_RECRUIT;
        }
        int const player = DAT_GameSynchronyState::instance.currentPlayerSlotID;
        if (DAT_GameState::instance.playerDataArray[player].armySize
                + DAT_GameState::instance.playerDataArray[player].count_2
            >= DAT_GameState::instance.mapAndTime.armySizeLimit) {
            return Map::Units::ERS_UNABLE_BECAUSE_MAX_ARMY;
        }
        if (DAT_GameState::instance.playerDataArray[player].currentResources[Game::Resources::RT_GOLD]
            < DAT_TroopDefinedData::instance.NonEuroUnitCost[unitType - Map::Units::UT_A_ARCHER]) {
            return Map::Units::ERS_CAN_NOT_RECRUIT;
        }
        if (DAT_GameState::instance.playerDataArray[player].availablePeasantsOrHousedPeasants
                - DAT_GameState::instance.playerDataArray[player].count
            <= 0) {
            return Map::Units::ERS_UNABLE_MISSING_PEASANTS;
        }
        return Map::Units::ERS_CAN_RECRUITUnk;
    }

}
}
