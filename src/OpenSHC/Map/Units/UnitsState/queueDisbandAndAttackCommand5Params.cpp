#include "../UnitsState.func.hpp"

#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Commands::GameCommandType;

        // FUNCTION: STRONGHOLDCRUSADER 0x005371A0
        void UnitsState::queueDisbandAndAttackCommand5Params(undefined4 commandParam0, UnitInstructionType instruction,
            undefined4 commandParam2, undefined4 commandParam3, undefined4 commandParam4)
        {
            DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = commandParam0;
            DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = instruction;
            DAT_GameSynchronyState::instance.DAT_GameCommandParam2 = commandParam2;
            DAT_GameSynchronyState::instance.DAT_GameCommandParam3 = commandParam3;
            DAT_GameSynchronyState::instance.DAT_GameCommandParam4 = commandParam4;
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                OpenSHC::Commands::GCT_DISBAND_AND_ATTACK_UNITS);
        }

    }
}
}
