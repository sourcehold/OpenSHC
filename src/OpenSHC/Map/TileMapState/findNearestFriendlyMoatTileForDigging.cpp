
#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_MOAT;
    using OpenSHC::Map::LogicHelpers::L_MOAT_DUG_OR_PLANNED;

    using OpenSHC::Map::LogicHelpers::L_MOAT;
    using OpenSHC::Map::LogicHelpers::L_MOAT_DUG_OR_PLANNED;

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
    // FUNCTION: STRONGHOLDCRUSADER 0x005111D0
    BOOLEnum TileMapState::findNearestFriendlyMoatTileForDigging(int playerID, int unitID, int number)
    {
        int unitX = DAT_UnitsState::instance.units[unitID].x;
        int unitY = DAT_UnitsState::instance.units[unitID].y;
        ushort area = this->PathConnectionLayer[DAT_ViewportRenderState::instance.translationMatrix[unitY].addXgetTile
            + unitX];
        int best = 1000;
        BOOLEnum bestMoatID = ~FALSE;
        if (0 < this->currentMoatCount) {
        for (int moatID = 0; moatID < this->currentMoatCount; moatID++) {
            /* digging works on own moat, filling in works on anyone else's */
            if (number == 1
                && DAT_GameState::instance.mapAndTime.playerTeams[this->moats[moatID].owner]
                    != DAT_GameState::instance.mapAndTime.playerTeams[playerID]) {
                continue;
            }
            if (number == 2
                && DAT_GameState::instance.mapAndTime.playerTeams[this->moats[moatID].owner]
                    == DAT_GameState::instance.mapAndTime.playerTeams[playerID]) {
                continue;
            }
            if (this->moats[moatID].stage != number) {
                continue;
            }
            int tile = this->moats[moatID].tile;
            if (this->BuildingLayer[tile] != 0 && this->moats[moatID].zeroOrTwo == 0) {
                continue;
            }
            if ((this->LogicLayer[tile] & (L_MOAT_DUG_OR_PLANNED | L_MOAT)) == 0) {
                continue;
            }
            if (this->moats[moatID].someCountDown >= 'd') {
                continue;
            }
            if (this->UnitLayer[tile] != 0 && DAT_UnitsState::instance.units[this->UnitLayer[tile]].someUnitStat4 == 0) {
                continue;
            }
            if (number == 2
                && MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::findTileInSameAreaAndNoTooHeightDifference, this)(
                       area, tile, this->moats[moatID].y)
                    == FALSE) {
                continue;
            }

            byte pathCost = this->SEC_PathfindingCostTileMap1105[this->moats[moatID].owner][tile];
            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult, DAT_DirectionAlgorithmState::ptr)(
                unitX, unitY, this->moats[moatID].x, this->moats[moatID].y);
            int score = DAT_DirectionAlgorithmState::instance.distanceHigh;
            int fromTarget;
            if (DAT_UnitsState::instance.units[unitID].targetX < 1) {
                fromTarget = 0;
            } else {
                fromTarget = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                    DAT_DirectionAlgorithmState::ptr)(DAT_UnitsState::instance.units[unitID].targetX, DAT_UnitsState::instance.units[unitID].targetY,
                    this->moats[moatID].x, this->moats[moatID].y);
            }
            if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[playerID] == -1) {
                score = score + pathCost * 10;
            }
            score = fromTarget / 2 + this->moats[moatID].someCountDown + score;
            if (score < best) {
                bestMoatID = moatID;
                best = score;
            }
        }

        if (bestMoatID == FALSE) {
            return FALSE;
        }
        }
        /* bug:fixme: with no moats at all the original indexes moats[-1] here */
        this->moats[bestMoatID].someCountDown = this->moats[bestMoatID].someCountDown + 20;
        return bestMoatID;
    }

}
}
