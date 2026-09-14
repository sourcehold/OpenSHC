#include "OpenSHC/Synchrony/Actions.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x00465890
    void Actions::ChangeRations(int playerID, int rationsSetting)
    {
        DAT_GameState::instance.playerDataArray[playerID].rationsSetting = rationsSetting;
    }

}
}
