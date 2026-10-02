#include "../../Synchrony.func.hpp"
#include "../Actions.func.hpp"

#include "OpenSHC/Audio/MissingResourceState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Audio/SFX/ResourceLackSFX.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MissingResourceState.hpp"

namespace OpenSHC {
namespace Synchrony {

    using OpenSHC::Audio::SFX::ResourceLackSFX;
    using OpenSHC::Game::Resources::ResourceType;

    /*
      WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
     */
    /*
      WARNING: Enum "DPERRInt": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00466260
    void Actions::ProcessTowerRepair(
        int playerID, int buildingID, int requiredWood, int requiredStone, int gameObjectID)
    {
        if (DAT_BuildingsState::instance.buildings[buildingID].uid == gameObjectID) {
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::updateRepairCostAndReturnIfDamaged,
                DAT_BuildingsState::ptr)(buildingID);
            if (requiredWood > DAT_GameState::instance.playerDataArray[playerID].currentResources[2]) {
                if (playerID == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::MissingResourceState_Func::playResourceLackSFX,
                        DAT_MissingResourceState::ptr)(1, OpenSHC::Audio::SFX::RLSFX_WOOD);
                }
            } else if (requiredStone > DAT_GameState::instance.playerDataArray[playerID].currentResources[4]) {
                if (playerID == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::MissingResourceState_Func::playResourceLackSFX,
                        DAT_MissingResourceState::ptr)(1, OpenSHC::Audio::SFX::RLSFX_STONE);
                }
            } else {
                DAT_BuildingsState::instance.buildings[buildingID].currentHealth
                    = DAT_BuildingsState::instance.buildings[buildingID].maxHealth;
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::processResourceLoss,
                    DAT_BuildingsState::ptr)(playerID, OpenSHC::Game::Resources::RT_WOOD, requiredWood, 0);
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::processResourceLoss,
                    DAT_BuildingsState::ptr)(playerID, OpenSHC::Game::Resources::RT_STONE, requiredStone, 0);
            }
        }
    }

}
}
