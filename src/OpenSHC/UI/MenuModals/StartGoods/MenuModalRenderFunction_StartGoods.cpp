#include "OpenSHC/UI/MenuModals/StartGoods.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"

#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuModals {
        namespace StartGoods {

            // FUNCTION: STRONGHOLDCRUSADER 0x004AB4E0
            void MenuModalRenderFunction_StartGoods(int x, int y, int width, int height)
            {

                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawHeaderTextBanner,
                    DAT_PencilRenderCore::ptr)(199, 0x29, x, y, width);
            }

        }
    }
}
}
