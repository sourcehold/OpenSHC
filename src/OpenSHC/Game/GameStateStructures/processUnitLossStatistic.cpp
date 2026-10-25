#include "../GameStateStructures.func.hpp"

#include "OpenSHC/Game.func.hpp"
#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/Map/Version.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Game {

    // FUNCTION: STRONGHOLDCRUSADER 0x004563D0
    void GameStateStructures::processUnitLossStatistic(int playerID, int unitID)
    {
        if (playerID < 1 || playerID > 8) {
            return;
        }
        int lossValue;
        switch (DAT_UnitsState::instance.units[unitID].unitType) {
        case Map::Units::UT_S_CATAPULT:
        case Map::Units::UT_S_TREBUCHET:
        case Map::Units::UT_S_MANGONEL:
        case Map::Units::UT_S_TOWER:
        case Map::Units::UT_S_BATTERINGRAM:
        case Map::Units::UT_S_SHIELD:
        case Map::Units::UT_S_BALLISTA:
        case Map::Units::UT_S_FBALLISTA:
            this->playerDataArray[playerID].troopsLost = this->playerDataArray[playerID].troopsLost
                + DAT_UnitsState::instance.units[unitID]
                      .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300;
            lossValue = MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::getValueOfTroopType,
                            DAT_TroopValueState::ptr)(Map::Units::UT_E_ENGINEER)
                * DAT_UnitsState::instance.units[unitID]
                      .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300;
            break;
        default:
            ++this->playerDataArray[playerID].troopsLost;
            lossValue = MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::getValueOfTroopType,
                DAT_TroopValueState::ptr)((Map::Units::UnitType)DAT_UnitsState::instance.units[unitID].unitType);
        }
        this->playerDataArray[playerID].weightedLosses = this->playerDataArray[playerID].weightedLosses + lossValue;
        if (lossValue > 0) {
            if (playerID == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                MACRO_CALL(Map::Version_Func::UpdateUnitLossData)(
                    -lossValue, DAT_UnitsState::instance.units[unitID].lastEncounteredEnemyPlayerID);
            }
            if (DAT_UnitsState::instance.units[unitID].lastEncounteredEnemyPlayerID
                == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                MACRO_CALL(Game_Func::UpdateUnitValueLoss)(lossValue);
            }
        }
        if (DAT_UnitsState::instance.units[unitID].lastEncounteredEnemyPlayerID != 0) {
            this->playerDataArray[playerID].lastlastEncounteredEnemyPlayerID
                = DAT_UnitsState::instance.units[unitID].lastEncounteredEnemyPlayerID;
            if (DAT_UnitsState::instance.units[unitID].lastEncounteredEnemyPlayerID >= 2
                && DAT_UnitsState::instance.units[unitID].lastEncounteredEnemyPlayerID <= 5) {
                this->playerDataArray[playerID]
                    .lostUnitToEnemyPlayerFlags[DAT_UnitsState::instance.units[unitID].lastEncounteredEnemyPlayerID - 2]
                    = 1;
            }
        }
        if (DAT_GameSynchronyState::instance.currentGameMode != GM_SOLITARY) {
            int const enemyPlayerID = DAT_UnitsState::instance.units[unitID].lastEncounteredEnemyPlayerID;
            DAT_GameSynchronyState::instance.finalResults.finalKillMatrix[enemyPlayerID][playerID]
                = DAT_GameSynchronyState::instance.finalResults.finalKillMatrix[enemyPlayerID][playerID] + 1;
            if (DAT_GameState::instance.mapAndTime.playerTeams[enemyPlayerID]
                != DAT_GameState::instance.mapAndTime.playerTeams[playerID]) {
                if (DAT_UnitsState::instance.units[unitID].field323_0x442 != 0) {
                    DAT_GameSynchronyState::instance.finalResults.finalTroopsKilledWeighted[enemyPlayerID]
                        += lossValue / 4;
                } else {
                    DAT_GameSynchronyState::instance.finalResults.finalTroopsKilledWeighted[enemyPlayerID] += lossValue;
                }
            }
            DAT_GameState::instance.playerDataArray[playerID].attackedByPlayerArrayUnk[enemyPlayerID][2]
                = DAT_GameState::instance.playerDataArray[playerID].attackedByPlayerArrayUnk[enemyPlayerID][2] + 1;
        }
        if (DAT_UnitsState::instance.units[unitID].isSelected != 0) {
            DAT_GameCore::instance.countdown = 1;
        }
    }

}
}
