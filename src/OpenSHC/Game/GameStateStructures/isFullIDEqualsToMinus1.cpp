#include "../GameStateStructures.func.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Game {

    /*
      WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
     */
    /*
      WARNING: Enum "DPERRInt": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004563B0
    BOOLEnum GameStateStructures::isFullIDEqualsToMinus1(int param_1)
    {
        return (uint)(DAT_GameSynchronyState::instance.currentPlayerFullIDArray[param_1] == -1);
    }

}
}
