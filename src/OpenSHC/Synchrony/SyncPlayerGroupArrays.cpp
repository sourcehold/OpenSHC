#include "OpenSHC/Synchrony.func.hpp"

#include "OpenSHC/Globals/DAT_00df423c.hpp"
#include "OpenSHC/Globals/DAT_00df4240.hpp"
#include "OpenSHC/Globals/DAT_00df4288.hpp"
#include "OpenSHC/Globals/DAT_00df4298.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x004AEA10
void Synchrony::SyncPlayerGroupArrays()
{
    DAT_00df423c::instance = 0;
    DAT_00df4288::instance = 0;
    memcpy(DAT_GameSynchronyState::instance.playerGroupArray2Unk, DAT_GameSynchronyState::instance.DAT_PlayerGroupArray,
        sizeof(DAT_GameSynchronyState::instance.playerGroupArray2Unk));
    DAT_00df4240::instance = 0;
    DAT_00df4298::instance = 0;
}

}
