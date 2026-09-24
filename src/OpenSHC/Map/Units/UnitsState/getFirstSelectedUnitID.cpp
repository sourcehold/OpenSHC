#include "../UnitsState.func.hpp"

#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Commands::GameCommandType;

        // FUNCTION: STRONGHOLDCRUSADER 0x00535DF0
        void UnitsState::getFirstSelectedUnitID(undefined4 param_1)
        {
            DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = param_1;
            DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = DAT_TribesState::instance.DAT_CurrentTribeID;
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                ((GameCommandType)0x48));
        }

    }
}
}
