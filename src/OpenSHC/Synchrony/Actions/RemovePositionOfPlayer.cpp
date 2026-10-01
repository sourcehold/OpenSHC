#include "OpenSHC/Synchrony/Actions.func.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x004285C0
    void Actions::RemovePositionOfPlayer(int playerID)
    {
        for (int position = 0; position < 8; ++position) {
            if ((char)DAT_GameSynchronyState::instance.playerPositionsArray[position] + 1 == playerID) {
                DAT_GameSynchronyState::instance.playerPositionsArray[position] = 0xf6;
            }
        }
    }

}
}
