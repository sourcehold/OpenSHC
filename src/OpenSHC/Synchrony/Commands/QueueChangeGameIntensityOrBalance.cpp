#include "OpenSHC/Synchrony/Commands.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Synchrony {

    using OpenSHC::Commands::GameCommandType;

    // FUNCTION: STRONGHOLDCRUSADER 0x00429630
    void Commands::QueueChangeGameIntensityOrBalance()
    {
        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
            OpenSHC::Commands::GCT_CHANGE_GAME_INTENSITY_OR_BALANCE);
        DAT_GameSynchronyState::instance.field235_0x1072e8 = -1;
        DAT_GameSynchronyState::instance.field236_0x1072ec = -1;
    }

}
}
