#include "../BuildingsState.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0040CAC0
        uint BuildingsState::hasEnoughGoldForMoat()
        {
            int gold;
            int stone;
            MACRO_CALL_MEMBER(BuildingsState_Func::getBuildingCost, this)(Commands::M_MAPPER_MOAT, &stone, &gold);
            int const playerID = DAT_GameSynchronyState::instance.currentPlayerSlotID;
            return DAT_GameState::instance.playerDataArray[playerID].startResources[Game::Resources::RT_GOLD]
                >= ((int)DAT_TileMapState::instance.moatTileCount
                       - DAT_GameState::instance.playerDataArray[playerID].moatTileCount + 1)
                * gold;
        }

    }
}
}
