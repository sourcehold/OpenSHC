#include "OpenSHC/UI/MenuModals/OptionsMenu.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"

#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuModals {
        namespace OptionsMenu {

            // FUNCTION: STRONGHOLDCRUSADER 0x00491810
            void MenuModalRenderFunction_OptionsMenu(int x, int y, int width, int height)
            {

                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawHeaderTextBanner,
                    DAT_PencilRenderCore::ptr)(0x4a, 1, x, y, width);
            }

        }
    }
}
}
