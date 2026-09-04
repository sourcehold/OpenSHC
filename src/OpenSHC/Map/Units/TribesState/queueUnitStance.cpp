#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Commands::GameCommandType;

        // FUNCTION: STRONGHOLDCRUSADER 0x00522BF0
        void TribesState::queueUnitStance(undefined4 stanceID, undefined4 param_2)
        {
            DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = stanceID;
            DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = param_2;

            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                OpenSHC::Commands::GCT_UNIT_STANCE);
        }

    }
}
}
