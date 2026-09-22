#include "../AICState.func.hpp"

#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Random/RNG.func.hpp"
#include "OpenSHC/Map/Units/UnitInstructionType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace AI {

    using OpenSHC::Map::Units::UnitInstructionType;

    // FUNCTION: STRONGHOLDCRUSADER 0x004D1A00
    void AICState::decideOnTribeAttackLocation(uint tribeID)
    {
        if (MACRO_CALL_MEMBER(AICState_Func::checkTribeActivityPercentages, this)(tribeID, FALSE, TRUE) != FALSE) {
            DAT_TribesState::instance.tribes[tribeID].counter = 0;
            return;
        }

        int targetPlayer = DAT_TribesState::instance.tribes[tribeID].targetPlayer_outpost;
        if (DAT_TribesState::instance.tribes[tribeID].randomNumber == 0) {
            DAT_TribesState::instance.tribes[tribeID].randomNumber = SEC_RNG::instance.currentNumber2;
            MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
        }

        DAT_TribesState::instance.tribes[tribeID].counter++;
        if (DAT_TribesState::instance.tribes[tribeID].counter
            == DAT_TribesState::instance.tribes[tribeID].randomNumber % 6 + 7) {
            DAT_TribesState::instance.tribes[tribeID].counter = 0;
            byte moatWasHit = 0;
            int x = 0;
            int y = 0;
            int unitID
                = MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::getUnitIDForIndexInTribe, DAT_TribesState::ptr)(
                    tribeID, 0);
            if (unitID != 0
                && MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::pathFindingToAttackCastleIncludingMoat,
                    DAT_PathFindingState::ptr)(DAT_TribesState::instance.tribes[tribeID].owner, targetPlayer,
                    DAT_UnitsState::instance.units[unitID].x, DAT_UnitsState::instance.units[unitID].y, &moatWasHit, &x,
                    &y)) {
                if (moatWasHit != 0) {
                    MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::relayTribeInstruction, DAT_UnitsState::ptr)(
                        tribeID, (UnitInstructionType)35, DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x,
                        0, 0);
                    return;
                }
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::relayTribeInstruction, DAT_UnitsState::ptr)(
                    tribeID, OpenSHC::Map::Units::UIT_FILL_MOAT, x, y, 1000);
                return;
            }
        }

        if (DAT_TribesState::instance.tribes[tribeID].tribeSubtype1 != 182
            && DAT_TribesState::instance.tribes[tribeID].tribeSubtype1 != 185) {
            if (MACRO_CALL_MEMBER(AICState_Func::checkTribeActivityPercentages, this)(tribeID, FALSE, FALSE) != FALSE)
                return;

            int targetBuildingID = DAT_TribesState::instance.tribes[tribeID].targetBuildingID;
            if (targetBuildingID != 0
                && DAT_BuildingsState::instance.buildings[targetBuildingID].uid
                    == DAT_TribesState::instance.tribes[tribeID].targetBuildingUID
                && DAT_BuildingsState::instance.buildings[targetBuildingID].fireDuration == 0
                && MACRO_CALL_MEMBER(AICState_Func::checkTribeActivityPercentages, this)(tribeID, FALSE, TRUE) != FALSE) {
                if (DAT_GameState::instance.mapAndTime.yearChanged != 0)
                    DAT_TribesState::instance.tribes[tribeID].targetBuildingID = 0;
                return;
            }

            int buildingID = MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::selectARandomBuildingOwnedByPlayer,
                DAT_GameState::ptr)(targetPlayer);
            if (buildingID != 0) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::relayTribeInstruction, DAT_UnitsState::ptr)(tribeID,
                    OpenSHC::Map::Units::UIT_ATTACK_BUILDING, buildingID, DAT_BuildingsState::instance.buildings[buildingID].uid,
                    0);
                DAT_TribesState::instance.tribes[tribeID].targetBuildingID = buildingID;
                DAT_TribesState::instance.tribes[tribeID].targetBuildingUID
                    = DAT_BuildingsState::instance.buildings[buildingID].uid;
                return;
            }

            int destinationX = DAT_GameState::instance.playerDataArray[targetPlayer].campground.xEntry;
            DAT_TribesState::instance.tribes[tribeID].targetBuildingID = 0;
            int destinationY = DAT_GameState::instance.playerDataArray[targetPlayer].campground.yEntry;
            if (MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::canNavigateUnitsFromTileToTargetTile, this)(
                    tribeID, DAT_ViewportRenderState::instance.translationMatrix[destinationY].addXgetTile + destinationX)
                == FALSE)
                return;

            MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::commandUnitsToLocation, DAT_TribesState::ptr)(
                tribeID, destinationX, destinationY, 1);
            return;
        }

        int buildingID = MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::selectARandomBuildingOwnedByPlayer,
            DAT_GameState::ptr)(targetPlayer);
        int destinationTile;
        if (buildingID == 0) {
            destinationTile = DAT_ViewportRenderState::instance
                                  .translationMatrix[DAT_GameState::instance.playerDataArray[targetPlayer].campground.yEntry]
                                  .addXgetTile
                + DAT_GameState::instance.playerDataArray[targetPlayer].campground.xEntry;
        } else if (DAT_TribesState::instance.tribes[tribeID].selectionTargetUnitID == 0) {
            destinationTile = DAT_BuildingsState::instance.buildings[buildingID].buildingEntryX
                + DAT_ViewportRenderState::instance
                      .translationMatrix[DAT_BuildingsState::instance.buildings[buildingID].buildingEntryY]
                      .addXgetTile;
        } else {
            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::pathfindingForAttacksUnk,
                DAT_PathFindingState::ptr)(tribeID, buildingID, 1,
                (short)DAT_TileMapState::instance.PathConnectionLayer
                    [DAT_UnitsState::instance.units[DAT_TribesState::instance.tribes[tribeID].selectionTargetUnitID].tile],
                targetPlayer);
            destinationTile = DAT_PathFindingState::instance.searchQueue.destinationsArray[0].tile1;
            if (DAT_PathFindingState::instance.searchQueue.destinationsArray[0].tile2OrAHelper == 0)
                destinationTile
                    = DAT_ViewportRenderState::instance
                          .translationMatrix[DAT_GameState::instance.playerDataArray[targetPlayer].campground.yEntry]
                          .addXgetTile
                    + DAT_GameState::instance.playerDataArray[targetPlayer].campground.xEntry;
        }

        if (destinationTile == 0)
            return;

        int destinationY = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[destinationTile];
        int destinationX = destinationTile - DAT_ViewportRenderState::instance.translationMatrix[destinationY].addXgetTile;
        if (MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::canNavigateUnitsFromTileToTargetTile, this)(
                tribeID, destinationTile)
            == FALSE) {
            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::sendUnitsToCampfire, this)(tribeID, targetPlayer);
            return;
        }
        MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::commandUnitsToLocation, DAT_TribesState::ptr)(
            tribeID, destinationX, destinationY, 1);
    }
}
}
