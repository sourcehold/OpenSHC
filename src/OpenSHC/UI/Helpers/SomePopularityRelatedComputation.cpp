#include "../Helpers.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x0043E540
    int Helpers::SomePopularityRelatedComputation()
    {
        // Picks a message number from the player's popularity.
        int const popularity
            = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID].popularity
            / 100;
        if (popularity >= 100) {
            return 12;
        }
        if (popularity <= 0) {
            return 2;
        }
        if (popularity < 50) {
            return popularity / 10 + 3;
        }
        return popularity / 10 + 2;
    }

}
}
