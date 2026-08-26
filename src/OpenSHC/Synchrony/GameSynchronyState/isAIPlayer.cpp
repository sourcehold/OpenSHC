#include "../GameSynchronyState.func.hpp"

#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace Synchrony {

    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x004010B0
    BOOLEnum GameSynchronyState::isAIPlayer(int playerID)
    {
        if (this->currentPlayerFullIDArray[playerID] != -1) {
            return FALSE;
        }
        return this->currentAIArray[playerID] != 0;
    }

}
}
