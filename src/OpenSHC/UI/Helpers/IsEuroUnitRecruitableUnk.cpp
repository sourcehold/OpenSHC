#include "../Helpers.func.hpp"

#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TroopDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UnitPropertiesDefinedData.hpp"

namespace OpenSHC {
namespace UI {

    using Map::Units::EuroRecruitableState;

    // FUNCTION: STRONGHOLDCRUSADER 0x00464DA0
    EuroRecruitableState Helpers::IsEuroUnitRecruitableUnk(int unitType)
    {
        int const barracksUnit = unitType - Map::Units::UT_E_ARCHER;
        int goldCost = DAT_TroopDefinedData::instance.BarracksUnitCost[barracksUnit];
        if (DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SOLITARY
            && !DAT_GameSynchronyState::instance.skirmishTroopsCostGold) {
            goldCost = 0;
        }
        // Indexed from unitType again, as the original does: barracksUnit here changes the code.
        if (DAT_GameState::instance.mapAndTime.euroRecruitable[unitType - Map::Units::UT_E_ARCHER] == 0) {
            return Map::Units::ERS_NOT_ALLOWED_TO_RECRUIT;
        }
        int const player = DAT_GameSynchronyState::instance.currentPlayerSlotID;
        if (DAT_GameState::instance.playerDataArray[player].armySize
                + DAT_GameState::instance.playerDataArray[player].count_2
            >= DAT_GameState::instance.mapAndTime.armySizeLimit) {
            return Map::Units::ERS_UNABLE_BECAUSE_MAX_ARMY;
        }
        if (DAT_GameState::instance.playerDataArray[player].currentResources[Game::Resources::RT_GOLD] < goldCost) {
            return Map::Units::ERS_CAN_NOT_RECRUIT;
        }
        // The unit needs one of each of up to four goods; -1 stands for a horse.
        for (int good = 0; good < 4; ++good) {
            int const resource = DAT_UnitPropertiesDefinedData::instance.EuroUnitResourceCosts[barracksUnit][good];
            if (resource == -1) {
                if (DAT_GameState::instance.playerDataArray[player].availableHorses == 0) {
                    return Map::Units::ERS_CAN_NOT_RECRUIT;
                }
            } else if (resource != 0) {
                if (DAT_GameState::instance.playerDataArray[player].currentResources[resource] == 0) {
                    return Map::Units::ERS_CAN_NOT_RECRUIT;
                }
            }
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
