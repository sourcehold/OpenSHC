#include "../TileMapState.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
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

    // FUNCTION: STRONGHOLDCRUSADER 0x005024F0
    BOOLEnum TileMapState::isValidCastleSiteLocation(int x, uint y, int cbt)
    {
        int tile = DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x;
        int const baseTile = tile;
        uint const baseY = y;
        int validTiles = 0;

        int enemyRange;
        int searchRange;
        if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY) {
            enemyRange = 15;
            searchRange = 7;
        } else {
            enemyRange = 30;
            searchRange = 30;
        }

        for (int index = 0; index < 9; index++) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getTileForBrush, this)(
                0, index, &tile, (int*)&y, baseTile, baseY);
            int const brushTile = tile;
            if (this->OrganismLayer[brushTile] != 0) {
                continue;
            }
            if ((this->LogicLayer[brushTile] & (L_BUILDING | L_KEEP_NON_MANOR_HOUSE)) != 0) {
                continue;
            }
            if (this->BuildingLayer[brushTile] != 0) {
                continue;
            }
            if ((this->LogicLayer[brushTile] & (L_WALL_OR_GATEHOUSE | L_BOULDERS | L_IRON | L_RIVER | L_FORD | L_MARSH))
                != 0) {
                continue;
            }
            if ((this->LogicLayer[brushTile] & (L_SEA | L_PLAIN1_AND_FARM | L_ROCKY)) != 0) {
                continue;
            }

            uint const brushY = y;
            int const tileX = brushTile - DAT_ViewportRenderState::instance.translationMatrix[brushY].addXgetTile;
            if (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_EDITOR
                && DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_SIEGE_THAT
                && MACRO_CALL_MEMBER(
                    OpenSHC::Map::Navigation::PathFindingState_Func::isEnemyTooCloseUnk, DAT_PathFindingState::ptr)(
                    DAT_GameSynchronyState::instance.currentPlayerSlotID, tileX, brushY, enemyRange)) {
                continue;
            }
            if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY) {
                int const buildRange
                    = MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getCastleBuildRangeForMapSize, this)();
                if (MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::isOpponentBuildingInRange,
                        DAT_PathFindingState::ptr)(DAT_GameSynchronyState::instance.currentPlayerSlotID, tileX, brushY,
                        searchRange, -1, -1, buildRange + 5)) {
                    continue;
                }
            }

            // a moat site must be clear of moat, a moat-fill site must sit on one
            if (cbt == 106) {
                if ((this->LogicLayer[brushTile] & (L_MOAT | L_MOAT_DUG_OR_PLANNED)) == 0) {
                    validTiles += 1;
                }
            } else if (cbt != 107 || (this->LogicLayer[brushTile] & L_MOAT_DUG_OR_PLANNED) != 0) {
                validTiles += 1;
            }
        }
        return (BOOLEnum)(validTiles != 0);
    }

}
}
