#include "OpenSHC/UI/MenuModals/NetworkOptions.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"

#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuModals {
        namespace NetworkOptions {

            // FUNCTION: STRONGHOLDCRUSADER 0x00492A60
            void MenuModalRenderFunction_NetworkOptions(int x, int y, int width, int height)
            {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawHeaderTextBanner,
                    DAT_PencilRenderCore::ptr)(0x4a, 6, x, y, width);
            }

        }
    }
}
}
