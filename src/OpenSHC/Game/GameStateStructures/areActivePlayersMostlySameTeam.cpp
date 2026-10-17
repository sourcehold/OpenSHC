#include "../GameStateStructures.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Game {

    /*
      WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
     */
    /*
      WARNING: Enum "DPERRInt": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004597D0
    BOOLEnum GameStateStructures::areActivePlayersMostlySameTeam()
    {
        int soloCount = 0;
        int soloTeam = -1;
        /*
          four players are handled per pass, exactly as the original binary does
         */
        for (int playerID = 1; playerID < 9; playerID += 4) {
            if (((DAT_GameSynchronyState::instance.currentAIArray[playerID] != 0)
                    || (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[playerID] != -1))
                && (DAT_GameState::instance.playerDataArray[playerID].lordKilledByPlayerID == 0)) {
                if (soloTeam == -1) {
                    soloTeam = this->mapAndTime.playerTeams[playerID];
                    soloCount = soloCount + 1;
                } else if (this->mapAndTime.playerTeams[playerID] != soloTeam) {
                    soloCount = soloCount + 1;
                }
            }
            if (((DAT_GameSynchronyState::instance.currentAIArray[playerID + 1] != 0)
                    || (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[playerID + 1] != -1))
                && (DAT_GameState::instance.playerDataArray[playerID + 1].lordKilledByPlayerID == 0)) {
                if (soloTeam == -1) {
                    soloTeam = this->mapAndTime.playerTeams[playerID + 1];
                    soloCount = soloCount + 1;
                } else if (this->mapAndTime.playerTeams[playerID + 1] != soloTeam) {
                    soloCount = soloCount + 1;
                }
            }
            if (((DAT_GameSynchronyState::instance.currentAIArray[playerID + 2] != 0)
                    || (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[playerID + 2] != -1))
                && (DAT_GameState::instance.playerDataArray[playerID + 2].lordKilledByPlayerID == 0)) {
                if (soloTeam == -1) {
                    soloTeam = this->mapAndTime.playerTeams[playerID + 2];
                    soloCount = soloCount + 1;
                } else if (this->mapAndTime.playerTeams[playerID + 2] != soloTeam) {
                    soloCount = soloCount + 1;
                }
            }
            if (((DAT_GameSynchronyState::instance.currentAIArray[playerID + 3] != 0)
                    || (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[playerID + 3] != -1))
                && (DAT_GameState::instance.playerDataArray[playerID + 3].lordKilledByPlayerID == 0)) {
                if (soloTeam == -1) {
                    soloTeam = this->mapAndTime.playerTeams[playerID + 3];
                    soloCount = soloCount + 1;
                } else if (this->mapAndTime.playerTeams[playerID + 3] != soloTeam) {
                    soloCount = soloCount + 1;
                }
            }
        }
        return soloCount <= 1;
    }
}
}
