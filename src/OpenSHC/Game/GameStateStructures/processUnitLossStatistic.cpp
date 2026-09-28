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

    using OpenSHC::Game::GameMode;
    using OpenSHC::Map::Units::UnitType;

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
    // FUNCTION: STRONGHOLDCRUSADER 0x004563D0
    void GameStateStructures::processUnitLossStatistic(int playerID, int unitID)
    {
        if (playerID - 1U >= 8) {
            return;
        }
        int lossValue;
        switch (DAT_UnitsState::instance.units[unitID].unitType) {
        case OpenSHC::Map::Units::UT_S_CATAPULT:
        case OpenSHC::Map::Units::UT_S_TREBUCHET:
        case OpenSHC::Map::Units::UT_S_MANGONEL:
        case OpenSHC::Map::Units::UT_S_TOWER:
        case OpenSHC::Map::Units::UT_S_BATTERINGRAM:
        case OpenSHC::Map::Units::UT_S_SHIELD:
        case OpenSHC::Map::Units::UT_S_BALLISTA:
        case OpenSHC::Map::Units::UT_S_FBALLISTA:
            this->playerDataArray[playerID].troopsLost = this->playerDataArray[playerID].troopsLost
                + DAT_UnitsState::instance.units[unitID]
                      .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300;
            lossValue = MACRO_CALL_MEMBER(OpenSHC::Map::Units::TroopValueState_Func::getValueOfTroopType,
                            DAT_TroopValueState::ptr)(OpenSHC::Map::Units::UT_E_ENGINEER)
                * DAT_UnitsState::instance.units[unitID]
                      .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300;
            break;
        default:
            this->playerDataArray[playerID].troopsLost = this->playerDataArray[playerID].troopsLost + 1;
            lossValue = MACRO_CALL_MEMBER(
                OpenSHC::Map::Units::TroopValueState_Func::getValueOfTroopType, DAT_TroopValueState::ptr)(
                (OpenSHC::Map::Units::UnitType)DAT_UnitsState::instance.units[unitID].unitType);
        }
        this->playerDataArray[playerID].weightedLosses = this->playerDataArray[playerID].weightedLosses + lossValue;
        if (lossValue > 0) {
            if (playerID == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                MACRO_CALL(OpenSHC::Map::Version_Func::UpdateUnitLossData)(
                    -lossValue, DAT_UnitsState::instance.units[unitID].lastEncounteredEnemyPlayerID);
            }
            if (DAT_UnitsState::instance.units[unitID].lastEncounteredEnemyPlayerID
                == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                MACRO_CALL(OpenSHC::Game_Func::UpdateUnitValueLoss)(lossValue);
            }
        }
        if (DAT_UnitsState::instance.units[unitID].lastEncounteredEnemyPlayerID != 0) {
            this->playerDataArray[playerID].lastlastEncounteredEnemyPlayerID
                = DAT_UnitsState::instance.units[unitID].lastEncounteredEnemyPlayerID;
            if ((DAT_UnitsState::instance.units[unitID].lastEncounteredEnemyPlayerID > 1)
                && (DAT_UnitsState::instance.units[unitID].lastEncounteredEnemyPlayerID < 6)) {
                this->playerDataArray[playerID]
                    .lostUnitToEnemyPlayerFlags[DAT_UnitsState::instance.units[unitID].lastEncounteredEnemyPlayerID - 2]
                    = 1;
            }
        }
        if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY) {
            int enemyPlayerID = DAT_UnitsState::instance.units[unitID].lastEncounteredEnemyPlayerID;
            DAT_GameSynchronyState::instance.finalResults.finalKillMatrix[enemyPlayerID][playerID]
                = DAT_GameSynchronyState::instance.finalResults.finalKillMatrix[enemyPlayerID][playerID] + 1;
            if (this->mapAndTime.playerTeams[enemyPlayerID] != this->mapAndTime.playerTeams[playerID]) {
                if (DAT_UnitsState::instance.units[unitID].field323_0x442 == 0) {
                    DAT_GameSynchronyState::instance.finalResults.finalTroopsKilledWeighted[enemyPlayerID]
                        = DAT_GameSynchronyState::instance.finalResults.finalTroopsKilledWeighted[enemyPlayerID]
                        + lossValue;
                } else {
                    DAT_GameSynchronyState::instance.finalResults.finalTroopsKilledWeighted[enemyPlayerID]
                        = DAT_GameSynchronyState::instance.finalResults.finalTroopsKilledWeighted[enemyPlayerID]
                        + lossValue / 4;
                }
            }
            DAT_GameState::instance.playerDataArray[playerID].unusedEnemyAttackTracker[enemyPlayerID][0]
                = DAT_GameState::instance.playerDataArray[playerID].unusedEnemyAttackTracker[enemyPlayerID][0] + 1;
        }
        if (DAT_UnitsState::instance.units[unitID].isSelected != 0) {
            DAT_GameCore::instance.countdown = 1;
        }
    }
}
}
