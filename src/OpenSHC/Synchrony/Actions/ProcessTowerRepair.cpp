#include "OpenSHC/Audio/MissingResourceState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Synchrony/Actions.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MissingResourceState.hpp"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x00466260
    void Actions::ProcessTowerRepair(
        int playerID, int buildingID, int requiredWood, int requiredStone, int gameObjectID)
    {
        if (DAT_BuildingsState::instance.buildings[buildingID].uid != gameObjectID) {
            return;
        }
        MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::updateRepairCostAndReturnIfDamaged,
            DAT_BuildingsState::ptr)(buildingID);
        if (requiredWood
            > DAT_GameState::instance.playerDataArray[playerID].currentResources[Game::Resources::RT_WOOD]) {
            if (playerID == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                MACRO_CALL_MEMBER(Audio::MissingResourceState_Func::playResourceLackSFX, DAT_MissingResourceState::ptr)(
                    1, Audio::SFX::RLSFX_WOOD);
            }
            return;
        }
        if (requiredStone
            > DAT_GameState::instance.playerDataArray[playerID].currentResources[Game::Resources::RT_STONE]) {
            if (playerID == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                MACRO_CALL_MEMBER(Audio::MissingResourceState_Func::playResourceLackSFX, DAT_MissingResourceState::ptr)(
                    1, Audio::SFX::RLSFX_STONE);
            }
            return;
        }
        DAT_BuildingsState::instance.buildings[buildingID].currentHealth
            = DAT_BuildingsState::instance.buildings[buildingID].maxHealth;
        MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::processResourceLoss, DAT_BuildingsState::ptr)(
            playerID, Game::Resources::RT_WOOD, requiredWood, 0);
        MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::processResourceLoss, DAT_BuildingsState::ptr)(
            playerID, Game::Resources::RT_STONE, requiredStone, 0);
    }

}
}
