#include "../TribesState.func.hpp"

#include "OpenSHC/Map/LandscapeState.func.hpp"
#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Map/LogicHelpers/Logic1.hpp"
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

        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x005261B0
        void TribesState::respawnDeer()
        {
            if (DAT_GameCore::instance.gameMode_2 == Game::GM_EDITOR
                || DAT_GameCore::instance.gameMode_2 == Game::GM_SIEGE_THAT
                || (DAT_GameCore::instance.gameMode_2 == Game::GM_BUILDERUnk
                    && DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 == Map::MT_SIEGE)
                || DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SOLITARY
                || !DAT_GameState::instance.mapAndTime.aliveDeerCount
                || 6 <= DAT_GameState::instance.mapAndTime.deerCount) {
                return;
            }
            for (int spawnCandidate = 0; spawnCandidate < 5; ++spawnCandidate) {
                uint x;
                uint y;
                if (spawnCandidate < 4) {
                    x = DAT_GameState::instance.mapAndTime.deerSpawnLocationsXY[spawnCandidate].x;
                    y = DAT_GameState::instance.mapAndTime.deerSpawnLocationsXY[spawnCandidate].y;
                } else {
                    x = DAT_GameState::instance.mapAndTime.signpostsMapEdge[0][0].x;
                    y = DAT_GameState::instance.mapAndTime.signpostsMapEdge[0][0].y;
                }
                BOOLEnum const xyAreValid = MACRO_CALL_MEMBER(
                    Rendering::ViewportRenderState_Func::xyAreValid, DAT_ViewportRenderState::ptr)(x, y);
                if (!xyAreValid) {
                    continue;
                }
                int const tile = DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x;
                if (DAT_TileMapState::instance.LogicLayer[tile]
                    & (LogicHelpers::L_SEA | LogicHelpers::L_ROCKY | LogicHelpers::L_WALL_OR_GATEHOUSE
                        | LogicHelpers::L_BUILDING | LogicHelpers::L_TREE | LogicHelpers::L_RIVER
                        | LogicHelpers::L_CRENEL_VARIATIONUnk | LogicHelpers::L_KEEP_NON_MANOR_HOUSE
                        | LogicHelpers::L_MOAT)) {
                    int const organismID = DAT_TileMapState::instance.OrganismLayer[tile];
                    if (organismID == 0) {
                        continue;
                    }
                    MACRO_CALL_MEMBER(Map::LandscapeState_Func::removeTree, DAT_LandscapeState::ptr)(organismID);
                }
                MACRO_CALL_MEMBER(Map::Units::TribesState_Func::createAnimal, this)(
                    Commands::M_MAPPER_DEER, x, y, DAT_TileMapState::instance.HeightLayer[tile]);
                return;
            }
        }

    }
}
}
