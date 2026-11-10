#include "../Helpers.func.hpp"

#include "OpenSHC/Game/Resources/ResourceType.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x0043E5F0
    int Helpers::SomeGoldRelatedComputation()
    {
        int const gold = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                             .currentResources[Game::Resources::RT_GOLD];
        if (gold == 0) {
            return 29;
        }
        if (gold >= 1000) {
            return 32;
        }
        int const blessed
            = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                  .blessedPeoplePercentage;
        if (blessed >= 80) {
            return 23;
        }
        int const inns = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                             .workingInnsCount;
        if (inns >= 3) {
            return 27;
        }
        if (blessed >= 40) {
            return 22;
        }
        if (inns == 2) {
            return 26;
        }
        if (gold >= 5000) {
            return 31;
        }
        if (blessed >= 20) {
            return 21;
        }
        if (inns == 1) {
            return 25;
        }
        if (gold < 500) {
            return 30;
        }
        if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                .totalEnemyUnitsCount
            > 4) {
            return 36;
        }
        int const population
            = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                  .currentPopulation;
        if (population == 0) {
            return 34;
        }
        if (population >= 5) {
            return 39;
        }
        return 35;
    }

}
}
