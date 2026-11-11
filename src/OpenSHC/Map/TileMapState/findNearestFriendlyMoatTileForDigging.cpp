#include "../TileMapState.func.hpp"

#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_MOAT;
    using OpenSHC::Map::LogicHelpers::L_MOAT_DUG_OR_PLANNED;

    // FUNCTION: STRONGHOLDCRUSADER 0x005111D0
    BOOLEnum TileMapState::findNearestFriendlyMoatTileForDigging(int playerID, int unitID, int number)
    {
        int best = 1000;
        int bestMoatID = -1;
        int const unitX = DAT_UnitsState::instance.units[unitID].x;
        int const unitY = DAT_UnitsState::instance.units[unitID].y;
        int const area
            = (short)this
                  ->PathConnectionLayer[DAT_ViewportRenderState::instance.translationMatrix[unitY].addXgetTile + unitX];
        for (int moatID = 0; moatID < this->currentMoatCount; moatID++) {
            // digging works on own moat, filling in works on anyone else's
            if (number == 1) {
                if (DAT_GameState::instance.mapAndTime.playerTeams[this->moats[moatID].owner]
                    == DAT_GameState::instance.mapAndTime.playerTeams[playerID]) {
                    // the moat belongs to the digger's team
                } else {
                    continue;
                }
            } else if (number == 2) {
                if (DAT_GameState::instance.mapAndTime.playerTeams[this->moats[moatID].owner]
                    == DAT_GameState::instance.mapAndTime.playerTeams[playerID]) {
                    continue;
                }
            }
            if ((char)this->moats[moatID].stage != number) {
                continue;
            }
            if (this->BuildingLayer[this->moats[moatID].tile] != 0 && this->moats[moatID].zeroOrTwo == 0) {
                continue;
            }
            int const tile = this->moats[moatID].tile;
            if ((this->LogicLayer[tile] & (L_MOAT_DUG_OR_PLANNED | L_MOAT)) == 0) {
                continue;
            }
            if (this->moats[moatID].someCountDown >= 100) {
                continue;
            }
            if (this->UnitLayer[tile] != 0
                && DAT_UnitsState::instance.units[this->UnitLayer[tile]].someUnitStat4 == 0) {
                continue;
            }
            if (number == 2
                && !MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::findTileInSameAreaAndNoTooHeightDifference,
                    this)(area, tile, this->moats[moatID].y)) {
                continue;
            }

            int const pathCost
                = DAT_TileMapState::instance.SEC_PathfindingCostTileMap1105[this->moats[moatID].owner][tile];
            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                DAT_DirectionAlgorithmState::ptr)(unitX, unitY, this->moats[moatID].x, this->moats[moatID].y);
            int score = DAT_DirectionAlgorithmState::instance.distanceHigh;
            int fromTarget;
            if (DAT_UnitsState::instance.units[unitID].targetX > 0) {
                fromTarget = MACRO_CALL_MEMBER(
                    OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                    DAT_DirectionAlgorithmState::ptr)(DAT_UnitsState::instance.units[unitID].targetX,
                    DAT_UnitsState::instance.units[unitID].targetY, this->moats[moatID].x, this->moats[moatID].y);
            } else {
                fromTarget = 0;
            }
            if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[playerID] == -1) {
                score += pathCost * 10;
            }
            score += fromTarget / 2 + this->moats[moatID].someCountDown;
            if (score < best) {
                best = score;
                bestMoatID = moatID;
            }
        }

        // bug:fixme: when no moat qualifies (or there are none) the original indexes moats[-1] here
        if (bestMoatID != 0) {
            this->moats[bestMoatID].someCountDown += 20;
        }
        return bestMoatID;
    }
}
}
