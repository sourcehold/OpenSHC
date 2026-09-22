#include "OpenSHC/AI/AICState.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004CFFD0
    BOOLEnum AICState::hasNoTroopsOrAllAreDiggers(int playerID)
    {
        int totalTroops = DAT_GameState::instance.playerDataArray[playerID].totalAssassinTroops
            + DAT_GameState::instance.playerDataArray[playerID].totalUnit2Troops
            + DAT_GameState::instance.playerDataArray[playerID].totalUnitPatrolTroops;
        int halfOfDiggingTroops = 0;

        if (DAT_GameState::instance.playerDataArray[playerID].aiPlayerState == 6) {
            totalTroops += DAT_GameState::instance.playerDataArray[playerID].totalDiggingUnitTroops;
            if (DAT_GameState::instance.playerDataArray[playerID].attackTicker > 16)
                totalTroops += DAT_GameState::instance.playerDataArray[playerID].totalUnitBackupTroops / 8;
            else
                totalTroops += DAT_GameState::instance.playerDataArray[playerID].totalUnitBackupTroops;
            totalTroops += DAT_GameState::instance.playerDataArray[playerID].totalUnitEngageTroops
                + DAT_GameState::instance.playerDataArray[playerID].totalUnitSiegeDefTroops
                + DAT_GameState::instance.playerDataArray[playerID].totalMaxDefaultTroops;
        } else {
            halfOfDiggingTroops = DAT_GameState::instance.playerDataArray[playerID].totalDiggingUnitTroops / 2;
            if (DAT_GameState::instance.playerDataArray[playerID].attackTicker > 12)
                totalTroops += DAT_GameState::instance.playerDataArray[playerID].totalUnitBackupTroops / 8;
            else
                totalTroops += DAT_GameState::instance.playerDataArray[playerID].totalUnitBackupTroops;
            totalTroops += DAT_GameState::instance.playerDataArray[playerID].totalUnitEngageTroops
                + DAT_GameState::instance.playerDataArray[playerID].totalUnitSiegeDefTroops
                + DAT_GameState::instance.playerDataArray[playerID].totalMaxDefaultTroops;
        }

        if (totalTroops <= 1)
            return TRUE;
        if (totalTroops <= 4 && halfOfDiggingTroops > totalTroops * 2)
            return TRUE;
        return FALSE;
    }
}
}
