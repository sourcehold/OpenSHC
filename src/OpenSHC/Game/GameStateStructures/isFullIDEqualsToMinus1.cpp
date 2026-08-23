#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Game {

    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x004563B0
    BOOLEnum GameStateStructures::isFullIDEqualsToMinus1(int param_1)
    {
        return DAT_GameSynchronyState::instance.currentPlayerFullIDArray[param_1] == -1;
    }

}
}
