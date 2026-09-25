#include "OpenSHC/Synchrony.func.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x0042AC60
int Synchrony::GetPlayerPosition(int playerID)
{
    for (int position = 0; position < 8; ++position) {
        if (DAT_GameSynchronyState::instance.playerPositionsArray[position] + 1 == playerID) {
            return position + 1;
        }
    }
    return 0;
}

}
