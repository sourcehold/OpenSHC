#include "../GameStateStructures.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Game {

    // FUNCTION: STRONGHOLDCRUSADER 0x00459740
    uint GameStateStructures::teamToBitFlagsUnk(int unitID)
    {
        uint playerFlags = 0xff;
        if (DAT_UnitsState::instance.units[unitID].owner == 0) {
            return playerFlags;
        }
        int const team = DAT_GameState::instance.mapAndTime.playerTeams[DAT_UnitsState::instance.units[unitID].owner];

        for (int playerID = 1; playerID < 9; playerID += 1) {
            if (DAT_GameState::instance.mapAndTime.playerTeams[playerID] == team) {
                playerFlags &=  ~(1 << (playerID - 1));
            }
        }
        return playerFlags;
    }

}
}
