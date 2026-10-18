#include "../GameStateStructures.func.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Game {

    // FUNCTION: STRONGHOLDCRUSADER 0x004563B0
    BOOLEnum GameStateStructures::isFullIDEqualsToMinus1(int param_1)
    {
        return (uint)(DAT_GameSynchronyState::instance.currentPlayerFullIDArray[param_1] == -1);
    }

}
}
