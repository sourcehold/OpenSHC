#include "OpenSHC/UI/MenuModals/GameplayOptions.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"

#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuModals {
        namespace GameplayOptions {

            // FUNCTION: STRONGHOLDCRUSADER 0x00491E80
            void MenuModalRenderFunction_GameplayOptions(int x, int y, int width, int height)
            {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawHeaderTextBanner,
                    DAT_PencilRenderCore::ptr)(0x4a, 0x19, x, y, width);
            }

        }
    }
}
}
