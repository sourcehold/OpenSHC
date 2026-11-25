#include "../GameStateStructures.func.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Game {

    // FUNCTION: STRONGHOLDCRUSADER 0x004563B0
    BOOLEnum GameStateStructures::isFullIDEqualsToMinus1(int playerID)
    {
        return DAT_GameSynchronyState::instance.currentPlayerFullIDArray[playerID] == -1;
    }

}
}
