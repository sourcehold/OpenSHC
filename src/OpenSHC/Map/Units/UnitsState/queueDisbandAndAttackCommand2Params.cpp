#include "../UnitsState.func.hpp"

#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00537100
        void UnitsState::queueDisbandAndAttackCommand2Params(undefined4 commandParam0, undefined4 commandParam1)
        {
            DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = commandParam0;
            DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = commandParam1;
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                OpenSHC::Commands::GCT_DISBAND_AND_ATTACK_UNITS);
        }

    }
}
}
