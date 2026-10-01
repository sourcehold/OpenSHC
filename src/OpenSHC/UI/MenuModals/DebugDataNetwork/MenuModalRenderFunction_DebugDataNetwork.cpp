#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/UI/MenuModals/DebugDataNetwork.func.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuModals {
        namespace DebugDataNetwork {

            // FUNCTION: STRONGHOLDCRUSADER 0x004AAAE0
            void MenuModalRenderFunction_DebugDataNetwork(int x, int y, int width, int height)
            {
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::renderDebugDataNetwork,
                    DAT_GameSynchronyState::ptr)(x, y, width, height);
            }

        }
    }
}
}
