#include "OpenSHC/UI/MenuModals/TriggerEvent.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"

#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuModals {
        namespace TriggerEvent {

            // FUNCTION: STRONGHOLDCRUSADER 0x004AC250
            void MenuModalRenderFunction_TriggerEvent(int x, int y, int width, int height)
            {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawHeaderTextBanner,
                    DAT_PencilRenderCore::ptr)(199, 0x17, x, y, width, height);
            }

        }
    }
}
}
