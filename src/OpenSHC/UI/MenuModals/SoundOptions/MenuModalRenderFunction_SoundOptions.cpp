#include "OpenSHC/UI/MenuModals/SoundOptions.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"

#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuModals {
        namespace SoundOptions {

            // FUNCTION: STRONGHOLDCRUSADER 0x00492660
            void MenuModalRenderFunction_SoundOptions(int x, int y, int width, int height)
            {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawHeaderTextBanner,
                    DAT_PencilRenderCore::ptr)(0x4a, 5, x, y, width);
            }

        }
    }
}
}
