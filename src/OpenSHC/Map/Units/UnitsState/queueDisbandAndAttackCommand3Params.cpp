#include "../UnitsState.func.hpp"

#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00537130
        void UnitsState::queueDisbandAndAttackCommand3Params(
            undefined4 commandParam0, undefined4 commandParam1, undefined4 commandParam2)
        {
            DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = commandParam0;
            DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = commandParam1;
            DAT_GameSynchronyState::instance.DAT_GameCommandParam2 = commandParam2;
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                OpenSHC::Commands::GCT_DISBAND_AND_ATTACK_UNITS);
        }

    }
}
}
