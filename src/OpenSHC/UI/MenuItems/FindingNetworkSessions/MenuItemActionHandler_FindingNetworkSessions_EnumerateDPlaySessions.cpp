#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/UI.func.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace FindingNetworkSessions {

            // FUNCTION: STRONGHOLDCRUSADER 0x0048BF70
            void MenuItemActionHandler_FindingNetworkSessions_EnumerateDPlaySessions(int param_1, ...)
            {
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::restartDPlaySessionEnumeration,
                    DAT_GameSynchronyState::ptr)(param_1);
            }

        }
    }
}
}
