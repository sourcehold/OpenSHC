#include "../Helpers.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x0043E5A0
    undefined4 Helpers::SomeFearFactorComputation()
    {
        // Picks a message number from the player's fear factor level.
        int const fearFactor
            = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                  .fearFactorLevel;
        if (fearFactor <= -5) {
            return 14;
        }
        if (fearFactor <= -3) {
            return 15;
        }
        if (fearFactor <= -1) {
            return 16;
        }
        if (fearFactor >= 5) {
            return 19;
        }
        int message = 18;
        if (fearFactor < 3) {
            message = 17;
        }
        return message;
    }

}
}
