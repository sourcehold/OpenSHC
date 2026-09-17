#include "OpenSHC/Synchrony/Actions.func.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x004285C0
    void Actions::RemovePositionOfPlayer(int playerID)
    {
        for (int _position = 0; _position < 8; _position++) {
            if ((char)DAT_GameSynchronyState::instance.playerPositionsArray[_position] + 1 == playerID) {
                DAT_GameSynchronyState::instance.playerPositionsArray[_position] = 0xf6;
            }
        }
    }

}
}
