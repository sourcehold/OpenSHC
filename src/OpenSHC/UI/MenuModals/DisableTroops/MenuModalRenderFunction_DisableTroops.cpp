#include "../DisableTroops.func.hpp"

#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"

#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuModals {
        namespace DisableTroops {

            // FUNCTION: STRONGHOLDCRUSADER 0x004ABCB0
            void MenuModalRenderFunction_DisableTroops(int x, int y, int width, int height)
            {
                // "Troops"
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawHeaderTextBanner,
                    DAT_PencilRenderCore::ptr)(OpenSHC::DE::SHCDE::TEXT_SCENARIO, 188, x, y, width, height);
            }

        }
    }
}
}
