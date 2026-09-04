#include "OpenSHC/Synchrony.func.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x0042AC60
int Synchrony::GetPlayerPosition(int playerID)
{
    for (int _position = 0; _position < 8; _position++) {
        if (DAT_GameSynchronyState::instance.playerPositionsArray[_position] + 1 == playerID) {
            return _position + 1;
        }
    }
    return 0;
}

}
