#include "../../../Map.func.hpp"

#include "OpenSHC/Map/LandscapeState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Map/MapType2.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_LandscapeState.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using Commands::MappersEnum;
        using Game::GameMode;
        using Game::GameMode2;
        using Map::MapType2;
        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x005261B0
        void TribesState::respawnDeer()
        {
            BOOLEnum BVar1;
            uint _x;
            uint _y;
            if (DAT_GameCore::instance.gameMode_2 != Game::GM_EDITOR
                && DAT_GameCore::instance.gameMode_2 != Game::GM_SIEGE_THAT
                && (DAT_GameCore::instance.gameMode_2 != Game::GM_BUILDERUnk
                    || (DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 != Map::MT_SIEGE))
                && DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SOLITARY
                && DAT_GameState::instance.mapAndTime.aliveDeerCount
                && DAT_GameState::instance.mapAndTime.deerCount < 6) {
                /*
                  One `for` over five spawn candidates, where the import had a `while (true)`
                  with an `if (4 < _counter) {}` that never left it and a goto back in from
                  the tile check. The original ends the loop on `cmp ebp, 5; jl`, and spawns
                  at most one deer before returning.
                 */
                for (int _counter = 0; _counter < 5; _counter = _counter + 1) {
                    if (_counter < 4) {
                        _x = (int)DAT_GameState::instance.mapAndTime.deerSpawnLocationsXY[_counter].x;
                        _y = (int)DAT_GameState::instance.mapAndTime.deerSpawnLocationsXY[_counter].y;
                    } else {
                        _x = DAT_GameState::instance.mapAndTime.signpostsMapEdge[0][0].x;
                        _y = DAT_GameState::instance.mapAndTime.signpostsMapEdge[0][0].y;
                    }
                    BVar1 = MACRO_CALL_MEMBER(
                        Rendering::ViewportRenderState_Func::xyAreValid, DAT_ViewportRenderState::ptr)(_x, _y);
                    if (!BVar1) {
                        continue;
                    }
                    int _tile = DAT_ViewportRenderState::instance.translationMatrix[_y].addXgetTile + _x;
                    if ((DAT_TileMapState::instance.LogicLayer[_tile] & 0x50501581U)) {
                        int const _organismID = DAT_TileMapState::instance.OrganismLayer[_tile];
                        if (_organismID == 0) {
                            continue;
                        }
                        MACRO_CALL_MEMBER(Map::LandscapeState_Func::removeTree, DAT_LandscapeState::ptr)(
                            _organismID);
                    }
                    MACRO_CALL_MEMBER(Map::Units::TribesState_Func::createAnimal, this)(
                        Commands::M_MAPPER_DEER, _x, _y, (int)(DAT_TileMapState::instance.HeightLayer[_tile]));
                    return;
                }
            }
        }

    }
}
}
