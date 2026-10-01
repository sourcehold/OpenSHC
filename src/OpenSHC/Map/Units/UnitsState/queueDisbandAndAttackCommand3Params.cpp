#include "../UnitsState.func.hpp"

#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Commands::GameCommandType;

        // FUNCTION: STRONGHOLDCRUSADER 0x00537130
        void UnitsState::queueDisbandAndAttackCommand3Params(undefined4 param_1, undefined4 param_2, undefined4 param_3)
        {
            DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = param_1;
            DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = param_2;
            DAT_GameSynchronyState::instance.DAT_GameCommandParam2 = param_3;
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                OpenSHC::Commands::GCT_DISBAND_AND_ATTACK_UNITS);
        }

    }
}
}
