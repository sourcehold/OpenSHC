#include "../CreateOrTriggerInvasion.func.hpp"

#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"

#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuModals {
        namespace CreateOrTriggerInvasion {

            // FUNCTION: STRONGHOLDCRUSADER 0x004AB540
            void MenuModalRenderFunction_CreateOrTriggerInvasion(int x, int y, int width, int height)
            {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawHeaderTextBanner,
                    DAT_PencilRenderCore::ptr)(OpenSHC::DE::SHCDE::TEXT_SCENARIO, 46, x, y, width, height);
            }

        }
    }
}
}
