#include "../AICState.func.hpp"

#include "OpenSHC/AI/AITypeA.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004D18B0
    void AICState::setInitialAIC()
    {
        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::wipeAICMemory, this)();

        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::setAICParameters_01, this)(OpenSHC::AI::AITA_RAT);

        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::setAICParameters_02, this)(OpenSHC::AI::AITA_SNAKE);

        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::setAICParameters_03, this)(OpenSHC::AI::AITA_PIG);

        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::setAICParameters_04, this)(OpenSHC::AI::AITA_WOLF);

        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::setAICParameters_05, this)(OpenSHC::AI::AITA_SALADIN);

        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::setAICParameters_06, this)(OpenSHC::AI::AITA_CALIPH);

        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::setAICParameters_07, this)(OpenSHC::AI::AITA_SULTAN);

        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::setAICParameters_08, this)(OpenSHC::AI::AITA_RICHARD);

        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::setAICParameters_09, this)(OpenSHC::AI::AITA_FREDERICK);

        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::setAICParameters_10, this)(OpenSHC::AI::AITA_PHILIPP);

        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::setAICParameters_11, this)(OpenSHC::AI::AITA_WAZIR);

        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::setAICParameters_12, this)(OpenSHC::AI::AITA_EMIR);

        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::setAICParameters_13, this)(OpenSHC::AI::AITA_NIZAR);

        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::setAICParameters_14, this)(OpenSHC::AI::AITA_SHERIFF);

        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::setAICParameters_15, this)(OpenSHC::AI::AITA_MARSHAL);

        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::setAICParameters_16, this)(OpenSHC::AI::AITA_ABBOT);
    }

}
}
