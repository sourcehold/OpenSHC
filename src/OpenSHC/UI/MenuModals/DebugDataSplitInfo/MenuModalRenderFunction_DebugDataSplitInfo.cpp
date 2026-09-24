#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/UI/MenuModals/DebugDataSplitInfo.func.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuModals {
        namespace DebugDataSplitInfo {

            // FUNCTION: STRONGHOLDCRUSADER 0x004AAB00
            void MenuModalRenderFunction_DebugDataSplitInfo(int x, int y, int width, int height)
            {
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::renderDebugDataSplitInfo,
                    DAT_GameSynchronyState::ptr)(x, y, width, height);
            }

        }
    }
}
}
