#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        using OpenSHC::Game::Resources::ResourceType;

        // FUNCTION: STRONGHOLDCRUSADER 0x0041C240
        void BuildingsState::applyFoodLossPercentageToPlayer(int param_1, int param_2)
        {
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::processResourceLoss,
                DAT_BuildingsState::ptr)(param_1, OpenSHC::Game::Resources::RT_BREAD,
                DAT_GameState::instance.playerDataArray[param_1].currentResources[OpenSHC::Game::Resources::RT_BREAD]
                    * param_2 / 100,
                0);
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::processResourceLoss,
                DAT_BuildingsState::ptr)(param_1, OpenSHC::Game::Resources::RT_CHEESE,
                DAT_GameState::instance.playerDataArray[param_1].currentResources[OpenSHC::Game::Resources::RT_CHEESE]
                    * param_2 / 100,
                0);
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::processResourceLoss,
                DAT_BuildingsState::ptr)(param_1, OpenSHC::Game::Resources::RT_MEAT,
                DAT_GameState::instance.playerDataArray[param_1].currentResources[OpenSHC::Game::Resources::RT_MEAT]
                    * param_2 / 100,
                0);
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::processResourceLoss,
                DAT_BuildingsState::ptr)(param_1, OpenSHC::Game::Resources::RT_APPLE,
                DAT_GameState::instance.playerDataArray[param_1].currentResources[OpenSHC::Game::Resources::RT_APPLE]
                    * param_2 / 100,
                0);
        }

    }
}
}
