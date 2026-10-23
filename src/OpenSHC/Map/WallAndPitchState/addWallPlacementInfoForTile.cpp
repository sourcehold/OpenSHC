#include "../WallAndPitchState.func.hpp"

#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Map/LogicHelpers/Logic1.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Game::GameMode2;

    // FUNCTION: STRONGHOLDCRUSADER 0x00500D60
    void WallAndPitchState::addWallPlacementInfoForTile(int tile)
    {
        if (((DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_SKIRMISH_AND_MULTIPLAYER)
                && (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_SIEGE_THAT))
            && (this->index < 100)) {
            this->wallPlacementInfoArray[this->index].tile_OR_pitchID = tile;
            this->wallPlacementInfoArray[this->index].height = DAT_TileMapState::instance.HeightLayer[tile];
            this->wallPlacementInfoArray[this->index].logic = DAT_TileMapState::instance.LogicLayer[tile]
                & (LogicHelpers::L_WALL_OR_GATEHOUSE | LogicHelpers::L_CRENEL | LogicHelpers::L_STAIRS
                    | LogicHelpers::L_UNKNOWN_WALL_RELATED | LogicHelpers::L_BOULDERS | LogicHelpers::L_PEBBLES
                    | LogicHelpers::L_CRENEL_VARIATIONUnk);
            this->wallPlacementInfoArray[this->index].damage = DAT_TileMapState::instance.DamageLayer[tile];
            this->index += 1;
        }
    }

}
}
