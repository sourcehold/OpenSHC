#include "OpenSHC/UI/MenuModals/SkirmishConnectionOptions.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"

#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuModals {
        namespace SkirmishConnectionOptions {

            // FUNCTION: STRONGHOLDCRUSADER 0x004ABE50
            void MenuModalRenderFunction_SkirmishConnectionOptions(int x, int y, int width, int height)
            {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawHeaderTextBanner,
                    DAT_PencilRenderCore::ptr)(0x4f, 0x5d, x, y, width, height);
            }

        }
    }
}
}
