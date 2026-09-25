#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/UI/MenuModals/DebugDataAiInfo.func.hpp"

#include "OpenSHC/Globals/DAT_AICState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuModals {
        namespace DebugDataAiInfo {

            // FUNCTION: STRONGHOLDCRUSADER 0x004AAA60
            void MenuModalRenderFunction_DebugDataAiInfo(int x, int y, int width, int height)
            {
                MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::renderDebugDataAiInfo, DAT_AICState::ptr)(
                    x, y, width, height);
            }

        }
    }
}
}
