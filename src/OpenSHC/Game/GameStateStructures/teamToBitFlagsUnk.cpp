#include "../GameStateStructures.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Game {

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00459740
    uint GameStateStructures::teamToBitFlagsUnk(int unitID)
    {
        uint playerFlags = 0xff;
        if (DAT_UnitsState::instance.units[unitID].owner == 0) {
            return playerFlags;
        }
        int team = DAT_GameState::instance.mapAndTime.playerTeams[DAT_UnitsState::instance.units[unitID].owner];
        /*
          four players are handled per pass, exactly as the original binary does
         */
        for (int playerID = 1; playerID < 9; playerID += 4) {
            if (DAT_GameState::instance.mapAndTime.playerTeams[playerID] == team) {
                playerFlags = playerFlags & ~(1 << (playerID - 1));
            }
            if (DAT_GameState::instance.mapAndTime.playerTeams[playerID + 1] == team) {
                playerFlags = playerFlags & ~(1 << playerID);
            }
            if (DAT_GameState::instance.mapAndTime.playerTeams[playerID + 2] == team) {
                playerFlags = playerFlags & ~(1 << (playerID + 1));
            }
            if (DAT_GameState::instance.mapAndTime.playerTeams[playerID + 3] == team) {
                playerFlags = playerFlags & ~(1 << (playerID + 2));
            }
        }
        return playerFlags;
    }
}
}
