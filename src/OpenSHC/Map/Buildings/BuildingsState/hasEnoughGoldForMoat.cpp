#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        using OpenSHC::Commands::MappersEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0040CAC0
        uint BuildingsState::hasEnoughGoldForMoat()
        {
            int stone;
            int gold;
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingCost, this)(
                OpenSHC::Commands::M_MAPPER_MOAT, &stone, &gold);
            return ((int)DAT_TileMapState::instance.moatTileCount
                       - DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                           .moatTileCount
                       + 1)
                * gold
                <= DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                       .startResources[OpenSHC::Game::Resources::RT_GOLD];
        }

    }
}
}
