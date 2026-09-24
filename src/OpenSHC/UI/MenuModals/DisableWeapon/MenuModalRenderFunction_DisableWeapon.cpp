#include "OpenSHC/UI/MenuModals/DisableWeapon.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"

#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuModals {
        namespace DisableWeapon {

            // FUNCTION: STRONGHOLDCRUSADER 0x004ABCE0
            void MenuModalRenderFunction_DisableWeapon(int x, int y, int width, int height)
            {

                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawHeaderTextBanner,
                    DAT_PencilRenderCore::ptr)(199, 0xbd, x, y, width);
            }

        }
    }
}
}
