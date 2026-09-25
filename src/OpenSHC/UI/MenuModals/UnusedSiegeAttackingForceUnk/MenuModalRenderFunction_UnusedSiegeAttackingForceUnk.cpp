#include "OpenSHC/UI/MenuModals/UnusedSiegeAttackingForceUnk.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"

#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuModals {
        namespace UnusedSiegeAttackingForceUnk {

            // FUNCTION: STRONGHOLDCRUSADER 0x004AB510
            void MenuModalRenderFunction_UnusedSiegeAttackingForceUnk(int x, int y, int width, int height)
            {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawHeaderTextBanner,
                    DAT_PencilRenderCore::ptr)(199, 0xa4, x, y, width, height);
            }

        }
    }
}
}
