
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_BOULDERS;
    using OpenSHC::Map::LogicHelpers::L_BUILDING;
    using OpenSHC::Map::LogicHelpers::L_FORD;
    using OpenSHC::Map::LogicHelpers::L_IRON;
    using OpenSHC::Map::LogicHelpers::L_KEEP_NON_MANOR_HOUSE;
    using OpenSHC::Map::LogicHelpers::L_MARSH;
    using OpenSHC::Map::LogicHelpers::L_MOAT;
    using OpenSHC::Map::LogicHelpers::L_MOAT_DUG_OR_PLANNED;
    using OpenSHC::Map::LogicHelpers::L_PLAIN1_AND_FARM;
    using OpenSHC::Map::LogicHelpers::L_RIVER;
    using OpenSHC::Map::LogicHelpers::L_ROCKY;
    using OpenSHC::Map::LogicHelpers::L_SEA;
    using OpenSHC::Map::LogicHelpers::L_WALL_OR_GATEHOUSE;

    using OpenSHC::Game::GameMode;
    using OpenSHC::Game::GameMode2;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
     */
    /*
      WARNING: Enum "DPERRInt": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x005024F0
    BOOLEnum TileMapState::isValidCastleSiteLocation(int x, uint y, int cbt)
    {
        int baseTile = DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x;
        uint baseY = y;
        /* x is reused as the count of tiles that qualified */
        x = 0;

        int enemyRange;
        int searchRange;
        if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY) {
            enemyRange = 15;
            searchRange = 7;
        } else {
            enemyRange = 30;
            searchRange = 30;
        }

        int tile = baseTile;
        for (int index = 0; index < 9; index++) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getTileForBrush, this)(0, index, &tile, (int*)&y, baseTile, baseY);
            /* the brush call may move both, so the original keeps its own copies for later use */
            int brushTile = tile;
            uint brushY = y;
            if (this->OrganismLayer[tile] != 0) {
                continue;
            }
            if ((this->LogicLayer[tile] & (L_BUILDING | L_KEEP_NON_MANOR_HOUSE)) != 0) {
                continue;
            }
            if (this->BuildingLayer[tile] != 0) {
                continue;
            }
            if ((this->LogicLayer[tile]
                    & (L_WALL_OR_GATEHOUSE | L_BOULDERS | L_IRON | L_RIVER | L_FORD | L_MARSH))
                != 0) {
                continue;
            }
            if ((this->LogicLayer[tile] & (L_SEA | L_PLAIN1_AND_FARM | L_ROCKY)) != 0) {
                continue;
            }

            uint brushX = tile - DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile;
            if (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_EDITOR
                && DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_SIEGE_THAT
                && MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::isEnemyTooCloseUnk, DAT_PathFindingState::ptr)(
                       DAT_GameSynchronyState::instance.currentPlayerSlotID, brushX, y, enemyRange)
                    != FALSE) {
                continue;
            }
            if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY) {
                int buildRange = MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getCastleBuildRangeForMapSize, this)();
                if (MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::isOpponentBuildingInRange, DAT_PathFindingState::ptr)(
                        DAT_GameSynchronyState::instance.currentPlayerSlotID, brushX, brushY, searchRange, -1, -1, buildRange + 5)
                    != 0) {
                    continue;
                }
            }

            /* a moat site must be clear of moat, a moat-fill site must sit on one */
            if (cbt == 0x6a) {
                if ((this->LogicLayer[brushTile] & (L_MOAT | L_MOAT_DUG_OR_PLANNED)) == 0) {
                    x = x + 1;
                }
            } else if (cbt != 0x6b || (this->LogicLayer[brushTile] & L_MOAT_DUG_OR_PLANNED) != 0) {
                x = x + 1;
            }
        }
        return (BOOLEnum)(x != 0);
    }

}
}
