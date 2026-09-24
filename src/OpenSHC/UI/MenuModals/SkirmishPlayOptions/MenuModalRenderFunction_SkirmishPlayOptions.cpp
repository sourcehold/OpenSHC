#include "OpenSHC/UI/MenuModals/SkirmishPlayOptions.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"

#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuModals {
        namespace SkirmishPlayOptions {

            // FUNCTION: STRONGHOLDCRUSADER 0x004ABE80
            void MenuModalRenderFunction_SkirmishPlayOptions(int x, int y, int width, int height)
            {

                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawHeaderTextBanner,
                    DAT_PencilRenderCore::ptr)(0x4f, 0x67, x, y, width);
            }

        }
    }
}
}
