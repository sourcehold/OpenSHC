#include "../UnitsState.func.hpp"

#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Commands::GameCommandType;

        // FUNCTION: STRONGHOLDCRUSADER 0x00536C90
        void UnitsState::queueUnitTypeCommand(undefined4 unitType)
        {
            DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = -1;
            DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = unitType;
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                OpenSHC::Commands::GCT_ESCAPE);
        }

    }
}
}
