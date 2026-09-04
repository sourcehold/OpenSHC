#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Commands::GameCommandType;

        // FUNCTION: STRONGHOLDCRUSADER 0x00536C70
        void UnitsState::queueEscapeCommand()
        {
            DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = 0;
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                (GameCommandType)0xf);
        }

    }
}
}
