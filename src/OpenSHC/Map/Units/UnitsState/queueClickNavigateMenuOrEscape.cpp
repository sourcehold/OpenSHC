#include "../UnitsState.func.hpp"

#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Commands::GameCommandType;

        // FUNCTION: STRONGHOLDCRUSADER 0x00536CC0
        void UnitsState::queueClickNavigateMenuOrEscape(undefined4 param_1)
        {
            DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = -1;
            DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = param_1;
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                OpenSHC::Commands::GCT_ESCAPE);
        }

    }
}
}
