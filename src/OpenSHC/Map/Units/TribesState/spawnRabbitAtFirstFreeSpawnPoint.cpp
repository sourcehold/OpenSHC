#include "../TribesState.func.hpp"

#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Map/LogicHelpers/Logic1.hpp"
#include "OpenSHC/Map/MapConstants.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x005262A0
        void TribesState::spawnRabbitAtFirstFreeSpawnPoint()
        {
            if (DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SOLITARY
                || 160 <= DAT_GameState::instance.mapAndTime.wildlifeCount) {
                return;
            }
            for (int _slot = 0; _slot < (int)_countof(DAT_GameState::instance.mapAndTime.rabbitSpawnXY)
                    + (int)_countof(DAT_GameState::instance.mapAndTime.signpostsMapEdge);
                ++_slot) {
                uint x;
                uint y;
                if (_slot < (int)_countof(DAT_GameState::instance.mapAndTime.rabbitSpawnXY)) {
                    x = DAT_GameState::instance.mapAndTime.rabbitSpawnXY[_slot][0];
                    y = DAT_GameState::instance.mapAndTime.rabbitSpawnXY[_slot][1];
                } else {
                    if (DAT_GameState::instance.mapAndTime.signpostIDs[_slot - 4] == 0) {
                        continue;
                    }
                    x = DAT_GameState::instance.mapAndTime.signpostsMapEdge[_slot - 4][0].x;
                    y = DAT_GameState::instance.mapAndTime.signpostsMapEdge[_slot - 4][0].y;
                }
                if (x <= OpenSHC::Map::MC_MAP_XY_LIMIT_MIN_1 && y <= OpenSHC::Map::MC_MAP_XY_LIMIT_MIN_1
                    && DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y * OpenSHC::Map::MC_MAP_XY_LIMIT + x]
                        != 0) {
                    int const _tile = DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x;
                    if ((DAT_TileMapState::instance.LogicLayer[_tile]
                            & (LogicHelpers::L_SEA | LogicHelpers::L_ROCKY | LogicHelpers::L_WALL_OR_GATEHOUSE
                                | LogicHelpers::L_BUILDING | LogicHelpers::L_TREE | LogicHelpers::L_RIVER
                                | LogicHelpers::L_CRENEL_VARIATIONUnk | LogicHelpers::L_KEEP_NON_MANOR_HOUSE
                                | LogicHelpers::L_MOAT))
                        == 0) {
                        MACRO_CALL_MEMBER(Map::Units::TribesState_Func::createAnimal, this)(
                            Commands::M_MAPPER_RABBIT, x, y, DAT_TileMapState::instance.HeightLayer[_tile]);
                        this->unknownX_01 = x;
                        this->unknownY_01 = y;
                        return;
                    }
                }
            }
        }

    }
}
}
