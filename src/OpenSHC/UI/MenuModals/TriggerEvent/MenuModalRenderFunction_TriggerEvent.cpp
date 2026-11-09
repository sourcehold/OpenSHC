#include "../TriggerEvent.func.hpp"

#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"

#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuModals {
        namespace TriggerEvent {

            // FUNCTION: STRONGHOLDCRUSADER 0x004AC250
            void MenuModalRenderFunction_TriggerEvent(int x, int y, int width, int height)
            {
                // "Events"
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawHeaderTextBanner,
                    DAT_PencilRenderCore::ptr)(OpenSHC::DE::SHCDE::TEXT_SCENARIO, 23, x, y, width, height);
            }

        }
    }
}
}
