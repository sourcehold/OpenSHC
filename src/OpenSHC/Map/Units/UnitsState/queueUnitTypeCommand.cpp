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

        // FUNCTION: STRONGHOLDCRUSADER 0x00536C90
        void UnitsState::queueUnitTypeCommand(undefined4 unitType)

        {
            DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = 0xffffffff;
            DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = unitType;
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                OpenSHC::Commands::GCT_ESCAPE);
            return;
        }

    }
}
}
