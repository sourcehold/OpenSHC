#include "../AICState.func.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Units/Behavior/UnitStanceEnum.hpp"
#include "OpenSHC/Map/Units/UnitInstructionType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_SkirmishDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004D2A70
    void AICState::aiGiveRaidInstructions(int playerID)
    {
        int aiType = DAT_GameState::instance.playerDataArray[playerID].aiType;
        if (aiType == 0)
            return;
        int aicIndex = aiType - 1;

        DAT_GameState::instance.playerDataArray[playerID].raidRetargetDelayCounter++;
        if (DAT_GameState::instance.playerDataArray[playerID].raidRetargetDelayCounter
            >= this->aics[aicIndex].RaidRetargetDelay)
            DAT_GameState::instance.playerDataArray[playerID].raidRetargetDelayCounter = 0;

        if (DAT_GameState::instance.playerDataArray[playerID].totalRaidingTroopsUnk == 0)
            DAT_GameState::instance.playerDataArray[playerID].someTotalDefenseTroopsRelatedCountdown = 0;
        else if (DAT_GameState::instance.playerDataArray[playerID].someTotalDefenseTroopsRelatedCountdown > 0)
            DAT_GameState::instance.playerDataArray[playerID].someTotalDefenseTroopsRelatedCountdown--;

        for (int i = 0; i < 6; i++) {
            int tribeID = DAT_GameState::instance.playerDataArray[playerID].aiTribeIDs[180 + i];
            DAT_TribesState::instance.tribes[tribeID].unitStance = OpenSHC::Map::Units::Behavior::USE_AGGRESSIVE;
            if (tribeID == 0)
                continue;
            if (DAT_TribesState::instance.tribes[tribeID].uid
                != DAT_GameState::instance.playerDataArray[playerID].aiTribeUIDs[i + 180])
                continue;

            int buildingID = 0;
            if (DAT_GameState::instance.playerDataArray[playerID].requestStateUnk == 2
                && MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::getAliveLordForPlayer, DAT_UnitsState::ptr)(
                       DAT_GameState::instance.playerDataArray[playerID].playerID_askerUnk)
                    != 0) {
                if (DAT_GameState::instance.playerDataArray[playerID].raidRetargetDelayCounter != 0)
                    continue;
                buildingID = MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::selectRandomBuildingIDFromListOfBuildingTypes,
                    this)(DAT_GameState::instance.playerDataArray[playerID].playerID_askerUnk, i);
                if (buildingID == 0)
                    buildingID
                        = MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::selectBuildingFromAListOfBuildingTypes, this)(playerID);
            } else if (DAT_GameState::instance.playerDataArray[playerID].someTotalDefenseTroopsRelatedCountdown == 0
                && DAT_GameState::instance.playerDataArray[playerID].totalRaidingTroopsUnk
                    < MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::getCurrentDesiredAttackRaidUnitCount, this)(
                        aicIndex, playerID)) {
                if (DAT_GameState::instance.playerDataArray[playerID].raidRetargetDelayCounter != 0)
                    continue;
                if (MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::checkTribeActivityPercentages, this)(tribeID, i, TRUE)
                    != FALSE)
                    continue;
                buildingID = MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::selectRandomBuildingIDFromListOfBuildingTypes,
                    this)(playerID, i);
                if (buildingID == 0)
                    buildingID
                        = MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::selectBuildingFromAListOfBuildingTypes, this)(playerID);
            } else if (DAT_SkirmishDefinedData::instance.TribeTypeID[i] == 182
                || DAT_SkirmishDefinedData::instance.TribeTypeID[i] == 181) {
                if (DAT_GameState::instance.playerDataArray[playerID].raidRetargetDelayCounter != 0)
                    continue;
                if (MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::checkTribeActivityPercentages, this)(tribeID, i, FALSE)
                    != FALSE)
                    continue;
                buildingID = MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::selectRandomBuildingIDFromListOfBuildingTypes,
                    this)(DAT_GameState::instance.playerDataArray[playerID].attackedPlayerID_2Unk, i);
                if (buildingID == 0)
                    buildingID = MACRO_CALL_MEMBER(
                        OpenSHC::AI::AICState_Func::chooseRandomBuildingIDFromPlayersArrayOfBuildings, this)(
                        DAT_GameState::instance.playerDataArray[playerID].attackedPlayerID_2Unk);
            } else {
                if (MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::checkTribeActivityPercentages, this)(tribeID, i, FALSE)
                    != FALSE)
                    continue;

                int targetBuildingID = DAT_TribesState::instance.tribes[tribeID].targetBuildingID;
                if (targetBuildingID != 0
                    && DAT_BuildingsState::instance.buildings[targetBuildingID].uid
                        == DAT_TribesState::instance.tribes[tribeID].targetBuildingUID
                    && DAT_BuildingsState::instance.buildings[targetBuildingID].fireDuration == 0
                    && MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::checkTribeActivityPercentages, this)(tribeID, i, TRUE)
                        != FALSE) {
                    if (DAT_GameState::instance.mapAndTime.yearChanged != 0)
                        DAT_TribesState::instance.tribes[tribeID].targetBuildingID = 0;
                    DAT_GameState::instance.playerDataArray[playerID].someTotalDefenseTroopsRelatedCountdown = 100;
                    continue;
                }

                targetBuildingID
                    = MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::chooseRandomBuildingIDFromPlayersArrayOfBuildings, this)(
                        DAT_GameState::instance.playerDataArray[playerID].attackedPlayerID_2Unk);
                if (targetBuildingID == 0) {
                    DAT_TribesState::instance.tribes[tribeID].targetBuildingID = 0;
                    DAT_GameState::instance.playerDataArray[playerID].someTotalDefenseTroopsRelatedCountdown = 0;
                    continue;
                }
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::relayTribeInstruction, DAT_UnitsState::ptr)(tribeID,
                    OpenSHC::Map::Units::UIT_ATTACK_BUILDING, targetBuildingID,
                    DAT_BuildingsState::instance.buildings[targetBuildingID].uid, 0);
                DAT_TribesState::instance.tribes[tribeID].targetBuildingID = targetBuildingID;
                DAT_TribesState::instance.tribes[tribeID].targetBuildingUID
                    = DAT_BuildingsState::instance.buildings[targetBuildingID].uid;
                DAT_GameState::instance.playerDataArray[playerID].someTotalDefenseTroopsRelatedCountdown = 100;
                continue;
            }

            if (buildingID == 0)
                continue;
            int tile = DAT_BuildingsState::instance.buildings[buildingID].buildingEntryX
                + DAT_ViewportRenderState::instance
                      .translationMatrix[DAT_BuildingsState::instance.buildings[buildingID].buildingEntryY]
                      .addXgetTile;
            if (tile == 0)
                continue;

            int y = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile];
            int x = tile - DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile;
            if (MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::canNavigateUnitsFromTileToTargetTile, this)(tribeID, tile)
                == FALSE)
                MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::sendUnitsToCampfire, this)(tribeID, playerID);
            else
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::commandUnitsToLocation, DAT_TribesState::ptr)(
                    tribeID, x, y, 0);
        }
    }
}
}
