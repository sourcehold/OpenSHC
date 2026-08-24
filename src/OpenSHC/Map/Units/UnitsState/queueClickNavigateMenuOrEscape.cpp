#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Commands::GameCommandType;

        /*
          WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
         */

        /*
          WARNING: Enum "DPERRInt": Some values do not have unique names
         */

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */

        // FUNCTION: STRONGHOLDCRUSADER 0x00536CC0
        void UnitsState::queueClickNavigateMenuOrEscape(undefined4 param_1)

        {
            DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = 0xfffffffe;
            DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = param_1;
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                OpenSHC::Commands::GCT_ESCAPE);
            return;
        }

    }
}
}
