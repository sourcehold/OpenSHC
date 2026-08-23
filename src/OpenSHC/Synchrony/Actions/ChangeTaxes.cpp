#include "OpenSHC/Synchrony/Actions.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x00465800
    void Actions::ChangeTaxes(int playerID, int taxesSetting)
    {
        DAT_GameState::instance.playerDataArray[playerID].taxesSetting = taxesSetting;
    }

}
}
