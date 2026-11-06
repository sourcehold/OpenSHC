#include "../BuildingsState.func.hpp"

#include "OpenSHC/Game/Resources/ResourceType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0041C240
        void BuildingsState::applyFoodLossPercentageToPlayer(int playerID, int percentage)
        {
            MACRO_CALL_MEMBER(BuildingsState_Func::processResourceLoss, DAT_BuildingsState::ptr)(playerID,
                Game::Resources::RT_BREAD,
                DAT_GameState::instance.playerDataArray[playerID].currentResources[Game::Resources::RT_BREAD]
                    * percentage / 100,
                0);
            MACRO_CALL_MEMBER(BuildingsState_Func::processResourceLoss, DAT_BuildingsState::ptr)(playerID,
                Game::Resources::RT_CHEESE,
                DAT_GameState::instance.playerDataArray[playerID].currentResources[Game::Resources::RT_CHEESE]
                    * percentage / 100,
                0);
            MACRO_CALL_MEMBER(BuildingsState_Func::processResourceLoss, DAT_BuildingsState::ptr)(playerID,
                Game::Resources::RT_MEAT,
                DAT_GameState::instance.playerDataArray[playerID].currentResources[Game::Resources::RT_MEAT]
                    * percentage / 100,
                0);
            MACRO_CALL_MEMBER(BuildingsState_Func::processResourceLoss, DAT_BuildingsState::ptr)(playerID,
                Game::Resources::RT_APPLE,
                DAT_GameState::instance.playerDataArray[playerID].currentResources[Game::Resources::RT_APPLE]
                    * percentage / 100,
                0);
        }

    }
}
}
