#include "../UnitsState.func.hpp"

#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00537130
        void UnitsState::queueDisbandAndAttackCommand3Params(int tribeID, UnitInstructionType instruction, int targetID)
        {
            DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = tribeID;
            DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = instruction;
            DAT_GameSynchronyState::instance.DAT_GameCommandParam2 = targetID;
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                OpenSHC::Commands::GCT_DISBAND_AND_ATTACK_UNITS);
        }

    }
}
}
