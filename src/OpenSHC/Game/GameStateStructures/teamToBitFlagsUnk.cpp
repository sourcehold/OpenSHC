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

        // The original unrolls this four wide. A plain 1..8 loop compiles to 33 instructions against the
        // original's 50 (measured: quick_diff 1.0000 -> 0.2892), while an outer loop stepping by 4 with the
        // inner four left to the compiler reproduces the instruction stream exactly. See the cheat sheet's
        // note on unrolling.
        for (int playerID = 1; playerID < 9; playerID += 4) {
            for (int offset = 0; offset < 4; ++offset) {
                if (DAT_GameState::instance.mapAndTime.playerTeams[playerID + offset] == team) {
                    playerFlags &= ~(1 << (playerID + offset - 1));
                }
            }
        }
        return playerFlags;
    }

}
}
